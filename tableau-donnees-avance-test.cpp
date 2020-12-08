#include <stdexcept>
/** @file **/
#include <iostream>
#include "tableau-donnees-avance.h"
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

vector<string> prenoms = {"Bubulle", "Bichette", "Babouche", "Ziboulette"};

void testChercheIndice() {
    ASSERT(chercheIndice(prenoms, "Bichette") == 1);
    ASSERT(chercheIndice(prenoms, "Bubulle") == 0);
    ASSERT(chercheIndice(prenoms, "Ziboulette") == 3);
    ASSERT(chercheIndice(prenoms, "bloup") == -1);
}

void testDistinct() {
    ASSERT(distinct(tableauTest,0) == vector<string>({"M", "F"}));
    ASSERT(distinct(tableauTest,1) == vector<string>({"2011", "2012"}));
}

void testGroupByInt() {
    ASSERT(groupByInt(tableauTest, {"M", "F"}, 0, 3) == vector<int>({3, 12}));
    ASSERT(groupByInt(tableauTest, {"2011", "2012"}, 1, 3) == vector<int>({11, 4}));
    ASSERT(groupByInt(tableauTest, {"Bichette", "Babouche"}, 2, 3) == vector<int>({4, 7}));
}

void testGroupByDouble() {
    ASSERT(groupByDouble(tableauTest, {"M", "F"}, 0, 3) == vector<double>({3., 12.}));
}

void testGroupByTemplate() {
    ASSERT(groupBy<int>(tableauTest, {"M", "F"}, 0, 3) == vector<int>({3, 12}));
    ASSERT(groupBy<int>(tableauTest, {"2011", "2012"}, 1, 3) == vector<int>({11, 4}));
    ASSERT(groupBy<int>(tableauTest, {"Bichette", "Babouche"}, 2, 3) == vector<int>({4, 7}));
    ASSERT(groupBy<double>(tableauTest, {"M", "F"}, 0, 3) == vector<double>({3., 12.}));
}

void testConversionDouble() {
    ASSERT( conversionDouble  ({ "12.1", " 14.13 " }) == vector<double>({ 12.1, 14.13 }) );
}

void testConversionTemplate() {
    ASSERT( conversion<int>({ "12", " 14" }) == vector<int>({ 12, 14}) );
    ASSERT( conversion<double>({ "12.1", " 14.13 " }) == vector<double>({ 12.1, 14.13 }) );
}


int main() {
    cout << "Lancement des tests de cherche indice" << endl;
    testChercheIndice();
    cout << "Lancement des tests de distinct" << endl;
    testDistinct();
    cout << "Lancement des tests de group by (int)" << endl;
    testGroupByInt();
    cout << "Lancement des tests de conversion double" << endl;
    testConversionDouble();
    cout << "Lancement des tests de group by (double)" << endl;
    testGroupByDouble();
    cout << "Lancement des tests de conversion (template)" << endl;
    testConversionTemplate();
    cout << "Lancement des tests de group by (template)" << endl;
    testGroupByTemplate();
}
