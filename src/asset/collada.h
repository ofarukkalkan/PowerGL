#ifndef _powergl_asset_collada_h
#define _powergl_asset_collada_h

#include <stddef.h>
#include <stdio.h>

/* MACROS */

#define collada_func(NAME)  \
  powergl_collada_func_ ## NAME

#define collada_elem(NAME)  \
  powergl_collada_elem_ ## NAME

#define decl_attrib(TYPE,NAME)  \
  collada_elem( TYPE ) a_ ## NAME

#define decl_child(TYPE)    \
  collada_elem( TYPE ) * c_ ## TYPE

#define decl_choice_child(TYPE) \
	collada_elem( TYPE ) *cc_ ## TYPE

#define decl_parent(TYPE)   \
  collada_elem( TYPE ) * p_ ## TYPE

#define decl_ref(TYPE)  \
  ptr_complex_element  r_ ## TYPE	;

#define decl_children(TYPE) \
  collada_elem( TYPE ) ** ch_ ## TYPE ; \
  size_t n_ ## TYPE

#define decl_base(TYPE) \
	TYPE _base;

#define decl_extend(TYPE)   \
  collada_elem( TYPE ) _ext

#define alias_element(NAME) \
  typedef struct collada_elem( NAME ## _t ) collada_elem( NAME )

#define alias_attrib(NAME)  \
  typedef struct collada_elem( NAME ## _t ) collada_elem( NAME )





typedef struct simple_element_t simple_element;
typedef struct complex_element_t complex_element;
typedef struct ptr_complex_element_t ptr_complex_element;

struct simple_element_t {
  char *name;
  char *base_type;
  void *parent;

  void *value_ptr;
};

struct complex_element_t {
  char *name;
  char *base_type;
  void *parent;

  void *value_ptr;
  size_t value_size; // bu da bazi yerlerde atanmamis

  size_t n_elem;
  size_t n_attrib;
  size_t n_ref;

  complex_element **elems;
  simple_element **attribs;
  ptr_complex_element **refs;

  complex_element ** **ch_container; // stores element ( TYPE ) **ch_xxx pointers
  size_t n_ch_container;
};

struct ptr_complex_element_t {
  complex_element *ptr;
  const char *src;
  char *ptr_type;

  void *parent;
};


/* COLLADA TYPEDEFS */


/* COLLADA CORE */

alias_element( collada );
alias_element( up_axis );
alias_element( unit );
alias_element( library_geometries );
alias_element( geometry );
alias_element( mesh );
alias_element( source );
alias_element( source_technique_common );
alias_element( float_array );
alias_element( int_array );
alias_element( accessor );
alias_element( param );
alias_element( p );
alias_element( vcount );
alias_element( polylist );
alias_element( triangles );
alias_element( vertices );
alias_element( library_cameras );
alias_element( camera );
alias_element( optics );
alias_element( optics_technique_common );
alias_element( perspective );
alias_element( orthographic );
alias_element( xmag );
alias_element( ymag );
alias_element( xfov );
alias_element( yfov );
alias_element( znear );
alias_element( zfar );
alias_element( aspect_ratio );
alias_element( library_nodes );
alias_element( library_lights );
alias_element( light );
alias_element( light_technique_common );
alias_element( directional );
alias_element( light_color );
alias_element( library_visual_scenes );
alias_element( visual_scene );
alias_element( node );
alias_element( instance_geometry );
alias_element( instance_camera );
alias_element( instance_node );
alias_element( lookat );
alias_element( matrix );
alias_element( rotate );
alias_element( scale );
alias_element( translate );
alias_element( scene );
alias_element( instance_visual_scene );
alias_element( instance_light );
alias_element( input_local_offset );
alias_element( input_local );


/* COLLADA FX */

alias_element( library_effects );
alias_element( library_materials );
alias_element( effect );
alias_element( profile_COMMON );
alias_element( technique_FX_COMMON );
alias_element( lambert );
alias_element( ambient );
alias_element( diffuse );
alias_element( fx_common_color_or_texture );
alias_element( profile_COMMON_color );
alias_element( material );
alias_element( instance_effect );
alias_element( instance_material );
alias_element( bind_material );
alias_element( material_technique_common );


alias_element( targetable_float );
alias_element( targetable_float3 );
alias_element( targetable_float4 );


/* COLLADA ELEMENT VALUE TYPES */

alias_attrib( float );
alias_attrib( int );
alias_attrib( uint );
alias_attrib( float3 );
alias_attrib( float4 );
alias_attrib( string );
alias_attrib( list_of_floats );
alias_attrib( list_of_ints );
alias_attrib( list_of_uints );
alias_attrib( float3x3 );
alias_attrib( float4x4 );
alias_attrib( version_enum );
alias_attrib( up_axis_enum );
alias_attrib( node_type_enum );



/* EXPORTED FUNCTIONS */

collada_elem( collada ) *collada_func( parse )( const char *filename );
void collada_func( export_dae_file )( complex_element *root, const char *file_name );
void collada_func( delete_complex_element )( complex_element *elemm, size_t depth );
void collada_func( print_element )( FILE *file, complex_element *elem, int depth );
void collada_func( print_attribute )( FILE *file, simple_element *elem );
void collada_func( print_elem_value )( FILE *file, complex_element *elem );

/* SIMPLE TYPES */

struct collada_elem( float_t ) {
  decl_base( simple_element );
  double value;
};

struct collada_elem( int_t ) {
  decl_base( simple_element );
  long int value;
};

struct collada_elem( uint_t ) {
  decl_base( simple_element );
  unsigned long value;
};

struct collada_elem( float3_t ) {
  decl_base( simple_element );
  double *value;
};

struct collada_elem( float4_t ) {
  decl_base( simple_element );
  double *value;
};

struct collada_elem( float3x3_t ) {
  decl_base( simple_element );
  double *value;
};

struct collada_elem( float4x4_t ) {
  decl_base( simple_element );
  double *value;
};

struct collada_elem( string_t ) {
  decl_base( simple_element );
  char *value;
};

struct collada_elem( list_of_floats_t ) {
  decl_base( simple_element );
  double *value;
};

struct collada_elem( list_of_ints_t ) {
  decl_base( simple_element );
  long int *value;
};

struct collada_elem( list_of_uints_t ) {
  decl_base( simple_element );
  unsigned long *value;
};

struct collada_elem( version_enum_t ) {
  decl_base( simple_element );
  enum { V_1_5_0 }  value;
};

struct collada_elem( up_axis_enum_t ) {
  decl_base( simple_element );
  enum { X_UP, Y_UP, Z_UP }  value;
};

struct collada_elem( node_type_enum_t ) {
  decl_base( simple_element );
  enum { JOINT, NODE }  value;
};



/* COMPLEX TYPES */



struct collada_elem( targetable_float_t ) {

  decl_base( complex_element );
  decl_extend( float );

  decl_attrib( string, sid );

};


struct collada_elem( targetable_float3_t ) {

  decl_base( complex_element );
  decl_extend( float3 );

  decl_attrib( string, sid );

};


struct collada_elem( targetable_float4_t ) {

  decl_base( complex_element );
  decl_extend( float4 );

  decl_attrib( string, sid );

};


struct collada_elem( bind_material_t ) {

  decl_base( complex_element );


  decl_parent( instance_geometry );

};


struct collada_elem( instance_material_t ) {

  decl_base( complex_element );

  decl_attrib( string, sid );
  decl_attrib( string, name );
  decl_attrib( string, symbol );
  decl_attrib( string, target );

  decl_ref( material );

  decl_parent( node );

};


struct collada_elem( instance_effect_t ) {

  decl_base( complex_element );

  decl_attrib( string, sid );
  decl_attrib( string, name );
  decl_attrib( string, url );

  decl_ref( effect );

  decl_parent( node );

};


struct collada_elem( instance_light_t ) {

  decl_base( complex_element );

  decl_attrib( string, sid );
  decl_attrib( string, name );
  decl_attrib( string, url );

  decl_ref( light );

  decl_parent( node );

};



struct collada_elem( profile_COMMON_color_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float4 );

  decl_parent( fx_common_color_or_texture );

};


struct collada_elem( fx_common_color_or_texture_t ) {

  decl_base( complex_element );

  decl_choice_child( profile_COMMON_color );

  decl_parent( diffuse );
  decl_parent( ambient );

};


struct collada_elem( diffuse_t ) {

  decl_base( complex_element );
  decl_extend( fx_common_color_or_texture );

  decl_parent( lambert );

};


struct collada_elem( ambient_t ) {

  decl_base( complex_element );
  decl_extend( fx_common_color_or_texture );

  decl_parent( lambert );

};


struct collada_elem( lambert_t ) {

  decl_base( complex_element );

  decl_choice_child( ambient );
  decl_choice_child( diffuse );

  decl_parent( technique_FX_COMMON );

};


struct collada_elem( technique_FX_COMMON_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, sid );

  decl_child( lambert );

  decl_parent( profile_COMMON );

};


struct collada_elem( profile_COMMON_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );

  decl_child( technique_FX_COMMON );

  decl_parent( effect );

};


struct collada_elem( effect_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( profile_COMMON );

  decl_parent( library_effects );

};


struct collada_elem( light_color_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float3 );

  decl_parent( directional );

};


struct collada_elem( directional_t ) {

  decl_base( complex_element );

  decl_child( light_color );

  decl_parent( light_technique_common );

};


struct collada_elem( light_technique_common_t ) {

  decl_base( complex_element );

  decl_choice_child( directional );

  decl_parent( light );

};


struct collada_elem( light_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_child( light_technique_common );

  decl_parent( library_lights );

};


struct collada_elem( library_effects_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( effect );

  decl_parent( collada );

};


struct collada_elem( library_materials_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( material );

  decl_parent( collada );

};


struct collada_elem( library_lights_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( light );

  decl_parent( collada );

};


struct collada_elem( input_local_t ) {

  decl_base( complex_element );

  decl_attrib( string, semantic );
  decl_attrib( string, source );

  decl_ref( source );

  decl_parent( vertices );

};


struct collada_elem( input_local_offset_t ) {

  decl_base( complex_element );

  decl_attrib( uint, set );
  decl_attrib( uint, offset );
  decl_attrib( string, semantic );
  decl_attrib( string, source );

  decl_ref( source );
  decl_ref( vertices );

  decl_parent( polylist );
  decl_parent( triangles );

};


struct collada_elem( vcount_t ) {

  decl_base( complex_element );
  decl_extend( list_of_uints );

  decl_parent( polylist );

};

struct collada_elem( p_t ) {

  decl_base( complex_element );
  decl_extend( list_of_uints );

  decl_parent( polylist );
  decl_parent( triangles );

};

struct collada_elem( float_array_t ) {

  decl_base( complex_element );
  decl_extend( list_of_floats );

  decl_attrib( string, id );
  decl_attrib( string, name );
  decl_attrib( uint, count );

  decl_parent( source );

};


struct collada_elem( int_array_t ) {

  decl_base( complex_element );
  decl_extend( list_of_ints );

  decl_attrib( string, id );
  decl_attrib( string, name );
  decl_attrib( uint, count );

  decl_parent( source );

};


struct collada_elem( param_t ) {

  decl_base( complex_element );

  decl_attrib( string, sid );
  decl_attrib( string, name );
  decl_attrib( string, type );
  decl_attrib( string, semantic );

  decl_parent( accessor );

};


struct collada_elem( accessor_t ) {

  decl_base( complex_element );

  decl_attrib( uint, count );
  decl_attrib( uint, offset );
  decl_attrib( uint, stride );
  decl_attrib( string, source );

  decl_children( param );

  decl_ref( float_array );
  decl_ref( int_array );

  decl_parent( source_technique_common );

};


struct collada_elem( source_technique_common_t ) {

  decl_base( complex_element );

  decl_child( accessor );

  decl_parent( source );

};


struct collada_elem( source_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_child( float_array );
  decl_child( int_array );
  decl_child( source_technique_common );

  decl_parent( mesh );

};


struct collada_elem( polylist_t ) {

  decl_base( complex_element );

  decl_attrib( string, name );
  decl_attrib( uint, count );

  decl_children( input_local_offset );
  decl_child( vcount );
  decl_child( p );

  decl_parent( mesh );

};

struct collada_elem( triangles_t ) {

  decl_base( complex_element );

  decl_attrib( string, name );
  decl_attrib( uint, count );

  decl_children( input_local_offset );
  decl_child( p );

  decl_parent( mesh );

};


struct collada_elem( vertices_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( input_local );

  decl_parent( mesh );

};


struct collada_elem( mesh_t ) {

  decl_base( complex_element );

  decl_children( source );
  decl_children( polylist );
  decl_children( triangles );
  decl_child( vertices );

  decl_parent( geometry );

};


struct collada_elem( znear_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float );
  decl_parent( perspective );
  decl_parent( orthographic );
};

struct collada_elem( zfar_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float );
  decl_parent( perspective );
  decl_parent( orthographic );
};

struct collada_elem( xmag_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float );
  decl_parent( orthographic );
};

struct collada_elem( ymag_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float );
  decl_parent( orthographic );
};

struct collada_elem( yfov_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float );
  decl_parent( perspective );
};

struct collada_elem( xfov_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float );
  decl_parent( perspective );
};

struct collada_elem( aspect_ratio_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float );
  decl_parent( perspective );
  decl_parent( orthographic );
};


struct collada_elem( orthographic_t ) {

  decl_base( complex_element );

  decl_choice_child( xmag );
  decl_choice_child( ymag );
  decl_child( aspect_ratio );
  decl_child( znear );
  decl_child( zfar );

  decl_parent( optics_technique_common );

};


struct collada_elem( perspective_t ) {

  decl_base( complex_element );

  decl_choice_child( xfov );
  decl_choice_child( yfov );
  decl_child( aspect_ratio );
  decl_child( znear );
  decl_child( zfar );

  decl_parent( optics_technique_common );

};


struct collada_elem( optics_technique_common_t ) {

  decl_base( complex_element );

  decl_choice_child( perspective );
  decl_choice_child( orthographic );

  decl_parent( optics );

};


struct collada_elem( optics_t ) {

  decl_base( complex_element );

  decl_child( optics_technique_common );

  decl_parent( camera );

};


struct collada_elem( camera_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_child( optics );

  decl_parent( library_cameras );

};


struct collada_elem( geometry_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_child( mesh );

  decl_parent( library_geometries );

};


struct collada_elem( lookat_t ) {

  decl_base( complex_element );
  decl_extend( float3x3 );

  decl_attrib( string, sid );

  decl_parent( node );

};


struct collada_elem( matrix_t ) {

  decl_base( complex_element );
  decl_extend( float4x4 );

  decl_attrib( string, sid );

  decl_parent( node );

};


struct collada_elem( rotate_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float4 );

  decl_attrib( string, sid );

  decl_parent( node );

};


struct collada_elem( scale_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float3 );

  decl_attrib( string, sid );

  decl_parent( node );

};


struct collada_elem( translate_t ) {

  decl_base( complex_element );
  decl_extend( targetable_float3 );

  decl_attrib( string, sid );

  decl_parent( node );

};


struct collada_elem( instance_camera_t ) {

  decl_base( complex_element );

  decl_attrib( string, sid );
  decl_attrib( string, name );
  decl_attrib( string, url );

  decl_ref( camera );

  decl_parent( node );

};


struct collada_elem( instance_geometry_t ) {

  decl_base( complex_element );

  decl_attrib( string, sid );
  decl_attrib( string, name );
  decl_attrib( string, url );

  decl_child( bind_material );

  decl_ref( geometry );

  decl_parent( node );

};


struct collada_elem( instance_node_t ) {

  decl_base( complex_element );

  decl_attrib( string, sid );
  decl_attrib( string, name );
  decl_attrib( string, url );

  decl_ref( node );

  decl_parent( node );


};


struct collada_elem( instance_visual_scene_t ) {

  decl_base( complex_element );

  decl_attrib( string, sid );
  decl_attrib( string, name );
  decl_attrib( string, url );

  decl_ref( visual_scene ) ;

  decl_parent( scene );

};


struct collada_elem( library_cameras_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( camera );

  decl_parent( collada );

};


struct collada_elem( library_geometries_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( geometry );

  decl_parent( collada );

};


struct collada_elem( library_visual_scenes_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( visual_scene );

  decl_parent( collada );

};


struct collada_elem( node_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );
  decl_attrib( string, sid );

  decl_children( matrix );
  decl_children( instance_camera );
  decl_children( instance_light );
  decl_children( instance_geometry );
  decl_children( instance_node );
  decl_children( node );


  decl_parent( node );
  decl_parent( visual_scene );

};


struct collada_elem( visual_scene_t ) {

  decl_base( complex_element );

  decl_attrib( string, id );
  decl_attrib( string, name );

  decl_children( node );

  decl_parent( library_visual_scenes );

};


struct collada_elem( scene_t ) {

  decl_base( complex_element );

  decl_child( instance_visual_scene );

  decl_parent( collada );

};


struct collada_elem( collada_t ) {

  decl_base( complex_element );

  decl_attrib( string, version );
  decl_attrib( string, xmlns );

  decl_children( library_geometries );
  decl_children( library_cameras );
  decl_children( library_lights );
  decl_children( library_materials );
  decl_children( library_visual_scenes );
  decl_child( scene );

};




/* UNDEF UNNECESSARY MACROS */

#undef decl_attrib
#undef decl_child
#undef decl_choice_child
#undef decl_paren
#undef decl_ref
#undef decl_children
#undef end_type
#undef decl_extend
#undef alias_element
#undef alias_attrib


#endif
