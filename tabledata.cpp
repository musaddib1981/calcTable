#include "tabledata.h"

CTableData::CTableData()// : QObject()
{

}

QVariant CTableData::getData(int col, int row) const
{
    if (row < rowCount() && col < columnCount())
        return data[col][row];

    return QVariant();
}

void CTableData::setData(int col, int row, QVariant value)
{
    if (row < rowCount() && col < columnCount())
        data[col][row] = value;
}

void CTableData::clearRow(int n)
{
    data[0][n] = "";
    data[1][n] = 0.01;
    data[2][n] = 0;
    data[3][n] = 0;
    data[4][n] = "";
}

void CTableData::insertRowUp(int n)
{
    int i;
    for (i = 0; i < data.size(); i++)
       if (i == 1)
          data[i].insert(n, 0.01);
       else
          data[i].insert(n, "");
}

void CTableData::insertRowDown(int n)
{
    int i;
    for (i = 0; i < data.size(); i++)
        if (i == 1)
           data[i].insert(n + 1, 0.01);
        else
           data[i].insert(n + 1, "");
}

void CTableData::deleteRow(int n)
{
    int i;
    if (data[0].size() > 1)
    {
        for (i = 0; i < data.size(); i++)
        {
            data[i].erase(data[i].begin() + n);
        }
    }
}

void CTableData::clear(void)
{
    int i;
    for (i = 0; i < data.size(); i++)
      data[i].clear();
}

void CTableData::append(std::array<QVariant, colCount> arr)
{
    int i;
    for (i = 0; i < arr.size(); i++)
       data[i].push_back(arr[i]);

}

void CTableData::append(void)
{
    int i;
    for (i = 0; i < data.size(); i++)
       data[i].push_back("");
}
