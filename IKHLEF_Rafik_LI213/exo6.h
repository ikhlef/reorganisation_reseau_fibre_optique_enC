#ifndef EXO6_H_INCLUDED
#define EXO6_H_INCLUDED

#define  n 100
typedef struct element{                       // structure d 'un element du tas
     int numero;
     double clef;
}Element;

typedef struct tas{                         // structure du tas ,  tableau d'elements de taille taille=n+1
     Element *tab[n+1];                     // tableau  d'element.
     int taille;
}Tas;

#endif // EXO6_H_INCLUDED
