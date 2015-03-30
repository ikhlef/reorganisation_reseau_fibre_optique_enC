#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<malloc.h>

#include "Djikstra.h"
#define INFINI 10000

void Initialisation(Graphe * G,Sommet * deb,Dijks * dij,Reseau * r){
     //Initialisation de tous les tableaux a utiliser
    int j;
    for(j=0;j<r->nbNoeuds;j++){
        dij->Dist[j]= 10000;/* on initialise les sommets autres que sdeb (sommet de depart, la racine)à infini */
        dij->Marque[j]= 0;/*Initialiser tous les sommets comme étant "non marqué"(non visiter )*/
        dij->Pred1[j]=-1;
    }
    dij->Dist[deb->i]=0;/* deb étant le point le plus proche du sommet de debut*/
    dij->Marque[deb->i]= 1;//on marque le sommet visité a 1
}

//////////////////-----------------------------
//la fonction poids retourne le poid de l'arete (s1,s2) si s1 et s2 sont voisins (c'est la longueur entre les 2 sommets)
//double a,b,lon;
double Poids(Sommet *s1, Sommet * s2){
    double lon, a, b;
     a=pow((s2->x)-(s1->x),2);
     b=pow((s2->y)-(s1->y),2);
    lon =sqrt((a+b));
    return lon;
}
///////////----------------------------------------

void RemplireDist(Graphe * G,Sommet * sdeb,Dijks * dij){
    //on calcule la distance entre le sommet du debut  et le reste des sommets, si les 2 sommets sont voisin.  sinon on laisse a infini qui est a 10000
    //on parcour les arrete du graphe si on trouve le sommet deb ds une arrete on prend lautre sommet de larete et on calcul le poids
    ElementListeA * A = G->listA;
    while(A!=NULL){
        if ((A->a->u== sdeb->i)||(A->a->v==sdeb->i)){
            if((A->a->u== sdeb->i)){//ici c'est l'arrete (sdeb,a)
                int v = A->a->v;
                Sommet * s1= (Sommet * )TrouveSommet(G->Sliste,v);
                dij->Dist[v]=Poids(sdeb,s1);
            }
            if((A->a->v== sdeb->i)){//ici donc c l'arrete (a,sdeb)
                int v = A->a->u;
                Sommet * s1= (Sommet * )TrouveSommet(G->Sliste,v);
                dij->Dist[v]=Poids(sdeb,s1);
            }
        }
        A=A->suiv;
    }
}

///////////------------------------------------------------

void djikstra1(Graphe* G,Sommet* sDeb,Sommet *sFin, Reseau * r,Dijks * dij){
    Sommet_Liste * S= ( Sommet_Liste *)NewVsListe();
    Tas *Bordure = malloc(sizeof(Tas));
    init(Bordure);//initialisation du Tas ki contiendra l'ensemble(numero du sommet, diastance avec le sommet debut)
    int k;
    for(k=0;k<r->nbNoeuds;k++) {
        if((dij->Dist[k]!=10000)&&(dij->Marque[k]!=1)){
            Element * e =(Element *) nouveauElement(k,dij->Dist[k]);
            insert(Bordure,e);//on rempli le tas
            dij->Marque[k]=1;//on marque les sommet voisin au sommet debut a 1
        }
    }

    while(taill(Bordure)!=0){//tq le tas n'est pas vide
        ElementListeA * A = G->listA;//on recupere la liste des arete du graphe
        Element *e1 = (Element *)min(Bordure);//on prend le min du tas
        suppMin(Bordure);//on supprime le min du tas
        dij->Marque[e1->numero]=1;
        
	while(A!=NULL){
            if ((A->a->u== e1->numero)||(A->a->v==e1->numero)){
                
		if((A->a->u== e1->numero)){
                    int v = A->a->v;
                    Sommet * s1=(  Sommet *)TrouveSommet(G->Sliste,e1->numero);
                    Sommet * s2=(  Sommet *)TrouveSommet(G->Sliste,v);
                    double d1 = dij->Dist[e1->numero];
                    double d2 = dij->Dist[v];
                   
		     if((d2) > (d1+Poids(s1,s2))){
                        dij->Dist[v] = d1+Poids(s1,s2);
                        dij->Pred1[v]=s1->i;
                        Element*e2= (Element*)nouveauElement(v,dij->Dist[v]);
                        insert(Bordure,e2);
                        dij->Marque[v]=1;
                     }
                }
                if((A->a->v== e1->numero)){
                    int v = A->a->u;
                    Sommet * s1=(Sommet *) TrouveSommet(G->Sliste,e1->numero);
                    Sommet * s2=(Sommet *)TrouveSommet(G->Sliste,v);
                    double d1 = dij->Dist[e1->numero];
                    double d2 = dij->Dist[v];
                    if((d2) > (d1+Poids(s1,s2))){
                        dij->Dist[v] = d1+Poids(s1,s2);
                        dij->Pred1[v]=s1->i;
                        Element*e2= ( Element*)nouveauElement(v,dij->Dist[v]);
                        insert(Bordure,e2);
                        dij->Marque[v]=1;
                    }
                }
            }
            A=A->suiv;
        }
    }
    Sommet* s3= sFin;
    VsListeInserer(S,s3);
    while((s3!=sDeb)&&(dij->Pred1[s3->i]!=-1)){
        s3= (Sommet*)TrouveSommet(G->Sliste,dij->Pred1[s3->i]);
        VsListeInserer(S,s3);
    }
    VsListeInserer(S,sDeb);
    printf("le chemin: \n");
    PrintVsListe(S);
}

