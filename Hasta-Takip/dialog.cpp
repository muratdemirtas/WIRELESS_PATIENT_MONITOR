#include "dialog.h"
#include "ui_dialog.h"
QString hedef_ip;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
socket = new QTcpSocket();

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString komut="";
    komut+="komut/";
    komut+="ledac";
     komut+="*";
     komut+=",";
     komut+="hello";
    socket->write(komut.toUtf8().data());
    socket->waitForBytesWritten(30000);
    komut="";
}

void Dialog::on_pushButton_3_clicked()
{

    QString komut="";
    komut+="komut/";
    komut+="ledkapa";
    komut+="*";
    komut+=",";
    komut+="hello";
    socket->write(komut.toUtf8().data());
    socket->waitForBytesWritten(30000);
    komut="";
}

void Dialog::verial(QString ip) {
hedef_ip=ip;
qDebug()   << "gelen_ip" << hedef_ip;


 socket->connectToHost(hedef_ip,80);
}

void Dialog::on_pushButton_2_clicked()
{

    QString komut="";
    komut+="komut/";
    komut+="sesac";
     komut+="*";
     komut+=",";
     komut+="hello";
    socket->write(komut.toUtf8().data());
    socket->waitForBytesWritten(30000);
    komut="";
}

void Dialog::on_pushButton_4_clicked()
{

    QString komut="";
    komut+="komut/";
    komut+="seskapa";
     komut+="*";
    socket->write(komut.toUtf8().data());
    socket->waitForBytesWritten(30000);
    komut="";
}

void Dialog::on_horizontalSlider_valueChanged(int value)
{
    QString komut="";
    komut+="komut/";
     komut+="*";
    komut+=QString(value);
    socket->write(komut.toUtf8().data());
    socket->waitForBytesWritten(30000);
    komut="";
}

void Dialog::on_verticalSlider_valueChanged(int value)
{
    QString komut="";
    komut+="komut/";
    komut+=value;
     komut+=",";
     komut+="hello";
    socket->write(komut.toUtf8().data());
    socket->waitForBytesWritten(30000);
    komut="";
}

void Dialog::on_pushButton_5_clicked()
{
    QString komut="";
    komut+="komut/";
    komut+="alarm";
     komut+="*";
    socket->write(komut.toUtf8().data());
    socket->waitForBytesWritten(30000);
    komut="";
}

void Dialog::on_pushButton_6_clicked()
{
    Dialog::close();
}
