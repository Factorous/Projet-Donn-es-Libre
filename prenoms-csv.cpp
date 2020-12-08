#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;



//Auteur: Victor Robert
//J'ai confiance en ce code, j'aurais peut être pu implémenter des fonctions à la place de tout mettre dans main pour que ce soit un peu plus lisible mais le code fonctionne bien 
/** Calcule et affiche le prénom le plus donné une année donnée
 * ainsi que le nombre de naissance cette année là **/
int main() {
    ifstream fichier("donnees/liste_des_prenoms.csv");
    int annee;
    if (!fichier){
        throw runtime_error("fichier n'a pas pu s'ouvrir");
    }
    //On demande l'année souhaitée à l'utilisateur
    cout << "Année donnée:";
    cin >> annee;
    
    //On "retire" la première ligne
    string entete;
    getline(fichier,entete);
    
    string Nombre1;
    string ML;
    string AnneeLigne;
    string prenom;
    string Nombre2;
    
    int EntierAnneeLigne;
    
    int nombreDeNaissances=0;
    int NaissancesLigne;
    vector<string> Noms;
    
    while (true){
        getline(fichier,Nombre1,';');
        getline(fichier,ML,';');
        getline(fichier,AnneeLigne,';');
        getline(fichier,prenom,';');
        getline(fichier,Nombre2,'\n');
        
        istringstream(AnneeLigne) >> EntierAnneeLigne;
        if (EntierAnneeLigne==annee){
            //cout << Nombre1 << " " << ML << " "<<AnneeLigne << " " << prenom<< " " << Nombre2<< endl;
            istringstream(Nombre2) >> NaissancesLigne;
            nombreDeNaissances += NaissancesLigne;
            for (int i = 0; i < NaissancesLigne; i++){
            Noms.push_back(prenom);}
            
        }
        //si on arrive à la fin du fichier on quitte la boucle principale
        if (fichier.eof()) break;
        
        
    }
    
    //On compte maintenant le prénom qui apparait le plus souvent
    int maxNom = -1;
    int nombre;
    string NomQuiApparaitLePlus;
    for (string nom1: Noms){
        nombre = 0;
        for (string nom2 : Noms){
            if (nom1 == nom2){
                nombre ++;
            }
            
            if (nombre > maxNom){
                maxNom = nombre;
                NomQuiApparaitLePlus = nom2;
            }
            
        }
    }
    
    //affichage
    cout << "Il y a eu " << nombreDeNaissances << " nombre de naissances pendant l'année " << annee<< endl;
    cout << "Le nom qui apparait le plus est " << NomQuiApparaitLePlus << ". Il apparait " << maxNom<< " fois." << endl;
    
    fichier.close();
}
