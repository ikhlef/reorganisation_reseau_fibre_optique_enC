#include <stdio.h>
#include <stdlib.h>

#include "structure1.h"
#include "fonction_reseau_exo2.h"

#ifndef __Exo3_H__
#define __Exo3_H__

void permute(CelluleLNoeud* This,int i,int j);
 int tri_rapide_separation(CelluleLNoeud* This,int deb,int fin);
 CelluleLNoeud* tri_rapide(CelluleLNoeud *cel,int deb,int fin);
 CelluleLNoeud* TriRapide_CelleLNoeud(CelluleLNoeud* This);
 Noeud * recherche_cree_noeud(Reseau *R, float x, float y);
void Ajouter1_Cellule_Commodite_Reseau(Reseau * res, CelluleCommodite* com); //inserer une cellule de commodité au debut de la liste des commoditées.
int compare(double x1,double y1,double x2, double y2);
void recree_reseau(ListeChaine *L, Reseau * R);

#endif


