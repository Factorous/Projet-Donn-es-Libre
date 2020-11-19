#include <stdexcept>
/** @file **/
#include <iostream>
#include "tableau-lecture-csv.h"
#include "tableau-donnees.h"
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<vector<string>> tableauTest = {
    {"3", "M", "2011", "Bubulle", "3"},
    {"4", "F", "2012", "Bichette", "4"},
    {"7", "F", "2011", "Babouche", "7"},
    {"1", "F", "2011", "Ziboulette", "1"}
};

vector<vector<string>> petites_donnees = { { "a0", "b0"}, { "a1", "b1" } };

void testLitTableauCSVAvecColonnes() {
    ASSERT( litTableauCSV("donnees/donnees-test.csv", 5) == tableauTest);
    vector<vector<string>> t = litTableauCSV("donnees/liste_des_prenoms.csv", 5);
    ASSERT(t.size() == 20453);
    ASSERT(t[0][1] == "M");
    ASSERT(t[5][3] == "Aboubacar");
    ASSERT(t[6][4] == "7");
}

void testLitTableauCSVSansColonnes() {
    ASSERT( litTableauCSV("donnees/donnees-test.csv") == tableauTest);
    vector<vector<string>> t = litTableauCSV("donnees/liste_des_prenoms.csv");
    ASSERT(t.size() == 20453);
    ASSERT(t[0][1] == "M");
    ASSERT(t[5][3] == "Aboubacar");
    ASSERT(t[6][4] == "7");
    t = litTableauCSV("donnees/statistiques-des-jours-des-mariages.csv");
    ASSERT(t.size() == 42);
    ASSERT(t[0].size() == 9);
    ASSERT(t[0][0] == "2015");
    ASSERT(t[0][1] == "Jeudi");
    ASSERT(t[0][2] == "756.0");
    ASSERT(t[0][3] == "");
    ASSERT(t[0][8] == "");
}

int main() {
    cout << "Lancement des tests de litTableauCSVAvecColonnes" << endl;
    testLitTableauCSVAvecColonnes();
    cout << "Lancement des tests de litTableauCSVSansColonnes" << endl;
    testLitTableauCSVSansColonnes();
}
