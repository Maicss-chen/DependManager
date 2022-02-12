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
#include "build-system/XMakeBSParser.h"
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

    void startChooseBS();
    void startParse();
    void startChooseDepend();

    BuildSystem bs;
    DependList m_dependList;
};


#endif //DEPENDMANAGER_MAINWINDOW_H
