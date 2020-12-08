#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


//Auteur: Victor Robert
//J'ai confiance en ce code

/** Calcule et affiche le nombre total de mariages célébrés entre 2010 et 2015 **/
int main() {
    string nomFichier = "donnees/statistiques-des-jours-des-mariages.txt";
    int sommeMariages = 0;
    int annee, nombreMariages;
    string Jour;
    ifstream fichier;
    fichier.open(nomFichier);
    if (fichier)//si le fichier a pu être ouvert
    {
    
    while (fichier>> annee,fichier>>Jour,fichier>>nombreMariages){
        if (annee >= 2010 and annee <= 2015){
            sommeMariages += nombreMariages;
        }
    }
    }
    else{
        throw runtime_error("Le fichier n'a pas pu être ouvert!");
        return 0;
    }
    cout << "Nombre total de mariages entre 2010 et 2015 " << sommeMariages << endl;
    fichier.close();
    return 0;
}
