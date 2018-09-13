#include <stdlib.h>
#include "graphes-chevauchement.h"

// Algorithme de construction d'un graphe de chevauchement 

// entree : filename, nom d'un fichier texte contenant des fragments d'ADN
// sortie : G, le graphe de chevauchement 

    /*****************************************************************************************************
    ******************     INITILISATION GRAPHE + PARCOURS -- VERSION ~ OK          **********************
    ******************************************************************************************************/  

int main(int argc, char *argv[]) 
{
    GRAPHE G = NULL; // Initialisation graphe
    LISTE_frag S = NULL; // Initialisation liste de fragments

    if(argc>1) // Gestion d'erreurs minimale pour le fichier : si pas donné en argument, stopper l'exécution.
    {
        char *filename = argv[1];

        printf("\n\t *** Fichier  %s ***\n",filename);
        
        printf("\n++++++++++++++ FRAGMENTS AVANT DEDUPLICATION ++++++++++++++\n\n\n");

        S = initListeFragments(S, filename); //Initialiser la liste de fragments
        printFrags(S); // Afficher la liste de fragments
        

        printf("\n++++++++++++++ FRAGMENTS APRES DEDUPLICATION ++++++++++++++\n\n\n");

        S = fsd(S); // Trimmer les fragments contenant le facteur d'un autre fragment
        printFrags(S); // Afficher la liste de fragments

        
        printf("\n++++++++++++++ SOMMETS ET FRAGMENTS ASSOCIES ++++++++++++++\n\n\n");

        G = construitGrapheChevauchement_custom(G, S); //Construire le graphe de chevauchement

        for (int i=0; i<getNbSommets(G); ++i) // Afficher les sommets et les fragments du graphe de chevauchement
        {
            printf("\t%s%d%s%s\n", "Sommet ", i, " : ", G -> t[i] -> fragment);
        }


        printf("\n++++++++++++++++++ GRAPHE : VUE SIMPLIFIEE ++++++++++++++++\n\n\n");

        for (int i=0; i<getNbSommets(G); ++i) // Afficher tout le graphe par appel de printArc() pour tous les successeurs de tous les sommets
        {
            printArc(G -> t[i] -> successeurs,i);
        } 


        printf("\n++++++++++++++++++ PARCOURS EN PROFONDEUR ++++++++++++++++\n\n\n");

        parcoursEnProfondeur(G); // Afficher le parcours en profondeur du graphe


    //===================================================================================================================== //
    //===================================================================================================================== //
    //===================================================================================================================== //
    //========================================  V1 : FIN D'EXECUTION  ===================================================== //
    //===================================================================================================================== //
    //===================================================================================================================== //
    //===================================================================================================================== //




        /*****************************************************************************************************
        ******************     INITILISATION GRAPHE + PARCOURS -- ANCIENNE VERSION          ******************
        ******************************************************************************************************/  

        /*DECOMMENTER POUR EXECUTER LE CODE BUGGUÉ
        // !! A ameliorer/corriger !!
        printf("\t\t\t A PARTIR D'ICI : ANCIENNE VERSION (BUGUEE)");

        //declarations de variables
        // un graphe
        GRAPHE G2 = NULL;
        // une liste de chaines de caracteres
        LISTE_frag S2 = NULL; 

        printf("\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");

        printf("\n++++++++++++++ FRAGMENTS AVANT DEDUPLICATION ++++++++++++++\n\n\n");

        S = initListeFragments(S2, filename); //Initialiser la liste de fragments
        printFrags(S2); // Afficher la liste de fragments
        

        printf("\n++++++++++++++ FRAGMENTS APRES DEDUPLICATION ++++++++++++++\n\n\n");

        S2 = fsd(S2); // Trimmer les fragments contenant le facteur d'un autre fragment
        printFrags(S2); // Afficher la liste de fragments

        
        printf("\n++++++++++++++ SOMMETS ET FRAGMENTS ASSOCIES ++++++++++++++\n\n\n");

        construitGrapheChevauchement(G2, S2); //Construire le graphe de chevauchement

        for (int i=0; i<getNbSommets(G2); ++i) // Afficher les sommets et les fragments du graphe de chevauchement
        {
            printf("\t%s%d%s%s\n", "Sommet ", i, " : ", G2 -> t[i] -> fragment);
        }


        printf("\n++++++++++++++++++ GRAPHE : VUE SIMPLIFIEE ++++++++++++++++\n\n\n");

        for (int i=0; i<getNbSommets(G2); ++i) // Afficher tout le graphe par appel de printArc() pour tous les successeurs de tous les sommets
        {
            printArc(G2 -> t[i] -> successeurs,i);
        } 


        printf("\n++++++++++++++++++ PARCOURS EN PROFONDEUR ++++++++++++++++\n\n\n");

        parcoursEnProfondeur(G2); // Afficher le parcours en profondeur du graphe


        printf("\n\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n");*/

        printf("\n\n\n");
        return EXIT_SUCCESS;
    }
    else
    {
        printf("Fichier non renseigné ou problème avec le fichier");
        return EXIT_FAILURE;
    }
}