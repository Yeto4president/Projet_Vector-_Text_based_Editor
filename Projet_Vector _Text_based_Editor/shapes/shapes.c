#include "shapes.h"
#include <stdio.h>
#include <stdlib.h>
#include"../id/id.h"
// Fonction pour créer un point à partir de deux coordonnées, abcisse et ordonnée
Point *create_point(int px, int py)
{
    Point *pt = malloc(sizeof(Point));
    if(pt == NULL)
    {
        printf("Erreur de l'allocation memoire");
    return  NULL;
    }
    pt->pos_x = px;
    pt->pos_y = py;

    return pt;
}

// Fonction pour supprimer un point
void delete_point(Point * pt)
{
    free(pt);
    pt = NULL;
}

// Fonction pour afficher les coordonnées d'un point
void print_point(Point * p)
{
    printf("POINT %d %d", p->pos_x, p->pos_y);
}

// Fonction pour créer une ligne à partir de deux points
Line *create_line(Point * p1, Point * p2)
{
    Line *ln = malloc(sizeof(Line));
    if(ln == NULL)
    {
        printf("Erreur de l'allocation memoire");
        return  NULL;
    }

    ln->p1 = p1;
    ln->p2 = p2;
    return ln;
}

// Fonction pour supprimer une ligne
void delete_line(Line * ln)
{
    delete_point(ln->p1);
    delete_point(ln->p2);

    free(ln);
    ln = NULL;
}

// Fonction pour afficher les coordonnées d'une ligne
void print_line(Line * ln)
{
    printf("LINE %d %d %d %d", ln->p1->pos_x, ln->p1->pos_y, ln->p2->pos_x, ln->p2->pos_y);
}

// Fonction pour créer un carré à partir d'un point et d'une longueur
Square *create_square(Point * csg, int lg)
{
    Square * carre = malloc(sizeof(Square));
    if(carre == NULL)
    {
        printf("Erreur de l'allocation memoire");
        return  NULL;
    }

    carre->csgauche = csg;
    carre->longueur = lg;
    return carre;
}

// Fonction pour supprimer un carré
void delete_square(Square * square)
{
    delete_point(square->csgauche);
    free(square);
    square = NULL;
}

// Fonction pour afficher les coordonnées d'un carré
void print_square(Square * square)
{
    int px = square->csgauche->pos_x;
    int py = square->csgauche->pos_y;
    printf("SQUARE %d %d %d %d %d %d %d %d", px, py, px, py + square->longueur, px + square->longueur, py + square->longueur, px + square->longueur, py);
}

// Fonction pour créer un rectangle à partir d'un point, d'une largeur et d'une longueur
Rectangle *create_rectangle(Point * pt, int larg, int lg)
{
    Rectangle * rec = malloc(sizeof(Rectangle));
    if(rec == NULL)
    {
        printf("Erreur de l'allocation memoire");
        return  NULL;
    }

    rec->csgauche = pt;
    rec->largeur = larg;
    rec->longueur = lg;
    return rec;
}

// Fonction pour supprimer un rectangle
void delete_rectangle(Rectangle * rec)
{
    delete_point(rec->csgauche);
    free(rec);
    rec = NULL;
}

// Fonction pour afficher les coordonnées d'un rectangle
void print_rectangle(Rectangle * rectangle)
{
    int px = rectangle->csgauche->pos_x;
    int py = rectangle->csgauche->pos_y;
    printf("RECTANGLE %d %d %d %d %d %d %d %d", px, py, px, py + rectangle->longueur, px + rectangle->largeur, py + rectangle->longueur, px + rectangle->largeur, py);
}

// Fonction pour créer un cercle à partir d'un point central et d'un rayon
Circle *create_circle(Point * ctr, int ray)
{
    Circle * cer = malloc(sizeof(Circle));
    if(cer == NULL)
    {
        printf("Erreur de l'allocation memoire");
        return  NULL;
    }

    cer->centre = ctr;
    cer->rayon = ray;
    return cer;
}

// Fonction pour supprimer un cercle
void delete_circle(Circle *circle) {
    delete_point(circle->centre);
    free(circle);
    circle = NULL;
}

// Fonction pour afficher les coordonnées d'un cercle
void print_circle(Circle *circle) {
    printf("CIRCLE %d %d %d\n", circle->centre->pos_x, circle->centre->pos_y, circle->rayon);
}

// Fonction pour créer un polygone à partir d'un tableau de points
Polygon *create_polygon(int n, Point ** points) {
    Polygon* polygon = (Polygon*)malloc(sizeof(Polygon));
    polygon->n = n;
    polygon->points = (Point**)malloc(n * sizeof(Point*));
    for (int i = 0; i < n; i++) {
        polygon->points[i] = create_point(points[i]->pos_x, points[i]->pos_y);
    }
    return polygon;
}

// Fonction pour supprimer un polygone
void delete_polygon(Polygon *polygon) {
    for (int i = 0; i < polygon->n; i++) {
        free(polygon->points[i]);
    }
    free(polygon->points);
    free(polygon);
    polygon = NULL;
}

// Fonction pour afficher les coordonnées d'un polygone
void print_polygon(Polygon *polygon) {
    for (int i = 0; i < polygon->n; i++) {
        printf("Point %d: (%d, %d)\n", i + 1, polygon->points[i]->pos_x, polygon->points[i]->pos_y);
    }
}

// Fonction pour créer une forme vide avec un type spécifié
Shape *create_empty_shape(SHAPE_TYPE shape_type) {
    Shape *shp = (Shape *) malloc(sizeof(Shape));
    shp->ptrShape = NULL;
    shp->id = get_next_id(); // plus tard on appelera get_next_id();
    shp->shape_type = shape_type;
    return shp;
}

// Fonction pour créer une forme de point
Shape *create_point_shape(int px, int py) {
    Shape *shp = create_empty_shape(POINT);
    Point *p = create_point(px, py);
    shp->ptrShape = p;
    return shp;
}

// Fonction pour créer une forme de ligne
Shape *create_line_shape(int px1, int py1, int px2, int py2) {
    Shape *shp = create_empty_shape(LINE);
    Point *p1 = create_point(px1, py1);
    Point *p2 = create_point(px2, py2);
    Line *lg = create_line(p1, p2);

    shp->ptrShape = lg;
    return shp;
}

// Fonction pour créer une forme de carré
Shape *create_square_shape(int px, int py, int length) {
    Shape *shp = create_empty_shape(SQUARE);
    Point *p = create_point(px, py);
    Square *sq = create_square(p, length);

    shp->ptrShape = sq;
    return shp;
}

// Fonction pour créer une forme de rectangle
Shape *create_rectangle_shape(int px, int py, int width, int height){
    Shape *shp = create_empty_shape(RECTANGLE);
    Point *p = create_point(px, py);
    Rectangle *rec = create_rectangle(p, width, height);

    shp->ptrShape = rec;
    return shp;
}

// Fonction pour créer une forme de cercle
Shape *create_circle_shape(int px, int py, int radus){
    Shape *shp = create_empty_shape(CIRCLE);
    Point *p = create_point(px, py);
    Circle *cer = create_circle(p, radus);

    shp->ptrShape = cer;
    return shp;
}

// Fonction pour créer une forme de polygone
Shape *create_polygon_shape(int lst[], int n) {
    if (n % 2 != 0) {
        exit(EXIT_FAILURE);
    }

    Shape *shape = create_empty_shape(POLYGON);
    Polygon* polygon = (Polygon*)malloc(sizeof(Polygon)); // Allocation mémoire pour un polygone

    Point ** points = (Point**)malloc(polygon->n * sizeof(Point*)); // Allocation mémoire pour le tableau de points du polygone

    if (polygon->points != NULL) {
        // Création des points à partir du tableau lst et assignation aux positions paires et impaires du tableau de points du polygone
        for (int i = 0; i < n; i += 2) {
            Point *point = create_point(lst[i], lst[i + 1]);
            points[i / 2] = point;
        }
    }
    polygon = create_polygon(n / 2,points);
    shape->ptrShape = polygon;

    return shape;
}

// Fonction pour supprimer une forme
void delete_shape(Shape *shape) {

    switch (shape->shape_type) {
        case POINT:
            delete_point((Point *)shape->ptrShape);
            break;
        case LINE:
            delete_line((Line *)shape->ptrShape);
            break;
        case SQUARE:
            delete_square((Square *)shape->ptrShape);
            break;
        case RECTANGLE:
            delete_rectangle((Rectangle *)shape->ptrShape);
            break;
        case CIRCLE:
            delete_circle((Circle *)shape->ptrShape);
            break;
        case POLYGON:
            delete_polygon((Polygon *)shape->ptrShape);
            break;
        default:
            printf("Erreur de creation shape");
            break;
    }

    free(shape);
}

// Fonction pour afficher une forme
void print_shape(Shape *shape) {

    printf("Shape ID: %d", shape->id);

    switch (shape->shape_type) {
        case POINT:
            printf("Type: POINT");
            print_point((Point *)shape->ptrShape);
            break;
        case LINE:
            printf("Type: LINE");
            print_line((Line *)shape->ptrShape);
            break;
        case SQUARE:
            printf("Type: SQUARE");
            print_square((Square *)shape->ptrShape);
            break;
        case RECTANGLE:
            printf("Type: RECTANGLE");
            print_rectangle((Rectangle *)shape->ptrShape);
            break;
        case CIRCLE:
            printf("Type: CIRCLE");
            print_circle((Circle *)shape->ptrShape);
            break;
        case POLYGON:
            printf("Type: POLYGON");
            print_polygon((Polygon *)shape->ptrShape);
            break;
        default:
            printf("Erreur de creation shape");
            break;
    }
}



