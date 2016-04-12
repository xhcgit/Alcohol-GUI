#include "FindData.h"
#include "ui_FindData.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QVBoxLayout>

FindData::FindData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindData)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    queryModel = new QSqlQueryModel;
    ui->tableView->setModel(queryModel);
}

FindData::~FindData()
{
    delete queryModel;
    delete ui;
}

//查询当天的数据
void FindData::on_pushButton_clicked()
{
    /*QDate date = ui->dateEdit->date();
    QString strDate = date.toString("yyyy-MM-dd");

    QSqlQuery query;
    QString str = "2016-04-13";
    //QDateTime dt;
    //dt = QDateTime::fromString(str,"yyyy-MM-dd-HH:mm:ss");
    //qDebug() << dt;
    query.prepare("select * from ValueFromSerialport where receiveTime > :str");
    query.bindValue(":str",str);
    query.exec();
    while(query.next())
    {
        qDebug() << query.value(0);
    }*/

   /* QSqlQuery query;
    QDate date = ui->dateEdit->date();
    QString str = date.toString("yyyy-MM-dd");
    query.prepare("select * from ValueFromSerialport where receiveTime > :str");
    query.bindValue(":str",str);
    queryModel->setQuery(query);
    queryModel->query();*/

    QSqlQuery query;
    QString today = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString nextDay = ui->dateEdit->date().addDays(1).toString();

    queryModel->setQuery(QString("select * from ValueFromSerialport where receiveTime > '%1' and receiveTime < '%2' ")
                         .arg(today).arg(nextDay));
    queryModel->query();
    queryModel->setHeaderData(0, Qt::Horizontal, "时间");
    queryModel->setHeaderData(1, Qt::Horizontal, "酒精值");
}