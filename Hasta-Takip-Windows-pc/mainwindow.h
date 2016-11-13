#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_22_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_horizontalSlider_valueChanged(int value);
    void grafikciz();
    void veriiste();


    void on_pushButton_25_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;

QSqlQueryModel *liste;
QTimer   *timer;
QTimer   *timer2;
QSqlQuery *query;
};

#endif // MAINWINDOW_H
