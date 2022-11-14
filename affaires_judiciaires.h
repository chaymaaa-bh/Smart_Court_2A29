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
    Affaires_judiciaires(int, QString, QString, QString, QString, QString, QString);
    int getid();
    QString getNom();
    QString getType();
    QString getHorraire();
    QString getAvancement();
    QString getFaits();
    QString getDecision();
    void setid(int);
    void setNom(QString);
    void setType(QString);
    void setHorraire(QString);
    void setAvancement(QString);
    void setFaits(QString);
    void setDecision(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel* Rechercher_aff(QString value);
    QSqlQueryModel* Trier_aff(QString croissance,QString critere);
    QChartView* stat_type();
    QChartView *stat_annee();











private:
    int id;
    QString Nom, Type, Avancement, Faits, Decision, Horraire;

};

#endif // AFFAIRES_JUDICIAIRES_H
