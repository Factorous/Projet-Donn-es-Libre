#include <stdexcept>
/** @file **/
#include <iostream>
#include <fstream>
#include <sstream>
#include "tableau-lecture-csv.h"

// Il a été testé, et j'ai vérifié que la logique était correcte avec le briser_la_glace
// Je suis assez confiant.
// Auteur : Fabio
vector<vector<string>> litTableauCSV(string nom_fichier, int nb_colonnes) {
    vector<vector<string>> a_return;
    
    ifstream file(nom_fichier);
    string entete = "";
    getline(file, entete);
        
    while(file) {
        vector<string> liste = {};
        string valeur;
        
        // -1 à nb_colonnes car on ignore la dernière
        for (int i = 0; i < nb_colonnes-1; i++){
            getline(file, valeur, ';');
            
            liste.push_back(valeur);
        }
        
        // Vu que les lignes ne finissent pas par ';', on récupère ce qui reste de la ligne
        getline(file, valeur);

        // C'est une valeur qui n'est pas "vide" et la fin est \r ?
        if (valeur.size() > 0 and valeur[valeur.length()-1] == '\r'){
            // Alors on retire ce vilain /r
            valeur.resize(valeur.length() - 1);
        }
        liste.push_back(valeur);
        
        // Il reste à lire dans le fichier ? Si non, il faut ignorer la dernière ligne qu'on a lu
        if(file)
            a_return.push_back(liste);
    };
    
    if (nom_fichier == "donnees/donnees-test.csv"){
        ofstream ok;
        ok.open("test.txt");
        for(int i = 0; i < a_return.size(); i++){
            ok << "Index " << i << " : ";
            for(int j = 0; j < a_return[i].size(); j++){
                ok << a_return[i][j] << " ";

                if(i == 6 and j == 4){
                    cout << endl << endl << a_return[i][j].length() << endl;
                };
            }
            ok << "\n";
        };
        ok.close();
    }
    

    file.close();
    return a_return;
}

// Il a été testé, et j'ai vérifié que la logique était correcte avec le briser_la_glace
// Je suis assez confiant.
// Auteur : Fabio
vector<vector<string>> litTableauCSV(string nom_fichier) {
    vector<vector<string>> a_return;
    
    string entete = "", ligne;
    ifstream file(nom_fichier);
    getline(file, entete);
    
    // Mécanisme : On va récupérer la ligne, et lire l'intérieur de la ligne, au lieu de lire "partie par partie" de la phrase direct
    while(getline(file, ligne)){
        
        // On transforme en flux, pour pouvoir utiliser les fonctions getline
        istringstream stream_ligne(ligne);
        vector<string> liste = {};
        string ligne_content;
        
        while(getline(stream_ligne, ligne_content, ';')){
            if (ligne_content[ligne_content.length()-1] == '\r'){
                ligne_content.resize(ligne_content.length() - 1);
            }
            liste.push_back(ligne_content);
        }
        
        // Il reste à lire dans le fichier ? Si non, il faut ignorer la dernière ligne qu'on a lu
        if(file)
            a_return.push_back(liste);
    };

    file.close();
    return a_return;
}



