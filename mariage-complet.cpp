#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<string> jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};


//Auteur: Victor Robert
//J'ai confiance en ce code: si le fichier ne s'ouvre pas le programme renvoie automatiquement une erreur
//par contre le code ne fonctionne que sur un fichier dont les années vont de 2010 à 2015.
/** Construction du tableau des mariages par années
 * On suppose que le fichier contient sur chaque ligne une année entre 2010 et 2015
 * suivi d'un jour, puis d'un nombre de mariages
 * @param nom_fichier, le nom du fichier de données
 * @return un tableau d'entiers tel que dans chaque
 * case d'indice i, on trouve le nombre total de mariages de l'année 2010+i
 **/
vector<int> litTableauAnnee(string nom_fichier) {
    ifstream fichier;
    vector<int> TableauAnnee(6);
    int annee, nombreMariages;
    string jour;
    fichier.open(nom_fichier);
    if (fichier){
        while (fichier>>annee,fichier>>jour,fichier>>nombreMariages){
            TableauAnnee[annee-2010] += nombreMariages;
        }
    }
    else{
        throw runtime_error("Le fichier n'a pas pu être ouvert!");
        return {0};
    }
    fichier.close();
    return TableauAnnee;
}

/** Test de la fonction litTableauAnnee **/
void testLitTableauAnnee() {
    vector<int> t = litTableauAnnee("donnees/statistiques-des-jours-des-mariages.txt");
    ASSERT(t[0] == 9195); // Nombre de mariages en 2010
    ASSERT(t[3] == 9443); // Nombre de mariages en 2013
    ASSERT(t[5] == 9046); // Nombre de mariages en 2015
}

//Auteur: Victor Robert
//Ce code fonctionne bien, je vois pas comment il pourrait être amélioré
/** Renvoie le numéro du jour correspondant à la chaîne de caractères
 * @param jour une chaine de caractère contenant un jour de la semaine (première lettre en majuscule)
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

//Auteur: Victor Robert
//J'ai confiance en ce code: si le fichier ne s'ouvre pas le programme renvoie automatiquement une erreur
/** Construction du tableau des mariages par jour
 * On suppose que le fichier contient sur chaque ligne une année entre 2010 et 2015
 * suivie d'un jour, puis d'un nombre de mariages
 * @param nom_fichier, le nom du fichier de données
 * @return un tableau d'entiers tel que dans chaque
 * case d'indice i, on trouve le nombre total de mariages célébrés le jour i
 **/
vector<int> litTableauJours(string nom_fichier) {
    ifstream fichier;
    vector<int> TableauJours(7);
    int annee, nombreMariages;
    string jour;
    fichier.open(nom_fichier);
    if (!fichier){
        throw runtime_error("Le fichier "+nom_fichier+" n'a pas pu s'ouvrir");
    }
    while (fichier>>annee,fichier>>jour,fichier>>nombreMariages){
        TableauJours[indiceJour(jour)] += nombreMariages;
    }
    
    fichier.close();
    return TableauJours;
}

/** Test de la fonction litTableauJours **/
void testLitTableauJours() {
    vector<int> t = litTableauJours("donnees/statistiques-des-jours-des-mariages.txt");
    ASSERT(t[0] == 4171); // Nombre de mariages le lundi
    ASSERT(t[3] == 4393); // Nombre de mariages le jeudi
    ASSERT(t[6] == 2); // Nombre de mariages le dimanche
}

//Auteur: Victor Robert
//Ce code fonctionne bien et je pense pas qu'il puisse être am"lioré
/** Renvoie la somme d'un tableau d'entiers
 * @param t, un tableau d'entier
 * @return la somme des valeurs du tableau
 **/
int somme(vector<int> t) {
    int SommeTableau = 0;
    for (int i = 0; i < t.size(); i++){
        SommeTableau += t[i];
    }
    return SommeTableau;
}

/** Test de la fonction somme **/
void testSomme() {
    ASSERT(somme({1,2,3}) == 6);
    ASSERT(somme({}) == 0);
    ASSERT(somme({2,2,4,8}) == 16);
}

//Auteur: Victor Robert
//J'ai confiance en ce code: il intercepte automatiquement un tableau vide qui causerait une division par 0.

/** Renvoie la moyenne d'un tableau d'entier
 * @param t, un tableau d'entiers
 * @return la moyenne (entière) des valeurs
 * (on arrondit à l'entier inférieur)
 **/
int moyenne(vector<int> t) {
    if (t.size()<=0){
        throw runtime_error("Un tableau non vide doit être utilisé!");
    }
    return somme(t)/t.size();
}

/** Test de la fonction moyenne **/
void testMoyenne() {
    ASSERT(moyenne({1,2,3}) == 2);
    ASSERT(moyenne({1}) == 1);
    ASSERT(moyenne({2,2,4,8}) == 4);
}

//Auteur: Victor Robert
//J'ai confiance en ce code
/** Renvoie l'indice de la valeur maximale du tableau
 * @param t, un tableau d'entier
 * @return l'indice de la valeur maximale ou -1 si le tableau est vide
 **/
int indiceMax(vector<int> t) {
    if (t.size() == 0){return -1;} //si le tableau est vide, on renvoie -1
    int max_ = 0;
    for (int i = 1; i < t.size(); i++){
        if (t[i]>=t[max_]){max_=i;}
    }
    return max_;
}

/** Test de la fonction IndiceMax **/
void testIndiceMax() {
    ASSERT(indiceMax({}) == -1);
    ASSERT(indiceMax({1,2,3}) == 2);
    ASSERT(indiceMax({1,3,2}) == 1);
    ASSERT(indiceMax({1}) == 0);
    ASSERT(indiceMax({2,8,4,4}) == 1);
}

//Auteur: Victor Robert
/** Lance les fonctions de test puis affiche :
 * - le nombre total de mariages
 * - le nombre moyen de mariages célébrés par an
 * - l'année où l'on a célébré le plus de mariages (et leur nombre)
 * - le jour de la semaine où l'on célèbre le plus de mariages (et leur nombre)
 * - le pourcentage de mariages célébrés un samedi
 **/
int main() {
    string nomFichier = "donnees/statistiques-des-jours-des-mariages.txt";
    //On fait tous les test
    testLitTableauAnnee();
    testLitTableauJours();
    testSomme();
    testMoyenne();
    testIndiceMax();
    //On affiche:
    vector<int> MariagesParAn = litTableauAnnee(nomFichier);
    vector<int> MariagesParJour = litTableauJours(nomFichier);
        
    
    int nbTotalDeMariages = somme(MariagesParAn); //ou somme(litTableauJours(nomFichier));
    cout << "Nombre total de mariages: " << nbTotalDeMariages << endl;
    
    int nbMoyen = moyenne(MariagesParAn);
    cout << "Nombre moyen de mariages par an: " << nbMoyen << endl;
    
    int anneeMaxMariages = indiceMax(MariagesParAn)+2010;
    cout << "Année où il y a eu le plus de mariages: " << anneeMaxMariages << " ,nombre de mariages: " << MariagesParAn[anneeMaxMariages-2010] << endl;
    
    
    string JourMaxMariages = jours[indiceMax(MariagesParJour)];
    cout << "Jour de la semaine où il y a eu le plus de mariages: " << JourMaxMariages << " ,nombre de mariages: " << MariagesParJour[indiceJour(JourMaxMariages)]<< endl;
    
    float PourcentageMariagesSamedi = (100.0*(float)MariagesParJour[5])/(float)nbTotalDeMariages;
    cout << "Pourcentage de mariages le samedi: " << PourcentageMariagesSamedi << "%"<<endl;
    
    return 0;
    
    
}
