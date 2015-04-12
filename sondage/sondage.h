#ifndef SONDAGE_H
#define SONDAGE_H


class Sondage
{
public:
    int id_p;
   int nb_marques_connues;
   std::vector<QString> tab_marques_connues;
   int nb_marques_achetees;
   std::vector<QString> tab_marques_achetees;
   QString frequence;
   int nb_type;
   std::vector<QString> tab_types;
};


#endif // SONDAGE_H
