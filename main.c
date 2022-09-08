//DUMAS Constance et BRARD Elise
//1A Groupe A2
//PROJET DOG

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>//pour la fonction srand, lors de la pioche d'une carte
#include <windows.h>//pour la fonction color, lors de l'affichage
#define STR 20//pour la dimension du tableau des pseudos
#define NB_CARTES_MAX 6
#define NB_PION 4

//Déclaration de notre structure
struct joueur {
    char nom[STR] ;
    int couleur;
    int pioche_joueur [NB_CARTES_MAX] ;
    int equipe ;
    int pion ;
    int ecurie[NB_PION];
};

typedef struct joueur S_Joueur;

//Declaration des sous programmes
void color (int couleurDuTexte, int couleurDuFond);
int menu();
void initialisation_joueur ( S_Joueur tab [], int nbj);
void initialisation_pioche (int tab [][14]);
int piocher_1_carte (int tab [][14]);
int distribution (S_Joueur tab[] , int pioche [][14] , int nbj ,int nb_manche );
void afficher_pioche_joueur (S_Joueur tab [] , int num_joueur );
void echange_carte_debut_manche (S_Joueur tab [], int nbmanche , int nbj);
void afficher_plateau (int *tab, int nbj , int  nbcase);
void* tour_joueur (S_Joueur tab[], int num_joueur,int *tabl, int nb_cases , int* tab_verif_gagnant);
int carte_4 ();
int carte_1 (int verif, int verif_case_depart );
int carte_13 (int verif, int verif_case_depart );
int carte_14 (int verif, int verif_case_depart );
int carte_11 (int num_joueur1, int *tab ,int nbj);
int carte_7 (S_Joueur tabl[],int *tab, int num_joueur , int nb_cases, int nb_joueur);
int avancer_pion (S_Joueur tabl[], int valeur_carte,int *tab, int num_joueur , int nb_cases, int nb_joueur);
void jouer (S_Joueur tab[] , int pioche [][14] , int nbj,int *tabl,int* tab_verif_gagnant );
int test_gagnant_1_joueur ( int* tab_verif_gagnant , int nb_tour, int* tab, int num_joueur, S_Joueur tabl [],int nb_cases );
int test_gagnant_1_equipe ( int nb_tour, int* tab, int num_joueur, S_Joueur tabl [] , int nbj );

//PROGRAMME PRINCIPAL
int main()
{
    int nb_joueur = 0 , nb_manche ,i ,nb_cases , verif_test ;
    int *plateau_jeu=NULL, *tab_verif_gagnant=NULL;
    int pioche [8][14] ;

    nb_joueur = menu() ;
    S_Joueur joueur[nb_joueur];

    nb_cases = 16 * nb_joueur ;

    tab_verif_gagnant=malloc(2*sizeof(int));
    if (tab_verif_gagnant == NULL)
    {
        exit(0); //On vérifie l'allocation mémoire.
    }

//Création et initialisation du plateau de jeu
//La taille de notre plateau varie en fonction du nombre de joueur.
//La boucle "for" nous permet d'initialiser l'ensemble des cases à 0, qui seront considérées comme des cases vides.
    plateau_jeu=malloc(nb_cases *sizeof(int));
    if (plateau_jeu == NULL)
    {
        exit(0); //On vérifie l'allocation mémoire.
    }

    for (i=0; i<nb_cases; i++)
    {
        plateau_jeu[i]=0 ;//vide le plateau
    }
    initialisation_joueur (joueur,nb_joueur) ;
    initialisation_pioche(pioche);
    jouer (joueur , pioche , nb_joueur,plateau_jeu,tab_verif_gagnant);
    return 0;
}

//COLOR
//Ce ss programme permet de varier les couleurs d'affichage.
void color (int couleurDuTexte, int couleurDuFond)
{
  HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDuFond*16+couleurDuTexte);
}

// MENU
// Ce ss programme permet d'afficher les règles et choisir le nombre de joueur.
// Sortie : nombre de joueur, réutilisé dans tout le reste du programme.
    int menu()
{
	int c, nb =0 ;
 	color(15,1);
	printf("   	____  ____  ______           	\n  	\/ __ \/ __ \/ \/ ____\/        	\n 	\/ \/ \/ \/ \/ \/ \/ \/ __       	\n	\/ \/_\/ \/ \/_\/ \/ \/_\/ \/         	\n   \/_____\/\____/  \____\/           	");
 	color(15,0);
	printf("\nQue voulez-vous faire ?\n\n");
	do
	{
    	printf("Pour jouer tapez 1\n");
    	printf("Pour voir le regles tapez 2\n\n");
    	scanf("%d",&c);
    	switch (c)
    	{
        	case 1 : printf("Voulez vous jouer a 4 ou 6 joueurs \n");
            	do {
                	scanf("%d",&nb);
                	if (nb != 4 && nb != 6 )
                	{
                    	printf("Le nombre que vous avez tape n'est pas valide, veuillez recommencer SVP \n");
                	}
            	} while (nb != 4 && nb != 6 );
            	break;
        	case 2 : printf("\n\n BUT DU JEU : On forme des equipes de deux joueurs.\n Chaque joueur essaie d atteindre son ecurie avec ses quatre pions le plus vite possible.\n On deplace les pions en utilisant des cartes.\n Il n est pas possible de gagner la partie de manière individuelle.\n Lorsqu un joueur a atteint l arrivee avec tous ses pions, il aide son partenaire a atteindre lui aussi l arrivee avec ses pions.\n Une fois qu une equipe a atteint l arrivee avec ses huit pions, elle a gagne. \n Cartes \n 2 3 5 6 8 9 10 12 : permettent d avancer le pion de la valeur de la carte\n 1 : 1 pas en avant ou 11 pas en avant ou placer pion sur case depart \n 4 : avancer ou reculer de 4 \n 7 : avancer de 7 avec un  seul pion ou plusieurs et renvoie au nid des autres pions en les depassant\n 11 : echange de pions\n 13 : avancer de 13 ou mettre pion sur case depart\n 14 : joker, prend la valeur de carte que l’on souhaite\n \n\n\n");
            	break;
        	default : printf("Cette option n'existe pas, veuillez recommencer\n\n");
            	break;
    	}
	}while(c != 1 ) ;//Cette boucle while permet de sasuré que le joueur entre un chiffre conforme aux propositions qu'on lui fait
	system ("PAUSE");
	system ("cls");
	return nb ;
}

//INITIALISATION JOUEUR
//Ce ss programme a pour but de récolter les pseudo des joueurs, de former les équipes, de leur attribuer une couleur, un chiffre qui symbolisera leur pion, de vider leurs écuries.
void initialisation_joueur ( S_Joueur tab [], int nbj)
{
    int i,j  ;
    printf("\n Tres bien vous etes donc %d joueurs \nVeuillez a present entrer le pseudo de chacun des joueurs \n",nbj);
    for (i=0; i < nbj ; i++ )
    {
        printf("Joueur %d votre pseudo est : \n",i+1);
        scanf("%s",tab[i].nom );
    }
    system ("PAUSE");
    system ("cls");

    if (nbj == 4 )
    {
        tab[0].equipe = 1 ;
        tab[1].equipe = 1 ;
        tab[2].equipe = 2 ;
        tab[3].equipe = 2 ;
        printf("%s et %s forme l'equipe 1 \n%s et %s forme l'equipe 2 \n " ,tab[0].nom, tab[1].nom,tab[2].nom,tab[3].nom ) ;
    }

    else {
        tab[0].equipe = 1 ;
        tab[1].equipe = 1 ;
        tab[2].equipe = 2 ;
        tab[3].equipe = 2 ;
        tab[4].equipe = 3 ;
        tab[5].equipe = 3 ;
        printf("%s et %s forme l'equipe 1 \n%s et %s forme l'equipe 2 \n%s et %s forme l'equipe 3 \n",tab[0].nom,tab[1].nom,tab[2].nom,tab[3].nom,tab[4].nom,tab[5].nom) ;
    }
    printf("\n\n");

    if (nbj == 4 )
    {
        tab[0].couleur = 10 ; //vert
        tab[1].couleur = 12 ; //rouge
        tab[2].couleur = 11  ;//bleu
        tab[3].couleur = 14  ;//jaune
    }

    else {
        tab[0].couleur = 10 ;//vert
        tab[1].couleur = 12; //rouge
        tab[2].couleur = 11; //bleu
        tab[3].couleur = 14; //jaune
        tab[4].couleur = 7; //violet
        tab[5].couleur = 13;// gris
    }

    for(i=0 ; i<nbj ; i++ )//attribution des pions : chaque joueur déplace des chiffres sur le plateau, ce chiffre lui est propre et correspond à son indice (dans les struct) + 1
        {
            tab[i].pion = i+1 ;
        }

    for (i=0; i < nbj ; i++ )//affichage des couleurs
    {
        color(tab[i].couleur,0) ;
        printf("%s, vous etes cette couleur \n", tab[i].nom) ;
        color(15,0) ;
    }

    for (i=0; i < nbj ; i++ )//initialisation des écuries à 0, soit vide.
    {
        for (j=0; j < NB_CARTES_MAX ; j++ )
        {
            tab[i].ecurie[j]=0;
        }
    }

    system ("PAUSE");
    system ("cls");
}

//INITIALISATION PIOCHE

// Ce ss programme permet d'initialiser la pioche ( 110 cartes ), tableau à 2 dimensions

void initialisation_pioche (int tab [][14])
{
    int i , j ;
    for ( i=0 ; i<8 ; i++)
    {
        for (j=0 ; j < 14 ; j++ )
        {
            tab[i][j]=j+1 ;
        }
    }
    tab [6][13] = 0 ;//car il y a que 6 cartes joker
    tab [7][13] = 0 ;
}

//PIOCHER 1 CARTE
//Ce ss programme permet de piocher une carte aléatoirement et d'enlever cette carte de la pioche en mettant la case à 0
int piocher_1_carte (int tab [][14])
{
    int i=0 , j=0 , carte_tiree = 0;
    srand(time(NULL));
    do {
        i = (rand() % (7 - 0 + 1)) + 0;//génère un nombre aléatoire pour les lignes
        j = (rand() % (13 - 0 + 1)) + 0;//génère un nombre aléatoire pour les colonnes
        carte_tiree = tab[i][j] ;
        tab [i][j] =0 ;
    } while ( carte_tiree == 0) ;//assurance que la carte piochée ne l'a pas déja été

    return carte_tiree ;
}

//DISTRIBUTION
//Ce ss programme permet d'affecter selon la manche un certain nombre de carte à chaque joueur
int distribution (S_Joueur tab[] , int pioche [][14] , int nbj ,int nb_manche )
{
    int i , j ,k , nb_carte_manche, nb_carte_a_distribuer, compteur_carte_pioche=0;
        for(k=0;k<15;k++){//cette boucle permet peut importe le nombre de manche déja joué de savoir combien de carte il faut distribuer
            if(nb_manche == 1+5*k)
            {
                nb_carte_manche= 6;
            }
            if(nb_manche == 2+5*k)
            {
                nb_carte_manche= 5;
            }
            if(nb_manche == 3+5*k)
            {
                nb_carte_manche= 4;
            }
            if(nb_manche == 4+5*k)
            {
                nb_carte_manche= 3;
            }
            if(nb_manche == 5*k)
            {
                nb_carte_manche= 2;
            }
        }
    compteur_carte_pioche=0 ;
    for ( i=0 ; i < 8 ; i++) //compte le nombre de carte qu'il reste dans la pioche
    {
        for ( k=0 ;k < 14 ; k++) //initialisation des cartes de chacun des joueurs, étape indispensable à cause du nombre variant de cartes en fonction de la manche
        {
            if(pioche[i][k] != 0 )//s'il y a une carte le compteur s'incrémente de 1
            {
                compteur_carte_pioche ++ ;
            }
        }
    }
    nb_carte_a_distribuer= nb_carte_manche*nbj ;
    if(nb_carte_a_distribuer > compteur_carte_pioche) //s'il faut distribuer plus de carte au joueur que ce qu'il en reste dans la pioche alors reinitialisation de la pioche
    {
        initialisation_pioche(pioche);
    }

    for ( i=0 ; i < nbj ; i++) //initialisation des cartes de chacun des joueurs, étape indispensable à cause du nombre variant de cartes en fonction de la manche
    {
        for ( j=0 ; j < NB_CARTES_MAX ; j++)
        {
            tab[i].pioche_joueur [j] = 0 ;
        }
    }

    for ( i=0 ; i < nbj ; i++)//distribution du nombre exact de carte (en fonction de la manche) à chaque joueur
    {
        for ( j=0 ; j < nb_carte_manche ; j++)
        {
            tab[i].pioche_joueur [j] = piocher_1_carte(pioche) ;
        }
    }

    return nb_carte_manche ;
}

//AFFICHER PIOCHE JOUEUR
//Ce ss programme permet d'afficher les cartes de chaque joueur.
void afficher_pioche_joueur (S_Joueur tab [] , int num_joueur )
{
    int  j ;
        printf("\n%s Vous avez ces cartes \n\nPour les afficher ", tab[num_joueur].nom) ;
        system("PAUSE");
           for ( j=0 ; j< NB_CARTES_MAX ; j++)
           {
                   color(7,0);
                   printf("(%d)",j+1);//affichage des indices, utile pour les "scanf" qui suivent
                   color(15,0);
                   if(tab[num_joueur].pioche_joueur[j] == 2 || tab[num_joueur].pioche_joueur[j] == 3 || tab[num_joueur].pioche_joueur[j] == 5 || tab[num_joueur].pioche_joueur[j] ==6 || tab[num_joueur].pioche_joueur[j] == 8 ||tab[num_joueur].pioche_joueur[j] == 9 || tab[num_joueur].pioche_joueur[j] == 10 ||tab[num_joueur].pioche_joueur[j] == 12 )
                    {
                        color(15,1);
                        printf("%3.d ",tab[num_joueur].pioche_joueur [j]) ; //affichage des cartes bleues
                        color(15,0);
                        printf(" |");
                    }

                    else if(tab[num_joueur].pioche_joueur[j] == 1 || tab[num_joueur].pioche_joueur[j] == 4 || tab[num_joueur].pioche_joueur[j] == 7 || tab[num_joueur].pioche_joueur[j] == 13 || tab[num_joueur].pioche_joueur[j] == 14 || tab[num_joueur].pioche_joueur[j] == 11 )
                    {
                        color(15,12);
                        printf("%3.d ",tab[num_joueur].pioche_joueur [j]) ; //affichage des cartes rouges/spéciales
                        color(15,0);
                        printf(" |");
                    }
                    else{
                         printf("%3.d |",tab[num_joueur].pioche_joueur [j]) ; //affichage des cartes vides
                    }
            }
}

//ECHANGE CARTE DEBUT DE MANCHE
//Au debut de chaque manche les joueurs d'une même équipe doivent échanger une carte avec leur coéquipié, ce ss programme permet cet échange.
void echange_carte_debut_manche (S_Joueur tab [], int nbmanche , int nbj)
{
    int i=0 , iemecarte1 , iemecarte2 , carte_en_memoire =0 ;
    printf("Bienvenue dans cette %d manche, chaque joueur doit a present echanger une carte avec son/sa coequipie(ere)\n",nbmanche) ;
    do {
        printf("C'est au tour de l'equipe %d \n\n", tab[i].equipe) ;
            printf("%s quelle carte voulez vous echanger ?\n",tab[i].nom) ;//le premier joueur choisit la carte qu'il désire échanger
            afficher_pioche_joueur(&tab[0] ,i) ;
            printf("\n");
            do {
                printf("Entrez l'indice de la carte, le chiffre entre parentheses\n") ;
                scanf("%d",&iemecarte1) ;
                if (((iemecarte1 <= NB_CARTES_MAX) && (iemecarte1 > 0)) || ((tab[i].pioche_joueur[iemecarte1-1] != 0)) )//assurance que le joueur a bien cette carte
                    {
                        carte_en_memoire = tab[i].pioche_joueur[iemecarte1-1] ;//mise en mémoire tampon de la carte
                    }
                else
                printf("Vous n'avez pas cette carte\n, recommencez\n") ;
        }while(iemecarte1 > NB_CARTES_MAX || iemecarte1 < 0 || tab[i].pioche_joueur[iemecarte1-1] == 0 ) ;

        printf("%s quelle carte voulez vous echanger ?\n Voici votre pioche\n",tab[i+1].nom) ;//le second joueur choisit la carte qu'il désire échanger
        afficher_pioche_joueur(&tab[0] ,i+1) ;
        printf("\n");

        do {
            scanf("%d",&iemecarte2) ;
            if (iemecarte2 <= NB_CARTES_MAX && iemecarte2 > 0 )
            {
                tab[i].pioche_joueur[iemecarte1-1] = tab[i+1].pioche_joueur[iemecarte2-1] ;//la carte choisit par le second joueur va à la place de la carte selectionné par le premier
                tab[1+i].pioche_joueur[iemecarte2-1] = carte_en_memoire;//la carte stocker dans la mémoire tampon est mise à la place de la carte choisit par le second joueur
            }
            else
                printf("Vous n'avez pas cette carte \n, recommencez\n") ;
        }while(iemecarte2 > NB_CARTES_MAX || iemecarte2 < 0 || tab[i+1].pioche_joueur[iemecarte2-1] == 0) ;
    i=i+2;//passage d'une équipe à la suivante
    system ("PAUSE");
    system ("cls");
    }while (i < nbj ) ;
}

//AFFICHER PLATEAU
//Ce ss programme permet d'afficher le plateau avec les pions colorés dessus
void afficher_plateau (int *tab, int nbj , int  nbcase)
{
    int i, j ,colore ;
    for (i=0 ; i< nbj ; i++)
    {   color(15,0);
        printf("\n\n%2.d\n",i+1);
        color(15,0);
        printf("\n") ;
        for (j=0 ;  j< 16 ; j++)
           {    color(15,0);
               printf("%1.d",j+1);
                color(15,0);
               colore = *(tab+(i*16)+j);//permet d'afficher en fonction des cases les pions des joueurs
        switch (colore)
        {
            case 0 :
                color(0,0);
                 printf("%  d",*(tab+i)) ;
                 color(15,0) ;
                break;

            case 1 :color(10,10); //par exemple :l'ordi lit un 1 dans la case il affiche donc un 1 rouge sur un fond rouge -> carré rouge
                 printf("%2.d",*(tab+i)) ;
                 color(15,0) ;
                break;


            case 2 :
                color(12,12);
                 printf("%2.d",*(tab+i)) ;
                 color(15,0) ;
                break;

            case 3 :color(11,11);
                 printf("%2.d",*(tab+i)) ;
                 color(15,0) ;
                break;

            case 4 : color(14,14);
                 printf("%2.d",*(tab+i)) ;
                 color(15,0) ;
                break;


            case 5 :color(7,7);
                 printf("%2.d",*(tab+i)) ;
                 color(15,0) ;
                break;


            case 6 :color(13,13);
                 printf("%2.d",*(tab+i)) ;
                 color(15,0) ;
                break;
        }
        }
    }
}

//TOUR JOUEUR

//Ce ss programme permet a un joueur de jouer son tour, soit de voir son jeu, de choisir la carte qu'il désire jouer, de mettre celle-ci à zéro, et de renvoyer au sous-programme qui corrrespond à la carte.
//Toute les vérifications pour savoir si le joueur peut jouer cette carte ou non sont faites dans ce programme, d'ou sa longueur.
void* tour_joueur (S_Joueur tab[], int num_joueur,int *tabl, int nb_cases , int* tab_verif_gagnant)
{
    int indice_carte_choisie=0,compteur_pion_ecurie=0 ,compteur_pion_plateau,compteur_pion_total,valeur_carte,verif_pion_plateau=0,j, compteur_pion=0, verif_carte,verif,verif_carte_11,compteur_joueur_depart=0, verif_sortir_pion,indice_plateau_final, sauvegarde_CARTE;
    printf("\nC'est au tour du joueur %s\n",tab[num_joueur].nom);
    afficher_pioche_joueur(&tab[0], num_joueur);

//1ere verification :  Y a-t-il un pion sur sa case départ du joueur  ?
if(*(tabl+((num_joueur*15)+num_joueur) )==num_joueur+1)
{
    verif_sortir_pion = 1; //le joueur a un pion sur sa case départ il ne peut donc pas en sortir un nouveau
}
else { verif_sortir_pion =0 ; } //le joueur n'a pas de pion sur sa case départ il  peut en sortir un nouveau

//2eme verfication :  le joueur a-t-il une carte pour commencer ?
   for ( j=0 ; j < NB_CARTES_MAX ; j++)//
        {
                if(tab[num_joueur].pioche_joueur [j] == 13 || tab[num_joueur].pioche_joueur [j] == 1 ||tab[num_joueur].pioche_joueur [j] == 14 )
                {
                    verif_carte =1 ;//le joueur a au moins une carte pour commencer
                    break ;//le "break" traduit le "au moins"
                }
                else {
                    verif_carte=0;
                }
        }

//3eme verification ; le joueur a-t-il déjà des pions sur le plateau ?
     for(j=0 ; j< nb_cases ; j++ )
    {
            if (*(tabl+j) == num_joueur+1 )
        {
               verif_pion_plateau =1 ; //le joueur a au moins un pion sur le plateau
               break;
        }
            else
        {
                verif_pion_plateau = 0 ;
        }
    }

//4eme verification : le joueur a-t-il des pions à sortir en tenant compte de ceux dans son écurie (donc déjà joué)
    for(j=0;j<NB_PION;j++)//compte les pions dans l'écurie du joueur, parcoure l'écurie du joueur
                {
                    if(tab[num_joueur].ecurie[j] == num_joueur+1)
                    {
                        compteur_pion_ecurie ++;
                    }
                }
    for(j=0 ; j< nb_cases ; j++ )//compte les pions du joueur sur le plateau, parcoure le plateau

    {

            if (*(tabl+j) == num_joueur+1 )

        {
               compteur_pion_plateau ++;

        }
    }

    compteur_pion_total=compteur_pion_ecurie+compteur_pion_plateau ;//ensemble des pions déjà ou en train d'être joué par le joueur

    if(compteur_pion_total == 4)//il a déjà 4 pions avec lesquels il a joué
    {
        verif_sortir_pion=1;//il ne peut donc plus en sortir de nouveau
    }



//5eme verification : si joueur veut tirer la carte 11, il doit y avoir au moins 2 pions sur le plateau ET le deuxième ne doit pas être sur SA case départ
    for(j=0 ; j< nb_cases ; j++ )//compte l'ensemble des pions, peu importe leur couleur, présent sur le plateau
    {
            if (*(tabl+j) != 0 )
        {
               compteur_pion =compteur_pion +1 ;
        }
    }

    if(compteur_pion >= 2)
    {
        if(tabl[0]==1) //les 6 boucles qui suivent servent à savoir combien il y a de pion sur leur case départ respective
        {compteur_joueur_depart=compteur_joueur_depart+1 ;}
        if(tabl[16]==2)
        {compteur_joueur_depart=compteur_joueur_depart+1 ;}
        if(tabl[32]==3)
        {compteur_joueur_depart=compteur_joueur_depart+1 ;}
        if(tabl[48]==4)
        {compteur_joueur_depart=compteur_joueur_depart+1 ;}
        if(tabl[64]==5)
        {compteur_joueur_depart=compteur_joueur_depart+1 ;}
        if(tabl[80]==6)
        {compteur_joueur_depart=compteur_joueur_depart+1 ;}

            if(compteur_pion-compteur_joueur_depart-1 > 0)//s'il y a au moins un pion, en dehors du sien,qui n'est pas sur sa case départ , le joueur peut utliser la carte 11
                {
                    verif_carte_11 =1;
                }
            else {verif_carte_11 = 0; }

    }
    else {verif_carte_11 =0;}//il n'y a pas assez de pions sur le plateau pour que le joueur puisse échanger son pion avec.



//Apres ces 5 vérifications, il suffit de les associer pour savoir quand le joueur peut jouer quelle carte
if( (verif_pion_plateau == 0 && verif_carte == 1 ))//Le joueur n'a pas de pion mais une carte pour debuter la manche, il ne peut donc jouer qu'avec ses carte 11 13 ou 1
{
    verif=2 ;
}

else if( (verif_pion_plateau == 1 && verif_carte == 0) || (verif_pion_plateau == 1 && verif_carte ==1 ))//le joueur a déjà des pions sur le plateau, il peut donc jouer avec n'importe lequel de ses pions soit ceux qu'il a dans le nid soit ceux déjà sur le plateau
    {

    verif=1 ;
}

else{//le joueur n'a ni pion ni carte départ, il ne peut donc pas débuter cette manche.

    verif =0 ;
}

if(verif==1 || verif ==2)//dans ce cas le joueur va pouvoir jouer
    {
                if(verif == 1)//RAPPEL :le joueur a déjà des pions sur le plateau, il peut donc jouer avec n'importe lequel de ses pions soit ceux qu'il a dans le nid soit ceux déjà sur le plateau
                {
                        do {
                            printf("\nQuelle carte desirez-vous jouer ? Entrez l'indice de la carte, le chiffre entre parentheses\n");
                            scanf("%d",&indice_carte_choisie);
                            if (verif_carte_11 == 0 && tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 11 ) //si le joueur souhaite jouer la carte 11 alors que c'est impossible, il ne peut pas
                                    {
                                        printf("\nVous ne pouvez pas jouer la carte 11, il n'y a pas assez de pion disponible sur le plateau pour echanger le votre avec\n");
                                    }
                             else if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] != 0 && indice_carte_choisie-1 >= 0 && indice_carte_choisie-1 <= 6)
                            {
                                printf("vous avez choisi de jouer cette carte %d", tab[num_joueur].pioche_joueur[indice_carte_choisie-1]);//validation de la carte choisie pas le joueur
                                verif_carte_11 = 1;
                            }
                            else if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 0 || indice_carte_choisie-1 <0 || indice_carte_choisie-1 > 6 )
                            {
                                printf("vous n'avez pas cette carte\n");
                            }
                        }while(indice_carte_choisie-1 < 0 || indice_carte_choisie-1 > 6 || tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 0 || verif_carte_11 ==0 );
                }
                if(verif==2)//RAPPEL : Le joueur n'a pas de pion mais une carte pour debuter la manche, il ne peut donc jouer qu'avec ses carte 11 13 ou 1
                {
                    do{
                            do {
                                    printf("\nQuelle carte desirez-vous jouer pour placer un pion sur votre case départ, vous avez le choix entre les cartes 1, 13 et 14 ? Entrez l'indice de la carte, le chiffre entre parentheses\n");
                                    scanf("%d",&indice_carte_choisie);
                                    if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] != 0 && indice_carte_choisie-1 >= 0 && indice_carte_choisie-1 <= 6)
                                    {
                                        printf("vous avez choisi de jouer cette carte %d", tab[num_joueur].pioche_joueur[indice_carte_choisie-1]);
                                    }
                                    else if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 0 || indice_carte_choisie-1 <0 || indice_carte_choisie-1 > 6 )
                                    {
                                        printf("vous n'avez pas cette carte\n");
                                    }
                                }while(indice_carte_choisie-1 < 0 || indice_carte_choisie-1 > 6 || tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 0 );
                    }while( tab[num_joueur].pioche_joueur[indice_carte_choisie-1] != 1 && tab[num_joueur].pioche_joueur[indice_carte_choisie-1] != 13 && tab[num_joueur].pioche_joueur[indice_carte_choisie-1] != 14);//assurance que le joueur choisit une carte qui lui permet de débuter le jeu
                }

//La fin du sous programme renvoie le joueur au sous-programme associé à la carte qu'il a choisit de jouer
                if(tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 2 || tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 3 || tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 5 || tab[num_joueur].pioche_joueur[indice_carte_choisie-1] ==6 || tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 8 ||tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 9 || tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 10 ||tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 12 )
                {
                    sauvegarde_CARTE = tab[num_joueur].pioche_joueur[indice_carte_choisie-1];//utile pour le test gagnant
                    valeur_carte = tab[num_joueur].pioche_joueur[indice_carte_choisie-1] ;
                    indice_plateau_final=avancer_pion (tab,valeur_carte,tabl,num_joueur ,nb_cases, nb_cases/16);//utile pour le test gagnant
                }

                else if(tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 4)
                {
                    sauvegarde_CARTE=tab[num_joueur].pioche_joueur[indice_carte_choisie-1];
                    valeur_carte = carte_4();
                    indice_plateau_final=avancer_pion (tab,valeur_carte,tabl,num_joueur ,nb_cases, nb_cases/16);
                }

                else if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 1)
                {
                    sauvegarde_CARTE =tab[num_joueur].pioche_joueur[indice_carte_choisie-1];
                    valeur_carte = carte_1(verif,verif_sortir_pion);
                    indice_plateau_final=avancer_pion (tab,valeur_carte,tabl,num_joueur ,nb_cases, nb_cases/16);
                }

                else if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 13)

                {
                    valeur_carte = carte_13(verif,verif_sortir_pion);
                    sauvegarde_CARTE=valeur_carte ;
                    indice_plateau_final=avancer_pion (tab,valeur_carte,tabl,num_joueur ,nb_cases, nb_cases/16);

                }

                else if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 14)
                {
                    sauvegarde_CARTE=tab[num_joueur].pioche_joueur[indice_carte_choisie-1];
                    valeur_carte = carte_14(verif,verif_sortir_pion);
                    indice_plateau_final=avancer_pion (tab,valeur_carte,tabl,num_joueur ,nb_cases, nb_cases/16);
                }

                else if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 11)
                {
                    sauvegarde_CARTE=tab[num_joueur].pioche_joueur[indice_carte_choisie-1];
                    indice_plateau_final=carte_11(num_joueur,tabl,nb_cases/16);
                }

                else if (tab[num_joueur].pioche_joueur[indice_carte_choisie-1] == 7)
                {
                    sauvegarde_CARTE=tab[num_joueur].pioche_joueur[indice_carte_choisie-1];
                    indice_plateau_final=carte_7 (tab,tabl, num_joueur , nb_cases, nb_cases/16);
                }
    tab[num_joueur].pioche_joueur[indice_carte_choisie-1] =0;//retire la carte du jeu du joueur après qu'il l'ait utilisé
    }

    else if(verif==0)//dans ce cas le joueur ne va pas pouvoir jouer
    {
        printf("\nDesole Joueur %s, vous n'avez pas de carte pour debuter cette manche, vous pourrez jouer la prochaine manche\n",tab[num_joueur].nom);
    }

    tab_verif_gagnant[0]=indice_plateau_final;
    tab_verif_gagnant[1]=sauvegarde_CARTE;

    return tab_verif_gagnant ;

}

//CARTE X
//Les 6 ss-programmes qui suivent correspondent aux cartes rouges/spéciales, chacun renvoie la valeur désirée par le joueur sauf la carte 11 qui permet d'échanger un de ses pions avec le pion d'un de ses adversaires
int carte_4 ()
{
    int valeur_carte_4;
    printf("\nTapez 1 pour avancer ou 2 pour reculer\n");
    do {
            scanf("%d",&valeur_carte_4);
    }while(valeur_carte_4 != 1 && valeur_carte_4 != 2) ;
    switch(valeur_carte_4)
    {
    case 1 :
        valeur_carte_4 = 4 ;
        break ;

    case 2 :
        valeur_carte_4 =-4 ;
        break;
    }

    return valeur_carte_4;

}

int carte_1 (int verif, int verif_case_depart )
{
    int valeur_carte_1;
    if (verif == 1 && verif_case_depart == 1)
    {
        printf("\nTapez 1 pour avancer de 1 \n 2 pour avancer de 11 \n"); // il ne peut pas sortir de pion car il a déjà un pion sur sa case départ
        do {
                scanf("%d",&valeur_carte_1);
        }while(valeur_carte_1 != 1 && valeur_carte_1 != 2 ) ;
    }

    else if (verif == 1 && verif_case_depart == 0)
    {
        printf("\nTapez 1 pour avancer de 1 \n2 pour avancer de 11 \n3 pour mettre un pion du nid sur votre case depart\n");
        do {
                scanf("%d",&valeur_carte_1);
        }while(valeur_carte_1 != 1 && valeur_carte_1 != 2 && valeur_carte_1 != 3 ) ;
    }

    else if(verif == 2)
    {
        printf("\nTapez 3 pour mettre un pion du nid sur votre case depart\n");// il ne peut que sortir un pion de son nid, il n'a pas de pion sur le plateau
        do {
                scanf("%d",&valeur_carte_1);
        }while(valeur_carte_1 != 3) ;
    }
    switch(valeur_carte_1)
    {
    case 1 :
        valeur_carte_1 = 1;
        break ;

    case 2 :
        valeur_carte_1 =11 ;
        break;

    case 3 :
        valeur_carte_1 = 111 ;
        break ;
    }

   return valeur_carte_1;
}

int carte_13 (int verif, int verif_case_depart)
{
    int valeur_carte_13;
    if(verif == 1 && verif_case_depart == 1)
    {
            printf("\nTapez 1 pour avancer de 13 \n ");// il ne peut pas sortir de pion car il a deja un pion sur sa case départ
            do {
                    scanf("%d",&valeur_carte_13);
            }while(valeur_carte_13 != 1 ) ;
    }

    else if (verif == 1 && verif_case_depart == 0)
    {
        printf("\nTapez 1 pour avancer de 13 \n2 pour mettre un pion du nid sur votre case depart\n");
            do {
                    scanf("%d",&valeur_carte_13);
            }while(valeur_carte_13 != 1 &&valeur_carte_13 != 2 ) ;
    }

    else if(verif == 2)
    {
            printf("\nTapez 2 pour mettre un pion du nid sur votre case depart\n");// il ne peut que sortir de pion car il n'a deja pas de pion sur le ^plateau
            do {
                    scanf("%d",&valeur_carte_13);
            }while( valeur_carte_13 != 2 ) ;
    }

    switch(valeur_carte_13)
    {
    case 1 :
        valeur_carte_13 = 13;
        break ;

    case 2 :
        valeur_carte_13 =113 ;
        break;
    }

   return valeur_carte_13;
}

int carte_14 (int verif,int verif_case_depart)

{
    int valeur_carte_14 , choix ;
    if(verif == 1 && verif_case_depart == 1)
    {
             printf("\nTapez 1 pour choisir de combien de case avancer votre pion \n ");// il ne peut pas sortir de pion car il a deja un pion sur sa case départ
            do {
                    scanf("%d",&choix );
            }while(choix  != 1 ) ;
    }
    else if (verif == 1 && verif_case_depart == 0)
    {
        printf("\nTapez 1 pour choisir de combien de case avancer votre pion \n2 pour mettre un pion du nid sur votre case depart\n");
            do {
                    scanf("%d",&choix );
            }while(choix  != 1 &&choix != 2 ) ;
    }

    else if(verif == 2)
    {
            printf("\nTapez 2 pour mettre un pion du nid sur votre case depart\n");
            do {
                    scanf("%d",&choix );
            }while(choix != 2 ) ;
    }

    switch(choix )
    {
    case 1 :
        do{
            printf("\nDe combien voulez vous avancer votre pion (entre 1 et 13 cases) ? \n");
            scanf("%d",&valeur_carte_14);
        }while(valeur_carte_14 <1 || valeur_carte_14 >13);
        break ;

    case 2 :
        valeur_carte_14 =114 ;
        break;
    }
   return valeur_carte_14;
}

int carte_11 (int num_joueur1, int *tab ,int nbj)

{
    int ligne_j1,colonne_j1,colonne_j2,ligne_j2,indice_j1=0,indice_j2, num_joueur2;
         afficher_plateau(tab , nbj,nbj*16) ;
        do{
            do{
                printf("\nEntrez les coordonnées de votre pion que vous souhaitez echanger, ligne puis colonne \n");
                scanf("%d%d",&ligne_j1,&colonne_j1);
                indice_j1=((ligne_j1-1)*16)+colonne_j1-1;//sauvegarde de l'indice de la case ou se trouve le pion que le joueur veut échanger
            }while(*(tab+indice_j1) != num_joueur1+1 );
             do{
                printf("\nEntrez les coordonnées du pion de l'adversaire que vous souhaitez echanger, ligne puis colonne \n");
                scanf("%d%d",&ligne_j2,&colonne_j2);
                indice_j2=((ligne_j2-1)*16)+colonne_j2-1;//sauvegarde de l'indice de la case ou se trouve le pion de l'adversaire que le joueur veut échanger
            }while(*(tab+indice_j2) == 0 || *(tab+indice_j2) == num_joueur1+1 );
            num_joueur2 = *(tab+indice_j2)-1 ;//sauvegarde du pion/chiffre  de l'adversaire
        }while(indice_j2 == (num_joueur2*15)+num_joueur2 );
        *(tab+indice_j1)=*(tab+indice_j2);//mise du pion du joueur sur la case de l'adversaire
        *(tab+indice_j2)=num_joueur1+1;//mise en place du pion de l'adversaire sur la case du joueur
         afficher_plateau(tab , nbj,nbj*16) ;
    return indice_j2 ;

}

int carte_7 (S_Joueur tabl[],int *tab, int num_joueur , int nb_cases, int nb_joueur)
{
    int ligne,colonne, indice_plateau_debut, indice_plateau_final, indice_bonus,  verif=1 ,j ,i,somme_avancement=0, valeur_desire,nb_pion_desire,nb_pion_plateau=0,choix;
    for(j=0 ; j< nb_cases ; j++ ){
                {
                    if (*(tab+j) == num_joueur+1 )//compte le nombre de pion du joueur sur le plateau
                        {
                            nb_pion_plateau = nb_pion_plateau +1 ;
                        }
                }
   }
    do{
            do{
                printf("\nSi vous souhaitez avancer un seul pion tapez 1\n si vous souhaitez en avancer plusieurs tapez 2\n");
                scanf("%d",&choix);
                if(choix == 2 && nb_pion_plateau == 1 )
                {
                    verif = 1 ;
                }
                else {
                    verif = 0 ;
                }
            }while(choix !=1 && choix !=2 );

    }while(verif == 1);
    switch(choix)
    {
    case 1: //le pion avance de 7 cases
        afficher_plateau(tab , nb_cases/16,nb_cases) ;
        do{
            printf("\nEntrez les coordonnees du pion que vous souhaitez jouer, ligne puis colonne \n");
            scanf("%d%d",&ligne,&colonne);
            indice_plateau_debut=((ligne-1)*16)+colonne-1;
        }while(*(tab+indice_plateau_debut) != num_joueur+1 );
            indice_plateau_final = indice_plateau_debut + 7 ;
        if (indice_plateau_final <= nb_cases && indice_plateau_final > 0 )
        {
                *(tab+indice_plateau_debut) =0 ;
                *(tab+indice_plateau_final)=num_joueur+1 ;
            for(j=indice_plateau_debut ; j<indice_plateau_final ; j++)
            {
                tab[j] = 0 ;
            }
            return indice_plateau_final;
        }
        else if ( indice_plateau_final > nb_cases)
        {
                indice_bonus = indice_plateau_final - nb_cases ;
                *(tab+indice_plateau_debut) =0 ;
                *(tab+indice_bonus)=num_joueur+1 ;
            for(j=indice_plateau_debut ; j<nb_cases ; j++)
            {
                tab[j] = 0 ;
            }
            for(j=0 ; j<indice_bonus ; j++)
            {
                tab[j] = 0 ;
            }
        return indice_bonus ;
        }
        afficher_plateau(tab , nb_cases/16,nb_cases) ;
        break;

    case 2: //avancement de plusieurs pions d'un nombre variable de case
         afficher_plateau(tab , nb_cases/16,nb_cases) ;
        do{
            printf("\nCombien de vos pions deja present sur le plateau voulez-vous avancer ?\n");
            scanf("%d",&nb_pion_desire);
        }while( nb_pion_desire > nb_pion_plateau || nb_pion_desire < 2);
        do{
                for(i=0 ; i<nb_pion_desire ; i ++)
                {
                    do{
                        printf("\nEntrez les coordonnees du pion %d que vous souhaitez jouer, ligne puis colonne \n",i+1);
                        scanf("%d%d",&ligne,&colonne);
                        indice_plateau_debut=((ligne-1)*16)+colonne-1;
                    }while(*(tab+indice_plateau_debut) != num_joueur+1 );
                    do{
                        printf("De combien de case souhaitez-vous avancer le pion %d\n",i+1);
                        scanf("%d",&valeur_desire);
                    }while(valeur_desire < 1 || valeur_desire > 7);
                    indice_plateau_final = indice_plateau_debut + valeur_desire ;
                    if (indice_plateau_final <= nb_cases && indice_plateau_final > 0 )
                    {
                        *(tab+indice_plateau_debut) =0 ;
                        *(tab+indice_plateau_final)=num_joueur+1 ;
                        for(j=indice_plateau_debut ; j<indice_plateau_final ; j++)
                            {
                                tab[j] = 0 ;
                            }
                    }
                    else if ( indice_plateau_final > nb_cases)
                    {
                        indice_bonus = indice_plateau_final - nb_cases ;
                        *(tab+indice_plateau_debut) =0 ;
                        *(tab+indice_bonus)=num_joueur+1 ;
                        for(j=indice_plateau_debut ; j<nb_cases ; j++)
                        {
                            tab[j] = 0 ;
                        }
                        for(j=0 ; j<indice_bonus ; j++)
                        {
                            tab[j] = 0 ;
                        }
                    }
                    somme_avancement=somme_avancement+valeur_desire ;
                }
        }while(somme_avancement!=7);// verification que l'ensemble des mouvement = 7

        afficher_plateau(tab , nb_joueur,nb_cases) ;
        return -1 ;// pour le test gagnant
        break;
    }
}

//AVANCER PION
//Ce sous programme permet à un joueur de choisir s'il veut sortir un pion de son nid ou jouer avec un de ses pions déja sur le plateau.

int avancer_pion (S_Joueur tabl[], int valeur_carte,int *tab, int num_joueur , int nb_cases, int nb_joueur)
{
    int ligne,colonne, indice_plateau_debut, indice_plateau_final, indice_bonus, compteur_pion=0,j  ,indice;
            if(valeur_carte == 111 || valeur_carte == 113 || valeur_carte == 114 )//le joueur souhaite sortir un pion de son nid
                                    {
                                       for(j=0 ; j< nb_cases ; j++ )
                                       {
                                           if (*(tab+j) == num_joueur+1 )
                                           {
                                               compteur_pion =compteur_pion +1 ;
                                           }
                                            else
                                            {
                                            indice = (num_joueur*15)+num_joueur ;
                                            tab[indice] = num_joueur+1 ;
                                            }
                                       }

                            afficher_plateau(tab , nb_joueur,nb_cases);
                            return -1 ; // le pion vient juste de sortir du nid il ne peut donc pas gagner avec
                                    }
            else {
                                    afficher_plateau(tab , nb_joueur,nb_cases) ;
                                    do{
                                    printf("\nEntrez les coordonnées du pion que vous souhaitez jouer, ligne puis colonne \n");
                                    scanf("%d%d",&ligne,&colonne);
                                    indice_plateau_debut=((ligne-1)*16)+colonne-1;
                                    }while(*(tab+indice_plateau_debut) != num_joueur+1 );
                                    indice_plateau_final = indice_plateau_debut + valeur_carte ;
                                    if (indice_plateau_final <= nb_cases && indice_plateau_final > 0 )
                                    {
                                        *(tab+indice_plateau_debut) =0 ;
                                        *(tab+indice_plateau_final)=num_joueur+1 ;
                                    }
                                    else if ( indice_plateau_final > nb_cases)
                                    {
                                        indice_bonus = indice_plateau_final - nb_cases ;
                                        *(tab+indice_plateau_debut) =0 ;
                                        *(tab+indice_bonus)=num_joueur+1 ;
                                    }
                                    else if (indice_plateau_final < 0)
                                    {
                                        indice_bonus = nb_cases+indice_plateau_final ;
                                        *(tab+indice_plateau_debut) =0 ;
                                        *(tab+indice_bonus)=num_joueur+1 ;
                                    }
                                    afficher_plateau(tab , nb_joueur,nb_cases) ;
                    return indice_plateau_debut ;
            }
}

//JOUER
//Ce sous programme permet de jouer à DOG
void jouer (S_Joueur tab[] , int pioche [][14] , int nbj,int *tabl,int* tab_verif_gagnant )
{
    int compteur_manche=0,verif_gagnant_equipe, nb_carte_manche,i,compteur_tour=0,verif_gagnant_joueur;
        do{
            compteur_manche++;
            compteur_tour=0;
            nb_carte_manche=distribution(tab , pioche, nbj,compteur_manche );
            echange_carte_debut_manche (tab, compteur_manche , nbj);
            do{
                compteur_tour++;
                printf("Bienvenue dans ce tour %d",compteur_tour);
                for(i=0;i<nbj;i++)//pendant un tour chacun des joueurs joue
                {
                    verif_gagnant_joueur =0;
                    tab_verif_gagnant=tour_joueur ( tab, i,tabl, nbj*16 , tab_verif_gagnant );
                    verif_gagnant_joueur = test_gagnant_1_joueur(tab_verif_gagnant,compteur_tour*compteur_manche,tabl,i,tab,nbj*16);
                    if(verif_gagnant_joueur==1)
                    {
                        printf("\nBRAVO %s vous avez mis un de vos pion dans la zone d'arrivee il est maintenant immunisé \n",tab[i].nom);
                    }
                    verif_gagnant_equipe = test_gagnant_1_equipe ( compteur_tour, tabl, i,  tab ,  nbj );
                    if(verif_gagnant_equipe == 1 )
                    {
                        printf("\nBRAVO equipe %d vous avez gagné",tab[i].equipe);

                    }

                        system ("PAUSE");
                        system ("cls");
                }

            }while(compteur_tour < nb_carte_manche );

        }while(verif_gagnant_equipe ==0 );
}

//TEST GAGNANT UN JOUEUR
//Ce sous programme permet de tester si le joueur i a réussi à mettre un de ses pions dans son écurie
int test_gagnant_1_joueur ( int* tab_verif_gagnant , int nb_tour, int* tab, int num_joueur, S_Joueur tabl [],int nb_cases )
{
    int verif_gagnant,verif_zone_ss_valeur,verif_zone_avec_val,k,indice_stalle_libre, indice_plateau_final ;
    indice_plateau_final=tab_verif_gagnant[0]+tab_verif_gagnant[1];
 if ( indice_plateau_final > nb_cases)//permet de ne pas pourvoir gagner avec un -4
                                    {
                                        indice_plateau_final = indice_plateau_final - nb_cases ;
                                    }

    if(nb_tour > 5 )// Imppossible de placer dans l'écurie un pion avant 5 tour, le premier permet de sortir un pion, les 5 suivants de l'avancer
    {
        if(tab_verif_gagnant[0] < num_joueur*15+num_joueur || tab_verif_gagnant[0] > num_joueur*15+num_joueur+3 )// s'il debute avant de poser sa carte avant ou apres sa zone d'écurie
        {
            verif_zone_ss_valeur = 1 ;
        }


        else
        {
            verif_zone_ss_valeur =0 ; //il est dans sa zone de depart il n'a donc pas encore fait un tour
        }

        if(indice_plateau_final  >= num_joueur*15+num_joueur && indice_plateau_final <= num_joueur*15+num_joueur+4 )
        {
            verif_zone_avec_val =1;
        }
        else
        {
            verif_zone_avec_val=0 ;
        }


        if(verif_zone_avec_val == 1 && verif_zone_ss_valeur ==1 )
        {
            verif_gagnant=1;

            for(k=0;k<NB_PION;k++)
            {
                if(tabl[num_joueur].ecurie[k] == 0)
                {
                    indice_stalle_libre=k;
                    break;
                }
            }
            tabl[num_joueur].ecurie[indice_stalle_libre] = num_joueur+1 ;//mettre un pion dans l'ecurie

        }
        else
        {
                verif_gagnant=0;
        }

    }
    else if (tab_verif_gagnant[0]==-1) // le joueur ne peut pas gagner avec un pion qui vient de sortir
    {
        verif_gagnant = 0 ;
    }
    else
    {
        verif_gagnant = 0 ;
    }

return verif_gagnant ;
}

//TEST GAGNANT 1 EQUIPE
// Ce sous programe permet de tester si les deux joueurs d'une même équipe ont tous leurs pions dans leur écurie
int test_gagnant_1_equipe ( int nb_tour, int* tab, int num_joueur, S_Joueur tabl [] , int nbj )
{
    int k ,compteur_pion_ecurie_j1 =0,compteur_pion_ecurie_j2 =0 ,verif_gagnant_j1,verif_gagnant_j2,indice_coequipiee, verif_gagnant ;

        for(k=0;k<NB_PION;k++) //compte les pions déjà présents dans l'ecurie du joueur 1
                {
                    if(tabl[num_joueur].ecurie[k] == num_joueur+1)
                    {
                        compteur_pion_ecurie_j1 ++;
                    }
                }
                if (compteur_pion_ecurie_j1 == 4 )//en fonction du nombre de pion présent dans l'écurie de ce joueur on sait s'il a gagné ou non
                {
                    verif_gagnant_j1=1;
                }
                else
                {
                    verif_gagnant_j1=0;
                }

    // recherche de l'indice du coéquipié  du premier joueur
    //sachant qu'une équipe est formée d'un nombre pair et d'un nombre impair
    if (tabl[num_joueur].equipe%2 == 0 )
    {
                indice_coequipiee = num_joueur+1 ;
    }
    else
    {
                indice_coequipiee = num_joueur-1 ;
            }



//idem pour le second joueur, comptage des pions dans son écurie, test gagnant
     for(k=0;k<NB_PION;k++)
                {
                    if(tabl[indice_coequipiee].ecurie[k] == indice_coequipiee+1)
                    {
                        compteur_pion_ecurie_j2 ++;
                    }
                }
                if (compteur_pion_ecurie_j2 == 4 )
                {
                    verif_gagnant_j2=1;
                }
                else
                {
                    verif_gagnant_j2=0;
                }

    if (verif_gagnant_j1 == 1 && verif_gagnant_j2 == 1)
    {
        verif_gagnant=1;
    }
    else {
        verif_gagnant=0;
    }

return verif_gagnant;
}
