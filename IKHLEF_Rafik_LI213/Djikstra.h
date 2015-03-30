#ifndef DJIKSTRA_H_INCLUDED
#define DJIKSTRA_H_INCLUDED

#include "exo7.h"


#define  n 100
typedef struct dijks
{
     double Dist[n-1];//tableau de distance entre le sommet debut et le reste des sommets
     int Pred1[n-1];//tableau possedant le numero du sommet precedant de chaque sommet
     int Marque[n-1];//tableau qui marque si le sommet est visité ou pas, il a 0 si le sommt n'est pas visité ,1 sinon
}Dijks;


#endif // DJIKSTRA_H_INCLUDED
