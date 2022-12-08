#include "Salle.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QMessageBox>
#include <QChart>
#include <QtCharts>
#include <QIntValidator>
#include <QPieSeries>
#include <QChartView>
#include <QGraphicsView>

Salle::Salle()
{
Num = 0;
Type = "";
Inventaire = 0;
Surface = 0;
Emplacement = "";
Permission = "";
descpanne="";
}


Salle::Salle(int Num, QString Type, int Inventaire, int Surface, QString Emplacement, QString Permission,QString descpanne)
{
    this->Num=Num;
    this->Type=Type;
    this->Inventaire=Inventaire;
    this->Surface=Surface;
    this->Emplacement=Emplacement;
    this->Permission=Permission;
    this->descpanne=descpanne;
}

bool Salle::ajouter()
{
    QSqlQuery query;
    QString Num_string= QString::number(Num);
    QString Inventaire_string= QString::number(Inventaire);
    QString Surface_string= QString::number(Surface);
    if(query.exec("select * from Salle where Num='"+Num_string+"'"))
    { int count=0;
        while(query.next())
            count++;
        if (count==0)
       {


//prepare() prend la requète en paramètre pour la préparer à l'éxécution.

    query.prepare("INSERT INTO Salle (Num, Type, Inventaire, Surface, Emplacement, Permission,descpanne)" "VALUES(:Num, :Type, :Inventaire, :Surface, :Emplacement, :Permission,:descpanne)");

// Création des variables liées
    query.bindValue(":Num",Num_string);
    query.bindValue(":Type",Type);
    query.bindValue(":Inventaire",Inventaire_string);
    query.bindValue(":Surface",Surface_string);
    query.bindValue(":Emplacement",Emplacement);
    query.bindValue(":Permission",Permission);
    query.bindValue(":Desc panne",descpanne);
    } else
            QMessageBox::critical(nullptr, QObject::tr(" not OK"),
                                           QObject::tr("le Numéro de Salle existe deja .\n"
                                                       "click cancel to exit."),QMessageBox::Cancel);}

    return query.exec(); //exec() envoie la requète pour l'exécuter

}



bool Salle::supprimer(int Num)
{
    QSqlQuery query;
    QString res=QString::number(Num);
    query.prepare("Delete from Salle where Num= :Num");
    query.bindValue(":Num",res);
    return query.exec();
}



QSqlQueryModel * Salle::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Salle");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Num"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Type"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Inventaire"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Surface"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Emplacement"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Permission"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("descpanne"));

    return model;
}

bool Salle::modifier(int Num,QString Type,int Inventaire,int Surface,QString Emplacement,QString Permission,QString descpanne)
{
    QSqlQuery query;
    QString Num_string=QString::number(Num);
    QString Inventaire_string=QString::number(Inventaire);
    QString Surface_string=QString::number(Surface);

          query.prepare("update Salle set Type=:Type,Inventaire=:Inventaire,Surface=:Surface,Emplacement=:Emplacement,Permission=:Permission,descpanne=:descpanne where Num=:Num");
          query.bindValue(":Num",Num_string);
          query.bindValue(":Type",Type);
          query.bindValue(":Inventaire",Inventaire_string);
          query.bindValue(":Surface",Surface_string);
          query.bindValue(":Emplacement",Emplacement);
          query.bindValue(":Permission",Permission);
          query.bindValue(":descpanne",descpanne);
          return query.exec();
}

QSqlQueryModel * Salle::trier_Num()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Salle ORDER BY Num ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Num"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("Type"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("Inventaire"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("Surface"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("Emplacement"));
          model->setHeaderData(5,Qt::Horizontal,QObject::tr("Permission"));
          model->setHeaderData(6,Qt::Horizontal,QObject::tr("descpanne"));



    return model;
}

QSqlQueryModel * Salle::trier_Inventaire()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Salle ORDER BY Inventaire ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Num"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("Type"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("Inventaire"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("Surface"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("Emplacement"));
          model->setHeaderData(5,Qt::Horizontal,QObject::tr("Permission"));
          model->setHeaderData(6,Qt::Horizontal,QObject::tr("descpanne"));



    return model;
}

QSqlQueryModel * Salle::trier_Surface()
{
    QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM Salle ORDER BY Surface ");
          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Num"));
          model->setHeaderData(1,Qt::Horizontal,QObject::tr("Type"));
          model->setHeaderData(2,Qt::Horizontal,QObject::tr("Inventaire"));
          model->setHeaderData(3,Qt::Horizontal,QObject::tr("Surface"));
          model->setHeaderData(4,Qt::Horizontal,QObject::tr("Emplacement"));
          model->setHeaderData(5,Qt::Horizontal,QObject::tr("Permission"));
          model->setHeaderData(6,Qt::Horizontal,QObject::tr("descpanne"));



    return model;
}

QSqlQueryModel* Salle::rechercherNum(QString NNum)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from Salle where Num ='"+NNum+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Inventaire"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Surface"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Emplacement"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Permission"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("descpanne"));


            return model;
    }

QSqlQueryModel* Salle::rechercherType(QString Type)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from Salle where Type ='"+Type+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Inventaire"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Surface"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Emplacement"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Permission"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("descpanne"));


            return model;
    }

QSqlQueryModel* Salle::rechercherEmplacement(QString Emplacement)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from Salle where Emplacement ='"+Emplacement+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Num"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("Inventaire"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Surface"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("Emplacement"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Permission"));
            model->setHeaderData(6,Qt::Horizontal,QObject::tr("descpanne"));


            return model;
    }


QChartView *Salle::stat_type()
  {
      int t1=0;
      int t2=0;
      int t3=0;
      int t4=0;

      QSqlQuery query;
      query.prepare("select * from Salle where TYPE='Type1'");
      query.exec();

      while(query.next())
          t1++;

      query.prepare("select * from Salle where TYPE='Type2'");
      query.exec();

      while(query.next())
          t2++;

      query.prepare("select * from Salle where TYPE='Type3'");
      query.exec();

      while(query.next())
          t3++;

      query.prepare("select * from Salle where TYPE='Type4'");
      query.exec();

      while(query.next())
          t4++;

      qDebug() << t1<< t2 << t3 << t4 ;

      QPieSeries *series = new QPieSeries();
          series->append("Type1", t1);
          series->append("Type2", t2);
          series->append("Type3", t3);
          series->append("Type4", t4);

          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#4C6293");
          slice->setLabel("Type 1 "+QString("%1%").arg(100*slice->percentage(),1,'f',1));
          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#E4F0FF");
          slice2->setLabel("Type 2 "+QString("%1%").arg(100*slice2->percentage(),1,'f',1));
          QPieSlice *slice3 = series->slices().at(2);
          slice3->setColor("#7D83D6");
          slice3->setLabel("Type 3 "+QString("%1%").arg(100*slice3->percentage(),1,'f',1));
          QPieSlice *slice4 = series->slices().at(3);
          slice4->setColor("#6495ed");
          slice4->setLabel("Type 4 "+QString("%1%").arg(100*slice4->percentage(),1,'f',1));

          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique du type");


          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
          chartView->chart()->setAnimationOptions(QChart::AllAnimations);
          chartView->chart()->legend()->hide();
          chartView->resize(1000,500);
          return chartView;
}

