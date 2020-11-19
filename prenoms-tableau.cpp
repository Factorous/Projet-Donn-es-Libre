#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<vector<string>> tableauTest = {
    { "M", "2011", "Bubulle", "3"},
    { "F", "2012", "Bichette", "4"},
    { "F", "2011", "Babouche", "7"},
    { "F", "2011", "Ziboulette", "1"}
};

/** Affiche le contenu d'un tableau de chaînes à deux dimensions
 * @param tableau un tableau à deux dimensions
 **/
void afficheTableau(vector<vector<string>> tableau) {
    for(int i = 0; i < tableau.size(); i++){
        for(int j = 0; j < tableau[i].size(); j++){
            cout << tableau[i][j];
        }
        cout << endl;
    }
}

void testAfficheTableau() {
    afficheTableau(tableauTest);
}


/** Construction d'un tableau 2D de chaines de caractères lu depuis un fichier
 * @param fichier le nom d'un fichier contenant un nombre fixe
  * de colonnes séparées par des espaces
 * @param nb_colonnes le nombre de colonnes du fichier
 * @return un tableau de chaines de caractères à deux dimensions
 **/
vector<vector<string>> litTableau(string nom_fichier, int nb_colonnes) {
    vector<vector<string>> a_return;
    
    ifstream file;
    file.open(nom_fichier);
    
    string premierecolonne = "";
        
    while(file >> premierecolonne){
        vector<string> liste = {premierecolonne};
        string valeur = "";
        
        for (int i = 1; i < nb_colonnes; i++){
            file >> valeur;
            liste.push_back(valeur);
        }
        a_return.push_back(liste);
    };

    file.close();
    return a_return;
}

/** Test de la fonction litTableau **/
void testLitTableau() {
    ASSERT(litTableau("donnees/donnees-test.txt", 4) == tableauTest);
    vector<vector<string>> t = litTableau("donnees/liste_des_prenoms.txt", 4);
    ASSERT(t.size() == 20453);
    ASSERT(t[0][0] == "M");
    ASSERT(t[5][2] == "Aboubacar");
    ASSERT(t[6][3] == "7");
}

/** Extraction d'une colonne d'un tableau de données
 * @param t un tableau 2D de chaines de caractères
 * @param i un numéro de colonne
 * @return la colonne j, représentée par un vecteur de chaines de caractères
 **/
vector<string> colonne(vector<vector<string>> t, int j) {
    vector<string> a_return = {};
    
    for(int i = 0; i < t.size(); i++){
        a_return.push_back(t[i][j]);
    };
    return a_return;
}

/** Test de la fonction colonne **/
void testColonne() {
    ASSERT(colonne(tableauTest, 0) == vector<string>({"M","F","F","F"}));
    ASSERT(colonne(tableauTest, 1) == vector<string>({"2011","2012","2011","2011"}));
    ASSERT(colonne(tableauTest, 2) == vector<string>({"Bubulle","Bichette","Babouche","Ziboulette"}));
    ASSERT(colonne(tableauTest, 3) == vector<string>({"3","4","7","1"}));
}

/** Convertit un tableau de chaines de caractères en un tableau d'entiers
 * @param t, un vecteur de chaines de caractères
 * @return un vecteur d'entiers
 **/
vector<int> conversionInt(vector<string> t) {
    vector<int> resultat = vector<int>(t.size());
    for(int i =0; i < t.size(); i++) {
        istringstream(t[i]) >> resultat[i];
    }
    return resultat;
}

void testConversionInt() {
    ASSERT(conversionInt({}) == vector<int>({}));
    ASSERT(conversionInt({"1","2","3"}) == vector<int>({1,2,3}));
}

/** copier la fonction somme déjà écrite **/
int somme(vector<int> t) {
    int somme = 0;
    for(int i = 0; i < t.size(); i++){
        somme += t[i];
    };
    return somme;
}

/** copier la fonction moyenne déjà écrite **/
int moyenne(vector<int> t) {
    int somme = 0;
    int check_count = 0;
    
    for(int i = 0; i < t.size(); i++){
        somme += t[i];
        ++check_count;
    };
    return somme/check_count;
}

/** copier la fonction indiceMax déjà écrite **/
int indiceMax(vector<int> t) {
    int index_max = 0;
    
    for(int i = 1; i < t.size(); i++){
        if (t[index_max] < t[i]){
            index_max = i;
        }
    }
    return index_max;
}

/** Sélection des lignes d'un tableau de données
 * Sélectionne un ensemble de lignes en fonction d'un critère donné
 * @param t, un tableau contenant des lignes de données
 * @param j, l'indice de la colonne à vérifier
 * @param valeur, une chaine de caractères correspondant au critère
 * @return un tableau de données ne contenant que les lignes de t telles
 *  que la colonne j ait la valeur correspondant au critère
 **/
vector<vector<string>> selectLignes(vector<vector<string>> t, int j, string valeur) {
    vector<vector<string>> new_vec = {};
    
    for(int i = 0; i < t.size(); i++){
        if (t[i][j] == valeur)
            new_vec.push_back(t[i]);
    }
    return new_vec;
}

/** Test de la fonction selectLignes **/
void testSelectLignes() {
    ASSERT(selectLignes(tableauTest, 0, "M") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}}));
    ASSERT(selectLignes(tableauTest, 1, "2011") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}, { "F", "2011", "Babouche", "7"}, { "F", "2011", "Ziboulette", "1"}}));
}

/** Lance les tests de litTableau, selectLignes et colonne puis
 * affiche le nombre total de naissances puis
 * demande à l'utilisateur un prénom et calcule et affiche
 * - le nombre de garçons et filles à qui l'on a donné ce prénom
 * - la meilleure année pour ce prénom pour les garçons et filles
 **/
int main() {
    // test
    testLitTableau();
    testColonne();
    testSelectLignes();
    
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
