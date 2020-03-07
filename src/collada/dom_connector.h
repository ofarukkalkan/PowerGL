#ifndef _powergl_asset_collada_dom_connector_h
#define _powergl_asset_collada_dom_connector_h

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "parse_utils.h"
#include "../powergl.h"


typedef struct dom_connector_t dom_connector;
typedef struct map_dom_connector_t map_dom_connector;
typedef struct arr_dom_connector_t arr_dom_connector;
typedef struct supported_type_t supported_type;

typedef void (*fpadd_child)(void *, size_t, dom_connector *);
typedef void (*fpset_ref)(void *, size_t, dom_connector *);
typedef void (*fpparse_attrib)(void *, size_t, const char *);
typedef void (*fpparse_content)(void *, size_t, const char *);


struct map_dom_connector_t
{
    char *name;
    char *base_type;
    char node_type;
};

struct arr_dom_connector_t
{
    dom_connector  **nodes;
    size_t n_node;
};

struct dom_connector_t
{
    ///////////
    //DOM fields
    char *name;
    char *value;//these fields are null-terminated
    dom_connector *ref;
    dom_connector *parent;

    //sub nodes
    arr_dom_connector *nodes;
    map_dom_connector *map;
    size_t n_map;

    fpadd_child add_child;
    fpset_ref set_ref;
    fpparse_attrib parse_attrib;
    fpparse_content parse_content;
};

struct supported_type_t
{
    map_dom_connector *map;
    size_t n_map;
    char *name;
    char *parent;
    void* (*get_instance)(void);

};

void powergl_collada_add_child(arr_dom_connector *, size_t index, dom_connector *);
void powergl_collada_set_ref(arr_dom_connector *, size_t index, dom_connector *);
void powergl_collada_parse_attrib(arr_dom_connector *, size_t index, const char *);
void powergl_collada_parse_content(arr_dom_connector *, size_t index, const char *);
void powergl_collada_print_element( FILE *file, dom_connector *node, int depth );

#endif
