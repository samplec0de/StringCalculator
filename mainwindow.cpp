#include "mainwindow.h"

static QGridLayout * grid = nullptr;
static QLineEdit * inputLineEdit = nullptr;
static QLineEdit * polishLabel = nullptr;
static QLineEdit * answer = nullptr;
static QLineEdit * logLineEdit = nullptr;
static VariablesTable * varsTable = nullptr;
std::string var_index[MAX_VARS_COUNT];
double var_value[MAX_VARS_COUNT];
static int vars_count = 0;
static Pair<Queue<std::string>, size_t> ans;

void setupGrid(QWidget * central) {
    grid = new QGridLayout(central);
}

void spawnLineEdit(MainWindow * window) {
    inputLineEdit = new QLineEdit;
    inputLineEdit->setPlaceholderText("Enter what you want to calculate");
    inputLineEdit->setFixedSize(QSize(window->mainFieldsSize, 100));
    inputLineEdit->setStyleSheet("QLineEdit { "
                                 "background: rgb(30, 30, 30);"
                                 "font-size: 30px;"
                                 "}");
    grid->addWidget(inputLineEdit, 3, 3, 4, 4);
    grid->setAlignment(inputLineEdit, Qt::AlignTop);
}

void spawnPolishLabel(MainWindow * window) {
//    QScrollArea * polishScrollArea = new QScrollArea;
    polishLabel = new QLineEdit;
    polishLabel->setMinimumSize(window->mainFieldsSize, 100);
    polishLabel->setReadOnly(true);
//    polishLabel->setMaximumSize(QSize(window->mainFieldsSize, 10));
    polishLabel->setStyleSheet("QLineEdit { "
                               "background: rgb(30, 30, 30);"
                               "font-size: 35px;"
                               "color: #ffffff;"
                               "}");

    polishLabel->setFixedSize(QSize(window->mainFieldsSize, 50));
//    polishScrollArea->setWidget(polishLabel);
//    polishScrollArea->setBackgroundRole(QPalette::Dark);
    grid->addWidget(polishLabel, 9, 3, 4, 4);
    grid->setAlignment(polishLabel, Qt::AlignTop);
}

void spawnCosmetic(MainWindow * window) {
    QLabel * polish = new QLabel("Your postfix entry is:");
    polish->setStyleSheet("QLabel { "
                          "color: rgb(0, 200, 0); "
                          "font-size: 25px;"
                          "}");
    grid->addWidget(polish, 8, 3, 1, 1);
    grid->setAlignment(polish, Qt::AlignTop);

}

void spawnVarsTable(MainWindow * window) {
    varsTable = new VariablesTable();
    grid->addWidget(varsTable, 3, 10, 9, 1);
    varsTable->show();
}

void spawnAnswer(MainWindow * window) {
    answer = new QLineEdit;
    answer->setMinimumSize(100, 40);
    answer->setReadOnly(true);
    answer->setStyleSheet("QLineEdit { "
                          "background: rgb(7, 7, 7);"
                          "font-size: 30px;"
                          "}");
    answer->setText("");

    QLabel * answerInfoLabel = new QLabel;
    answerInfoLabel->setMinimumSize(100, 48);
    answerInfoLabel->setMaximumSize(QSize(20, 10));
    answerInfoLabel->setStyleSheet("QLabel { "
                                   "background: rgb(7, 7, 7);"
                                   "font-size: 30px;"
                                   "}");
    answerInfoLabel->setText("Result: ");
    grid->addWidget(answer, 7, 6, 1, 1);
    grid->addWidget(answerInfoLabel, 7, 3, 1, 1);
    grid->setAlignment(answerInfoLabel, Qt::AlignLeft | Qt::AlignTop);
    grid->setAlignment(answer, Qt::AlignRight);
}

void spawnlogLineEdit(MainWindow * window) {
    logLineEdit = new QLineEdit;
    logLineEdit->setReadOnly(true);
    logLineEdit->setFixedHeight(48);
    logLineEdit->setStyleSheet("QLineEdit { "
                       "background: rgb(32, 30, 30);"
                       "font-size: 30px;"
                       "}"
                       "");
    grid->addItem(new QSpacerItem(10, 20), 11, 3);
    grid->addWidget(logLineEdit, 12, 3, 3, 8);
}

void clearVars() {
    logLineEdit->setText("");
    polishLabel->setText("");
    while (varsTable->table->rowCount() > 0) {
        varsTable->table->removeRow(0);
    }
    for (size_t i = 0; i < MAX_VARS_COUNT; ++i)
        var_value[i] = SERVICE_VALUE;
}

void MainWindow::userEnter() {
//    qDebug() << inputLineEdit->text();
    clearVars();
    answer->setText("");
    try {
        std::string input = inputLineEdit->text().toStdString();
        if (input.size() == 0) {
            return;
        }
        ans = convert(input, var_index, 0);
        Queue<std::string> q;
        Queue<std::string> q2 = ans.first;
        std::string POLIS = "";
        while (!q2.is_empty()) {
            q.push(q2.front());
            POLIS += q2.front();
            POLIS += ' ';
            q2.pop();
        }
        polishLabel->setText(QString::fromStdString(POLIS));
        ans.first = q;
        vars_count = int(ans.second);
        if (ans.second != 0) {
            varsTable->table->setRowCount(int(ans.second));
            for (size_t i = 0; i < ans.second; ++i) {
                QTableWidgetItem * item =  new QTableWidgetItem(QString::fromStdString(var_index[i]));
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                varsTable->table->setItem(int(i), 0, item);
                QTableWidgetItem * item_2 =  new QTableWidgetItem("");
                varsTable->table->setItem(int(i), 1, item_2);
            }
        }
        else {
            answer->setText(QString::fromStdString(std::to_string(count_postfix_entry(ans, var_index, var_value))));
        }
    } catch (DijkstraValidateException e) {
        logLineEdit->setText(QString::fromStdString(e.reason()));
    } catch (MathException e) {
        logLineEdit->setText(QString::fromStdString(e.reason()));
    }
    catch (UtilsException e) {
            logLineEdit->setText(QString::fromStdString(e.reason()));
    }
    catch (DijkstraException e) {
            logLineEdit->setText(QString::fromStdString(e.reason()));
    }
    catch (...) {
        logLineEdit->setText("Invalid syntax");
    }
}

bool setVariable(std::string var, double val) {
    bool allSet = true;
    for (int i = 0; i < vars_count; ++i) {
        if (var_index[i] == var) {
//            qDebug() << QString::fromStdString(var) << ' ' << val;
            var_value[i] = val;
        }
        if (fabs(var_value[i] - SERVICE_VALUE) <= 1e-8) {
            allSet = false;
        }
    }
    return allSet;
}

void MainWindow::tableChanged(int row, int column) {
    auto val = varsTable->table->item(row, column);
    auto var = varsTable->table->item(row, column - 1);
    if (val == nullptr || var == nullptr) return;
    if (!is_integer_or_double(val->text().toStdString())) {
       varsTable->table->item(row, column)->setText("");
       setVariable(var->text().toStdString(), SERVICE_VALUE);
       answer->setText("");
       return;
    }
    if (setVariable(var->text().toStdString(), val->text().toDouble())) {
        try {
            std::string input = inputLineEdit->text().toStdString();
            ans = convert(input, var_index, 0);
            answer->setText(QString::fromStdString(std::to_string(count_postfix_entry(ans, var_index, var_value))));
        } catch (DijkstraValidateException e) {
            logLineEdit->setText(QString::fromStdString(e.reason()));
        } catch (MathException e) {
            logLineEdit->setText(QString::fromStdString(e.reason()));
        }
        catch (UtilsException e) {
                logLineEdit->setText(QString::fromStdString(e.reason()));
        }
        catch (DijkstraException e) {
                logLineEdit->setText(QString::fromStdString(e.reason()));
        }
        catch (...) {
            logLineEdit->setText("Invalid syntax");
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setStyleSheet("MainWindow {"
                        "background-color: rgb(7,7,7);"
                        "}");
    this->mainFieldsSize = 650;
    QWidget * central = new QWidget(this);
    this->setCentralWidget(central);
    setupGrid(centralWidget());
    spawnLineEdit(this);
    spawnCosmetic(this);
    spawnPolishLabel(this);
    this->setMinimumSize(QSize(940, 500));
    grid->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    spawnVarsTable(this);
    spawnAnswer(this);
    spawnlogLineEdit(this);
    connect(inputLineEdit, SIGNAL(returnPressed()), SLOT(userEnter()));
    connect(varsTable->table, SIGNAL(cellChanged(int, int)), SLOT(tableChanged(int, int)));
}

MainWindow::~MainWindow() {

}
