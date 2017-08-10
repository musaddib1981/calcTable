#include "tablemodel2.h"

CTableModel2::CTableModel2(void)
{

}

int CTableModel2::rowCount(const QModelIndex &parent) const
{
    return tableData.rowCount();
}

int CTableModel2::columnCount(const QModelIndex &parent) const
{
    return tableData.columnCount();
}

QString CTableModel2::getStrValue(int row, int col) const
{
    QVariant value = tableData.getData(col,row);
    if (col == 0 || col == 4)
        return value.toString();
    else
    if (col == 1)
    {
        if  (value.toFloat() == 0)
            return "";
        return QString::number(value.toFloat(), 'f', 2);
    }
    else
    {
        if  (value.toFloat() == 0)
            return "";
        return QString::number(value.toFloat(), 'f', 4);
    }


    return QString();
}

QVariant CTableModel2::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (getStrValue(index.row(), 0) == "")
            return "";
        else
            return getStrValue(index.row(), index.column());
    }
    else
    //получение данных для делегатов
    if (role == Qt::EditRole)
    {
        return tableData.getData(index.column(), index.row());
    }
    return QVariant();
}

bool CTableModel2::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        tableData.setData(index.column(), index.row(), value);
        return true;
    }

    return false;
}

Qt::ItemFlags CTableModel2::flags(const QModelIndex &index) const
{
    return (Qt::ItemIsEnabled);
}

QVariant CTableModel2::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            if (section == 0)
                return "Тип";
            if (section == 1)
                return "Объем";
            if (section == 2)
                return "Цена открытия";
            if (section == 3)
                return "Тп";
            if (section == 4)
                return "Комментарий";
        }
    }
    else
    if (orientation == Qt::Vertical)
    {
       return QString::number(section) + QString(".");
    }
    return QVariant();
}

void CTableModel2::clear(void)
{
    beginResetModel();

    tableData.clear();

    endResetModel();
}

void CTableModel2::appendRow(void)
{
    beginResetModel();

    tableData.append();

    endResetModel();
}

void CTableModel2::setData(int col, int row, QVariant str)
{
    beginResetModel();

    tableData.setData(col,row, str);

    endResetModel();
}
