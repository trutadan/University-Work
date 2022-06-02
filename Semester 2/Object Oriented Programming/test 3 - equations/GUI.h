#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "Controller.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <qpushbutton.h>

class GUI : public QWidget
{
    Q_OBJECT

private:
    Controller controller;

public:
    GUI(Controller& controller, QWidget *parent = Q_NULLPTR);

    void initGUI();

    void addEquation();

    void populateList();

    void connectSignalsAndSlots();

    void computeSolution();

    ~GUI() override;

private:
    QVBoxLayout* mainLayout;
    QListWidget* equationsWidgetList;
    QLineEdit* aLine, * bLine, * cLine, *resultLine;
    QPushButton* computeButton, *addButton;
};
