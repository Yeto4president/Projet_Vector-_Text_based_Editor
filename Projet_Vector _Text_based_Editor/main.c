#include <stdio.h>
#include"shapes/shapes.h"
#include"area/area.h"
#include"command/command.h"

#include<stdlib.h>
int main() {

    Area * draw_zone = create_area(20,20);
    Shape * shape1 = create_line_shape(5,5,10,10);
    Shape * shape2 = create_circle_shape(5,5,5);
    Shape *shape3 = create_square_shape(5,5,5);
    Shape *shape4 = create_rectangle_shape(6, 6, 4, 5);
    int lst[8]= {1, 2, 3, 4, 5, 6, 7, 8};
    Shape *shape5 = create_polygon_shape(lst,8);

    add_shape_to_area(draw_zone,shape3);
    draw_area(draw_zone);
    print_area(draw_zone);

   /* char choice;

    do {
        printf("Veuillez choisir une action :\n");
        printf("A- Ajouter une forme\n");
        printf("B- Afficher la liste des formes\n");
        printf("C- Supprimer une forme\n");
        printf("D- Tracer le dessin\n");
        printf("E- Aide\n");
        printf("[Autres actions]\n");
        printf(">> Votre choix : ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
                printf("Veuillez choisir une action :\n");
                printf("1- Ajouter un point\n");
                printf("2- Ajouter une ligne\n");
                printf("3- Ajouter un cercle\n");
                printf("4- Ajouter un carré\n");
                printf("5- Ajouter un rectangle\n");
                printf("6- Ajouter un polygone\n");
                printf("7- Revenir au menu précédent\n");
                printf(">> Votre choix : ");

                int addChoice;
                scanf("%d", &addChoice);

                switch (addChoice) {
                    case 1:
                        printf("Saisir les informations du point : \n >> Saisir les coordonnées du point x1 y1 : ");
                        int px = 0, py = 0;
                        scanf ("%d %d", &px, &py);

                        Point * p =create_point( px, py);
                        print_point(p);
                        break;
                    case 2:
                        printf("Saisir les informations de la ligne : \n >> Saisir les coordonnées du premier point x1 y1 : \n >> Saisir les coordonnées du deuxième point x2 y2 : \");");
                        int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
                        scanf ("%d %d %d %d", &p1, &p2 ,&p3, &p4);
                        Point * P1 =create_point( p1, p2);
                        Point * P2 =create_point( p3, p4);

                        Line * l = create_line(P1, P2);

                        break;
                    case 3:
                        printf("Saisir les informations du cercle : \n >> Saisir les coordonnées du centre x1 y1 : \n Saisir le  rayon :");
                        int p5 = 0, p6 = 0, p7;
                        scanf ("%d %d", &p5, &p6, &p7);

                        Point * P3 =create_point( p5, p6);
                        Circle * cer = create_circle(P3, p7);
                    case 4 :
                        printf("Saisir les informations du carré : \n >> Saisir les coordonnées du point supérieur gauche x1 y1 : \n Saisir la longueur :");
                        int p8 = 0, p9 = 0, p10 = 0;
                        scanf ("%d %d", &p8, &p9, &p10);

                        Point * P4 =create_point( p8, p9);
                        Square * sq = create_square( P4, p10);
                        break;
                    case 5:
                        printf("Saisir les informations du cercle : \n >> Saisir les coordonnées du centre x1 y1 : \n Saisir le  rayon :");

                        printf("Saisir les informations du carré : \n >> Saisir les coordonnées du point supérieur gauche x1 y1 : \n Saisir la longueur: \n Saisir la largeur:");
                        int p11 = 0, p12 = 0, p13 = 0, p14 = 0;
                        scanf ("%d %d", &p11, &p12, &p13, &p14);

                        Point * P5 =create_point( p11, p12);
                        Rectangle * rec = create_rectangle(P5, p13, p14);

                        break;
                    case 6 :
                        printf("Ajouter un polygone\n");
                        printf("Saisir les coordonnées des points (x y) (séparés par des espaces, terminer par un point '.'):\n");


                    case 7:
                        printf("Retour au menu précédent.\n");
                        break;
                        ;
                    default:
                        printf("Choix invalide.\n");
                        break;
                }

                break;
            case 'B':
                printf("Liste des formes :\n"
                       "                1 : CIRCLE 20 10 5\n"
                       "                2 : CIRCLE 20 25 5\n"
                       "                3 : LINE 5 20 10 25\n"
                       "                4 : POLYGON 15 0 5 10 10 15 5 20 10 25 5 30 15 35\n"
                       "                5 : CURVE 35 5 25 5 40 30 30 30");

                break;
            case 'C':
                // Code pour supprimer une forme
                break;
            case 'D':
                // Code pour tracer le dessin
                break;
            case 'E':
                printf("Liste des commandes :\n");
                printf("clear : efface toutes les formes de la zone.\n");
                printf("exit : quitte le programme.\n");
                printf("point x y : crée un point aux coordonnées (x, y).\n");
                printf("line x1 y1 x2 y2 : crée une ligne entre les points (x1, y1) et (x2, y2).\n");
                printf("circle cx cy r : crée un cercle de centre (cx, cy) et de rayon r.\n");
                printf("square x y s : crée un carré avec le coin supérieur gauche aux coordonnées (x, y) et de longueur de côté s.\n");
                printf("rectangle x y w h : crée un rectangle avec le coin supérieur gauche aux coordonnées (x, y), une largeur w et une hauteur h.\n");
                printf("polygon x1 y1 x2 y2 ... xn yn : crée un polygone avec les points (x1, y1), (x2, y2), ..., (xn, yn).\n");
                printf("plot : affiche la zone avec les formes dessinées.\n");
                printf("list : affiche la liste des formes dans la zone.\n");
                printf("delete id : supprime la forme avec l'identifiant id.\n");
                printf("erase : efface complètement la zone.\n");
                printf("help : affiche cette liste de commandes.\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }

    } while (choice != 'C' && choice != 'D' && choice != 'E');

    return 0;
}
*/}