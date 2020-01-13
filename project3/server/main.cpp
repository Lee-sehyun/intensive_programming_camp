#include "server.h"
#include "echoserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server w;
    w.show();

    EchoServer server;

    server.listen(QHostAddress::Any, 8010);

    return a.exec();
}
