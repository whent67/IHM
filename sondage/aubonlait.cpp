#include "aubonlait.h"
#include "ui_aubonlait.h"

AuBonLait::AuBonLait(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuBonLait)
{
    ui->setupUi(this);

    // Create model
    model = new QStringListModel(this);
    // Make data
    QStringList List;
    List << "Danone" << "Yoplait" << "Leader-price" << "Carrefour" << "Paturages" << "Auchan" << "Activia" << "Nestle" << "U" << "Milbona" << "Casino" << "Dia" << "Mamie-nova" << "Sojasun" << "Sveltesse";
    // Populate our model
    model->setStringList(List);
    // Glue model and view together
    ui->listView->setModel(model);
    ui->listView_2->setModel(model);
  //  ui->gridLayout_4->ch
}

AuBonLait::~AuBonLait()
{
    delete ui;
}
