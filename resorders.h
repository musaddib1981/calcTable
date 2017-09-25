#ifndef CRESORDERS_H
#define CRESORDERS_H

#include <QString>

class CResOrders
{
private:
    QString orderType;
    int orderNum;
    float orderPrice;
public:
    CResOrders(QString type, int num, float price);
    CResOrders(void);
    QString getType(void) { return orderType; }
    int getNum(void) { return orderNum; }
    float getPrice(void) { return orderPrice; }

};

#endif // CRESORDERS_H
