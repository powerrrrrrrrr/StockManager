#include "inputstock.h"
#include "ui_inputstock.h"

inputStock::inputStock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inputStock)
{
    ui->setupUi(this);

    //禁止窗口最大化按钮
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

    //禁止用户拖拉窗口改变大小
    setFixedSize(this->width(), this->height());

    //光标定位
    ui->lineEditId->setFocus();
}

inputStock::~inputStock()
{
    delete ui;
}

void inputStock::on_inStockBtn_clicked()
{
    QString stockId = ui->lineEditId->text();
    QString stockName = ui->lineEditName->text();
    QString stockCount = ui->lineEditCount->text();
    QString stockProject = ui->lineEditProject->text();
    QString stockSuplier = ui->lineEditSuplier->text();
    QString stockMag = ui->lineEditManger->text();
    QString stockOther = ui->textEditOther->toPlainText();
    QString stockInputTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    if(ui->lineEditId->text().isEmpty()){
        QMessageBox::critical(this,"Tips", "样品编号不能为空！");
        ui->lineEditId->setFocus();
        return;
    }
    if(ui->lineEditName->text().isEmpty()){
        QMessageBox::critical(this,"Tips", "样品名称不能为空！");
        ui->lineEditName->setFocus();
        return;
    }
    if(ui->lineEditCount->text().isEmpty()){
        QMessageBox::critical(this,"Tips", "样品数量不能为空！");
        ui->lineEditCount->setFocus();
        return;
    }
    if(ui->lineEditProject->text().isEmpty()){
        QMessageBox::critical(this,"Tips", "检验项目不能为空！");
        ui->lineEditProject->setFocus();
        return;
    }
    if(ui->lineEditSuplier->text().isEmpty()){
        QMessageBox::critical(this,"Tips", "委托单位不能为空！");
        ui->lineEditSuplier->setFocus();
        return;
    }
    if(ui->lineEditManger->text().isEmpty()){
        QMessageBox::critical(this,"Tips", "负责人不能为空！");
        ui->lineEditManger->setFocus();
        return;
    }

    QString addstr = QString("insert into stockdata(stockid, stockname, count, project, supplier, manager, whentimein, other) "
                             "values('%1','%2','%3','%4','%5','%6','%7','%8')")
                         .arg(stockId).arg(stockName).arg(stockCount).arg(stockProject).arg(stockSuplier)
                         .arg(stockMag).arg(stockInputTime).arg(stockOther);
    //QMessageBox::information(this, "msg", addstr);

    QSqlQuery sqlquery;
    if(sqlquery.exec(addstr)){
        QMessageBox::information(this, "Tips","样品添加成功！");
    }
    else{
        QMessageBox::information(this, "Tips","样品添加失败，请重新添加。");
    }
}


void inputStock::on_cancelBtn_clicked()
{
    close();
}

