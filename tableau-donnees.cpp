#include <stdexcept>
/** @file **/
#include <fstream>
#include <sstream>
#include "tableau-donnees.h"

void afficheTableau(vector<vector<string>> tableau) {
    for(int i = 0; i < tableau.size(); i++){
        for(int j = 0; j < tableau[i].size(); j++){
            cout << tableau[i][j];
        }
        cout << endl;
    }
}

int moyenne(vector<int> t) {
    int somme = 0;
    int check_count = 0;
    
    for(int i = 0; i < t.size(); i++){
        somme += t[i];
        ++check_count;
    };
    return somme/check_count;
}

int somme(vector<int> t) {
    int somme = 0;
    for(int i = 0; i < t.size(); i++){
        somme += t[i];
    };
    return somme;
}


int indiceMax(vector<int> t) {
    int index_max = 0;
    
    for(int i = 1; i < t.size(); i++){
        if (t[index_max] < t[i]){
            index_max = i;
        }
    }
    return index_max;
}

vector<string> colonne(vector<vector<string>> t, int j) {
    vector<string> a_return = {};
    
    for(int i = 0; i < t.size(); i++){
        a_return.push_back(t[i][j]);
    };
    return a_return;
}


vector<int> conversionInt(vector<string> t) {
    vector<int> resultat = vector<int>(t.size());
    for(int i =0; i < t.size(); i++) {
        istringstream(t[i]) >> resultat[i];
    }
    return resultat;
}

vector<vector<string>> selectLignes(vector<vector<string>> t, int j, string valeur) {
    vector<vector<string>> new_vec = {};
    
    for(int i = 0; i < t.size(); i++){
        if (t[i][j] == valeur)
            new_vec.push_back(t[i]);
    }
    return new_vec;
}
