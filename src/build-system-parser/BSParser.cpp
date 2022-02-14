//
// Created by maicss on 2022/2/12.
//

#include "BSParser.h"

#include <utility>
void BSParser::setProjectPath(std::string path) {
    m_path=std::move(path);
}

void BSParser::setProgressCallback(ProgressCallbackFun callback) {
    progressCallbackFun = callback;
}

BSParser::BSParser() {
    progressCallbackFun = nullptr;
    m_userData = nullptr;
}

void BSParser::updateProgress(int progress, std::string log, LOG_LEVEL logLevel) {\
    if (progressCallbackFun != nullptr){\
        progressCallbackFun(progress,std::move(log),logLevel,m_userData);
    }
}

void BSParser::setUserData(void *data) {
    m_userData = data;
}
