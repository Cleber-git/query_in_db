#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include <QDebug>
#include <QSqlError>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getNotification()));
    timer->start(10000);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonSend_clicked()
{
//    qDebug()<< QSqlDatabase::drivers();

    if(ui->order->text().isEmpty() || ui->password->text().isEmpty()) return;
    QString sql;


    configDb();
    QSqlQuery query;

    if (db.open()) {
        int notification = 1;

        sql = "INSERT INTO fluxo (orders, password, notification) VALUES (:orders, :password, :n)";

        query.prepare(sql);
        qDebug() << ui->order->text() << "  " << ui->password->text() << notification;

        query.bindValue(":orders", ui->order->text());
        query.bindValue(":password", ui->password->text());
        query.bindValue(":n", notification);

        if (!query.exec()){

            qDebug() << "not exec query" << query.lastError().text(); ;

            return;
        }
        qDebug() << "exec query: OK";
        closeDb();
        return;
    }
    qDebug() << "db not open";

}


void MainWindow::getNotification(){


    configDb();
    if(db.open()){
        QSqlQuery query;
        QString sql;
        sql = "update fluxo set notification = 0 where notification = :val";

        query.prepare(sql);
        query.bindValue(":val", 1);
        if(!query.exec()) return;
        qDebug() << "passei";
    }

    closeDb();
}

void MainWindow::configDb(){

    path = qApp->applicationDirPath();
    path += "/pedidos.db";
    qDebug() << path;
    db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

}

void MainWindow::closeDb(){
    db.close();
}

void MainWindow::updateNotification(){





}
