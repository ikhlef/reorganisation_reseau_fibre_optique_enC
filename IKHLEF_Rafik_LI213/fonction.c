#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <math.h>

#include "fonction.h"

//-------------copie d une chaine extraire et recuperation de la sous chaine
void Recuperation_sous_chaine(char* dest, char* src, int debut, int fin){
    if (src == NULL)
        return;
    strncpy(dest, &src[debut], (fin-debut)); //copier les (fin-debut) octés de la chaine de caractere lu depuis src dans le dest.
    dest[(fin-debut)] = '\0';                // caractere de fin de chaine

}
//------------indice du caractere "c" dans la chaine passé en parametre,
int Numero_Indice(char* src, char c){
    int i;
    for(i=0; i< strlen(src); i++)
    {
        if (src[i] == c)
            return i;
    }
    return -1;
}
 /*------------------------------exercice 1 question 1------------------------------------------*/

 //...........................inserer un point a la fin d'une chaine des points.................
void Ajouter_Point_Chaine_Fin(Chaine* ch, Point* p){

    if (ch->uneExtremite == NULL){
        ch->uneExtremite = p;
        return;
    }

       Point* tmp = ch->uneExtremite;
       while(tmp->ptSuiv!= NULL)
               tmp= tmp->ptSuiv;
       tmp->ptSuiv = p;
}

//----ajouter une chaine a la fin de la liste des chaines ..........................

void Ajouter_Chaine_Fin(ListeChaine* liste, Chaine* ch){
    if (liste->LCh == NULL){
        liste->LCh = ch;
        return;
    }
   Chaine* tmp = liste->LCh;                   // ajout en fin de liste
    while(tmp->chSuiv != NULL)
        tmp = tmp->chSuiv;
    tmp->chSuiv = ch;
}

//.....................................
Chaine* Analyser_Chaine1(char* ligne){
    Chaine* chtmp = (Chaine*)malloc(sizeof(Chaine));//allocation et initialisation d'une chaine a null
    chtmp->uneExtremite = NULL;
    chtmp->chSuiv = NULL;

	// Lire les parametre de la chaine
    int indice = Numero_Indice(ligne, ':');                                    // reuperer l'indice du caractere ':' dans le tableau
    char tab_param[20];                                                       //tab_param[20]={h 3 4}; , dans l exemple ligne
    Recuperation_sous_chaine(tab_param, ligne,0, indice-1);

    int numero, nbPoints;
    sscanf(tab_param,"h %d %d", &numero, &nbPoints);   //lire depuis tab_param le numero de la chaine et le nbre des points de la chaine

    chtmp->numero = numero;                           //affecter le numero de la chaine a la chaine allouer, dans l exemple : numero =3
    chtmp->nbPoint = nbPoints;                        //affecter le nbre de points de la chaine a la chaine allouer, dans l exemple nbPoints=4

    // Lecture  des Points de la chaine
    char tab_point[5000];
    Recuperation_sous_chaine(tab_point, ligne, indice+2, strlen(ligne)-1);  //recuperation de la liste des points de la chaine, dans l exemple
                                                                            // 14.05 98.12 / 19.41 97.13 / 22 96.05 / 20.09 94.55 /
    int i;
    for(i = 0; i<nbPoints;i++){
        Point* p = (Point*) malloc(sizeof(Point));         //allocation d'un point p et initilaisation des parametres du point p.
        p->ptSuiv = NULL;

        float x,y;                                           // recuperation des coordonnées x, y depuis le reste de la chaine passé en parametre.
        int pointlimit = Numero_Indice(tab_point, '/');
        char strp[50];
        Recuperation_sous_chaine(strp, tab_point, 0, pointlimit-1);                       //reccuperation du point a traiter
        Recuperation_sous_chaine(tab_point, tab_point, pointlimit+2, strlen(tab_point)); //recuperation de la liste des points de la chaine
        sscanf(strp, "%g %g", &x,&y);                                                    // qui reste a traiter
                                                                                        //  printf("%s \n", strp);
        p->x = x;
        p->y = y;
       Ajouter_Point_Chaine_Fin(chtmp, p);
    }

    return chtmp;
}

//----------fonction de lecture de la liste des chaines depuis fichier...............................
  void Lecture_chaine1(FILE* file,ListeChaine* machaine){
    char line[5000];
    int nbChaine = 0;

    fgets(line, sizeof(line), file);
    sscanf(line, "c NbChain: %d", &nbChaine);
    machaine->nbchaine = nbChaine;

    // Lire le nombre maximal de fibre
    int nbMax = 0;
    fgets(line, sizeof(line), file);
    sscanf(line, "c Gamma: %d", &nbMax);
    machaine->gamma = nbMax;

    // Lecture des chaines
    int i = 0;
    for(i=0.; i<= nbChaine;i++){
        fgets(line, sizeof(line), file);
        if (line[0] == 'h'){
            Chaine* nouvelle_chaine = Analyser_Chaine1(line);
            Ajouter_Chaine_Fin(machaine, nouvelle_chaine);
        }
    }
}
 /*-----------------questi 1 a utiliser pour les autres exo ---------------------------------*/

//---ajouter un point a une chaine
//......................Inserer un point  au debut de la chaine....................................
void Ajouter_Point_Chaine(Chaine* ch, Point* p){
    if (ch->uneExtremite == NULL){
        ch->uneExtremite = p;
        return;
    }

    Point* tmp = ch->uneExtremite;
    p->ptSuiv = tmp;
    ch->uneExtremite = p;

}

//--analyse d'une chaine de caractere passer en parametre et renvoie un pointeur sur la chaine
//.exemple ligne=h 3 4 : 14.05 98.12 / 19.41 97.13 / 22 96.05 / 20.09 94.55 /
Chaine* Analyser_Chaine(char* ligne){
    Chaine* chtmp = (Chaine*)malloc(sizeof(Chaine));//allocation et
    chtmp->uneExtremite = NULL;                     //initialisation
    chtmp->chSuiv = NULL;			    //initialisation

	// Lire les parametre de la chaine
    int indice = Numero_Indice(ligne, ':');
    char tab_param[20];                                                       //strparam[20]=h 3 4 , dans l exemple ligne
    Recuperation_sous_chaine(tab_param, ligne,0, indice-1);

    int numero, nbPoints;
    sscanf(tab_param,"h %d %d", &numero, &nbPoints);   //lire depuis strparam le numero de la chaine et le nbre des points de la chaine

    chtmp->numero = numero;                           //affecter le numero de la chaine a la chaine allouer, dans l exemple : numero =3
    chtmp->nbPoint = nbPoints;                        //affecter le nbre de points de la chaine a la chaine allouer, dans l exemple nbPoints=4

    // Lecture  des Points;
    char tab_point[5000];
    Recuperation_sous_chaine(tab_point, ligne, indice+2, strlen(ligne)-1);  //recuperation de la liste des points de la chaine, dans l exemple
                                                                            // 14.05 98.12 / 19.41 97.13 / 22 96.05 / 20.09 94.55 /
    int i;
    for(i = 0; i<nbPoints;i++){
        Point* p = (Point*) malloc(sizeof(Point));         //allocation d'un point p et initilaisation des parametres du point p.
        p->ptSuiv = NULL;

        float x,y;                                           // recuperation des coordonnées x, y depuis le reste de la chaine passé en parametre.
        int pointlimit = Numero_Indice(tab_point, '/');
        char strp[50];
        Recuperation_sous_chaine(strp, tab_point, 0, pointlimit-1);                       //reccuperation du point a traiter
        Recuperation_sous_chaine(tab_point, tab_point, pointlimit+2, strlen(tab_point)); //recuperation de la liste des points de la chaine
        sscanf(strp, "%g %g", &x,&y);                                                    // qui reste a traiter
                                                                                        //  printf("%s \n", strp);
        p->x = x;
        p->y = y;
       Ajouter_Point_Chaine(chtmp, p);
    }

    return chtmp;
}

//----ajout d une chaine dans la liste des chaines.
void Ajouter_Chaine(ListeChaine* liste, Chaine* ch){
    //incremetation du nombre de list de chaine?
    if (liste->LCh == NULL){
        liste->LCh = ch;
        return;
    }
           ch->chSuiv= liste->LCh;
           liste->LCh = ch;
}
//----------lecture de la liste des chaines depuis fichier
  void Lecture_chaine(FILE* file,ListeChaine* machaine){
    char line[5000];
    int nbChaine = 0;

    fgets(line, sizeof(line), file);
    sscanf(line, "c NbChain: %d", &nbChaine);
    machaine->nbchaine = nbChaine;

    // Lire le nombre maximal de fibre
    int nbMax = 0;
    fgets(line, sizeof(line), file);
    sscanf(line, "c Gamma: %d", &nbMax);
    machaine->gamma = nbMax;

    // Lecture des chaine
    int i = 0;
    for(i=0.; i<= nbChaine;i++){
        fgets(line, sizeof(line), file);
        if (line[0] == 'h'){
            Chaine* nouvelle_chaine = Analyser_Chaine(line);
            Ajouter_Chaine(machaine, nouvelle_chaine);
        }
    }
}


 /* .....................................exercice 1 question 2......................................*/

//.....................................fonction d'ecriture (ajouter) d'une chaine des points dans un fichier..........

void Ecrire_Chaine_Fichier(Chaine* ch, FILE* file){

    fprintf(file,"h %d %d : ", ch->numero, ch->nbPoint);
    Point* p = ch->uneExtremite;
    while(p != NULL){
        fprintf(file, "%g %g / ", p->x, p->y);
        p = p->ptSuiv;
    }
    fprintf(file,"\n");                                    //retour a la ligne.
}

//............................................fonction d'ecriture de la liste des chaines dans un fichier.............
void Ecrire_chaine_txt(ListeChaine* listechaine, FILE* file){

    fprintf(file,"c NbChain: %d\n", listechaine->nbchaine);
    fprintf(file,"c Gamma: %d\n", listechaine->gamma);
    fprintf(file,"c \n");

    Chaine* ch = listechaine->LCh;

    int num = 1;
    while(ch !=NULL ){
       // printf("Ecriture de la chaine : %d \n", num);
        Ecrire_Chaine_Fichier(ch, file);
        ch = ch->chSuiv;
        num++;
    }
}

//...........................fonction d'affichage d'un point......................
void Ecrire_Point(Point* This){
    printf("Point : (%.2f ,%.2f)\n", This->x, This->y);
}

//.....................................fonction d'affichage d'une chaine des points........................
void Ecrire_Chaine(Chaine* This){
    printf("Chaine : (%d)\n", This->numero);
    if (This->uneExtremite == NULL){
        printf("La chaine est vide");
    }
    Point* tmp = This->uneExtremite;
    while(tmp != NULL){

        Ecrire_Point(tmp);
        tmp = tmp->ptSuiv;
    }

}

//..........................................fonction d'affichage de la liste des chaines...................

void afficher_ListeChaines(ListeChaine* L){
    printf("%d\n", L->nbchaine);
    printf("%d\n", L->gamma);
    Chaine* ch=L->LCh;

    while(ch!= NULL){
        Ecrire_Chaine(ch);
        ch = ch->chSuiv;
    }
}

/*------------------qst3 exo 1-----------------------------*/

//---------------------------------creer ou dessiner une ligne avec XFIG------------------
       char tab[1024];
char* CreerLigne(int style, int couleur, int size, Point* p1 ,Point* p2, int z){
    
    int x1= (int)(p1->x)*z;
    int y1=(int)(p1->y)*z;
    int x2= (int)(p2->x)*z;
    int y2=(int)(p2->y)*z;

    sprintf(tab,"\n2 1 %d %d %d 7 100 0 -1 0.000 0 0 -1 0 0 2\n         %d %d %d %d",style, size,couleur,x1,y1,x2, y2);
    return tab;
}

//.................................fonction de creation de l'en tete du fichier XFIG....................

char* CreerEntete(){
    return "#FIG 3.2\nLandscape\nCenter\nMetric\nA4\n100.0\nSingle\n-2\n1200 2";
}

//.................................fonction de creation et d ouverture de fiichier XFIG en ecriture......

FILE* CreerFichier(char nomfichier[256]){
    FILE *f = fopen(nomfichier, "w");
    char* entete = CreerEntete();
    fprintf(f,"%s",entete);
    return f;
}

//.................................fonction d'ecriture d'une chaine dans le fichier XFIG.............

void ecrit_chaine_xfig(FILE* f, Chaine* Ch, int zoom, int epaisseur){
    char tab[1024];
    if (Ch==NULL){
        printf("La chaine est vide\n");
    }
    Point* tmp = Ch->uneExtremite;
    while(tmp != NULL){

        if (tmp->ptSuiv!=NULL){
            sprintf(tab,"\n1 4 0 %d 1 7 50 0 -1 0.000 1 0.0000 %d %d 5 5 0 0 0 0",zoom/40,(int)tmp->x*zoom,(int)tmp->y*zoom);
            fputs(tab,f);
            sprintf(tab,"\n1 4 0 %d 1 7 50 0 -1 0.000 1 0.0000 %d %d 5 5 0 0 0 0",zoom/40,(int)tmp->ptSuiv->x*zoom,(int)tmp->ptSuiv->y*zoom);
            fputs(tab,f);
              char* ligne = CreerLigne(0,4,epaisseur,tmp,tmp->ptSuiv,zoom);
              fputs(ligne, f);
        }
        tmp = tmp->ptSuiv;
    }
}

//...............................fonction d'ecriture d'une liste des chaines dans un fichier XFIG...................................;

void ecrit_Lchaine_xfig(FILE* f, ListeChaine* L, int zoom, int epaisseur){

    Chaine *ch = L->LCh;

    while(ch != NULL){
        ecrit_chaine_xfig(f, ch,zoom ,epaisseur);
        ch = ch->chSuiv;
    }
}
/*-----------------------qst 4 exo 1--------------------------*/

//....................................calculer la longueur totale d'une chaine des points...................

double longueurChaine(Chaine *This){
    double lon,lon1;
    if (This==NULL){
        printf("La chaine est vide");
    }
    lon=0;
    Point* ext=This->uneExtremite;
    lon1=0;
    while(ext->ptSuiv !=NULL){

	Point * p1=ext;
        Point* p2=ext->ptSuiv;
        double a=pow((p2->x)-(p1->x),2);
        double b=pow((p2->y)-(p1->y),2);

        lon =sqrt(a+b);
        ext = ext->ptSuiv;
        lon1  =lon1+lon;
    }
  return lon1;
}

//..............................renvoie la longueur totatle de la liste....................;
double longueurTotale(ListeChaine *This){
    double lon,lon1;
    lon = 0;
    if (This==NULL){
       printf("La chaine est vide");
    }
    Chaine* ch=This->LCh;
    lon1=0;
    while(ch !=NULL){
        lon = longueurChaine(ch);
        ch = ch->chSuiv;
        lon1  =lon1+lon;
    }
    printf("Longueur Totale de la liste est : %.2f \n", lon1);
  return 0;
}
//..................................fonction pour caluler le nombre de point de la liste..................

int compte_point(ListeChaine *This){
    if(This== NULL){
        printf("La liste des chaine est vide donc on a 0 point");
    }
    int i=0;
    Chaine* ch=This->LCh;
    while(ch!= NULL){
        i=i+ch->nbPoint;
        ch = ch->chSuiv;
    }
    return i;
}
