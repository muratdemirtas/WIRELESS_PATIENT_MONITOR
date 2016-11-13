#include "anaekran.h"
#include "ui_anaekran.h"
#include <QString>
#include <QTimer>

#include <QUrl>
#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QtGlobal>
QString hasta,kimlik;
QByteArray hasta_verisi;
bool anlik_veri=false,yenibaglanti=false,yeniveritabaniacildi=false;
QString client_ip,gun,zaman,tckimlikno,ad,soyad,yas,tani,lokasyon,nabiz,tansiyon,oksijen,hastasicaklik,odasicaklik,odanem,odaaydinlik;
QString hastalar[] = {"Murat Demirtaş","Orcun Tari","Murat Uz","Reşat Bozkurt"};
QString istek;
int sayac1,sayac2;
anaekran::anaekran(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::anaekran)
{
    ui->setupUi(this);
    qDebug() << "Sunucu/is parcacigi : Veri tabani olusturuluyor";
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    QString ip = ui->textEdit_2->toPlainText();

    db.setHostName(ip);
    db.setDatabaseName("onlinehastalar");
    db.setPort(3306);
    db.setUserName("hasta");
    db.setPassword("hasta");
    if (!db.open()) {
        qDebug() << "Database error occurred";
        ui->label_33->setText("BASARISIZ BAGLANTI");
        }
    else {

         qDebug() << "Connected!";
          ui->label_33->setText("BASARILI BAGLANTI");
    }

query = new QSqlQuery();
    QMainWindow::maximumSize();
    timer  =new QTimer(this);
    timer2 = new QTimer(this);
        timer->setInterval(1000);
         timer2->setInterval(3000);
        connect(timer,SIGNAL(timeout()),SLOT(veriiste()));
        connect(timer2,SIGNAL(timeout()),SLOT(grafikciz()));
    soket = new QTcpSocket();
menajer = new QNetworkAccessManager(this);
connect(menajer,SIGNAL(finished(QNetworkReply*)),this,SLOT(deneme()));
QNetworkRequest request(QUrl("http://scontent-cdg2-1.xx.fbcdn.net/hphotos-xlf1/v/t1.0-9/12705452_1501898083453174_4532869115513549444_n.jpg?oh=78f9cf6379dad4594ca55b682dea9794&oe=5751481F"));
reply = menajer->get(request);

    QPixmap pixmap(":/new/prefix1/resources/logo.png");
    ui->label->setPixmap(pixmap);
    ui->label->setMask(pixmap.mask());
    ui->label->setScaledContents(true);
    ui->label->show();

    QPixmap pixmap2(":/new/prefix1/resources/kalp.png");
    ui->label_12->setPixmap(pixmap2);
    ui->label_12->setMask(pixmap2.mask());
    ui->label_12->setScaledContents(true);
    ui->label_12->show();

    QPixmap pixmap3(":/new/prefix1/resources/derece.png");
    ui->label_29->setPixmap(pixmap3);
    ui->label_29->setMask(pixmap3.mask());
    ui->label_29->setScaledContents(true);
    ui->label_29->show();

    QPixmap pixmap4(":/new/prefix1/resources/oksijen.png");
    ui->label_14->setPixmap(pixmap4);
    ui->label_14->setMask(pixmap4.mask());
    ui->label_14->setScaledContents(true);
    ui->label_14->show();

    QPixmap pixmap5(":/new/prefix1/resources/derece.png");
    ui->label_13->setPixmap(pixmap5);
    ui->label_13->setMask(pixmap5.mask());
    ui->label_13->setScaledContents(true);
    ui->label_13->show();

    QPixmap pixmap6(":/new/prefix1/resources/oksijen.png");
    ui->label_22->setPixmap(pixmap6);
    ui->label_22->setMask(pixmap6.mask());
    ui->label_22->setScaledContents(true);
    ui->label_22->show();

    QPixmap pixmap7(":/new/prefix1/resources/nem.png");
    ui->label_30->setPixmap(pixmap7);
    ui->label_30->setMask(pixmap7.mask());
    ui->label_30->setScaledContents(true);
    ui->label_30->show();

ui->pushButton_5->hide();

    player = new QMediaPlayer;
   player->setMedia(QUrl("qrc:/new/prefix1/resources/ses.wav"));
    player->setVolume(100);
    connect(soket,SIGNAL(readyRead()),SLOT(verioku()));
}

anaekran::~anaekran()
{
    soket->close();
    delete ui;
}

void anaekran::deneme() {
  qDebug() << "İkinci Ad VAR";

    if (reply->error() != QNetworkReply::NoError) {
    qDebug() << "Error in" << reply->url() << ":" << reply->errorString();
    return;

}
}

void anaekran::verioku() {
    QByteArray client_verisi = soket->readAll();

    sayac2++;
    if(sayac2%2==1)
     ui->label_12->show();
    else if(sayac2%2==0)

        ui->label_12->hide();

    qDebug() << client_verisi;
    if(client_verisi[0]=='*') {
        hasta_verisi=client_verisi;
        gun = QDate::currentDate().toString();
        zaman = QTime::currentTime().toString();
        QString deneme=client_verisi;
        QStringList pieces = deneme.split( "*" );
        tckimlikno=pieces.value( pieces.length() - 14);
        ad=pieces.value( pieces.length() - 13);
        ui->label_8->setText(ad);
        soyad=pieces.value( pieces.length() - 12);
        ui->label_6->setText(soyad);
        yas=pieces.value( pieces.length() - 11);
        ui->label_7->setText(yas);
        tani=pieces.value( pieces.length() - 10);
        ui->label_11->setText(tani);
        lokasyon=pieces.value( pieces.length() - 9);
        ui->label_9->setText(lokasyon);
        tansiyon=pieces.value( pieces.length() - 8);
        nabiz=pieces.value( pieces.length() - 7);
        ui->label_19->setText(nabiz+"BPM");
        oksijen=pieces.value( pieces.length() - 6);
        ui->label_15->setText("%"+oksijen);
        hastasicaklik=pieces.value( pieces.length() - 5);
        ui->label_23->setText(hastasicaklik+"C°");
        odasicaklik=pieces.value( pieces.length() - 4);
         ui->label_26->setText(odasicaklik+"C°");
        odanem=pieces.value( pieces.length() - 3);
         ui->label_28->setText("%"+odanem);
        odaaydinlik=pieces.value((pieces.length()-2));
         ui->label_27->setText(odaaydinlik);


        deneme="";


}

    player->play();



}




void anaekran::on_pushButton_clicked()
{

 QByteArray bytes = reply->readAll();
 QImage img(10, 10, QImage::Format_Indexed8);
 img.loadFromData(bytes);
 ui->label->setScaledContents(true);
 ui->label->setPixmap(QPixmap::fromImage(img));
   ui->label->show();

connect(timer,SIGNAL(timeout()),SLOT(pingkontrol()));
ui->pushButton->setText("Bagli Durumda");
ui->pushButton->setEnabled(false);

QString ip = ui->textEdit_2->toPlainText();
QString port = ui->textEdit->toPlainText();
qDebug() << ip +port;
    soket->connectToHost(ip,port.toInt());
    if(!soket->waitForConnected(1000))
        {
            qDebug() << "Error: " << soket->errorString();
            ui->pushButton->setText(soket->errorString());
             ui->pushButton->setEnabled(true);
        }

}

void anaekran::pingkontrol() {

}


void anaekran::on_pushButton_3_clicked()
{


    soket->write("h");
    soket->flush();
        timer->start();

        QByteArray bytes = reply->readAll();
        QImage img(10, 10, QImage::Format_Indexed8);
        img.loadFromData(bytes);
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap::fromImage(img));
          ui->label->show();

}

void anaekran::veriiste() {
 QString istek_komutu;
 istek_komutu += "-";
 istek_komutu += istek;



soket->write(istek_komutu.toUtf8().data());
   soket->flush();
istek_komutu="";
}

void anaekran::on_pushButton_4_clicked()
{

liste = new QSqlQueryModel();
query->prepare("show tables from onlinehastalar");

if( !query->exec() )
  qDebug() << "Sunucu/is parcacigi : Veriler Veritabanina aktarilirken Hata Olustu:";
else
  qDebug() << "Sunucu/is parcacigi : Veriler Veritabanina Basari ile aktarildi";



liste->setQuery(*query);
ui->listView->setModel(liste);
qDebug() << liste->rowCount();




}

void anaekran::on_pushButton_8_clicked()
{
   QModelIndexList list =ui->listView->selectionModel()->selectedIndexes();


    QStringList slist;
      foreach(const QModelIndex &index, list){
          slist.append( index.data(Qt::DisplayRole ).toString());
      }
      qDebug() << slist.join(",");


      istek = slist[0];

      timer->start();

}

void anaekran::grafikciz() {

int olcum_sikligi= ui->horizontalSlider->value();

query = new QSqlQuery();
QVector<double> nabiz(100000), oksijen(100000),hastasicaklik(100000),sira(100000);
QVector<double> odasicaklik(100000), odanem(100000),odaaydinlik(100000);
int nb;

   QString database_sec="";
   database_sec +="SELECT nabiz,oksijen,hastasicaklik,odasicaklik,odanem,odaaydinlik,no FROM ";
   database_sec +=kimlik;
  if (query->exec(database_sec))
        {
      nb = query->size();

    for( int i = 0; query->next(); i++ )
        {
nabiz[i] = query->value(0).toDouble();
oksijen[i] = query->value(1).toDouble();
hastasicaklik[i] = query->value(2).toDouble();
odasicaklik[i] = query->value(3).toDouble();
odanem[i] = query->value(4).toDouble();
odaaydinlik[i] = query->value(5).toDouble();
sira[i] = query->value(6).toDouble();

      }

    }
            else
        {

            qDebug() << query->lastError();
        }


  ui->customplot->addGraph();
  ui->customplot->graph(0)->setData(sira,nabiz);
  ui->customplot->yAxis->setRange(0,250);
  ui->customplot->xAxis->setRange(0,olcum_sikligi);

  ui->customplot->xAxis->setLabel("Olcum Sayisi");
  ui->customplot->yAxis->setLabel("Kalp Atımı");
  ui->customplot->replot();

  ui->customplot_2->addGraph();
  ui->customplot_2->graph(0)->setData(sira,oksijen);
  ui->customplot_2->yAxis->setRange(0,1000);
  ui->customplot_2->xAxis->setRange(0,olcum_sikligi);

  ui->customplot_2->xAxis->setLabel("Olcum Sayisi");
  ui->customplot_2->yAxis->setLabel("Pulse Oksimetre");
  ui->customplot_2->replot();


  ui->customplot_3->addGraph();
  ui->customplot_3->graph(0)->setData(sira,hastasicaklik);
  ui->customplot_3->yAxis->setRange(0,50);
  ui->customplot_3->xAxis->setRange(0,olcum_sikligi);

  ui->customplot_3->xAxis->setLabel("Olcum Sayisi");
  ui->customplot_3->yAxis->setLabel("Hasta Sicaklik");
  ui->customplot_3->replot();



  ui->customplot_4->addGraph();
  ui->customplot_4->graph(0)->setData(sira,odasicaklik);
  ui->customplot_4->yAxis->setRange(0,80);
  ui->customplot_4->xAxis->setRange(0,olcum_sikligi);

  ui->customplot_4->xAxis->setLabel("Olcum Sayisi");
  ui->customplot_4->yAxis->setLabel("Oda Sicaklik");
  ui->customplot_4->replot();

  ui->customplot_5->addGraph();
  ui->customplot_5->graph(0)->setData(sira,odanem);
  ui->customplot_5->yAxis->setRange(0,100);
  ui->customplot_5->xAxis->setRange(0,olcum_sikligi);

  ui->customplot_5->xAxis->setLabel("Olcum Sayisi");
  ui->customplot_5->yAxis->setLabel("Oda Nemi");
  ui->customplot_5->replot();

  ui->customplot_6->addGraph();
  ui->customplot_6->graph(0)->setData(sira,odaaydinlik);
  ui->customplot_6->yAxis->setRange(0,100);
  ui->customplot_6->xAxis->setRange(0,olcum_sikligi);

  ui->customplot_6->xAxis->setLabel("Olcum Sayisi");
  ui->customplot_6->yAxis->setLabel("Aydinlik Seviyesi");
  ui->customplot_6->replot();




}

void anaekran::on_pushButton_22_clicked()
{

timer2->start();
       QModelIndexList list =ui->listView->selectionModel()->selectedIndexes();
    QStringList slist;
      foreach(const QModelIndex &index, list){
          slist.append( index.data(Qt::DisplayRole ).toString());
      }
      qDebug() << slist.join(",");


     kimlik= slist[0];

}

void anaekran::on_horizontalSlider_valueChanged(int value)
{

    ui->label_31->setText(QString::number(value));
}
