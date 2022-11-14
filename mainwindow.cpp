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
#include "QrCode.h"
#include <QPixmap>
#include "connection.h"
#include <QPrintDialog>
#include "smtp.h"
#include <QFile>
#include <QFileDialog>
#include "qrcodegeneratorworker.h"
#include "exportexcelprojet.h"
#include <QFontDatabase>
#include <QPixmap>
#define chars_rx "[A-Za-z]{3,10}"
#define avancement_rx "[0-9]{1,3}%"
#include<fstream>
using namespace qrcodegen;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(2000, 1200);
    Affaires_judiciaires a;
    ui->setupUi(this);
     ui->tab_affaire->setModel(A.afficher());
    ui->le_id->setValidator(new QIntValidator(100, 999999, this));
ui->le_nom->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
ui->le_avancement->setValidator(new QRegExpValidator( QRegExp(avancement_rx),this));
  //  ui->stat->addWidget(a.stat_type(), 0, 0);
     ui->stat->addWidget(A.stat_type(), 0, 0);
     ui->stat->addWidget(A.stat_annee(), 0, 1);


     connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
     //connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
     connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

     ui->paswd->setEchoMode(QLineEdit::Password);






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bp_ajouter_clicked()
{

  int id = ui->le_id->text().toInt();
 QString Nom = ui->le_nom->text();
 QString Type = ui->typeee->currentText();
QString Horraire = ui->dateTimeEdit->dateTime().toString("dd.MM.yyyy hh:mm");
 QString Avancement = ui->le_avancement->text();
 QString Faits = ui->textEdit_faits->toPlainText();
QString Decision = ui->comboBox_decision->currentText();




 Affaires_judiciaires A(id, Nom, Type, Horraire, Avancement, Faits, Decision);

 bool test = A.ajouter();
 QMessageBox msgBox;

 if(test) {
     msgBox.setText("Ajout avec succes.");
      ui->tab_affaire->setModel(A.afficher());
      effacer_champs();
       update_stat();

 }
             else
     msgBox.setText("Echec d'ajout.");
             msgBox.exec();

}


void MainWindow::on_pb_supprimer_clicked()
{
Affaires_judiciaires A1;
A1.setid(ui->le_id->text().toInt());

bool test = A1.supprimer(A1.getid());
QMessageBox msgBox;

if(test) {
    msgBox.setText("Suppression avec succes.");
    ui->tab_affaire->setModel(A1.afficher());
    effacer_champs();
    update_stat();
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
      ui->dateTimeEdit->setDateTime(QDateTime::fromString(qry.value(3).toString(), "dd.MM.yyyy hh:mm"));
      ui->le_avancement->setText(qry.value(4).toString());
      ui->textEdit_faits->setPlainText(qry.value(5).toString());
      ui->comboBox_decision->setCurrentText(qry.value(6).toString());
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
        QString Horraire=ui->dateTimeEdit->dateTime().toString("dd.MM.yyyy hh:mm");
        QString Avancement=ui->le_avancement->text();
        QString Faits=ui->textEdit_faits->toPlainText();
        QString Decision = ui->comboBox_decision->currentText();

        QSqlQuery quer;
        quer.prepare("update AFFAIRE set  id='"+id_string+"', nom='"+Nom+"', type='"+Type+"', horraire='"+Horraire+"', avancement='"+Avancement+"', faits='"+Faits+"', decision='"+Decision+"' where id='"+id_string+"'");
          if(quer.exec())
          {

              ui->tab_affaire->setModel(A.afficher());
           QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectuée \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);
           effacer_champs();
           update_stat();
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
}

void MainWindow::update_stat()
{
    Affaires_judiciaires e;
    ui->stat->addWidget(e.stat_type(), 0, 0);
    ui->stat->addWidget(e.stat_annee(), 0, 1);

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

       /*  const int rowCount = tab_affaire.model()->rowCount();
         const int columnCount =  tab_affaire.model()->columnCount();*/

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


void MainWindow::on_qr_code_clicked()
{
    int tabeq=ui->tab_affaire->currentIndex().row();
        QVariant idd=ui->tab_affaire->model()->data(ui->tab_affaire->model()->index(tabeq,0));
        int id= idd.toInt();
        QSqlQuery qry;
        qry.prepare("select * from AFFAIRE where id=:id");
        qry.bindValue(":id",id);
        qry.exec();
        QString nom, type,ide;

        while(qry.next()){
            nom=qry.value(1).toString();
            type=qry.value(2).toString();

        }
         ide=int(id);
         ide="id: "+ide+"nom: "+nom+" type: "+type;
        QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

        // Read the black & white pixels
        QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
        for (int y = 0; y < qr.getSize(); y++) {
            for (int x = 0; x < qr.getSize(); x++) {
                int color = qr.getModule(x, y);  // 0 for white, 1 for black

                // You need to modify this part
                if(color==0)
                    im.setPixel(x, y,qRgb(254, 254, 254));
                else
                    im.setPixel(x, y,qRgb(0, 0, 0));
            }
        }
        im=im.scaled(200,200);
        ui->qrlabel->setPixmap(QPixmap::fromImage(im));
        int i=0 ;
        for(i=0;i<100;i=i+0.1){
            i++;
            ui->progressBar->setValue(i);
}
        }



void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
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


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
