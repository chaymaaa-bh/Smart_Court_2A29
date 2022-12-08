#include "chat.h"
#include "ui_chat.h"


chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{

    QHostAddress me(get_ip());
    ui->setupUi(this);
    employeSocket=new QUdpSocket(this);
    employeSocketc=new QUdpSocket(this);
    employeSocketc->bind(me, 7000);
    connect(employeSocketc,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}

chat::~chat()
{
    delete ui;
}

void chat::on_sendButton_clicked()
{
    QString word=ui->lineEdit->text();
    ui->textBrowser->append(word);
    QByteArray buffer;
    buffer.resize(employeSocket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    buffer=word.toUtf8();
    employeSocketc->writeDatagram(buffer.data(), QHostAddress::Broadcast, 8001 );
    ui->lineEdit->clear();
}
void chat::readPendingDatagrams()
{
    while (employeSocketc->hasPendingDatagrams()) {
        QByteArray buffer;
        buffer.resize(employeSocketc->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        employeSocketc->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
        ui->textBrowser->append(buffer.data());

    }

}

QString chat::get_ip()
{
    QProcess process;
    process.start("ipconfig");
    process.waitForFinished(-1); // will wait forever until finished
    QString output = process.readAllStandardOutput();
    QString errors = process.readAllStandardError();
    int pos=output.toStdString().find("Wi-Fi");
    QRegularExpression ip_regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]+)");
    QRegularExpressionMatch ip_match=ip_regex.match(output.mid(pos+50,220));
    qDebug() <<ip_match.captured(0);
    return ip_match.captured(0);
}

void chat::on_connect_udp_clicked()
{
//  QHostAddress me(ui->lineEdit_ip->text());
//    clientSocket=new QUdpSocket(this);
//    clientSocketc=new QUdpSocket(this);
//    clientSocketc->bind(me, 7000);
////    connect(clientSocketc,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()));
}
