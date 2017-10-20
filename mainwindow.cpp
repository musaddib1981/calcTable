#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget();
    mainLayout = new QGridLayout();
    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);

    setFixedSize(1024,768);

    label1 = new QLabel("Исходная таблица");
    tableView1 = new QTableView();
    tableModel1 = new CTableModel1();
    label2 = new QLabel("Расчетная таблица");
    tableView1->setModel(tableModel1);
    tableView1->setFixedWidth(603);

    tableView2 = new QTableView();
    tableModel2 = new CTableModel2();
    tableView2->setModel(tableModel2);
    tableView2->setFixedWidth(603);

    buttonAddUp = new QPushButton("Добавить выше");
    buttonAddDown = new QPushButton("Добавить ниже");
    buttonDelete = new QPushButton("Удалить");
    buttonSave = new QPushButton("Сохранить");
    buttonLoad = new QPushButton("Загрузить");
    buttonClear = new QPushButton("Очистить строку");
    buttonCalc = new QPushButton("Рассчитать");

    buttonAddUp->setFixedSize(150,30);
    buttonAddDown->setFixedSize(150,30);
    buttonDelete->setFixedSize(150,30);
    buttonSave->setFixedSize(150,30);
    buttonLoad->setFixedSize(150,30);
    buttonClear->setFixedSize(150,30);
    buttonCalc->setFixedSize(150,30);

    connect(buttonAddUp, SIGNAL(clicked(bool)), this, SLOT(slotButtonAddUp()));
    connect(buttonAddDown, SIGNAL(clicked(bool)), this, SLOT(slotButtonAddDown()));
    connect(buttonDelete, SIGNAL(clicked(bool)), this, SLOT(slotButtonDelete()));
    connect(buttonSave, SIGNAL(clicked(bool)), this, SLOT(slotButtonSave()));
    connect(buttonLoad, SIGNAL(clicked(bool)), this, SLOT(slotButtonLoad()));
    connect(buttonClear, SIGNAL(clicked(bool)), this, SLOT(slotButtonClear()));
    connect(buttonCalc, SIGNAL(clicked(bool)), this, SLOT(slotButtonCalc()));

    mainLayout->addWidget(label1,0,0);
    mainLayout->addWidget(tableView1,1,0,1,5);
    mainLayout->addWidget(label2,2,0);
    mainLayout->addWidget(tableView2,3,0,1,5);
    mainLayout->addWidget(buttonAddUp,4,0);
    mainLayout->addWidget(buttonAddDown,4,1);
    mainLayout->addWidget(buttonDelete,4,2);
    mainLayout->addWidget(buttonSave,4,3);
    mainLayout->addWidget(buttonLoad,5,0);
    mainLayout->addWidget(buttonClear,5,1);
    mainLayout->addWidget(buttonCalc,5,2);

    CDoubleSpinBoxDelegate *doubleSpinBox1 = new CDoubleSpinBoxDelegate(0, 1000, 2, 0.01);
    CDoubleSpinBoxDelegate *doubleSpinBox2 = new CDoubleSpinBoxDelegate(0, 10000, 4, 0.0001);
    CComboBoxDelegate *comboBox1 = new CComboBoxDelegate();

    tableView1->setColumnWidth(0,120);
    tableView1->setColumnWidth(1,120);
    tableView1->setColumnWidth(2,120);
    tableView1->setColumnWidth(3,120);
    tableView1->setColumnWidth(4,120);

    tableView1->setItemDelegateForColumn(0, comboBox1);
    tableView1->setItemDelegateForColumn(1, doubleSpinBox1);
    tableView1->setItemDelegateForColumn(2, doubleSpinBox2);
    tableView1->setItemDelegateForColumn(3, doubleSpinBox2);

    tableView1->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView1->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView1->verticalHeader()->setDefaultSectionSize(20);

    tableView2->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView2->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView2->verticalHeader()->setDefaultSectionSize(20);

    //tableModel2->appendRow();
    //tableModel2->setData(0,0,"sell");
    //tableModel2->setData(1,0,0.01);

}

MainWindow::~MainWindow()
{

}

void MainWindow::slotButtonAddUp(void)
{
    if (tableView1->currentIndex().row() >= 0)
      tableModel1->insertStringUp(tableView1->currentIndex().row());
}

void MainWindow::slotButtonAddDown(void)
{
    if (tableView1->currentIndex().row() >= 0)
       tableModel1->insertStringDown(tableView1->currentIndex().row());
}

void MainWindow::slotButtonDelete(void)
{
    if (tableView1->currentIndex().row() >= 0)
       tableModel1->deleteString(tableView1->currentIndex().row());
}

void MainWindow::slotButtonSave(void)
{
     QString filename = QFileDialog::getSaveFileName(
                        this,
                        tr("Сохранить таблицу"),
                        QDir::currentPath(),
                        tr("Файл таблицы (*.tfx)"));

     if ( filename.isEmpty() )
             return;
     tableModel1->save(filename );
}

void MainWindow::slotButtonLoad(void)
{
    QString filename = QFileDialog::getOpenFileName(
                        this,
                        tr("Загрузить таблицу"),
                        QDir::currentPath(),
                        tr("Файл таблицы (*.tfx)") );

     if ( filename.isEmpty() )
             return;
     tableModel1->load(filename);
}


bool searchDuplicate(float lev, const QVector<float> &vec)
{
    QString level = QString::number(lev,'f',4);
    int i;
    for (i = 0; i < vec.size(); i++)
       if (QString::number(vec[i],'f',4) == level)
           return true;
    return false;
}

QVector<float> createPriceLevels(const CTableData &table)
{
    int i;
    QString orderType;
    float price;
    float tp;
    QVector<float> vec;

    for (i = 0; i < table.rowCount(); i++)
    {
        orderType = table.getData(0,i).toString();
        price = table.getData(2,i).toFloat();
        tp = table.getData(3,i).toFloat();
        if ((orderType == "buy" || orderType == "sell") && tp > 0.0001 && searchDuplicate(tp, vec) == false)
            vec.push_back(tp);
        else
        if ((orderType == "buy stop" || orderType == "sell stop" || orderType == "buy limit" || orderType == "sell limit") && searchDuplicate(price, vec) == false)
            vec.push_back(price);

    }

    return vec;
}




//Функция возвращает каких ордеров больше и на какой объем
//Возвращаемое значение тип ордера, buy, sell или none, если объемы ордеров buy и sell равны
//n - на сколько штук относительно рабочего объема идет превышение
int MainWindow::getBuySell(const CTableData &tableData, float cur_volume, int &n)
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

   // qDebug()<<buy_volume<<sell_volume;
    count_buy = buy_volume / cur_volume + 0.5;
    count_sell = sell_volume / cur_volume + 0.5;

    if (count_buy > count_sell)
    {
        n = count_buy - count_sell;
        return e_buy;
    }
    if (count_sell > count_buy)
    {
        n = count_sell - count_buy;
        return e_sell;
    }

    n = 0;
    return e_null;


}

void MainWindow::emulate(CTableData &tableData, float lev)
{
    int i;
    unsigned int level = (lev + 0.00005) * 10000;

    for (i = 0; i < tableData.rowCount(); i++)
    {
        unsigned int price = (tableData.getData(2,i).toFloat() + 0.00005) *10000;
        unsigned int tp = (tableData.getData(3,i).toFloat() + 0.00005)*10000;
        if (tableData.getData(0,i) == "sell stop" && level <= price)
            tableData.setData(0,i,"sell");
        else
        if (tableData.getData(0,i) == "sell limit" && level >=price)
            tableData.setData(0,i,"sell");
        else
        if (tableData.getData(0,i) == "sell" && tp > 0 && level <= tp)
            tableData.clearRow(i);
        else
        if (tableData.getData(0,i) == "buy stop" && level >= price)
            tableData.setData(0,i,"buy");
        else
        if (tableData.getData(0,i) == "buy limit" && level <=price)
            tableData.setData(0,i,"buy");
        else
        if (tableData.getData(0,i) == "buy" && tp > 0 && level >= tp)
            tableData.clearRow(i);

    }
}

void MainWindow::slotButtonCalc(void)
{
    float current_volume = -1;
    int i,j,k;

    //Находим минимальный объем - это будет рабочим объемом
    for (i = 0; i < tableModel1->rowCount(); i++)
        if (tableModel1->getData(0,i) != "" && current_volume < 0)
            current_volume = tableModel1->getData(1,i).toFloat();
        else
        if (tableModel1->getData(0,i) != "" && current_volume > 0 && tableModel1->getData(1, i).toFloat() < current_volume)
            current_volume = tableModel1->getData(1,i).toFloat();

    if (current_volume < 0)
        return;

    qDebug()<<"Рабочий объем: "<<current_volume;

    int op, n;

    COrders orders = COrders(tableModel1->getTableData(), current_volume);
    orders.print();
    op = orders.getType();
    n = orders.getNum();


    CTableData tableData = tableModel1->getTableData();
    CLevels levels;

    QVector<float> priceLevels = createPriceLevels(tableData);

    for (i = 0; i < priceLevels.size(); i++)
    {

        tableData = tableModel1->getTableData();
        //эмулируем уровень какие ордера откроются или закроются на этом уровне
        emulate(tableData, priceLevels[i]);
        //смотрим превышение объема ордеров на данном уровне
        COrders orders2 = COrders(tableData, current_volume);
        //сопоставляем уровню превышение объема ордеров
        levels.addLevel(orders2.getType(), orders2.getNum(), priceLevels[i]);
    }

    tableModel2->clear();
    QVector<CResOrders> vec = levels.getResult(op, n);

    for (i = 0, k = 0; i < vec.size(); i++)
    {
        for (j = 0; j < vec[i].getNum(); j++, k++)
        {
          tableModel2->appendRow();
          tableModel2->setData(0, k, vec[i].getType());
          tableModel2->setData(1, k, current_volume);
          if (vec[i].getType() == "buy" || vec[i].getType() == "sell")
             tableModel2->setData(3, k, vec[i].getPrice());
          else
             tableModel2->setData(2, k, vec[i].getPrice());
        }
    }

}

void MainWindow::slotButtonClear(void)
{
    if (tableView1->currentIndex().row() >= 0)
       tableModel1->clearString(tableView1->currentIndex().row());
}

