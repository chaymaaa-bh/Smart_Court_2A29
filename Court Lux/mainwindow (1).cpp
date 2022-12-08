#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "affaires_judiciaires.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlError>
#include <QChar>
#include <QRegExp>
#include <QRegExpValidator>
#include <QPainter>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QLineEdit>
#include <QPainter>
#include <QPrinter>
#include <QPdfWriter>
#include <QDir>
#include <QTextDocument>
#include <QDateTime>
#include <QtWidgets>
#include <QPixmap>
#include "connection.h"
#include <QPrintDialog>
#include "smtp.h"
#include <QFile>
#include <QFileDialog>
#include "exportexcelprojet.h"
#include <QFontDatabase>
#include <QPixmap>
#define chars_rx "[A-Za-z]{3,10}"
#define avancement_rx "[0-9]{1,3}%"
#include<fstream>
#include "qrcodegen.hpp"
#include "historique.h"
#include <QDesktopServices>
#include "arduino.h"
using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //chayma

    Historique h;
    this->setFixedSize(1000, 730);
    Affaires_judiciaires a;
    ui->setupUi(this);
     ui->tab_affaire->setModel(A.afficher());
    ui->le_id->setValidator(new QIntValidator(100, 999999, this));
ui->le_nom->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
ui->le_avancement->setValidator(new QRegExpValidator( QRegExp(avancement_rx),this));

     ui->stat->addWidget(A.stat_type(), 0, 0);
     //ui->stat->addWidget(A.stat_annee(), 0, 1);





ui->histo->setText(h.load());

QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                   QCoreApplication::organizationName(), QCoreApplication::applicationName());

ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.gmail.com");






//soua


ui->TableauAffichage->setModel(S.afficher());

QSqlQueryModel *model=new QSqlQueryModel();
model = S.afficher();

int count=0;
for (int i = 0; i < model->rowCount(); i++){
    if(model->data(model->index(i,5)).toString() == "Panne")
    {count ++;
    }
}
       if (count!=0 ){
                   QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                   QString res=QString::number(count);
                   notifyIcon->show();
                   notifyIcon->showMessage("Alerte ! ","Vous avez "+res+" salles en pannes",QSystemTrayIcon::Information,15000);
               }


       int ret=a1.connect_arduino();
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< a1.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<a1.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(a1.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));







}


                 void MainWindow::update_label()
                 {
                     QByteArray Myint =a1.read_from_arduino();
                     QString Myint1=QString (Myint);
                 // ui->arduinoline->setText(Myint1);
                  data=a1.cherchercode(Myint1);
                 // ui->DATA->setText(data);

                     if(data=="1")      {
                       //  ui->label_msg->setText("unlocked");
                      }
                 // else{ui->label_msg->setText("locked");

                 }






MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bp_ajouter_clicked()
{

  int id = ui->le_id->text().toInt();
  int Num = ui->num->text().toInt();

 QString Nom = ui->le_nom->text();
 QString Type = ui->typeee->currentText();
QString Horraire = ui->dateEdit->date().toString("dd.MM.yyyy");
 QString Avancement = ui->le_avancement->text();
 QString Faits = ui->textEdit_faits->toPlainText();
QString Decision = ui->comboBox_decision->currentText();

QString id_string = QString::number(id);
QString num_string = QString::number(Num);


 Affaires_judiciaires A(id, Nom, Type, Horraire, Avancement, Faits, Decision, Num);

 bool test = A.ajouter();
 QMessageBox msgBox;

 if(test) {
     msgBox.setText("Ajout avec succes.");
      ui->tab_affaire->setModel(A.afficher());
      effacer_champs();
       update_stat();
       Historique h;
       h.save(id_string, Nom, Type, Horraire, Avancement, Decision, num_string, "Ajout");
       ui->histo->setText(h.load());

 }
             else
     msgBox.setText("Echec d'ajout.");
             msgBox.exec();

}


void MainWindow::on_pb_supprimer_clicked()
{
Affaires_judiciaires A1;
A1.setid(ui->le_id->text().toInt());
A1.setNum(ui->num->text().toInt());
int id = ui->le_id->text().toInt();
int Num = ui->num->text().toInt();
QString Nom = ui->le_nom->text();
QString Type = ui->typeee->currentText();
QString Horraire = ui->dateEdit->date().toString("dd.MM.yyyy");
QString Avancement = ui->le_avancement->text();
QString Faits = ui->textEdit_faits->toPlainText();
QString Decision = ui->comboBox_decision->currentText();
QString num_string = QString::number(Num);
QString id_string = QString::number(id);

bool test = A1.supprimer(A1.getid());
QMessageBox msgBox;


if(test) {
    msgBox.setText("Suppression avec succes.");
    ui->tab_affaire->setModel(A1.afficher());
    effacer_champs();
    update_stat();
    Historique h;
    h.save(id_string, Nom, Type, Horraire, Avancement, Decision, num_string, "Supression");
    ui->histo->setText(h.load());
}
            else
    msgBox.setText("Echec de supression.");
            msgBox.exec();


}





void MainWindow::on_tab_affaire_activated(const QModelIndex &index)
{
    QString val=ui->tab_affaire->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from AFFAIRE where id='"+val+"'");
    if(qry.exec())
    {
     while(qry.next())
     {
      ui->le_id->setText(qry.value(0).toString());
      ui->le_nom->setText(qry.value(1).toString());
      ui->typeee->setCurrentText(qry.value(2).toString());
      ui->dateEdit->setDate(QDate::fromString(qry.value(3).toString(),"dd.MM.yyyy"));//date
      ui->le_avancement->setText(qry.value(4).toString());
      ui->textEdit_faits->setPlainText(qry.value(5).toString());
      ui->comboBox_decision->setCurrentText(qry.value(6).toString());
      ui->num->setText(qry.value(7).toString());
     }
    }
    else
    {
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

void MainWindow::on_pushButton_modifier_clicked()
{
    int id=ui->le_id->text().toInt();
    QString id_string = QString::number(id);
        QString Nom=ui->le_nom->text();
        QString Type=ui->typeee->currentText();
     QString Horraire = ui->dateEdit->date().toString("dd.MM.yyyy");
        QString Avancement=ui->le_avancement->text();
        QString Faits=ui->textEdit_faits->toPlainText();
        QString Decision = ui->comboBox_decision->currentText();
        int Num=ui->num->text().toInt();
        QString num_string = QString::number(Num);

        QSqlQuery quer;
        quer.prepare("update AFFAIRE set  id='"+id_string+"', nom='"+Nom+"', type='"+Type+"', horraire='"+Horraire+"', avancement='"+Avancement+"', faits='"+Faits+"', decision='"+Decision+"', num='"+Num+"' where id='"+id_string+"'");
          if(quer.exec())
          {

              ui->tab_affaire->setModel(A.afficher());
           QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectuée \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);
           effacer_champs();
           update_stat();
           Historique h;
           h.save(id_string, Nom, Type, Horraire, Avancement, Decision, num_string, "Modification");
           ui->histo->setText(h.load());

          }
          else
              QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                    QObject::tr("modification non effectuée \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_search_tab_textChanged(const QString &arg1)
{
    QString search=arg1;
      ui->tab_affaire->setModel(A.Rechercher_aff(search));

}



void MainWindow::on_comboBox_highlighted(const QString &arg1)
{
    Affaires_judiciaires e;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(arg1 != "Choisir")
        ui->tab_affaire->setModel(e.Trier_aff(type,arg1));

    else  ui->tab_affaire->setModel(e.afficher());

}



void MainWindow::on_radioButton_clicked()
{
    Affaires_judiciaires e;
    QString type="";


    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(ui->comboBox->currentText() != "Choisir")
        ui->tab_affaire->setModel(e.Trier_aff(type,ui->comboBox->currentText()));

    else  ui->tab_affaire->setModel(e.afficher());
}

void MainWindow::on_radioButton_2_clicked()
{
    Affaires_judiciaires e;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(ui->comboBox->currentText() != "Choisir")
        ui->tab_affaire->setModel(e.Trier_aff(type,ui->comboBox->currentText()));


    else  ui->tab_affaire->setModel(e.afficher());
}

void MainWindow::effacer_champs() {
   ui->le_id->clear();
   ui->le_nom->clear();
   //ui->le_type->clear();
   //ui->dateTimeEdit->setDateTime();
   ui->le_avancement->clear();
   //ui->le_faits->clear();
   //ui->le_decision->clear();
   ui->num->clear();
}

void MainWindow::update_stat()
{
    Affaires_judiciaires e;
    ui->stat->addWidget(e.stat_type(), 0, 0);
   // ui->stat->addWidget(e.stat_annee(), 0, 1);

}




void MainWindow::on_pdf_clicked()
{
    QTableView tab_affaire;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QString value=ui->id_label->text();
         Connection c;

         QSqlQuery qry;




         qry.prepare("select * from affaire where id='"+value+"'");
         qry.exec();
         Mod->setQuery(qry);
         tab_affaire.setModel(Mod);
         //c.closeconnection();

         QString strStream;
         QTextStream out(&strStream);

       //  const int rowCount = tab_affaire.model()->rowCount();
        //const int columnCount =  tab_affaire.model()->columnCount();

         const QString strTitle ="Document";



         out <<  "<html>\n"
                               //"<img src=':/icons/icons/icone.png'/>"
                              "<head>\n"
                                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                              <<  QString("<title>%1</title>\n").arg(strTitle)
                              <<  "</head>\n"
                                  "<style> h3{"
                                  "font-family: Century Gothic; color: #333; font-weight: lighter;"
                                  "}\n"
                                  "</style>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"
                             << QString("<h1 style=\" font-size: 40px; font-family: Century Gothic; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h1>\n").arg("Fiche affaire judiciaire")
                             <<"<br>";

                            QString id = tab_affaire.model()->data(tab_affaire.model()->index(0, 0)).toString().simplified();
                            qDebug()<<id;
                            out << QString("<h3>id : %1</h3>").arg((!id.isEmpty()) ? id : QString("&nbsp;"));
                            QString nom = tab_affaire.model()->data(tab_affaire.model()->index(0, 1)).toString().simplified();
                            out << QString("<h3>Nom : %1</h3>").arg((!nom.isEmpty()) ? nom : QString("&nbsp;"));
                            QString type = tab_affaire.model()->data(tab_affaire.model()->index(0, 2)).toString().simplified();
                            out << QString("<h3>Type : %1</h3>").arg((!type.isEmpty()) ? type : QString("&nbsp;"));
                            QString horraire = tab_affaire.model()->data(tab_affaire.model()->index(0, 3)).toString().simplified();
                            out << QString("<h3 bkcolor=0>horraire : %1</h3>").arg((!horraire.isEmpty()) ? horraire : QString("&nbsp;"));
                            QString avancement = tab_affaire.model()->data(tab_affaire.model()->index(0, 4)).toString().simplified();
                            out << QString("<h3 bkcolor=0>avanement : %1</h3>").arg((!avancement.isEmpty()) ? avancement : QString("&nbsp;"));
                            QString faits = tab_affaire.model()->data(tab_affaire.model()->index(0, 5)).toString().simplified();
                            out << QString("<h3 bkcolor=0>faits : %1</h3>").arg((!faits.isEmpty()) ? faits : QString("&nbsp;"));
                            QString decision = tab_affaire.model()->data(tab_affaire.model()->index(0, 6)).toString().simplified();
                            out << QString("<h3 bkcolor=0>Decision : %1</h3>").arg((!decision.isEmpty()) ? decision : QString("&nbsp;"));

                            out<<
                              "</body>\n"
                              "</html>\n";

                                  QTextDocument *document = new QTextDocument();
                                                  document->setHtml(strStream);

                                                  QPrinter printer;
                                                  QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                                  if (dialog->exec() == QDialog::Accepted) {

                                                      document->print(&printer);
                                                  }

                                                  printer.setOutputFormat(QPrinter::PdfFormat);
                                                  printer.setPaperSize(QPrinter::A4);
                                                  printer.setOutputFileName("/tmp/affaire.pdf");
                                                  printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                                                  delete document;


}




void MainWindow::on_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tab_affaire);

    //colums to export
    obj.addField(0, "Id", "char(20)");
    obj.addField(1, "Nom", "char(20)");
    obj.addField(2, "Type", "char(20)");
    obj.addField(3, "Horraire", "char(20)");
    obj.addField(4, "Avancement", "char(20)");
    obj.addField(5, "Faits", "char(20)");
    obj.addField(5, "Decision", "char(20)");
    obj.addField(6, "Num", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}



void MainWindow::on_qr_code_clicked()
{
    using namespace qrcodegen;

       ///////////////// FETCH DATA FROM DATABASE ////////////////////////
       QTableView tab_affaire;
       QSqlQueryModel * Mod=new  QSqlQueryModel();
       QString value=ui->le_id->text();


            QSqlQuery qry;




            qry.prepare("select * from AFFAIRE where id='"+value+"'");
            qry.exec();
            Mod->setQuery(qry);
            tab_affaire.setModel(Mod);


           ///////////////// SAVING DATA ///////////
           QString id = tab_affaire.model()->data(tab_affaire.model()->index(0, 0)).toString().simplified();
           QString Nom = tab_affaire.model()->data(tab_affaire.model()->index(0, 1)).toString().simplified();
           QString Type = tab_affaire.model()->data(tab_affaire.model()->index(0, 2)).toString().simplified();
           QString Horraire = tab_affaire.model()->data(tab_affaire.model()->index(0, 3)).toString().simplified();
           QString Avancement = tab_affaire.model()->data(tab_affaire.model()->index(0, 4)).toString().simplified();
           QString Faits = tab_affaire.model()->data(tab_affaire.model()->index(0, 5)).toString().simplified();
           QString Decision = tab_affaire.model()->data(tab_affaire.model()->index(0, 6)).toString().simplified();
           QString Num = tab_affaire.model()->data(tab_affaire.model()->index(0, 7)).toString().simplified();



       QString text = id+"\n"+Nom+"\n"+Type+"\n"+Horraire+"\n"+Avancement+"\n"+Faits+"\n"+Decision+"\n"+Decision+"\n";
         // Create the QR Code object
         QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );

         qint32 sz = qr.getSize();
         QImage im(sz,sz, QImage::Format_RGB32);
           QRgb black = qRgb(0, 0, 0);
           QRgb white = qRgb(255, 255, 255);
         for (int y = 0; y < sz; y++)
           for (int x = 0; x < sz; x++)
             im.setPixel(x,y,qr.getModule(x, y) ? black : white );//setpixelmap tafichilek qr code
         ui->qrlabel->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
         int i=0 ;
         for(i=0;i<100;i=i+0.1){
             i++;
             ui->progressBar->setValue(i);
}
         }



//soua

void MainWindow::on_Ajouter_clicked()
{
    //Récupération des informations saisies dans les 3 champs
        int Num=ui->Num->text().toInt();
        QString Type = ui->Type5->text();
        int Inventaire=ui->Inventaire->text().toInt();
        int Surface=ui->Surface->text().toInt();
        QString Emplacement=ui->Emplacement->text();
        QString Permission=ui->Permission->currentText();
        QString descpanne=ui->Emplacement_2->text();



        Salle SA(Num, Type ,Inventaire,Surface,Emplacement,Permission,descpanne);
        bool test=SA.ajouter();

        if(test)
        {
            //Refresh (Actualiser)
            ui->TableauAffichage->setModel(S.afficher());
            QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Ajout effectué\n""Click Cancel to exit."), QMessageBox::Cancel);

        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Ajout non effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_Supprimer_clicked()
{
    int Num=ui->Num->text().toInt();
        bool test=S.supprimer(Num);

        if(test)
        {
            //Refresh (Actualiser)
            ui->TableauAffichage->setModel(S.afficher());
            QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectuée. \n""Click Cancel to Exit."),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),QObject::tr("Suppression non effectué.\n""Click Cancel to exit."), QMessageBox::Cancel);

}
//currentText()
void MainWindow::on_Modifier_clicked()
{
    Salle S1;
          int Num=ui->Num->text().toInt();
           QString Type=ui->Type5->text();
          int Inventaire=ui->Inventaire->text().toInt();
          int Surface=ui->Surface->text().toInt();
          QString Emplacement=ui->Emplacement->text();
          QString Permission=ui->Permission->currentText();
          QString descpanne=ui->Emplacement_2->text();

          Salle S(Num,Type,Inventaire,Surface,Emplacement,Permission,descpanne);

         bool test=S.modifier(Num,Type,Inventaire,Surface,Emplacement,Permission,descpanne);
         if(test)
         {ui->TableauAffichage->setModel(S1.afficher());
             QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("modif successful.\n"
                                                 "click cancel to exit."),QMessageBox::Cancel);

         }
         else QMessageBox::critical(nullptr, QObject::tr(" not OK"),
                                       QObject::tr("modif non effectue.\n"
                                                   "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_TableauAffichage_activated(const QModelIndex &index)
{

    QSqlQuery query;

    QString val;
            val=ui->TableauAffichage->model()->data(index).toString();
    //val=ui->TableauAffichage->model()->index(index.row(),index.column()).data().toString();
    query.prepare("select * from Salle where Num='"+val+"' or Type='"+val+"' or Inventaire='"+val+"' or Surface='"+val+"' or Emplacement='"+val+"' or Permission='"+val+"' or descpanne='"+val+"' ");
    if(query.exec())
 {  while(query.next()){
            ui->Num->setText(query.value(0).toString());
            ui->Type5->setText(query.value(1).toString());
            ui->Inventaire->setValue(query.value(2).toFloat());
            ui->Surface->setValue(query.value(3).toFloat());
            ui->Emplacement->setText(query.value(4).toString());
            ui->Permission->setCurrentText(query.value(5).toString());
            ui->Emplacement_2->setText(query.value(6).toString());


  }}
 else
      QMessageBox::critical(this,tr("error"),query.lastError().text());
}

void MainWindow::on_Trier_clicked()
{
    Salle S;
                    QString choix=ui->comboBox_tri->currentText();
                    if (choix=="Num")
                    {
                        ui->TableauAffichage->setModel(S.trier_Num());
                        ui->TableauAffichage->setModel(S.afficher());
                        bool test=S.trier_Num();
                        if (test)
                        {

                    ui->TableauAffichage->setModel(S.trier_Num());
                            QMessageBox::information(nullptr,QObject::tr("ok"),
                                                     QObject::tr("tri Num effectué \n"
                                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

                        }
                        else
                              QMessageBox::critical(nullptr, QObject::tr("non"),
                                          QObject::tr("tri Num failed.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
                    }
                    if (choix=="Inventaire")
                    {
                        ui->TableauAffichage->setModel(S.trier_Inventaire());
                        ui->TableauAffichage->setModel(S.afficher());
                        bool test=S.trier_Inventaire();
                        if (test)
                        {

                    ui->TableauAffichage->setModel(S.trier_Inventaire());
                            QMessageBox::information(nullptr,QObject::tr("ok"),
                                                     QObject::tr("tri Inventaire effectué \n"
                                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

                        }
                        else
                              QMessageBox::critical(nullptr, QObject::tr("non"),
                                          QObject::tr("tri Inventaire failed.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
                    }
                    if (choix=="Surface")
                    {
                        ui->TableauAffichage->setModel(S.trier_Surface());
                        ui->TableauAffichage->setModel(S.afficher());
                        bool test=S.trier_Surface();
                        if (test)
                        {

                    ui->TableauAffichage->setModel(S.trier_Surface());
                            QMessageBox::information(nullptr,QObject::tr("ok"),
                                                     QObject::tr("tri Surface effectué \n"
                                                                 "Click Cancel to exist ."),QMessageBox::Cancel);

                        }
                        else
                              QMessageBox::critical(nullptr, QObject::tr("non"),
                                          QObject::tr("tri Surface failed.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
                    }

}

void MainWindow::on_Rechercher_clicked()
{
    Salle S;


                   QString choix=ui->comboBox_recherche->currentText();

                   if (choix=="Num")
                   {
                       QString Num=ui->Le_rech->text();
                       ui->TableauAffichage->setModel(S.rechercherNum(Num));
                   }
                   if (choix=="Type")
                   {
                       QString Type=ui->Le_rech->text();
                       ui->TableauAffichage->setModel(S.rechercherType(Type));
                   }
                   if (choix=="Emplacement")
                   {
                       QString Emplacement=ui->Le_rech->text();
                       ui->TableauAffichage->setModel(S.rechercherEmplacement(Emplacement));
                   }
}



int MainWindow::on_Importer_PDF_clicked()
{
    QPrinter printer;
                  printer.setOutputFormat(QPrinter::PdfFormat);
                  printer.setOutputFileName("GestiondeSalle.pdf");
                  QPainter painter;
                  if (! painter.begin(&printer)) { // failed to open file
                      qWarning("failed to open file, is it writable?");
                      return 1;
                  }
                      QString Num=ui->Num->text();
                      QString Type=ui->Type5->text();
                      QString Inventaire=ui->Inventaire->text();
                      QString Surface=ui->Surface->text();
                      QString Emplacement=ui->Emplacement->text();
                      QString Permission=ui->Permission->currentText();
                      painter.drawText(400,10,"gestion des Salles");
                      painter.drawText(10,30,"Numéro:");
                      painter.drawText(80,30,Num);
                      painter.drawText(10,50,"Type:");
                      painter.drawText(80,50,Type);
                      painter.drawText(10,70,"Inventaire:");
                      painter.drawText(80,70,Inventaire);
                      painter.drawText(10,90,"Surface:");
                      painter.drawText(150,90,Surface);
                      painter.drawText(10,110,"Emplacement:");
                      painter.drawText(150,110,Emplacement);
                      painter.drawText(10,130,"Permission:");
                      painter.drawText(150,130,Permission);


                   painter.end();

}




void MainWindow::on_pushButton_2_clicked()
{
    QChartView *chartView = S.stat_type();
    chartView->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->TableauAffichage->setModel(S.afficher());
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model = S.afficher();

    int count=0;
    for (int i = 0; i < model->rowCount(); i++){
        if(model->data(model->index(i,5)).toString() == "Panne")
        {count ++;
        }
    }


            //QSqlQuery query("SELECT * FROM salle WHERE permission='Panne' ");

            //query.exec();
            //while (query.next())
            //{


                    //count++;

            //}

//    ui->stat->addWidget(S.stat_type(), 0, 0);
//    if (S.notification()>0)
//                 {
//                     QString notif=QString::number(S.notification())+" salles dont l'entree n'est pas permise.\n""Click Ok to exit.";
//                     QMessageBox::warning(nullptr, QObject::tr("Alerte"),notif, QMessageBox::Ok);
//                 }

           if (count!=0 ){
                       QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
                       QString res=QString::number(count);
                       notifyIcon->show();
                       notifyIcon->showMessage("Alerte ! ","Vous avez "+res+" salles en pannes",QSystemTrayIcon::Information,15000);
                   }
}

void MainWindow::on_pushButton_4_clicked()
{
        QDate datea;
    QSqlQuery Query;
    int Num=ui->Num->text().toInt();
    Query.prepare("SELECT horraire from affaire where num=:Num ");
    Query.bindValue(":Num",Num);

    Query.exec();
    while(Query.next())
    {

        datea=Query.value(0).toDate();
    }
ui->calendarWidget->setSelectedDate(datea);


    qDebug() << datea;
}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{

    QString dates = date.toString("dd.MM.yyyy");
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery Query;
    Query.prepare("SELECT num  from affaire where horraire=:d ");
    Query.bindValue(":d",dates);
    Query.exec();



    model->setQuery(Query);
     model->setHeaderData(0,Qt::Horizontal,QObject::tr("salles occupées"));

   ui->tableView_date->setModel(model);
}

//arduino


void MainWindow::on_arduino_clicked()
{
    a1.read_from_arduino();

}




void MainWindow::on_retour_affaires_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_login_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_gestAffaires_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_logout_clicked()
{
 ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_gestSalles_clicked()
{
   ui->stackedWidget->setCurrentIndex(3);
}



void MainWindow::on_retour_salles_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_retour_salles_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_retour_affaires_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_retour_affaires_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_retour_affaires_2_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
}
