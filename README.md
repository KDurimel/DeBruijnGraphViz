# DeBruijnGraphViz
Génération et visualisation de graphes de chevauchements à partir de reads (projet Université)

### Installation
Executer la commande `make`dans le répertoire racine.

### Utilisation
```bash
#Listereads.txt ou tout autre fichier de reads au même format.
./main Listereads.txt 
```
### Fonctionnement
Le script s'execute uniquement si le lien vers le fichier est donné en argument.

L'execution de déroule alors de la manière suivante (description non exhaustive) : 

* initListeFragments initialise une liste de fragments à partir de la lecture d'un fichier : pour chaque ligne lue dans le fichier, un fragment est généré. On peut dire par abus de language que initListeFragments convertit une ligne de fichier en fragment.

* fsd upprime de la liste de fragments toutes les chaines qui sont facteur d'une autre chaine. Cette fonction est appelée pour la construction du graphe de chevauchement.

* lplc ensuite itère sur chaque fragment et en extrait le suffixe et le prefixe : ces 2 sont comparés caractere par caractere et 
lplc retourne la plus grande longueur de matching retrouvé. Cette fonction est appelée pour la construction du graphe de chevauchement.

* construitGrapheChevauchement_custom construit le graphe des chevauchements en initialisant le graphe, puis en attribuant un fragment à chaque sommet du graphe (grace a la liste de sommets) les arcs+valuation et les sucesseurs sont ajoutés par itération sur des fonctions d'ajout d'arcs et sucesseurs respectives.

* Les fonctions d'affichage permettent d'afficher de nombreuses informations sur le contenu du graphe et le contenu de départ ayant permis de le générer: Liste des fragments avant déduplication (i.e suppression des fragments contenant le facteur d'un fragment) ; Liste des fragments après déduplication ; Liste des sommets et fragments dans le graphe. (parcours par ordre d'ajout des sommets) ; Vue des sommes et arcs VALUES du graphe ainsi que leur orientation. (experimental,à réellement verifier) ; Vue du graphe selon un parcours en profondeur : les sommets et leurs successeurs sont visités recursivements et marqués quand visités (condition d'arrêt : tous visités)

### Exemple de sortie graphique
```text
	 *** Fichier  /home/wrecker/DUMMY/graphes/Listereads.txt ***

++++++++++++++ FRAGMENTS AVANT DEDUPLICATION ++++++++++++++


	0. AGGCTTAGAATTAACCCAGGCTTAGC
	1. GCTTAGCAAGGCGCGTCTAAAA
	2. CTAAAATTTCTTGGA
	3. GTCT
	4. GGAATTTCTAT
	5. CTATTGGCTTAAAGT
	6. AAAGTTTCGAATT
	7. TTTCGGAA
	8. TTCTG
	9. AATTCTGGATCTTGC
	10. TGGATCTT
	11. TGGCCAGT
	12. GCGGATTTCGGAA
	13. AAGTGGCCAGTTGCGGA
	14. TTGCGGATTTTCCAGAAGTGG
	15. GCGGATT

++++++++++++++ FRAGMENTS APRES DEDUPLICATION ++++++++++++++


	0. AGGCTTAGAATTAACCCAGGCTTAGC
	1. GCTTAGCAAGGCGCGTCTAAAA
	2. CTAAAATTTCTTGGA
	3. GGAATTTCTAT
	4. CTATTGGCTTAAAGT
	5. AAAGTTTCGAATT
	6. AATTCTGGATCTTGC
	7. GCGGATTTCGGAA
	8. AAGTGGCCAGTTGCGGA
	9. TTGCGGATTTTCCAGAAGTGG

++++++++++++++ SOMMETS ET FRAGMENTS ASSOCIES ++++++++++++++


	Sommet 0 : AGGCTTAGAATTAACCCAGGCTTAGC
	Sommet 1 : GCTTAGCAAGGCGCGTCTAAAA
	Sommet 2 : CTAAAATTTCTTGGA
	Sommet 3 : GGAATTTCTAT
	Sommet 4 : CTATTGGCTTAAAGT
	Sommet 5 : AAAGTTTCGAATT
	Sommet 6 : AATTCTGGATCTTGC
	Sommet 7 : GCGGATTTCGGAA
	Sommet 8 : AAGTGGCCAGTTGCGGA
	Sommet 9 : TTGCGGATTTTCCAGAAGTGG

++++++++++++++++++ GRAPHE : VUE SIMPLIFIEE ++++++++++++++++


	 Sommet 0 ------- 2 --------> Sommet 7
	 Sommet 0 <------ 1 --------- Sommet 4
	 Sommet 0 ------- 1 --------> Sommet 2
	 Sommet 0 <------ 7 --------- Sommet 1

	 Sommet 1 ------- 2 --------> Sommet 8
	 Sommet 1 <------ 2 --------- Sommet 6
	 Sommet 1 ------- 3 --------> Sommet 5
	 Sommet 1 <------ 6 --------- Sommet 2
	 Sommet 1 ------- 1 --------> Sommet 0

	 Sommet 2 ------- 1 --------> Sommet 8
	 Sommet 2 <------ 1 --------- Sommet 6
	 Sommet 2 ------- 1 --------> Sommet 5
	 Sommet 2 <------ 3 --------- Sommet 3
	 Sommet 2 ------- 1 --------> Sommet 0

	 Sommet 3 ------- 1 --------> Sommet 9
	 Sommet 3 <------ 4 --------- Sommet 4

	 Sommet 4 ------- 1 --------> Sommet 9
	 Sommet 4 <------ 4 --------- Sommet 8
	 Sommet 4 ------- 5 --------> Sommet 5

	 Sommet 5 ------- 2 --------> Sommet 9
	 Sommet 5 <------ 4 --------- Sommet 6

	 Sommet 6 ------- 4 --------> Sommet 9
	 Sommet 6 <------ 2 --------- Sommet 7
	 Sommet 6 ------- 1 --------> Sommet 4
	 Sommet 6 <------ 1 --------- Sommet 2
	 Sommet 6 ------- 2 --------> Sommet 1

	 Sommet 7 ------- 2 --------> Sommet 8
	 Sommet 7 <------ 2 --------- Sommet 6
	 Sommet 7 ------- 2 --------> Sommet 5
	 Sommet 7 <------ 4 --------- Sommet 3
	 Sommet 7 ------- 1 --------> Sommet 0

	 Sommet 8 ------- 7 --------> Sommet 9
	 Sommet 8 <------ 5 --------- Sommet 7
	 Sommet 8 ------- 1 --------> Sommet 6
	 Sommet 8 <------ 1 --------- Sommet 5
	 Sommet 8 ------- 3 --------> Sommet 3
	 Sommet 8 <------ 1 --------- Sommet 0

	 Sommet 9 ------- 6 --------> Sommet 8
	 Sommet 9 <------ 1 --------- Sommet 7
	 Sommet 9 ------- 2 --------> Sommet 3
	 Sommet 9 <------ 1 --------- Sommet 1


++++++++++++++++++ PARCOURS EN PROFONDEUR ++++++++++++++++


        Sommet  0  - AGGCTTAGAATTAACCCAGGCTTAGC
        Sommet  7  - GCGGATTTCGGAA
        Sommet  8  - AAGTGGCCAGTTGCGGA
        Sommet  9  - TTGCGGATTTTCCAGAAGTGG
        Sommet  3  - GGAATTTCTAT
        Sommet  4  - CTATTGGCTTAAAGT
        Sommet  5  - AAAGTTTCGAATT
        Sommet  6  - AATTCTGGATCTTGC
        Sommet  2  - CTAAAATTTCTTGGA
        Sommet  1  - GCTTAGCAAGGCGCGTCTAAAA
```
