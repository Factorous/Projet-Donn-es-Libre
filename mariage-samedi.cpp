#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/** Calcule et affiche le nombre de mariages un samedi entre 2010 et 2015 **/
int main() {
    string nomFichier = "donnees/statistiques-des-jours-des-mariages.txt";
    ifstream fichier;
    fichier.open(nomFichier);
    int sommeMariages, nombreMariages, annee;
    sommeMariages = 0;
    string Jour;
    while (fichier >>annee, fichier>> Jour, fichier >> nombreMariages){
        if (annee >=2010 and annee <= 2015 and Jour=="Samedi"){
            sommeMariages += nombreMariages;
        }
    }
    cout << sommeMariages << endl;
    fichier.close();
    return 0;
}
