#include "tablemodel1.h"

CTableModel1::CTableModel1(void)
{
    tableData.insertRowUp(0);
}

int CTableModel1::rowCount(const QModelIndex &) const
{
    return tableData.rowCount();
}

int CTableModel1::columnCount(const QModelIndex &) const
{
    return tableData.columnCount();
}

QString CTableModel1::getStrValue(int row, int col) const
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

QVariant CTableModel1::data(const QModelIndex &index, int role) const
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

bool CTableModel1::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        tableData.setData(index.column(), index.row(), value);
        return true;
    }

    return false;
}

Qt::ItemFlags CTableModel1::flags(const QModelIndex &index) const
{
    return (Qt::ItemIsEditable | Qt::ItemIsEnabled);
}

QVariant CTableModel1::headerData(int section, Qt::Orientation orientation, int role) const
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

void CTableModel1::clearString(int n)
{
    beginResetModel();

    tableData.clearRow(n);

    endResetModel();
}

void CTableModel1::insertStringUp(int n)
{
    beginResetModel();

    tableData.insertRowUp(n);

    endResetModel();
}

void CTableModel1::insertStringDown(int n)
{
    beginResetModel();

    tableData.insertRowDown(n);

    endResetModel();
}

void CTableModel1::deleteString(int n)
{
    beginResetModel();

    tableData.deleteRow(n);

    endResetModel();
}

void CTableModel1::save(QString name)
{
    int i;
    QFile data(name);
    if (data.open(QFile::WriteOnly | QFile::Truncate) == true)
    {
        QTextStream stream(&data);
        for (i = 0; i < tableData.rowCount(); i++)
        {
             stream<<tableData.getData(0, i).toString()<<";";
             //stream.setRealNumberPrecision(2);
             stream<<QString::number(tableData.getData(1, i).toFloat(),'f',2)<<";";
             //stream.setRealNumberPrecision(4);
             stream<<QString::number(tableData.getData(2, i).toFloat(),'f',4)<<";"<<QString::number(tableData.getData(3, i).toFloat(),'f',4)<<";"<<tableData.getData(4, i).toString()<<";\n";

        }
        stream.flush();
        data.close();
    }
}

void CTableModel1::load(QString name)
{
    int i;
    QString str;
    QStringList list;
    std::array<QVariant, 5> arr;

    QFile data(name);
    if (data.open(QFile::ReadOnly) == true)
    {

        beginResetModel();

        tableData.clear();

        QTextStream stream(&data);
        do
        {
             str = stream.readLine();
             list = str.split(";");

             arr[0] = list[0];
             arr[1] = list[1].toFloat();
             arr[2] = list[2].toFloat();
             arr[3] = list[3].toFloat();
             arr[4] = list[4];
             tableData.append(arr);

        }while(stream.atEnd() == false);

        endResetModel();
        data.close();
    }
}

