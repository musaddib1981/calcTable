#ifndef CLEVELS_H
#define CLEVELS_H

#include <QVector>
#include <QString>
#include <QDebug>
#include "orders.h"
#include "resorders.h"

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
    int getDeltaOrders(int index1, int index2);
    void calcLimits(int op);
public:
    CLevels(void);
    int size(void) { return data.size(); }
    DataLevels operator [](int n);
    void setType(int i, int type) { data[i].type = type; }
    void setNum(int i, int num) { data[i].num = num; }
    QVector<CResOrders> getResult(int type, int num);

    void addLevel(int type, int num, float price);
    bool isExistsUpperLimits(void);
};

#endif // CLEVELS_H
