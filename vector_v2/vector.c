#include "vector.h"
#include <stdlib.h>

#define MIN_MALLOC 16
#define TRUE 1
#define FALSE 0

/*
    Retourne le maximum de a, b
*/
size_t max_size_t(size_t a, size_t b)
{
    return a < b ? b : a;
}

/*
    Ecrit un warning si p_vector est NULL et renvoie FALSE, TRUE sinon
*/
int isNull(s_vector *p_vector)
{
    if (p_vector == NULL)
    {
        printf("\nWarning: can't be NULL\n\n");
        return TRUE;
    }
    return FALSE;
}

/*
    Ecrit un warning si l'index i n'est pas valable et renvoie FALSE, TRUE sinon
*/
int isOutOfBounds(s_vector *p_vector, size_t i)
{
    if (!(0 <= i && i < p_vector->size))
    {
        printf("\nWarning: out of bounds\n\n");
        return TRUE;
    }
    return FALSE;
}

/*
    Alloue et retourne votre structure. 
    Le tableau dynamique contient n double initialisés à 0.0.
*/
s_vector *vector_alloc(size_t n)
{
    if (n < 0)
    {
        printf("Warning: n can't be negative");
        return NULL;
    }

    s_vector *vector = (s_vector *)malloc(sizeof(s_vector));

    vector->size = n;
    vector->capacity = max_size_t(MIN_MALLOC, n); // Règle 1
    vector->tab = (double *)malloc(vector->capacity * sizeof(double));

    for (int i = 0; i < n; i++)
        vector->tab[i] = 0.0;

    return vector;
}

/*
    Libère votre structure.
*/
void vector_free(s_vector *p_vector)
{
    if (isNull(p_vector) == TRUE)
        return;

    free(p_vector->tab);
    p_vector->tab = NULL;

    free(p_vector);
    p_vector = NULL;
}

/*
    Affecte la donnée v à l’index i de votre tableau dynamique.
*/
void vector_set(s_vector *p_vector, size_t i, double v)
{
    if (isNull(p_vector) == TRUE || isOutOfBounds(p_vector, i) == TRUE)
        return;

    p_vector->tab[i] = v;
}

/*
    Retourne la donnée de l’index i.
*/
double vector_get(s_vector *p_vector, size_t i)
{
    if (isNull(p_vector) == TRUE || isOutOfBounds(p_vector, i) == TRUE)
        return -1;

    return p_vector->tab[i];
}

/*
    Insère une nouvelle donnée à l’index i de votre tableau dynamique.
*/
void vector_insert(s_vector *p_vector, size_t i, double v)
{
    if (isNull(p_vector) == TRUE || (i != 0 && isOutOfBounds(p_vector, i - 1) == TRUE))
        return;

    double *tab;

    if (p_vector->capacity <= p_vector->size)
    {
        p_vector->capacity *= 2; // Règle 2
        tab = (double *)malloc(p_vector->capacity * sizeof(double));
    }
    else
    {
        tab = p_vector->tab;
    }
    p_vector->size++;

    for (int index = 0; index < i; index++)
        tab[index] = p_vector->tab[index];

    for (int index = p_vector->size - 1; i < index; index--)
        tab[index] = p_vector->tab[index - 1];

    tab[i] = v;

    p_vector->tab = tab;
}

/*
    Supprime la donnée à l’index i de votre tableau dynamique.
*/
void vector_erase(s_vector *p_vector, size_t i)
{
    if (isNull(p_vector) == TRUE || (i != 0 && isOutOfBounds(p_vector, i - 1) == TRUE))
        return;

    double *tab;

    if (MIN_MALLOC < p_vector->capacity && p_vector->size <= p_vector->capacity / 4) // Règle 1
    {
        p_vector->capacity /= 2; // Règle 3
        tab = (double *)malloc(p_vector->capacity * sizeof(double));
    }
    else
    {
        tab = p_vector->tab;
    }

    for (int index = 0; index < p_vector->size; index++)
    {
        if (index == i)
            continue;
        else if (index < i)
            tab[index] = p_vector->tab[index];
        else
            tab[index - 1] = p_vector->tab[index];
    }

    p_vector->tab = tab;
    p_vector->size--;
}

/*
    Insère une nouvelle donnée à la fin de votre tableau dynamique.
*/
void vector_push_back(s_vector *p_vector, double v)
{
    if (isNull(p_vector) == TRUE)
        return;

    vector_insert(p_vector, p_vector->size, v);
}

/*
    Supprime la dernière donnée de votre tableau dynamique.
*/
void vector_pop_back(s_vector *p_vector)
{
    if (isNull(p_vector) == TRUE)
        return;

    vector_erase(p_vector, p_vector->size);
}

/*
    Supprime toutes les données de votre tableau dynamique.
*/
void vector_clear(s_vector *p_vector)
{
    if (isNull(p_vector) == TRUE)
        return;

    free(p_vector->tab);

    p_vector->size = 0;
    p_vector->capacity = MIN_MALLOC; // Règle 1
    p_vector->tab = (double *)malloc(p_vector->capacity * sizeof(double));
}

/*
    Retourne un entier non nul si votre tableau dynamique est vide et zéro sinon.
*/
int vector_empty(s_vector *p_vector)
{
    if (isNull(p_vector) == TRUE)
        return -1;

    return p_vector->size == 0 ? TRUE : FALSE;
}

/*
    Retourne le nombre d’élément stocker dans le tableau dynamique.
*/
size_t vector_size(s_vector *p_vector)
{
    if (isNull(p_vector) == TRUE)
        return -1;

    return p_vector->size;
}

/*
    Affiche la structure.
*/
void vector_print(s_vector *p_vector)
{
    if (isNull(p_vector) == TRUE)
        return;

    printf("s_vector(%ld) : ", p_vector->size);

    if (p_vector->size == 0)
    {
        printf("[]\n");
        return;
    }

    printf("[%f", p_vector->tab[0]);

    for (int i = 1; i < p_vector->size; i++)
        printf(", %f", p_vector->tab[i]);

    printf("]\n");
}