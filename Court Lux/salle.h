#ifndef SALLE_H
#define SALLE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QString>
#include <QChart>
#include <QtCharts>
#include <QIntValidator>
#include <QPieSeries>
#include <QChartView>
#include <QGraphicsView>

class Salle
{
public:
    //Constructeur
    Salle();
    Salle(int, QString, int, int, QString, QString,QString );
    //getters
    int getNum(){return Num;}
    QString getType(){return Type;}
    int getInventaire(){return Inventaire;}
    int getSurface(){return Surface;}
    QString getEmplacement(){return Emplacement;}
    QString getPermission(){return Permission;}
    //setters
    void setNum(int){this->Num=Num;}
    void setType(QString t){Type=t;}
    void setInventaire(int){this->Inventaire=Inventaire;}
    void setSurface(int){this->Surface=Surface;}
    void setEmplacement(QString e){Emplacement=e;}
    void setPermission(QString p){Permission=p;}
    //fonctions
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);

    bool modifier(int,QString,int,int,QString,QString,QString);
        QSqlQueryModel * trier_Num();
        QSqlQueryModel * trier_Inventaire();
        QSqlQueryModel * trier_Surface();


        QSqlQueryModel * rechercherNum(QString);
            QSqlQueryModel * rechercherType(QString);
            QSqlQueryModel * rechercherEmplacement(QString);

QChartView *stat_type();







private:
    int Num,Inventaire,Surface;
    QString Type,Emplacement,Permission,descpanne;
};

#endif // Salle_H
