#pragma once
#include <QStyledItemDelegate>
#include <QPainter>

class ModelDelegate : public QStyledItemDelegate
{
public:
    ModelDelegate(QWidget* parent = 0);

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};
