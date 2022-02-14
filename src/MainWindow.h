//
// Created by maicss on 2022/2/12.
//

#ifndef DEPENDMANAGER_MAINWINDOW_H
#define DEPENDMANAGER_MAINWINDOW_H
#include <QDialog>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "pages.h"
#include "build-system-parser/XMakeBSParser.h"
class MainWindow : public QDialog{
    Q_OBJECT
public:
    MainWindow();

private:
    void closeEvent(QCloseEvent* event) override;
    void initPages();
    QStackedWidget m_stackWidget;

    PageOpenProject m_pageOpenProject;
    PageBSChoose m_pageBSChoose;
    PageWorking m_pageWorking;
    PageDependChoose m_pageDependChoose;
    PageInstallWorking m_pageInstallWorking;

    void startChooseBS();
    void startParse();
    void startChooseDepend();
    void startInstall();


    BuildSystem bs;
    DependList m_dependList;
    DependList m_installList;

    std::vector<std::string> sourceList;
};


#endif //DEPENDMANAGER_MAINWINDOW_H
