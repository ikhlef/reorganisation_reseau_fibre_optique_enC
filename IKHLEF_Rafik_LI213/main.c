#include <stdio.h>
#include <stdlib.h>

#include "fonction.h"
#include "fonction_reseau_exo2.h"
#include "ArbreAVL.h"
#include "exo7.h"
#include "Djikstra.h"

int main(){
//-------------------------------------------EXERCICE 1--------------------------------------------

       printf("Hello world!\n");

 //---------------------------------test_numero1--------00014_burma.cha.....................................
        FILE* file00 = fopen("Instance/00014_burma.cha","r" );                               // ouverture du fichier en lecture
        if (file00==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }

        ListeChaine* liste00 = (ListeChaine*) malloc(sizeof(ListeChaine));  //allocatiion et initialisation (a NULL) d'une liste des chaines.
        liste00->LCh = NULL;
        Lecture_chaine1(file00, liste00);                                     // lecture d'une liste depuis un fichier

        //afficher_ListeChaines(liste00);                                     // affichage de la liste des chaines a la sortie srandard

        FILE *file01 = fopen("burma_test.cha", "w");
        Ecrire_chaine_txt(liste00, file01);                                //ecriture de la liste des chaines dans un fichier *.cha

        FILE* file01_fig = (FILE*)CreerFichier("burma_test.fig");
        ecrit_Lchaine_xfig(file01_fig, liste00,300,1);                   //creation et production du fichier XFIG
        fprintf(file01_fig,"%s","\n");
        fclose(file01_fig);


        longueurTotale(liste00);                                           // longueur totale des chaines de ma liste
        int r00=compte_point(liste00);
        printf("Nombre de point :%d\n",r00);



//-----------------test numero 2--------------00052_berlin.cha-------------------
 FILE* file10 = fopen("Instance/00052_berlin.cha", "r" );
        if (file10==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }
        ListeChaine* liste10 = (ListeChaine*) malloc(sizeof(ListeChaine));
        liste10->LCh = NULL;
        Lecture_chaine1(file10, liste10);

        //afficher_ListeChaines(liste10);

        FILE *file11 = fopen("berlin_test.cha", "w");
        Ecrire_chaine_txt(liste10, file11);
        FILE* file11_fig = (FILE*)CreerFichier("berlin_test.fig");
        ecrit_Lchaine_xfig(file11_fig, liste10,250,1);
        fprintf(file11_fig,"%s","\n");
        fclose(file11_fig);

        longueurTotale(liste10);
        int r10=compte_point(liste10);
        printf("Nombre de point :%d\n",r10);



//------------------------------test numero 3 ------00022_ulysses.cha---------------------------------------
 FILE* file20 = fopen("Instance/00022_ulysses.cha", "r" );
        if (file20==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }
        ListeChaine* liste20 = (ListeChaine*) malloc(sizeof(ListeChaine));
        liste20->LCh = NULL;
        Lecture_chaine1(file20, liste20);

        //afficher_ListeChaines(liste20);

        FILE *file21 = fopen("ulysses_test.cha", "w");
        Ecrire_chaine_txt(liste20, file21);

        FILE* file21_fig = (FILE*)CreerFichier("ulysses_test.fig");
        ecrit_Lchaine_xfig(file21_fig, liste20,250,1);
        fprintf(file21_fig,"%s","\n");

        longueurTotale(liste20);

        int r20=compte_point(liste20);
        printf("Nombre de point :%d\n",r20);

//-------------------test_numero4-----------------plus grand fichier-------07397_pla.cha------------------
 FILE* file40 = fopen("Instance/07397_pla.cha", "r" );
        if (file40==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }
        ListeChaine* liste40 = (ListeChaine*) malloc(sizeof(ListeChaine));
        liste40->LCh = NULL;
        Lecture_chaine1(file40, liste40);

        //afficher_ListeChaines(liste40);

        FILE *file41 = fopen("pla_test.cha", "w");
        Ecrire_chaine_txt(liste40, file41);

        FILE* file41_fig = (FILE*)CreerFichier("pla_test.fig");
        ecrit_Lchaine_xfig(file41_fig, liste40,1,1);
        fprintf(file41_fig,"%s","\n");

        longueurTotale(liste40);

        int r40=compte_point(liste40);
        printf("Nombre de point :%d\n",r40);

//---------------------------------fin de l'exrecice 1-------------------------------------*/

//-------------------------------------------EXERCICE 2-------------------------------

//----------------------------------exercice 2 test numero 1 ----00014_burma.res------------

        FILE* fichier00 = fopen("Instance/00014_burma.res", "r" ); // ouverture en lecture du fichier 00014-burma.res
        if (fichier00==NULL) {
            printf("erreur d'ouverture\n");
            return  0;
        }

        Reseau* res_burma = (Reseau*)malloc(sizeof(Reseau));            //allocation et initialisation d'un reseau
        res_burma->LCommodites = NULL;
        res_burma->LNoeuds = NULL;

        Lecture_Fichier_Reseau(fichier00, res_burma);                   //creation du reseau depuis le fichier *.res
        Afficher_Reseau(res_burma);                                     //affichage du reseau sur la sortie standard

        FILE *fichier01 = fopen("burma_test.res", "w");                 //ouverture du fichier res_burma en ecriture
        ecrit_reseau_disque(res_burma, fichier01);                      // creation d'un fichier reseau depuis un reseau.

        FILE* fichier01_fig = CreerFichierReseau("burma_fig.fig");      // creation du fichier *.fig a partir d'un reseau
        ecrit_reseau_xfig(res_burma,fichier01_fig,300,1);
        fclose(fichier01_fig);

        int i =recherche_voisin(res_burma->LNoeuds->ptrnoeud,0);     // le voinsin d'un noeud
        printf("voisin num : %d\n",i);

        int nbre_cable_res_burma =compteCable(res_burma);            // renvoie le nombre de cable d'un reseau
        printf("nombre de cable : %d\n",nbre_cable_res_burma);

        int k=compare(17.05,16.00,17.00,19.00);                      // la fonction compare.
        printf(" k :%i\n",k);



//----------------------EXERCICE  3--------------------------------------------------

//-------------------------test Numero 1 -----Instance/00014_burma.cha---------------
        //utiliser la fonction lecture chaine on inserant au debut les chaines et les points,
        // redefinir la liste a utilisée pour le reseau
        FILE* f30 = fopen("Instance/00014_burma.cha", "r" ); // ouverture du fichier en lecture
        if (f30==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }
        ListeChaine* liste30 = (ListeChaine*) malloc(sizeof(ListeChaine));  //allocatiion + initialisation d'une liste de chaines.
        liste30->LCh = NULL;
        Lecture_chaine(f30, liste30);                                        //l'insertion des chaines dans la liste de chaines se fait au debut
        FILE *file31 = fopen("exercice3_burma.cha", "w");                           //l'insertion des points dans la chaine se fait aussi au debut.
        Ecrire_chaine_txt(liste30, file31);                                 //ecriture de la liste de chaines dans le fichier exercice3_burma.cha

        Reseau* reseau30 = (Reseau*)malloc(sizeof(Reseau));                  //allocation + initialisation du reseau
        reseau30->LCommodites = NULL;
        reseau30->LNoeuds = NULL;
        recree_reseau(liste30, reseau30);                                  //recree le reseau depuis la liste des chaines
        Afficher_Reseau(reseau30);                                       // afficher le reseau sur la sortie standard
        FILE *file32 = fopen("exercice3_burma.res", "w");                  //creation de l'instance exercice3_burma.res
        ecrit_reseau_disque(reseau30, file32);

        FILE* file33 = CreerFichierReseau("exercice3_burma.fig");         //dessiner le fichier exrecice3_burma.fig
        ecrit_reseau_xfig(reseau30,file33,300,1);
        fprintf(file33,"%s","\n");
        fclose(file33);


//--------------------------------------test numero 2 --------Instance/00022_ulysses.cha---------------
       FILE* fichier30 = fopen("Instance/00022_ulysses.cha", "r" );
        if (fichier30==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }
        ListeChaine* liste31 = (ListeChaine*) malloc(sizeof(ListeChaine));
        liste31->LCh = NULL;

        Lecture_chaine(fichier30, liste31);
        FILE *fichier31 = fopen("exercice3_ulysses.cha", "w");
        Ecrire_chaine_txt(liste31, fichier31);

        Reseau* reseau31 = (Reseau*)malloc(sizeof(Reseau));
        reseau31->LCommodites = NULL;
        reseau31->LNoeuds = NULL;
        recree_reseau(liste31, reseau31);
        //Afficher_Reseau(reseau31);
        FILE *fichier32 = fopen("exercice3_ulysses.res", "w");
        ecrit_reseau_disque(reseau31, fichier32);

        FILE* fichier33 = CreerFichierReseau("exercice3_ulysses.fig");
        ecrit_reseau_xfig(reseau31,fichier33,300,1);
        fprintf(fichier33,"%s","\n");
        fclose(fichier33);

//------------------test numero3---------00052_berlin.cha-----
FILE* foufi30 = fopen("Instance/00052_berlin.cha", "r" );
        if (foufi30==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }
        ListeChaine* liste_foufi31 = (ListeChaine*) malloc(sizeof(ListeChaine));
        liste_foufi31->LCh = NULL;

        Lecture_chaine(foufi30, liste_foufi31);
        FILE *foufi31 = fopen("exercice3_00052_berlin.cha", "w");
        Ecrire_chaine_txt(liste_foufi31, foufi31);

        Reseau* reseau_foufi31 = (Reseau*)malloc(sizeof(Reseau));
        reseau_foufi31->LCommodites = NULL;
        reseau_foufi31->LNoeuds = NULL;
        recree_reseau(liste_foufi31, reseau_foufi31);
        //Afficher_Reseau(reseau_foufi31);
        FILE *foufi32 = fopen("exercice3_00052_berlin.res", "w");
        ecrit_reseau_disque(reseau_foufi31, foufi32);

        FILE* foufi33 = CreerFichierReseau("exercice3_00052_berlin.fig");
        ecrit_reseau_xfig(reseau_foufi31,foufi33,300,1);
        fprintf(foufi33,"%s","\n");
        fclose(foufi33);
/*
//------------------test numero 3--la plus grande instance -07397_pla.cha--------------
        FILE* foufi30 = fopen("Instance/07397_pla.cha", "r" );
        if (foufi30==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }
        ListeChaine* liste_foufi31 = (ListeChaine*) malloc(sizeof(ListeChaine));
        liste_foufi31->LCh = NULL;

        Lecture_chaine(foufi30, liste_foufi31);
        FILE *foufi31 = fopen("exercice3_07397_pla.cha", "w");
        Ecrire_chaine_txt(liste_foufi31, foufi31);

        Reseau* reseau_foufi31 = (Reseau*)malloc(sizeof(Reseau));
        reseau_foufi31->LCommodites = NULL;
        reseau_foufi31->LNoeuds = NULL;
        recree_reseau(liste_foufi31, reseau_foufi31);
        Afficher_Reseau(reseau_foufi31);
        FILE *foufi32 = fopen("exercice3_07397_pla.res", "w");
        ecrit_reseau_disque(reseau_foufi31, foufi32);

        FILE* foufi33 = CreerFichierReseau("exercice3_07397_pla.fig");
        ecrit_reseau_xfig(reseau_foufi31,foufi33,300,1);
        fprintf(foufi33,"%s","\n");
        fclose(foufi33);
*/
//------------------------FIN EXERCICE 3---------------------------

//----------------------------exercie 4-------------------------

//------------------- teste numero 1------Instance/00014_burma.cha-----------------------

        Reseau* res40 = (Reseau*)malloc(sizeof(Reseau));                 //allocation + initoialisation d'un reseau.
        res40->LCommodites = NULL;
        res40->LNoeuds = NULL;
        recree_reseau_hashtable(liste30, res40);
        Afficher_Reseau(res40);

        FILE *file400 = fopen("exercice4_00014_burma.res", "w");
        ecrit_reseau_disque(res40, file400);

        FILE* file410 = CreerFichierReseau("exercice4_00014_burma.fig");
        ecrit_reseau_xfig(res40,file410,300,1);
        fprintf(file410,"%s","\n");
        fclose(file410);
//------------------- teste numero 2------Instance/00022_ulysses.cha-----------------------

        Reseau* res41 = (Reseau*)malloc(sizeof(Reseau));                 //allocation + initoialisation d'un reseau.
        res41->LCommodites = NULL;
        res41->LNoeuds = NULL;
        recree_reseau_hashtable(liste31, res41);
        //Afficher_Reseau(res41);

        FILE *fichier400 = fopen("exercice4_00022_ulysses.res", "w");
        ecrit_reseau_disque(res41, fichier400);

        FILE* fichier410 = CreerFichierReseau("exercice4_00022_ulysses.fig");
        ecrit_reseau_xfig(res41,fichier410,300,1);
        fprintf(fichier410,"%s","\n");
        fclose(fichier410);

//------------------- teste numero 3------Instance/00052_berlin.cha-----------------------

        Reseau* res42 = (Reseau*)malloc(sizeof(Reseau));                 //allocation + initoialisation d'un reseau.
        res42->LCommodites = NULL;
        res42->LNoeuds = NULL;
        recree_reseau_hashtable(liste_foufi31, res42);
        //Afficher_Reseau(res42);

        FILE *fichier433 = fopen("exercice4_00052_berlin.res", "w");
        ecrit_reseau_disque(res42, fichier433);

        FILE* fichier4333 = CreerFichierReseau("exercice4_00052_berlin.fig");
        ecrit_reseau_xfig(res42,fichier4333,300,1);
        fprintf(fichier4333,"%s","\n");
        fclose(fichier4333);


//--------------exercice 5------------test 00014_burma------
printf("-------------------------EXERCIE N°5\n"); 
 FILE* f305 = fopen("Instance/00014_burma.cha", "r" ); // ouverture du fichier en lecture
        if (f305==NULL) {
            printf("erreur ouverture\n");
            return  0;
        }
        ListeChaine* liste305 = (ListeChaine*) malloc(sizeof(ListeChaine));  //allocatiion + initialisation d'une liste de chaines.
        liste30->LCh = NULL;
        Lecture_chaine(f305, liste305);
        afficher_ListeChaines(liste305);
        Reseau* r1 = (Reseau*)malloc(sizeof(Reseau));
        r1->LCommodites = NULL;
        r1->LNoeuds = NULL;
        recree_reseau_Arbre(liste305,r1);
        Afficher_Reseau(r1);

        FILE *file4 = fopen("test_reseau_exo5.res", "w");
        ecrit_reseau_disque(r1, file4);
        FILE* f121 = CreerFichierReseau("exercice5_reseau.fig");
        ecrit_reseau_xfig(r1,f121,300,1);
        fprintf(f121,"%s","\n");
        fclose(f121);

//--------------exercice 6------------test le tas------
printf("-------------------------EXERCIE N°6\n");
Tas *t;
    t = malloc(sizeof(Tas));
    init(t);
    Element * e0 = (Element *)nouveauElement(0,10.2);
    insert(t,e0);
    Element * e1 =(Element *) nouveauElement(1,5.3);
    insert(t,e1);
    Element * e2 = (Element *)nouveauElement(2,23.67);
    insert(t,e2);
    Element * e3 = (Element *)nouveauElement(3,13.87);
    insert(t,e3);
    Element * e4 = (Element *)nouveauElement(4,2.9);
    insert(t,e4);
    printf("taille du tas : %d\n",taill(t));
    AfficherTas(t);
    Element * e = (Element *)min(t);
    printf("le min du tas :(%d, %.2f)\n",e->numero,e->clef);
    printf("\n");
    Element * eR =(Element *)rechercheElement(t,3);
    printf("l'element du tas recherché est : \n");
    AfficherElement(eR);
     printf("\n");
    Element * eR1 =(Element *)rechercheElement(t,7);
    printf("l'element du tas recherché est : \n");
    AfficherElement(eR1);
     printf("\n");
    

//--------------exercice 7------------test le graphe------
 printf("-------------------------EXERCIE N°7\n");
Graphe * G2 =(Graphe *)CreerGrapheReseau(r1);
    GraphePrint(G2);
    //Application de l'algo de dijkstra
    CelluleCommodite *tmp=r1->LCommodites;
    int i1,i2;
    //on parcours la liste des commodité pour récupéré le debut et la fin de chaque chaine
    while(tmp!=NULL)
    {
        i1=tmp->extr1;
        i2 =tmp->extr2;
        Dijks * dij = malloc(sizeof(Dijks));
        Sommet * s=  (Sommet *)TrouveSommet(G2->Sliste,i1);
        Sommet * s1= (Sommet *) TrouveSommet(G2->Sliste,i2);
        Initialisation(G2,s,dij,r1);
        //il fau dabord calcullé la distance entre le sommet debut et le reste des sommets voisin
        RemplireDist(G2,s,dij);
        djikstra1(G2,s,s1,r1,dij);
        tmp=tmp->commSuiv;
    }

return 0;
}
