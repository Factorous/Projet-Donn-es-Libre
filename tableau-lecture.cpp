#include <stdexcept>
/** @file **/
#include <fstream>
#include <sstream>
#include "tableau-lecture.h"

//Auteur: Victor Robert
//J'ai confiance en cette fonction, mais il faut faire confiance à l'utilisateur de la fonction:
//si il entre un mauvais nombre de colonnes le programme ne fonctionne plus
//aussi si le tableau n'est pas rectangulaire (si il n'a pas pour chaque ligne le même nombre de colonnes) on a un problème
vector<vector<string> > litTableau(string nom_fichier, int nb_colonnes) {
    ifstream fichier;
    vector<vector<string>> Tableau;
    vector<string> Ligne(nb_colonnes);
    string ligne;
    fichier.open(nom_fichier);
    int i = 0;
    if (fichier){
        while (fichier >> ligne){
            Ligne[i] = ligne;
            i++;
            if (i==nb_colonnes){
                i = 0;
                Tableau.push_back(Ligne);
            }

        }
    }
    else{
        throw runtime_error("Le fichier n'a pas pu être ouvert!");
        return {{""}};
    }
    fichier.close();
    return Tableau;
}
