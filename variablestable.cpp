#include "variablestable.h"

VariablesTable::VariablesTable(QWidget *parent) : QWidget(parent)
{
    this->table = new QTableWidget();
    table->setFixedSize(QSize(240, 280));
    this->setFixedSize(QSize(240, 280));
    QScrollArea * mainScrollArea = new QScrollArea(this);
    mainScrollArea->setMaximumSize(QSize(348, 400));
    mainScrollArea->setWidget(table);
    table->setColumnCount(2);
    table->setColumnWidth(0, 130);
    table->setColumnWidth(1, 105);
    auto variable = new QTableWidgetItem("Variable");
    variable->setBackgroundColor(QColor("#2c2d2f"));
    QFont font = variable->font();
    font.setPointSize(14);
    variable->setFont(font);
    auto value = new QTableWidgetItem("Value");
    value->setFont(font);
    value->setBackgroundColor(QColor("#2c2d2f"));
    table->setHorizontalHeaderItem(0, variable);
    table->setHorizontalHeaderItem(1, value);
    table->verticalHeader()->setVisible(false);
    table->setAlternatingRowColors(true);
    this->setStyleSheet("VariablesTable {"
                        "background-color: rgb(10, 5, 1);"
                        "}");
    mainScrollArea->setStyleSheet("VariablesTable {"
                        "background-color: rgb(10, 5, 1);"
                        "}");
    table->setStyleSheet("QTableView {"
                         "alternate-background-color: rgb(30, 30, 30);"
                         "background-color: rgb(10, 5, 1);"
                         "background: rgb(10, 5, 1);"
                         "gridline-color: #138808;"
                         "}"
                         "QTableView::item {"
                         "background: rgb(10, 5, 1);"
                         "}"
                         "QTableView:item:hover {background-color: #138808;}"
                         "QLineEdit {"
                         "background: rgb(10, 5, 1);;"
                         "}"
                         );

//    table->model()->setData(table->model()->index(0, 0, QModelIndex()), QVariant(QColor(Qt::red)), Qt::DecorationRole);
}
