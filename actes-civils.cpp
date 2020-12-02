#include <stdexcept>
/** @file **/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "tableau-donnees.h"
#include "tableau-donnees-avance.h"
#include "tableau-lecture-csv.h"
using namespace std;




/** Affiche l'année avec le plus de naissances et l'année avec le plus de mariages
 **/
int main() {
    ifstream fichier("donnees/statistiques_de_creation_d_actes_d_etat_civil_par_arrondissement.csv");
    
    //les années vont de 2004 à 2015
    int anneeDebut = 2004;
    int anneeFin = 2015;
    
    vector<int> mariages(anneeFin-anneeDebut);
    vector<int> naissances(anneeFin-anneeDebut);
    
    
    
    string typeActe;
    string annee;
    int EntierAnnee;
    string arrondissement;
    string nombre;
    int EntierNombre;
    
    while (true){
        getline(fichier,typeActe,';');
        getline(fichier,annee,';');
        getline(fichier,arrondissement,';');
        getline(fichier,nombre,'\n');
        
        if (typeActe == "Mariages"){
            istringstream(annee) >> EntierAnnee;
            istringstream(nombre) >> EntierNombre;
            mariages[EntierAnnee-anneeDebut] += EntierNombre;
        }
        
        if (typeActe == "Naissances"){
            istringstream(annee) >> EntierAnnee;
            istringstream(nombre) >> EntierNombre;
            naissances[EntierAnnee-anneeDebut] += EntierNombre;
        }
        
        if (fichier.eof()){break;}
    }
    
    cout << "Année avec le plus de mariages: " << indiceMax(mariages)+2004 << endl;
    cout << "Année avec le plus de naissances: " << indiceMax(naissances)+2004 << endl;
    fichier.close();
}


