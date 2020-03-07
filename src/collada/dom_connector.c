#include "dom_connector.h"

static const size_t g_max_unit_per_line = 50;

void powergl_collada_add_child(arr_dom_connector *this, size_t index, dom_connector *child)
{
    this[index].nodes = powergl_resize(this[index].nodes, ++this[index].n_node * sizeof(dom_connector*));
    this[index].nodes[this[index].n_node-1] = child;
}

void powergl_collada_set_ref(arr_dom_connector *this, size_t index, dom_connector *child)
{
    this[index].nodes[0]->ref = child;
}

void powergl_collada_parse_attrib(arr_dom_connector *this, size_t index, const char *value)
{
    this[index].nodes[0]->value = powergl_resize(NULL, (strlen(value)+1) * sizeof(char));
    strcpy(this[index].nodes[0]->value, value);
}

void powergl_collada_parse_content(arr_dom_connector *this, size_t index, const char *value)
{
    this[index].nodes[0]->value = powergl_resize(NULL, (strlen(value)+1) * sizeof(char));
    strcpy(this[index].nodes[0]->value, value);
}


void powergl_collada_print_element( FILE *file, dom_connector *elem, int depth )
{
    assert( elem );
    int flag = 0;
    fprintf( file, "\n" );
    for ( int i = 0; i < depth; ++i )
        {
            fprintf( file, "  " );
        }
    fprintf( file, "<%s", elem->name );
    for ( int i = 0; i < elem->n_map; ++i )
        {
            if( elem->map[i].node_type == 1 && elem->nodes[i].n_node > 0)
                {
                    for ( int j = 0; j < elem->nodes[i].n_node; ++j)
                        {
                            fprintf( file, " %s=\"", elem->nodes[i].nodes[j]->name );
                            fprintf( file, "%s", elem->nodes[i].nodes[j]->value );
                            fprintf( file, "\"" );
                        }
                }
        }
    for ( int i = 0; i < elem->n_map; ++i )
        {
            if( elem->map[i].node_type == 0 && elem->nodes[i].n_node > 0)
                {
                    if(flag == 0)
                        {
                            flag = 1;
                            fprintf( file, ">" );
                        }
                    for ( int j = 0; j < elem->nodes[i].n_node; ++j)
                        {
                            powergl_collada_print_element( file, elem->nodes[i].nodes[j], depth + 1 );
                        }
                }
        }
    for ( int i = 0; i < elem->n_map; ++i )
        {
            if( elem->map[i].node_type == 2 && elem->nodes[i].n_node > 0)
                {
                    for ( int j = 0; j < elem->nodes[i].n_node; ++j)
                        {
                            flag = 2;
                            fprintf( file, ">%s", elem->nodes[i].nodes[j]->value );
                        }
                }
        }
    if(flag == 1)
        {
            fprintf( file, "\n" );
            for ( int i = 0; i < depth; ++i )
                {
                    fprintf( file, "  " );
                }
            fprintf( file, "</%s>", elem->name );
        }
    else if(flag == 2)
        {
            fprintf( file, "</%s>", elem->name );
        }
    else if(flag == 0)
        {
            fprintf( file, "/>" );
        }
}
