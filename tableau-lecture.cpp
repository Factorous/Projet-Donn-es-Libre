#include <stdexcept>
/** @file **/
#include <fstream>
#include <sstream>
#include "tableau-lecture.h"


vector<vector<string>> litTableau(string nom_fichier, int nb_colonnes) {
    vector<vector<string>> a_return;
    
    ifstream file;
    file.open(nom_fichier);
    
    string premierecolonne = "";
        
    while(file >> premierecolonne){
        vector<string> liste = {premierecolonne};
        string valeur = "";
        
        for (int i = 1; i < nb_colonnes; i++){
            file >> valeur;
            liste.push_back(valeur);
        }
        a_return.push_back(liste);
    };

    file.close();
    return a_return;
}
