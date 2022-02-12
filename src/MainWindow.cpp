//
// Created by maicss on 2022/2/12.
//

#include "MainWindow.h"
#include <QLayout>
#include <QFileInfo>
#include "build-system/BSParser.h"
#include "build-system/XMakeBSParser.h"
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

    m_stackWidget.setCurrentIndex(0);

    connect(&m_stackWidget,&QStackedWidget::currentChanged,[=](){
        if (m_stackWidget.currentWidget() == &m_pageBSChoose)
            startChooseBS();
        else if (m_stackWidget.currentWidget() == &m_pageWorking)
            startParse();
        else if (m_stackWidget.currentWidget() == &m_pageDependChoose)
            startChooseDepend();
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
    disconnect(&m_stackWidget);
    QDialog::closeEvent(event);
}
