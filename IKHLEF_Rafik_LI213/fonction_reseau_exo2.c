#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>

#include "fonction_reseau_exo2.h"


// initialisation d'un noeud a partir d'une ligne lue depuis fichier
Noeud* Recuperation_ligne_Noeud(char* ligne){                                 //la ligne lue depuis un fichier.

    Noeud* noeud = (Noeud*) malloc(sizeof(Noeud));                     // declaration et allocation d'un noeud.
    noeud->LVoisins = NULL;                                            // initialisation de la liste voisin a null

    int numero;
    float x,y;

    sscanf(ligne,"v %d %f %f", &numero,&x,&y);

    noeud->u = numero;                                             // intionlisation du numero du noeud
    noeud->x = x;                                                  // coordonnée x d'un noeud
    noeud->y = y;                                                  // coordonnée y d'un noeud
    noeud->LVoisins = NULL;

    return noeud;                                                  // renvoie le noeud recuperer depuis la ligne
}

//-----------------------------------------------

/// ajouter un element (une CelluleLNoeuds) dans la liste des noeuds du reseau. ( ajouter a la fin de la liste)

void Ajouter_Cellule_Noeud_Reseau(Reseau * res, CelluleLNoeud* cellule){

    if (res->LNoeuds == NULL){                                                   //cas de base : la liste des noeuds du reseau est vide.
        res->LNoeuds = cellule;
        return ;
    }
    CelluleLNoeud* tmp = res->LNoeuds;
    while(tmp->noeudSuiv!= NULL)                                              // recuperer le dernier pointeur null, ajout a la fin.
        tmp= tmp->noeudSuiv;

    tmp->noeudSuiv = cellule;
}

//-----------------------------------------------------
// ajouter une cellule commodité a la liste des commodités du reseau .
void Ajouter_Cellule_Commodite_Reseau(Reseau * res, CelluleCommodite* com){

   if (res->LCommodites == NULL){                                         //cas de base : la liste des commodités est vide = NuLL
        res->LCommodites = com;
        return ;
    }

    CelluleCommodite* tmp =res->LCommodites;        // parcourir la liste des commodités du reseau, et ajouter un element a la afin.

    while(tmp->commSuiv!= NULL)
        tmp= tmp->commSuiv;

    tmp->commSuiv= com;
}
///-------------------------------------------------------

   // ajouter un noeud voisin a la liste des voisins d'un noeud
void Ajouter_Voisin_Noeud(Noeud* noeud, Voisin * v){
    if( noeud->LVoisins==NULL){                                                      //cas de base : la liste des voisins est vide.
       	noeud->LVoisins = v;
        return;
      }
      Voisin* tmp =noeud->LVoisins;
    while ( tmp->voisSuiv !=NULL)
        tmp = tmp->voisSuiv;
    tmp->voisSuiv = v;
}

///-------------------------------------------------------------
//  la fonction de lecture du fichier et d'allocation & initialisation du reseau res.

void Lecture_Fichier_Reseau(FILE* file, Reseau *res){

    char tab[5000];
    // Lire le nombre de Noeud
    int nbNoeud = 0;
    fgets(tab, sizeof(tab), file);
    sscanf(tab, "c NbNodes: %d", &nbNoeud);
    res->nbNoeuds = nbNoeud;

    // Lire le nombre de cable
    int nbCable = 0;
    fgets(tab, sizeof(tab), file);
    sscanf(tab, "c NbCables: %d", &nbCable);
    res->nbCables = nbCable;

    // Lire le nombre maximal de fibre
    int nbMax = 0;
    fgets(tab, sizeof(tab), file);
    sscanf(tab, "c Gamma: %d", &nbMax);
    res->gamma = nbMax;

    // Lecture des Noeuds depuis le fichier passer en parametre et initialisation de la liste chainée des cellules noeuds du reseau.
    int i = 0;
    for(i; i<= nbNoeud;i++){
        fgets(tab, sizeof(tab), file);
        if (tab[0] == 'v'){
            Noeud* nouveau_Noeud = Recuperation_ligne_Noeud(tab);
            CelluleLNoeud * cel1 =(CelluleLNoeud*) malloc(sizeof(CelluleLNoeud));
            cel1->ptrnoeud = nouveau_Noeud;
            cel1->noeudSuiv = NULL;
            Ajouter_Cellule_Noeud_Reseau(res,cel1);
        }
    }

    /* lire la liste des cables du reseau */
    int i1=0;
    int v1,v2;
    for (i1; i1<=nbCable;i1++){
        fgets(tab, sizeof(tab), file);
        if (tab[0] == 'a'){
            sscanf(tab,"a %d %d",&v1,&v2);

            Voisin* V1 = (Voisin*)malloc(sizeof(Voisin));                         //creation de la listes des voisins d'un noeud.
            V1->v = v2;
            V1->voisSuiv = NULL;

            CelluleLNoeud * tmp = res->LNoeuds;
            while(tmp != NULL){
                   if(tmp->ptrnoeud->u==v1){
                      Ajouter_Voisin_Noeud(tmp->ptrnoeud,V1);
                   }
               tmp = tmp->noeudSuiv;
           }
       }
   }

   //Lire la liste des commodites depuis fichier et la rajouter dans le reseau res
    int a1,a2;
    int i2=0;
    while (!feof(file)){    //verifié la fin dans fichier.
       fgets(tab, sizeof(tab), file);
        if (tab[0] == 'k'){
            CelluleCommodite * com = ( CelluleCommodite*)malloc(sizeof(CelluleCommodite));
            sscanf(tab,"k %d %d",&a1,&a2);

            com->extr1=a1;
            com->extr2=a2;
            com->commSuiv=NULL;
            Ajouter_Cellule_Commodite_Reseau(res,com);
        }
     }

}


//--------------------------Question 2----exo2-----------------
 //la fonction comptecable verifiée si la liste des voisins d'un noeud n'est pas vide et calcule le nbre de voisins du noeud de chaque Cellule noeud dans ce cas
 //la elle imcremente nbcales de 1. et      voisin* v =res->LNoeuds->ptrnoeud->LVoisins

 int compteCable(Reseau *res){
    int nbcables = 0;

    if(res->LNoeuds == NULL){
        printf("la liste des cables est vide");
        return 0;
        }
    CelluleLNoeud* cellule_noeud = res->LNoeuds;

        while(cellule_noeud != NULL){
              Noeud * noeud = cellule_noeud->ptrnoeud;
              Voisin *v = noeud->LVoisins;
                    while(v !=NULL){
                            nbcables = nbcables+1;
                            v = v->voisSuiv;
                     }
             cellule_noeud = cellule_noeud->noeudSuiv;
         }
    return nbcables;
  }

//---------------------------------------Question 3----exo2--------------------
void ecrit_reseau_disque(Reseau *res,  FILE *file){
    // Info du reseau
    fprintf(file,"c NbNodes: %d\n", res->nbNoeuds);
    fprintf(file,"c NbCables: %d\n", res->nbCables);
    fprintf(file,"c Gamma: %d\n", res->gamma);
    fprintf(file, "c\n");

    //Ecriture de la liste des noeuds
    CelluleLNoeud* cellule_noeud = res->LNoeuds;
    CelluleLNoeud* cellule_noeud1 = res->LNoeuds;
    while(cellule_noeud != NULL){
        fprintf(file,"v %d %.2f %.2f\n", cellule_noeud->ptrnoeud->u, cellule_noeud->ptrnoeud->x,cellule_noeud->ptrnoeud->y);
        cellule_noeud=cellule_noeud->noeudSuiv;
    }
    fprintf(file, "c\n");
    //Ecriture de la liste des cables
    while(cellule_noeud1 != NULL){
        Noeud * noeud = cellule_noeud1->ptrnoeud;
        Voisin *voisin= noeud->LVoisins;
             while(voisin !=NULL){
                       if ((noeud->u)<(voisin->v)){
                         fprintf(file,"a %d %d\n", noeud->u, voisin->v);
                         voisin = voisin->voisSuiv;
                     }
                     else{
                         fprintf(file,"a %d %d\n", voisin->v, noeud->u);
                         voisin = voisin->voisSuiv;
                     }
                 }
        cellule_noeud1=cellule_noeud1->noeudSuiv;
    }
    fprintf(file, "c\n");

    //Ecriture de la liste des commodites
    CelluleCommodite* commodite = res->LCommodites;
    while(commodite != NULL)
    {
        fprintf(file,"k %d %d\n", commodite->extr1, commodite->extr2);
        commodite=commodite->commSuiv;
    }
}
/*------------------qst4 exo 2-----------------------------*/
/*---------------creer la ligne avec xfig------------------*/
char ligne[1024];
char * CreerLigneReseau(int style, int couleur, int epaisseur,int z, Noeud* noeud1 ,Noeud* noeud2){
    
    int x1= (int)(noeud1->x)*z;
    int y1=(int)(noeud1->y)*z;
    int x2= (int)(noeud2->x)*z;
    int y2=(int)(noeud2->y)*z;
    sprintf(ligne,"\n2 1 %d %d %d 7 100 0 -1 0.000 0 0 -1 0 0 2\n         %d %d %d %d",style, epaisseur, couleur,x1,y1,x2, y2);
    return ligne;
}
//-------------------------------------------------
char* CreerEnteteReseau(){
    return "#FIG 3.2\nLandscape\nCenter\nMetric\nA4\n100.0\nSingle\n-2\n1200 2";
}
//------------------------------------------------------------------
FILE* CreerFichierReseau(char nomfichier[256]){
    FILE *f = fopen(nomfichier, "w");
    char* entete = CreerEnteteReseau();
    fprintf(f,"%s",entete);
    return f;
}
//----------------------------------------------------
Noeud * RechercheNoeud(CelluleLNoeud *cel, int u){
    if(cel==NULL)
    {
        printf("la liste des noeuds est vide");
    }
    CelluleLNoeud *tmp = cel;
    while (tmp->ptrnoeud->u!=u)
    {
        tmp=tmp->noeudSuiv;
    }
    return tmp->ptrnoeud;
}
//----------dessiner les deux points et le segment-------------------------------------------

void ecrit_cable_xfig(FILE* f, CelluleLNoeud* cel,CelluleLNoeud* cel1,int zoom, int epaisseur){
    char tab[1024];
    if (cel->ptrnoeud->LVoisins==NULL)
        return;

    Noeud* tmp = cel->ptrnoeud;
    Voisin* V = tmp->LVoisins;
    if(V != NULL)
    {
        Voisin * v1= V;
        while(v1 !=NULL)
        {
            Noeud * tmp2 = RechercheNoeud(cel1,v1->v);
            sprintf(tab,"\n1 4 0 %d 1 7 50 0 -1 0.000 1 0.0000 %d %d 5 5 0 0 0 0",zoom/50,(int)tmp->x*zoom,(int)tmp->y*zoom);
            fputs(tab,f);
            sprintf(tab,"\n1 4 0 %d 1 7 50 0 -1 0.000 1 0.0000 %d %d 5 5 0 0 0 0",zoom/40,(int)tmp2->x*zoom,(int)tmp2->y*zoom);
            fputs(tab,f);
            char* ligne = CreerLigneReseau(0,4,epaisseur,zoom, tmp,tmp2);
            fputs(ligne, f);
            v1 = v1->voisSuiv;
        }
    }
}
//--------------------------dessiner le reseau R dans le fichier XFIG-------------------------------------------
void ecrit_reseau_xfig( Reseau *R, FILE* f, int zom, int epaisseur){

    CelluleLNoeud *cel = R->LNoeuds;
    CelluleLNoeud *cel1 = R->LNoeuds;

    while(cel != NULL){
        ecrit_cable_xfig(f, cel,cel1,zom,epaisseur);
        cel = cel->noeudSuiv;
    }
}

//------------------------Question5---------------exo2------------
int recherche_voisin(Noeud * noeud, int u){                                    // renvoie la liste des voisins d'un noeud a partir de son numero.
    int i=0;
    //int num;
    Voisin * V= noeud->LVoisins;
    while((V->voisSuiv!=NULL )&&(i!=u)){
        V = V->voisSuiv;
        i=i+1;
    }
    if (i==u)
       return V->v;
    else{
        printf("le noeud n'a pas de voisin");
        return -1;
    }
}
//---------------afficher un voisin ---------------------------
void Afficher_Voisin(Voisin * This)
{
    if(This == NULL)
    {
        printf("La liste des voisins est vide\n");
        printf("\n");
    }
    Voisin * tmp = This;
    while(tmp != NULL)
    {
        printf("%d\n",tmp->v);
        tmp = tmp->voisSuiv;
    }
}
//----------------------------------afficher un noeud---------------------------
void Afficher_Noeud(Noeud* This)
{
    printf("Noeud  %d : (%.2f ,%.2f)\n",This->u, This->x, This->y);
    printf("Laliste des voisins du noeud %d est :\n",This->u);
    printf("\n");
    Afficher_Voisin(This->LVoisins);
}
//--------------------------afficher une cellule noeud d'un reseau------------------
void Afficher_Cellule_Noeud(CelluleLNoeud * This)
{
    if(This == NULL)
    {
        printf("La liste des noeuds est vide");
    }
    CelluleLNoeud * tmp = This;
    while(tmp != NULL)
    {
        Afficher_Noeud(tmp->ptrnoeud);
        tmp = tmp->noeudSuiv;
    }
}
//-----------------afficher une cellule commodité d'un reseau-----------------
void Afficher_Cellule_Commodite(CelluleCommodite * This)
{
    if(This == NULL)
    {
        printf("La liste des commodite est vide");
    }

    CelluleCommodite * tmp = This;
        printf("\n");
        printf("Les commodites du reseau sont :\n");
    while(tmp!= NULL)
    {
        printf("(%d ,%d)\n",tmp->extr1,tmp->extr2);
        tmp = tmp->commSuiv;
    }
    printf("\n");
}
//------------------------------- afficher un reseau----------------------------------------
void Afficher_Reseau(Reseau* This){
    printf("NbNoeuds: %d\n", This->nbNoeuds);
    printf("NbCables: %d\n", This->nbCables);
    printf("Gamma: %d\n", This->gamma);
    Afficher_Cellule_Noeud(This->LNoeuds);
    Afficher_Cellule_Commodite(This->LCommodites);
}
