#include <stdexcept>
/** @file **/
#include <fstream>
#include <sstream>
#include "tableau-donnees-avance.h"
#include <iostream>

// Auteur : Fabio, confiant pour ce code, c'est un for simple, y'a une valeur return dans tout les cas, et testé
int chercheIndice(vector<string> t, string valeur) {
    for(int i = 0; i < t.size(); i++){
        if (valeur == t[i]){
            return i;
        }
    }
    return -1;
}

// Auteur : Fabio, confiant pour ce code, il est testé, et n'est pas plus complexe que cela, 2 for
vector<string> distinct(vector<vector<string>> data, int j) {
    vector<string> tri;
    
    // On trie
    for(int i = 0; i < data.size(); i++){
        tri.push_back(data[i][j]);
    };
    
    vector<string> vec_final;
    
    // On vérifie si cette variable est déjà dans le vecteur vec_final, si oui on fait rien, si non alors on ajoute
    for(int i = 0; i < tri.size(); i++){
        if(chercheIndice(vec_final, tri[i]) == -1){
            vec_final.push_back(tri[i]);
        }
    }
    
    return vec_final;
}

// Auteur : Fabio, je suis mitigé, je ne suis pas à l'aise avec les istringstream, mais le code à été testé donc je suis confiant, néanmoins je pense qu'il peut y avoir un problème, si le stringstream renvoie des valeurs incompatibles avec le T
template<class T>
vector<T> conversion(vector<string> t) {
    vector<T> a_return;
    
    istringstream flux;
    
    for(int i = 0; i < t.size(); i++){
        flux = istringstream(t[i]);
        
        T var;
        T total = 0;
        while(flux >> var){
            total += var;
        }
        a_return.push_back(total);
    }
    return a_return;
}

template<class T>
// Auteur : Fabio, confiant pour ce code, il est testé, et n'est pas plus complexe que cela, 2 for
vector<T> groupBy(vector<vector<string>> data, vector<string> valeurs, int j1, int j2) {
    // data = pack de données
    // valeurs = On regroupe en rapport à ces valeurs
    // j1 = colonne où on doit comparer aux variables valeurs 
    // j2 = colonne qu'on doit additionner si y'a un valeurs == j1 en résumé.
    
    vector<string> vec;
    
    for(int i = 0; i < valeurs.size(); i++){
        vec.push_back("");
    };
    
    for(int i = 0; i < data.size(); i++){
        // Vérifier si à la colonne j1, sa variable est compris dans le vecteur valeurs
        int check_index = chercheIndice(valeurs, data[i][j1]);
            
        if(check_index != -1){
            vec[check_index] += (" " + data[i][j2]);
        }
    }
    
    // Convertir vec (string) en final_vec ( T )
    vector<T> final_vec = conversion<T>(vec);
    
    // On le convertis dans le bon type
    return final_vec;
}

// Force l'instanciation des templates
template vector<int> conversion<int>(vector<string> t);
template vector<double> conversion<double>(vector<string> t);
template vector<int> groupBy<int>(vector<vector<string>> data, vector<string> valeurs, int j1, int j2);
template vector<double> groupBy<double>(vector<vector<string>> data, vector<string> valeurs, int j1, int j2);
