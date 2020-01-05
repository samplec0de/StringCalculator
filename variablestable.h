#ifndef VARIABLESTABLE_H
#define VARIABLESTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QScrollArea>
#include <QHeaderView>

class VariablesTable : public QWidget
{
    Q_OBJECT
public:
    QTableWidget * table;
    explicit VariablesTable(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // VARIABLESTABLE_H
