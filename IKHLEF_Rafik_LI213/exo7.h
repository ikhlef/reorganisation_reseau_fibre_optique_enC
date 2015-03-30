#ifndef EXO7_H_INCLUDED
#define EXO7_H_INCLUDED

#include "exo6.h"
#include "structure_reseau.h"
#include "fonction.h"

typedef struct arete {
    int i; //numero de l'arete
    int u ; // numero sommet debut
    int v ;// numero sommet fin
 } Arete ;

typedef struct elementListeA {
    Arete * a ;
    struct elementListeA * suiv ;
 } ElementListeA ;

 typedef struct sommet{
     int i; // num Sommet
     int nbA ; // nb aretes incidentes
     ElementListeA * L_adj; // liste des aretes incidentes a ce sommet
     double x ;// coordonnees
     double y;
 } Sommet;

typedef struct sommet_Liste {               // la liste des sommets
    Sommet * v ;
    struct sommet_Liste * suiv ;
 } Sommet_Liste;

typedef struct graphe {                                //implementation par liste d'adjacense
    int m ; // nb d aretes
    int n1;// nb de sommets
    Sommet_Liste * Sliste; // liste de pointeurs sur sommets
    ElementListeA * listA ; // liste de pointeurs sur aretes
} Graphe ;

#endif // EXO7_H_INCLUDED


