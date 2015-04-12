#include "gestionsondes.h"
#include "ui_gestionsondes.h"

GestionSondes::GestionSondes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GestionSondes)
{
    setWindowModality(Qt::ApplicationModal);
    ui->setupUi(this);
}

GestionSondes::~GestionSondes()
{
    delete ui;
}

void GestionSondes::setListe(QStringListModel *l)
{
    ui->list_sondes->setModel(l);
}

void GestionSondes::on_btn_ok_clicked()
{

    //QString ide << ui->list_sondes->model()->data(ui->list_sondes->currentIndex()).value;
    QModelIndexList list =ui->list_sondes->selectionModel()->selectedIndexes();

     QStringList slist;
     foreach(const QModelIndex &index, list){
         slist.append( index.data(Qt::DisplayRole ).toString());
     }

    int id = slist.at(0).toInt();
   // int id = listmodel.at(0).data().toInt();
    emit valider_choix_id(id);
    this->close();
}
