#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>
#include "exo6.h"


//................ fonction racine renvoie 1

int racine(void) {
    return 1;
}

// ---- fonction de verification d'existance d'un pere dans un tas, pour un noeud i.

int hasPere(int i) {
    return i!=racine();
}
//---------------- renvoie le numero du fils gauche d'un noeud i
int filsGauche(int i) {
    return 2 * i;
}
//-------------renvoie le numero du fils droit d'un noeud i
int filsDroit(int i) {
    return 2 * i + 1;
}

//----------------renvoie le numero du pere d'un noeud i
int pere(int i) {
     /* tester si i==1 */
     return i / 2;
}
///////--------------------------------

/*----------------------------Implementation du tas par tableau-----------------*/

//-----allocation + initialisation d'un nouveau element.-----------
Element * nouveauElement(int i, double clef){
    Element * e;
    e = malloc(sizeof(Element));
    e->numero =i;
    e->clef = clef ;
    return e;
}

//----------initialisation d'un tas ------------------
void init(Tas* t) {
    t->taille=0;
    int i;
    for( i=0;i<t->taille; i++){
        t->tab[i]=NULL;
    }
}

//--------renvoie la taille d'un tas-----------
int taill(Tas* t){
    return t->taille;
}

//-----------est un noeud du tas ,renvoie i, si i est plus petit que la taille du tas
int isNoeud(Tas* t,int i) {
    return i<=taill(t);
}
// --- renvoie le numero du noeud fils gauche d'un noeud, s il existe
 int hasFilsGauche(Tas *t,int i) {
    return isNoeud(t,filsGauche(i));
}

//-----renvoie le numero du noeud fils droit d'un noeud, s il existe
int hasFilsDroit(Tas *t,int i) {
    return isNoeud(t,filsDroit(i));
}

// ---- renvoie vrai (0), si le noeud i n'a pas de fils gauche, ni de fils droit
int estFeuille(Tas *t,int i) {
    return !hasFilsGauche(t,i);
}

//----------------echanger deux noeud i,j d'un tas.
void echanger(Tas *t,int i, int j) {
     Element *tmp;
     tmp=t->tab[i];
     t->tab[i]=t->tab[j];
     t->tab[j]=tmp;
}
//----- monter une valeur si la clef d'un noeud est superieure a la clef de son pere. 
void monter(Tas *t,int i) {
     if (!hasPere(i)) return ;       

     int papa=pere(i);
     Element *e1 = t->tab[papa];
     if ( e1->clef>t->tab[i]->clef) {
     echanger(t,i,papa);
     monter(t,papa);
     }
}

//----renvoie l'elment minimum du tas , la racine du tas
Element* min(Tas *t) {
    return t->tab[racine()];
}

//-------------inserer un element dans un tas--------------
int insert(Tas *t,Element *elt) {
     t->taille++;                //incrementer la taille du tableau
     t->tab[t->taille]=elt;      // inserer l element a la fin du tas
     monter(t,t->taille);        
}

//----- renvoie le plus petit fils d'un noeud i
int plusPetitFils(Tas *t,int i) {    
     if (!hasFilsDroit(t,i)) {
     return filsGauche(i);
     } else {
     int fg=filsGauche(i);                  //---le numero du fils gauche d'un noeud i
     int fd=filsDroit(i);                   //---le numero du fils droit d'un noeud i 
     return               
     (t->tab[fg]->clef<t->tab[fd]->clef)?fg:fd;      // renvoie fg si la clef du fils gauche d'un noeud i est infieure a la clef du fils droit, fd sinon.       
     }
}

void descendre(Tas *t,int i) {
     if (estFeuille(t,i)) return;

     int fiston=plusPetitFils(t,i);
  
   if (t->tab[i]->clef > t->tab[fiston]->clef) {
     echanger(t,fiston,i);
     descendre(t,fiston);
     }
}

//--------------------extraction du minimum
void suppMin(Tas *t) {
     /* verification tas non vide */
     echanger(t,t->taille,racine());
     t->taille--;
      descendre(t,racine());
}

//------------------pour la recherche du i eme element, parcours le tableau et on compare au numero de l'element si on le trouve on l affiche

Element* rechercheElement(Tas *t,int i){
    int z=1;
    while(z<=t->taille){
        if (t->tab[z]->numero == i){
        return t->tab[z];
        }
        z++;
        }
        return NULL;
}
//---------------
//void suppElement(Tas *t, int i)  a faire?????????????????
//{
//}

//////--------------- methode d'affichage d'un element----renvoie l'element e-------
void AfficherElement(Element * e){
    if(e==NULL){
    printf("l'element est a null\n");
    }
      else{
	 printf("l'element du tas:(%d, %.2f)\n",e->numero,e->clef);
    }	
}

// ------------- methode d'affichage d'un tas-------renoie un tas t---------
void AfficherTas(Tas * t){
    if (t->taille ==0)
    printf("le tas est vide\n");
    else{
        int i;
        for (i=1;i<=t->taille;i++){
           Element * e=t->tab[i];
           AfficherElement(e);
        }
    }
}
