#include <QApplication>
#include "MainWindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    BSParser::exe_path = argv[0];
    MainWindow mainWindow;
    mainWindow.show();
    return QApplication::exec();
}
