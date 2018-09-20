#include "collada.h"

#include "../powergl.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <expat.h>


#define element(NAME)														\
  powergl_collada_elem_ ## NAME

/* globals */
static size_t g_current_depth;
static int g_undefined_element_flag;
static const char *g_current_elem_tag;
static void *g_current_elem;
static ptr_complex_element **g_pending_references;
static size_t g_n_pending_reference;
static int g_parser_status; // 0 : elemstart , 1 : chardata , 2 : elemend

struct collada_elem_attribs {
  const char *id;
  const char *sid;
  const char *name;
  const char *type;
  const char *source;
  const char *semantic;
  const char *version;
  const char *url;
  const char *xmlns;

  size_t count;
  size_t stride;
  size_t offset;
  size_t set;

  double meter;

} g_collada_elem_attribs;

struct collada_elem_attrib_states {
  short id;
  short sid;
  short name;
  short type;
  short source;
  short semantic;
  short version;
  short url;
  short xmlns;

  short count;
  short stride;
  short offset;
  short set;

  short meter;
};

struct collada_elem_attrib_states g_collada_elem_attrib_states;

void collada_func( print_elem_value )( FILE *file, complex_element *elem ) {
  if ( strcmp( elem->base_type, "list_of_floats" ) == 0 ) {
    double *ptr = *( ( double ** )elem->value_ptr );
    for ( int i = 0; i < elem->value_size; i++ ) {
      if ( i == elem->value_size - 1 ) {
        fprintf( file, "%.7g", ptr[i] );
      } else {
        fprintf( file, "%.7g ", ptr[i] );
      }
    }
  } else if ( strcmp( elem->base_type, "list_of_ints" ) == 0 ) {
    long int *ptr = *( ( long int ** )elem->value_ptr );
    for ( int i = 0; i < elem->value_size; i++ ) {
      if ( i == elem->value_size - 1 ) {
        fprintf( file, "%ld", ptr[i] );
      } else {
        fprintf( file, "%ld ", ptr[i] );
      }
    }
  } else if ( strcmp( elem->base_type, "list_of_uints" ) == 0 ) {
    unsigned long *ptr = *( ( unsigned long ** )elem->value_ptr );
    for ( int i = 0; i < elem->value_size; i++ ) {
      if ( i == elem->value_size - 1 ) {
        fprintf( file, "%lu", ptr[i] );
      } else {
        fprintf( file, "%lu ", ptr[i] );
      }
    }
  } else if ( strcmp( elem->base_type, "float4x4" ) == 0 ) {
    double *ptr = *( ( double ** )elem->value_ptr );
    for ( int i = 0; i < elem->value_size; i++ ) {
      if ( i == elem->value_size - 1 ) {
        fprintf( file, "%.7g", ptr[i] );
      } else {
        fprintf( file, "%.7g ", ptr[i] );
      }
    }
  } else if ( strcmp( elem->base_type, "float" ) == 0 ) {
    fprintf( file, "%.7g", *( double * )elem->value_ptr );
  } else if ( strcmp( elem->base_type, "int" ) == 0 ) {
    fprintf( file, "%ld", *( long int * )elem->value_ptr );
  } else if ( strcmp( elem->base_type, "uint" ) == 0 ) {
    fprintf( file, "%lu", *( unsigned long * )elem->value_ptr );
  }
}

void collada_func( print_attribute )( FILE *file, simple_element *elem ) {
  assert( elem );
  if ( strcmp( elem->base_type, "float" ) == 0 ) {
    fprintf( file, " %s=\"", elem->name );
    fprintf( file, "%f", *( ( double * )elem->value_ptr ) );
    fprintf( file, "\"" );
  } else if ( strcmp( elem->base_type, "int" ) == 0 ) {
    fprintf( file, " %s=\"", elem->name );
    fprintf( file, "%d", *( ( int * )elem->value_ptr ) );
    fprintf( file, "\"" );
  } else if ( strcmp( elem->base_type, "uint" ) == 0 ) {
    fprintf( file, " %s=\"", elem->name );
    fprintf( file, "%u", *( ( unsigned int * )elem->value_ptr ) );
    fprintf( file, "\"" );
  } else if ( strcmp( elem->base_type, "string" ) == 0 ) {
    if ( *( ( char ** )elem->value_ptr ) ) {
      fprintf( file, " %s=\"", elem->name );
      fprintf( file, "%s", *( ( char ** )elem->value_ptr ) );
      fprintf( file, "\"" );
    }
  }
}

void collada_func( print_element )( FILE *file, complex_element *elem, int depth ) {
  assert( elem );
  complex_element *elem_ptr = ( complex_element * )elem;

  fprintf( file, "\n" );
  for ( int i = 0; i < depth; ++i ) {
    fprintf( file, "  " );
  }
  fprintf( file, "<%s", elem_ptr->name );
  for ( int i = 0; i < elem_ptr->n_attrib; ++i ) {
    collada_func( print_attribute )( file, elem_ptr->attribs[i] );
  }
  if ( elem_ptr->n_elem ) {
    fprintf( file, ">" );
    for ( int i = 0; i < elem_ptr->n_elem; ++i ) {
      collada_func( print_element )( file, elem_ptr->elems[i], depth + 1 );
    }
    fprintf( file, "\n" );
    for ( int i = 0; i < depth; ++i ) {
      fprintf( file, "  " );
    }
    fprintf( file, "</%s>", elem_ptr->name );
  } else if ( elem_ptr->value_ptr ) {
    fprintf( file, ">" );
    collada_func( print_elem_value )( file, elem_ptr );
    fprintf( file, "</%s>", elem_ptr->name );
  } else {
    fprintf( file, "/>" );
  }
}

void collada_func( export_dae_file )( complex_element *root, const char *file_name ) {
  FILE *file = fopen( file_name, "w" );
  if ( !file ) {
    printf( "File opening failed" );
    return;
  }
  fprintf( file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>" );
  collada_func( print_element )( file, root, 0 );
  fprintf( file, "\n" );
  fclose( file );
}

static int init_simple_element_base( void *obj, char *name, char *base_type, void *parent, void *value_ptr ) {
  simple_element *this = ( simple_element * )obj;
  this->name = NULL;
  this->base_type = NULL;
  this->parent = parent;
  this->value_ptr = value_ptr;

  complex_element *parent_ptr = ( complex_element * ) parent;

  if ( parent != NULL ) {
    int parsed = 1;
    if ( strcmp( name, "sid" ) == 0 && g_collada_elem_attrib_states.sid ) { //sid
      char **sid  = ( char ** )this->value_ptr;
      ( *sid ) = powergl_resize( ( *sid ), strlen( g_collada_elem_attribs.sid ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *sid ), g_collada_elem_attribs.sid );
    } else if ( strcmp( name, "id" ) == 0 && g_collada_elem_attrib_states.id ) { //id
      char **id  = ( char ** )this->value_ptr;
      ( *id ) = powergl_resize( ( *id ), strlen( g_collada_elem_attribs.id ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *id ), g_collada_elem_attribs.id );
    } else if ( strcmp( name, "name" ) == 0 && g_collada_elem_attrib_states.name ) { //name
      char **name  = ( char ** )this->value_ptr;
      ( *name ) = powergl_resize( ( *name ), strlen( g_collada_elem_attribs.name ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *name ), g_collada_elem_attribs.name );
    } else if ( strcmp( name, "type" ) == 0 && g_collada_elem_attrib_states.type ) { //type
      char **type  = ( char ** )this->value_ptr;
      ( *type ) = powergl_resize( ( *type ), strlen( g_collada_elem_attribs.type ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *type ), g_collada_elem_attribs.type );
    } else if ( strcmp( name, "source" ) == 0 && g_collada_elem_attrib_states.source ) { //source
      char **source  = ( char ** )this->value_ptr;
      ( *source ) = powergl_resize( ( *source ), strlen( g_collada_elem_attribs.source ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *source ), g_collada_elem_attribs.source );
    } else if ( strcmp( name, "semantic" ) == 0 && g_collada_elem_attrib_states.semantic ) { //semantic
      char **semantic  = ( char ** )this->value_ptr;
      ( *semantic ) = powergl_resize( ( *semantic ), strlen( g_collada_elem_attribs.semantic ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *semantic ), g_collada_elem_attribs.semantic );
    } else if ( strcmp( name, "version" ) == 0 && g_collada_elem_attrib_states.version ) { //version
      char **version  = ( char ** )this->value_ptr;
      ( *version ) = powergl_resize( ( *version ), strlen( g_collada_elem_attribs.version ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *version ), g_collada_elem_attribs.version );
    } else if ( strcmp( name, "url" ) == 0 && g_collada_elem_attrib_states.url ) { //url
      char **url  = ( char ** )this->value_ptr;
      ( *url ) = powergl_resize( ( *url ), strlen( g_collada_elem_attribs.url ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *url ), g_collada_elem_attribs.url );
    } else if ( strcmp( name, "xmlns" ) == 0 && g_collada_elem_attrib_states.xmlns ) { //xmlns
      char **xmlns  = ( char ** )this->value_ptr;
      ( *xmlns ) = powergl_resize( ( *xmlns ), strlen( g_collada_elem_attribs.xmlns ) * sizeof( char ) + sizeof( char ) );
      strcpy( ( *xmlns ), g_collada_elem_attribs.xmlns );
    } else if ( strcmp( name, "count" ) == 0 && g_collada_elem_attrib_states.count ) { //count
      size_t *count = ( size_t * )this->value_ptr;
      ( *count ) = g_collada_elem_attribs.count;
      \
    } else if ( strcmp( name, "stride" ) == 0 && g_collada_elem_attrib_states.stride ) { //stride
      size_t *stride = ( size_t * )this->value_ptr;
      ( *stride ) = g_collada_elem_attribs.stride;
    } else if ( strcmp( name, "offset" ) == 0 && g_collada_elem_attrib_states.offset ) { //offset
      size_t *offset = ( size_t * )this->value_ptr;
      ( *offset ) = g_collada_elem_attribs.offset;
    } else if ( strcmp( name, "set" ) == 0 && g_collada_elem_attrib_states.set ) { //set
      size_t *set = ( size_t * )this->value_ptr;
      ( *set ) = g_collada_elem_attribs.set;
    } else if ( strcmp( name, "meter" ) == 0 && g_collada_elem_attrib_states.meter ) { //meter
      double *meter = ( double * )this->value_ptr;
      ( *meter ) = g_collada_elem_attribs.meter;
    } else {
      parsed = 0;
    }
    if ( parsed ) {
      this->name =  powergl_resize( this->name, strlen( name ) * sizeof( char ) + sizeof( char ) );
      strcpy( this->name, name );
      this->base_type =  powergl_resize( this->base_type, strlen( base_type ) * sizeof( char ) + sizeof( char ) );
      strcpy( this->base_type, base_type );

      parent_ptr->attribs = powergl_resize( parent_ptr->attribs, ++parent_ptr->n_attrib * sizeof( simple_element * ) );
      parent_ptr->attribs[parent_ptr->n_attrib - 1] = ( simple_element * ) this;
    }
  } else {
    fprintf( stderr, "parent NULL oldugu icin attrib eklenemiyor" );
  }
}

static int init_complex_element_base( void *obj, char *name, char *base_type, void *parent, void *value_ptr, complex_element ***ch_cont[], size_t n_ch_cont ) {
  complex_element *this = ( complex_element * )obj;
  this->name = NULL;
  this->base_type = NULL;
  this->value_ptr = NULL;
  this->parent = NULL;
  this->elems = NULL;
  this->attribs = NULL;
  this->refs = NULL;
  this->ch_container = NULL;
  this->n_ref = 0;
  this->n_attrib = 0;
  this->n_elem = 0;
  this->n_ch_container = 0;

  this->ch_container = powergl_resize( NULL, sizeof( complex_element ** * ) * n_ch_cont );
  for ( size_t i = 0; i < n_ch_cont; i++ ) {
    this->ch_container[i] = ch_cont[i];
  }
  this->n_ch_container = n_ch_cont;

  complex_element *parent_ptr = ( complex_element * ) parent;

  if ( parent != NULL || strcmp( name, "COLLADA" ) == 0 ) {
    this->name =  powergl_resize( this->name, strlen( name ) * sizeof( char ) + sizeof( char ) );
    strcpy( this->name, name );
    this->base_type =  powergl_resize( this->base_type, strlen( base_type ) * sizeof( char ) + sizeof( char ) );
    strcpy( this->base_type, base_type );
    this->parent = parent;
    this->value_ptr = value_ptr;
  }

  if ( parent != NULL ) {
    parent_ptr->elems = powergl_resize( parent_ptr->elems, ++parent_ptr->n_elem * sizeof( complex_element * ) );
    parent_ptr->elems[parent_ptr->n_elem - 1] = ( complex_element * ) this;
  } else if ( strcmp( name, "COLLADA" ) == 0 ) {

  }	else {
    fprintf( stderr, "parent NULL oldugu icin element eklenemiyor" );
  }

  g_current_elem = this;
}

static int init_ptr_complex_element_base( void *obj, char *src, char *ptr_type, void *parent ) {
  ptr_complex_element *this = ( ptr_complex_element * )obj;
  this->ptr = NULL;
  this->ptr_type = NULL;
  this->parent = NULL;
  this->src = NULL;

  complex_element *parent_ptr = ( complex_element * ) parent;

  if ( parent != NULL ) {

    this->ptr_type =  powergl_resize( NULL, strlen( ptr_type ) * sizeof( char ) + sizeof( char ) );
    strcpy( this->ptr_type, ptr_type );
    this->src = src;
    this->parent = parent;

    parent_ptr->refs = powergl_resize( parent_ptr->refs, ++parent_ptr->n_ref * sizeof( ptr_complex_element * ) );
    parent_ptr->refs[parent_ptr->n_ref - 1] = this;

    g_pending_references = powergl_resize( g_pending_references, ++g_n_pending_reference * sizeof( ptr_complex_element * ) );
    g_pending_references[g_n_pending_reference - 1] = this;
  }  else {
    fprintf( stderr, "parent NULL oldugu icin attrib eklenemiyor" );
  }


}


static void reset_parsed_attrib_states() {
  g_collada_elem_attrib_states = ( struct collada_elem_attrib_states ) {
    .id = 0,
     .sid = 0,
      .name = 0,
       .type = 0,
        .version = 0,
         .url = 0,
          .xmlns = 0,
           .stride = 0,
            .offset = 0,
             .set = 0,
              .meter = 0
  };
}

static void parse_attribs( const char **attr, size_t nattr ) {

  size_t i = 0;
  const char *ptr = NULL;

  if ( nattr ) {
    for ( i = 0; i < nattr / 2; ++i ) {
      ptr = attr[i * 2];
      if ( ptr[0] == 'i' ) { //id
        ptr = attr[i * 2 + 1];
        g_collada_elem_attribs.id = ptr;
        g_collada_elem_attrib_states.id = 1;
      } else if ( ptr[0] == 'n' ) { //name
        ptr = attr[i * 2 + 1];
        g_collada_elem_attribs.name = ptr;
        g_collada_elem_attrib_states.name = 1;
      } else if ( ptr[0] == 's' ) {
        if ( ptr[1] == 'i' ) { //sid
          ptr = attr[i * 2 + 1];
          g_collada_elem_attribs.sid = ptr;
          g_collada_elem_attrib_states.sid = 1;
        } else if ( ptr[1] == 'e' ) {
          if ( ptr[2] == 't' ) { //set
            ptr = attr[i * 2 + 1];
            g_collada_elem_attribs.set = strtoul( ptr, NULL, 10 );
            g_collada_elem_attrib_states.set = 1;
          } else if ( ptr[2] == 'm' ) { //semantic
            ptr = attr[i * 2 + 1];
            g_collada_elem_attribs.semantic = ptr;
            g_collada_elem_attrib_states.semantic = 1;
          }
        } else if ( ptr[1] == 'o' ) { //source
          ptr = attr[i * 2 + 1];
          g_collada_elem_attribs.source = ptr;
          g_collada_elem_attrib_states.source = 1;
        } else if ( ptr[1] == 't' ) { //stride
          ptr = attr[i * 2 + 1];
          g_collada_elem_attribs.stride = strtoul( ptr, NULL, 10 );
          g_collada_elem_attrib_states.stride = 1;
        }
      } else if ( ptr[0] == 't' ) { //type
        ptr = attr[i * 2 + 1];
        g_collada_elem_attribs.type = ptr;
        g_collada_elem_attrib_states.type = 1;
      } else if ( ptr[0] == 'u' ) { //url
        ptr = attr[i * 2 + 1];
        g_collada_elem_attribs.url = ptr;
        g_collada_elem_attrib_states.url = 1;
      } else if ( ptr[0] == 'm' ) { //meter
        ptr = attr[i * 2 + 1];
        g_collada_elem_attribs.meter = strtod( ptr, NULL );
        g_collada_elem_attrib_states.meter = 1;
      } else if ( ptr[0] == 'v' ) { //version
        ptr = attr[i * 2 + 1];
        g_collada_elem_attribs.version = ptr;
        g_collada_elem_attrib_states.version = 1;
      } else if ( ptr[0] == 'c' ) { //count
        ptr = attr[i * 2 + 1];
        g_collada_elem_attribs.count = strtoul( ptr, NULL, 10 );
        g_collada_elem_attrib_states.count = 1;
      } else if ( ptr[0] == 'o' ) { //offset
        ptr = attr[i * 2 + 1];
        g_collada_elem_attribs.offset = strtoul( ptr, NULL, 10 );
        g_collada_elem_attrib_states.offset = 1;
      } else if ( ptr[0] == 'x' ) {
        if ( ptr[5] == '\0' ) { //xmlns
          ptr = attr[i * 2 + 1];
          g_collada_elem_attribs.xmlns = ptr;
          g_collada_elem_attrib_states.xmlns = 1;
        } else { //xmlns:xsi
          // not implemented
        }
      }
    }
  }

}


static int init_library_effects( const char **attr, size_t nattr ) {

}

static int init_library_materials( const char **attr, size_t nattr ) {

}

static int init_library_lights( const char **attr, size_t nattr ) {

}


static int init_light( const char **attr, size_t nattr ) {

}


static int init_light_technique_common( complex_element *parent_complex ) {

}


static int init_directional( complex_element *parent_complex ) {

}

static int init_effect( complex_element *parent_complex ) {

}

static int init_profile_COMMON( complex_element *parent_complex ) {

}

static int init_technique_FX_COMMON( complex_element *parent_complex ) {

}

static int init_lambert( complex_element *parent_complex ) {

}

static int init_ambient( complex_element *parent_complex ) {

}

static int init_diffuse( complex_element *parent_complex ) {

}

static int init_fx_common_color_or_texture( complex_element *parent_complex ) {

}

static int init_light_color( complex_element *parent_complex ) {

}

static int init_profile_COMMON_color( complex_element *parent_complex ) {

}

static int init_material( complex_element *parent_complex ) {

}

static int init_instance_effect( complex_element *parent_complex ) {

}

static int init_instance_material( complex_element *parent_complex ) {

}

static int init_instance_light( complex_element *parent_complex ) {

}

static int init_bind_material( complex_element *parent_complex ) {

}

static int init_instance_geometry( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "node" ) == 0 ) {
    element( node ) * parent = ( element( node ) * ) parent_complex;
    element( instance_geometry ) **ptr = parent->ch_instance_geometry;
    ptr = powergl_resize( ptr, ++parent->n_instance_geometry * sizeof( element( instance_geometry ) * ) );
    parent->ch_instance_geometry = ptr;
    parent->ch_instance_geometry[parent->n_instance_geometry - 1] = powergl_resize( NULL, sizeof( element( instance_geometry ) ) );
    element( instance_geometry )* this = parent->ch_instance_geometry[parent->n_instance_geometry - 1];

    this->p_node = parent;
    this->a_sid.value = NULL;
    this->a_name.value = NULL;
    this->a_url.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "instance_geometry", "none", parent, NULL, NULL, 0 );
    init_simple_element_base( &this->a_sid, "sid", "string", this, &this->a_sid.value );
    init_simple_element_base( &this->a_url, "url", "string", this, &this->a_url.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
    init_ptr_complex_element_base( &this->r_geometry, this->a_url.value, "geometry", this );
  } else {
    return 0;
  }

  return 1;
}

static int init_instance_camera( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "node" ) == 0 ) {
    element( node ) * parent = ( element( node ) * ) parent_complex;
    element( instance_camera ) **ptr = parent->ch_instance_camera;
    ptr = powergl_resize( ptr, ++parent->n_instance_camera * sizeof( element( instance_camera ) * ) );
    parent->ch_instance_camera = ptr;
    parent->ch_instance_camera[parent->n_instance_camera - 1] = powergl_resize( NULL, sizeof( element( instance_camera ) ) );
    element( instance_camera )* this = parent->ch_instance_camera[parent->n_instance_camera - 1];

    this->p_node = parent;
    this->a_sid.value = NULL;
    this->a_name.value = NULL;
    this->a_url.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "instance_camera", "none", parent, NULL, NULL, 0 );
    init_simple_element_base( &this->a_sid, "sid", "string", this, &this->a_sid.value );
    init_simple_element_base( &this->a_url, "url", "string", this, &this->a_url.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
    init_ptr_complex_element_base( &this->r_camera, this->a_url.value, "camera", this );
  } else {
    return 0;
  }
  return 1;
}

static int init_matrix( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "node" ) == 0 ) {
    element( node ) * parent = ( element( node ) * ) parent_complex;
    element( matrix ) **ptr = parent->ch_matrix;
    ptr = powergl_resize( ptr, ++parent->n_matrix * sizeof( element( matrix ) * ) );
    parent->ch_matrix = ptr;
    parent->ch_matrix[parent->n_matrix - 1] = powergl_resize( NULL, sizeof( element( matrix ) ) );
    element( matrix )* this = parent->ch_matrix[parent->n_matrix - 1];

    this->p_node = parent;
    this->a_sid.value = NULL;
    this->_ext.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "matrix", "float4x4", parent, &this->_ext.value, NULL, 0 );
    init_simple_element_base( &this->a_sid, "sid", "string", this, &this->a_sid.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_node( complex_element *parent_complex, const char **attr, size_t nattr ) {
  element( node )* this = NULL;
  complex_element *parent_ptr  = NULL;

  if ( strcmp( parent_complex->name, "visual_scene" ) == 0 ) { // visual_scene
    element( visual_scene ) * parent = ( element( visual_scene ) * ) parent_complex;
    element( node ) **ptr = parent->ch_node;
    ptr = powergl_resize( ptr, ++parent->n_node * sizeof( element( node ) * ) );
    parent->ch_node = ptr;
    parent->ch_node[parent->n_node - 1] = powergl_resize( NULL, sizeof( element( node ) ) );
    this = parent->ch_node[parent->n_node - 1];

    this->p_visual_scene = parent;
    parent_ptr = ( complex_element * ) parent_complex;
  } else if ( strcmp( parent_complex->name, "node" ) == 0 ) { // node
    element( node ) * parent = ( element( node ) * ) parent_complex;
    element( node ) **ptr = parent->ch_node;
    ptr = powergl_resize( ptr, ++parent->n_node * sizeof( element( node ) * ) );
    parent->ch_node = ptr;
    parent->ch_node[parent->n_node - 1] = powergl_resize( NULL, sizeof( element( node ) ) );
    this = parent->ch_node[parent->n_node - 1];

    this->p_node = parent;
    parent_ptr = ( complex_element * ) parent_complex;
  } else {
    return 0;
  }

  this->a_id.value = NULL;
  this->a_sid.value = NULL;
  this->a_name.value = NULL;

  this->ch_matrix = NULL;
  this->ch_instance_camera = NULL;
  this->ch_instance_geometry = NULL;
  this->ch_instance_light = NULL;
  this->ch_instance_node = NULL;
  this->ch_node = NULL;
  complex_element ***ch_cont[6] = {
    ( complex_element ** * ) &this->ch_instance_camera,
    ( complex_element ** * ) &this->ch_instance_geometry,
    ( complex_element ** * ) &this->ch_instance_node,
    ( complex_element ** * ) &this->ch_instance_light,
    ( complex_element ** * ) &this->ch_node,
    ( complex_element ** * ) &this->ch_matrix,
  };

  this->n_matrix = 0;
  this->n_instance_camera = 0;
  this->n_instance_geometry = 0;
  this->n_instance_light = 0;
  this->n_instance_node = 0;
  this->n_node = 0;

  parse_attribs( attr, nattr );
  init_complex_element_base( this, "node", "none", parent_ptr, NULL, ch_cont, 6 );
  init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
  init_simple_element_base( &this->a_sid, "sid", "string", this, &this->a_sid.value );
  init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );

  return 1;
}

static int init_p( complex_element *parent_complex ) {
  if ( strcmp( parent_complex->name, "polylist" ) == 0 ) {
    element( polylist ) * parent = ( element( polylist ) * ) parent_complex;
    parent->c_p = powergl_resize( NULL, sizeof( element( p ) ) );
    element( p )* this = parent->c_p;
    this->p_polylist = parent;
    this->_ext.value = NULL;

    init_complex_element_base( this, "p", "list_of_uints", parent, &this->_ext.value, NULL, 0 );
  } else if ( strcmp( parent_complex->name, "triangles" ) == 0 ) {
    element( triangles ) * parent = ( element( triangles ) * ) parent_complex;
    parent->c_p = powergl_resize( NULL, sizeof( element( p ) ) );
    element( p )* this = parent->c_p;
    this->p_triangles = parent;
    this->_ext.value = NULL;

    init_complex_element_base( this, "p", "list_of_uints", parent, &this->_ext.value, NULL, 0 );
  } else {
    return 0;
  }
  return 1;
}

static int init_vcount( complex_element *parent_complex ) {
  if ( strcmp( parent_complex->name, "polylist" ) == 0 ) {
    element( polylist ) * parent = ( element( polylist ) * ) parent_complex;
    parent->c_vcount = powergl_resize( NULL, sizeof( element( vcount ) ) );
    element( vcount )* this = parent->c_vcount;
    this->p_polylist = parent;
    this->_ext.value = NULL;

    init_complex_element_base( this, "vcount", "list_of_uints", parent, &this->_ext.value, NULL, 0 );
  } else {
    return 0;
  }
  return 1;
}

static int init_input( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "vertices" ) == 0 ) { // vertices
    element( vertices ) * parent = ( element( vertices ) * ) parent_complex;
    element( input_local ) **ptr = parent->ch_input_local;
    ptr = powergl_resize( ptr, ++parent->n_input_local * sizeof( element( input_local ) * ) );
    parent->ch_input_local = ptr;
    parent->ch_input_local[parent->n_input_local - 1] = powergl_resize( NULL, sizeof( element( input_local ) ) );
    element( input_local )* this = parent->ch_input_local[parent->n_input_local - 1];

    this->p_vertices = parent;
    this->a_semantic.value = NULL;
    this->a_source.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "input", "none", parent, NULL, NULL, 0 );
    init_simple_element_base( &this->a_semantic, "semantic", "string", this, &this->a_semantic.value );
    init_simple_element_base( &this->a_source, "source", "string", this, &this->a_source.value );
    init_ptr_complex_element_base( &this->r_source, this->a_source.value, "source", this );

  } else if ( strcmp( parent_complex->name, "polylist" ) == 0 || strcmp( parent_complex->name, "triangles" ) == 0 ) { // polylist or triangles
    void *parent_ptr = NULL;
    element( input_local_offset )* this = NULL;
    if ( strcmp( parent_complex->name, "polylist" ) == 0 ) {
      element( polylist ) * parent = ( element( polylist ) * ) parent_complex;
      element( input_local_offset ) **ptr = parent->ch_input_local_offset;
      ptr = powergl_resize( ptr, ++parent->n_input_local_offset * sizeof( element( input_local_offset ) * ) );
      parent->ch_input_local_offset = ptr;
      parent->ch_input_local_offset[parent->n_input_local_offset - 1] = powergl_resize( NULL, sizeof( element( input_local_offset ) ) );
      this = parent->ch_input_local_offset[parent->n_input_local_offset - 1];
      this->p_polylist = parent_ptr;
      this->p_triangles = NULL;
      this->a_semantic.value = NULL;
      this->a_source.value = NULL;
      parent_ptr = parent;
    } else if ( strcmp( parent_complex->name, "triangles" ) == 0 ) {
      element( triangles ) * parent = ( element( triangles ) * ) parent_complex;
      element( input_local_offset ) **ptr = parent->ch_input_local_offset;
      ptr = powergl_resize( ptr, ++parent->n_input_local_offset * sizeof( element( input_local_offset ) * ) );
      parent->ch_input_local_offset = ptr;
      parent->ch_input_local_offset[parent->n_input_local_offset - 1] = powergl_resize( NULL, sizeof( element( input_local_offset ) ) );
      this = parent->ch_input_local_offset[parent->n_input_local_offset - 1];
      this->p_triangles = parent_ptr;
      this->p_triangles = NULL;
      this->a_semantic.value = NULL;
      this->a_source.value = NULL;
      parent_ptr = parent;
    }

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "input", "none", parent_ptr, NULL, NULL, 0 );
    init_simple_element_base( &this->a_semantic, "semantic", "string", this, &this->a_semantic.value );
    init_simple_element_base( &this->a_source, "source", "string", this, &this->a_source.value );
    init_simple_element_base( &this->a_set, "set", "uint", this, &this->a_set.value );
    init_simple_element_base( &this->a_offset, "offset", "uint", this, &this->a_offset.value );
    init_ptr_complex_element_base( &this->r_source, this->a_source.value, "source", this );
    init_ptr_complex_element_base( &this->r_vertices, this->a_source.value, "vertices", this );

  } else {
    return 0;
  }
  return 1;
}

static int init_param( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "accessor" ) == 0 ) {
    element( accessor ) * parent = ( element( accessor ) * ) parent_complex;
    element( param ) **ptr = parent->ch_param;
    ptr = powergl_resize( ptr, ++parent->n_param * sizeof( element( param ) * ) );
    parent->ch_param = ptr;
    parent->ch_param[parent->n_param - 1] = powergl_resize( NULL, sizeof( element( param ) ) );
    element( param )* this = parent->ch_param[parent->n_param - 1];

    this->p_accessor = parent;
    this->a_sid.value = NULL;
    this->a_name.value = NULL;
    this->a_type.value = NULL;
    this->a_semantic.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "param", "none", parent, NULL, NULL, 0 );
    init_simple_element_base( &this->a_sid, "sid", "string", this, &this->a_sid.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
    init_simple_element_base( &this->a_semantic, "semantic", "string", this, &this->a_semantic.value );
    init_simple_element_base( &this->a_type, "type", "string", this, &this->a_type.value );
  } else {
    return 0;
  }
  return 1;

}

static int init_accessor( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "technique_common" ) == 0 ) {
    element( source_technique_common ) * parent = ( element( source_technique_common ) * ) parent_complex;
    parent->c_accessor = powergl_resize( NULL, sizeof( element( accessor ) ) );
    element( accessor ) * this = parent->c_accessor;
    this->p_source_technique_common = parent;

    this->a_source.value = NULL;
    this->ch_param = NULL;
    this->n_param = 0;
    complex_element ***ch_cont[] = {
      ( complex_element ** * ) &this->ch_param
    };

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "accessor", "none", parent, NULL, ch_cont, 1 );
    init_simple_element_base( &this->a_source, "source", "string", this, &this->a_source.value );
    init_simple_element_base( &this->a_count, "count", "uint", this, &this->a_count.value );
    init_simple_element_base( &this->a_stride, "stride", "uint", this, &this->a_stride.value );
    init_simple_element_base( &this->a_offset, "offset", "uint", this, &this->a_offset.value );
    init_ptr_complex_element_base( &this->r_float_array, this->a_source.value, "float_array", this );
    init_ptr_complex_element_base( &this->r_int_array, this->a_source.value, "int_array", this );
  } else {
    return 0;
  }
  return 1;
}

static int init_int_array( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "source" ) == 0 ) {
    element( source ) * parent = ( element( source ) * ) parent_complex;
    parent->c_int_array = powergl_resize( NULL, sizeof( element( int_array ) ) );
    element( int_array ) * this = parent->c_int_array;
    this->p_source = parent;
    this->a_name.value = NULL;
    this->a_id.value = NULL;
    this->_ext.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "int_array", "list_of_ints", parent, &this->_ext.value, NULL, 0 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
    init_simple_element_base( &this->a_count, "count", "uint", this, &this->a_count.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_float_array( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "source" ) == 0 ) {
    element( source ) * parent = ( element( source ) * ) parent_complex;
    parent->c_float_array = powergl_resize( NULL, sizeof( element( float_array ) ) );
    element( float_array ) * this = parent->c_float_array;
    this->p_source = parent;
    this->a_name.value = NULL;
    this->a_id.value = NULL;
    this->_ext.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "float_array", "list_of_floats", parent, &this->_ext.value, NULL, 0 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
    init_simple_element_base( &this->a_count, "count", "uint", this, &this->a_count.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_polylist( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "mesh" ) == 0 ) {
    element( mesh ) * parent = ( element( mesh ) * ) parent_complex;
    element( polylist ) **ptr = parent->ch_polylist;
    ptr = powergl_resize( ptr, ++parent->n_polylist * sizeof( element( polylist ) * ) );
    parent->ch_polylist = ptr;
    parent->ch_polylist[parent->n_polylist - 1] = powergl_resize( NULL, sizeof( element( polylist ) ) );
    element( polylist )* this = parent->ch_polylist[parent->n_polylist - 1];

    this->p_mesh = parent;
    this->a_name.value = NULL;
    this->ch_input_local_offset = NULL;
    this->n_input_local_offset = 0;
    complex_element ***ch_cont[] = {
      ( complex_element ** * ) &this->ch_input_local_offset
    };

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "polylist", "none", parent, NULL, ch_cont, 1 );
    init_simple_element_base( &this->a_count, "count", "uint", this, &this->a_count.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_triangles( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "mesh" ) == 0 ) {
    element( mesh ) * parent = ( element( mesh ) * ) parent_complex;
    element( triangles ) **ptr = parent->ch_triangles;
    ptr = powergl_resize( ptr, ++parent->n_triangles * sizeof( element( triangles ) * ) );
    parent->ch_triangles = ptr;
    parent->ch_triangles[parent->n_triangles - 1] = powergl_resize( NULL, sizeof( element( triangles ) ) );
    element( triangles )* this = parent->ch_triangles[parent->n_triangles - 1];

    this->p_mesh = parent;
    this->a_name.value = NULL;
    this->ch_input_local_offset = NULL;
    this->n_input_local_offset = 0;
    complex_element ***ch_cont[] = {
      ( complex_element ** * ) &this->ch_input_local_offset
    };

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "triangles", "none", parent, NULL, ch_cont, 1 );
    init_simple_element_base( &this->a_count, "count", "uint", this, &this->a_count.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_vertices( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "mesh" ) == 0 ) {
    element( mesh ) * parent = ( element( mesh ) * ) parent_complex;
    parent->c_vertices = powergl_resize( NULL, sizeof( element( vertices ) ) );
    element( vertices ) * this = parent->c_vertices;
    this->p_mesh = parent;

    this->a_id.value = NULL;
    this->a_name.value = NULL;
    this->ch_input_local = NULL;
    this->n_input_local = 0;
    complex_element ***ch_cont[] = {
      ( complex_element ** * ) &this->ch_input_local
    };

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "vertices", "none", parent, NULL, ch_cont, 1 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_source( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "mesh" ) == 0 ) {
    element( mesh ) * parent = ( element( mesh ) * ) parent_complex;
    element( source ) **ptr = parent->ch_source;
    ptr = powergl_resize( ptr, ++parent->n_source * sizeof( element( source ) * ) );
    parent->ch_source = ptr;
    parent->ch_source[parent->n_source - 1] = powergl_resize( NULL, sizeof( element( source ) ) );
    element( source )* this = parent->ch_source[parent->n_source - 1];

    this->p_mesh = parent;
    this->a_id.value = NULL;
    this->a_name.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "source", "none", parent, NULL, NULL, 0 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_mesh( complex_element *parent_complex ) {
  if ( strcmp( parent_complex->name, "geometry" ) == 0 ) {
    element( geometry ) * parent = ( element( geometry ) * ) parent_complex;
    parent->c_mesh = powergl_resize( NULL, sizeof( element( mesh ) ) );
    element( mesh )* this = parent->c_mesh;
    this->p_geometry = parent;

    this->ch_source = NULL;
    this->ch_polylist = NULL;
    this->ch_triangles = NULL;
    this->n_source = 0;
    this->n_polylist = 0;
    this->n_triangles = 0;
    complex_element ***ch_cont[3] = {
      ( complex_element ** * ) &this->ch_source,
      ( complex_element ** * ) &this->ch_polylist,
      ( complex_element ** * ) &this->ch_triangles
    };

    init_complex_element_base( this, "mesh", "none", parent, NULL, ch_cont, 3 );
  } else {
    return 0;
  }
  return 1;
}

static int init_aspect_ratio( complex_element *parent_complex, const char **attr, size_t nattr ) {
  element( aspect_ratio )* this = NULL;
  complex_element *parent_ptr = NULL;

  if ( strcmp( parent_complex->name, "perspective" ) == 0 ) { // perspective
    element( perspective ) * parent = ( element( perspective ) * ) parent_complex;
    parent->c_aspect_ratio = powergl_resize( NULL, sizeof( element( aspect_ratio ) ) );
    this = parent->c_aspect_ratio;
    this->p_perspective = parent;
    parent_ptr = ( complex_element * ) parent_complex;
  } else if ( strcmp( parent_complex->name, "orthographic" ) == 0 ) { // orthographic
    element( orthographic ) * parent = ( element( orthographic ) * ) parent_complex;
    parent->c_aspect_ratio = powergl_resize( NULL, sizeof( element( aspect_ratio ) ) );
    this = parent->c_aspect_ratio;
    this->p_orthographic = parent;
    parent_ptr = ( complex_element * ) parent_complex;
  } else {
    return 0;
  }

  this->_ext.a_sid.value = NULL;
  this->_ext._ext.value = 0.0f;

  parse_attribs( attr, nattr );
  init_complex_element_base( this, "aspect_ratio", "float", parent_ptr, &this->_ext._ext.value, NULL, 0 );
  init_simple_element_base( &this->_ext.a_sid, "sid", "string", this, &this->_ext.a_sid.value );

  return 1;
}

static int init_zfar( complex_element *parent_complex, const char **attr, size_t nattr ) {
  element( zfar )* this = NULL;
  complex_element *parent_ptr = NULL;
  if ( strcmp( parent_complex->name, "perspective" ) == 0 ) { // perspective
    element( perspective ) * parent = ( element( perspective ) * ) parent_complex;
    parent->c_zfar = powergl_resize( NULL, sizeof( element( zfar ) ) );
    this = parent->c_zfar;
    this->p_perspective = parent;
    parent_ptr = ( complex_element * )parent;
  } else if ( strcmp( parent_complex->name, "orthographic" ) == 0 ) { // orthographic
    element( orthographic ) * parent = ( element( orthographic ) * ) parent_complex;
    parent->c_zfar = powergl_resize( NULL, sizeof( element( zfar ) ) );
    this = parent->c_zfar;
    this->p_orthographic = parent;
    parent_ptr = ( complex_element * )parent;
  } else {
    return 0;
  }

  this->_ext.a_sid.value = NULL;
  this->_ext._ext.value = 0.0f;

  parse_attribs( attr, nattr );
  init_complex_element_base( this, "zfar", "float", parent_ptr, &this->_ext._ext.value, NULL, 0 );
  init_simple_element_base( &this->_ext.a_sid, "sid", "string", this, &this->_ext.a_sid.value );

  return 1;
}

static int init_znear( complex_element *parent_complex, const char **attr, size_t nattr ) {
  element( znear )* this = NULL;
  complex_element *parent_ptr = NULL;
  if ( strcmp( parent_complex->name, "perspective" ) == 0 ) { // perspective
    element( perspective ) * parent = ( element( perspective ) * ) parent_complex;
    parent->c_znear = powergl_resize( NULL, sizeof( element( znear ) ) );
    this = parent->c_znear;
    this->p_perspective = parent;
    parent_ptr = ( complex_element * )parent;
  } else if ( strcmp( parent_complex->name, "orthographic" ) == 0 ) { // orthographic
    element( orthographic ) * parent = ( element( orthographic ) * ) parent_complex;
    parent->c_znear = powergl_resize( NULL, sizeof( element( znear ) ) );
    this = parent->c_znear;
    this->p_orthographic = parent;
    parent_ptr = ( complex_element * )parent;
  } else {
    return 0;
  }
  this->_ext.a_sid.value = NULL;
  this->_ext._ext.value = 0.0f;

  parse_attribs( attr, nattr );
  init_complex_element_base( this, "znear", "float", parent_ptr, &this->_ext._ext.value, NULL, 0 );
  init_simple_element_base( &this->_ext.a_sid, "sid", "string", this, &this->_ext.a_sid.value );
  return 1;
}

static int init_ymag( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "orthographic" ) == 0 ) { // orthographic
    element( orthographic ) * parent = ( element( orthographic ) * ) parent_complex;
    parent->cc_xmag = NULL;
    parent->cc_ymag = NULL;
    parent->cc_ymag = powergl_resize( NULL, sizeof( element( ymag ) ) );
    element( ymag )* this = parent->cc_ymag;
    this->p_orthographic = parent;
    this->_ext.a_sid.value = NULL;
    this->_ext._ext.value = 0.0f;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "ymag", "float", parent, &this->_ext._ext.value, NULL, 0 );
    init_simple_element_base( &this->_ext.a_sid, "sid", "string", this, &this->_ext.a_sid.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_xmag( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "orthographic" ) == 0 ) { // orthographic
    element( orthographic ) * parent = ( element( orthographic ) * ) parent_complex;
    parent->cc_xmag = NULL;
    parent->cc_ymag = NULL;
    parent->cc_xmag = powergl_resize( NULL, sizeof( element( xmag ) ) );
    element( xmag )* this = parent->cc_xmag;
    this->p_orthographic = parent;
    this->_ext.a_sid.value = NULL;
    this->_ext._ext.value = 0.0f;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "xmag", "float", parent, &this->_ext._ext.value, NULL, 0 );
    init_simple_element_base( &this->_ext.a_sid, "sid", "string", this, &this->_ext.a_sid.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_yfov( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "perspective" ) == 0 ) { // perspective
    element( perspective ) * parent = ( element( perspective ) * ) parent_complex;
    parent->cc_xfov = NULL;
    parent->cc_yfov = NULL;
    parent->cc_yfov = powergl_resize( NULL, sizeof( element( yfov ) ) );
    element( yfov )* this = parent->cc_yfov;
    this->p_perspective = parent;
    this->_ext.a_sid.value = NULL;
    this->_ext._ext.value = 0.0f;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "yfov", "float", parent, &this->_ext._ext.value, NULL, 0 );
    init_simple_element_base( &this->_ext.a_sid, "sid", "string", this, &this->_ext.a_sid.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_xfov( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "perspective" ) == 0 ) { // perspective
    element( perspective ) * parent = ( element( perspective ) * ) parent_complex;
    parent->cc_xfov = NULL;
    parent->cc_yfov = NULL;
    parent->cc_xfov = powergl_resize( NULL, sizeof( element( xfov ) ) );
    element( xfov )* this = parent->cc_xfov;
    this->p_perspective = parent;
    this->_ext.a_sid.value = NULL;
    this->_ext._ext.value = 0.0f;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "xfov", "float", parent, &this->_ext._ext.value, NULL, 0 );
    init_simple_element_base( &this->_ext.a_sid, "sid", "string", this, &this->_ext.a_sid.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_orthographic( complex_element *parent_complex ) {
  if ( strcmp( parent_complex->name, "technique_common" ) == 0 ) {
    element( optics_technique_common ) * parent = ( element( optics_technique_common ) * ) parent_complex;
    parent->cc_orthographic = NULL;
    parent->cc_perspective = NULL;
    parent->cc_orthographic = powergl_resize( NULL, sizeof( element( orthographic ) ) );
    element( orthographic )* this = parent->cc_orthographic;
    this->p_optics_technique_common = parent;

    init_complex_element_base( this, "orthographic", "none", parent, NULL, NULL, 0 );
  } else {
    return 0;
  }
  return 1;
}

static int init_perspective( complex_element *parent_complex ) {
  if ( strcmp( parent_complex->name, "technique_common" ) == 0 ) {
    element( optics_technique_common ) * parent = ( element( optics_technique_common ) * ) parent_complex;
    parent->cc_orthographic = NULL;
    parent->cc_perspective = NULL;
    parent->cc_perspective = powergl_resize( NULL, sizeof( element( perspective ) ) );
    element( perspective )* this = parent->cc_perspective;

    init_complex_element_base( this, "perspective", "none", parent, NULL, NULL, 0 );
  } else {
    return 0;
  }
  return 1;
}

static int init_technique_common( complex_element *parent_complex ) {
  if ( strcmp( parent_complex->name, "optics" ) == 0 ) { // optics
    element( optics ) * parent = ( element( optics ) * ) parent_complex;
    parent->c_optics_technique_common = powergl_resize( NULL, sizeof( element( optics_technique_common ) ) );
    element( optics_technique_common )* this = parent->c_optics_technique_common;
    this->p_optics = parent;

    init_complex_element_base( this, "technique_common", "none", parent, NULL, NULL, 0 );
  } else if ( strcmp( parent_complex->name, "source" ) == 0 ) { // source
    element( source ) * parent = ( element( source ) * ) parent_complex;
    parent->c_source_technique_common = powergl_resize( NULL, sizeof( element( source_technique_common ) ) );
    element( source_technique_common )* this = parent->c_source_technique_common;
    this->p_source = parent;

    init_complex_element_base( this, "technique_common", "none", parent, NULL, NULL, 0 );
  } else {
    return 0;
  }
  return 1;
}

static int init_optics( complex_element *parent_complex ) {
  if ( strcmp( parent_complex->name, "camera" ) == 0 ) {
    element( camera ) * parent = ( element( camera ) * ) parent_complex;
    parent->c_optics = powergl_resize( NULL, sizeof( element( optics ) ) );
    element( optics )* this = parent->c_optics;
    this->p_camera = parent;

    init_complex_element_base( this, "optics", "none", parent, NULL, NULL, 0 );
  } else {
    return 0;
  }
  return 1;
}

static int init_instance_visual_scene( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "scene" ) == 0 ) {
    element( scene ) * parent = ( element( scene ) * ) parent_complex;
    parent->c_instance_visual_scene = powergl_resize( NULL, sizeof( element( instance_visual_scene ) ) );
    element( instance_visual_scene ) * this = parent->c_instance_visual_scene;
    this->p_scene = parent;
    this->a_sid.value = NULL;
    this->a_name.value = NULL;
    this->a_url.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "instance_visual_scene", "none", parent, NULL, NULL, 0 );
    init_simple_element_base( &this->a_sid, "sid", "string", this, &this->a_sid.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
    init_simple_element_base( &this->a_url, "url", "string", this, &this->a_url.value );
    init_ptr_complex_element_base( &this->r_visual_scene, this->a_url.value, "visual_scene", this );
  } else {
    return 0;
  }
  return 1;
}

static int init_visual_scene( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "library_visual_scenes" ) == 0 ) {
    element( library_visual_scenes ) * parent = ( element( library_visual_scenes ) * ) parent_complex;
    element( visual_scene ) **ptr = parent->ch_visual_scene;
    ptr = powergl_resize( ptr, ++parent->n_visual_scene * sizeof( element( visual_scene ) * ) );
    parent->ch_visual_scene = ptr;
    parent->ch_visual_scene[parent->n_visual_scene - 1] = powergl_resize( NULL, sizeof( element( visual_scene ) ) );
    element( visual_scene )* this = parent->ch_visual_scene[parent->n_visual_scene - 1];

    this->p_library_visual_scenes = parent;
    this->a_id.value = NULL;
    this->a_name.value = NULL;
    this->ch_node = NULL;
    this->n_node = 0;
    complex_element ***ch_cont[1] = {
      ( complex_element ** * ) &this->ch_node
    };


    parse_attribs( attr, nattr );
    init_complex_element_base( this, "visual_scene", "none", parent, NULL, ch_cont, 1 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_geometry( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "library_geometries" ) == 0 ) {
    element( library_geometries ) * parent = ( element( library_geometries ) * ) parent_complex;
    element( geometry ) **ptr = parent->ch_geometry;
    ptr = powergl_resize( ptr, ++parent->n_geometry * sizeof( element( geometry ) * ) );
    parent->ch_geometry = ptr;
    parent->ch_geometry[parent->n_geometry - 1] = powergl_resize( NULL, sizeof( element( geometry ) ) );
    element( geometry )* this = parent->ch_geometry[parent->n_geometry - 1];

    this->p_library_geometries = parent;
    this->a_id.value = NULL;
    this->a_name.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "geometry", "none", parent, NULL, NULL, 0 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_camera( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "library_cameras" ) == 0 ) {
    element( library_cameras ) * parent = ( element( library_cameras ) * ) parent_complex;
    element( camera ) **ptr = parent->ch_camera;
    ptr = powergl_resize( ptr, ++parent->n_camera * sizeof( element( camera ) * ) );
    parent->ch_camera = ptr;
    parent->ch_camera[parent->n_camera - 1] = powergl_resize( NULL, sizeof( element( camera ) ) );
    element( camera )* this = parent->ch_camera[parent->n_camera - 1];

    this->p_library_cameras = parent;
    this->a_id.value = NULL;
    this->a_name.value = NULL;

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "camera", "none", parent, NULL, NULL, 0 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_library_cameras( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "COLLADA" ) == 0 ) {
    element( collada ) * parent = ( element( collada ) * ) parent_complex;
    element( library_cameras ) **ptr = parent->ch_library_cameras;
    ptr = powergl_resize( ptr, ++parent->n_library_cameras * sizeof( element( library_cameras ) * ) );
    parent->ch_library_cameras = ptr;

    parent->ch_library_cameras[parent->n_library_cameras - 1] = powergl_resize( NULL, sizeof( element( library_cameras ) ) );
    element( library_cameras )* this = parent->ch_library_cameras[parent->n_library_cameras - 1];

    this->p_collada = parent;
    this->a_id.value = NULL;
    this->a_name.value = NULL;
    this->n_camera = 0;
    this->ch_camera = NULL;
    complex_element ***ch_cont[1] = {
      ( complex_element ** * ) &this->ch_camera
    };

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "library_cameras", "none", parent, NULL, ch_cont, 1 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_library_geometries( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "COLLADA" ) == 0 ) {
    element( collada ) * parent = ( element( collada ) * ) parent_complex;
    element( library_geometries ) **ptr = parent->ch_library_geometries;
    ptr = powergl_resize( ptr, ++parent->n_library_geometries * sizeof( element( library_geometries ) * ) );
    parent->ch_library_geometries = ptr;
    parent->ch_library_geometries[parent->n_library_geometries - 1] = powergl_resize( NULL, sizeof( element( library_geometries ) ) );
    element( library_geometries )* this = parent->ch_library_geometries[parent->n_library_geometries - 1];

    this->p_collada = parent;
    this->a_id.value = NULL;
    this->a_name.value = NULL;
    this->n_geometry = 0;
    this->ch_geometry = NULL;
    complex_element ***ch_cont[1] = {
      ( complex_element ** * ) &this->ch_geometry
    };

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "library_geometries", "none", parent, NULL, ch_cont, 1 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_library_visual_scenes( complex_element *parent_complex, const char **attr, size_t nattr ) {
  if ( strcmp( parent_complex->name, "COLLADA" ) == 0 ) {
    element( collada ) * parent = ( element( collada ) * ) parent_complex;
    element( library_visual_scenes ) **ptr = parent->ch_library_visual_scenes;
    ptr = powergl_resize( ptr, ++parent->n_library_visual_scenes * sizeof( element( library_visual_scenes ) * ) );
    parent->ch_library_visual_scenes = ptr;
    parent->ch_library_visual_scenes[parent->n_library_visual_scenes - 1] = powergl_resize( NULL, sizeof( element( library_visual_scenes ) ) );
    element( library_visual_scenes )* this = parent->ch_library_visual_scenes[parent->n_library_visual_scenes - 1];

    this->p_collada = parent;
    this->a_id.value = NULL;
    this->a_name.value = NULL;
    this->n_visual_scene = 0;
    this->ch_visual_scene = NULL;
    complex_element ***ch_cont[1] = {
      ( complex_element ** * ) &this->ch_visual_scene
    };

    parse_attribs( attr, nattr );
    init_complex_element_base( this, "library_visual_scenes", "none", parent, NULL, ch_cont, 1 );
    init_simple_element_base( &this->a_id, "id", "string", this, &this->a_id.value );
    init_simple_element_base( &this->a_name, "name", "string", this, &this->a_name.value );
  } else {
    return 0;
  }
  return 1;
}

static int init_scene( complex_element *parent_complex ) {
  if ( strcmp( parent_complex->name, "COLLADA" ) == 0 ) {
    element( collada ) * parent = ( element( collada ) * ) parent_complex;
    parent->c_scene = powergl_resize( NULL, sizeof( element( scene ) ) );
    element( scene ) * this = parent->c_scene;
    this->p_collada = parent;

    init_complex_element_base( this, "scene", "none", parent, NULL, NULL, 0 );
  } else {
    return 0;
  }
  return 1;
}

static int init_collada( complex_element *parent_complex, const char **attr, size_t nattr ) {
  element( collada )* this = ( element( collada ) * ) parent_complex;

  this->a_version.value = NULL;
  this->a_xmlns.value = NULL;

  this->ch_library_geometries = NULL;
  this->ch_library_cameras = NULL;
  this->ch_library_lights = NULL;
  this->ch_library_visual_scenes = NULL;
  this->ch_library_materials = NULL;

  this->n_library_geometries = 0;
  this->n_library_cameras = 0;
  this->n_library_lights = 0;
  this->n_library_visual_scenes = 0;
  this->n_library_materials = 0;

  complex_element ***ch_cont[5] = {
    ( complex_element ** * ) &this->ch_library_geometries,
    ( complex_element ** * ) &this->ch_library_cameras,
    ( complex_element ** * ) &this->ch_library_lights,
    ( complex_element ** * ) &this->ch_library_materials,
    ( complex_element ** * ) &this->ch_library_visual_scenes
  };

  parse_attribs( attr, nattr );
  init_complex_element_base( this, "COLLADA", "none", NULL, NULL, ch_cont, 5 );
  init_simple_element_base( &this->a_xmlns, "xmlns", "string", this, &this->a_xmlns.value );
  init_simple_element_base( &this->a_version, "version", "string", this, &this->a_version.value );

  return 1;
}


static void elemend( void *userdata, const char *elem ) {
  g_undefined_element_flag = 0;
  g_parser_status = 2;
  g_current_depth--;

  if ( g_current_depth == 5 ) {
    if ( strcmp( elem, "perspective" ) == 0 ) {
    } else if ( strcmp( elem, "orthographic" ) == 0 ) {
    } else if ( strcmp( elem, "float_array" ) == 0 ) {
    } else if ( strcmp( elem, "int_array" ) == 0 ) {
    } else if ( strcmp( elem, "technique_common" ) == 0 ) {
    } else if ( strcmp( elem, "input" ) == 0 ) {
    } else if ( strcmp( elem, "p" ) == 0 ) {
    } else if ( strcmp( elem, "vcount" ) == 0 ) {
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 4 ) {
    if ( strcmp( elem, "technique_common" ) == 0 ) {
    } else if ( strcmp( elem, "source" ) == 0 ) {
    } else if ( strcmp( elem, "vertices" ) == 0 ) {
    } else if ( strcmp( elem, "polylist" ) == 0 ) {
    } else if ( strcmp( elem, "triangles" ) == 0 ) {
    } else if ( strcmp( elem, "matrix" ) == 0 ) {
    } else if ( strcmp( elem, "instance_camera" ) == 0 ) {
    } else if ( strcmp( elem, "instance_geometry" ) == 0 ) {
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 6 ) {
    if ( strcmp( elem, "xfov" ) == 0 ) {
    } else if ( strcmp( elem, "yfov" ) == 0 ) {
    } else if ( strcmp( elem, "aspect_ratio" ) == 0 ) {
    } else if ( strcmp( elem, "znear" ) == 0 ) {
    } else if ( strcmp( elem, "zfar" ) == 0 ) {
    } else if ( strcmp( elem, "accessor" ) == 0 ) {
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 1 ) {
    if ( strcmp( elem, "library_cameras" ) == 0 ) {
    } else if ( strcmp( elem, "library_geometries" ) == 0 ) {
    } else if ( strcmp( elem, "library_visual_scenes" ) == 0 ) {
    } else if ( strcmp( elem, "scene" ) == 0 ) {
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 2 ) {
    if ( strcmp( elem, "up_axis" ) == 0 ) {
    } else if ( strcmp( elem, "camera" ) == 0 ) {
    } else if ( strcmp( elem, "geometry" ) == 0 ) {
    } else if ( strcmp( elem, "visual_scene" ) == 0 ) {
    } else if ( strcmp( elem, "instance_visual_scene" ) == 0 ) {
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 3 ) {
    if ( strcmp( elem, "optics" ) == 0 ) {
    } else if ( strcmp( elem, "mesh" ) == 0 ) {
    } else if ( strcmp( elem, "node" ) == 0 ) {
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 0 ) {
    if ( strcmp( elem, "COLLADA" ) == 0 ) {
      /* printf("%s\n", ((complex_element*) g_current_elem)->name); */
      g_current_depth--;
      return;
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 7 ) {
    if ( strcmp( elem, "param" ) == 0 ) {
    } else {
      g_undefined_element_flag = 1;
    }
  }

  g_current_depth++;

  if ( g_undefined_element_flag != 1 ) {
    /* printf("%s\n", ((complex_element*) g_current_elem)->name); */
    g_current_elem = ( ( complex_element * ) g_current_elem )->parent;
    g_current_depth--;
  }
}

static unsigned long *parse_list_of_uints_tail( size_t *value_size, const XML_Char *str, int len ) {
  char *end = NULL;
  const char *old_ptr = str;
  int i = 0;
  for ( unsigned long f = strtoul( str, &end, 10 ); end <= ( old_ptr + len * sizeof( char ) ); f = strtoul( str, &end, 10 ) ) {
    if ( end == str ) { //  If no conversion can be performed
      break;
    }
    str = end;
    if ( errno == ERANGE ) {
      printf( "range error, got " );
      errno = 0;
    } else {
      i++;
    }
  }
  if ( i == 0 ) {
    *value_size = 0;
    return NULL;
  }
  unsigned long *arr = NULL;
  arr = powergl_resize( arr, i * sizeof( unsigned long ) );
  i = 0;
  str = old_ptr;
  end = NULL;
  for ( unsigned long f = strtoul( str, &end, 10 ); end <= ( old_ptr + len * sizeof( char ) ); f = strtoul( str, &end, 10 ) ) {
    if ( end == str ) { //  If no conversion can be performed
      break;
    }
    str = end;
    if ( errno == ERANGE ) {
      printf( "range error, got " );
      errno = 0;
    } else {
      *( arr + i ) = f;
      i++;
    }
  }
  *value_size = i;
  return arr;
}

static long int *parse_list_of_ints_tail( size_t *value_size, const XML_Char *str, int len ) {
  char *end = NULL;
  const char *old_ptr = str;
  int i = 0;
  for ( long int f = strtol( str, &end, 10 ); end <= ( old_ptr + len * sizeof( char ) ); f = strtol( str, &end, 10 ) ) {
    if ( end == str ) { //  If no conversion can be performed
      break;
    }
    str = end;
    if ( errno == ERANGE ) {
      printf( "range error, got " );
      errno = 0;
    } else {
      i++;
    }
  }
  if ( i == 0 ) {
    *value_size = 0;
    return NULL;
  }
  long int *arr = NULL;
  arr = powergl_resize( arr, i * sizeof( long int ) );
  i = 0;
  str = old_ptr;
  end = NULL;
  for ( long int f = strtol( str, &end, 10 ); end <= ( old_ptr + len * sizeof( char ) ); f = strtol( str, &end, 10 ) ) {
    if ( end == str ) { //  If no conversion can be performed
      break;
    }
    str = end;
    if ( errno == ERANGE ) {
      printf( "range error, got " );
      errno = 0;
    } else {
      *( arr + i ) = f;
      i++;
    }
  }
  *value_size = i;
  return arr;
}

static double *parse_list_of_floats_tail( size_t *value_size, const XML_Char *str, int len ) {
  char *end = NULL;
  const char *old_ptr = str;
  int i = 0;
  for ( double f = strtod( str, &end ); end <= ( old_ptr + len * sizeof( char ) ); f = strtod( str, &end ) ) {
    if ( end == str ) { //  If no conversion can be performed
      break;
    }
    str = end;
    if ( errno == ERANGE ) {
      printf( "range error, got " );
      errno = 0;
    } else {
      i++;
    }
  }
  if ( i == 0 ) {
    *value_size = 0;
    return NULL;
  }
  double *arr = NULL;
  arr = powergl_resize( arr, i * sizeof( double ) );
  i = 0;
  str = old_ptr;
  end = NULL;
  for ( double f = strtod( str, &end ); end <= ( old_ptr + len * sizeof( char ) ); f = strtod( str, &end ) ) {
    if ( end == str ) { //  If no conversion can be performed
      break;
    }
    str = end;
    if ( errno == ERANGE ) {
      printf( "range error, got " );
      errno = 0;
    } else {
      *( arr + i ) = f;
      i++;
    }
  }
  *value_size = i;
  return arr;
}

static void parse_list_of_floats( complex_element *this, int merge_data_flag, const XML_Char *string, int len ) {
  double **value_ptr = ( double ** )this->value_ptr;
  if ( merge_data_flag ) {
    size_t size = 0;
    double *buffer = parse_list_of_floats_tail( &size, string, len );
    if ( size != 0 ) {
      size_t new_size = size + this->value_size;
      ( *value_ptr ) = powergl_resize( ( *value_ptr ), new_size * sizeof( double ) );
      assert( buffer );
      for ( int i = this->value_size, j = 0 ; i < new_size; i++, j++ ) {
        ( *value_ptr )[i] = buffer[j];
      }
      this->value_size = new_size;
    }
  } else {
    size_t size = 0;
    double *buffer = parse_list_of_floats_tail( &size, string, len );
    if ( size > 0 && buffer != NULL ) {
      ( *value_ptr ) = buffer;
      this->value_size = size;
    }
  }
}

static void parse_list_of_ints( complex_element *this, int merge_data_flag, const XML_Char *string, int len ) {
  long int **value_ptr = ( long int ** )this->value_ptr;
  if ( merge_data_flag ) {
    size_t size = 0;
    long int *buffer = parse_list_of_ints_tail( &size, string, len );
    if ( size != 0 ) {
      size_t new_size = size + this->value_size;
      ( *value_ptr ) = powergl_resize( ( *value_ptr ), new_size * sizeof( long int ) );
      assert( buffer );
      for ( int i = this->value_size, j = 0 ; i < new_size; i++, j++ ) {
        ( *value_ptr )[i] = buffer[j];
      }
      this->value_size = new_size;
    }
  } else {
    size_t size = 0;
    long int *buffer = parse_list_of_ints_tail( &size, string, len );
    if ( size > 0 && buffer != NULL ) {
      ( *value_ptr ) = buffer;
      this->value_size = size;
    }
  }
}

static void parse_list_of_uints( complex_element *this, int merge_data_flag, const XML_Char *string, int len ) {
  unsigned long **value_ptr = ( unsigned long ** )this->value_ptr;
  if ( merge_data_flag ) {
    size_t size = 0;
    unsigned long *buffer = parse_list_of_uints_tail( &size, string, len );
    if ( size != 0 ) {
      size_t new_size = size + this->value_size;
      ( *value_ptr ) = powergl_resize( ( *value_ptr ), new_size * sizeof( unsigned long ) );
      assert( buffer );
      for ( int i = this->value_size, j = 0 ; i < new_size; i++, j++ ) {
        ( *value_ptr )[i] = buffer[j];
      }
      this->value_size = new_size;
    }
  } else {
    size_t size = 0;
    unsigned long *buffer = parse_list_of_uints_tail( &size, string, len );
    if ( size > 0 && buffer != NULL ) {
      ( *value_ptr ) = buffer;
      this->value_size = size;
    }
  }
}

static void parse_double( complex_element *this, int merge_data_flag, const XML_Char *string, int len ) {
  double *value_ptr = ( double * )this->value_ptr;
  if ( merge_data_flag ) {
    if ( this->value_size == 0 ) {
      size_t size = 0;
      double *buffer = parse_list_of_floats_tail( &size, string, len );
      if ( size != 0 ) {
        assert( buffer );
        ( *value_ptr ) = buffer[0];
        this->value_size = 1;
      }
    }
  } else {
    size_t size = 0;
    double *buffer = parse_list_of_floats_tail( &size, string, len );
    if ( size > 0 && buffer != NULL ) {
      ( *value_ptr ) = buffer[0];
      free( buffer );
    }
  }
}

static void chardata( void *userdata, const XML_Char *string, int len ) {
  int data_parsed = 1;
  int merge_data_flag = 0;
  // bu fonksiyonda string komple geldigi icin parse edilirken kontroller eklenecek !
  if ( g_parser_status == 1 ) { // eger onceki asamada chardata calistiysa onceki ile burdaki string i birlestir
    merge_data_flag = 1;
  }

  if ( g_current_depth == 6 ) {
    if ( strcmp( g_current_elem_tag, "float_array" ) == 0 ) {
      parse_list_of_floats( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else if ( strcmp( g_current_elem_tag, "int_array" ) == 0 ) {
      parse_list_of_ints( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else if ( strcmp( g_current_elem_tag, "p" ) == 0 ) {
      parse_list_of_uints( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else if ( strcmp( g_current_elem_tag, "vcount" ) == 0 ) {
      parse_list_of_uints( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else {
      data_parsed = 0;
    }
  } else if ( g_current_depth == 5 ) {
    if ( strcmp( g_current_elem_tag, "matrix" ) == 0 ) {
      parse_list_of_floats( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else {
      data_parsed = 0;
    }
  } else if ( g_current_depth == 7 ) {
    if ( strcmp( g_current_elem_tag, "xfov" ) == 0 ) {
      parse_double( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else if ( strcmp( g_current_elem_tag, "yfov" ) == 0 ) {
      parse_double( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else if ( strcmp( g_current_elem_tag, "aspect_ratio" ) == 0 ) {
      parse_double( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else if ( strcmp( g_current_elem_tag, "znear" ) == 0 ) {
      parse_double( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else if ( strcmp( g_current_elem_tag, "zfar" ) == 0 ) {
      parse_double( ( complex_element * )g_current_elem, merge_data_flag, string, len );
    } else {
      data_parsed = 0;
    }
  } else if ( g_current_depth == 3 ) {
    if ( strncmp( g_current_elem_tag, "up", 2 ) == 0 ) {
    } else {
      data_parsed = 0;
    }
  } else {
    data_parsed = 0;
  }

  /* if(data_parsed){ */
  /*   for(int tab_count=0;tab_count<g_current_depth;++tab_count){ */
  /*     printf("  "); */
  /*   } */
  /*   printf("%.*s\n",len,string); */
  /* } */

  g_parser_status = 1;

}

static void elemstart( void *userdata, const char *elem, const char **attr ) {
  g_current_elem_tag = elem;
  g_undefined_element_flag = 0;
  g_parser_status = 0;

  reset_parsed_attrib_states();

  size_t nattr = XML_GetSpecifiedAttributeCount( ( XML_Parser ) userdata );

  complex_element *parent = ( complex_element * ) g_current_elem;

  if ( strcmp( elem, "COLLADA" ) == 0 ) {


  } else {

    assert( parent );

  }

  int result = 1;
  // burdaki string karsilastirmasi icin hash fonksiyonu bulunacak
  // bu kisimda herhangi bir element icin parse_attribs calistirilmaz ise onceki degerler kaliyor
  // o yuzden ya parse_attribs en ustte bir kez cagirilacak yada dikkatli sekilde her biri iicn ayri ayri cagirilacak
  if ( g_current_depth == 5 ) {
    if ( strcmp( elem, "perspective" ) == 0 ) {
      result = init_perspective( parent );
    } else if ( strcmp( elem, "orthographic" ) == 0 ) {
      result = init_orthographic( parent );
    } else if ( strcmp( elem, "float_array" ) == 0 ) {
      result = init_float_array( parent, attr, nattr );
    } else if ( strcmp( elem, "int_array" ) == 0 ) {
      result = init_int_array( parent, attr, nattr );
    } else if ( strcmp( elem, "technique_common" ) == 0 ) {
      result = init_technique_common( parent );
      if ( result == 0 ) {
        g_undefined_element_flag = 1;
      }
    } else if ( strcmp( elem, "input" ) == 0 ) {
      result = init_input( parent, attr, nattr );
      if ( result == 0 ) {
        g_undefined_element_flag = 1;
      }
    } else if ( strcmp( elem, "p" ) == 0 ) {
      result = init_p( parent );
      if ( result == 0 ) {
        g_undefined_element_flag = 1;
      }
    } else if ( strcmp( elem, "vcount" ) == 0 ) {
      result = init_vcount( parent );
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 4 ) {
    if ( strcmp( elem, "technique_common" ) == 0 ) {
      result = init_technique_common( parent );
      if ( result == 0 ) {
        g_undefined_element_flag = 1;
      }
    } else if ( strcmp( elem, "source" ) == 0 ) {
      result = init_source( parent, attr, nattr );
    } else if ( strcmp( elem, "vertices" ) == 0 ) {
      result = init_vertices( parent, attr, nattr );
    } else if ( strcmp( elem, "polylist" ) == 0 ) {
      result = init_polylist( parent, attr, nattr );
    } else if ( strcmp( elem, "triangles" ) == 0 ) {
      result = init_triangles( parent, attr, nattr );
    } else if ( strcmp( elem, "matrix" ) == 0 ) {
      result = init_matrix( parent, attr, nattr );
    } else if ( strcmp( elem, "instance_camera" ) == 0 ) {
      result = init_instance_camera( parent, attr, nattr );
    } else if ( strcmp( elem, "instance_geometry" ) == 0 ) {
      result = init_instance_geometry( parent, attr, nattr );
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 6 ) {
    if ( strcmp( elem, "xfov" ) == 0 ) {
      result =  init_xfov( parent, attr, nattr );
    } else if ( strcmp( elem, "yfov" ) == 0 ) {
      result = init_yfov( parent, attr, nattr );
    } else if ( strcmp( elem, "aspect_ratio" ) == 0 ) {
      result = init_aspect_ratio( parent, attr, nattr );
    } else if ( strcmp( elem, "znear" ) == 0 ) {
      result = init_znear( parent, attr, nattr );
    } else if ( strcmp( elem, "zfar" ) == 0 ) {
      result = init_zfar( parent, attr, nattr );
    } else if ( strcmp( elem, "accessor" ) == 0 ) {
      result = init_accessor( parent, attr, nattr );
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 1 ) {
    if ( strcmp( elem, "library_cameras" ) == 0 ) {
      result = init_library_cameras( parent, attr, nattr );
    } else if ( strcmp( elem, "library_geometries" ) == 0 ) {
      result = init_library_geometries( parent, attr, nattr );
    } else if ( strcmp( elem, "library_visual_scenes" ) == 0 ) {
      result = init_library_visual_scenes( parent, attr, nattr );
    } else if ( strcmp( elem, "scene" ) == 0 ) {
      result = init_scene( parent );
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 2 ) {
    if ( strcmp( elem, "up_axis" ) == 0 ) {
      // not implemented
    } else if ( strcmp( elem, "camera" ) == 0 ) {
      result = init_camera( parent, attr, nattr );
    } else if ( strcmp( elem, "geometry" ) == 0 ) {
      result =  init_geometry( parent, attr, nattr );
    } else if ( strcmp( elem, "visual_scene" ) == 0 ) {
      result =  init_visual_scene( parent, attr, nattr );
    } else if ( strcmp( elem, "instance_visual_scene" ) == 0 ) {
      result =  init_instance_visual_scene( parent, attr, nattr );
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 3 ) {
    if ( strcmp( elem, "optics" ) == 0 ) {
      result = init_optics( parent );
    } else if ( strcmp( elem, "mesh" ) == 0 ) {
      result = init_mesh( parent );
    } else if ( strcmp( elem, "node" ) == 0 ) {
      result = init_node( parent, attr, nattr );
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 0 ) {
    if ( strcmp( elem, "COLLADA" ) == 0 ) {
      result = init_collada( parent, attr, nattr );
    } else {
      g_undefined_element_flag = 1;
    }
  } else if ( g_current_depth == 7 ) {
    if ( strcmp( elem, "param" ) == 0 ) {
      result = init_param( parent, attr, nattr );
    } else {
      g_undefined_element_flag = 1;
    }
  }

  if ( result == 0 ) {
    /* fprintf(stderr,"%s element couldnt init\n", g_current_elem_tag); */
  }

  if ( !g_undefined_element_flag ) {
    g_current_depth++;
  } else {
    /* fprintf(stderr,"%s element is not defined\n", g_current_elem_tag); */
  }
}

static int resolve_refs( complex_element *root, int n_resolved ) {

  int resolved = 0;

  for ( int i = 0; i < root->n_elem; ++i ) {
    if ( n_resolved + resolved == g_n_pending_reference ) {
      return resolved;
    } else {
      resolved += resolve_refs( root->elems[i], n_resolved + resolved );
    }
  }

  if ( n_resolved + resolved == g_n_pending_reference ) {
    return n_resolved + resolved;
  } else {

    for ( int k = 0; k < g_n_pending_reference; k++ ) {

      if ( g_pending_references[k]->src[0] == '#' ) {
        // URI Addressing

        for ( int j = 0; j < root->n_attrib; ++j ) {

          if ( strcmp( "id", root->attribs[j]->name ) == 0 ) {

            if ( strcmp( ( g_pending_references[k]->src + sizeof( char ) ), *( ( char ** )root->attribs[j]->value_ptr ) ) == 0 ) { // + sizeof(char) is used to skip # char

              if ( strcmp( g_pending_references[k]->ptr_type, root->name ) == 0 ) {

                g_pending_references[k]->ptr = root;
                // printf("\nfound ref [ elem =  %s ] [ str = %s ] [ type = %s ] [ ptr = %p ]", root->name, g_pending_references[k]->src,g_pending_references[k]->ptr_type,g_pending_references[k]->ptr);
                return 1 + resolved;

              }

            }

          }

        }

      } else {
        // SID Addressing

        // not implemented yet
      }

    }

  }

  return resolved;

}

static size_t n_free;


void collada_func( delete_complex_element )( complex_element *root, size_t depth ) {

  if ( root == NULL ) {

    return;

  }


  printf( "element [%s] [%p]\n", root->name, root );


  if ( root->elems != NULL ) {

    // delete child elems
    for ( size_t i = 0; i < root->n_elem ; i++ ) {

      collada_func( delete_complex_element )( root->elems[i], depth + 1 );

    }


    printf( "[%lu] memfree  = [ element -> elems [%p ] ]\n", n_free++, root->elems );
    free( root->elems );
    root->elems = NULL;
    root->n_elem = 0;
  }


  if ( root->attribs != NULL ) {

    // delete attribs
    for ( size_t i = 0; i < root->n_attrib ; i++ ) {

      if ( root->attribs[i]->value_ptr ) {

        if ( strcmp( "string", root->attribs[i]->base_type ) == 0 ) {

          printf( "[%lu] memfree  = [ attribute [%lu] -> value_ptr [%p] ]\n", n_free++, i, root->attribs[i]->value_ptr );

          char **ptr = ( char ** ) root->attribs[i]->value_ptr;

          free( *ptr );
          ptr = NULL;
          root->attribs[i]->value_ptr = NULL;
        }

      }

      if ( root->attribs[i]->base_type ) {

        printf( "[%lu] memfree  = [ attribute [%lu] -> base_type [%p] ] \n", n_free++, i, root->attribs[i]->base_type );
        free( root->attribs[i]->base_type );
        root->attribs[i]->base_type = NULL;

      }

      if ( root->attribs[i]->name ) {

        printf( "[%lu] memfree  = [ attribute [%lu] -> name [%p] ]\n", n_free++, i, root->attribs[i]->name );
        free( root->attribs[i]->name );
        root->attribs[i]->name = NULL;

      }

      // DELETE ATTRIBUTE

      printf( "[%lu] memfree  = [ attribute [%lu] [%p] ]\n", n_free++, i, root->attribs[i] );
      root->attribs[i]->parent = NULL;
      //free(root->attribs[i]);
      root->attribs[i] = NULL;

    }



    printf( "[%lu] memfree  = [ element -> attribs [%p] ]\n", n_free++, root->attribs );
    free( root->attribs );
    root->attribs = NULL;
    root->n_attrib = 0;

  }



  if ( root->refs != NULL ) {

    for ( size_t i = 0; i < root->n_ref; i++ ) {

      if ( root->refs[i]->ptr_type != NULL ) {

        printf( "[%lu] memfree  = [ refs [%lu] -> ptr_type [%p] ]\n", n_free++, i, root->refs[i]->ptr_type );
        free( root->refs[i]->ptr_type );
        root->refs[i]->ptr_type = NULL;
      }

      root->refs[i]->parent = NULL;
      root->refs[i]->ptr = NULL;

      printf( "[%lu] memfree  = [ refs [%lu] [%p] ]\n", n_free++, i, root->refs[i] );
      //free(root->refs[i]);
      root->refs[i] = NULL;
    }


    printf( "[%lu] memfree  = [ element -> refs [%p] ]\n", n_free++, root->refs );
    free( root->refs );
    root->refs = NULL;
    root->n_ref = 0;

  }

  if ( root->ch_container != NULL ) { // complex_element****

    for ( size_t i = 0; i < root->n_ch_container; i++ ) {

      if ( root->ch_container[i] != NULL ) { // complex_element***

        if ( *root->ch_container[i] != NULL ) { // complex_element**
          printf( "[%lu] memfree  = [ ch_container [%lu] [%p] ]\n", n_free++, i, *root->ch_container[i] );
          free( *root->ch_container[i] );
          *root->ch_container[i] = NULL;
        }

      }

    }

    printf( "[%lu] memfree  = [ element -> ch_container [%p] ]\n", n_free++, root->ch_container );
    free( root->ch_container );
    root->ch_container = NULL;
    root->n_ch_container = 0;

  }


  if ( root->value_ptr != NULL ) {

    printf( "[%lu] memfree  = [ element -> value_ptr [%p] ]\n", n_free++, root->value_ptr );

    if ( strcmp( "list_of_floats", root->base_type ) == 0
         || strcmp( "float4x4", root->base_type ) == 0 ) {

      double **ptr = ( double ** ) root->value_ptr;

      free( *ptr );
      ptr = NULL;
      root->value_ptr = NULL;
      root->value_size = 0;

    } else if ( strcmp( "list_of_uints", root->base_type ) == 0 ) {

      unsigned long **ptr = ( unsigned long ** ) root->value_ptr;

      free( *ptr );
      ptr = NULL;
      root->value_ptr = NULL;
      root->value_size = 0;
    }

  }



  if ( root->base_type != NULL ) {

    printf( "[%lu] memfree  = [ element -> base_type [%p] ]\n", n_free++, root->base_type );
    free( root->base_type );
    root->base_type = NULL;

  }




  if ( root->name != NULL ) {

    printf( "[%lu] memfree  = [ element -> name [%p] ]\n", n_free++,  root->name );
    free( root->name );
    root->name = NULL;

  }



  // delete itself

  root->parent = NULL;

  printf( "[%lu] memfree  = [ element root [%p] ]\n", n_free++, root );
  free( root );
  root = NULL;

}



element( collada ) *collada_func( parse )( const char *filename ) {
  XML_Parser p;
  FILE *f;
  long fsize;
  char *string;
  size_t i;
  /* init local */
  string = NULL;
  fsize = 0;
  f = NULL;
  element( collada ) *root = NULL;
  g_current_elem = NULL;

  /* read dae file */
  f = fopen( filename, "rb" );
  if ( !f ) {
    puts( "import edilecek dosya bulunamadi\n" );

    /* return NULL; */
  } else {
    fseek( f, 0, SEEK_END );
    fsize = ftell( f );
    fseek( f, 0, SEEK_SET ); //same as rewind(f);

    string = malloc( fsize + 1 );
    assert( string );
    if ( !fread( string, fsize, 1, f ) ) {
      puts( "dosya okunamadi\n" );
      fclose( f );
    } else {
      fclose( f );

      string[fsize] = 0;
      /* puts(string); */

      /* init globals */

      g_current_depth = 0;
      g_pending_references = NULL;
      g_n_pending_reference = 0;

      root = powergl_resize( NULL, sizeof( element( collada ) ) );
      g_current_elem = root;

      /* printf("\n-------------PARSING DOCUMENT\n"); */

      /* create parser and parse */
      p = XML_ParserCreate( NULL );
      assert( p );
      XML_UseParserAsHandlerArg( p );
      XML_SetElementHandler( p, elemstart, elemend );
      XML_SetCharacterDataHandler( p, chardata );

      if ( !XML_Parse( p, string, fsize, -1 ) ) {
        fprintf( stderr, "Parse error at line %lu:\n%s\n", XML_GetCurrentLineNumber( p ), XML_ErrorString( XML_GetErrorCode( p ) ) );
      } else {

        /* printf("\n\n\n\n"); */
        /* printf("\n-------------EXPORTING DOCUMENT\n"); */
        /* printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>"); */
        /* print_element(stdout,(complex_element*)g_collada,0); */

        /* export_dae_file("exported.dae"); */

        /* printf("\n\n\n\n"); */
        /* printf("\n-----------------RESOLVING REFERENCES\n"); */
        /* printf("pending refs = %lu",g_n_pending_reference); */
        int resolved = resolve_refs( ( complex_element * )root, 0 );

        /* printf("\nresolved refs = %d",resolved); */
        /* printf("\n\n\n\n"); */

      }

      /* cleaning */
      free( g_pending_references );
      g_pending_references = NULL;
      XML_ParserFree( p );
      p = NULL;
      free( string );
      string = NULL;

    }
  }
  return root;
}
