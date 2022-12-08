#include "employe.h"
#include <QString>
#include <QSqlQueryModel>
#include <iostream>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableView>

Employe::Employe()
{
    id=0;
    CIN="";
    Telephone="";
    Nom="";
    Prenom="";
    Naissance="";
    Nationalite="";
    Email="";
    Departement="";
    Role="";
    mdp="";
}


Employe:: Employe(int id,QString cin, QString no, QString pr, QString nai , QString na,QString tel ,QString em, QString de, QString ro,QString md)
{
    this->id=id;
    this->CIN=cin; 
    this->Nom=no;
    this->Prenom=pr;
    this->Naissance=nai;
    this->Nationalite=na;
    this->Telephone=tel;
    this->Email=em;
    this->Departement=de;
    this->Role=ro;
    this->mdp=md;
}

void Employe::setid(int d) {id=d;}
int Employe::getid() {return id;}

//pour changer mdp
void Employe::setmdp(QString m){mdp=m;}
QString Employe::getmdp(){return mdp;}


bool Employe::ajouter() //completed
{
    QSqlQuery query;
    QString id_string = QString::number(id);

        query.prepare("INSERT INTO EMPLOYE (id, CIN,  Nom, Prenom , Naissance, Nationalite, Telephone, Email, Departement, Role, mdp) "
                      "VALUES (:ID, :CIN, :NOM, :PRENOM , :NAISSANCE, :NATIONALITE, :TELEPHONE, :EMAIL, :DEPARTEMENT, :ROLE, :MDP)");

        query.bindValue(0, id_string);
        query.bindValue(1, CIN);
        query.bindValue(2, Nom);
        query.bindValue(3, Prenom);
        query.bindValue(4, Naissance);
        query.bindValue(5, Nationalite);
        query.bindValue(6, Telephone);
        query.bindValue(7, Email);
        query.bindValue(8, Departement);
        query.bindValue(9, Role);
        query.bindValue(10, mdp);

       return query.exec();

}

QSqlQueryModel* Employe::afficher() //not completed
{
    QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("SELECT* from EMPLOYE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("NAISSANCE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("NATIONALITE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("TELEPHONE"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("EMAIL"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("DEPARTEMENT"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("ROLE"));
        model->setHeaderData(10, Qt::Horizontal, QObject::tr("MDP"));



    return model;
}

//delete
bool Employe::supprimer(int) //completed
{
    QSqlQuery query;
    QString res= QString::number(id);
        query.prepare("DELETE FROM EMPLOYE where id=:ID");
        query.bindValue(0, res);

       return query.exec();
}




//rechercher
QSqlQueryModel* Employe::Rechercher_emp(QString value) //completed
{
    QSqlQueryModel *modal=new QSqlQueryModel();
    modal->setQuery("select * from EMPLOYE where ID like '%"+value+"%' or NOM like '%"+value+"%' or CIN like '%"+value+"%' or TELEPHONE like '%"+value+"%' or EMAIL like '%"+value+"%' or ROLE like '%"+value+"%' or DEPARTEMENT like '%"+value+"%'");
    return modal;
}


QSqlQueryModel* Employe::Trier_emp(QString croissance,QString critere) //not complete
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "id" && croissance == "ASC")
        modal->setQuery("select * from EMPLOYE order by ID ASC ");
    else if(critere == "id" && croissance == "DESC")
        modal->setQuery("select * from EMPLOYE order by ID DESC ");

    else if(critere == "Nom" && croissance == "ASC")
        modal->setQuery("select * from EMPLOYE order by NOM ASC ");
    else if(critere == "Nom" && croissance == "DESC")
        modal->setQuery("select * from EMPLOYE order by NOM DESC ");

    return  modal;


}

bool Employe::modifier(int id, QString cin, QString Nom, QString Prenom, QString Naissance, QString Nationalite, QString tele, QString Email,  QString Departement, QString role, QString mdp)
{
    QSqlQuery query;
    mdp="";
    QString id_string =QString::number(id);
    query.prepare("update EMPLOYE set cin=:CIN,Nom=:NOM,Prenom=:PRENOM,Naissance=:NAISSANCE,Nationalite=:NATIONALITE,tele=:TELEPHONE,Email=:EMAIL,Departement=:DEPARTEMENT,role=:ROLE, mdp=:MDP where id=:ID");
    query.bindValue(":ID", id_string);
    query.bindValue(":CIN", cin);
    query.bindValue(":NOM", Nom);
    query.bindValue(":PRENOM", Prenom);
    query.bindValue(":NAISSANCE", Naissance);
    query.bindValue(":NATIONALITE", Nationalite);
    query.bindValue(":TELEPHONE", tele);
    query.bindValue(":EMAIL", Email);
    query.bindValue(":DEPARTEMENT",Departement );
    query.bindValue(":ROLE", role);
    query.bindValue(":MDP", mdp);

    return    query.exec();

}


