#pragma once
#include "Observer.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include <QTableView>
#include <QVBoxLayout>
#include "Service.h"

class StatisticsWindow : public  QWidget, public  Observer {
private:
    Service& service;
    int xAxis = 0;
    int yAxis = 0;

public:
    StatisticsWindow(Service& _service, QWidget* parent = Q_NULLPTR);

    void update() override;
    
    QSize sizeHint() const Q_DECL_OVERRIDE;
    
    void drawCircle(Member& member);
    
    void resizeEvent(QResizeEvent* event);
    
    void paintEvent(QPaintEvent* event);
};
    