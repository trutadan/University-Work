#pragma once

#ifndef NOMINMAX
# define NOMINMAX
#endif

#include "ui_GUI.h"
#include "Controller/Controller.h"
#include "Functions/Validator.h"
#include "./ModelPictureDelegate.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QRadioButton>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSet>
#include <QShortcut>
#include <QTableView>
#include <QHeaderView>

class GUI : public QWidget
{
private:
    void initializeGUI();

    void popAdminWindow();

    void popUserWindow();

    void connectSignalsAndSlots();

public:
    explicit GUI(Controller& _controller);

    ~GUI() override;

private:
    Controller controller;
    QLabel* welcomeLabel;
    QPushButton* adminButton;
    QPushButton* userButton;
};

class AdminGUI : public QWidget
{
private:
    void initializeAdminGUI();

    int getSelectedEventIndex() const;

    void populateEventsListWidget();

    void checkAdminEmptyLineEdits();

    void addEvent();

    void removeEvent();

    void updateEvent();

    void displayChart();

    void undo();
    
    void redo();

    void connectSignalsAndSlots();

public:
    explicit AdminGUI(QWidget* parent, Controller& _controller);

    ~AdminGUI() override;

private:
    Controller controller;
    QMessageBox* errorBox;
    QLabel* entryMessageLabel;
    QListWidget* eventsListWidget;
    QLineEdit* titleLineEdit, * descriptionLineEdit, * dateLineEdit, * timeLineEdit, * numberOfPeopleLineEdit, * linkLineEdit;
    QPushButton* addEventButton, * removeEventButton, * updateEventButton, * chartButton;
    QWidget* chartWindow;
    QPushButton* undoActionButton, * redoActionButton;
    QShortcut* undoActionShortcut, * redoActionShortcut;
};

class EventsTableModel : public QAbstractTableModel {
private:
    Controller& controller;

public:
    explicit EventsTableModel(Controller& _controller);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;

    int columnCount(const QModelIndex& parent = QModelIndex()) const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void update();
};

class UserGUI : public QWidget
{
private:
    void initializeUserGUI();

    int getSelectedEventIndexFromList() const;

    void populateEventsListWidget();

    void checkUserEmptyLineEdits();

    void setUserListFile();

    void addEvent();

    void undo();

    void redo();

    void openFile();

    void createTable();

    void connectSignalsAndSlots();

public:
    UserGUI(QWidget* parent, Controller& _controller);

    ~UserGUI() override;

private:
    Controller controller;
    bool isRepositoryTypeSet;

    QMessageBox* errorBox;
    QLabel* entryMessageLabel, * repositoryTypeMessageLabel, * repositoryNameMessageLabel, * eventsListTitleLabel, * userEventsListTitleLabel, * tableViewMessageLabel;
    QRadioButton* csvDatabaseButton, * htmlDatabaseButton, * sqlDatabaseButton;
    QListWidget* eventsListWidget, * userEventsListWidget;
    QLineEdit* titleLineEdit, * descriptionLineEdit, * dateLineEdit, * timeLineEdit, * numberOfPeopleLineEdit, * linkLineEdit, * titleFilterLineEdit, * monthFilterLineEdit, * repositoryTypeLineEdit;
    QPushButton* addEventButton, * saveListToFileButton, * openUserListOfEventsFileButton, * openTableViewButton;
    QPushButton* undoActionButton, * redoActionButton;
    QShortcut* undoActionShortcut, * redoActionShortcut;

    EventsTableModel* eventsListTableModel;
};