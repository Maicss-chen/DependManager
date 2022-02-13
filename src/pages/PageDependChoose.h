//
// Created by maicss on 2022/2/12.
//

#ifndef DEPENDMANAGER_PAGEDEPENDCHOOSE_H
#define DEPENDMANAGER_PAGEDEPENDCHOOSE_H

#include <QWidget>
#include <QLabel>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>
#include <QTableView>
#include "../build-system/XMakeBSParser.h"
#include "PageBSChoose.h"


class PageDependChoose : public QWidget{
Q_OBJECT
public:
    PageDependChoose();
    void setDependList(DependList dependList);
    QStandardItemModel listModel;
private:
    QLabel m_label1;
    QPushButton m_chooseAll;
    QTableView m_list;
    QPushButton m_installDepend;
};


#endif //DEPENDMANAGER_PAGEDEPENDCHOOSE_H
