//
// Created by Yeto.wrld on 5/19/2023.
//
#include <stdlib.h>
#include <stdio.h>
#include "area.h"
// Fonction pour créer une nouvelle zone
Area* create_area(unsigned int width, unsigned int height) {
    Area* zone = malloc(sizeof(Area));
    zone->mat = (int**)malloc(height * sizeof(int*));

    // Allouer de la mémoire pour la matrice et initialiser tous les pixels à 0
    for (unsigned int i = 0; i < height; i++) {
        zone->mat[i] = (int*)malloc(width * sizeof(int));
        for (unsigned int j = 0; j < width; j++) {
            zone->mat[i][j] = 0;
        }
    }

    zone->width = width;
    zone->height = height;
    zone->nb_shape = 0;
    return zone;
}

// Fonction pour ajouter une forme à une zone
void add_shape_to_area(Area* area, Shape* shape) {
    if (area->nb_shape < SHAPE_MAX) {
        area->shapes[area->nb_shape] = shape;
        area->nb_shape++;
    } else {
        printf("Nombre maximum de formes atteint.");
    }
}

// Fonction pour effacer tous les pixels d'une zone (les réinitialiser à 0)
void clear_area(Area* area) {
    for (unsigned int i = 0; i < area->height; i++) {
        for (unsigned int j = 0; j < area->width; j++) {
            area->mat[i][j] = 0;
        }
    }
}

// Fonction pour effacer toutes les formes d'une zone
void erase_area(Area* area) {
    // Libérer la mémoire pour chaque forme dans le tableau shapes
    for (int i = 0; i < area->nb_shape; i++) {
        free(area->shapes[i]);
        area->shapes[i] = NULL;
    }

    // Réinitialiser le nombre de formes à zéro
    area->nb_shape = 0;
}

// Fonction pour supprimer complètement une zone (libérer toute la mémoire)
void delete_area(Area* area) {
    // Effacer toutes les formes dans la zone
    erase_area(area);

    // Libérer la mémoire pour la matrice de pixels
    for (unsigned int i = 0; i < area->height; i++) {
        free(area->mat[i]);
    }
    free(area->mat);

    // Libérer la mémoire pour la structure Area
    free(area);
}

// Fonction pour dessiner les formes dans une zone en mettant à jour la matrice de pixels
void draw_area(Area* area) {
    for (int i = 0; i < area->nb_shape; i++) {
        Shape* shape = area->shapes[i];
        int nb_pixels = 0;
        Pixel** pixels = create_shape_to_pixel(shape, &nb_pixels);

        for (int j = 0; j < nb_pixels; j++) {
            unsigned int x = pixels[j]->px;
            unsigned int y = pixels[j]->py;

            if (x < area->width && y < area->height) {
                area->mat[y][x] = 1;
            }
        }

        free(pixels);
    }
}

// Fonction pour afficher la zone en utilisant les pixels dans la matrice
void print_area(Area* area) {
    for (unsigned int i = 0; i < area->height; i++) {
        for (unsigned int j = 0; j < area->width; j++) {
            if (area->mat[i][j] == 0) {
                printf(".");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
}

// Fonction pour créer un nouveau pixel
Pixel* create_pixel(int px, int py) {
    Pixel* pix = malloc(sizeof(Pixel));
    if (pix == NULL) {
        printf("Erreur d'allocation mémoire");
        exit(EXIT_FAILURE);
    }
    pix->px = px;
    pix->py = py;
    return pix;
}

// Fonction pour supprimer un pixel
void delete_pixel(Pixel* pixel) {
    free(pixel);
    pixel = NULL;
}

// Fonction pour convertir une forme de type Point en pixels
void pixel_point(Shape* shape, Pixel*** pixel_tab, int* nb_pixels) {
    Point* pt = (Point*)shape->ptrShape;
    *pixel_tab = (Pixel**)malloc(sizeof(Pixel*));
    (*pixel_tab)[0] = create_pixel(pt->pos_x, pt->pos_y);
    *nb_pixels = 1;
}

void pixel_line (Shape* line , Pixel *** pixel_tab , int* nb_pixels) {
    Line *l = (Line *) line->ptrShape;
    int xa;
    int xb;
    int ya;
    int yb;
    if (l->p1->pos_x < l->p2->pos_x) {
        xa = l->p1->pos_x;
        ya = l->p1->pos_y;
        xb = l->p2->pos_x;
        yb = l->p2->pos_y;
    } else {
        xa = l->p2->pos_x;
        ya = l->p2->pos_y;
        xb = l->p1->pos_x;
        yb = l->p1->pos_y;
    }
    int dx = xb - xa;
    int dy = yb - ya;
    int dmin;
    int dmax;
    if (dx < abs(dy)) {
        dmin = dx;
        dmax = abs(dy);
    } else {
        dmin = abs(dy);
        dmax = dx;
    }
    int nb_segs = dmin + 1;
    int taille_segs = (dmax + 1) / (dmin + 1);
    *pixel_tab = malloc((dmax+1)*sizeof (Pixel*));
    int *segments = malloc(nb_segs * sizeof(int));

    for (int i = 0; i < nb_segs; i++) {
        segments[i] = taille_segs;
    }
    int reste = (dmax + 1) / (dmin + 1);
    int *cumuls = (int *) malloc(nb_segs * sizeof(int));
    cumuls[0] = 0;
    for (int i = 1; i < nb_segs; i++) {
        cumuls[i] = ((i * reste) % (dmin + 1) < ((i - 1) * reste) % (dmin + 1));
        segments[i] = segments[i] + cumuls[i];
    }
    int x = l->p1->pos_x;
    int y = l->p1->pos_y;

    for (int i = 0; i < nb_segs; i++) {
        for (int j = 0; j < segments[i]; j++) {
            if (dy < 0) {
                if (dx > abs(dy)) {
                    (*pixel_tab)[(*nb_pixels)++] = create_pixel(x++, y);
                } else {
                    (*pixel_tab)[(*nb_pixels)++] = create_pixel(x, y--);
                }
            } else {
                if (dx > dy) {
                    (*pixel_tab)[(*nb_pixels)++] = create_pixel(x++, y);
                } else {
                    (*pixel_tab)[(*nb_pixels)++] = create_pixel(x, y++);
                }
            }
        }
        if (dy < 0) {
            if (dx > abs(dy)) {
                --y;
            } else {
                x++;
            }

        } else {
            if (dx > dy) {
                y++;
            } else {
                x++;
            }
        }
    }

}


void pixel_circle(Shape * shape, Pixel *** pixel_tab, int *nb_pixels){
    Circle * c = shape->ptrShape;
    *pixel_tab = malloc((c -> rayon * 8) * sizeof(Pixel*)); // Allocation mémoire
    int x = 0;
    int y = c ->rayon;
    int d = c -> rayon-1;

    Pixel * px = NULL;
    while (y >= x){

        px = create_pixel((c ->centre->pos_x)+x, (c -> centre->pos_y)+y);
        (*pixel_tab)[(*nb_pixels)++] = px;

        px = create_pixel((c ->centre->pos_x)+y, (c ->centre->pos_y)+x);
        (*pixel_tab)[(*nb_pixels)++] = px;

        px = create_pixel((c->centre->pos_x)-x,(c->centre->pos_y)+y);
        (*pixel_tab)[(*nb_pixels)++] = px;

        px = create_pixel((c->centre->pos_x)-y,(c->centre->pos_y)+x);
        (*pixel_tab)[(*nb_pixels)++] = px;

        px = create_pixel((c->centre->pos_x)+x,(c->centre->pos_y)-y);
        (*pixel_tab)[(*nb_pixels)++] = px;

        px = create_pixel((c->centre->pos_x)+y, (c->centre->pos_y)-x);
        (*pixel_tab)[(*nb_pixels)++] = px;

        px = create_pixel((c->centre->pos_x)-x,(c->centre->pos_y)-y);
        (*pixel_tab)[(*nb_pixels)++] = px;

        px = create_pixel((c->centre->pos_x)-y, (c->centre->pos_y)-x);
        (*pixel_tab)[(*nb_pixels)++] = px;


        if (d>=(2*x)){
            d -= 2*x+1;
            x++;
        }
        else if (d<2*(c->rayon-y)){
            d+= 2*y-1;
            y--;
        }
        else{
            d += 2 * (y-x-1);
            y--;
            x++;
        }
    }
}
void pixel_square (Shape* square , Pixel *** pixel_tab , int *nb_pixel) {
    Square *square1 = square->ptrShape;
    int nb_pixel_tmp = 0;
    *nb_pixel = 0;
    Shape *l1 = create_line_shape(square1->csgauche->pos_x, square1->csgauche->pos_y, square1->csgauche->pos_x,
                                  square1->csgauche->pos_y + square1->longueur);
    Shape *l2 = create_line_shape(square1->csgauche->pos_x, square1->csgauche->pos_y + square1->longueur,
                                  square1->csgauche->pos_x + square1->longueur,
                                  square1->csgauche->pos_y + square1->longueur);
    Shape *l3 = create_line_shape(square1->csgauche->pos_x + square1->longueur, square1->csgauche->pos_y,
                                  square1->csgauche->pos_x + square1->longueur,
                                  square1->csgauche->pos_y + square1->longueur);
    Shape *l4 = create_line_shape(square1->csgauche->pos_x, square1->csgauche->pos_y,
                                  square1->csgauche->pos_x + square1->longueur, square1->csgauche->pos_y);
    Pixel **pixel_tab1 = malloc(*nb_pixel * 4 * sizeof(Pixel *));
    Pixel **pixel_tab2 = malloc(*nb_pixel * 4 * sizeof(Pixel *));
    Pixel **pixel_tab3 = malloc(*nb_pixel * 4 * sizeof(Pixel *));
    Pixel **pixel_tab4 = malloc(*nb_pixel * 4 * sizeof(Pixel *));

    pixel_line(l1, &pixel_tab1, &nb_pixel_tmp);
    pixel_line(l2, &pixel_tab2, &nb_pixel_tmp);
    pixel_line(l3, &pixel_tab3, &nb_pixel_tmp);
    pixel_line(l4, &pixel_tab4, &nb_pixel_tmp);
    *nb_pixel = 4 * nb_pixel_tmp;
    *pixel_tab = malloc(*nb_pixel * 4 * sizeof(Pixel *));
    int k = 0;

    for (int i = 0; i < nb_pixel_tmp; i+=4) {
        (*pixel_tab)[k++] = pixel_tab1[i];
        (*pixel_tab)[k++] = pixel_tab2[i];
        (*pixel_tab)[k++] = pixel_tab3[i];
        (*pixel_tab)[k++] = pixel_tab4[i];
    }

}
void pixel_rectangle(Shape* rectangle, Pixel*** pixel_tab, int* nb_pixels) {
    Rectangle* rec = rectangle->ptrShape;
    Shape* lines[4];

    lines[0] = create_line_shape(rec->csgauche->pos_x, rec->csgauche->pos_y, rec->csgauche->pos_x, rec->csgauche->pos_y + rec->longueur);
    lines[1] = create_line_shape(rec->csgauche->pos_x, rec->csgauche->pos_y + rec->longueur, rec->csgauche->pos_x + rec->largeur, rec->csgauche->pos_y + rec->longueur);
    lines[2] = create_line_shape(rec->csgauche->pos_x + rec->largeur, rec->csgauche->pos_y + rec->longueur, rec->csgauche->pos_x + rec->largeur, rec->csgauche->pos_y);
    lines[3] = create_line_shape(rec->csgauche->pos_x + rec->largeur, rec->csgauche->pos_y, rec->csgauche->pos_x, rec->csgauche->pos_y);

    for (int i = 0; i < 4; i++) {
        pixel_line(lines[i], pixel_tab, nb_pixels);
    }

    for (int i = 0; i < 4; i++) {
        free(lines[i]);
    }
}
void pixel_polygon(Shape* polygon, Pixel*** pixel_tab, int* nb_pixels) {
    // Récupérer les points du polygone
    Polygon* poly = polygon->ptrShape;
    Point** points = poly->points;
    int num_points = poly->n;

    // Relier les points par des segments
    for (int i = 0; i < num_points - 1; i++) {
        Shape* line = create_line_shape(points[i]->pos_x, points[i]->pos_y, points[i+1]->pos_x, points[i+1]->pos_y);
        pixel_line(line, pixel_tab, nb_pixels);
        free(line);
    }

    // Relier le dernier point au premier point pour former une boucle
    Shape* line = create_line_shape(points[num_points - 1]->pos_x, points[num_points - 1]->pos_y, points[0]->pos_x, points[0]->pos_y);
    pixel_line(line, pixel_tab, nb_pixels);
    free(line);
}

Pixel ** create_shape_to_pixel (Shape * shape , int  * nb_pixels){
    Pixel ** tab = NULL;

    switch (shape->shape_type) {
        case LINE  :
        {
            pixel_line(shape , &tab , nb_pixels);
            break;
        }
        case SQUARE :
        {
            pixel_square(shape, &tab, nb_pixels);
            break;
        }
        case CIRCLE :
        {
            pixel_circle( shape , &tab , nb_pixels);
        }
    }
    return tab;
}
void delete_pixel_shape(Pixel*** pixel, int nb_pixels) {
    if (*pixel == NULL) {
        return; // Vérifier si le tableau de pixels est déjà libéré
    }

    for (int i = 0; i < nb_pixels; i++) {
        free((*pixel)[i]); // Libérer chaque ligne du tableau
    }

    free(*pixel); // Libérer le tableau principal
    *pixel = NULL; // Réinitialiser le pointeur à NULL
}