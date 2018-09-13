#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Construction d'un graphe de chevauchement G = (S, A)
// a partir d'un fichier contenant des fragments d'ADN
// G est un graphe oriente pondere represente par listes d'adjacence 
// un fragment d'ADN est attaché à un sommet
// Il existe un arc de x vers y si il existe un suffixe non vide du fragment attaché à x
// qui est un prefixe du fragment attaché à y


/*****************************************************************************************************
******************        PROTOTYPAGE STRUCTURES ET TYPES SPECIAUX              **********************
******************************************************************************************************/ 

// definition du type arc
typedef struct ELEMENT 
{
  int poids; //poids des arcs
  int destination; // numero du sommet de destination
  struct ELEMENT *suivant;
} ELEMENT;

// definition du type LISTE_arc
typedef ELEMENT *LISTE_arc ;

//definition du type sommet 
struct _sommet 
{
   char *fragment; // le fragment attache au sommet
   LISTE_arc successeurs; // une liste de successeurs
};

// le type pointeur sur _sommet
typedef struct _sommet *Sommet;


// definition du type graphe pondere
typedef struct _GRAPHE 
{
   int nbSommets; //  nombre de sommets du graphe
   Sommet *t;     // un tableau de sommets indicé de 0 à nbSommets-1
} _GRAPHE;

// le type pointeur sur _GRAPHE
typedef struct _GRAPHE *GRAPHE;


// definition du type fragment
typedef struct fragment 
{
  char* frag;
  struct fragment *suivant;
} fragment;

// definition du type liste_frag
typedef fragment* LISTE_frag ;


/*****************************************************************************************************
******************                   PROTOTYPAGE FONCTIONS                      **********************
******************************************************************************************************/  


char* getFragment(Sommet s); // Retourne le fragment attache au sommet s

LISTE_frag fsd(LISTE_frag S); // supprime de la liste de fragments S tous les fragments qui sont facteurs d'un autre fragment

int lplc(char *x, char *y); //Retourne la longueur du plus long suffixe de x qui est un prefixe de y

LISTE_frag initListeFragments(LISTE_frag S, char *nomf); // Initialise l'ensemble S faec les fragments contenus dans le fichier nomf

GRAPHE construitGrapheChevauchement_custom(GRAPHE G, LISTE_frag S); // Construit le graphe de chevauchement pondéré G a partir des fragments contenus dans la liste S

void parcoursEnProfondeur(GRAPHE G); // Afficher le parcours en profondeur d'un graphe G 

void visiteEnProfondeur(GRAPHE g, int s, int * marque); // Affiche le fragment d'un sommet d'un graphe g et parcoure ses successeurs

int getNbSommets(GRAPHE g); // Retourne le nombre de sommets d'un graphe g

int estVideGRAPHE(GRAPHE g); // Retourne 1 si le graphe est vide , 0 sinon

int lenListe(LISTE_frag l); // Retourne la longueur d'une liste de fragments l

LISTE_frag getSuivant(LISTE_frag l); // Renvoie la variable suivante de la liste de fragment suivants l

LISTE_frag defiler(LISTE_frag S, char * frag); // Retire un element frag de la liste ("defiler like")

LISTE_frag enfiler(LISTE_frag l, char * k); // Ajoute un element de valeur k en tete de liste ("enfiler like")

LISTE_arc getSuivantArc(LISTE_arc l); // Renvoie la variable suivante de la liste d'arc suivants l

LISTE_arc enfilArc(LISTE_arc A, int val, int dest); // Insère un élément en tête de liste chaînée d'arcs avec sa valuation val et destination dest

Sommet empilerNouveauSommet(char * e); // Ajoute un nouveau sommet qui contient le fragment e (empiler like)

Sommet getSommet(GRAPHE g, int k); // Renvoie le sommet du graphe a la k-ieme position

GRAPHE nouveauGraphe(int n); // Initialise un graphe de n sommets

void printFrags(LISTE_frag S); // Affiche une liste de fragments S

void printArc(LISTE_arc A, int i); // Affiche une liste d'arcs A a la i-eme position d'un sommet

void printCARDSommet(int i,int sens); // Affiche le bon numero de sommet independamment des arcs

char * subString(char * chaine, int start, int end); // Retourne un substring de start-ième a end-ième position de la chaine initiale dont elle est issue



// ******************************************** FONCTIONS ABANDONNEES apres mise a jour  ******************************************** //

//Fonction abandonnées après passage à une autre version du code, gardées ici pour conserver la possibilité de voir
// l'execution de cette version du code en dé-commentant le code approprié dans le main.

void construitGrapheChevauchement(GRAPHE G, LISTE_frag S);
void putEtiquette(GRAPHE g, int num, char* etiquette);
Sommet getSommet(GRAPHE g, int k);
void nouvelArc(GRAPHE g, int s, float val ,int dest);
LISTE_arc ajoutEnTete(LISTE_arc liste, int valuation, int destination);