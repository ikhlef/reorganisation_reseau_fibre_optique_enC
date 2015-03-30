#include <stdio.h>
#include <stdlib.h>

#include "structure_reseau.h"

#ifndef __FONCTION_RESEAU_EXO2_H__
#define __FONCTION_RESEAU_EXO2_H__

Noeud* Recuperation_ligne_Noeud(char* ligne);    // la fonction de recuperation et d initialisation d'un noeud a partir de la chaine de caractere ligne.
void Ajouter_Cellule_Noeud_Reseau(Reseau* res, CelluleLNoeud* cellule); // ajouter l'element celluleNoeud dans la liste des noeuds du reseau.
void Ajouter_Cellule_Commodite_Reseau(Reseau * res, CelluleCommodite* com); // ajouter l'element cellulecommodité dans la liste chainée des commodités du reseau.
void Ajouter_Voisin_Noeud(Noeud* noeud, Voisin * v);             // la fonction d'ajout d'un voisin a la liste chainée des voisins d'un noeud.
void Lecture_Fichier_Reseau(FILE* file, Reseau* res);
//---------------Q2----------
int compteCable(Reseau *res);
//------------------------------------Q3-------------------------
void ecrit_reseau_disque(Reseau *res,  FILE *file);
//------------------Q4----------------------------------------------
char * CreerLigneReseau(int style, int couleur, int epaisseur,int z, Noeud* noeud1 ,Noeud* noeud2);
char* CreerEnteteReseau();
FILE* CreerFichierReseau(char nomfichier[256]);
Noeud * RechercheNoeud(CelluleLNoeud *cel, int u);
void ecrit_cable_xfig(FILE* f, CelluleLNoeud* cel,CelluleLNoeud* cel1,int zoom, int epaisseur);
void ecrit_reseau_xfig( Reseau *R, FILE* f, int zom, int epaisseur);
//----------------Q5-------------------------------------------------------
int recherche_voisin(Noeud * noeud, int u);
//----------------------------------------------------
void Afficher_Voisin(Voisin * This);
void Afficher_Noeud(Noeud* This);
void Afficher_Cellule_Noeud(CelluleLNoeud * This);
void Afficher_Cellule_Commodite(CelluleCommodite * This);
void Afficher_Reseau(Reseau* This);

#endif

