#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include "affaires_judiciaires.h"
#include "smtp.h"
#include <iostream>
#include "Salle.h"
#include <QDebug>
//#include "arduino.h"
#include "employe.h"
#include "chat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // chayma
    void on_bp_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_tab_affaire_activated(const QModelIndex &index);

    void on_pushButton_modifier_clicked();

    void on_search_tab_textChanged(const QString &arg1);

    void on_tri_combobox_highlighted(int index);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_comboBox_highlighted(const QString &arg1);

    void effacer_champs();

void update_stat();

void on_pdf_clicked();

void on_qr_code_clicked();

void browse();

void sendMail();

void mailSent(QString status);

void on_excel_clicked();

void on_retour_affaires_clicked();

void on_login_clicked();

void on_gestAffaires_clicked();

void on_logout_clicked();



//soua

void on_Ajouter_clicked();

void on_Supprimer_clicked();

void on_Modifier_clicked();

void on_TableauAffichage_activated(const QModelIndex &index);

void on_Trier_clicked();

void on_Rechercher_clicked();

int on_Importer_PDF_clicked();





void on_pushButton_2_clicked();

void on_pushButton_3_clicked();

void on_pushButton_clicked();

void on_pushButton_4_clicked();

void on_calendarWidget_activated(const QDate &date);


void on_gestSalles_clicked();

//arduino
void update_label();

void on_arduino_clicked();

//Employes
void on_enregistrer_clicked();
void effacer_champs2();

void on_pb_supprimer2_clicked();

void on_le_rechercher_textChanged();

void on_cb_tri_currentTextChanged();

void on_tabWidget_tabBarClicked();

void on_pb_pdf_clicked();

void on_chat_clicked();

bool launch_chat(chat &chat_window);

void on_tabWidget_3_tabBarClicked(int index);

//menu

void on_retour_salles_clicked();

void on_retour_salles_2_clicked();

void on_retour_affaires_4_clicked();

void on_retour_affaires_3_clicked();

void on_retour_affaires_2_clicked();

void on_retour_employe_clicked();

//chat
void on_chat_clicked();
bool launch_chat(chat &chat_window);



void on_gestEmployes_clicked();

private:
    Ui::MainWindow *ui;
    Affaires_judiciaires A;
    QStringList files;
     Salle S;
     //Arduino a1;
     QByteArray data;
};

#endif // MAINWINDOW_H
