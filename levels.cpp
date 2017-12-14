#include "levels.h"

CLevels::CLevels(void)
{

}

void CLevels::addLevel(int type, int num, float price)
{
    DataLevels item;
    item.type = type;
    item.num = num;
    item.price = price;
    data.push_back(item);
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

int invertOrderType(int type)
{
    if (type == e_buy)
        return e_sell;
    else
    if (type == e_sell)
        return e_buy;

    return type;
}

//расчет лимитов
void CLevels::calcLimits(int op)
{
    int i;
    int op2 = invertOrderType(op);
    //цикл по buy
    i = data.size() - 1;
    do
    {
        if ((i - 1) < 0)
            break;

        if (data[i - 1].type != op)
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

        if (data[i + 1].type != op2)
            break;

        if (data[i].num <= 0 || data[i + 1].num <= 0)
            break;

        data[i].num = data[i].num - data[i + 1].num;
        i++;
    }while(1);
}

QVector<CResOrders> CLevels::getResult(int type, int num)
{
    QVector <CResOrders> vec;

    if (type == e_sell || type == e_null)
       qStableSort(data.begin(), data.end(), lessThanSell);
    else
       qStableSort(data.begin(), data.end(), lessThanBuy);

    int i, n, delta, p;
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
       p = 0;

       do
       {
           //Исправлена такая ситуация:
           //sell
           //sell
           //1.1853 sell 6
           //1.1839 sell 4
           //1.0779 buy 1
           //1.0528 buy 3

           if (p == 0 && data[i].type != type)
               delta = num;
           else
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
               {
                  qDebug()<<"buy"<<data[i].price;
                  vec.push_back(CResOrders("buy", 1, data[i].price));
               }
               else
               if (type == e_sell)
               {
                  qDebug()<<"sell"<<data[i].price;
                  vec.push_back(CResOrders("sell", 1, data[i].price));
               }

               delta--;
               n--;
               p++;
           }while (delta > 0 && n > 0);
           i++;
        }while(n > 0);

        //расчет количества лимитных ордеров сверху
        //если первый уровень не превышает кол-во текущих ордеров то все обнуляем
        //пример текущее кол-во ордеров - 2
        //       sell 1.2029 2 -> 0
        //       sell 1.1829 1 -> 0
        //       buy  1.0779 2
        //       buy  1.0528 4
        if (data[0].num <= num)
        {
            for (i = 0; i < data.size()- 1; i++)
               if (data[i].type == type)
                   data[i].num = 0;
               else
                   break;
        }
        else
        {
         for (i = 0; i < data.size() - 1; i++)
           if (data[i].type == type && data[i + 1].type == data[i].type && data[i].num >= num)
              data[i].num = data[i].num - num;
           else
           if (data[i].type == type && data[i + 1].type == data[i].type && data[i].num < num)
              data[i].num = data[i].num - data[i + 1].num;
           else
           if (data[i].type == type && data[i + 1].type != data[i].type)
              data[i].num = data[i].num - num;
           else
              break;
        }
        //расчет количества лимитных ордеров снизу
        /*for (i = 0; i < data.size(); i++)
           if (data[i].type != type && data[i-1].type == data[i].type)
              data[i].num = data[i].num - data[i - 1].num;*/

        for (i = data.size() - 1; i >= 0; i--)
           if (data[i].type != type && data[i - 1].type == data[i].type)
               data[i].num = data[i].num - data[i - 1].num;
           else
              break;

    }

    //calcLimits(type);

    for (i = 0; i < data.size(); i++)
    {
       if (data[i].type == e_buy && data[i].num > 0)
       {
          qDebug()<<data[i].price<<"buy limit"<<data[i].num;
          vec.push_back(CResOrders("buy limit", data[i].num, data[i].price));
       }
       else
       if (data[i].type == e_sell && data[i].num > 0)
       {
          qDebug()<<data[i].price<<"sell limit"<<data[i].num;
          vec.push_back(CResOrders("sell limit", data[i].num, data[i].price));
       }
    }

    return vec;

}

