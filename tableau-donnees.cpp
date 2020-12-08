#include <stdexcept>
/** @file **/
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "tableau-donnees.h"


//Auteur: Victor Robert
//J'ai confiance en ce code: affichage normal d'un tableau
void afficheTableau(vector<vector<string>> tableau) {
    for (int i= 0; i< tableau.size(); i++){
        for (int j = 0; j<tableau[i].size();j++){
            cout << setw(2) << tableau[i][j] << " ";
        }
        cout << endl;
    }
    
}

//Auteur: Victor Robert
//J'ai confiance en ce code: moyenne simple, cette fois ci on n'engendre pas une erreur mais on renvoie 0, afin que le programme ne crash pas (inconvéniant de cette méthode: l'utilisateur du code ne saura pas pourquoi il obtient des données bizarres)
int moyenne(vector<int> t) {
    if (t.size()==0){
        return 0;
    }
    return somme(t)/t.size();
}

//Auteur: Victor Robert
//J'ai confiance en ce code: somme simple
int somme(vector<int> t) {
    int SommeTableau = 0;
    for (int i = 0; i < t.size(); i++){
        SommeTableau += t[i];
    }
    return SommeTableau;
}

//Auteur: Victor Robert
//J'ai confiance en ce code
int indiceMax(vector<int> t) {
    if (t.size() == 0){return -1;}
    int max_ = 0;
    for (int i = 1; i < t.size(); i++){
        if (t[i]>=t[max_]){max_=i;}
    }
    return max_;
}

//Auteur: Victor Robert
//J'ai confiance en ce code
vector<string> colonne(vector<vector<string>> t, int j) {
    vector<string> Col;
    for (int i = 0; i< t.size();i++){
        Col.push_back(t[i][j]);
    }
    return Col;
}

//Auteur: Victor Robert
//J'ai confiance en ce code, mais si l'utilisateur du code envoie un tableau du genre: {"3","7","a"}, le programme aura un problème: on peut remédier à cette situation en mettant un: try{stringstream valeur(t[i]);} catch {throw runtime_error("le tableau utilisé ne contient pas que des chiffres");}
vector<int> conversionInt(vector<string> t) {
    vector<int> resultat(t.size()); 
    for (int i =0; i < t.size();i++){
        stringstream valeur(t[i]);
        valeur >> resultat[i];
    }
    return resultat;
}

//Auteur: Victor Robert
//J'ai confiance en ce code
vector<vector<string>> selectLignes(vector<vector<string>> t, int j, string valeur) {
    vector<vector<string>> Lignes;
    for (int i = 0; i < t.size(); i ++){
        if (t[i][j]==valeur){Lignes.push_back(t[i]);}
    }
    return Lignes;
}
