#ifndef CTABLEMODEL2_H
#define CTABLEMODEL2_H

#include <QAbstractTableModel>
#include "tabledata.h"

class CTableModel2 : public QAbstractTableModel
{
private:
    CTableData tableData;
    QString getStrValue(int row, int col) const;
protected:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public:
    CTableModel2(void);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    void setData(int col, int row, QVariant str);
    void clear(void);
    void appendRow(void);
};

#endif // CTABLEMODEL2_H
