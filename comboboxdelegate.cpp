#include "comboboxdelegate.h"

CComboBoxDelegate::CComboBoxDelegate(QObject *parent)
{

}

QWidget * CComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
     QComboBox *editor = new QComboBox(parent);
     editor->setFrame(false);
     editor->addItem("buy");
     editor->addItem("buy limit");
     editor->addItem("buy stop");
     editor->addItem("sell");
     editor->addItem("sell limit");
     editor->addItem("sell stop");

     return editor;
}
void CComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
     QString value = index.model()->data(index, Qt::EditRole).toString();
     QComboBox *comboBox = static_cast<QComboBox*>(editor);
     comboBox->setCurrentText(value);
}
void CComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
     QComboBox *comboBox = static_cast<QComboBox*>(editor);
     QString value = comboBox->currentText();

     model->setData(index, value, Qt::EditRole);
}
void CComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
     editor->setGeometry(option.rect);
}
