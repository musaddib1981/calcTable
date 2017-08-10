#include "doublespinboxdelegate.h"

CDoubleSpinBoxDelegate::CDoubleSpinBoxDelegate(double min, double max, double precision, double sstep) :
    //QStyledItemDelegate(parent)
    minimum(min), maximum(max), prec(precision), step(sstep)
{

}

QWidget * CDoubleSpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
     QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
     editor->setFrame(false);
     editor->setMinimum(minimum);
     editor->setMaximum(maximum);
     editor->setDecimals(prec);
     editor->setSingleStep(step);
     return editor;
}
void CDoubleSpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     double value = index.model()->data(index, Qt::EditRole).toDouble();

     QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
     doubleSpinBox->setValue(value);
}
void CDoubleSpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
     QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
     doubleSpinBox->interpretText();
     double value = doubleSpinBox->value();

     model->setData(index, value, Qt::EditRole);
}
void CDoubleSpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
     editor->setGeometry(option.rect);
}
