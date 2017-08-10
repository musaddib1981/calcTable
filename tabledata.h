#ifndef CTABLEDATA_H
#define CTABLEDATA_H

#include <QVector>
#include <array>
#include <QVariant>
#include <QObject>

class CTableData//: public QObject
{
private:
    static const int colCount = 5;
    std::array<QVector<QVariant> , colCount> data;
public:
    CTableData();
    QVariant getData(int col, int row) const;
    void setData(int col, int row, QVariant value);
    int rowCount(void) const { return data[0].size(); }
    int columnCount(void) const { return colCount; }
    void clearRow(int n);
    void insertRowUp(int n);
    void insertRowDown(int n);
    void deleteRow(int n);
    void append(std::array<QVariant, colCount> arr);
    void append(void);
    void clear(void);
};

#endif // CTABLEDATA_H
