#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //设置主窗口背景颜色
    QPalette plt;
    plt.setColor(QPalette::Window, QColor(175, 255, 170));
    this->setPalette(plt);

    ConnectMySQLDBFunc();

    //禁止窗口最大化按钮
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

    //禁止用户拖拉窗口改变大小
    setFixedSize(this->width(), this->height());

    //tablewidget表格控件初始化操作
    TableWidgetListDataFunc();

    InitTableWidgetFunc();

}

MainWidget::~MainWidget()
{
    delete ui;
}

//连接mysql数据库函数
void MainWidget::ConnectMySQLDBFunc()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("manager_db");
    db.setUserName("root");
    db.setPassword("Yyc7161319%");

    bool bok = db.open();
    if(!bok){
        QMessageBox::information(this, "OBDC", "MYSQL connect fail!");
    }
}

//tablewidget表格控件初始化操作
void MainWidget::TableWidgetListDataFunc()
{
    //编号 样品名称 数量 检验项目 委托单位 负责人 入库时间 出库时间 备注

    //设置表格控件200行9列
    ui->dataTableWidget->setColumnCount(9);
    ui->dataTableWidget->setRowCount(200);

    //设置表头
    ui->dataTableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"样品名称"<<"数量"<<"检验项目"<<"委托单位"
                                                                 <<"负责人"<<"入库时间"<<"出库时间"<<"备注");

}

void MainWidget::InitTableWidgetFunc()
{
    //调整列宽度
    ui->dataTableWidget->setColumnWidth(0, 80);
    ui->dataTableWidget->setColumnWidth(1, 150);
    ui->dataTableWidget->setColumnWidth(2, 80);
    ui->dataTableWidget->setColumnWidth(3, 200);
    ui->dataTableWidget->setColumnWidth(4, 300);
    ui->dataTableWidget->setColumnWidth(5, 80);
    ui->dataTableWidget->setColumnWidth(6, 200);
    ui->dataTableWidget->setColumnWidth(7, 200);
    ui->dataTableWidget->setColumnWidth(8, 80);


    QSqlQuery sqlquery;
    sqlquery.exec("select * from stockdata");

    int i = 0;

    //编号 样品名称 数量 检验项目 委托单位 负责人 入库时间 出库时间 备注
    while(sqlquery.next()){
        QString strstockid = sqlquery.value(0).toString();
        QString strstockname = sqlquery.value(1).toString();
        QString strstockcount = sqlquery.value(2).toString();
        QString strstockpj = sqlquery.value(3).toString();
        QString strstocksp = sqlquery.value(4).toString();
        QString strstockmg = sqlquery.value(5).toString();
        QString strstockit = sqlquery.value(6).toString();
        QString strstockot = sqlquery.value(7).toString();
        QString strstockth = sqlquery.value(8).toString();

        ui->dataTableWidget->setItem(i, 0, new QTableWidgetItem(strstockid));
        ui->dataTableWidget->setItem(i, 1, new QTableWidgetItem(strstockname));
        ui->dataTableWidget->setItem(i, 2, new QTableWidgetItem(strstockcount));
        ui->dataTableWidget->setItem(i, 3, new QTableWidgetItem(strstockpj));
        ui->dataTableWidget->setItem(i, 4, new QTableWidgetItem(strstocksp));
        ui->dataTableWidget->setItem(i, 5, new QTableWidgetItem(strstockmg));
        ui->dataTableWidget->setItem(i, 6, new QTableWidgetItem(strstockit));
        ui->dataTableWidget->setItem(i, 7, new QTableWidgetItem(strstockot));
        ui->dataTableWidget->setItem(i, 8, new QTableWidgetItem(strstockth));
        i++;
    }
}


void MainWidget::on_dataSelectBtn_clicked()
{
    //表格控件初始化
    InitTableWidgetFunc();

    //清空表格
    ui->dataTableWidget->clear();

    //设置表头
    ui->dataTableWidget->setHorizontalHeaderLabels(QStringList()<<"编号"<<"样品名称"<<"数量"<<"检验项目"<<"委托单位"
                                                                 <<"负责人"<<"入库时间"<<"出库时间"<<"备注");

    QSqlQuery sqlquery;
    QString strid = "stockid=";
    strid += ui->numLineEdit->text();

    //QMessageBox::information(this, "test", strid);

    QString str = QString("select * from stockdata where %1").arg(strid);
    //QMessageBox::information(this, "test", str);

    sqlquery.exec(str);

    int i = 0;

    //编号 样品名称 数量 检验项目 委托单位 负责人 入库时间 出库时间 备注
    while(sqlquery.next()){
        QString strstockid = sqlquery.value(0).toString();
        QString strstockname = sqlquery.value(1).toString();
        QString strstockcount = sqlquery.value(2).toString();
        QString strstockpj = sqlquery.value(3).toString();
        QString strstocksp = sqlquery.value(4).toString();
        QString strstockmg = sqlquery.value(5).toString();
        QString strstockit = sqlquery.value(6).toString();
        QString strstockot = sqlquery.value(7).toString();
        QString strstockth = sqlquery.value(8).toString();

        ui->dataTableWidget->setItem(i, 0, new QTableWidgetItem(strstockid));
        ui->dataTableWidget->setItem(i, 1, new QTableWidgetItem(strstockname));
        ui->dataTableWidget->setItem(i, 2, new QTableWidgetItem(strstockcount));
        ui->dataTableWidget->setItem(i, 3, new QTableWidgetItem(strstockpj));
        ui->dataTableWidget->setItem(i, 4, new QTableWidgetItem(strstocksp));
        ui->dataTableWidget->setItem(i, 5, new QTableWidgetItem(strstockmg));
        ui->dataTableWidget->setItem(i, 6, new QTableWidgetItem(strstockit));
        ui->dataTableWidget->setItem(i, 7, new QTableWidgetItem(strstockot));
        ui->dataTableWidget->setItem(i, 8, new QTableWidgetItem(strstockth));
    }
}


void MainWidget::on_inputBtn_clicked()
{
    inputStock* inputst = new inputStock();
    inputst->show();
}


void MainWidget::on_outputBtn_clicked()
{
    outputstock* output = new outputstock();
    output->show();
}



void MainWidget::on_loadDataBtn_clicked()
{

}


void MainWidget::on_dropBtn_clicked()
{
    //获取当前选择行
    int iRow = ui->dataTableWidget->currentRow();

    //根据行获取对应编号
    QString strId = ui->dataTableWidget->model()->index(iRow,0).data().toString();
    //QMessageBox::information(this, "tips", strId);

    //判断是否选择了样品进行删除
    if(strId == ""){
        QMessageBox::critical(this, "Tips", "请选择要删除的样品！");
        return;
    }

    //首先：提醒用户是否确认删除
    int iclick = QMessageBox::warning(this,"Tips", "请确认是否要删除样品！",QMessageBox::Yes|QMessageBox::No);

    //判断返回结果
    if(iclick == QMessageBox::Yes){

        QSqlQuery sqlquery;
        QString sqlstr = QString("delete from stockdata where stockid=%1").arg(strId);
        if(sqlquery.exec(sqlstr)){
            QMessageBox::information(this, "Tips", "样品删除成功！");
        }

        InitTableWidgetFunc();
    }
    else{
        return;
    }
}


void MainWidget::on_updataBtn_clicked()
{
    QSqlQuery sqlquery;
    sqlquery.exec("select * from stockdata");

    int i = 0;

    //编号 样品名称 数量 检验项目 委托单位 负责人 入库时间 出库时间 备注
    while(sqlquery.next()){
        QString strstockid = sqlquery.value(0).toString();
        QString strstockname = sqlquery.value(1).toString();
        QString strstockcount = sqlquery.value(2).toString();
        QString strstockpj = sqlquery.value(3).toString();
        QString strstocksp = sqlquery.value(4).toString();
        QString strstockmg = sqlquery.value(5).toString();
        QString strstockit = sqlquery.value(6).toString();
        QString strstockot = sqlquery.value(7).toString();
        QString strstockth = sqlquery.value(8).toString();

        ui->dataTableWidget->setItem(i, 0, new QTableWidgetItem(strstockid));
        ui->dataTableWidget->setItem(i, 1, new QTableWidgetItem(strstockname));
        ui->dataTableWidget->setItem(i, 2, new QTableWidgetItem(strstockcount));
        ui->dataTableWidget->setItem(i, 3, new QTableWidgetItem(strstockpj));
        ui->dataTableWidget->setItem(i, 4, new QTableWidgetItem(strstocksp));
        ui->dataTableWidget->setItem(i, 5, new QTableWidgetItem(strstockmg));
        ui->dataTableWidget->setItem(i, 6, new QTableWidgetItem(strstockit));
        ui->dataTableWidget->setItem(i, 7, new QTableWidgetItem(strstockot));
        ui->dataTableWidget->setItem(i, 8, new QTableWidgetItem(strstockth));
        i++;
    }
}

