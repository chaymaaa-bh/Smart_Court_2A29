#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include <iostream>
#include <QSqlQuery>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <fstream>
#include <windows.h>
#include <QTextStream>
#include <QPixmap>
#include <QPainter>




class Employe
{
public:

    //constructors
    Employe();
   Employe(int, QString, QString, QString, QString, QString, QString, QString, QString, QString, QString);


    bool ajouter();

    void setid(int);
    int getid();

    //pour changer mdp
    void setmdp(QString);
    QString getmdp();

    //read
    QSqlQueryModel* afficher();

    //update
    bool modifier(int, QString, QString, QString, QString, QString, QString, QString, QString, QString, QString);

    //delete
    bool supprimer(int);

    //metiers
    QSqlQueryModel* Rechercher_emp(QString value);
    QSqlQueryModel* Trier_emp(QString croissance,QString critere);

private:
    int id;
    QString CIN,Nom,Prenom,Naissance,Nationalite,Email,Departement,Role,Telephone,mdp;
};

#endif // EMPLOYE_H

