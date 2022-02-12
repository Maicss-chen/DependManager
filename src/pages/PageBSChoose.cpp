//
// Created by maicss on 2022/2/12.
//

#include "PageBSChoose.h"
#include <QLayout>
#include <QStackedWidget>

PageBSChoose::PageBSChoose() {
    m_label1.setText("构建系统：");
    m_label2.setText("构建命令：");
    m_lastPage.setText("上一步");
    m_nextPage.setText("下一步");

    auto layout = new QVBoxLayout;
    auto layout1 = new QHBoxLayout;
    layout1->addWidget(&m_label1);
    layout1->addWidget(&m_bsChooser);
    layout->addLayout(layout1);
    layout->addWidget(&m_label2);
    layout->addWidget(&m_buildCommend);

    auto *layout2 = new QHBoxLayout;
    layout2->addStretch();
    layout2->addWidget(&m_lastPage);
    layout2->addWidget(&m_nextPage);
    layout->addLayout(layout2);

    setLayout(layout);

    connect(&m_nextPage,&QPushButton::clicked,[=](){
        ((QStackedWidget*)parentWidget())->setCurrentIndex(((QStackedWidget*)parentWidget())->currentIndex()+1);
    });
    connect(&m_lastPage,&QPushButton::clicked,[=](){
        ((QStackedWidget*)parentWidget())->setCurrentIndex(((QStackedWidget*)parentWidget())->currentIndex()-1);
    });
}

void PageBSChoose::addBSOption(BuildSystem bs) {
    switch (bs) {
        case XMake:
            m_bsChooser.addItem("XMake",QVariant::fromValue(bs));
            break;
        case CMake:
            m_bsChooser.addItem("CMake",QVariant::fromValue(bs));
            break;
        case NONE:
            m_bsChooser.addItem("NONE",QVariant::fromValue(bs));
            break;
    }
    m_bsChooser.setCurrentIndex(m_bsChooser.count()-1);
}

void PageBSChoose::cleanBSOptions() {
    m_bsChooser.clear();
    addBSOption(NONE);
}

BuildSystem PageBSChoose::getBS() {
//    return XMake;
    return m_bsChooser.currentData().value<BuildSystem>();
}
