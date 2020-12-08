#include <stdexcept>
/** @file **/
#include <iostream>
#include "tableau-donnees.h"
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<vector<string>> tableauTest = {
    { "M", "2011", "Bubulle", "3"},
    { "F", "2012", "Bichette", "4"},
    { "F", "2011", "Babouche", "7"},
    { "F", "2011", "Ziboulette", "1"}
};

vector<int> c = { 1, 5, 3, 5, 1 };
vector<vector<int>> t = { {1, 2}, {2,4}, {3,1}, {0,0} };

//Auteur: Victor Robert
//pas de test direct possible: on affiche le tableau, et l'utilisateur doit voir si le résultat de la fonction lui convient
void testAfficheTableau() {
    afficheTableau(tableauTest);
}

//Auteur: Victor Robert
//J'ai confiance en ce code
void testMoyenne() {
    ASSERT( moyenne(c) == 3 );
}

void testSomme() {
    ASSERT (somme(c)==15);
}

//Auteur: Victor Robert
//J'ai confiance en ce code
void testIndiceMax() {
    ASSERT(indiceMax(c)==3);
}

//Auteur: Victor Robert
//J'ai confiance en ce code
void testColonne() {
    ASSERT(colonne(tableauTest, 0) == vector<string>({"M","F","F","F"}));
    ASSERT(colonne(tableauTest, 1) == vector<string>({"2011","2012","2011","2011"}));
    ASSERT(colonne(tableauTest, 2) == vector<string>({"Bubulle","Bichette","Babouche","Ziboulette"}));
    ASSERT(colonne(tableauTest, 3) == vector<string>({"3","4","7","1"}));
}

//Auteur: Victor Robert
//J'ai confiance en ce code
void testConversionInt() {
    ASSERT(conversionInt({}) == vector<int>({}));
    ASSERT(conversionInt({"1","2","3"}) == vector<int>({1,2,3}));
}

//Auteur: Victor Robert
//J'ai confiance en ce code
void testSelectLignes() {
    ASSERT(selectLignes(tableauTest, 0, "M") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}}));
    ASSERT(selectLignes(tableauTest, 1, "2011") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}, { "F", "2011", "Babouche", "7"}, { "F", "2011", "Ziboulette", "1"}}));
}

//Auteur: Victor Robert
int main() {
    cout << "Test affichage du tableau" << endl;
    testAfficheTableau();
    cout << "Lancement des tests de moyenne" << endl;
    testMoyenne();
    cout << "Lancement des tests de somme" << endl;
    testSomme();
    cout << "Lancement des tests de indiceMax" << endl;
    testIndiceMax();
    cout << "Lancement des tests de colonne" << endl;
    testColonne();
    cout << "Lancement des tests de conversionInt" << endl;
    testConversionInt();
    cout << "Lancement des tests de selectLignes" << endl;
    testSelectLignes();
}
