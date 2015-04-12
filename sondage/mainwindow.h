#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

#include "ajoutpersonne.h"
#include "aubonlait.h"
#include "chargement.h"
#include "personne.h"
#include "gestionsondes.h"
#include "sondage.h"

#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Chargement *chargement;
    AjoutPersonne *ajout;
    GestionSondes *gestionsondes;
 //   std::list<Personne> liste_personnes;
    std::vector<Personne> tab;
    std::vector<Sondage> tab_sondages;

    int num;
    QString path;
    int pos_personne_sel;
    int pos_sondage_sel;
private slots:

    void on_actionNouveauSonde_triggered();

    void on_actionNouveauSondage_triggered();

    void on_actionSauvegarder_triggered();

    void valider(Personne data);

    void reception_liste(std::vector<Personne> data, int num, std::vector<Sondage> data2,QString path);

    void reception_choix_id(int id);

    void on_actionGestion_triggered();

    void on_actionOuvrir_triggered();

    void on_actionQuitter_triggered();

private:
    Ui::MainWindow *ui;

    QString filename;
     QStringListModel *model;
};

#endif // MAINWINDOW_H
