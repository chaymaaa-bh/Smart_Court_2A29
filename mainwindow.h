#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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





void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Affaires_judiciaires A;
    QStringList files;
};

#endif // MAINWINDOW_H
