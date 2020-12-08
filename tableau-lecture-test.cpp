#include <stdexcept>
/** @file **/
#include <iostream>
#include "tableau-lecture.h"
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<vector<string>> tableauTest = {
    { "M", "2011", "Bubulle", "3"},
    { "F", "2012", "Bichette", "4"},
    { "F", "2011", "Babouche", "7"},
    { "F", "2011", "Ziboulette", "1"}
};


void testLitTableau() {
    vector<vector<string>> t = litTableau("donnees/liste_des_prenoms.txt", 4);
    ASSERT(t.size() == 20453);
    ASSERT(t[0][0] == "M");
    ASSERT(t[5][2] == "Aboubacar");
    ASSERT(t[6][3] == "7");
    ASSERT(litTableau("donnees/donnees-test.txt", 4) == tableauTest);
}


int main() {
    cout << "Lancement des tests de litTableau" << endl;
    testLitTableau();
}
