#ifndef GESTIONSONDES_H
#define GESTIONSONDES_H

#include <QDialog>
#include <QStringListModel>
namespace Ui {
class GestionSondes;
}

class GestionSondes : public QDialog
{
    Q_OBJECT

public:
    explicit GestionSondes(QWidget *parent = 0);
    ~GestionSondes();

    void setListe(QStringListModel *l);

private slots:
    void on_btn_ok_clicked();

signals:
    void valider_choix_id(int id);

private:
    Ui::GestionSondes *ui;
};

#endif // GESTIONSONDES_H
