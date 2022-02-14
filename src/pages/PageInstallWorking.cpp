//
// Created by maicss on 2022/2/13.
//

#include "PageInstallWorking.h"
#include <QLayout>
PageInstallWorking::PageInstallWorking() {
    m_label1.setText("正在安装依赖");
    m_label2.setText("正在尝试从远程仓库中安装您选择的依赖");
    m_progressBar.setMaximum(100);

    auto layout = new QVBoxLayout;
    layout->addWidget(&m_label1);
    layout->addWidget(&m_label2);
    layout->addWidget(&m_progressBar);
    layout->addWidget(&m_logShower);

    setLayout(layout);
}

void PageInstallWorking::printLog(const QString& log,bool autoReline) {
    if(autoReline)
        m_logShower.append(log);
    else
        m_logShower.setText(m_logShower.toPlainText()+log);
}

void PageInstallWorking::setStepCount(int count) {
    m_pcount = count;
    m_progress = new int[count]{0};
}

void PageInstallWorking::setProgress(int step,int progress) {
    if(step >= m_pcount) return;
    m_progress[step] = progress;
    int sum=0;
    for (int i = 0; i < m_pcount; ++i) {
        sum+=m_progress[i];
    }
    m_progressBar.setValue(sum/m_pcount);
}
