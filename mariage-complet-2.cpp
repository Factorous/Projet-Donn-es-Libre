#include <stdexcept>
/** @file **/
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "tableau-donnees.h"
#include "tableau-lecture.h"
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<string> annees = {"2010", "2011", "2012", "2013", "2014", "2015"};
vector<string> jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};

//Auteur: Victor Robert (j'ai ajouté un message d'erreur au cas où l'utilisateur entre un entier négatif)
/** Construction d'un tableau à une dimension vide
    *@param taille, un entier qui représente la taille du tableau
    *@return un tableau d'entier de taille: taille, qui est initialisé avec des 0.
**/
vector<int> creerTableauVide(int taille){
    if (taille<0){
        throw runtime_error("Il faut entrer un entier positif.");
    }
    vector<int> Tableauvide(taille);
    for (int i = 0; i < taille; i++){
        Tableauvide[i] =0;
    }
    return Tableauvide;
}

//Auteur: Victor Robert
//J'ai confiance en ce code
/** Construction du tableau des mariages par années à partir d'un
 * tableau de données 2D (de chaines de caractères)
 * Chaque ligne contient : l'année, le jour, puis le nombre de mariages
 * @param t un tableau de données 2D de chaines de caractère
 * @return un tableau d'entiers tel que dans chaque
 * case d'indice i, on trouve le nombre total de mariages de l'année 2010+i
 **/
vector<int> creeTableauAnnee(vector<vector<string>> data) {
    vector<int> resultat = creerTableauVide(data.size());
    int indiceAnnee = 0;
    string annee;
    int r = 0;
    for (int i = 0; i < data.size();i++){
        annee = data[i][0];
        for(int j=0; j < annees.size(); j++) {
            if (annee == annees[j]) {
                indiceAnnee = j;
            }
        }
        istringstream flux = istringstream(data[i][2]); 
        flux >> r;
        resultat[indiceAnnee] += r;
    }
    return resultat;
}


/** Test de la fonction CreeTableauAnnee **/
void testCreeTableauAnnee() {
    vector<vector<string>> data = litTableau("donnees/statistiques-des-jours-des-mariages.txt", 3);
    vector<int> t = creeTableauAnnee(data);
    ASSERT(t[0] == 9195); // Nombre de mariages en 2010
    ASSERT(t[3] == 9443); // Nombre de mariages en 2013
    ASSERT(t[5] == 9046); // Nombre de mariages en 2015
}

//Auteur: Victor Robert
//J'ai confiance en ce code
/** Renvoie le numéro du jour correspondant à la chaîne de caractères
 * @param jour une chaine de caractères contenant un jour de la semaine (première lettre en majuscule)
 * @return un numéro entre 0 et 6 correspondant au jour de la semaine ou
 * -1 si le jour n'est pas valide
 **/
int indiceJour(string jour) {
    for(int i=0; i < jours.size(); i++) {
        if (jour == jours[i]) {
            return i;
        }
    }
    return -1;
}

void testIndiceJour() {
    ASSERT(indiceJour("Lundi") == 0);
    ASSERT(indiceJour("Samedi") == 5);
    ASSERT(indiceJour("Dimanche") == 6);
    ASSERT(indiceJour("samedi") == -1);
}

/** Construction du tableau des mariages à partir d'un
 * tableau de données 2D (de chaines de caractères)
 * suivi d'un jour, puis d'un nombre de mariages
 * Chaque ligne contient : l'année, le jour, puis le nombre de mariages
 * @param t un tableau de données 2D de chaines de caractère
 * @return un tableau d'entiers tel que dans chaque
 * case d'indice i, on trouve le nombre total de mariages célébrés le jour i
 **/
vector<int> creeTableauJours(vector<vector<string>> data) {
    vector<int> resultat = creerTableauVide(data.size());
    string jour;
    int r = 0;
    for (int i = 0; i < data.size();i++){
        jour = data[i][1];
        istringstream flux = istringstream(data[i][2]); 
        flux >> r;
        resultat[indiceJour(jour)] += r;
    }
    return resultat;
}

/** Test de la fonction litTableauJours **/
void testCreeTableauJours() {
    vector<vector<string>> data = litTableau("donnees/statistiques-des-jours-des-mariages.txt", 3);
    vector<int> t = creeTableauJours(data);
    ASSERT(t[0] == 4171); // Nombre de mariages le lundi
    ASSERT(t[3] == 4393); // Nombre de mariages le jeudi
    ASSERT(t[6] == 2); // Nombre de mariages le dimanche
}

//Auteur: Victor Robert
//On execute les tests.
/** Lance les fonctions de test puis affiche :
 * - le nombre total de mariages
 * - le nombre moyen de mariages célébrés par an
 * - l'année où l'on a célébré le plus de mariages (et leur nombre)
 * - le jour de la semaine où l'on célèbre le plus de mariages (et leur nombre)
 * - le pourcentage de mariages célébrés un samedi
 **/
int main() {
    testCreeTableauAnnee();
    testIndiceJour();
    testCreeTableauJours();
    
    return 0;
}
