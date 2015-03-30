#include <stdio.h>
#include <stdlib.h>
#include "structure1.h"

#ifndef __CHAINE_H__
#define __CHAINE_H__


// Question 1
void Recuperation_sous_chaine(char* dest, char* src, int debut, int fin);          //reccuperation d'une sous chaine depuis chaine

int Numero_Indice(char* src, char c);                                              //indice du caractere dans la chaine.

void Ajouter_Point_Chaine_Fin(Chaine* ch, Point* p);

void Ajouter_Chaine_Fin(ListeChaine* liste, Chaine* ch);

Chaine* Analyser_Chaine1(char* ligne);

void Lecture_chaine1(FILE* file,ListeChaine* machaine);


void Ajouter_Point_Chaine(Chaine* ch, Point* p);                                     // ajouter le point p dans la chaine ch
Chaine* Analyser_Chaine(char* line);
void Ajouter_Chaine(ListeChaine* liste, Chaine* ch);                                 //Ajouter_Chaine dans la liste des chaines liste
void Lecture_chaine(FILE* file,ListeChaine* liste);

//void lecture_chaine(FILE *f, ListeChaine *L);

//Question 2
void Ecrire_Chaine_Fichier(Chaine* ch, FILE* file);

void Ecrire_Point(Point* This);

void Ecrire_Chaine(Chaine* This);

void afficher_ListeChaines(ListeChaine* L);

void Ecrire_chaine_txt(ListeChaine* listechaine, FILE* file);

//Question 3
char* CreerLigne(int style, int couleur, int size, Point* p1 ,Point* p2, int z);
char* CreerEntete();
FILE* CreerFichier(char nomfichier[256]);
void ecrit_chaine_xfig(FILE* f, Chaine* Ch, int zoom, int epaisseur);
void ecrit_Lchaine_xfig(FILE* f, ListeChaine* L, int zoom, int epaisseur);

//Question 4
double longueurChaine(Chaine *This);

double longueurTotale(ListeChaine *This);

int compte_point(ListeChaine *This);


#endif

