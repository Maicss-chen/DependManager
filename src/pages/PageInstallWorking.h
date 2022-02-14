//
// Created by maicss on 2022/2/13.
//

#ifndef DEPENDMANAGER_PAGEINSTALLWORKING_H
#define DEPENDMANAGER_PAGEINSTALLWORKING_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QTextBrowser>
#include <QPushButton>

class PageInstallWorking : public QWidget{
    Q_OBJECT
public:
    PageInstallWorking();
    void printLog(const QString& log,bool autoReline = true);
    void setStepCount(int count);
    void setProgress(int step,int progress);
private:
    QLabel m_label1;
    QLabel m_label2;
    QProgressBar m_progressBar;
    QTextBrowser m_logShower;
    int *m_progress;
    int m_pcount;

};


#endif //DEPENDMANAGER_PAGEINSTALLWORKING_H
