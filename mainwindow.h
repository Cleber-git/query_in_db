#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QSqlDatabase"
#include "QSqlQuery"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void configDb();
    void closeDb();
    void updateNotification();

private slots:
    void on_buttonSend_clicked();
public slots:
    void getNotification();
private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
//    QSqlQuery query;
    QString path;

};
#endif // MAINWINDOW_H
