#include "levels.h"

CLevels::CLevels(void)
{

}

bool CLevels::searchDuplicate(float lev)
{
    QString level = QString::number(lev,'f',4);
    int i;
    for (i = 0; i < data.size(); i++)
       if (QString::number(data[i].price,'f',4) == level)
           return true;
    return false;
}

void CLevels::create(const CTableData &table)
{
    int i;
    QString orderType;
    float price;
    float tp;
    DataLevels item;

    for (i = 0; i < table.rowCount(); i++)
    {
        orderType = table.getData(0,i).toString();
        price = table.getData(2,i).toFloat();
        tp = table.getData(3,i).toFloat();
        if ((orderType == "buy" || orderType == "sell") && tp > 0.0001 && searchDuplicate(tp) == false)
        {
            item.price = tp;
            item.type = 0;
            item.num = 0;
            data.push_back(item);
        }
        else
        if ((orderType == "buy stop" || orderType == "sell stop" || orderType == "buy limit" || orderType == "sell limit") && searchDuplicate(price) == false)
        {
            item.price = price;
            item.type = 0;
            item.num = 0;
            data.push_back(item);

        }
    }
}

DataLevels CLevels::operator [](int n)
{
    return data[n];
}


bool inline lessThanSell(const DataLevels &data1, const DataLevels &data2)
{
    return (data1.price > data2.price);
}

bool inline lessThanBuy(const DataLevels &data1, const DataLevels &data2)
{
    return (data1.price < data2.price);
}


int CLevels::getDeltaOrders(int index1, int index2)
{
    int sum = 0;
    if (data[index1].type == data[index2].type)
    {
         sum = data[index1].num - data[index2].num;
         if (sum < 0)
             sum = -sum;
         return sum;
    }

    sum = data[index1].num + data[index2].num;

    return sum;

}

void CLevels::sort(int type, int num, CTableModel2 *tableModel2)
{
    if (type == e_sell || type == e_null)
       qStableSort(data.begin(), data.end(), lessThanSell);
    else
       qStableSort(data.begin(), data.end(), lessThanBuy);

    int i, n, delta, j, k = 0;
    for (i = 0; i < data.size(); i++)
    {
       if (data[i].type == e_buy)
          qDebug()<<data[i].price<<"buy"<<data[i].num;
       else
       if (data[i].type == e_sell)
          qDebug()<<data[i].price<<"sell"<<data[i].num;
       else
          qDebug()<<data[i].price;
    }

    //Определение тейкпрофитов текущих ордеров
    if (num > 0)
    {
       n = num;
       i = 0;
       while (i < data.size() && data[i].type == type && data[i].num >= n)
          i++;
       do
       {
           if (i == 0)
               delta = num - data[i].num;
           else
           if (data[i - 1].num >= num && data[i - 1].type == type) // важные изменения
               delta = num - data[i].num;                          // 4.09.2017
           else
               delta = getDeltaOrders(i - 1, i);
           do
           {
               if (type == e_buy)
                  qDebug()<<"buy"<<data[i].price;
               else
               if (type == e_sell)
                  qDebug()<<"sell"<<data[i].price;

               tableModel2->appendRow();

               if (type == e_buy)
                  tableModel2->setData(0, k, "buy");
               else
               if (type == e_sell)
                  tableModel2->setData(0, k, "sell");

               tableModel2->setData(3, k, data[i].price);
               delta--;
               n--;
               k++;
           }while (delta > 0 && n > 0);
           i++;
        }while(n > 0);


        for (i = 0; i < data.size(); i++)
           if (data[i].type == type)
              data[i].num = data[i].num - num;
    }

    if (type == e_sell || type == e_null)
    {
        //цикл по buy
        i = data.size() - 1;
        do
        {
            if ((i - 1) < 0)
                break;

            if (data[i - 1].type != e_buy)
                break;

            if (data[i].num <= 0 || data[i - 1].num <= 0)
                break;

            data[i].num = data[i].num - data[i - 1].num;
            i--;

        }while(1);

        //цикл по sell
        i = 0;
        do
        {
            if ((i + 1) > data.size() - 1)
                break;

            if (data[i + 1].type != e_sell)
                break;

            if (data[i].num <= 0 || data[i + 1].num <= 0)
                break;

            data[i].num = data[i].num - data[i + 1].num;
            i++;
        }while(1);
    }

    if (type == e_buy)
    {
        //цикл по buy
        i = data.size() - 1;
        do
        {
            if ((i - 1) < 0)
                break;

            if (data[i - 1].type != e_sell)
                break;

            if (data[i].num <= 0 || data[i - 1].num <= 0)
                break;

            data[i].num = data[i].num - data[i - 1].num;
            i--;

        }while(1);

        //цикл по sell
        i = 0;
        do
        {
            if ((i + 1) > data.size() - 1)
                break;

            if (data[i + 1].type != e_buy)
                break;

            if (data[i].num <= 0 || data[i + 1].num <= 0)
                break;

            data[i].num = data[i].num - data[i + 1].num;
            i++;
        }while(1);
    }

    for (i = 0; i < data.size(); i++)
    {
       if (data[i].type == e_buy && data[i].num > 0)
       {
          qDebug()<<data[i].price<<"buy limit"<<data[i].num;
          for (j = 0; j < data[i].num; j++)
          {
              tableModel2->appendRow();
              tableModel2->setData(0, k, "buy limit");
              tableModel2->setData(2, k, data[i].price);
              k++;
          }
       }
       else
       if (data[i].type == e_sell && data[i].num > 0)
       {
          qDebug()<<data[i].price<<"sell limit"<<data[i].num;
          for (j = 0; j < data[i].num; j++)
          {
              tableModel2->appendRow();
              tableModel2->setData(0, k, "sell limit");
              tableModel2->setData(2, k, data[i].price);
              k++;
          }

       }
    }

}

