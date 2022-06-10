#include <QPainter>
#include "StatisticsWindow.h"
#include <QMessageBox>

StatisticsWindow::StatisticsWindow(Service&_service, QWidget* parent) : service(_service), QWidget{ parent } {
    this->service.addObserver(this);
    this->setWindowTitle(QString::fromStdString("Members Statistics"));
}

void StatisticsWindow::update() {
    this->repaint();
}

void StatisticsWindow::paintEvent(QPaintEvent* event) {
    this->xAxis = 0;
    this->yAxis = 0;
    for (auto& p : this->service.getMembers()) {
        drawCircle(p);
    }
}

void StatisticsWindow::drawCircle(Member& member) {
    QPainter painter{ this };

    if (member.getNumberOfRevisedFiles() >= member.getTotalNumberOfFilesToRevise()) {
        QPen pen{ Qt::blue, 1, Qt::SolidLine, Qt::RoundCap };
        painter.setPen(pen);
        QBrush brush{ Qt::blue, Qt::FDiagPattern };
        painter.setBrush(brush);
    }

    else
    {
        QPen pen{ Qt::black, 1, Qt::SolidLine, Qt::RoundCap };
        painter.setPen(pen);
        QBrush brush{ Qt::black, Qt::FDiagPattern };
        painter.setBrush(brush);
    }

    int size = member.getNumberOfRevisedFiles();

    this->xAxis += size * 5;
    this->yAxis += size * 5;
    
    QString name = QString::fromStdString(member.getName());
    painter.drawEllipse(this->xAxis, this->yAxis, size * 10, size * 10);
    painter.drawText(this->xAxis + size * 15, this->yAxis + size * 5, name);
    
    this->yAxis += size * 10;
    this->xAxis = 0;
}

QSize StatisticsWindow::sizeHint() const {
    return QSize{ 1280, 640 };
}

void StatisticsWindow::resizeEvent(QResizeEvent* event) {
    this->xAxis = 0;
    this->yAxis = 0;
}
