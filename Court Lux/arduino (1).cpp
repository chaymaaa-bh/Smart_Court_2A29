#include "arduino.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QObject>
#include <QDebug>

Arduino::Arduino()
{
   data="";
   arduino_port_name="";
   arduino_is_available=false;
   Serial=new QSerialPort ;
}
QString Arduino::getarduino_port_name()
{

    return arduino_port_name ;

}

QSerialPort *Arduino::getserial()
{

    return Serial;
}

int Arduino::connect_arduino()
{
    foreach (const QSerialPortInfo &serial_port_info,QSerialPortInfo::availablePorts())
    {
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier())
        {
            if (serial_port_info.vendorIdentifier()== arduino_uno_vendor_id && serial_port_info.productIdentifier()== arduino_uno_producy_id)
            {
                arduino_is_available=true ;
                arduino_port_name=serial_port_info.portName();

            }
        }

    }
    qDebug() <<"arduino_port_name is :" <<arduino_port_name ;
    if(arduino_is_available)
    {
        Serial->setPortName(arduino_port_name);
        if(Serial->open(QSerialPort::ReadWrite))
        {
            Serial->setBaudRate(QSerialPort::Baud9600);//débit : 9600bits/s
            Serial->setDataBits(QSerialPort::Data8);//Longeur de donnée : 8bits
            Serial->setParity(QSerialPort::NoParity);//1 bit de parite optionnel
            Serial->setStopBits(QSerialPort::OneStop);//Nombre de bit de stop 1
            Serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0 ;

        }
        return 1;

    }
    return -1;

}
int Arduino::close_arduino()
{

    if(Serial->isOpen())
    {
        Serial->close();
        return 0;
    }
    return 1;

}

QByteArray Arduino::read_from_arduino()
{

    if (Serial->isReadable()){

        data=Serial->readAll();//récuperer les données réçues
       return data;
    }


}

int Arduino::write_to_arduino(QByteArray d)
{
    if (Serial->isWritable())
    {
        Serial->write(d);

    }
    else {qDebug()<<"couldn't write to Arduino !";}
}

QByteArray Arduino::cherchercode(QString key){

          QSqlDatabase bd = QSqlDatabase::database();

     // qDebug()<<"ide="<<id;
              QSqlQuery query;
              query.prepare("SELECT * FROM AFFAIRE WHERE id =:id");
       query.bindValue(":id",key);

              query.exec();
              if (query.next())
              {

                key=query.value(0).toString();
                  //qDebug()<<"code="<<nom;
                   return "1";
              }
              else {
                  return "0";
              }

  }

QByteArray Arduino::getdata()
{
    return data;
}

