//
// Created by Yeto.wrld on 5/29/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "command.h"
#include"../area//area.h"
#include"../shapes//shapes.h"
// Fonction pour créer une nouvelle commande
Command *create_commande() {
    Command *cm = malloc(sizeof(Command));
    cm->int_size = 0;
    cm->str_size = 0;

    // Initialiser le tableau de caractères name à '\0'
    for (int i = 0; i < sizeof(cm->name); i++) {
        cm->name[i] = '\0';
    }

    // Initialiser les tableaux int_params et str_params à des valeurs par défaut
    for (int i = 0; i < 10; i++) {
        cm->int_params[i] = 0;
        cm->str_params[i] = NULL;
    }

    return cm;
}

// Fonction pour ajouter un paramètre de type chaîne de caractères à une commande
void add_str_param(Command *cmd, char *p) {
    if (cmd->str_size < 10) {
        int length = strlen(p);
        char *new_str = malloc((length + 1) * sizeof(char)); // +1 pour le caractère nul

        if (new_str != NULL) {
            // Copier la chaîne de caractères dans le nouveau tableau alloué
            for (int i = 0; i <= length; i++) {
                new_str[i] = p[i];
            }

            // Ajouter le nouveau tableau de caractères aux str_params de la commande
            cmd->str_params[cmd->str_size] = new_str;
            cmd->str_size++;
        }
    }
}

// Fonction pour ajouter un paramètre de type entier à une commande
void add_int_param(Command *cmd, int p) {
    if (cmd->int_size < 10) {
        // Ajouter le paramètre entier à int_params de la commande
        cmd->int_params[cmd->int_size] = p;
        cmd->int_size++;
    }
}

// Fonction pour libérer la mémoire occupée par une commande
void free_cmd(Command *cmd) {
    // Libérer la mémoire allouée pour les paramètres de type chaîne de caractères
    for (int i = 0; i < cmd->str_size; i++) {
        free(cmd->str_params[i]);
    }

    cmd->str_size = 0;
    free(cmd);
    cmd = NULL;
}
int read_exec_command(Command* cmd, Area* area) {
    // Exécution de la commande saisie par l'utilisateur
    if (strcmp(cmd->name, "clear") == 0) {
        clear_area(area);
    } else if (strcmp(cmd->name, "exit") == 0) {
        exit(EXIT_FAILURE);
    } else if (strcmp(cmd->name, "point") == 0) {
        if (cmd->int_size < 2) {
            printf("Paramètres insuffisants pour la commande point.\n");
            return 0;
        }

        // Récupérer les coordonnées du point à partir des paramètres entiers
        int x = cmd->int_params[0];
        int y = cmd->int_params[1];

        // Créer un point dans Area
        Shape * pt = create_point_shape(x, y);
       int * nb_pixel = NULL;

        Pixel** pixel_tab = NULL;
        pixel_point(pt, &pixel_tab, nb_pixel);
        add_shape_to_area(area, pt);
        draw_area(area);
        print_area(area);

        } else if (strcmp(cmd->name, "line") == 0) {
        if (cmd->int_size < 4) {
            printf("Paramètres insuffisants pour la commande line.\n");
            return 0;
        }

        // Récupérer les coordonnées des points de la ligne à partir des paramètres entiers
        int x1 = cmd->int_params[0];
        int y1 = cmd->int_params[1];
        int x2 = cmd->int_params[2];
        int y2 = cmd->int_params[3];

        // Créer une ligne dans Area
        Shape* line = create_line_shape(x1, y1, x2, y2);
        add_shape_to_area(area, line);
        draw_area(area);
        print_area(area);
    } else if (strcmp(cmd->name, "circle") == 0) {
        if (cmd->int_size < 3) {
            printf("Paramètres insuffisants pour la commande circle.\n");
            return 0;
        }

        // Récupérer les coordonnées du centre et le rayon du cercle à partir des paramètres entiers
        int centerX = cmd->int_params[0];
        int centerY = cmd->int_params[1];
        int radius = cmd->int_params[2];

        // Créer un cercle dans Area
        Shape* circle = create_circle_shape(centerX, centerY, radius);
        add_shape_to_area(area, circle);
        draw_area(area);
        print_area(area);

    } else if (strcmp(cmd->name, "square") == 0) {
        if (cmd->int_size < 2) {
            printf("Paramètres insuffisants pour la commande square.\n");
            return 0;
        }

        // Récupérer les coordonnées du coin supérieur gauche et la longueur du côté du carré
        int topLeftX = cmd->int_params[0];
        int topLeftY = cmd->int_params[1];
        int sideLength = cmd->int_params[2];

        // Créer un carré dans Area
        Shape* square_shape = create_square_shape(topLeftX, topLeftY, sideLength);
        add_shape_to_area(area, square_shape);
        draw_area(area);
        print_area(area);
    } else if (strcmp(cmd->name, "rectangle") == 0) {
        if (cmd->int_size < 4) {
            printf("Paramètres insuffisants pour la commande rectangle.\n");
            return 0;
        }

        // Récupérer les coordonnées du coin supérieur gauche, la largeur et la hauteur du rectangle
        int topLeftX = cmd->int_params[0];
        int topLeftY = cmd->int_params[1];
        int width = cmd->int_params[2];
        int height = cmd->int_params[3];

        // Créer un rectangle dans Area
        Shape* rectangle_shape = create_rectangle_shape(topLeftX, topLeftY, width, height);
        add_shape_to_area(area, rectangle_shape);
        draw_area(area);
        print_area(area);

    } else if (strcmp(cmd->name, "polygon") == 0) {
        if (cmd->int_size < 2 || cmd->int_size % 2 != 0) {
            printf("Paramètres invalides pour la commande polygon.\n");
            return 0;
        }

        int numPoints = cmd->int_size;


        // Créer un polygone à partir des coordonnées
        Shape* polygon_shape = create_polygon_shape(cmd->int_params, numPoints);
        add_shape_to_area(area, polygon_shape);
        draw_area(area);
        print_area(area);
    } else if (strcmp(cmd->name, "plot") == 0) {
        draw_area(area);
        print_area(area);
    } else if (strcmp(cmd->name, "list") == 0) {
        printf("Liste des formes :\n");
        int numShapes = area->nb_shape;
        for (int i = 0; i < numShapes; i++) {
            Shape* shape = area->shapes[i];
            printf("%d : %s\n", i + 1, shape->ptrShape);
            // Afficher les informations spécifiques à chaque type de forme géométrique
            // Utilisez les membres de la structure Shape pour accéder aux informations spécifiques de chaque forme
        }
    }else if (strcmp(cmd->name, "delete id") == 0) {

    } else if (strcmp(cmd->name, "erase") == 0) {
        erase_area(area);
    } else if (strcmp(cmd->name, "help") == 0) {
        // Afficher la liste des commandes et le mode d'emploi
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
    } else {
        // Commande invalide
        printf("Commande invalide.\n");
        return 0;
    }

    return 1;}
void read_from_stdin(Command* cmd) {
    char line[256];
    printf(">> ");
    fgets(line, sizeof(line), stdin);

    // Supprimer le caractère de saut de ligne (\n) si présent
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    char* token;
    int int_value;
    char str_value[50];
    int int_count = 0;
    int str_count = 0;

    // Analyser la ligne en utilisant l'espace comme séparateur
    token = strtok(line, " ");
    while (token != NULL) {
        // Vérifier si le token est un entier
        if (sscanf(token, "%d", &int_value) == 1) {
            // Ajouter l'entier dans le tableau int_params
            if (int_count < MAX_TOKENS) {
                cmd->int_params[int_count] = int_value;
                int_count++;
            }
        } else {
            // Ajouter la chaîne de caractères dans le tableau str_params
            if (str_count < MAX_TOKENS) {
                strncpy(cmd->str_params[str_count], token, sizeof(cmd->str_params[str_count]) - 1);
                cmd->str_params[str_count][sizeof(cmd->str_params[str_count]) - 1] = '\0';
                str_count++;
            }
        }

        token = strtok(NULL, " ");
    }

    // Copier le nom de la commande
    strncpy(cmd->name, cmd->str_params[0], sizeof(cmd->name) - 1);
    cmd->name[sizeof(cmd->name) - 1] = '\0';

    // Mettre à jour les tailles des tableaux
    cmd->int_size = int_count;
    cmd->str_size = str_count;
}