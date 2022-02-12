//
// Created by maicss on 2022/2/12.
//

#ifndef DEPENDMANAGER_PAGEOPENPROJECT_H
#define DEPENDMANAGER_PAGEOPENPROJECT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
class PageOpenProject : public QWidget{
    Q_OBJECT
public:
    PageOpenProject();

    QString getPath();
private:
    QLabel m_label1;
    QLineEdit m_pathEdit;
    QPushButton m_btnOpenDir;
    QPushButton m_next;
};


#endif //DEPENDMANAGER_PAGEOPENPROJECT_H
