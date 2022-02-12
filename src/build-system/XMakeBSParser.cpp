//
// Created by maicss on 2022/2/12.
//

#include "XMakeBSParser.h"
#include <filesystem>
#include <cjson/cJSON.h>
#include <csignal>

using namespace std;
bool XMakeBSParser::isValid() {
    filesystem::path path(this->m_path+"/xmake.lua");
    return exists(path);
}

bool XMakeBSParser::getDepends(DependList &dependList) {

    updateProgress(5,"开始解析",NORMAL);
    string xmake_exe("xmake");
    updateProgress(10,"检查XMake是否存在",NORMAL);
    if(xmake_exe.empty()) {
        printf("cant find xmake\n");
        updateProgress(10,"没有找到XMake",ERROR);
        return false;
    }
    string xmake_script_dir = string(get_current_dir_name())+"/xmake";
    updateProgress(20,"检查info.lua是否存在",NORMAL);
    if(xmake_script_dir == "") {
        updateProgress(20,"没有找到info.lua",NORMAL);
        return false;
    }
    char olddir[1024];
    getcwd(olddir, sizeof(olddir));

    updateProgress(25,"进入目录："+m_path,NORMAL);
    chdir(m_path.c_str());
    string command_line = xmake_exe+" lua "+xmake_script_dir+"/info.lua";
    string clear_cache = xmake_exe+" f -c";


    updateProgress(30,"清除XMake缓存",NORMAL);
    /*
     * first clear the xmake cache.
    */
    FILE* xmake_ccfp = popen(clear_cache.c_str(), "r");
    pclose(xmake_ccfp);

    updateProgress(35,"开始解析依赖项",NORMAL);
    /*
     * execute command_line in tty, then get return to a json, finnaly use apt to install.
    */
    FILE* fp = popen(command_line.c_str(), "r");

    chdir(olddir);
    updateProgress(40,"进入目录："+string(olddir),NORMAL);

    char line[4096];

    if (fp == NULL) {
        updateProgress(45,"解析依赖项失败",NORMAL);
        printf("Popen Error!\n");
        return false;
    }

    if(fgets(line, 4096, fp) == NULL) {
        updateProgress(45,"不能解析出依赖列表，请检查xmake.lua是否存在且格式是否正常");
        return false;
    }
    else {
        //parse the terminal output as a json.
        cJSON* jsonroot = cJSON_Parse(line);
        if(!jsonroot) {
            updateProgress(60,"在解析json时报错："+string(cJSON_GetErrorPtr())+"\ninfo.lua可能返回了一个无效的结果",ERROR);
            return false;
        }
        unsigned jsonsize = cJSON_GetArraySize(jsonroot);
        if(jsonsize == 0) {
            updateProgress(60,"xmake.lua 中可能没有有效的“add_requires”元素",ERROR);
            return false;
        }
        dependList.clear();
        for(unsigned i = 0; i < jsonsize; ++i) {
            cJSON *item = cJSON_GetArrayItem(jsonroot, i);
            DependEntry entry;
            entry.name = item->string;
            string installed = cJSON_PrintUnformatted(cJSON_GetObjectItem(item, "installed"));
            entry.installed = (installed == "true");
            string optional = cJSON_PrintUnformatted(cJSON_GetObjectItem(item, "optional"));
            entry.optional = (optional == "true");
            dependList.emplace_back(entry);
        }

        updateProgress(100,"依赖列表解析成功",NORMAL);
    }
    pclose(fp);
    return false;
}
