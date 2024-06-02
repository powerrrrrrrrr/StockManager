#ifndef INPUTSTOCK_H
#define INPUTSTOCK_H

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlQuery>

namespace Ui {
class inputStock;
}

class inputStock : public QWidget
{
    Q_OBJECT

public:
    explicit inputStock(QWidget *parent = nullptr);
    ~inputStock();

private slots:
    void on_inStockBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::inputStock *ui;
};

#endif // INPUTSTOCK_H
