#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QMessageBox>
#include <QTableView>
#include <QLabel>
#include <QAbstractItemModel>
#include "tablemodel1.h"
#include "tablemodel2.h"
#include <QPushButton>
#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"
#include <QPushButton>
#include <QHeaderView>
#include <QDebug>
#include <QFileDialog>
#include <iostream>
#include "levels.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *mainWidget;
    QGridLayout *mainLayout;
    QLabel *label1;
    QLabel *label2;
    QTableView *tableView1;
    QTableView *tableView2;
    CTableModel1 *tableModel1;
    CTableModel2 *tableModel2;
    QPushButton *buttonAddUp, *buttonAddDown, *buttonDelete, *buttonSave, *buttonLoad, *buttonCalc, *buttonClear, *buttonSaveAs;
    QString fname;
    QLabel openedFile;

    int getBuySell(const CTableData &tableData, float cur_volume, int &n);
    void emulate(CTableData &tableData, float lev);

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotButtonAddUp(void);
    void slotButtonAddDown(void);
    void slotButtonDelete(void);
    void slotButtonSave(void);
    void slotButtonSaveAs(void);
    void slotButtonLoad(void);
    void slotButtonCalc(void);
    void slotButtonClear(void);
};

#endif // MAINWINDOW_H
