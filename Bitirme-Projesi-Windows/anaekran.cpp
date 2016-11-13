#include "anaekran.h"
#include "ui_anaekran.h"
#include <QString>
#include <QTimer>
#include <QDesktopWidget>
#include <QUrl>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtGlobal>
#include <iostream>
#include <QDialog>
#include <dialog.h>

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

Dialog *dialog;
QString hasta,kimlik,ekgverisi;
QString istek,client_ip;
int sayac1,sayac2;
anaekran::anaekran(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::anaekran)
{
    ui->setupUi(this);
    qDebug() << "Sunucu/is parcacigi : Veri tabani olusturuluyor";

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("onlinehastalar");
    db.setHostName("127.0.0.1");
    db.setUserName("hasta");
    db.setPassword("hasta");
    db.setPort(5555);
    if (!db.open()) {
        qDebug() << "Databaseye Erisirken Hata Olustu";

        }
    else {
         qDebug() << "Online Hasta Veritabanina Baglanildi.";
    }



  //  QMainWindow::maximumSize();
    timer  =new QTimer(this);
    timer2 = new QTimer(this);
    timer->setInterval(3000);
    timer2->setInterval(3000);
    connect(timer,SIGNAL(timeout()),SLOT(veriiste()));
    connect(timer2,SIGNAL(timeout()),SLOT(grafikciz()));


    QPixmap pixmap(":/new/prefix1/resources/logo.png");
    ui->label->setPixmap(pixmap);
    ui->label->setMask(pixmap.mask());
    ui->label->setScaledContents(true);
    ui->label->show();

    QPixmap pixmap5(":/new/prefix1/resources/call.png");
    ui->label_23->setPixmap(pixmap5);
    ui->label_23->setMask(pixmap5.mask());
    ui->label_23->setScaledContents(true);
    ui->label_23->show();

    QPixmap pixmap2(":/new/prefix1/resources/kalp.png");
    ui->label_12->setPixmap(pixmap2);
    ui->label_12->setMask(pixmap2.mask());
    ui->label_12->setScaledContents(true);
    ui->label_12->show();

    QPixmap pixmap3(":/new/prefix1/resources/derece.png");
    ui->label_13->setPixmap(pixmap3);
    ui->label_13->setMask(pixmap3.mask());
    ui->label_13->setScaledContents(true);
    ui->label_13->show();

    QPixmap pixmap6(":/new/prefix1/resources/oksijen.png");
    ui->label_22->setPixmap(pixmap6);
    ui->label_22->setMask(pixmap6.mask());
    ui->label_22->setScaledContents(true);
    ui->label_22->show();


    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/new/prefix1/resources/ses.wav"));
    player->setVolume(100);

}

anaekran::~anaekran()
{

    delete ui;
}

void anaekran::veriiste() {
 QByteArray outByteArray,po;
    QModelIndexList list =ui->listView->selectionModel()->selectedIndexes();
    QStringList slist;
      foreach(const QModelIndex &index, list){
          slist.append( index.data(Qt::DisplayRole ).toString());
      }
     kimlik= slist[0];


      query = new QSqlQuery();
      QString nabiz,oksijen,hastasicaklik,odasicaklik,odanem,odaaydinlik;


          QString database_sec="";
          database_sec +="SELECT nabiz,oksijen,hastasicaklik,odasicaklik,odanem,odaaydinlik,ekgverisi,oksimetre,no FROM ";
          database_sec +=kimlik;
          database_sec +=" ORDER BY no;";
            qDebug() << "Veri cekiliyor..";
         if (query->exec(database_sec))
               {
               qDebug() << "Veri cekme Basarili";

             if (query->isActive()){
                 if (query->isSelect()){
                     if (query->last()){

                         nabiz = query->value(0).toString();
                         oksijen = query->value(1).toString();
                         hastasicaklik = query->value(2).toString();
                         odasicaklik = query->value(3).toString();
                         odanem = query->value(4).toString();
                         odaaydinlik = query->value(5).toString();

                 outByteArray = query->value( 6 ).toByteArray();
                 po=query->value( 7 ).toByteArray();
                     }
                 }
             }



           }
                   else
               {

                   qDebug() << query->lastError();
               }
   ui->label_19->setText(nabiz);
   ui->label_21->setText(oksijen);
   ui->label_33->setText(hastasicaklik);
   ui->label_27->setText(odanem);
 //  ui->label_26->setText(odaaydinlik);
   ui->label_29->setText(odasicaklik);



QVector<double> k(100),n(10000),y(1000);

for(int i =0;i<1000;i++) {
    y[i]=i;
}
           QString deneme = outByteArray;

           QStringList myStringList = deneme.split("!");

           std::cout<<"Splitting String \"A;B;C;D;E;F;G;H\" into\n"
                <<"QStringList with delimiter ';'...\n"
                <<"myStringList elements are :"<<std::endl;

           for(int index =0;index < myStringList.length();index++)

           {
               k[index] = myStringList.at(index).toFloat();


           }

           QString deneme2 = po;

           QStringList myStringList2 = deneme2.split("!");

           std::cout<<"Splitting String \"A;B;C;D;E;F;G;H\" into\n"
                <<"QStringList with delimiter ';'...\n"
                <<"myStringList elements are :"<<std::endl;

           for(int index =0;index < myStringList2.length();index++)

           {
               n[index] = myStringList2.at(index).toInt();


           }


/*
           ui->customplot->xAxis->grid()->setVisible(false);
           ui->customplot->yAxis->grid()->setVisible(false);
           ui->customplot->setBackground(QColor(0, 0, 0));
           ui->customplot->addGraph();
           ui->customplot->graph(0)->setData(y,k);
           ui->customplot->yAxis->setRange(0,100);
           ui->customplot->yAxis->setLabelColor(QColor(255, 00, 00));
           ui->customplot->yAxis->setTickLabelColor(QColor(255, 00, 00));
         ui->customplot->rescaleAxes(true);
           ui->customplot->graph(0)->setPen(QColor(0, 250, 0));
           ui->customplot->xAxis->setRange(0,500);
           ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
           ui->customplot->xAxis->setLabel("Pulse Oksimetre");
           ui->customplot->yAxis->setLabel("Pulse Oksimetre");
           ui->customplot->replot();

         */

           ui->customplot->xAxis->grid()->setVisible(true);
           ui->customplot->yAxis->grid()->setVisible(true);
         //ui->customplot->setBackground(QColor(0, 0, 0));
         ui->customplot->addGraph();
         ui->customplot->graph(0)->setData(y,k);
         ui->customplot->yAxis->setRange(-1,1);
         ui->customplot->yAxis->setLabelColor(QColor(255, 0, 0));

         ui->customplot->yAxis->setTickLabelColor(QColor(255, 00, 00));
         //ui->customplot->rescaleAxes(true);
         ui->customplot->graph(0)->setPen(QColor(250, 0, 0));
         ui->customplot->xAxis->setRange(0,1000);
         ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
         //ui->customplot->xAxis->setLabel("Olcum Sayisi");
         ui->customplot->yAxis->setLabel("Amplitute(mV)");
         ui->customplot->replot();


         ui->customplot_2->xAxis->grid()->setVisible(false);
         ui->customplot_2->yAxis->grid()->setVisible(false);
         //ui->customplot_2->setBackground(QColor(0, 0, 0));
         ui->customplot_2->addGraph();
         ui->customplot_2->graph(0)->setData(y,n);
         ui->customplot_2->yAxis->setRange(0,100);
         ui->customplot_2->yAxis->setLabelColor(QColor(255, 00, 00));
         ui->customplot_2->yAxis->setTickLabelColor(QColor(255, 00, 00));
         ui->customplot_2->rescaleAxes(true);
         ui->customplot_2->graph(0)->setPen(QColor(0, 250, 0));
         ui->customplot_2->xAxis->setRange(0,1000);
         ui->customplot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
         ui->customplot_2->xAxis->setLabel("Pulse Oksimetre");
         ui->customplot_2->yAxis->setLabel("Pulse Oksimetre");
         ui->customplot_2->replot();



deneme="";
deneme2="";
}

void anaekran::on_pushButton_3_clicked()
{


}

void anaekran::on_pushButton_4_clicked()
{
    timer->stop();
    query = new QSqlQuery();
liste = new QSqlQueryModel();
QString listekomutu = "SELECT tablename FROM pg_tables WHERE schemaname = 'public';";
bool ok =  query->exec( listekomutu);

 if(!ok){
    qDebug() << query->lastError().databaseText();
    // do something
}
 else
     qDebug() << "zaaxd";

liste->setQuery(*query);
ui->listView->setModel(liste);
qDebug() << liste->rowCount();
}


void anaekran::grafikciz() {

int olcum_sikligi= ui->horizontalSlider->value();
QVector<double> k(10100),n(101000),y(100000);

for(int i =0;i<1000;i++) {
    y[i]=i;
}
query = new QSqlQuery();
QVector<double> nabiz(100000), oksijen(100000),hastasicaklik(100000),sira(100000);
QVector<double> odasicaklik(100000), odanem(100000);
 QByteArray ba,po;

int nb;

   QString database_sec="";
   database_sec +="SELECT nabiz,oksijen,hastasicaklik,ekgverisi,oksimetre,no FROM ";
   database_sec +=kimlik;
 //  database_sec +=" ORDER BY no;";
     qDebug() << "Veri cekiliyor..";
  if (query->exec(database_sec))
        {
        qDebug() << "Veri cekme Basarili";
      nb = query->size();

    for( int i = 0; query->next(); i++ )
        {
nabiz[i] = query->value(0).toDouble();
oksijen[i] = query->value(1).toDouble();
hastasicaklik[i] = query->value(2).toDouble();
ba += query->value(3).toByteArray();
po += query->value(4).toByteArray();
sira[i] = query->value(5).toDouble();
    }
  }

            else
        {

            qDebug() << query->lastError();
        }


QString deneme = QString(ba);
ba.clear();

    QStringList myStringList = deneme.split("!");
    for(int index =0;index < myStringList.length();index++)

    {

        k[index] = myStringList.at(index).toFloat();
         //qDebug() << k[index];
    }

    QString deneme2 = QString(po);
    po.clear();

        QStringList myStringList2 = deneme2.split("!");
        for(int index =0;index < myStringList2.length();index++)

        {

             n[index] = myStringList2.at(index).toInt();

        }








    ui->customplot->xAxis->grid()->setVisible(true);
    ui->customplot->yAxis->grid()->setVisible(true);
  //ui->customplot->setBackground(QColor(0, 0, 0));
  ui->customplot->addGraph();
  ui->customplot->graph(0)->setData(y,k);
  ui->customplot->yAxis->setRange(-1,1);
  ui->customplot->yAxis->setLabelColor(QColor(255, 0, 0));

  ui->customplot->yAxis->setTickLabelColor(QColor(255, 00, 00));
  ui->customplot->rescaleAxes(true);
  ui->customplot->graph(0)->setPen(QColor(250, 0, 0));
  ui->customplot->xAxis->setRange(0,1000);
  ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  ui->customplot->xAxis->setLabel("Örnekleme Sayisi");
  ui->customplot->yAxis->setLabel("Amplitute(mV)");
  ui->customplot->replot();


  ui->customplot_2->xAxis->grid()->setVisible(false);
  ui->customplot_2->yAxis->grid()->setVisible(false);
  //ui->customplot_2->setBackground(QColor(0, 0, 0));
  ui->customplot_2->addGraph();
  ui->customplot_2->graph(0)->setData(y,n);
  ui->customplot_2->yAxis->setRange(0,100);
  ui->customplot_2->yAxis->setLabelColor(QColor(255, 00, 00));
  ui->customplot_2->yAxis->setTickLabelColor(QColor(255, 00, 00));
  ui->customplot_2->rescaleAxes(true);
  ui->customplot_2->graph(0)->setPen(QColor(0, 250, 0));
  ui->customplot_2->xAxis->setRange(0,1000);
  ui->customplot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  ui->customplot_2->xAxis->setLabel("Örnekleme Sayısı");
  ui->customplot_2->yAxis->setLabel("Sensor(Oxygen%)");
  ui->customplot_2->replot();

ui->customplot_3->xAxis->grid()->setVisible(false);
ui->customplot_3->yAxis->grid()->setVisible(false);
ui->customplot_3->setBackground(QColor(0, 0, 0));
ui->customplot_3->addGraph();
ui->customplot_3->graph(0)->setData(sira,hastasicaklik);
ui->customplot_3->yAxis->setRange(0,50);
ui->customplot_3->yAxis->setLabelColor(QColor(255, 00, 00));
ui->customplot_3->yAxis->setTickLabelColor(QColor(255, 00, 00));
ui->customplot_3->rescaleAxes(true);
ui->customplot_3->graph(0)->setPen(QColor(0, 0, 250));
ui->customplot_3->xAxis->setRange(0,olcum_sikligi);
ui->customplot_3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
ui->customplot_3->xAxis->setLabel("Olcum Sayisi");
ui->customplot_3->yAxis->setLabel("Hasta Sicaklik");
ui->customplot_3->replot();

deneme="";
deneme2="";




}

void anaekran::on_pushButton_22_clicked()
{

 query = new QSqlQuery();
timer->stop();





       QModelIndexList list =ui->listView->selectionModel()->selectedIndexes();
    QStringList slist;
      foreach(const QModelIndex &index, list){
          slist.append( index.data(Qt::DisplayRole ).toString());
      }
      qDebug() << slist.join(",");


     kimlik= slist[0];
     qDebug() << "Secilen kimlik :" + kimlik;


     QString tckimlikno,ad,soyad,tani,lokasyon,yas;
     int nb;

        QString database_sec="";
        database_sec +="SELECT tckimlikno,ad,soyad,yas,tani,lokasyon,no FROM ";
        database_sec +=kimlik;
        database_sec +=" ORDER BY no;";
          qDebug() << "Veri cekiliyor..";
          if (query->exec(database_sec))
                {
                qDebug() << "Veri cekme Basarili";

              if (query->isActive()){
                  if (query->isSelect()){
                      if (query->last()){

                          tckimlikno = query->value(0).toString();
                          ad = query->value(1).toString();
                          soyad = query->value(2).toString();
                          yas = query->value(3).toString();
                          tani = query->value(4).toString();
                          lokasyon = query->value(5).toString();
                      }
                  }
              }



            }
                    else
                {

                    qDebug() << query->lastError();
                }
    ui->label_8->setText(ad);
    ui->label_6->setText(soyad);
    ui->label_7->setText(yas);
    ui->label_11->setText(tani);
    ui->label_9->setText(lokasyon);

    // Get image data back from database
    if( !query->exec( "SELECT imagedata from imgTable" ))
        qDebug() << "Error getting image from table:\n" << query->lastError();
    query->first();
    QByteArray outByteArray = query->value( 0 ).toByteArray();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray );
    ui->label->setPixmap(outPixmap);
    ui->label->show();


grafikciz();

}

void anaekran::on_horizontalSlider_valueChanged(int value)
{

    ui->label_31->setText(QString::number(value));
}



void anaekran::on_pushButton_clicked()
{

}

void anaekran::on_pushButton_28_clicked()
{

}

void anaekran::on_pushButton_5_clicked()
{
    timer->start();
    timer2->stop();
}

void anaekran::on_pushButton_25_clicked()
{
    /*
    soket = new QTcpSocket();
    soket->connectToHost("192.168.1.5",80);
    soket->waitForConnected(30000);
    soket->write("Hello/hello");
    */
  query = new QSqlQuery();
       QString database_sec="";
       database_sec +="SELECT ip,no FROM ";
       database_sec +=kimlik;
       database_sec +=" ORDER BY no;";
         qDebug() << "Veri cekiliyor..";
         if (query->exec(database_sec))
               {
               qDebug() << "Veri cekme Basarili";

             if (query->isActive()){
                 if (query->isSelect()){
                     if (query->last()){
                        client_ip = query->value(0).toString();
                     }
                 }
             }



           }
                   else
               {
qDebug() << "Veri cekiliyorrr..";
                   qDebug() << query->lastError();
               }



        dialog  = new Dialog;
             dialog->setWindowTitle("Oda Kontrol Arayüzü");
             dialog->show();


dialog->verial(client_ip);
}

void anaekran::veriyolla() {


}
