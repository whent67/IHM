#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <fstream>
#include <string>

#include <cstring>
#include <vector>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->hide();
    ui->tabprincipal->hide(); //au départ on n'a pas sélectionné de sondé
    ui->actionQuitter->setShortcut(QKeySequence::Quit);
   // ui->menuFichier->addAction()
//connect(action, SIGNAL(triggered()),this,SLOT(slotAbout()));

    // Create model
    model = new QStringListModel(this);
    // Make data
    QStringList List;
    List << "Danone" << "Yoplait" << "Leader-price" << "Carrefour" << "Paturages" << "Auchan" << "Activia" << "Nestle" << "U" << "Milbona" << "Casino" << "Dia" << "Mamie-nova" << "Sojasun" << "Sveltesse";
    // Populate our model
    model->setStringList(List);
    // Glue model and view together
    ui->listview_marques_achetees->setModel(model);
    ui->listview_marques_connues->setModel(model); //on charge la liste des marques qui seront sélectionnées si elles sont dans la bdd

    chargement = new Chargement(this);
    chargement->setModal(true);
    // lorsqu'il y a validation de la page chargement on récupère le tableau des personnes et le path du fichier
    connect(chargement, SIGNAL(envoi_liste(std::vector<Personne>, int,std::vector<Sondage>, QString)), this, SLOT(reception_liste(std::vector<Personne>,int,std::vector<Sondage>,QString)));
    chargement->exec(); // d'abord exécution en modal pour la fenêtre de chargement

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNouveauSonde_triggered()
{
    ui->tabprincipal->show();
    ui->lbl_warning_2->hide();
    if(tab.size() == 0)
    {
        //encore personne dans la bdd donc pos_personne actuelle = 0
        pos_personne_sel = 0;
    }
    else
    {
        pos_personne_sel = tab.size(); //il faut rajouter à la suite
    }
    //  ajout = new AjoutPersonne(this);
      //ajout->setModal(true);
      //connect(ajout, SIGNAL(valider(Personne)), this, SLOT(valider(Personne)));
      //ajout->exec();
}

void MainWindow::valider(Personne data)
{
    data.id = num;
    tab.push_back(data);
    num++;
}

void MainWindow::reception_liste(std::vector<Personne> data, int num, std::vector<Sondage> data2, QString path)
{
    this->num = num;
    tab = data;
    tab_sondages = data2;
    this->path = path;
}

void MainWindow::on_actionNouveauSondage_triggered()
{
    AuBonLait *aubonlait = new AuBonLait(this);
    aubonlait->show();
}

void MainWindow::on_actionSauvegarder_triggered()
{

  //  QString filename = QFileDialog::getSaveFileName(0, "Sauvegarde d'une personne","/home","Text files (*.txt)", 0,0);

   // std::ofstream fs(this->filename.toStdString().c_str(), std::ios::out | std::ios::app);
     std::ofstream fs(path.toStdString().c_str(), std::ios::out);
     //   std::ofstream fs("/home/marine/Documents/S6/IHM/test2.txt", std::ios::out | std::ios::app);

     //Partie personne
     Personne personne;
     personne.age = ui->txtbox_age_2->text().toInt();
     personne.nb_personnes = ui->spbox_nb_personnes_2->text().toInt();
     personne.nb_enfants = ui->spbox_enfants_2->text().toInt();
     personne.nb_animaux = ui->spbox_animaux_2->text().toInt();
     personne.etat_civil = ui->cb_etat_civil_2->currentText();
     int pos_revenu = ui->cb_revenu_2->currentIndex();
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

     if(ui->rdb_homme_2->isChecked())
     {
         personne.sexe = "homme";
     }
     else
     {
         personne.sexe = "femme";
     }

     if(personne.age == 0)
     {
         ui->lbl_warning_2->setText("<font color='red'>âge incorrect</font>");
         ui->lbl_warning_2->show();
     }
     else if(personne.nb_personnes < personne.nb_enfants || personne.nb_personnes == 0)
     {
         ui->lbl_warning_2->setText("<font color='red'>nombre de personnes incorrecte</font>");
     }
     else
     {
         ui->lbl_warning_2->hide();
    }



    //partie sondage
     Sondage sondage;
     QModelIndexList list =ui->listview_marques_connues->selectionModel()->selectedIndexes();
     QStringList slist;
     foreach(const QModelIndex &index, list){
         slist.append( index.data(Qt::DisplayRole ).toString());
     }
     for(int i=0; i< slist.size(); i++)
     {
         sondage.tab_marques_connues.push_back(slist.at(i));
     }
    sondage.nb_marques_connues =slist.size();
    list = ui->listview_marques_achetees->selectionModel()->selectedIndexes();
    slist.clear();
    foreach(const QModelIndex &index, list){
        slist.append((index.data(Qt::DisplayRole).toString()));
    }
    for(int i=0; i<slist.size(); i++)
    {
        sondage.tab_marques_achetees.push_back(slist.at(i));
    }
    sondage.nb_marques_achetees = slist.size();
    sondage.frequence = ui->cb_frequence->currentText();

    for(int i=0; i< ui->grid_types->count(); i++)
    {
        QLayoutItem * const item = ui->grid_types->itemAt(i);
        QWidget* widget = ui->grid_types->itemAt(i)->widget() ;
        QCheckBox *checkbox = qobject_cast<QCheckBox*>(widget);
        if (checkbox) {
            if(checkbox->isChecked())
            {
                sondage.tab_types.push_back(checkbox->text());
            }
        }
    }

    sondage.nb_type = sondage.tab_types.size();

    //suite partie personne
    if((pos_personne_sel ==0 && tab.size()==0)|| pos_personne_sel == tab.size())
    {
        num++;
        personne.id = num;
        tab.push_back(personne);
        sondage.id_p = num;
        tab_sondages.push_back(sondage);
    }
    else
    {
        personne.id = tab[pos_personne_sel].id;
        tab[pos_personne_sel] = personne;
        sondage.id_p = personne.id;
        tab_sondages[pos_personne_sel] =sondage;
    }


    for(int i=0; i<num;i++)
    {

        fs << tab[i].id;
        fs << ",";
        fs << tab[i].age;
        fs << ",";
        fs << tab[i].sexe.toStdString();
        fs << ",";
        fs << tab[i].etat_civil.toStdString();
        fs << ",";
        fs << tab[i].nb_personnes;
        fs << ",";
        fs << tab[i].nb_enfants;
        fs << ",";
        fs << tab[i].nb_animaux;
        fs << ",";
        fs << tab[i].min_revenu;
        fs << ",";
        fs << tab[i].max_revenu;
        fs << ",";
        fs << tab_sondages[i].nb_marques_connues;
        fs << ",";
        int t = tab_sondages[i].nb_marques_connues;
        for(int j = 0; j<tab_sondages[i].nb_marques_connues; j++)
        {
            QString s = tab_sondages[i].tab_marques_connues[j];
            fs << tab_sondages[i].tab_marques_connues[j].toStdString();
            fs << ",";
        }
        fs << tab_sondages[i].nb_marques_achetees;
        fs << ",";
        for(int j=0; j< tab_sondages[i].nb_marques_achetees; j++)
        {
            fs << tab_sondages[i].tab_marques_achetees[j].toStdString();
            fs << ",";
        }
        fs << tab_sondages[i].frequence.toStdString();
        fs << ",";
        fs << tab_sondages[i].nb_type;
        fs << ",";
        for(int j =0; j<tab_sondages[i].nb_type; j++)
        {
            fs << tab_sondages[i].tab_types[j].toStdString();
            fs << ",";
        }


        fs <<std::endl;
    }


}



void MainWindow::on_actionGestion_triggered()
{
    QStringListModel *model = new QStringListModel(this);
    QStringList list;

    //for (liste_personnes::iterator it=liste_personnes.begin(); it != liste_personnes.end(); ++it)
  //      std::cout << ' ' << *it;
    for(int i = 0; i< num; i++)
    {
        Personne p = tab[i];
        list.append(QString::number(tab[i].id));
    }
    model->setStringList(list);

    gestionsondes = new GestionSondes(this);

    connect(gestionsondes, SIGNAL(valider_choix_id(int)), this,SLOT(reception_choix_id(int)));
    gestionsondes->setListe(model);
    this->setWindowModality(Qt::NonModal);
    gestionsondes->show();


}

void MainWindow::on_actionOuvrir_triggered()
{
 /*   QStringListModel *model = new QStringListModel(this);
    QStringList list;

 //   int age = liste_personnes.front().age;
    //for (liste_personnes::iterator it=liste_personnes.begin(); it != liste_personnes.end(); ++it)
  //      std::cout << ' ' << *it;
    for(int i = 0; i< num; i++)
    {
        Personne p = tab[i];
        list.append(QString::number(tab[i].id));
    }
    model->setStringList(list);
    gestionsondes = new GestionSondes(this);


    gestionsondes->setListe(model);
    gestionsondes->setModal(true);
    gestionsondes->exec();*/
}

void MainWindow::reception_choix_id(int id)
{
    Personne p;
    Sondage s;
    for(int i=0; i<num;i++)
    {
        if(tab[i].id == id) //unique
        {
            p = tab[i]; //on récupère la bonne personne en fonction de l'id
            pos_personne_sel = i;
            break;
        }
    }
    for(int i=0; i< num; i++)
    {
        if(tab_sondages[i].id_p == id)
        {
            s = tab_sondages[i];
            pos_sondage_sel = i;
            break;
        }
    }
   //partie personne
    ui->txtbox_age_2->setText(QString::number(p.age));
    if(p.sexe == "femme")
    {
        ui->rdb_femme_2->setChecked(true);
      //  ui->rdb_homme_2->setChecked(false); nécessaire?
    }
    else
    {
        ui->rdb_homme_2->setChecked(true);
        //ui->rdb_femme_2->setChecked(false); nécessaire?
    }
    ui->lbl_warning_2->setText("hello");
    ui->cb_etat_civil_2->setCurrentText(p.etat_civil);
    ui->spbox_nb_personnes_2->setValue(p.nb_personnes);
    ui->spbox_enfants_2->setValue(p.nb_enfants);
    ui->spbox_animaux_2->setValue(p.nb_animaux);
    switch (p.min_revenu) {
    case 10000:
        ui->cb_revenu_2->setCurrentIndex(0);
        break;
    case 25000:
        ui->cb_revenu_2->setCurrentIndex(1);
        break;
    case 70000:
        ui->cb_revenu_2->setCurrentIndex(2);
        break;
    default:
        ui->cb_revenu_2->setCurrentIndex(3);
        break;
    }

    //partie sondage
    QAbstractItemModel* model = ui->listview_marques_connues->model() ;

    for( int i = 0 ; i < model->rowCount();i++ )
    {
       for(int k=0;k<model->columnCount(); k++)
       {
           if(i==2)
           {
               int e =0;
           }
           for(int j=0; j<s.tab_marques_connues.size(); j++)
           {
               if(model->itemData(model->index(i,k)).first().toString() == s.tab_marques_connues[j])
               {
                   //on select
                   ui->listview_marques_connues->selectionModel()->select(model->index(i,k), QItemSelectionModel::Select);
               }
           }
           //partie achetee
           for(int j=0; j<s.tab_marques_achetees.size(); j++)
           {
               if(model->itemData(model->index(i,k)).first().toString() == s.tab_marques_achetees[j])
               {
                   ui->listview_marques_achetees->selectionModel()->select(model->index(i,k), QItemSelectionModel::Select);
               }
           }
       }
    }
    ui->cb_frequence->setCurrentText(s.frequence);
    //test
    QList<QCheckBox*> allCheckBoxes = findChildren<QCheckBox*>();
    foreach(QCheckBox *checkBox, allCheckBoxes)
        if(std::find(s.tab_types.begin(), s.tab_types.end(), checkBox->text()) != s.tab_types.end())
        {
            checkBox->setChecked(true);
        }

    //fin test
  /*  for(int i=0; i< ui->grid_types->count(); i++)
    {
        QLayoutItem * const item = ui->grid_types->itemAt(i);
        QWidget* widget = ui->grid_types->itemAt(i)->widget() ;
        QCheckBox *checkbox = qobject_cast<QCheckBox*>(widget);

        for(int j=0; j<s.tab_types.size(); j++)
        {
            if (checkbox) {
                if(checkbox->text() == s.tab_types[j])
                {
                    checkbox->setChecked(true);
                    ui->grid_types->replaceWidget(checkbox,ui->grid_types->itemAt(i)->widget());
                }
            }
        }

    }*/

    ui->tabprincipal->show();
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}
