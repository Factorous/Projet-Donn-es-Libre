#include <stdexcept>
/** @file **/
#include <iostream>
#include "tableau-donnees.h"
#include "tableau-lecture-csv.h"
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

/** Affiche le genre et l'espece de l'arbre le plus haut de Paris
 * parmi les "arbres remarquables"
 **/
int main() {
    ifstream fichier("donnees/arbresremarquablesparis.csv");
    string entete;
    getline(fichier,entete);
    
    
    vector<string> ligne(20);
    int especeDansTableau = 2;
    int genreDansTableau = 1;
    int hauteurDansTableau = 12;
    
    int hauteurMax = 0;
    int hauteur;
    string especeMax;
    string genreMax;
    while (true){
        for (int i = 0; i < ligne.size(); i++){
            if (i== ligne.size()-1){
                getline(fichier,ligne[i],'\n');
            }
            else {
                getline(fichier,ligne[i],';');
                }
        }
        istringstream(ligne[hauteurDansTableau]) >> hauteur;
        //cout << "arbre " << ligne[2]<<":"<< ligne[1] << " a une hauteur de " << hauteur << "m." << endl;
        if (hauteur>hauteurMax){
            hauteurMax = hauteur;
            especeMax = ligne[especeDansTableau];
            genreMax = ligne[genreDansTableau];
        }
        if (fichier.eof()){break;}
    }
    cout << "L'arbre le plus grand est l'espèce "<< especeMax << ", genre " << genreMax << " avec une hauteur de "<< hauteurMax << " mètres." << endl; 
}
