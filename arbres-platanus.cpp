#include <stdexcept>
/** @file **/
#include <iostream>
#include <vector>
#include <fstream>

#include "tableau-donnees.h"
#include "tableau-donnees-avance.h"
#include "tableau-lecture-csv.h"
using namespace std;

bool ElementDansTableau(vector<string> t, string el){
    
    for (int i = 0; i < t.size();i++){
        if (t[i]==el){return true;}
    }
    return false;
}


/** Affiche le nombre d'arbres du genre Platanus, et le nombre d'espèces
 *  différentes pour ce genre Platanus, parmi les "arbres remarquables" 
 **/
int main() {
    ifstream fichier("donnees/arbresremarquablesparis.csv");
    string entete;
    getline(fichier,entete);
    
    vector<string> ligne(20);
    int especeDansTableau = 2;
    int genreDansTableau = 1;
    
    int nombrePlatanus = 0;
    vector<string> EspecesDifferentes;
    
    while (true){
        for (int i = 0; i < ligne.size(); i++){
            if (i== ligne.size()-1){
                getline(fichier,ligne[i],'\n');
            }
            else {
                getline(fichier,ligne[i],';');
                }
        }
        if (ligne[genreDansTableau] == "Platanus"){
            nombrePlatanus ++;
            if (!ElementDansTableau(EspecesDifferentes,ligne[especeDansTableau])){
                EspecesDifferentes.push_back(ligne[especeDansTableau]);
            }
            
        }
        
        
        if (fichier.eof()){break;}
    }
    cout << "nombre d'arbres du genre platanus: " << nombrePlatanus << ". Nombre d'espèces différentes:" << EspecesDifferentes.size() << "."<< endl;
    fichier.close();
    
    
}
