#ifndef CTABLEMODEL1_H
#define CTABLEMODEL1_H

#include <QObject>
#include <QAbstractTableModel>
#include <array>
#include <QDoubleSpinBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "tabledata.h"

class CTableModel1 : public QAbstractTableModel
{
    Q_OBJECT
private:
    CTableData tableData;
    QString getStrValue(int row, int col) const;
protected:
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public:
    CTableModel1(void);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void clearString(int n);
    void insertStringUp(int n);
    void insertStringDown(int n);
    void deleteString(int n);
    bool save(QString name);
    bool load(QString name);
    QVariant getData(int col, int row) { return tableData.getData(col,row); }
    CTableData getTableData(void) { return tableData; }
signals:

public slots:
};

#endif // CTABLEMODEL1_H
