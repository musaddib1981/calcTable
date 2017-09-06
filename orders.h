#ifndef CORDERS_H
#define CORDERS_H

#include <string>
#include <QDebug>
#include "tabledata.h"

enum
{
    e_null,
    e_buy,
    e_sell
};

class COrders
{
private:
    int ordersNum; //кол-во ордеров
    int orderType; //тип ордера

public:
    COrders(const CTableData &tableData, float cur_volume);

    int getNum(void) { return ordersNum; }
    int getType(void) { return orderType; }

    std::string getStringType(void);
    void print(void);
};

#endif // CORDERS_H
