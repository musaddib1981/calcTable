#include "orders.h"

COrders::COrders(const CTableData &tableData, float cur_volume)
{
    int i;

    float buy_volume = 0;
    float sell_volume = 0;
    int count_buy = 0;
    int count_sell = 0;

    for (i = 0; i < tableData.rowCount(); i++)
    {
        if (tableData.getData(0,i) == "buy")
            buy_volume += tableData.getData(1,i).toFloat();

        if (tableData.getData(0,i) == "sell")
            sell_volume += tableData.getData(1,i).toFloat();

    }

    count_buy = buy_volume / cur_volume + 0.5;
    count_sell = sell_volume / cur_volume + 0.5;

    if (count_buy > count_sell)
    {
        orderType = e_buy;
        ordersNum = count_buy - count_sell;
    }
    else
    if (count_sell > count_buy)
    {
        orderType = e_sell;
        ordersNum = count_sell - count_buy;
    }
    else
    {
        orderType = e_null;
        ordersNum = 0;
    }
}

std::string COrders::getStringType(void)
{
    if (orderType == e_buy)
        return "buy";

    if (orderType == e_sell)
        return "sell";

    return "e_null";
}

void COrders::print(void)
{
    int i;
    for (i = 0; i < ordersNum; i++)
        qDebug()<<getStringType().c_str();
}
