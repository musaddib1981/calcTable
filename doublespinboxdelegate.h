#ifndef DOUBLESPINBOXDELEGATE_H
#define DOUBLESPINBOXDELEGATE_H

#include <QtGui>
#include <QWidget>
#include <QDoubleSpinBox>
#include <QStyledItemDelegate>

class CDoubleSpinBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    double maximum;
    double minimum;
    int prec;
    double step;

public:
    CDoubleSpinBoxDelegate(double min, double max, double precision, double sstep);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

signals:

public slots:

};

#endif // DOUBLESPINBOXDELEGATE_H
