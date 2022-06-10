#include "ModelPictureDelegate.h"
#include <QEventLoop>
#include <QPushButton>
#include <QWidget>
#include <Windows.h>

ModelDelegate::ModelDelegate(QWidget* parent) : QStyledItemDelegate{ parent }
{
}

void ModelDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() != 5) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    // TO SOLVE: BUTTON IS "UNACTIONABLE"
    std::string eventLink = index.model()->data(index, Qt::EditRole).toString().toStdString();

    QPushButton* openButton = new QPushButton("OPEN");
    QObject::connect(openButton, &QPushButton::clicked, this, [eventLink]() { ShellExecuteA(NULL, NULL, "chrome.exe", eventLink.c_str(), NULL, SW_SHOWMAXIMIZED); });

    openButton->setGeometry(option.rect);
    painter->save();
    painter->translate(option.rect.topLeft());
    openButton->render(painter);

    painter->restore();
}

QSize ModelDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (index.column() == 1)
        return { 32, 64 };

    return QStyledItemDelegate::sizeHint(option, index);
}
