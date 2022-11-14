#include "affaires_judiciaires.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QTextDocument>
#include <QPrinter>

Affaires_judiciaires::Affaires_judiciaires()
{
id = 0;
Nom = "";
Type = "";
Horraire = "";
Avancement = "";
Faits = "";
Decision = "";
}


Affaires_judiciaires::Affaires_judiciaires(int id, QString Nom, QString Type, QString Horraire, QString Avancement, QString Faits, QString Decision)
{
    this->id = id;
    this->Nom = Nom;
    this->Type = Type;
    this->Horraire = Horraire;
    this->Avancement = Avancement;
    this->Faits = Faits;
    this->Decision = Decision;
}

int Affaires_judiciaires::getid(){return id;}
QString Affaires_judiciaires::getNom(){return Nom;}
QString Affaires_judiciaires::getType(){return Type;}
QString Affaires_judiciaires::getHorraire(){return Horraire;}
QString Affaires_judiciaires::getAvancement(){return Avancement;}
QString Affaires_judiciaires::getFaits(){return Faits;}
QString Affaires_judiciaires::getDecision(){return Decision;}
void Affaires_judiciaires::setid(int id){this->id = id;}
void Affaires_judiciaires::setNom(QString Nom){this->Nom = Nom;}
void Affaires_judiciaires::setType(QString Type){this->Type = Type;}
void Affaires_judiciaires::setHorraire(QString Horraire){this->Horraire = Horraire;}
void Affaires_judiciaires::setAvancement(QString Avancement){this->Avancement = Avancement;}
void Affaires_judiciaires::setFaits(QString Faits){this->Faits = Faits;}
void Affaires_judiciaires::setDecision(QString Decision){this->Decision = Decision;}



bool Affaires_judiciaires::ajouter(){

    QSqlQuery query;
    QString id_string = QString::number(id);

        query.prepare("INSERT INTO AFFAIRE (id, nom, type, horraire, avancement, faits, decision) "
                      "VALUES (:id, :nom, :type, :horraire, :avancement, :faits, :decision)");
        query.bindValue(":id", id_string);
        query.bindValue(":nom", Nom);
        query.bindValue(":type", Type);
        query.bindValue(":horraire", Horraire);
        query.bindValue(":avancement", Avancement);
        query.bindValue(":faits", Faits);
        query.bindValue(":decision", Decision);


       return query.exec();
}

bool Affaires_judiciaires::supprimer(int id) {
    QSqlQuery query;
QString res= QString::number(id);
        query.prepare("DELETE FROM AFFAIRE where id=:id");
        query.bindValue(0, res);

       return query.exec();
}





QSqlQueryModel* Affaires_judiciaires::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("SELECT* from AFFAIRE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("HORRAIRE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("AVANCEMENT"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("FAITS"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("DECISION"));


    return model;
}



QSqlQueryModel* Affaires_judiciaires::Rechercher_aff(QString value)
{
     QSqlQueryModel *modal=new QSqlQueryModel();
     modal->setQuery("select * from AFFAIRE where id like '%"+value+"%' or nom like '%"+value+"%' or type like '%"+value+"%' or horraire like '%"+value+"%' or avancement like '%"+value+"%' or faits like '%"+value+"%' or decision like '%"+value+"%'");
     return modal;
}


QSqlQueryModel *Affaires_judiciaires::Trier_aff(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "id" && croissance == "ASC")
        modal->setQuery("select * from AFFAIRE order by id ASC ");
    else if(critere == "id" && croissance == "DESC")
        modal->setQuery("select * from AFFAIRE order by id DESC ");

    else if(critere == "Nom" && croissance == "ASC")
        modal->setQuery("select * from AFFAIRE order by NOM ASC ");
    else if(critere == "Nom" && croissance == "DESC")
        modal->setQuery("select * from AFFAIRE order by NOM DESC ");

    else if(critere == "Type" && croissance == "ASC")
        modal->setQuery("select * from AFFAIRE order by TYPE ASC ");
    else if(critere == "Type" && croissance == "DESC")
        modal->setQuery("select * from AFFAIRE order by TYPE DESC ");

    else if(critere == "Horraire" && croissance == "ASC")
        modal->setQuery("select * from AFFAIRE order by HORRAIRE ASC ");
    else if(critere == "Horraire" && croissance == "DESC")
        modal->setQuery("select * from AFFAIRE order by HORRAIRE DESC ");

    else if(critere == "Avancement" && croissance == "ASC")
        modal->setQuery("select * from AFFAIRE order by AVANCEMENT ASC ");
    else if(critere == "Avancement" && croissance == "DESC")
        modal->setQuery("select * from AFFAIRE order by AVANCEMENT DESC ");

    else if(critere == "Faits" && croissance == "ASC")
        modal->setQuery("select * from AFFAIRE order by FAITS ASC ");
    else if(critere == "Faits" && croissance == "DESC")
        modal->setQuery("select * from AFFAIRE order by FAITS DESC ");

    else if(critere == "Decision" && croissance == "ASC")
        modal->setQuery("select * from AFFAIRE order by DECISION ASC ");
    else if(critere == "Decision" && croissance == "DESC")
        modal->setQuery("select * from AFFAIRE order by DECISION DESC ");




    else if(critere == "Nom" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by nom");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by nom");

    else if(critere == "Type" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by type");
    else if(critere == "Email" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by type");

    else if(critere == "Horraire" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by horraire");
    else if(critere == "Horraire" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by horraire");

    else if(critere == "id" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by id");
    else if(critere == "id" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by id");

    else if(critere == "Avancement" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by avancement");
    else if(critere == "Avancement" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by avancement");

    else if(critere == "Faits" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by faits");
    else if(critere == "Faits" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by faits");

    else if(critere == "Decision" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by decision");
    else if(critere == "Decision" && croissance == "")
        modal->setQuery("select * from AFFAIRE order by decision");


    return  modal;
}


QChartView *Affaires_judiciaires::stat_type()
  {
      int t1=0;
      int t2=0;
      int t3=0;
      int t4=0;

      QSqlQuery query;

      query.prepare("select * from affaire where type='Crime contre les personnes'");
      query.exec();

      while(query.next())
          t1++;

      query.prepare("select * from affaire where type='Crime contre les biens'");
      query.exec();

      while(query.next())
          t2++;

      query.prepare("select * from affaire where type='Crime contre la nation'");
      query.exec();

      while(query.next())
          t3++;

      query.prepare("select * from affaire where type='Crime de guerre'");
      query.exec();

      while(query.next())
          t4++;

      qDebug() << t1 << t2 << t3 << t4 ;

      QPieSeries *series = new QPieSeries();
          series->append("Crime contre les personnes", t1);
          series->append("Crime contre les biens", t2);
          series->append("Crime contre la nation", t3);
          series->append("Crime de guerre", t4);

          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#D6ABBD");
          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#B59BBF");
          QPieSlice *slice3 = series->slices().at(2);
          slice3->setColor("#8690BC");
          QPieSlice *slice4 = series->slices().at(3);
          slice4->setColor("#4887AD");

          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique du type");

          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
 chartView->chart()->legend()->hide();
          return chartView;

  }


QChartView *Affaires_judiciaires::stat_annee()
  {


      QSqlQuery query;
      int g1=0;
      int g2=0;
      int g3=0;

      query.prepare("select horraire from affaire");
      if(query.exec())
      {
          while(query.next())
          {
              QString dates =query.value(0).toString();
              QDateTime dateTime = QDateTime::fromString(dates,"dd.MM.yyyy hh:mm");
              dates = dateTime.toString("yyyy");
              int year = dates.toInt();

              if(((2022-year) >= 1) && ((2022-year) <= 5) )
              g1++;
              if(((2022-year) >= 10) && ((2022-year) <= 20) )
              g2++;
              if(((2022-year) >= 20) && ((2022-year) <= 50) )
              g3++;
          }

      }

      QPieSeries *series = new QPieSeries();
          series->append("1-5 ans", g1);
          series->append("10-20 ans", g2);
          series->append("20-50 ans", g3);

          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#D6ABBD");
          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#007669");
          QPieSlice *slice3 = series->slices().at(2);
          slice3->setColor("#00C9B7");
         /* series->setLabelsVisible();
          series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
          for(auto slice : series->slices())
              slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));*/

          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique des annes");

          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
 chartView->chart()->legend()->hide();
          return chartView;

  }















