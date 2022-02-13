//
// Created by maicss on 2022/2/12.
//

#ifndef DEPENDMANAGER_BSPARSER_H
#define DEPENDMANAGER_BSPARSER_H

#include <string>
#include <vector>
struct DependEntry {
    std::string name;
    bool installed;
    bool optional;
};
enum LOG_LEVEL{
    NORMAL,
    WARRING,
    ERROR
};
typedef void ProgressCallbackFun(int progress, std::string log, LOG_LEVEL logLevel, void* userData);
typedef std::vector<DependEntry> DependList;
class BSParser {
public:
    BSParser();
    /**
     * 设置解析器的目标项目目录。
     * @param path 项目在文件系统中的绝对路径。
     */
    void setProjectPath(std::string path);
    /**
     * 判断是否支持当前解析器。若为XMake解析器，则判断当前目录是否存在xmake.lua，其他同理。
     * @return 支持则返回true
     */
    virtual bool isValid()=0;
    /**
     * 解析获得当前项目的所需依赖列表
     * @param dependList 返回的结果
     * @return 是否解析成功
     */
    virtual bool getDepends(DependList &dependList)=0;
    /**
     * 设置进度更新的回调函数
     * @param callback 回调函数原型：void ProgressCallbackFun(int progress, std::string log)
     */
    void setProgressCallback(ProgressCallbackFun callback);
    /**
     * 设置用户数据指针，在进度更新回调函数被调用时，将作为参数传入该指针。
     * @param data 用户数据指针。
     */
    void setUserData(void *data);

    static std::string exe_path;
protected:

    void updateProgress(int progress, std::string log="", LOG_LEVEL logLevel=NORMAL);
    std::string m_path;
    ProgressCallbackFun *progressCallbackFun;
    void *m_userData;

};


#endif //DEPENDMANAGER_BSPARSER_H
