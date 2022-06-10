#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI.h"
#include "Service.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QLineEdit>
#include <qpushbutton.h>
#include <qmessagebox.h>

class GUI : public QWidget, public Observer
{
    Q_OBJECT

private:
    Service& service;
    Member member;

public:
    GUI(Service& service, Member member, QWidget *parent = Q_NULLPTR);

    void initGUI();

    void connectSignalsAndSlots();

    void populateAllFilesList();

    void populateLabels();

    void addSourceFile();

    int getSelectedIndex();

    void checkIfReviseAvailable();

    void revise();

    void update() override;

private:
    QVBoxLayout* mainLayout;
    QListWidget* allFilesListWidget;
    QLineEdit* unrevisedLabel;
    QLineEdit* revisedLabel;
    QLineEdit* addLineEdit;
    QPushButton* addButton;
    QPushButton* reviseButton;
};
