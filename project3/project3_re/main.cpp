#include "mainwindow.h"
//#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

//    server server;

//    if(!server.listen(QHostAddress::Any, 8010)){
//        printf("error\n");
//        return 1;
//    }

    return a.exec();
}
