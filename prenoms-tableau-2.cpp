#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include "tableau-donnees.h"
#include "tableau-lecture.h"
using namespace std;

//Auteur: Fabio (Victor a copié le code de Fabio dans ce fichier)
//J'ai confiance en ce code
/**
 * Demande à l'utilisateur un prénom et calcule
 * - le nombre de garçons et filles à qui l'on a donné ce prénom
 * - la meilleure année pour ce prénom pour les garçons et filles
 **/
int main() {
    // Lecture du tableau
    vector<vector<string>> tbl = litTableau("donnees/liste_des_prenoms.txt", 4);
        
    // Nombres de naissances
    int nb_naissances = 0;
    vector<int> naissance_tbl = conversionInt(colonne(tbl, 3));
        
    for(int i = 0; i < naissance_tbl.size(); i++){
        nb_naissances += naissance_tbl[i];
    }
    
    cout << "Nombre de naissances : " << nb_naissances << endl;
    
    // Prénom
    string name = "";
    cout << "Choississez un prénom : ";
    cin >> name;
        
    // Tableau avec TOUT les valeurs du nom
    // On réutilise la variable, on a plus besoin de TOUT le tableau
    tbl = selectLignes(tbl, 2, name);
        
    // On trie par sexe
    vector<vector<string>> m_tbl = selectLignes(tbl, 0, "M");
    vector<vector<string>> f_tbl = selectLignes(tbl, 0, "F");
        
    // Puis par naissances
    vector<int> m_trie_annee = conversionInt(colonne(m_tbl, 3));
    vector<int> f_trie_annee = conversionInt(colonne(f_tbl, 3));
        
    // Nombre naissances : homme
    int m_totalnum = 0;
    int m_best_index = -1;
        
    for(int i = 0; i < m_trie_annee.size(); i++){
        m_totalnum += m_trie_annee[i];
        if (m_trie_annee[m_best_index] <= m_trie_annee[i]){
            m_best_index = i;
        };
    };
        
    // Nombre naissances : femme
    int f_totalnum = 0;
    int f_best_index = -1;
        
    for(int i = 0; i < f_trie_annee.size(); i++){
        f_totalnum += f_trie_annee[i];
        if (f_trie_annee[f_best_index] <= f_trie_annee[i]){
            f_best_index = i;
        };
    };
    
    // Vérifions le nombre
    if (f_totalnum > 0 or m_totalnum > 0) {
        if (m_tbl.size() > 0){
            cout << endl << "Le prénom " << name << " a été donné à " << m_totalnum << " garçons entre 2004 et 2019" << endl;
            cout << "L'année la plus forte est " << m_tbl[m_best_index][1] << " avec " << m_trie_annee[m_best_index] << " enfants" << endl;
        };
        
        if (f_tbl.size() > 0){
            cout << endl << "Le prénom " << name << " a été donné à " << f_totalnum << " filles entre 2004 et 2019" << endl;
            cout << "L'année la plus forte est " << f_tbl[f_best_index][1] << " avec " << f_trie_annee[f_best_index] << " enfants" << endl;
        };
        
    } else {
        cout << endl << "Ce prénom ne fut jamais donné" << endl;
    }
}