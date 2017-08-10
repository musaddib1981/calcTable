#ifndef CCOMBOBOXDELEGATE_H
#define CCOMBOBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>

class CComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CComboBoxDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;


signals:

public slots:
};

#endif // CCOMBOBOXDELEGATE_H
