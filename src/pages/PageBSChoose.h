//
// Created by maicss on 2022/2/12.
//

#ifndef DEPENDMANAGER_PAGEBSCHOOSE_H
#define DEPENDMANAGER_PAGEBSCHOOSE_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
enum BuildSystem{
    CMake,
    XMake,
    NONE
};

Q_DECLARE_METATYPE(BuildSystem)

class PageBSChoose : public QWidget{
    Q_OBJECT
public:
    PageBSChoose();
    void addBSOption(BuildSystem bs);
    BuildSystem getBS();
    void cleanBSOptions();
private:
    QLabel m_label1;
    QComboBox m_bsChooser;
    QLabel m_label2;
    QTextEdit m_buildCommend;
    QPushButton m_lastPage;
    QPushButton m_nextPage;
};


#endif //DEPENDMANAGER_PAGEBSCHOOSE_H
