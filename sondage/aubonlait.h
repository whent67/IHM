#ifndef AUBONLAIT_H
#define AUBONLAIT_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class AuBonLait;
}

class AuBonLait : public QDialog
{
    Q_OBJECT

public:
    explicit AuBonLait(QWidget *parent = 0);
    ~AuBonLait();

private:
    Ui::AuBonLait *ui;

    QStringListModel *model;
};

#endif // AUBONLAIT_H
