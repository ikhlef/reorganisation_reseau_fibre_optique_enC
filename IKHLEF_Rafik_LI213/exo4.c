#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>

#include "exo4.h"
///-----------------------exercice 4--------question01--------------
HashTable* Initialiser_HashTable(int size ){

        HashTable *table = malloc(sizeof(struct hashTable*));
        table->taille = size;
        table->count = 0;
        table->listeElement = malloc(sizeof(TElement)*size);

        int i = 0;
        for (i = 0; i<size; i++ ){
            Element *el;
            el = malloc(sizeof(Element));
            el->cle = -1;
            el->suivant = NULL;
            el->valeur = NULL;
            table->listeElement[i] = el;
        }
        return table;
}
//---------------------- la fonction cle ---------------------------
double F(double x, double y){
    return y+(x+y)*(x+y+1)/2;
}

 double a;
 
//---------------la fonction de hachage h(k)--------------------
 int Hash(double x, double y){
a= ((sqrt(5))-1)/2;      
  int  m = 100;
    int cle = F(x, y);
    return floor(m*  (cle*a - floor(cle*a)));              //double floor(double x); c'est la fonction de math.h qui renvoie la valeur entiere. 
}


//--------------------------exercice 4-----question02--------------------------------
//------------------------ verifie si un noeud existe retourne sa valeur sinon retourne null
Noeud* Existe_noeud_hach(int hash, double k, HashTable *table){
    // Le noeud existe retourner sa valeur
    if (table->listeElement[hash] != NULL){
        Element *el = table->listeElement[hash];
        while(el != NULL){
            if (el->cle == k){
                return el->valeur;                        //renvoie la valeur du noeud
            }
            el = el->suivant;
        }
    }
    return NULL;                                        // renvoie null sinon
}

//---------------------------------------question02__exo4---------------
//----------la fonction renvoie un noeud correspondant a un point de la table, si ce point n'existe pas
//--------- elle cree un noeud et l'ajoute dans la table et l'ajoute en tete de la liste LNoeuds du reseau R


Noeud * Recherche_Cree_Noeud_Hashage(Reseau *res, HashTable *table, double x, double y ){
    double kle = F(x, y);
    int hash = Hash(x, y);
    Noeud * no= NULL;
    Noeud* n = Existe_noeud_hach(hash, kle, table);                  //verifie si le noeud existe .
    if (n != NULL){                                                  //si oui, renvoie sa valeur
        return n;
    }
    else{
        // Le noeud n'existe pas; l'inserer dans la table
        no = malloc(sizeof(Noeud));
        no->x = x;
        no->y = y;
        no->u = table->count;
        no->LVoisins = NULL;
        res->nbNoeuds++;
        Element *el = table->listeElement[hash];
        if(el->valeur == NULL){
            el->valeur = no;
            el->cle = kle;
            el->suivant = NULL;

            table->count++;
        }
        else{
            // element prec
            Element *tmp = el;

            while(tmp->suivant != NULL){
                tmp=tmp->suivant;
            }
            Element *nouveau_el = malloc(sizeof(Element));
            nouveau_el->cle = kle;
            nouveau_el->suivant = NULL;
            nouveau_el->valeur = no;
            tmp->suivant = nouveau_el;
        }

        // Inserer l'element en tete de liste LNoeuds du reseau;
        CelluleLNoeud *cel = malloc(sizeof(CelluleLNoeud));
        CelluleLNoeud *tmp = res->LNoeuds;
        cel->ptrnoeud = no;
        cel->noeudSuiv = tmp;
        res->LNoeuds = cel;
        return no;
    }
}
///-----------------------------exercice 4-----question03---------------
// --- la fonction recree le reseau a partir de la liste des chaines en utilisant la table de hachage.

//------------------- complexité pire cas-------, comme cette fonction permis de recree le reseau mais avec une table de hachage et a l aide de la liste des 
// chaines, sachant que la lecture des points a partir de la liste et pour n points données, donc on a un une complexité de O(n) et comme l'insertion se fait au 
// debut de la liste donc complexité en O(1). donc complexité globale pire cas est C(n)=O(n). 
void recree_reseau_hashtable(ListeChaine *L, Reseau * R){
    HashTable *table;
    Chaine* ch=L->LCh;
    R->nbNoeuds = 0;
     if (L!=NULL)
          R->gamma = L->gamma;
    table = Initialiser_HashTable(100);                  //initialiser la table de hachage
    while(ch!= NULL){
        Noeud *n1,*n2;
        Point* tmp = ch->uneExtremite;
        double x=tmp->x;
        double y = tmp->y;
        Noeud *n = Recherche_Cree_Noeud_Hashage(R,table, x, y);        // 
        int extr1 = n->u;
        Point* tmp1 =  tmp->ptSuiv;
        while( tmp1 != NULL){
            double x=tmp1->x;
            double y = tmp1->y;
            n1 = Recherche_Cree_Noeud_Hashage(R,table, x, y);
            tmp1= tmp1->ptSuiv;
        }
        //creer la liste des commodités
        int extr2 = n1->u;
        CelluleCommodite * com =(CelluleCommodite *) malloc(sizeof(CelluleCommodite));
        com->extr1=extr1;
        com->extr2=extr2;
        com->commSuiv=NULL;
        Ajouter1_Cellule_Commodite_Reseau(R,com);
        ch = ch->chSuiv;
    }

    Chaine* ch1=L->LCh;
    while(ch1!= NULL){                //parcourrir les chaines de la liste listechaine.
        Point *pt = ch1->uneExtremite;
        Point *prec = NULL;
        while(pt!=NULL)
        {
            Noeud *n = Recherche_Cree_Noeud_Hashage(R,table, pt->x, pt->y);
            if (pt->ptSuiv != NULL)
            {
                Noeud* _noeud = Recherche_Cree_Noeud_Hashage(R,table, pt->ptSuiv->x, pt->ptSuiv->y);
                if (!Pointvoisin(n->LVoisins, _noeud->u) && !Pointvoisin(_noeud->LVoisins, n->u))
                {
                    Voisin *v = malloc(sizeof(Voisin));
                    v->v = _noeud->u;
                    v->voisSuiv = NULL;
                    n->LVoisins = (Voisin *)ajouter_voisin_liste(v, n->LVoisins);
                }
            }
            if (prec != NULL)
            {
                Noeud* _noeud = Recherche_Cree_Noeud_Hashage(R, table,prec->x, prec->y);
                if (!Pointvoisin(n->LVoisins, _noeud->u) && !Pointvoisin(_noeud->LVoisins, n->u))
                {
                    Voisin *v = malloc(sizeof(Voisin));
                    v->v = _noeud->u;
                    v->voisSuiv = NULL;
                    n->LVoisins = (Voisin *)ajouter_voisin_liste(v, n->LVoisins);
                }
            }
            prec = pt;
            pt= pt->ptSuiv;
        }
        ch1 = ch1->chSuiv;
    }
    R->nbCables = Nombre_Cables(R->LNoeuds);
}
