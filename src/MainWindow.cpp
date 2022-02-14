//
// Created by maicss on 2022/2/12.
//

#include "package-installer/PackageInstaller.h"
#include "MainWindow.h"

#include <QLayout>
#include <QFileInfo>
#include <QProcess>
#include "build-system-parser/BSParser.h"
#include "build-system-parser/XMakeBSParser.h"
MainWindow::MainWindow() {
    setWindowTitle("依赖处理工具");
    setFixedSize(600,400);
    QHBoxLayout *layout1 = new QHBoxLayout;
    initPages();
    layout1->addWidget(&m_stackWidget);
    setLayout(layout1);
    m_stackWidget.show();
}

void MainWindow::initPages() {
    m_stackWidget.addWidget(&m_pageOpenProject);

    m_stackWidget.addWidget(&m_pageBSChoose);

    m_stackWidget.addWidget(&m_pageWorking);

    m_stackWidget.addWidget(&m_pageDependChoose);

    m_stackWidget.addWidget(&m_pageInstallWorking);

    m_stackWidget.setCurrentIndex(0);

    connect(&m_stackWidget,&QStackedWidget::currentChanged,[=](){
        if (m_stackWidget.currentWidget() == &m_pageBSChoose)
            startChooseBS();
        else if (m_stackWidget.currentWidget() == &m_pageWorking)
            startParse();
        else if (m_stackWidget.currentWidget() == &m_pageDependChoose)
            startChooseDepend();
        else if (m_stackWidget.currentWidget() == &m_pageInstallWorking)
            startInstall();
    });
}

void MainWindow::startParse() {
    bs = m_pageBSChoose.getBS();
    BSParser *parser;
    switch (bs) {
        case XMake:
            parser = new XMakeBSParser;
            break;
        case CMake:
        case NONE:
            return;
    }
    m_pageWorking.cleanLog();
    parser->setProjectPath(m_pageOpenProject.getPath().toStdString());
    parser->setUserData(this);
    parser->setProgressCallback([](int progress, std::string log, LOG_LEVEL,void *data){
        ((MainWindow*)data)->m_pageWorking.setProgress(progress);
        ((MainWindow*)data)->m_pageWorking.printLog(QString::fromStdString(log));
    });
    parser->getDepends(m_dependList);

}

void MainWindow::startChooseBS() {
    QString path = m_pageOpenProject.getPath();

    QFileInfo fileInfo(path);
    m_pageWorking.setProjectName(fileInfo.fileName());

    m_pageBSChoose.cleanBSOptions();
    fileInfo.setFile(path+"/xmake.lua");
    if (fileInfo.exists()) m_pageBSChoose.addBSOption(BuildSystem::XMake);

    fileInfo.setFile(path+"/CMakeLists.txt");
    if (fileInfo.exists()) m_pageBSChoose.addBSOption(BuildSystem::CMake);
}

void MainWindow::startChooseDepend() {
    m_pageDependChoose.setDependList(m_dependList);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    m_stackWidget.disconnect();
    QDialog::closeEvent(event);
}

void MainWindow::startInstall() {
    m_installList = m_pageDependChoose.getInstallList();
    m_pageInstallWorking.printLog("即将安装以下依赖：");
    for (const auto& item : m_installList){
        m_pageInstallWorking.printLog(QString::fromStdString(item.name));
    }
    m_pageInstallWorking.printLog("开始更新软件包缓存");
    auto installer = new PackageInstaller;
    m_pageInstallWorking.setStepCount(3);
    installer->setUserData(this);
    installer->setProgressCallbackFun([](int progress, std::string log, void* userData){
        auto _this = (MainWindow*)userData;
        if (!log.empty())
            _this->m_pageInstallWorking.printLog(QString::fromStdString(log));
        _this->m_pageInstallWorking.setProgress(0,progress);
    });
    installer->setReadyCallbackFun([](bool success,PackageInstaller *me, void* userData){
        auto _this = (MainWindow*)userData;
        if(success){
            _this->m_pageInstallWorking.printLog("软件包缓存更新完成");
            _this->m_pageInstallWorking.printLog("开始查找源码包");
            me->setProgressCallbackFun([](int progress, std::string log, void* userData){
                auto _this = (MainWindow*)userData;;
                if (!log.empty())
                    _this->m_pageInstallWorking.printLog(QString::fromStdString(log));
                _this->m_pageInstallWorking.setProgress(1,progress);
            });
            me->setReadyCallbackFun([](bool success,PackageInstaller *me, void* userData){});
            std::vector<std::string> tmpList;
            for (auto p : _this->m_installList){
                tmpList.emplace_back(p.name);
            }
            for (auto p : me->searchSourcePackage(tmpList)) {
                for (auto t : p.m_package_list) {
                    _this->sourceList.emplace_back(t);
                }
            }
            auto _this = (MainWindow*)userData;
            if (!_this->sourceList.empty()){
                _this->m_pageInstallWorking.printLog("开始安装");
                me->setProgressCallbackFun([](int progress, std::string log, void* userData){
                    auto _this = (MainWindow*)userData;;
                    if (!log.empty())
                        _this->m_pageInstallWorking.printLog(QString::fromStdString(log));
                    _this->m_pageInstallWorking.setProgress(2,progress);
                });
                me->setReadyCallbackFun([](bool success,PackageInstaller *me, void* userData){
                    auto _this = (MainWindow*)userData;
                    if (success){
                        _this->m_pageInstallWorking.printLog("安装成功");
                        _this->m_pageInstallWorking.setProgress(0,100);
                        _this->m_pageInstallWorking.setProgress(1,100);
                        _this->m_pageInstallWorking.setProgress(2,100);
                    } else{
                        _this->m_pageInstallWorking.printLog("安装失败");
                    }
                });
                me->installPackages(_this->sourceList);
            } else
                _this->m_pageInstallWorking.printLog("没有找到需要安装的源码包");
        }
        else
            _this->m_pageInstallWorking.printLog("软件包缓存更新失败");
    });
    installer->updateCache();
}
