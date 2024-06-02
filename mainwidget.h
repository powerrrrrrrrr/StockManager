#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

//操作数据库相关的头文件
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>
#include <QFileDialog>
#include <QDesktopServices>

#include "inputstock.h"
#include "outputstock.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    //连接mysql数据库函数
    void ConnectMySQLDBFunc();

    //tablewidget表格控件初始化操作
    void TableWidgetListDataFunc();

    //设置表格列宽
    void InitTableWidgetFunc();


private slots:
    void on_dataSelectBtn_clicked();

    void on_inputBtn_clicked();

    void on_outputBtn_clicked();

    void on_loadDataBtn_clicked();

    void on_dropBtn_clicked();

    void on_updataBtn_clicked();

private:
    Ui::MainWidget *ui; 
};
#endif // MAINWIDGET_H
