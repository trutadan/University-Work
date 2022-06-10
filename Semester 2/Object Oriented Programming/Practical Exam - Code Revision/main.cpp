#include "GUI.h"
#include <QtWidgets/QApplication>
#include "StatisticsWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MemberRepository memberRepo{};
    SourceFileRepository sourceFileRepo{};
    Service service{memberRepo, sourceFileRepo};

    for (auto& member : service.getMembers()) {
        GUI* memberWindow = new GUI(service, member);
        memberWindow->show();
    }

    StatisticsWindow* statsWindow = new StatisticsWindow(service);
    statsWindow->show();
    
    return a.exec();
}
