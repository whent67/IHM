#ifndef CHARGEMENT_H
#define CHARGEMENT_H

#include <QDialog>
#include "personne.h"
#include "sondage.h"
#include <iostream>
#include <vector> //Ne pas oublier !
namespace Ui {
class Chargement;
}

class Chargement : public QDialog
{
    Q_OBJECT

public:

    explicit Chargement(QWidget *parent = 0);
    ~Chargement();



private slots:
    void on_btn_ok_clicked();

    void on_btn_nouveau_clicked();

    void on_btn_parcourir_clicked();


signals:
    void envoi_liste(std::vector<Personne> data, int num,std::vector<Sondage> data2, QString path);

private:
    Ui::Chargement *ui;
};

#endif // CHARGEMENT_H
