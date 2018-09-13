#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphes-chevauchement.h"

/***********************************************************************************************************************************************

*************************************           FONCTIONS OBLIGATOIRES : DEBUT          ********************************************************

************************************************************************************************************************************************/

char * getFragment(Sommet s) // Retourne le fragment stocké a un sommet
{
	return s -> fragment; 
}


LISTE_frag fsd(LISTE_frag S) // S est une liste chainee de chaines de caracteres ,fsd(S) supprime de la liste S toutes les chaines qui sont facteur d'une autre chaine
{
    if (S != NULL) 
    {  
        LISTE_frag liste1 = S;
        while (liste1 -> suivant != NULL) 
        {       // Parcours de la liste de fragments de S jusqu'a sa fin exclue (NULL)
            LISTE_frag liste2 = getSuivant(liste1);
            while (liste2 != NULL) 
            {      // Parcours de la liste  suivante de fragments de S jusqu'a sa fin exclue (NULL)
                             
                if (strstr(liste1 -> frag, liste2 -> frag) != NULL) // Suppression du fragments si fragment liste 2 facteur de fragment liste 1
                {         
                    S = defiler(S, liste2 -> frag);                 
                } 
                else if (strstr(liste2 -> frag, liste1 -> frag) != NULL) // Suppression du fragments si fragment liste 1 facteur de fragment liste 2  
                {                  
                    S = defiler(S, liste1 -> frag);                    
                }
                liste2 = getSuivant(liste2); // incrementer curseur liste
            }
            liste1 = getSuivant(liste1); // incrementer curseur liste
        }    
    }
    return S; // retourne liste S sans  de caractères chaines facteurs d'une autre
}


// x et y sont des chaines de caracteres, lplc(x, y) retourne la longueur du plus long suffixe de x qui est un prefixe de y
int lplc(char * x, char * y) 
{
    int lenboucle = (int)strlen(x)-1; // Determine la longueur sur laquelle boucler
    int lplc = 0;
    int j =0;
    
    for (int i=lenboucle; i >= 0 ; i--) 
    {
        char* s1 = subString(x, i, lenboucle); // Extraction des suffixes de x
        char* s2 = subString(y, 0, j); // Extraction des prefixes de y        
        j += 1;
        if (strcmp(s1, s2) == 0) // si les substrings matchent
        {
            lplc = (int)strlen(s1); // Si suffixe substring1 = prefixe substring2, lplc=longueur substring
        }
    }
    return lplc; // retourner la longueur du plus long suffixe de substring1 qui est un prefixe de substring 2
}


// Lit le fichier et en retourne une liste chainee de fragments d'ADN
LISTE_frag initListeFragments(LISTE_frag S, char * nomf) 
{
    FILE* fichier = fopen(nomf, "r"); 
    if (fichier != NULL)
    {
        char* tmpFrag = (char*)malloc(sizeof(char)); // Pour lire les lignes,declaration d'une chaine de caractere de taille minimale

        while (fscanf(fichier,"%s\n",tmpFrag) != EOF) //A chaque ligne lue, allocation mémoire proportionelle à la taille de la ligne et stockage dans variable
        {
            size_t taille = strlen(tmpFrag);
            char* nouveauFrag = (char*)malloc(taille*sizeof(char)); // Allocation memoire selon la taille de fragTemp
            nouveauFrag = strncpy(nouveauFrag, tmpFrag, taille); // Sauvegarde dans nouvelle variable
            S = enfiler(S, nouveauFrag); // Insertion EN FIN de liste dans la liste de fragments.
        }
        free(tmpFrag); // fix : optimisation memoire
        fclose(fichier);
    }
    return S;
}


void construitGrapheChevauchement(GRAPHE G, LISTE_frag S)
{
    /* 
  
  initialiser les sommets du graphe a partir de S
  Pour chaque couple (x, y) de sommets distincts de G faire
       m <- lplc(getFragment(x), getFragment(y))
       si m <> 0 
          ajouter l'arc (x, m, y) a G
  */

    int length = lenListe(S);
    for(int i=0; i<length; i++)
    {
        if (S != NULL)
        {
            putEtiquette(G,i,S->frag);
            S=S->suivant;
        }

    }

    for(int i=0; i<getNbSommets(G); i++)
    {
        for(int j=0; j<getNbSommets(G); j++)
        {
            if (j!=i)
            {
                Sommet a = getSommet(G,i);
                Sommet b = getSommet(G,j);
                int m = lplc(a->fragment,b->fragment);
                if(m!=0)
                {
                    nouvelArc(G,i,m,j);
                }
            }
        }
    }
}


// Parcours un graphe en profondeur et affiche ses sommets à l'ecran
void parcoursEnProfondeur(GRAPHE G) 
{

    int * marque = (int*)malloc(sizeof(int)); // Futur FLAG pour parcours sommet : tous initialisés à 0. Si sommet visité, FLAG=1 (TRUE) 

    for (int i = 0; i < getNbSommets(G); i++) // Intiialiser le FLAG à 0 pour tous les sommets du graphe
    {
        marque[i] = 0;       
    }
    for (int i = 0; i < getNbSommets(G); i++) // Visiter tous les sommets pas encore visités et marquer son passage avec FLAG=1
    {
        if ( marque[i] == 0)
        {
            visiteEnProfondeur(G, i, marque);       
        }
    }
}

/***********************************************************************************************************************************************

*************************************           FONCTIONS OBLIGATOIRES : FIN         ***********************************************************

************************************************************************************************************************************************/


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                                                                         //
// INFORMATION : lire le .h pour une meilleure description des fonctions   //
//                                                                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


GRAPHE construitGrapheChevauchement_custom(GRAPHE G, LISTE_frag S) {  // V2

       /* 
  
  initialiser les sommets du graphe a partir de S
  Pour chaque couple (x, y) de sommets distincts de G faire
       m <- lplc(getFragment(x), getFragment(y))
       si m <> 0 
          ajouter l'arc (x, m, y) a G
  */

    // Initialisation de G    
    G = nouveauGraphe(lenListe(S));    

    // Remplissage des sommets de G
    int countsommet = 0;
    while (S != NULL) {
        G ->t[countsommet] = empilerNouveauSommet(S -> frag); // Ajout en tete 
        G -> t[0] -> successeurs = NULL;
        S = getSuivant(S);
        countsommet ++;
    }

    //Les sommets sont empilés donc gestion par ordre inverse par rapport a l'insertion
    for (int i=0; i < getNbSommets(G)-1; ++i) 
    {
        for (int j=i+1; j < getNbSommets(G); ++j) 
        {
            // Comparaison des suffixes et prefixes            
            int lenplc = lplc(getFragment(G -> t[i]), getFragment(G -> t[j])); // poids ARC SENS arc1 --> arc2 
            if (lenplc != 0) 
            {                
                G -> t[i] -> successeurs = enfilArc(G -> t[i] -> successeurs, lenplc, j);       // Cree arc pondéré par valeur lenplc
            }

            int lenplc2 = lplc(getFragment(G -> t[j]), getFragment(G -> t[i]));   // poids ARC ANTISENS arc1 <-- arc2         
            if (lenplc2 != 0) 
            {
                G -> t[j] -> successeurs = enfilArc(G -> t[j] -> successeurs, lenplc2, i);      // Cree arc pondéré par valeur lenplc
            }            
        }
    }
    return G; // Retourner le graphe de chevauchement pondéré 
}


void putEtiquette(GRAPHE g, int num, char * etiquette) //Ajouter du contenu aux fragments contenu dans les sommets du graphe
{
    g->t[num]->fragment=etiquette;
}


Sommet getSommet(GRAPHE g, int k) // Retourne un sommet
{
    if(!estVideGRAPHE(g))
    {
        return g->t[k];
    }
    return NULL;
}


int lenListe(LISTE_frag L) // Retourne la longueur de la liste de fragments
{
    int i = 0;
    LISTE_frag Lfrags = (LISTE_frag)malloc(sizeof(struct fragment));
    Lfrags = L;

    while( (Lfrags != NULL) )
    {
        i++;
        Lfrags = Lfrags->suivant;
    }
    return i;
}


void nouvelArc(GRAPHE g, int s, float val ,int dest) // Ajoute un nouvel arc en tete de liste des arcs
{
    g->t[s]->successeurs= ajoutEnTete(g->t[s]->successeurs,val,dest);
}


LISTE_arc ajoutEnTete(LISTE_arc liste, int valuation, int destination) // Retourne la liste avec un nouveau maillon en tete
{
    //2.Creer un nouvel element de type liste
        LISTE_arc liste_nouveau =(LISTE_arc)malloc(sizeof(LISTE_arc));
        
        //3.Verifier que la liste a bien ete cree
        if (liste_nouveau != NULL)
        {
            //4.Assigner valuation au nouvel element de la liste
            liste_nouveau->poids = valuation;
            
        //5.Assigner destination au nouvel element de la liste
                liste_nouveau->destination =  destination;
                
                
        //6. Assigner suivant au nouvel eelement de la liste                
                liste_nouveau->suivant = liste;
    
        //7.Faire pointer le sommet de la liste sur cet élément
                liste = liste_nouveau;
        }
        return liste;
}


void visiteEnProfondeur(GRAPHE g, int s, int * marque) // Visite en profondeur du graphe
{
	marque[s] = 1; // FLAG (1 : sommet deja visité  0:jamais visité)
    printf("        %s %d %s%s\n", "Sommet ", s, " - ", getFragment(g -> t[s]));
	while (g -> t[s] -> successeurs !=NULL) 
    {        
		int dest = g -> t[s] -> successeurs -> destination;

        if (marque[dest] == 0) //visite recursive du sommet du graphe si non flaggé
        {    
			visiteEnProfondeur(g, dest, marque);  
		}
        g -> t[s] -> successeurs = getSuivantArc(g -> t[s] -> successeurs);
	}
}


GRAPHE nouveauGraphe(int n) // Initialise et retourne un nouveau graphe
{
    GRAPHE G = (GRAPHE)malloc(sizeof(struct _GRAPHE));
    G -> nbSommets = n;
    G -> t = (Sommet*)malloc(n* sizeof(struct _sommet));
    return G;
}


int getNbSommets(GRAPHE g) // Retourne le nombre de sommets d'un graphe
{
    int nb = 0;
    if (!estVideGRAPHE(g)) 
    {
        nb = g -> nbSommets;   
    }     
    else
    {
        printf("%s\n", "Pas de sommets");
        return EXIT_FAILURE;
    }
    return nb;    
}


int estVideGRAPHE(GRAPHE g) // Teste si un graphe est vide
{  
    if(g == NULL) 
    {
        return 1; // si la le graphe n'est pas vide retourner 1 
    }
    else
    {
        return 0; // si le graphe est vide retourner 0 
    }  
}


LISTE_frag defiler(LISTE_frag S, char * unFrag) // Defile un fragment d'une file de fragments, retourne la liste de framents defilée
{    
    if (S != NULL) 
    {
        if (strcmp(S -> frag, unFrag) == 0) // si frag en tete de file
        {                    
            S = getSuivant(S);
        } 
        else // Si frag pas en tete de liste, parcourir les suivants jusqu'a le retrouver
        {
            LISTE_frag tmp = S; // sauvegarde frags
            while (strcmp(S -> suivant -> frag, unFrag) != 0) //recherche
            {            
                S = getSuivant(S);
            }
            //suppression et restauration de la tete de file
            S -> suivant = S -> suivant -> suivant;
            S = tmp;
        }
    }
    return S;
}


char * subString(char * chaine, int start, int end) // retourne le substring d'une chaine de caracteres
 {
    char * subString = NULL;
    int i;
    int len = end - start + 1;
    subString = (char*)malloc((size_t)len * sizeof(char));

    for (i = start; i <= end; ++i) // Construction du substring
    {
        subString[i-start] = chaine[i]; 
    }
    subString[i-start] = '\0';

    return subString;
}


LISTE_frag getSuivant(LISTE_frag listefragx) // Retourne l'element suivant d'une liste chainee de fragments
{
    return listefragx -> suivant;
}


LISTE_arc getSuivantArc(LISTE_arc listearcsx) // Retourne l'element suivant d'une liste chainee d'arcs
{
    return listearcsx -> suivant;
}


void printFrags(LISTE_frag LF) // Affihe une liste de fragments si possible
{
    if (LF != NULL) 
    {
        int count=0;
        while (LF != NULL) 
        {
            printf("\t%d. %s\n",count,LF -> frag);
            LF = getSuivant(LF);
            count++;
        }
    }
}


void printCARDSommet(int i,int sens) // Utilisé dans liste d'arcs pour afficher le bon numero de sommet independamment des arcs
{
    if(sens == 0)
    {
        printf("\t Sommet %d ------- ",i);
    }
    else
    {
        printf("\t Sommet %d <------ ",i);
    }
}


void printArc(LISTE_arc La,int i) // Affiche une liste d'arcs
{
    if (La != NULL)
    {
        int antisens=0;
        while (La != NULL) 
        {
            printCARDSommet(i,antisens);
            if(antisens == 0) // Affiche les sommets basiquement de manière graphique selon l'orientation de l'arc //  FLAG : a corriger 
            {
                printf("%d%s%d\n", La -> poids, " --------> Sommet ", La -> destination);
                antisens=1;
            }
            else
            {
                printf("%d%s%d\n", La -> poids, " --------- Sommet ", La -> destination);
                antisens=0;
            }
            La = getSuivantArc(La);
        }
        printf("\n");
    }
}


LISTE_frag enfiler(LISTE_frag S, char * k) // Retourne une liste de fragments avec le fragment ajouté en tête de liste
{
    LISTE_frag e = (LISTE_frag)malloc(sizeof(struct fragment));
    e -> frag = k;
    e -> suivant = S; 
    return e;
}


LISTE_arc enfilArc(LISTE_arc A, int val, int dest) // Retourne une liste d'arcs avec l'arc ajouté en tete de liste
{
    LISTE_arc La = (LISTE_arc)malloc(sizeof(struct ELEMENT));
    La -> poids = val;
    La -> destination = dest;
    La -> suivant = A;
    return La;
}


Sommet empilerNouveauSommet(char * e) // Initialise et retourne un nouveau sommet
{
    Sommet nouveauSommet = (Sommet)malloc(sizeof(struct _sommet));
    nouveauSommet -> fragment = e;
    nouveauSommet -> successeurs = NULL;
    return nouveauSommet;
}