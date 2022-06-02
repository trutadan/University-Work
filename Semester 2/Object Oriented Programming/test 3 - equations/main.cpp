#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    GUI w{controller};
    w.show();
    return a.exec();
}
