
#ifndef __STRUCTURE_RESEAU_H__
#define __STRUCTURE_RESEAU_H__
/*Element de la liste des noeuds voisins d'un noeud du reseau */

typedef struct voisin {

    int v; /*Numero du voisin dans le reseau*/
    struct voisin *voisSuiv; /*Pointeur sur le voisin suivant*/

} Voisin;

/*Noeud du reseau*/
typedef struct noeud{

    int u;  /*Numero du noeud dans le reseau*/

    double x,y; /*coordonnees du noeud */
    Voisin * LVoisins; /*Liste des noeuds voisins de u*/

}Noeud;

/*Element de la liste chainee des noeuds du reseau*/
typedef struct celluleLNoeud{

    Noeud *ptrnoeud; /*pointeur sur un noeud du reseau*/
    struct celluleLNoeud * noeudSuiv; /*Noeud suivant dans la liste des noeuds*/

}CelluleLNoeud;

/*Element de la liste chainee des commodites du reseau */
typedef struct celluleCommodite{

    int extr1,extr2;
    struct celluleCommodite* commSuiv;

}CelluleCommodite;

/*Unreseau*/
typedef struct Reseau{

    int nbNoeuds;  /*Nombre total de noeuds dans le reseau*/
    int nbCables;  /*Nombre total de cables dans le reseau*/
    int gamma; /*Nombre maximalde fibres dans le cable*/
    CelluleCommodite *LCommodites;/*Liste des commodites a relier*/
    CelluleLNoeud *LNoeuds;  /*Liste des noeuds du reseau*/

}Reseau;

#endif

