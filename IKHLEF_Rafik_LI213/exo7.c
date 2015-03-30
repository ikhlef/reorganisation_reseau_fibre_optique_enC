#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

#include "exo7.h"

/*------------------Methode Arete------(initialisation + allocation + affichage)----------------*/
// Initialisation d'une arete
void AreteInit(Arete* This, int index, int NumSom1, int NumSom2){
    This->i = index;
    This->u = NumSom1;
    This->v = NumSom2;
}

//Nouvelle arete, allocation
Arete* NewArete(int index, int NumSom1, int NumSom2){
    Arete* This = malloc(sizeof(Arete));
    if (!This) return NULL;
    AreteInit(This,index,NumSom1,NumSom2);
    return This;
}

//Afficher l'arete
void AretePrint(Arete* This){
    printf("Arete : (%d, %d, %d)\n", This->i, This->u, This->v);
}

/*-----------------------Methode liste des aretes--(allocation + initialisation + insertion d'une arete + affichage de la liste des aretes)----------*/
//void AListeInit(ElementListeA* This);
//Initialisation de la liste des aretes
void AListeInit(ElementListeA* This){
    This->a = NULL;
    This->suiv = NULL;
}

//---creation de la liste des aretes
ElementListeA* NewAListe(void){
    ElementListeA *This = malloc(sizeof(ElementListeA));
    if (!This) return NULL;
    AListeInit(This);
    return This;
}

// Insertion d'une arete a la fin de la Liste des arete
int AListeInserer(ElementListeA* This, Arete* a){
    if (This->a == NULL){
        This->a = a;
        return 1;
    }
     ElementListeA *suiv1 = NewAListe();
     suiv1->a = a;
     while(This->suiv != NULL){
        This=This->suiv;
    }
    This->suiv = suiv1;
    return 1;
}

//Aficher la liste des aretes
void PrintAListe(ElementListeA* This){
    if (This==NULL)
        printf("La Liste des aretes est vide\n");
    ElementListeA* tmp = This;
    while(tmp != NULL){
        if (tmp->a!=NULL)
                AretePrint(tmp->a);
        tmp = tmp->suiv;
    }
}

/*------------------Methode de Sommet---(initialisation + allocation + affichage + trouver un sommet )--------------------*/
//Initialisation du sommet
void Sommet_Init(Sommet* This, int i, double x1, double y1){
    This->i = i;
    This->L_adj = NewAListe();
    This->nbA = 0;
    This->x = x1;
    This->y = y1;
}

//creation du sommet et allocation
Sommet* NewSommet(int i,double x1, double y1){
    Sommet* This = malloc(sizeof(Sommet));
    if (!This) return NULL;
    Sommet_Init(This,i,x1,y1);
    return This;
}

//---------------affichage du sommet
void Sommet_Print(Sommet* This){
    printf("sommet : (%d, %.2f, %.2f)\n", This->i, This->x,This->y);
}

// renvoie le sommet qui pour numero i, s il existe dans la liste des sommets
Sommet* TrouveSommet(Sommet_Liste* This,int i){
    if(This==NULL)
        printf("La Liste des sommet est vide\n");
    else
    {
        Sommet_Liste* tmp = This;
        while(tmp != NULL){
             if(tmp->v->i==i )
                  return tmp->v;
             tmp = tmp->suiv;
        }
    }
}

/*----Methode de la liste des sommets---(allocation + initialisation + insertion d'un sommet + affichage de la liste des sommets)----------*/
//void VsListeInit(Sommet_Liste* This);
//initialisation de la liste des sommet 
void VsListeInit(Sommet_Liste* This){
    This->v = NULL;
    This->suiv = NULL;
}

//creation de la liste des sommet segment
Sommet_Liste* NewVsListe(void){
    Sommet_Liste *This = malloc(sizeof(Sommet_Liste));
    if (!This) return NULL;
    VsListeInit(This);
    return This;
}
// Inserer un sommet a la fin de la Liste des sommet
int VsListeInserer(Sommet_Liste* This, Sommet * v){
    if (This->v == NULL){
        This->v = v;
        return 1;
    }
    Sommet_Liste *suiv1 = NewVsListe();
    suiv1->v = v;
     while(This->suiv != NULL){
        This=This->suiv;
    }
    This->suiv = suiv1;
    return 1;
}
//Affichage de la liste des sommet
void PrintVsListe(Sommet_Liste* This)
{
    if (This==NULL)
        printf("La Liste des sommets est vide\n");
    Sommet_Liste* tmp = This;
    while(tmp != NULL)
    {
        if (tmp->v!=NULL)
                Sommet_Print(tmp->v);
        tmp = tmp->suiv;
    }
}
/*------------------Methodes du graphe-----(initialisation + allocation + affichage + ajouter une arete et un sommet)------------------*/
//initialisation du graphe
void GrapheInit(Graphe*This){
    This->n1 = 0;                  //nbre de sommets
    This->m = 0;                   //nbre d'aretes
    This->Sliste = NewVsListe();   // listes des sommets
    This->listA = NewAListe();     //listes des aretes
}

//creation d'un nouveau graphe vide
Graphe* NewGraphe(void){
    Graphe* This = malloc(sizeof(Graphe));    // allocation
    if (!This) return NULL;
    GrapheInit(This);
    return This;
}

//creation d'un nouveau graphe on lui passant la liste des sommet ainsi que la liste des aretes
Graphe* NewGraphe1(Sommet_Liste* S,ElementListeA* A){
     Graphe* This= malloc(sizeof(Graphe));/*nouvau graphe*/
     GrapheInit(This);
     This->Sliste = S;
     This->listA = A;

  return This;
 }
 
//ajouter une arete a un graphe
 void AjoutArete(Graphe* This,int i,int u,int v){
    Arete* a= NewArete(i,u,v);
    AListeInserer(This->listA,a);
    This->m+=1;
}

// Ajouter un sommet a un graphe
void AjoutSommet(Graphe* This,int i,int x, int y){
    Sommet* vs= NewSommet(i,x,y);
    VsListeInserer(This->Sliste,vs);
    This->n1= This->n1+1;
}
//Afficher le graphe donc on affiche tou les sommets et aretes
void GraphePrint(Graphe* This){
    printf("graphe : (%d, %d)\n", This->n1, This->m);
    printf("La liste des sommets\n");
    PrintVsListe(This->Sliste);
    printf("La liste des aretes\n");
    PrintAListe(This->listA);
}
//////-----------------------------(creation du graphe a partir du reseau de l exercice 5)--------------
//creer le graphe a partir du reseau de l'exo 5
Graphe * CreerGrapheReseau(Reseau * R){
    //recupération des sommet du reseau r de l'exo5 + insertion dans  le graphe
    Sommet_Liste * S2=NewVsListe();
    ElementListeA * A2 = NewAListe();
    CelluleLNoeud * cel =R->LNoeuds;
    int i=0;
    while (cel!=NULL){
        
        Sommet * s=NewSommet(cel->ptrnoeud->u,cel->ptrnoeud->x,cel->ptrnoeud->y);
        
        while (cel->ptrnoeud->LVoisins!=NULL){    
            int v =cel->ptrnoeud->LVoisins->v;
            Arete *a =NewArete(i,s->i,v);
            AListeInserer(A2,a);
            AListeInserer(s->L_adj,a);
            s->nbA++;
            i++;
            cel->ptrnoeud->LVoisins=cel->ptrnoeud->LVoisins->voisSuiv;
        }
        
        VsListeInserer(S2,s);
        cel =cel->noeudSuiv;
    }
    Graphe * G2 = NewGraphe1(S2,A2);
    return G2;
}


