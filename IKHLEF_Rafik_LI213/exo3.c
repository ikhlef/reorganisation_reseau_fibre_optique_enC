#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>

#include "exo3.h"

//.............permuter deux noeuds de position i et de position j dans la LNoeuds.
void permute(CelluleLNoeud* liste_cellule,int i,int j){
     int s=0;
     int s1=0;

     CelluleLNoeud* celi;
     CelluleLNoeud* celj;
     celi = liste_cellule;
     celj = liste_cellule;

      while(s<i){
         celi =celi->noeudSuiv;          // recuperer la cellule a la ieme position
         s++;
      }
      while(s1<j){
        celj = (CelluleLNoeud*)celj->noeudSuiv;   // recuperer la cellule a la jeme position
        s1++;
      }

     Noeud* tmp = celi->ptrnoeud;                //permutation entre les deux noeuds i et j.
     celi->ptrnoeud = celj->ptrnoeud;
     celj->ptrnoeud = tmp;
 }
//------------------------------TRI-rapide -----------------------------------
//-----------separation de la liste des noeuds-(diviser pour régner)-et recuperer l'indice du pivot
//---------- pour l'utiliser comme indice de debut ou de fin dans la liste des noeuds . comme vu en cours.
//----------compléxité : dans les pire des cas en parcour tout les element de la liste pour la séparation qui est lineaire
//----------O(n)=n
int tri_rapide_separation(CelluleLNoeud* This,int deb,int fin){
   int i;
   int sep=deb+1;
   int s=0;
   double xdeb,xi;

   CelluleLNoeud * cel,*cel1;
   cel = This;
   while(s<deb){
      cel = (CelluleLNoeud*)cel->noeudSuiv;     //recuperer la cellule du debut de la liste a trier
      s++;
   }
   Noeud* noeudd=cel->ptrnoeud;
   xdeb=noeudd->x;
   for(i=deb+1;i<=fin;i++) {
          cel1 =cel->noeudSuiv;

          Noeud* noeudi = cel1->ptrnoeud;
          xi = noeudi->x;
          if(compare(xi,noeudi->y,xdeb,noeudd->y)==0){
              if(i!=sep){
                  permute(This,i,sep);
              }
              sep++;
          }
          cel = (CelluleLNoeud*)cel->noeudSuiv;
       }
       if(sep!=deb+1){
           permute(This,deb,sep-1);
       }
       return sep-1;
 }

//-----------------------fonction de tri rapide-----------------------------
//---la compléxité du tri rapide pour trier une liste de noeuds a n elements est egale a la complexité pour le tri de inf et sup elements ou inf+sup+1=n
//--------compléxité meilleur cas :le nbre de noeuds inf = le nbre de noeuds sup d'ou C(n)=1+C(inf)+C(sup)= n+2C(n/2)= O(n.log²n). ce qui est analogue au tri
//-------par fusion sauf que l'etape fusion n'est pas nécissaire d'ou le tri rapide est plus rapide que le tri fusion.

//------  ------ compléxité pire cas : comme le choix du pivot depond  des noeuds de la liste de noeuds. si l'ensemble des noeuds a trier est classé de
//---------------maniere decroissante, alors le choix de la premiere valeur de la premiere valeur de la liste Lnoeuds produira 2 ensembles de taille 0 et (n-1).
//ce qui n'est pas 2 ensembles de taille egale. dans ce cas la complexité est de O(n²), ce qui revient à effectuer un tri par sélection.

CelluleLNoeud* tri_rapide(CelluleLNoeud *cel,int deb,int fin){
    if (deb<fin){
    int milieu=tri_rapide_separation(cel,deb,fin);
    tri_rapide(cel,deb,milieu);
    tri_rapide(cel,milieu+1,fin);
    }
    return cel;
 }
//---------j'applique le tri rapide a la liste des noeuds une fois que je recupere l'indice de fin de lise ..............
CelluleLNoeud* TriRapide_CelleLNoeud(CelluleLNoeud* liste_noeuds){
    int deb,fin;
    fin=0;
    Noeud* n1;
    Noeud* n=liste_noeuds->ptrnoeud;
    CelluleLNoeud* cel = liste_noeuds;
    deb = 0;                                     // initialiser l'indice du debut de la liste
    while(cel->noeudSuiv!=NULL){                 //parcourir la listes des noeuds, dans le but de recuperer l indice fin de la liste.
         cel =(CelluleLNoeud*)cel->noeudSuiv;
         fin =fin+1;                                                        //pour connaitre le nbre de cellule, (fin).
    }
    n1=cel->ptrnoeud;                                                   //recuperer le dernier element de la liste
    liste_noeuds = tri_rapide(liste_noeuds,deb,fin);                    // trier la liste.
    return liste_noeuds;                                                //renvoie ma liste LNoeuds triée
}
//..fonction ajouter un voisin dans la liste des voisins.meilleur cas O(1), pire cas O(n) parcourir toute la liste et inserer a la fin
Voisin* ajouter_voisin_liste(Voisin* voisin,Voisin* liste_voisin0){
    if(liste_voisin0==NULL){
        liste_voisin0=voisin;
        return liste_voisin0;
    }
    Voisin* tmp = liste_voisin0;
    while(tmp->voisSuiv=NULL){
        if (voisin->v == tmp->v)
            return liste_voisin0;
        tmp=tmp->voisSuiv;
    }
    if (voisin->v != tmp->v)
        tmp->voisSuiv=voisin;
   return liste_voisin0;
}
//-------------------creer la liste des voisins d'un noeud  de la  LNoeuds du reseau------
//-------------------on doit reparcourir la liste des chaines une 2eme fois pour creer la liste des voisins de chaque noeud de la liste LNoeuds.

Voisin* creer_liste_voisin_noeud(Noeud* nd, ListeChaine* list, Reseau* reseau){
   if((reseau==NULL)||(list==NULL)){
    return NULL;
    }

   Chaine * ch= list->LCh;
   Voisin * liste_voisin= NULL;
   while(ch!=NULL){
        Point* p= ch->uneExtremite;
        Point* prec = NULL;
       while(p!=NULL){
           //parcourrir les points de la chaine ch.
           if(((p->x)==(nd->x))&&((p->y)==(nd->y)))
           {
                if(p->ptSuiv!=NULL){
                    Voisin* voisin= malloc(sizeof(Voisin));
                    Noeud * pt = recherche_cree_noeud(reseau,p->ptSuiv->x, p->ptSuiv->y);
                    voisin->v= pt->u;
                    voisin->voisSuiv = NULL;
                    liste_voisin = ajouter_voisin_liste(voisin,liste_voisin);
                }
                if(prec!=NULL){
                    Voisin * voisin1 = malloc(sizeof(Voisin));
                    Noeud * pt = recherche_cree_noeud(reseau,prec->x, prec->y);
                    voisin1->v= pt->u;
                    voisin1->voisSuiv = NULL;
                    liste_voisin =  ajouter_voisin_liste(voisin1,liste_voisin);
                }
            }
            prec=p;
            p=p->ptSuiv;
      }
      ch= ch->chSuiv;
    }
    return liste_voisin;
}

//------------------------------------------exercice 3--question 1-----------
//-------- si le noeud existe dans la liste des noeuds, je renvoie le noeud, sinon je crée un noeud et je le rajoute a sa bonne position dans la liste LNoeuds,
//----------
Noeud * recherche_cree_noeud(Reseau *R, float x, float y){
    Noeud * nd;
    Noeud *noeud1=NULL;
    CelluleLNoeud * liste_cellule = R->LNoeuds;
    while(liste_cellule!=NULL){                 // si le noeud qu on souhaite ajouter a la liste est dans la liste.
        nd =liste_cellule->ptrnoeud;
        if (nd!=NULL){
            if((nd->x==x)&&(nd->y==y)){
                 noeud1 = nd;
            }
        }
        liste_cellule= liste_cellule->noeudSuiv;
    }
    if (noeud1==NULL){                              //si le noeud n'est pas dans la liste des noeuds.
        //creer le noeud. allocation + initialisation
        Noeud * nouveau_noeud = malloc(sizeof(Noeud));
        nouveau_noeud->x = x;
        nouveau_noeud->y = y;
        nouveau_noeud->LVoisins = NULL;
        nouveau_noeud->u = R->nbNoeuds;               //associer le numero du noeud au nouveau noeud cree.
        R->nbNoeuds = R->nbNoeuds + 1;                //incrementer le nbre de noeud
        //creer la cellule noeud. allocation + initialisation
        CelluleLNoeud * cellule = malloc(sizeof(CelluleLNoeud));
        cellule->ptrnoeud = nouveau_noeud;
        cellule->noeudSuiv = NULL;
        Ajouter_Cellule_Noeud_Reseau(R,cellule);
        R->LNoeuds = TriRapide_CelleLNoeud(R->LNoeuds);
        return nouveau_noeud;                      //dans le cas ou le noeud n'est pas dans la liste,je renvoie le nouveau neoud.
    }
    return noeud1;                                 // dans le cas ou le noeud est dans la liste.
}

//-------------------exercice 3 question 2----
//comparer la position de deux points d'une liste selon la coordonnée x et la coordonnée de y.

//donne la valeur absolue de la soustraction x à y
/*double valeur_abs(double x,double y){
    	if(x<y){
	return x - y ;
	}else {
	return y - x;
	}
}

int compare(double x1,double y1,double x2, double y2){
  if ((x1<x2) && (valeur_abs(x1,x2)<0.001 || (y1<y2))){
    return 0;
  }
  else {
   return 1;
  }

}*/
//donne la valeur absolue de la soustraction x à y
double valeur_abs(double x,double y){
	return (x<y)?x-y:y-x;
}
//compare point A et point B,et renvoie 0 si A est inférieur,B sinon (voir la question même pour mieux comprendre)
int compare(double x1, double y1, double x2, double y2){
	return (x1<x2&&valeur_abs(x1,x2)<0.001)?0:(x1>x2)?1:(y1<y2)?0:1;
}
//--------------------exercice 3 question 3----------------
//---- ajouter au debut , une cellule commodité dans la LCommodité du reseau
void Ajouter1_Cellule_Commodite_Reseau(Reseau* res, CelluleCommodite* com){
   if (res->LCommodites == NULL){                                         //cas de base : la liste des commodités est vide = NuLL
        res->LCommodites = com;
        return ;
    }
    CelluleCommodite* tmp = res->LCommodites;                           // ajout (au debut) d'une cellule de commodité dans la liste des commodités du reseau.
    com->commSuiv = tmp;
    res->LCommodites = com;
}
//----------------- fonction pour verifié si un voisin v est dans la liste de voisins
int Pointvoisin(Voisin* vliste, int num){
    Voisin *v = vliste;
    while(v!=NULL){
        if (v->v == num)
            return 1;
        v= v->voisSuiv;
    }
    return 0;
}
//-------------------fonction qui calcule le nombre des cables à partir d'une LNoeuds-----
int  Nombre_Cables(CelluleLNoeud *cellule_noeud1){
    int i=0;
     while(cellule_noeud1 != NULL){
        Noeud * noeud = cellule_noeud1->ptrnoeud;
        Voisin *voisin= noeud->LVoisins;
             while(voisin !=NULL){
                     i = i+1;
                     voisin = voisin->voisSuiv;
                 }
        cellule_noeud1=cellule_noeud1->noeudSuiv;
    }
    return i;
}


//----------------- la fonction qui permet de recreer le reseau a partir d'une liste de chaines.....................
//---la complexité de la fonction recree_reseau depond du nombre de point de la liste des chaines, car je doit creer une LNoeuds et pour chaque cellule Lnoeud
//---d'un noeud je dois lui affecter sa liste des voisins, donc LNoeuds est O(N) et Lvoisins sera aussi en  O(N) dans le cas ou tout les points sont des voisins
//du noeud creer alors C(N)= O(N²).
void recree_reseau(ListeChaine *L, Reseau * R){
    Chaine* ch=L->LCh;
    R->nbNoeuds = 0;
    if (L!=NULL)
      R->gamma = L->gamma;

    while(ch!= NULL){                //parcourrir les chaines de la liste listechaine.
        Noeud *n1,*n2;
        Point* tmp = ch->uneExtremite;   //recuperer le 1er point de ma 1ere chaine de la liste listechaine.
        double x=tmp->x;
        double y = tmp->y;
        Noeud *n = recherche_cree_noeud(R,x,y);
        Point* tmp1 =  tmp->ptSuiv;
        while( tmp1 != NULL){
            double i=tmp1->x;
            double j = tmp1->y;
            n1 = recherche_cree_noeud(R,i,j);

            tmp1= tmp1->ptSuiv;
        }
        int extr1 = n->u;
        int extr2 = n1->u;
        CelluleCommodite * commodite = malloc(sizeof(CelluleCommodite));
        commodite->extr1=extr1;
        commodite->extr2=extr2;
        commodite->commSuiv=NULL;
        Ajouter1_Cellule_Commodite_Reseau(R,commodite);
        ch = ch->chSuiv;
    }
    Chaine* ch1=L->LCh;
    while(ch1!= NULL){                //parcourrir les chaines de la liste listechaine.
        Point *pt = ch1->uneExtremite;
        Point *prec = NULL;
        while(pt!=NULL)
        {
            Noeud *n = recherche_cree_noeud(R, pt->x, pt->y);
            if (pt->ptSuiv != NULL)
            {
                Noeud* _noeud = recherche_cree_noeud(R, pt->ptSuiv->x, pt->ptSuiv->y);
                if (!Pointvoisin(n->LVoisins, _noeud->u) && !Pointvoisin(_noeud->LVoisins, n->u))
                {
                    Voisin *v = malloc(sizeof(Voisin));
                    v->v = _noeud->u;
                    v->voisSuiv = NULL;
                    n->LVoisins = ajouter_voisin_liste(v, n->LVoisins);
                }
            }
            if (prec != NULL)
            {
                Noeud* _noeud = recherche_cree_noeud(R, prec->x, prec->y);
                if (!Pointvoisin(n->LVoisins, _noeud->u) && !Pointvoisin(_noeud->LVoisins, n->u))
                {
                    Voisin *v = malloc(sizeof(Voisin));
                    v->v = _noeud->u;
                    v->voisSuiv = NULL;
                    n->LVoisins = ajouter_voisin_liste(v, n->LVoisins);
                }
            }
            prec = pt;
            pt= pt->ptSuiv;
        }
        ch1 = ch1->chSuiv;
    }
    R->nbCables = Nombre_Cables(R->LNoeuds);
}


