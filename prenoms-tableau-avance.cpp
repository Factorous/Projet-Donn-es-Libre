#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include "tableau-lecture.h"
#include "tableau-donnees.h"
#include "tableau-donnees-avance.h"
using namespace std;


/**
 * Calcule et affiche :
 * - le nombre total de naissances de garçons et de naissances de filles
 * - l'année qui a eu le plus de naissances (garçons et filles confondus), avec leur nombre
 * - le nombre de naissances en moyenne par an
 * - les nombres de prénoms féminins et masculins différents
 * - le prénom masculin et le prénom féminin le plus populaire
 **/
int main() {
    vector<vector<string>> data = litTableau("donnees/liste_des_prenoms.txt", 4);

    auto m_list = selectLignes(data, 0, "M");
    auto f_list = selectLignes(data, 0, "F");
    auto annees = distinct(data, 1);
    
    vector<int> garcon_annee_naissances = groupBy<int>(m_list, annees, 1, 3);
    vector<int> fille_annee_naissances = groupBy<int>(f_list, annees, 1, 3);
    vector<int> confondu = groupBy<int>(data, annees, 1, 3);
    
    
    cout << "Il y a eu " << somme(garcon_annee_naissances) << " naissances de garçons et "
         << somme(fille_annee_naissances) << " naissances de filles" << endl;
    
    
    int best_index = indiceMax(confondu);
    cout << "L'année avec le plus de naissances est : " << annees[best_index]
         << " avec " << confondu[best_index] << " naissances" << endl;
    
    
    cout << "En moyenne, naissent " << moyenne(confondu) << " enfants par an" << endl;
    
    // les nombres de prénoms féminins et masculins différents
    vector<string> nombre_prenom_m = distinct(m_list, 2);
    vector<string> nombre_prenom_f = distinct(f_list, 2);
    
    cout << "Il y a eu " << nombre_prenom_f.size() << " prénoms de filles différentes et "
         << nombre_prenom_m.size() << " prénoms de garçons différents" << endl;
    
    
    // le prénom masculin et le prénom féminin le plus populaire
    vector<int> m_list_regrouper = groupBy<int>(m_list, nombre_prenom_m, 2, 3);
    vector<int> f_list_regrouper = groupBy<int>(f_list, nombre_prenom_f, 2, 3);
    
    int meilleurindex_f = indiceMax(f_list_regrouper);
    int meilleurindex_m = indiceMax(m_list_regrouper);
    
    cout << "Le prénom féminin le plus populaire est " << nombre_prenom_f[meilleurindex_f] << " avec "
         << f_list_regrouper[meilleurindex_f] << " naissances" << endl;
    
    cout << "Le prénom masculin le plus populaire est " << nombre_prenom_m[meilleurindex_m] << " avec "
         << m_list_regrouper[meilleurindex_m] << " naissances" << endl;
}
