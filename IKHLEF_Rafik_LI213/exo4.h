#include <stdio.h>
#include <stdlib.h>
#include "exo3.h"

#ifndef __Exo4_H__
#define __Exo4_H__
//------------------------la structure d'un element de la liste de la table de hachage 
typedef struct element{
    double cle;                             //la clé d'un element 
    Noeud *valeur;                          // valeur est un pointeur sur un Noeud, il represente la donnée associée a la clé.
    struct element *suivant;                // pointeur sur l'element suivant
}Element, *TElement;                        //typedef Elment* TElement;

//--------------------structure de la table de hachage
typedef struct hashTable{                      
    int taille;                   //la taille de la table de hachage
    int count;                    //
    TElement *listeElement;       // pointeur sur la liste des elements de la table.
}HashTable;


HashTable* Initialiser_HashTable(int size );  // la fonction d'initialisation d'une table de hachage

double F(double x, double y);                 // la fonction F = f(x, y) y+(x+y)(x+y+1)/2

 int Hash(double x, double y);

Noeud* Existe_noeud_hach(int hash, double key, HashTable *table);

Noeud * Recherche_Cree_Noeud_Hashage(Reseau *res, HashTable *table, double x, double y );   

void recree_reseau_hashtable(ListeChaine *L, Reseau * R);

#endif



