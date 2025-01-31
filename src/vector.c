#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vector.h"

void vector_init(vector *v)
{
    v->data = NULL;
    v->size = 0;
    v->count = 0;
}

int vector_count(vector *v)
{
    return v->count;
}

void vector_add(vector *v, void *e)
{
    if (v->size == 0)
    {
        v->size = 10;
        v->data = malloc(sizeof(void *) * v->size);
        memset(v->data, '\0', sizeof(void) * v->size);
    }

    if (v->size == v->count)
    {
        v->size *= 2;
        v->data = realloc(v->data, sizeof(void *) * v->size);
    }

    v->data[v->count] = e;
    v->count++;
}

void vector_set(vector *v, int index, void *e)
{
    if (index >= v->count)
    {
        return;
    }

    v->data[index] = e;
}

void *vector_get(vector *v, int index)
{
    if (index >= v->count)
    {
        return;
    }

    return v->data[index];
}

void vector_delete(vector *v, int index)
{
    if (index >= v->count)
    {
        return;
    }

    v->data[index] = NULL;

    int i, j;
    void **newarr = (void **)malloc(sizeof(void *) * v->count * 2);
    for (i = 0, j = 0; i < v->count; i++)
    {
        if (v->data[i] != NULL)
        {
            newarr[j] = v->data[i];
            j++;
        }
    }

    free(v->data);

    v->data = newarr;
    v->count--;
}

int vector_get_index(vector *v, char *name)
{
    for (int i = 0; i < v->count; i++)
    {
        ip_t *ip = v->data[i];
        if (strncmp(ip->ip_address, name, strlen(name)) == 0)
        {
            return i;
        }
    }
    return -1;
}

void vector_free(vector *v)
{
    free(v->data);
}