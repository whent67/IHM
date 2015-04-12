#ifndef AJOUTPERSONNE_H
#define AJOUTPERSONNE_H

#include <QDialog>
#include <QAbstractButton>
#include "personne.h"

namespace Ui {
class AjoutPersonne;
}

class AjoutPersonne : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutPersonne(QWidget *parent = 0);
    ~AjoutPersonne();


    Personne personne;

private slots:

    void on_pushButton_clicked();
signals:
    void valider(Personne data);
private:
    Ui::AjoutPersonne *ui;
};

#endif // AJOUTPERSONNE_H
