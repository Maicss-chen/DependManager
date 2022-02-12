//
// Created by maicss on 2022/2/12.
//

#include "PageOpenProject.h"
#include <QLayout>
#include <QStackedWidget>
#include <QFileDialog>
PageOpenProject::PageOpenProject() {
    auto *layout = new QVBoxLayout;
    layout->addStretch();

    auto *layout1 = new QHBoxLayout;
    m_label1.setText("项目路径：");
    m_btnOpenDir.setText("...");
    layout1->addWidget(&m_label1);
    layout1->addWidget(&m_pathEdit);
    layout1->addWidget(&m_btnOpenDir);

    layout->addLayout(layout1);

    layout->addStretch();

    auto *layout2 = new QHBoxLayout;
    layout2->addStretch();
    layout2->addWidget(&m_next);
    m_next.setText("下一步");
    m_next.setEnabled(false);
    layout->addLayout(layout2);
    setLayout(layout);

    connect(&m_next,&QPushButton::clicked,[=](){
        ((QStackedWidget*)parentWidget())->setCurrentIndex(((QStackedWidget*)parentWidget())->currentIndex()+1);
    });
    connect(&m_btnOpenDir,&QPushButton::clicked,[=](){
        QFileDialog dlg;
        dlg.setFileMode(QFileDialog::FileMode::DirectoryOnly);
        dlg.exec();
        m_pathEdit.setText(dlg.directoryUrl().path());
    });
    connect(&m_pathEdit,&QLineEdit::textChanged,[=](){
        QFileInfo fileInfo(m_pathEdit.text());
        m_next.setEnabled(fileInfo.exists());
    });

    m_pathEdit.setText("/home/maicss/项目/building-system");

}

QString PageOpenProject::getPath() {
    return m_pathEdit.text();
}
