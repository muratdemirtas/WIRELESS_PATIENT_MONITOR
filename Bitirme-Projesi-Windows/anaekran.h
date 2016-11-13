#ifndef ANAEKRAN_H
#define ANAEKRAN_H
#include <QTcpSocket>
#include <QMainWindow>
#include <QtMultimedia>
#include <QLabel>
#include <QListView>
#include <QTimer>
#include <QPushButton>
#include <QUrl>
#include <QtSql>
#include <dialog.h>

namespace Ui {
class anaekran;
}

class anaekran : public QMainWindow
{
    Q_OBJECT

public:
    explicit anaekran(QWidget *parent = 0);
    ~anaekran();
public slots:

signals :
    void verigonder(QString);


private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void grafikciz();
    void on_pushButton_22_clicked();
    void on_horizontalSlider_valueChanged(int value);


    void on_pushButton_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_5_clicked();
    void veriiste();
    void veriyolla();
    void on_pushButton_25_clicked();

private:
    double x[100];
    double y[100];
    Ui::anaekran *ui;
    QTcpSocket *soket,*soket2;
    QMediaPlayer *player;
    QLabel label;
    QLabel label_12;
    QPushButton *pushButton_3;
    QStringListModel *model;


QSqlQueryModel *liste;

QSqlQuery *query;
QTimer   *timer;
QTimer   *timer2;
};





#endif // ANAEKRAN_H
