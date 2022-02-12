//
// Created by maicss on 2022/2/12.
//

#ifndef DEPENDMANAGER_PAGEWORKING_H
#define DEPENDMANAGER_PAGEWORKING_H
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QTextBrowser>
class PageWorking : public QWidget{

    Q_OBJECT
public:
    PageWorking();
    void setProjectName(const QString& name);
    void setProgress(int value);
    void printLog(const QString& log);
    void cleanLog();

private:
    QLabel m_label1;
    QLabel m_label2;
    QProgressBar m_progressBar;
    QPushButton m_saveLog;
    QTextBrowser m_logShower;
    QPushButton m_lastPage;
    QPushButton m_nextPage;
    QPushButton m_close;
};


#endif //DEPENDMANAGER_PAGEWORKING_H
