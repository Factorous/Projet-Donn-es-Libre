//
//  main.cpp
//  Exercice 10 projet progimperative (données libre)
//
//  Created by Victor Robert on 25/11/2020.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "primitives.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;



//On convertit la ligne en un tableau
vector<string> LigneATableau(string s,string sep){
    vector<string> t;
    string val;
    for (int i=0;i< s.size();i++){
        if (s[i]!=sep){
            val += s[i];
        }
        else if (i==s.size()-1){
            t.push_back(val);
        }
        else{
            t.push_back(val);
            val = "";
        }
    }
    return t;
}

//fonction qui calcule le barycentre, et renvoie ses coordonnées (x,y)
vector<int> CalculBaryCentre(vector<vector<int>> Villes){
    int BaryX = 0;
    int BaryY = 0;
    int nombreHabTotal = 0;
    int nombreHab;
    for (int i=0; i< Villes.size();i++){
        nombreHab = Villes[i][2];
        nombreHabTotal += nombreHab;
        BaryX += Villes[i][0]*nombreHab;
        BaryY += Villes[i][1]*nombreHab;
    }
    BaryX /= nombreHabTotal;
    BaryY /= nombreHabTotal;
    
    return {BaryX,BaryY};
}

void display_bary_centre(RenderWindow& window, vector<int> BaryCentre){
    draw_filled_rectangle(window, Point(BaryCentre[0],BaryCentre[1]), 5, 5, Color(0,0,255));
}

vector<string> calculPlusGrandeVille(vector<vector<int>> Ville, vector<string> NomsVille){
    int max_ = 0;
    for (int i = 0; i < Ville.size(); i++){
        if (Ville[max_][2]<Ville[i][2]){
            max_ = i;
        }
    }
    return {NomsVille[max_],to_string(Ville[max_][2])};
}

int nombreHabTotal(vector<vector<int>> Ville){
    int somme = 0;
    for (int i = 0; i < Ville.size();i++){
        somme += Ville[i][2];
    }
    return somme;
}

void display_stats(RenderWindow& w,vector<vector<int>> Ville, vector<string> NomsVille){
    int textSize = 15;
    draw_text(w, Point(10,10), textSize, "Communes de France:", Color::White);
    
    draw_text(w, Point(10,10+textSize), textSize, "Nombre de communes:"+to_string(Ville.size()), Color::White);
    draw_text(w, Point(10,10+2*textSize), textSize, "Nombre d'habitants au total:"+to_string(nombreHabTotal(Ville))+" mille", Color::White);
    vector<string> VilleAvecLePlusDhabitants = calculPlusGrandeVille(Ville, NomsVille);
    draw_text(w, Point(10,10+3*textSize), textSize, "Commune avec le plus d'habitants:"+VilleAvecLePlusDhabitants[0],Color::White); //on obtient pas Paris, parce que Paris est divisée en quartiers
    draw_text(w, Point(10,10+4*textSize), textSize, "  |->Nombre d'habitants:"+VilleAvecLePlusDhabitants[1]+" mille",Color::White);
    
}


int main(int argc, const char * argv[]) {
    //On créer une fenêtre
    float windowWidth = 1000;
    float windowHeight = 900;
    RenderWindow window(VideoMode(windowWidth,windowHeight),"exercice 10");
    
    //On créer une texture qui contient une carte de la France avec un sprite associé
    Texture backgroundTex;
    backgroundTex.loadFromFile("/Users/victor/Documents/Exercice 10 projet progimperative\ \(données\ libre\)/Exercice\ 10\ projet\ progimperative\ \(données\ libre\)/France.png"); //image de la france
    
    //backgroundTex.loadFromFile("France.png"); <-- cette ligne de code devra être utilisée sur jupyterhub (si sfml marche)
    
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTex);
    float textureWidth = backgroundTex.getSize().x;
    float textureHeight =backgroundTex.getSize().y;
    //backgroundSprite.scale(windowWidth/textureWidth, windowHeight/(textureHeight+150));
    
    //On ouvre le fichier csv
    ifstream fichierCSV;
    fichierCSV.open("/Users/victor/Documents/Exercice\ 10\ projet\ progimperative\ \(données\ libre\)/Exercice\ 10\ projet\ progimperative\ \(données\ libre\)/communes.csv");
    //fichierCSV.open("communes.csv"); <-- cette ligne de code devra être utilisée sur jupyterhub (si sfml marche)

    //si on
    if (!fichierCSV){
        throw runtime_error("Le fichier n'a pas pu être ouvert!\nRegardez bien le documentation si le fichier est ouvert sur jupyterhub (ligne 87 du code)");
    }
    //On met la première ligne du fichier dans une liste de charactères entete
    string entete;
    getline(fichierCSV, entete);
    
    //Maintenant on lit dans le fichier
    string ligne;
    string sep = ",";
    vector<string> t;
    
    /*
     Quelques informations concernant le placement d'une ville:
     -5 <Long<9
     42.5<Lat< 51
     point de départ: lat:50.796012, long: -4.859222
     */
    int rangLong = 5;
    int rangLat= 4;
    int rangNombreHab=10;
    int nombreHab;
    float longitude, latitude;
    float longMin = -5.0;
    float longMax = 9.0;
    float latMin = 42.5;
    float latMax = 51;
    
    int X,Y;
    float facteurReduction = 5;
    
    vector<vector<int>> Ville;
    vector<string> NomsVille;
    
    Color couleurDesVilles = Color(200,10,10);
    
    
    
    while (getline(fichierCSV, ligne)){
        t= LigneATableau(ligne,sep);
        istringstream(t[rangLat]) >> longitude; //on met la latitude en string sous forme de float
        istringstream(t[rangLong]) >> latitude;
        istringstream(t[rangNombreHab]) >> nombreHab;
        if (latitude<latMax and latitude>latMin and longitude<longMax and longitude>longMin){
            /* on calcule les coordonnées (x,y) à partir de la longitude et latitude*/
            X = (windowWidth*longitude)/(longMax-longMin)-(windowWidth*longMin)/(longMax-longMin);
            Y = (windowHeight*latitude)/(latMin-latMax)-(windowHeight/((latMin/latMax)-1));
            Ville.push_back({X,Y,nombreHab});
            NomsVille.push_back(t[1]);
        }
        
    }
    
    vector<int> BaryCentre = CalculBaryCentre(Ville);
    
    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::Resized){
                /* code qui ne sert à rien
                windowWidth = window.getSize().x;
                windowHeight = window.getSize().y;
                backgroundSprite.scale(windowWidth/textureWidth, windowHeight/textureHeight);*/
            }
            
            /* cette portion du code permet de changer la taille des villes dans la fenêtre*/
            if (event.type==Event::KeyPressed){
                if (event.key.code==Keyboard::Right){
                    facteurReduction += 2;
                }
                if (event.key.code==Keyboard::Left){
                    facteurReduction -= 2;
                    if (facteurReduction<1){
                        facteurReduction = 1;
                    }
                    
                }
            }
        }
        window.clear(Color(255,255,255)); //on crée une fenêtre blanche
        window.draw(backgroundSprite); //on dessine la carte de la France sur la fenêtre
        for (int i=0;i<Ville.size();i++){ //on parcourt les villes et on les dessine sur la fenêtre
            if (Ville[i][2]/facteurReduction==0){
                draw_point(window, Point(Ville[i][0],Ville[i][1]), couleurDesVilles); //si la ville a une population trop petite pour être affichée, on dessine un point à la place d'un cercle
            }
            else{draw_filled_circle(window, Point(Ville[i][0],Ville[i][1]), Ville[i][2]/facteurReduction, couleurDesVilles);}
            
        }
        display_stats(window,Ville,NomsVille);
        display_bary_centre(window,BaryCentre); //on dessine le braycnetre sur la fenetre
        window.display();
    }
    fichierCSV.close(); //on ferme le fichier
    return 0;
}
