#include "outputstock.h"
#include "ui_outputstock.h"

outputstock::outputstock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::outputstock)
{
    ui->setupUi(this);

    //禁止窗口最大化按钮
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

    //禁止用户拖拉窗口改变大小
    setFixedSize(this->width(), this->height());

    //初始化combo box 控件
    InitComboBoxFunc();
}

outputstock::~outputstock()
{
    delete ui;
}

//初始化combo box 控件
void outputstock::InitComboBoxFunc()
{
    int i = 0;
    QSqlQuery sqlQuery;
    sqlQuery.exec("select * from stockdata");

    QString strid;
    while(sqlQuery.next()){
        strid = sqlQuery.value(0).toString();
        ui->idcomBox->insertItem(i, strid);
        i++;
    }
}



void outputstock::on_outputBtn_clicked()
{
    QSqlQuery sqlQuery;
    QString strid = ui->idcomBox->currentText();

    if(ui->numLineEdit->text().isEmpty()){
        QMessageBox::critical(this, "Tips", "数量不能为空！");
        ui->numLineEdit->setFocus();
        return;
    }

    //获取数据表中商品编号对应的数量
    QString str = QString("select count from stockdata where stockid=%1;").arg(strid);
    sqlQuery.exec(str);
    QString strCnt;
    while(sqlQuery.next()){
        strCnt = sqlQuery.value(0).toString();
    }
    //获取要出库的数量
    QString strnum = ui->numLineEdit->text();

    int tableNum = strCnt.toUInt();
    int outNum = strnum.toInt();
    int resNum = tableNum - outNum;

    QString strres = QString::number(resNum);

    //更新表中数据
    QString curtime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString strdb = QString("update stockdata set count=%1,whentimeout=\"%2\" where stockid=%3").arg(strres).arg(curtime).arg(strid);
    QMessageBox::information(this, "tips", strdb);
    if(sqlQuery.exec(strdb)){
        QMessageBox::information(this, "Tips", "样品出库成功！");
    }
    else{
        QMessageBox::information(this, "Tips", "样品出库失败！");
    }


}


void outputstock::on_cancleBtn_clicked()
{
    close();
}


void outputstock::on_selectBtn_clicked()
{
    QString outputStockId = ui->idcomBox->currentText();
    QString selectStr = QString("select count from stockdata where stockid=%1;").arg(outputStockId);
    //QMessageBox::information(this, "Tips", selectStr);

    QSqlQuery selectCntQuery;
    selectCntQuery.exec(selectStr);
    while(selectCntQuery.next()){
        QString res = selectCntQuery.value(0).toString();
        //QMessageBox::information(this, "Tips", res);
        ui->numLineEdit->setText(res);
    }
}

