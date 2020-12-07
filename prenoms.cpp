#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


/** Calcule et affiche le prénom le plus utilisé une année donnée
 * ainsi que le nombre de naissances cette année là **/
// Auteur : Fabio
// Je suis confiant dans ce code, l'output est exactement le même que celui demandé
// J'ai néanmoins un doute sur l'input/cin, au cas où il mets une chose différente d'un nombre

int main() {
    int ask_annee = 2009, max_enfants = 0, total_enfants = 0;
    string max_enfants_nom = "";
    
    cout << "Entrez une année" << endl;
    cin >> ask_annee;
    
    ifstream file;
    file.open("donnees/liste_des_prenoms.txt");

	if (!file) {
		cout << "Problème à l'ouverture" << endl;
		return 1;
	};
    
    // On mets dans rien, car on s'en fiche du sexe 
    string rien = "", file_nom_enfant = "";
    int file_annee = 0, file_nb_naissances = 0;
    
    while(file >> rien >> file_annee >> file_nom_enfant >> file_nb_naissances){
        if(file_annee == ask_annee){
            total_enfants += file_nb_naissances;

            if(max_enfants < file_nb_naissances){
                max_enfants_nom = file_nom_enfant;
                max_enfants = file_nb_naissances;
            }
        }
    }
    
    cout << "Il y a eu " << total_enfants << " naissances en " << ask_annee << endl;
    cout << "Le prénom le plus donné est " << max_enfants_nom << " pour ( " << max_enfants << " naissances )" << endl;
    file.close();
}
