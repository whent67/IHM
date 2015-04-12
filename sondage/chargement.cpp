#include "chargement.h"
#include "ui_chargement.h"
#include <fstream>
#include <vector>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <sstream>

Chargement::Chargement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chargement)
{
    ui->setupUi(this);

}

Chargement::~Chargement()
{
    delete ui;
}

void Chargement::on_btn_ok_clicked()
{


    std::ifstream fo(ui->txt_fichier->text().toStdString().c_str() , std::ios::in);

    if(fo)
    {

    }
    std::string s;
    std::string tok;
    std::vector<std::string> tab_parties;


    std::vector<Personne> tableau;
    std::vector<Sondage> tableau_sondage;
    while(std::getline(fo,s)) //va lire chaque ligne et mettre dans s
    {

        //test virgule
        std::stringstream input_t(s); // va mettre dans un stream la ligne s

        while(std::getline(input_t,tok,',')) //va séparer les éléments de s en fonction de s permet de mettre des espaces dans les données
        {

            tab_parties.push_back(tok);
        }
        Personne p;
        Sondage s;
        p.id = std::atoi(tab_parties[0].c_str());
        p.age = std::atoi(tab_parties[1].c_str());
        p.sexe = QString::fromStdString(tab_parties[2]);
        p.etat_civil = QString::fromStdString(tab_parties[3]);
        p.nb_personnes = std::atoi(tab_parties[4].c_str());
        p.nb_enfants = std::atoi(tab_parties[5].c_str());
        p.nb_animaux = std::atoi(tab_parties[6].c_str());
        p.min_revenu = std::atoi(tab_parties[7].c_str());
        p.max_revenu = std::atoi(tab_parties[8].c_str());
        if(tab_parties.size() > 9) //on a un sondage
        {
            s.id_p = p.id;
            s.nb_marques_connues = std::atoi(tab_parties[9].c_str());
            std::vector<QString> liste_marques;
            int pos_c;
            for(pos_c=0; pos_c<s.nb_marques_connues; pos_c++)
            {
                //récupère les marques connues
                liste_marques.push_back(QString::fromStdString(tab_parties[10+pos_c].c_str()));
            }
            s.tab_marques_connues = liste_marques;
            liste_marques.clear();
            s.nb_marques_achetees = std::atoi(tab_parties[pos_c+10].c_str());
            int pos_a;
            for(pos_a=0; pos_a<s.nb_marques_achetees; pos_a++)
            {
                liste_marques.push_back(QString::fromStdString(tab_parties[11+pos_c+pos_a].c_str()));
            }
            s.tab_marques_achetees = liste_marques;
            liste_marques.clear();
            s.frequence = QString::fromStdString(tab_parties[11+pos_a+pos_c]);
            s.nb_type = std::atoi(tab_parties[12+pos_a+pos_c].c_str());
            int pos_t;
            for(pos_t=0; pos_t<s.nb_type; pos_t++)
            {
                liste_marques.push_back(QString::fromStdString(tab_parties[13+pos_c+pos_a+pos_t]));
            }
            s.tab_types = liste_marques;

        }

        tableau.push_back(p);
        tableau_sondage.push_back(s);
        tab_parties.clear();


    }

    QString path = ui->txt_fichier->text();
    emit envoi_liste(tableau, tableau.size(),tableau_sondage, path);

    this->close();


}

void Chargement::on_btn_nouveau_clicked()
{
     QString filename = QFileDialog::getSaveFileName(0, "Sauvegarde d'une personne","/home","Text files (*.txt *.csv)", 0,0);
     ui->txt_fichier->setText(filename);


}

void Chargement::on_btn_parcourir_clicked()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Text files (*.txt *.csv)");
    ui->txt_fichier->setText(fichier);
}

