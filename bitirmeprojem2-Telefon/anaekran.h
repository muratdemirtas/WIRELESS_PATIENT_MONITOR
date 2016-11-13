#ifndef ANAEKRAN_H
#define ANAEKRAN_H
#include <QTcpSocket>
#include <QMainWindow>
#include <QtMultimedia>
#include <QLabel>
#include <QListView>
#include <QTimer>
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
    void verioku();

    void deneme();
void pingkontrol();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();
void veriiste();
private:
    Ui::anaekran *ui;
    QTcpSocket *soket;
    QMediaPlayer *player;
    QLabel label;
QNetworkAccessManager *menajer;
QNetworkReply *reply;

 QTimer   *timer;
};

#endif // ANAEKRAN_H
