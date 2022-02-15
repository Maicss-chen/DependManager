//
// Created by maicss on 2022/2/13.
//

#ifndef DEPENDMANAGER_PACKAGEINSTALLER_H
#define DEPENDMANAGER_PACKAGEINSTALLER_H
//compatability for old packagekit version.
#ifndef I_KNOW_THE_PACKAGEKIT_GLIB2_API_IS_SUBJECT_TO_CHANGE
#define I_KNOW_THE_PACKAGEKIT_GLIB2_API_IS_SUBJECT_TO_CHANGE

#include <string>
#include <vector>
#include <packagekit-glib2/packagekit.h>

class PackageInstaller;
typedef void InstallProgressCallbackFun(int progress, std::string log, void* userData);
typedef void InstallReadyCallback(bool success,PackageInstaller *me,void* userData);
struct SourcePackage{
    std::string name;
    std::string version;
    std::vector<std::string> m_package_list;
};
class PackageInstaller{
public:
    PackageInstaller();
    ~PackageInstaller();
    void updateCache();
    std::vector<SourcePackage> searchSourcePackage(std::vector<std::string> packages);
    void installPackages(std::vector<std::string> packages);
    void setUserData(void *data);
    void setProgressCallbackFun(InstallProgressCallbackFun fun);
    void setReadyCallbackFun(InstallReadyCallback fun);
private:
    PkTask *m_task{};
    PkProgressCallback _progressCallback;
    GAsyncReadyCallback _readCallback;
    InstallProgressCallbackFun *m_callback;
    InstallReadyCallback *m_readCallback;
    void *m_userData;

};

#endif
#endif //DEPENDMANAGER_PACKAGEINSTALLER_H
