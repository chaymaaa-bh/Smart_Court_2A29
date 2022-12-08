#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Court_db");
db.setUserName("Nour123");//inserer nom de l'utilisateur
db.setPassword("Nour123");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
