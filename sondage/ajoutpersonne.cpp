#include "ajoutpersonne.h"
#include "ui_ajoutpersonne.h"
#include "mainwindow.h"


AjoutPersonne::AjoutPersonne(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjoutPersonne)
{
    ui->setupUi(this);

    ui->lbl_warning->hide();
}

AjoutPersonne::~AjoutPersonne()
{
    delete ui;
}

void AjoutPersonne::on_pushButton_clicked()
{
    personne.age = ui->txtbox_age->text().toInt();
    personne.nb_personnes = ui->spbox_nb_personnes->text().toInt();
    personne.nb_enfants = ui->spbox_enfants->text().toInt();
    personne.nb_animaux = ui->spbox_animaux->text().toInt();
    personne.etat_civil = ui->cb_etat_civil->currentText();
    int pos_revenu = ui->cb_revenu->currentIndex();
    switch(pos_revenu)
    {
        case 0:
            personne.min_revenu = 10000;
            personne.max_revenu = 25000;
        break;
        case 1:
            personne.min_revenu = 25000;
            personne.max_revenu = 70000;
        break;
        case 2:
            personne.min_revenu = 70000;
            personne.max_revenu = 150000;
        break;
        default:
            personne.min_revenu = 150000;
            personne.max_revenu = 0;
        break;

    }

    if(ui->rdb_homme->isChecked())
    {
        personne.sexe = "homme";
    }
    else
    {
        personne.sexe = "femme";
    }

    if(personne.age == 0)
    {
        ui->lbl_warning->setText("<font color='red'>âge incorrect</font>");
        ui->lbl_warning->show();
    }
    else if(personne.nb_personnes < personne.nb_enfants || personne.nb_personnes == 0)
    {
        ui->lbl_warning->setText("<font color='red'>nombre de personnes incorrecte</font>");
    }
    else
    {
        ui->lbl_warning->hide();


        emit valider(personne);


        this->close();

    }

}
