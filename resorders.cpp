#include "resorders.h"

CResOrders::CResOrders(QString type, int num, float price): orderType(type), orderNum(num), orderPrice(price)
{

}

CResOrders::CResOrders(void) : orderType(""), orderNum(0), orderPrice(0)
{

}
