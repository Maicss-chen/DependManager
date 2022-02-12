//
// Created by maicss on 2022/2/12.
//

#include "PageDependChoose.h"
#include <QLayout>
PageDependChoose::PageDependChoose() {
    m_label1.setText("以下是该项目所需的依赖列表，请选择需要安装的依赖");
    m_chooseAll.setText("全选");
    QSizePolicy policy;
    policy.setHorizontalStretch(0);
    m_chooseAll.setSizePolicy(policy);
    m_installDepend.setText("安装");

    listModel.setColumnCount(3);
    listModel.setRowCount(0);
    listModel.setHeaderData(0,Qt::Horizontal,"依赖名称");
    listModel.setHeaderData(1,Qt::Horizontal,"版本");
    listModel.setHeaderData(2,Qt::Horizontal,"是否可选");

//    m_list
    m_list.setEditTriggers( QAbstractItemView::NoEditTriggers);
    m_list.setSelectionBehavior(QAbstractItemView::SelectRows);
    m_list.setModel(&listModel);

    m_list.setColumnWidth(0,340);

    auto *layout = new QVBoxLayout;
    auto *layout1 = new QHBoxLayout;
    layout1->addWidget(&m_label1);
    layout1->addWidget(&m_chooseAll);
    layout->addLayout(layout1);

    layout->addWidget(&m_list);

    auto *layout2 = new QHBoxLayout;
    layout2->addStretch();
    layout2->addWidget(&m_installDepend);
    layout->addLayout(layout2);

    setLayout(layout);

    connect(&m_chooseAll,&QPushButton::clicked,[=](){
        for (int i=0;i<listModel.rowCount();i++){
            listModel.item(i)->setCheckState(Qt::Checked);
        }
    });

}

void PageDependChoose::setDependList(DependList dependList) {
    listModel.setRowCount(dependList.size());
    int i=0;
    for (auto item:dependList) {
        auto *item1 = new QStandardItem;
        auto *item2 = new QStandardItem;
        auto *item3 = new QStandardItem;

        item1->setText(QString::fromStdString(item.name));
        if (item.installed){
            item1->setCheckable(false);
            item1->setCheckState(Qt::Checked);
        } else{
            item1->setCheckable(true);
        }
        item2->setText("-");
        if(item.optional){
            item3->setText("可选");
            item1->setCheckState(Qt::Unchecked);
        }
        else{
            item3->setText("必选");
            item1->setCheckState(Qt::Checked);
        }
        listModel.setItem(i,0,item1);
        listModel.setItem(i,1,item2);
        listModel.setItem(i,2,item3);
        i++;
    }

}
