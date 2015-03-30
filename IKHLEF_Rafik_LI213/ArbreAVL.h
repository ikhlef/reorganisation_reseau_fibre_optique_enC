#include "structure_reseau.h"

typedef struct avl {

    int hauteur; /* hauteur de l’arbre */
    Noeud * noeud;
    struct avl * fg;
    struct avl * fd;

} AVL;
//___________________________________________
void calculerHauteur(AVL* This)// calcul la hauteur dun arbre avl
{
    This->hauteur = (int)(1 + max(H(This->fg), H(This->fd)));
}
//____________________
void AVLInit(AVL* This)
{
    This->noeud = NULL;
    This->fd = NULL;
    This->fg = NULL;
    This->hauteur=-1;

}
AVL* NewAVL(void)
{
    AVL* This = malloc(sizeof(AVL));
    if (!This) return NULL;
    AVLInit(This);
    return This;
}

AVL* NewAVL1(Noeud* n, AVL* fd, AVL* fg)
{
     AVL* This= (AVL*)malloc(sizeof(AVL));/*nouvel arbre*/
     AVLInit(This);
     This->noeud=n;
     This->hauteur=(int) 1 + max(H(fd),H(fg));
     This->fg=fg;
     This->fd=fd;

  return This;
 }

/*------------------------Rotation dans un arbre de recherche-------------*/
AVL* rotDroite(AVL* This)
 {
     AVL* nv=This->fg;
     This->fg=nv->fd;
     nv->fd=This;

     calculerHauteur(This);
     calculerHauteur(nv);

  return nv;
 }

 AVL* rotGauche(AVL* This)
 {

     AVL* nv=This->fd;
     This->fd=nv->fg;
     nv->fg=This;

     calculerHauteur(This);
     calculerHauteur(nv);

 return nv;
 }
 /*----------equilibrer larbre AVL apres insertion ou supression dun noeud pour kil reste tjrs AVL*/

AVL* equilibrer(AVL* This)
{
    if(!This)
		return This;
     AVL* G=This->fg;
     AVL* D=This->fd;

    if(H(G) - H(D) == 2)
    {
        if (H(G->fg) < H(G->fd))
        This->fg = rotGauche(G);
        return rotDroite(This);
    } //else version symétrique

    if (H(G) - H(D) == -2)
    {
        if (H(D->fd) < H(D->fg))
           This->fd = rotDroite(D);

        return rotGauche(This);
    }
  return This;
}
 /*-------parcours prefix d'un arbre de recherche---------*/
 void prefix(AVL *This)
 {
     if (This!=NULL)
     {
        if (This->noeud!=NULL)
             printf("Noeud :(%d,%f,%f,%d)\n",This->noeud->u,This->noeud->x,This->noeud->y,This->hauteur);
        prefix(This->fg);
        prefix(This->fd);
     }
 }

 void infix(AVL *This)
 {
      if (This->fg!=NULL)
         infix(This->fg);
       printf("Noeud :(%d,%.2f,%.2f,%d)\n",This->noeud->u,This->noeud->x,This->noeud->y,This->hauteur);

       if (This->fd!=NULL)
          infix(This->fd);
 }
/*------------------------------------------------------------------
-------------------------AVL Methode------------------------
-------------------------------------------------------------------*/

int max(int i,int j){

     int max;

     if (i<j){
        max=j;
     }
     if (i>=j){
        max=i;
     }

  return max;
}

int H(AVL* This)// donne la hauteur dun noeud dun arbre
    {
        if(This==NULL)
            return -1;
        else
            return This->hauteur;
    }

/*------------------------------Recherche AVL d'un segment-----------------*/

Noeud* rechercheAVL(AVL* avl,double x, double y)
{
   if(avl !=NULL)
   {
        double x1 = avl->noeud->x;
        double y1 = avl->noeud->y;

        if((x1==x)&&(y1==y))
        {
            return avl->noeud;
        }
        else
        {

           if (compare(x1,y1,x,y)==1)
           {
               rechercheAVL(avl->fg,x,y);
           }

           else
                rechercheAVL(avl->fd,x,y);
        }
    }
    else
    {
        return NULL;
    }

}
/*--------------------Insertion dans un arbre AVL----------------*/
AVL* AVLInserer(AVL* This, Noeud * noeud)
{
    float valx=noeud->x;
    float valy=noeud->y;

    if (This == NULL)
    { // premier element de l’ABR
        return NewAVL1(noeud,NULL,NULL);
        printf("insertion racine\n");
    }
    else
    {
     Noeud * noeud1=This->noeud;
     if(noeud1!=NULL)
     {
         if(noeud==noeud1)
             return This;
         else
         {
            float i=noeud1->x;
            float j=noeud1->y;
            if (compare(valx,valy,i,j)==0)
            {  //dans Ag
                if (This->fg==NULL)
                { // nouveau fils gauche
                    AVL* nv=NewAVL1(noeud,NULL,NULL);
                    This->fg=nv;
                } else
                    This->fg=AVLInserer(This->fg,noeud);
            }
            else
            { //dans Ad
                if (This->fd==NULL)
                { // nouveau fils droit
                     AVL* nv=NewAVL1(noeud,NULL,NULL);
                     This->fd=nv;

                } else
                    This->fd=AVLInserer(This->fd,noeud);
            }
           }
     }
    }
    calculerHauteur(This);
    return equilibrer(This);
}
/*-----------------------------qst3 exo 5-----------------------*/
void parcours_arbre_et_creer_celluleNoeud(AVL *This,Reseau *R)
 {
     if (This->fg!=NULL)
         parcours_arbre_et_creer_celluleNoeud(This->fg,R);

     CelluleLNoeud * cellule = malloc(sizeof(CelluleLNoeud));
     cellule->ptrnoeud = This->noeud;
     cellule->noeudSuiv=NULL;
     Ajouter_Cellule_Noeud_Reseau(R,cellule);
     if (This->fd!=NULL)
        parcours_arbre_et_creer_celluleNoeud(This->fd,R);
 }

void recree_reseau_Arbre(ListeChaine * L, Reseau*R)
{
    Chaine* ch=L->LCh;
    R->nbNoeuds = 0;
    AVL * avl=NULL;
    int extr1;
      if (L!=NULL)
          R->gamma = L->gamma;
    while(ch!= NULL)
    {
        //Noeud *n1,*n2;
        Point* tmp = ch->uneExtremite;
        if(tmp != NULL)
        {
            float x=tmp->x;
            float y = tmp->y;
            Noeud *arb = NULL;
            arb = rechercheAVL(avl,x, y);
            //Afficher_Noeud(arb);
            if (arb == NULL)
            {
                //on doi creer le noeud et l'inserer dans l'arbre avl
                Noeud * newnoeud = malloc(sizeof(Noeud));
                newnoeud->x = x;
                newnoeud->y = y;
                newnoeud->LVoisins = NULL;
                newnoeud->u = R->nbNoeuds; //incrementé le nbr de noeud
                R->nbNoeuds = R->nbNoeuds + 1;
                //Afficher_Noeud(newnoeud);
                avl = AVLInserer(avl, newnoeud);
                extr1 = newnoeud->u;
            }else extr1=arb->u;
        }
        int v;
        Point* tmp1 = tmp->ptSuiv;
        while(tmp1 != NULL)
        {
            float x=tmp1->x;
            float y = tmp1->y;
            Noeud *arb1 = NULL;
            arb1 = rechercheAVL(avl,x, y);
            if (arb1 == NULL)
            {
                //on doi creer le noeud et l'inserer dans l'arbre avl
                Noeud * newnoeud1 = malloc(sizeof(Noeud));
                newnoeud1->x = x;
                newnoeud1->y = y;
                newnoeud1->LVoisins = NULL;
                newnoeud1->u = R->nbNoeuds; //incrementé le nbr de noeud
                R->nbNoeuds = R->nbNoeuds + 1;
                avl = AVLInserer(avl, newnoeud1);
                v = newnoeud1->u;
            } else v=arb1->u;
            tmp1 = tmp1->ptSuiv;
        }
        //creer la liste des commodités
        int extr2 = v;
        CelluleCommodite * com = malloc(sizeof(CelluleCommodite));
        com->extr1=extr1;
        com->extr2=extr2;
        com->commSuiv=NULL;
        Ajouter1_Cellule_Commodite_Reseau(R,com);
        ch = ch->chSuiv;
   }
    // creer la liste des voisin de chaque noeuds
    Chaine* ch1=L->LCh;
    while(ch1!= NULL){                //parcourrir les chaines de la liste listechaine.
        Point *pt = ch1->uneExtremite;
        Point *prec = NULL;
        while(pt!=NULL)
        {
            Noeud *n = rechercheAVL(avl, pt->x, pt->y);
            if (pt->ptSuiv != NULL)
            {
                Noeud* _noeud = rechercheAVL(avl, pt->ptSuiv->x, pt->ptSuiv->y);
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
                Noeud* _noeud = rechercheAVL(avl, prec->x, prec->y);
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
 parcours_arbre_et_creer_celluleNoeud(avl,R);
 R->nbCables = Nombre_Cables(R->LNoeuds);
}
