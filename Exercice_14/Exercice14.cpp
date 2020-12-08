//
//  main.cpp
//  Exercice 14 projet Prog imperative
//
//  Created by Victor Robert on 04/12/2020.
//



/* Je n'ai pas trop confiance en ce code parce que j'ai du programmer les fonctions graphiques moi même; avec python je pouvais juste utiliser plt.plot(), alors que là je dois coder la fonction plot(), j'ai essayer de la rendre générale, ce qui m'a pris beaucoup de temps 

Aussi je voulais en plus d'utiliser l'interpolation de lagrange pour la courbe, faire une regression linéaire polynomiale mais je n'ai pas eu le temps :( 
*/



#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "primitives.hpp"


using namespace std;
using namespace sf;

int min(vector<int> t){
    int min_ = t[0];
    for (int i=0; i< t.size();i++){
        if (t[i]<min_){min_=t[i];}
    }
    return min_;
}

int max(vector<int> t){
    int max_ = t[0];
    for (int i=0; i< t.size();i++){
        if (t[i]>max_){max_=t[i];}
    }
    return max_;
}
//regarde si un élément est dans un tableau
template <typename T>
bool estDansTableau(T e,vector<T> t){
    for (int i=0;i<t.size();i++){
        if (e==t[i]){return true;}
    }
    return false;
}

//valeur absolue
template <typename T>
T abs(T a){
    if (a<0){return -a;}
    return a;
}
//initialise un tableau avec une certaine valeur
template <typename T, typename C>
vector<T> initialise(vector<T> t, C a){
    vector<T> new_t(t.size());
    for (int i=0; i< t.size();i++){
        new_t[i] =a;
    }
    return new_t;
    
}

//interpelation de langrange
//on pourrait optimiser ce code en renvoyant les coefficients à la place du point (parce que là on les calcule à nouveau à chaque frame pour chaque point), mais vu que le programme focntionne, je vais pas le faire tout de suite
int lagrangeInterpelation(float x,vector<int> X,vector<int> Y){
    vector<float> coefficients(X.size());
    coefficients = initialise(coefficients, 1);
    int y = 0;
    for (int i = 0; i < X.size();i++){
        for (int j = 0; j < X.size();j++){
            if (j!=i){
                coefficients[i] *= (x-X[j])/(X[i]-X[j]);
            }
        }
        y += coefficients[i]*Y[i];
    }
    return y;
}

/* fonction qui ne sera jamais utilisée (parce qu'elle fonctionne pas)
Son but était d'enlever les valeurs qui étaient proche afin qu'on ait pas plusieurs textes qui se recouvrent*/
vector<int> filter(vector<int> t, int textSize,int min_,int max_){
    vector<int> new_t;
    for (int i=0;i< t.size();i++){
        for (int j=0; j < t.size();j++){
            if (j!=i){//si ce n'est pas la même valeur
                
                if (abs((float)t[i]-(float)t[j])/((float)max_-(float)min_)>1){ //cette ligne ne fonctionne pas
                    
                    if (!estDansTableau(t[i], new_t)){
                        //cout << "jjj" << endl;
                        new_t.push_back(t[i]);
                    }
                }
            }
        }
    }
    return new_t;
}

//Dessine le repère (les axes avec les valeurs)
void draw_landmark(RenderWindow& window,int padding,int LargeurEcran,int HauteurEcran,vector<int> X, vector<int> Y,int textSize,int minX,int maxX, int minY, int maxY){
    
    //Y = filter(Y, textSize, minY, maxY);
    for (int i = 0; i<X.size();i++){
        int x  = padding+(LargeurEcran-2*padding)*(X[i]*minX-1)/(maxX-minX);
        draw_line(window, Point(x,HauteurEcran-padding-5),Point(x,HauteurEcran-padding+5), Color::Black);
        //draw_text(window, Point(x,HauteurEcran-padding), textSize, to_string(X[i]), Color::Black);
        
    }
    for (int i=0; i<Y.size();i++){
        int y = (HauteurEcran-padding)-(HauteurEcran-2*padding)*(Y[i]-minY)/(maxY-minY);
        draw_line(window, Point(padding-5,y), Point(padding+5,y), Color::Black);
        //draw_text(window, Point(padding-(int)textSize*2.3,y), textSize, to_string(Y[i]), Color::Black);
    }
    draw_text(window, Point(padding,HauteurEcran-padding+5), textSize, to_string(minX), Color::Black);
    draw_text(window, Point(LargeurEcran-padding,HauteurEcran-padding), textSize, to_string(maxX), Color::Black);
    draw_text(window, Point(padding-(int)textSize*2.3,HauteurEcran-padding), textSize, to_string(minY), Color::Black);
    draw_text(window, Point(padding-(int)textSize*2.3,padding), textSize, to_string(maxY), Color::Black);
    draw_line(window, Point(padding,HauteurEcran-padding), Point(LargeurEcran-padding,HauteurEcran-padding), Color::Black);
    draw_line(window, Point(padding,HauteurEcran-padding), Point(padding,padding), Color::Black);
}



//on affiche le graphe qu'on a créé
void plot(RenderWindow& window, vector<int> X, vector<int> Y,int padding,int textSize,bool relative,string xlabel, string ylabel){
    assert(X.size()==Y.size());
    //Y[0] = 1000;
    
    int LargeurEcran = window.getSize().x;
    int HauteurEcran = window.getSize().y;
    
    //on trouve les valeurs minimales et maximales pour les tableaux afin de créer un graphe de bonne taille
    int maxY = max(Y);
    int minY;
    if (relative){
        minY = min(Y);
    }
    else{
        minY = 0;
    }
    
    int maxX = max(X);
    int minX = min(X);
    
    draw_landmark(window, padding, LargeurEcran, HauteurEcran, X, Y,textSize,minX,maxX,minY,maxY);
    
    
    
    for (int i = 0; i< X.size();i++){
        int x  = padding+(LargeurEcran-2*padding)*(X[i]*minX-1)/(maxX-minX);
        int y = (HauteurEcran-padding)-(HauteurEcran-2*padding)*(Y[i]-minY)/(maxY-minY);
        draw_filled_circle(window, Point(x,y), 5, Color::Blue);
        
    }
    //on dessine l'interpolation
    for (float x=padding;x<LargeurEcran-padding; x+=1){
        
        float new_x = (minX-0.5)+x*(maxX-minX)/(LargeurEcran-2*padding);
        //cout << new_x << endl;
        float y = (HauteurEcran-padding)-(HauteurEcran-2*padding)*(lagrangeInterpelation(new_x, X, Y)-minY)/(maxY-minY);
        //new_x =padding+(LargeurEcran-2*padding)*(new_x*minX-1)/(maxX-minX);
        draw_point(window, Point((int)x,(int)y), Color::Green);
    }
    
    //on dessine les labels
    draw_text(window, Point(HauteurEcran/2,HauteurEcran-padding+2*textSize), textSize, xlabel, Color::Black);
    draw_text(window, Point(padding-textSize,padding-1.5*textSize), textSize, ylabel, Color::Black);

}

bool elementDansListe(char el,vector<string> liste){
    for (int i = 0; i < liste.size();i++){
        if (el==liste[i]){return true;}
    }
    return false;
}

bool estUnNombre(string s){
    for (int i=0;i<s.size();i++){
        if (not elementDansListe(s[i], {"1","2","3","4","5","6","7","8","9","."})){
            return false;
        }
    }
    return true;
}

//pour le debugage
template <typename T>
void displayTableau(vector<T> t){
    for (auto x: t){
        cout << x << " ";
    }
    cout << endl << endl << endl;
}

//On convertit la ligne en un tableau
vector<string> LigneATableau(string s,string sep){
    vector<string> t;
    string val;
    for (int i=0;i< s.size();i++){
        if (i==s.size()-1){
            t.push_back(val);
        }
         else if (s[i]!=sep){
            val += s[i];
        }
        
        else{
            t.push_back(val);
            val = "";
        }
    }
    return t;
}

//on nettoie la ligne d'un charactère: dans mon cas les données étaient parfois bizarres:
//Il y avait par exemple sur une ligne: a;b;c;;;;;;d
//il faut donc enlever les ;;; en trop sinon lorsque je veux accéder à un rang du tableau crée, j'obtiens un élément vide
string NettoyageDeLaLigne(string ligne,string charactererNett){
    string ligneNettoyee;
    for (int i=0;i<ligne.size()-1;i++){
        if (ligne[i]!=charactererNett or ligne[i]!=ligne[i+1]){
            ligneNettoyee += ligne[i];
        }
    }
    
    return ligneNettoyee;
}

int main(int argc, const char * argv[]) {
    int LargeurEcran = 800;
    int HauteurEcran = 600;
    int padding = 100;
    int textSize = 13;
    
    string xlabel = "taille de l'entreprise";
    string ylabel = "investissement";
    RenderWindow window(VideoMode(LargeurEcran,HauteurEcran), "Exercice 14");
    
    /* cette ligne devra êre changée si le code est utilisé sur jupyter*/
    ifstream fichier("/Users/victor/Desktop/Informatique impérative/fr-esr-rd-moyens-entreprises-taille.csv");
    
    vector<int> Taille_entreprise = {1,2,3,4};
    vector<int> Recherche_et_developpement = {0,0,0,0};
    vector<int> Nb_recherche_et_dev = {0,0,0,0};
    
    string ligne;
    vector<string> LigneTableau;
    getline(fichier, ligne); //On enlève l'entête
    
    //on créé des variables pour la conversion de string à int:
    int code_taille, valeur;
    
    string delimiter = ";";
    
    while (getline(fichier,ligne)){
        ligne = NettoyageDeLaLigne(ligne, ";");
        
        LigneTableau = LigneATableau(ligne, ";");
        if (LigneTableau.size()==13){
            
            if (LigneTableau[10]=="non"){
                
                if (LigneTableau[7] != "0"){
                    //cout << LigneTableau[3] << endl;
                    if (LigneTableau[3] == "pers"){
                        if (estUnNombre(LigneTableau[12])){
                            istringstream(LigneTableau[7]) >> code_taille;
                            istringstream(LigneTableau[12]) >> valeur;
                            Recherche_et_developpement[code_taille-1] += valeur;
                            Nb_recherche_et_dev[code_taille-1]++;
                        }
                    }
                }
            }
        }
    }
    
    fichier.close();
    for (int i= 0; i <Recherche_et_developpement.size();i++){
        Recherche_et_developpement[i] = Recherche_et_developpement[i]/Nb_recherche_et_dev[i];
    }
    
    
    //mainloop for the window, display all of the data
    while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == Event::Closed)
                    window.close();
            }
            window.clear(Color(255,255,255));
            plot(window, Taille_entreprise, Recherche_et_developpement,padding,textSize,false,xlabel,ylabel);
            window.display();
        }
    return 0;
}
