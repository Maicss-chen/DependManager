//
// Created by maicss on 2022/2/12.
//

#include "PageWorking.h"
#include <QLayout>
#include <QStackedWidget>
PageWorking::PageWorking() {
    m_label1.setText("正在解析中");
    setProjectName("XXX");
    m_progressBar.setMaximum(100);
    m_progressBar.setValue(20);
    m_saveLog.setText("保存日志");
    m_logShower.append("开始解析");
    m_lastPage.setText("上一步");
    m_nextPage.setText("下一步");
    m_close.setText("取消");

    auto *layout = new QVBoxLayout;
    layout->addWidget(&m_label1);
    layout->addWidget(&m_label2);
    layout->addWidget(&m_progressBar);

    auto *layout1 = new QHBoxLayout;
    layout1->addWidget(&m_saveLog);
    layout1->addStretch();
    layout->addLayout(layout1);

    layout->addWidget(&m_logShower);

    auto *layout2 = new QHBoxLayout;
    layout2->addStretch();
    layout2->addWidget(&m_lastPage);
    layout2->addWidget(&m_nextPage);
    layout2->addWidget(&m_close);
    layout->addLayout(layout2);

    setLayout(layout);

    connect(&m_nextPage,&QPushButton::clicked,[=](){
        ((QStackedWidget*)parentWidget())->setCurrentIndex(((QStackedWidget*)parentWidget())->currentIndex()+1);
    });
    connect(&m_lastPage,&QPushButton::clicked,[=](){
        ((QStackedWidget*)parentWidget())->setCurrentIndex(((QStackedWidget*)parentWidget())->currentIndex()-1);
    });

}

void PageWorking::setProjectName(const QString& name) {
    m_label2.setText(name + " 项目正在解析中，请稍候...");
}

void PageWorking::setProgress(int value) {
    m_progressBar.setValue(value);
    if (value == m_progressBar.maximum()){
        m_label2.setText("解析完成，请点击下一步。");
    }
}

void PageWorking::printLog(const QString& log) {
    m_logShower.append(log);
}

void PageWorking::cleanLog() {
    m_logShower.clear();
}
