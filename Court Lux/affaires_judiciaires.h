#ifndef AFFAIRES_JUDICIAIRES_H
#define AFFAIRES_JUDICIAIRES_H

#include <QString>
#include <QSqlQueryModel>
#include <QChartView>
#include <QGraphicsView>
#include <iostream>
#include <QtCharts>

class Affaires_judiciaires
{
public:
    Affaires_judiciaires();
    Affaires_judiciaires(int, QString, QString, QString, QString, QString, QString, int);
    int getid();
    QString getNom();
    QString getType();
    QString getHorraire();
    QString getAvancement();
    QString getFaits();
    QString getDecision();
    int getNum(){return Num;}
    void setid(int);
    void setNom(QString);
    void setType(QString);
    void setHorraire(QString);
    void setAvancement(QString);
    void setFaits(QString);
    void setDecision(QString);
    void setNum(int Num){this->Num = Num;}
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel* Rechercher_aff(QString value);
    QSqlQueryModel* Trier_aff(QString croissance,QString critere);
    QChartView* stat_type();
    QChartView *stat_annee();
    bool controle_d_existence(int id);











private:
    int id, Num;
    QString Nom, Type, Avancement, Faits, Decision, Horraire;

};

#endif // AFFAIRES_JUDICIAIRES_H
