#ifndef OUTPUTSTOCK_H
#define OUTPUTSTOCK_H

#pragma execution_character_set("utf-8");

#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlQuery>

namespace Ui {
class outputstock;
}

class outputstock : public QWidget
{
    Q_OBJECT

public:
    explicit outputstock(QWidget *parent = nullptr);
    ~outputstock();

    //初始化combo box 控件
    void InitComboBoxFunc();

private slots:


    void on_outputBtn_clicked();

    void on_cancleBtn_clicked();

    void on_selectBtn_clicked();

private:
    Ui::outputstock *ui;
};

#endif // OUTPUTSTOCK_H
