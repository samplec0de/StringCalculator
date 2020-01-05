#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QScrollArea>
#include <QPlainTextEdit>
#include "variablestable.h"
#include <QHeaderView>
#include <QDebug>
#include "Utils.hpp"
#include "Dijkstra.hpp"
#include "CommonStructures.hpp"
#include "PostfixToInt.hpp"

const double SERVICE_VALUE = (-1e9 - 48);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int mainFieldsSize;
public slots:
    void userEnter();
    void tableChanged(int, int);
};

#endif // MAINWINDOW_H
