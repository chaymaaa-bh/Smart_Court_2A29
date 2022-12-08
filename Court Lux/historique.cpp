#include "historique.h"
#include <QDateTime>
#include <QSqlQuery>
#include "mainwindow.h"
Historique::Historique()
{

}
void Historique::save(QString id_string, QString nom, QString type, QString horraire, QString avancement, QString decision, QString num, QString action)
{
    //QDate date;
    QDateTime date = QDateTime::currentDateTime();
    QString dates=date.toString();
    QFile file ("‪C:/Users/souam/Downloads/Chayma/Historique.txt");

     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";
     QTextStream out(&file);
     out << " Id:"+id_string+"    Nom: "+nom+"    Type: "+type+"    Horaire: "+horraire+"    Avancement: "+avancement+"    Decision: "+decision+"  Num: "+num+"    Action: "+action+"    Date de l'action: "+dates << " \n";
}


QString Historique::load()
{   tmp="";
        QFile file ("‪C:/Users/souam/Downloads/Chayma/Historique.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);
    int i=0;
            QString color="#F2D9EC";
   while (!in.atEnd()) {
       switch (i) {
                  case 0:
                  color="#E4D6FF";

                  break;
                  case 1:
                      color="#AFC1EF";
                  break;
                  case 2:
                      color="#73AED8";
                  break;
                  case 3:
                      color="#2D9AB6";
                      break;
                  }

         QString myString = in.readLine();
         tmp+="<font color="+color+">"+myString+"\n<br><br> <font>";
         i++;
                     if(i==4)
                         i=0;
   }
   return tmp;
}





