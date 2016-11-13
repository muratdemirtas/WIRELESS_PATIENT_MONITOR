#include "anaekran.h"
#include "ui_anaekran.h"
#include <QString>
#include <QTimer>





QString hastalar[] = {"Murat Demirtaş","Orcun Tari","Murat Uz","Reşat Bozkurt"};
 int sayac,sayac2=0;
 QString client_no,client_ad,client_soyad;
QString TANI,AD,SOYAD,YAS,IKINCIAD,ODA,ip,port;
QString HASTADERECE,NABIZ,HAVADERECE,HAVA,OKSIJEN,NEM;
anaekran::anaekran(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::anaekran)
{
    ui->setupUi(this);
    soket = new QTcpSocket();
    QMainWindow::maximumSize();

    timer  =new QTimer(this);
        timer->setInterval(1000);
        connect(timer,SIGNAL(timeout()),SLOT(veriiste()));
ui->pushButton_3->hide();



menajer = new QNetworkAccessManager(this);
connect(menajer,SIGNAL(finished(QNetworkReply*)),this,SLOT(deneme()));
QNetworkRequest request(QUrl("http://scontent-cdg2-1.xx.fbcdn.net/hphotos-xlf1/v/t1.0-9/12705452_1501898083453174_4532869115513549444_n.jpg?oh=78f9cf6379dad4594ca55b682dea9794&oe=5751481F"));
reply = menajer->get(request);





//"logo.png"


    QPixmap pixmap(":/resources/logo1.png");
    ui->label->setPixmap(pixmap);
    ui->label->setMask(pixmap.mask());
    ui->label->setScaledContents(true);
    ui->label->show();


//:/new/prefix1/resources/ses.wav


    player = new QMediaPlayer;

    player->setMedia(QUrl("qrc:/new/prefix1/resources/ses.wav"));
    player->setVolume(100);

    connect(soket,SIGNAL(readyRead()),SLOT(verioku()));

    QPixmap pixmap2(":/resources/kalp.png");
    ui->label_12->setPixmap(pixmap2);
    ui->label_12->setMask(pixmap2.mask());
    ui->label_12->setScaledContents(true);
    ui->label_12->show();

    QPixmap pixmap3(":/resources/derece.png");
    ui->label_29->setPixmap(pixmap3);
    ui->label_29->setMask(pixmap3.mask());
    ui->label_29->setScaledContents(true);
    ui->label_29->show();

    QPixmap pixmap4(":/resources/oksijen.png");
    ui->label_14->setPixmap(pixmap4);
    ui->label_14->setMask(pixmap4.mask());
    ui->label_14->setScaledContents(true);
    ui->label_14->show();

    QPixmap pixmap5(":/resources/derece.png");
    ui->label_13->setPixmap(pixmap5);
    ui->label_13->setMask(pixmap5.mask());
    ui->label_13->setScaledContents(true);
    ui->label_13->show();

    QPixmap pixmap6(":/resources/oksijen.png");
    ui->label_22->setPixmap(pixmap6);
    ui->label_22->setMask(pixmap6.mask());
    ui->label_22->setScaledContents(true);
    ui->label_22->show();

    QPixmap pixmap7(":/resources/nem.png");
    ui->label_30->setPixmap(pixmap7);
    ui->label_30->setMask(pixmap7.mask());
    ui->label_30->setScaledContents(true);
    ui->label_30->show();






}

void anaekran::veriiste() {


soket->write("s");
   soket->flush();

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

    sayac2++;
    if(sayac2%2==1)
     ui->label_12->show();
    else if(sayac2%2==0)

        ui->label_12->hide();


    QByteArray gelen_veri = soket->readAll();
    soket->flush();
   // soket->waitForReadyRead(3000);
    qDebug() << gelen_veri;
    if(gelen_veri[0]=='*') {
        QString deneme=gelen_veri;
        QStringList pieces = deneme.split( "*" );
        OKSIJEN = pieces.value( pieces.length() - 6 );
        ui->label_15->setText(QString("%"+OKSIJEN));
        NABIZ = pieces.value( pieces.length() -3 );
        ui->label_19->setText(QString(NABIZ +" BPM"));
        HASTADERECE = pieces.value( pieces.length() - 4 );
        ui->label_23->setText(QString(HASTADERECE+" °C"));
        HAVA = pieces.value( pieces.length() - 2 );
        ui->label_26->setText(QString("%"+HAVA));
        NEM= pieces.value( pieces.length() - 1 );
        ui->label_27->setText(QString("%"+NEM));
        HAVADERECE= pieces.value( pieces.length() - 1 );
        ui->label_28->setText(QString( HAVADERECE+ " °C"));
        gelen_veri="";
        deneme="";
 }

    if(gelen_veri[0]=='/') {
        QString deneme=gelen_veri;
        QStringList pieces = deneme.split( "/" );
        /*
        AD = pieces.value( pieces.length() - 6 );
        IKINCIAD =pieces.value( pieces.length() -5 );
        SOYAD = pieces.value( pieces.length() -4 );
        YAS = pieces.value( pieces.length() - 3 );
        TANI = pieces.value( pieces.length() - 2 );
        ODA = pieces.value( pieces.length() - 1 );
*/
      IKINCIAD =pieces.value( pieces.length() -5 );
        if(IKINCIAD=="NULL") {
             qDebug() << "İkinci Ad Yok";
             AD = pieces.value( pieces.length() - 6 );
             ui->label_8->setText(QString(AD));
             SOYAD = pieces.value( pieces.length() -4 );
             ui->label_6->setText(QString(SOYAD));
             YAS = pieces.value( pieces.length() - 3 );
             ui->label_7->setText(QString(YAS));
             TANI = pieces.value( pieces.length() - 2 );
             ui->label_11->setText(QString(TANI));
             ODA= pieces.value( pieces.length() - 1 );
             ui->label_9->setText(QString(ODA));
        }

        else {
            qDebug() << "İkinci Ad VAR";
            AD = pieces.value( pieces.length() - 5 );
            IKINCIAD =pieces.value( pieces.length() -4 );
            SOYAD = pieces.value( pieces.length() -3 );
            YAS = pieces.value( pieces.length() - 2 );
            TANI = pieces.value( pieces.length() - 1 );
             ODA= pieces.value( pieces.length() - 0 );
         }
        qDebug() <<  AD +IKINCIAD+ SOYAD + YAS + TANI +ODA ;
        gelen_veri="";
    }

    else if (gelen_veri[0]='+') {
             QString clientler=gelen_veri;
             QStringList pieces =  clientler.split( "+" );
             client_no = pieces.value( pieces.length() - 3 );
             client_ad = pieces.value( pieces.length() -2 );
             client_soyad  = pieces.value( pieces.length() - 1 );

         ui->pushButton_3->show();
ui->pushButton_3->setText(client_ad+client_soyad);

}

    player->play();


}




void anaekran::on_pushButton_clicked()
{
     ip = ui->lineEdit->text();
     port =ui->lineEdit_2->text();
 qDebug() << "ip" + port;




ui->pushButton->setText("Bagli Durumda");
ui->pushButton->setEnabled(false);


    soket->connectToHost(ip,port.toInt());
    if(!soket->waitForConnected(1000))
        {
            qDebug() << "Error: " << soket->errorString();
            ui->pushButton->setText(soket->errorString());
             ui->pushButton->setEnabled(true);
        }
    soket->write("H");
    soket->flush();
}




void anaekran::pingkontrol() {
    qDebug() << "timer kesmesi";
    ui->pushButton->setEnabled(true);ui->pushButton->setText("BAGLANTI KOPTU!");
  soket->close();


}



void anaekran::on_pushButton_6_clicked()
{
    QString link = "https://thingspeak.com/channels/101275";
    QDesktopServices::openUrl(QUrl(link));

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
          ui->pushButton_3->hide();
}
