#include <QApplication>
#include <csignal>
#include "MainWindow.h"

#define MAX_SIZE (PATH_MAX+1)

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    char  current_absolute_path[MAX_SIZE];
    //获取当前程序绝对路径
    int  cnt = readlink( "/proc/self/exe" , current_absolute_path, MAX_SIZE);
    if  (cnt < 0 || cnt >= MAX_SIZE)
    {
        printf ( "***Error***\n" );
        exit (-1);
    }
    //获取当前目录绝对路径，即去掉程序名
    int  i;
    for  (i = cnt; i >=0; --i)
    {
        if  (current_absolute_path[i] ==  '/' )
        {
            current_absolute_path[i+1] =  '\0' ;
            break ;
        }
    }
    printf ( "current absolute path:%s\n" , current_absolute_path);
    BSParser::exe_path = current_absolute_path;
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
