#ifndef CLEVELS_H
#define CLEVELS_H

#include <QVector>
#include "tabledata.h"
#include <QString>
#include <QDebug>
#include "tablemodel2.h"
#include "orders.h"

struct DataLevels
{
    float price;
    int type;
    int num;
};

class CLevels
{

private:
    QVector<DataLevels> data;
    bool searchDuplicate(float lev);
    int getDeltaOrders(int index1, int index2);
public:
    CLevels(void);
    void create(const CTableData &table);
    int size(void) { return data.size(); }
    DataLevels operator [](int n);
    void setType(int i, int type) { data[i].type = type; }
    void setNum(int i, int num) { data[i].num = num; }
    void sort(int type, int num, CTableModel2 *tableModel2);
};

#endif // CLEVELS_H
