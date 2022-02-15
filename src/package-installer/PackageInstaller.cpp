//
// Created by maicss on 2022/2/13.
//

#include "PackageInstaller.h"
#include <filesystem>
#include <fstream>
using namespace std;
PackageInstaller::PackageInstaller() {
    m_task = pk_task_new();
    _progressCallback = [](_PkProgress *progress, PkProgressType type, gpointer user_data) {
        if(user_data == nullptr) return ;
        auto _this = ((PackageInstaller*) user_data);
        if (_this->m_callback == nullptr) return;
        _this->m_callback(pk_progress_get_percentage(progress),"", _this->m_userData);
    };
    _readCallback = [](GObject *source_object,
                        GAsyncResult *res,
                        gpointer user_data){

        auto _this = ((PackageInstaller*) user_data);
        GError *error;
        g_async_result_legacy_propagate_error(res,&error);

        if (_this->m_readCallback == nullptr) return;
        _this->m_readCallback(error->code == 0, _this ,_this->m_userData);
    };
}

PackageInstaller::~PackageInstaller() {
    g_object_unref (m_task);
}

void PackageInstaller::updateCache() {
    pk_task_refresh_cache_async(m_task, false, nullptr, _progressCallback,
                                this, _readCallback, this);
}

void PackageInstaller::setProgressCallbackFun(InstallProgressCallbackFun fun) {
    m_callback = fun;
}

void PackageInstaller::setUserData(void *data) {
    m_userData = data;
}

void PackageInstaller::setReadyCallbackFun(InstallReadyCallback fun) {
    m_readCallback = fun;
}

std::vector<SourcePackage> PackageInstaller::searchSourcePackage(std::vector<std::string> packages) {
    vector<SourcePackage> res;
    std::vector<string> sources;
    m_callback(5,"检查缓存", m_userData);
    filesystem::path cacheDir("/var/lib/apt/lists/");
    filesystem::directory_entry entry(cacheDir);
    if(!entry.exists()){
        m_callback(5,"目录 /var/lib/apt/lists 不存在",m_userData);
        m_readCallback(false, this,m_userData);
        return res;
    }

    if(entry.status().type() != filesystem::file_type::directory){
        m_callback(5,"/var/lib/apt/lists 不是一个目录",m_userData);
        m_readCallback(false,this, m_userData);
        return res;
    }

    m_callback(20,"正在检查源码包缓存数据",m_userData);
    filesystem::directory_iterator iterator(cacheDir);
    for(auto& it:iterator){
        if(it.path().filename().string().find("_Sources")!=string::npos)
            sources.emplace_back(it.path().filename().string());
    }
    if(sources.empty()){
        m_callback(10,"没有找到源码包数据，请对源码仓库取消注释，并且尝试执行apt update后再试。",m_userData);
        m_readCallback(false, this ,m_userData);
        return res;
    }

    m_callback(30,"正在查找源码包",m_userData);
    for(const auto& source : sources){
        fstream file;
        file.open(cacheDir.string()+source, ios::in);
        if (!file)
        {
            continue;
        }
        string line;
        SourcePackage sourcesEntry;
        bool thisOne = false;
        bool readPackageList = false;
        while (getline(file, line))
        {
            if(line.empty()){
                if(thisOne == true){
                    m_callback(50,"在"+sourcesEntry.name+"中需要包含：",m_userData);
                    for (auto p:sourcesEntry.m_package_list) {
                        m_callback(50,"\t"+p,m_userData);
                    }
                    res.emplace_back(sourcesEntry);
                }
                thisOne = false;
                readPackageList = false;
                sourcesEntry.m_package_list.clear();
                continue;
            }
            if(line.substr(0,8)=="Package:"){
                sourcesEntry.name = line.substr(9,line.length()-9);
                for (int i = 0; i < packages.size(); ++i) {
                    if(packages.at(i) == sourcesEntry.name){
                        thisOne = true;
                        continue;
                    }
                }
            }
            if(thisOne && line.substr(0, 8) == "Version:"){
                sourcesEntry.version = line.substr(9,line.length()-9);
            }
            if(thisOne && line.substr(0, 13) == "Package-List:"){
                readPackageList = true;
                continue;
            }
            if(line.find(':') != string::npos){
                readPackageList = false;
            }
            if (thisOne && readPackageList) {
                sourcesEntry.m_package_list.emplace_back(line.substr(1,line.find_first_of(' ',2)-1));
            }
        }
        file.close();
    }
    m_readCallback(true,this,m_userData);
    return res;
}

void PackageInstaller::installPackages(vector<string> packages) {
    gchar **values;
    GPtrArray *array = nullptr;
    PkPackage *item;
    gchar **package_ids = nullptr;
    PkResults *results = nullptr;
    GError *error = nullptr;
    std::vector<PkPackage> res;
    if (packages.empty()){
        m_callback(5,"没有任何包需要安装",m_userData);
        return;
    }
    m_callback(5,"正在查找包",m_userData);
    values = g_new0 (gchar*, packages.size()+1);
    for (int i=0;i<packages.size();i++) {
        values[i] = g_strdup(packages.at(i).c_str());
    }
    values[packages.size()] = nullptr;
    results = pk_task_resolve_sync(m_task,PK_FILTER_ENUM_NOT_INSTALLED,values,nullptr,_progressCallback,this,&error);
    if (error){
        m_callback(10,"包查找失败，请将以下错误日志发送给 maicss@126.com 帮助我们解决问题",m_userData);
        m_callback(10,error->message,m_userData);
        g_error_free (error);
    }
    array = pk_results_get_package_array (results);
    for (int i = 0; i < array->len; i++) {
        item = (PkPackage*)g_ptr_array_index(array, i);
        if (pk_package_get_info(item) != PK_INFO_ENUM_INSTALLED){
#ifdef _x86_64_
            if(string (pk_package_get_arch(item)) == "amd64" ||
               string (pk_package_get_arch(item)) == "x86_64"){
                res.emplace_back(*item);
            }
#elif _x86_
            if(string (pk_package_get_arch(item)) == "i386" ||
               string (pk_package_get_arch(item)) == "x86"){
                package_ids[i] = g_strdup (pk_package_get_id ((_PkPackage*)item));
                res.emplace_back(*item);
            }
#endif

        }
    }

    g_strfreev(values);

    package_ids = g_new0 (gchar *, res.size()+1);

    for (int i = 0; i < res.size(); i++) {
        package_ids[i] = g_strdup(pk_package_get_id (&res[i]));
    }

    package_ids[res.size()]= nullptr;


    if (res.empty()){
        m_callback(100,"没有可以安装的软件包。",m_userData);
        m_readCallback(true,this,m_userData);
        return;
    }
    //安装所有软件包
    m_callback(5,"开始安装",m_userData);
    pk_task_install_packages_async(m_task, package_ids, nullptr, _progressCallback,
                                   this, _readCallback,this);
    g_strfreev(package_ids);

}


