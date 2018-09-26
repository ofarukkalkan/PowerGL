#ifndef _powergl_asset_collada_h
#define _powergl_asset_collada_h

#include <stddef.h>
#include <stdio.h>


#define collada_type(NAME)											\
  powergl_collada_ ## NAME

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
  size_t value_size;

  size_t n_elem;
  size_t n_attrib;
  size_t n_ref;

  complex_element **elems;
  simple_element **attribs;
  ptr_complex_element **refs;

  complex_element ** **ch_container;
  size_t n_ch_container;
};

struct ptr_complex_element_t {
  complex_element *ptr;
  const char *src;
  char *ptr_type;

  void *parent;
};


typedef struct powergl_collada_collada_t powergl_collada_collada;
typedef struct powergl_collada_up_axis_t powergl_collada_up_axis;
typedef struct powergl_collada_unit_t powergl_collada_unit;
typedef struct powergl_collada_library_geometries_t powergl_collada_library_geometries;
typedef struct powergl_collada_geometry_t powergl_collada_geometry;
typedef struct powergl_collada_mesh_t powergl_collada_mesh;
typedef struct powergl_collada_source_t powergl_collada_source;
typedef struct powergl_collada_source_technique_common_t powergl_collada_source_technique_common;
typedef struct powergl_collada_float_array_t powergl_collada_float_array;
typedef struct powergl_collada_int_array_t powergl_collada_int_array;
typedef struct powergl_collada_accessor_t powergl_collada_accessor;
typedef struct powergl_collada_param_t powergl_collada_param;
typedef struct powergl_collada_p_t powergl_collada_p;
typedef struct powergl_collada_triangles_t powergl_collada_triangles;
typedef struct powergl_collada_vertices_t powergl_collada_vertices;
typedef struct powergl_collada_library_cameras_t powergl_collada_library_cameras;
typedef struct powergl_collada_camera_t powergl_collada_camera;
typedef struct powergl_collada_optics_t powergl_collada_optics;
typedef struct powergl_collada_optics_technique_common_t powergl_collada_optics_technique_common;
typedef struct powergl_collada_perspective_t powergl_collada_perspective;
typedef struct powergl_collada_orthographic_t powergl_collada_orthographic;
typedef struct powergl_collada_library_nodes_t powergl_collada_library_nodes;
typedef struct powergl_collada_library_lights_t powergl_collada_library_lights;
typedef struct powergl_collada_light_t powergl_collada_light;
typedef struct powergl_collada_light_technique_common_t powergl_collada_light_technique_common;
typedef struct powergl_collada_directional_t powergl_collada_directional;
typedef struct powergl_collada_library_visual_scenes_t powergl_collada_library_visual_scenes;
typedef struct powergl_collada_visual_scene_t powergl_collada_visual_scene;
typedef struct powergl_collada_node_t powergl_collada_node;
typedef struct powergl_collada_instance_geometry_t powergl_collada_instance_geometry;
typedef struct powergl_collada_instance_camera_t powergl_collada_instance_camera;
typedef struct powergl_collada_instance_node_t powergl_collada_instance_node;
typedef struct powergl_collada_lookat_t powergl_collada_lookat;
typedef struct powergl_collada_matrix_t powergl_collada_matrix;
typedef struct powergl_collada_rotate_t powergl_collada_rotate;
typedef struct powergl_collada_scale_t powergl_collada_scale;
typedef struct powergl_collada_translate_t powergl_collada_translate;
typedef struct powergl_collada_scene_t powergl_collada_scene;
typedef struct powergl_collada_instance_visual_scene_t powergl_collada_instance_visual_scene;
typedef struct powergl_collada_instance_light_t powergl_collada_instance_light;
typedef struct powergl_collada_input_local_offset_t powergl_collada_input_local_offset;
typedef struct powergl_collada_input_local_t powergl_collada_input_local;




typedef struct powergl_collada_library_effects_t powergl_collada_library_effects;
typedef struct powergl_collada_library_materials_t powergl_collada_library_materials;
typedef struct powergl_collada_effect_t powergl_collada_effect;
typedef struct powergl_collada_profile_COMMON_t powergl_collada_profile_COMMON;
typedef struct powergl_collada_technique_FX_COMMON_t powergl_collada_technique_FX_COMMON;
typedef struct powergl_collada_lambert_t powergl_collada_lambert;
typedef struct powergl_collada_fx_common_color_or_texture_t powergl_collada_fx_common_color_or_texture;
typedef struct powergl_collada_material_t powergl_collada_material;
typedef struct powergl_collada_instance_effect_t powergl_collada_instance_effect;
typedef struct powergl_collada_instance_material_t powergl_collada_instance_material;
typedef struct powergl_collada_bind_material_t powergl_collada_bind_material;
typedef struct powergl_collada_bind_material_technique_common_t powergl_collada_bind_material_technique_common;


typedef struct powergl_collada_targetable_float_t powergl_collada_targetable_float;
typedef struct powergl_collada_targetable_float3_t powergl_collada_targetable_float3;
typedef struct powergl_collada_targetable_float4_t powergl_collada_targetable_float4;




typedef struct powergl_collada_float_t powergl_collada_float;
typedef struct powergl_collada_int_t powergl_collada_int;
typedef struct powergl_collada_uint_t powergl_collada_uint;
typedef struct powergl_collada_float3_t powergl_collada_float3;
typedef struct powergl_collada_float4_t powergl_collada_float4;
typedef struct powergl_collada_string_t powergl_collada_string;
typedef struct powergl_collada_list_of_floats_t powergl_collada_list_of_floats;
typedef struct powergl_collada_list_of_ints_t powergl_collada_list_of_ints;
typedef struct powergl_collada_list_of_uints_t powergl_collada_list_of_uints;
typedef struct powergl_collada_float3x3_t powergl_collada_float3x3;
typedef struct powergl_collada_float4x4_t powergl_collada_float4x4;
typedef struct powergl_collada_version_enum_t powergl_collada_version_enum;
typedef struct powergl_collada_up_axis_enum_t powergl_collada_up_axis_enum;
typedef struct powergl_collada_node_type_enum_t powergl_collada_node_type_enum;





powergl_collada_collada *powergl_collada_parse( const char *filename );
void powergl_collada_export_dae_file( complex_element *root, const char *file_name );
void powergl_collada_delete_complex_element( complex_element *elemm, size_t depth );
void powergl_collada_print_element( FILE *file, complex_element *elem, int depth );
void powergl_collada_print_attribute( FILE *file, simple_element *elem );
void powergl_collada_print_elem_value( FILE *file, complex_element *elem );



struct powergl_collada_float_t {
  simple_element _base;
  double value;
};

struct powergl_collada_int_t {
  simple_element _base;
  long int value;
};

struct powergl_collada_uint_t {
  simple_element _base;
  unsigned long value;
};

struct powergl_collada_float3_t {
  simple_element _base;
  double *value;
};

struct powergl_collada_float4_t {
  simple_element _base;
  double *value;
};

struct powergl_collada_float3x3_t {
  simple_element _base;
  double *value;
};

struct powergl_collada_float4x4_t {
  simple_element _base;
  double *value;
};

struct powergl_collada_string_t {
  simple_element _base;
  char *value;
};

struct powergl_collada_list_of_floats_t {
  simple_element _base;
  double *value;
};

struct powergl_collada_list_of_ints_t {
  simple_element _base;
  long int *value;
};

struct powergl_collada_list_of_uints_t {
  simple_element _base;
  unsigned long *value;
};

struct powergl_collada_version_enum_t {
  simple_element _base;
  enum { V_1_5_0 } value;
};

struct powergl_collada_up_axis_enum_t {
  simple_element _base;
  enum { X_UP, Y_UP, Z_UP } value;
};

struct powergl_collada_node_type_enum_t {
  simple_element _base;
  enum { JOINT, NODE } value;
};







struct powergl_collada_targetable_float_t {

  complex_element _base;
  powergl_collada_float _ext;

  powergl_collada_string a_sid;

	powergl_collada_perspective *p_perspective;

};


struct powergl_collada_targetable_float3_t {

  complex_element _base;
  powergl_collada_float3 _ext;

  powergl_collada_string a_sid;

	powergl_collada_directional *p_directional;

};


struct powergl_collada_targetable_float4_t {

  complex_element _base;
  powergl_collada_float4 _ext;

  powergl_collada_string a_sid;

	powergl_collada_fx_common_color_or_texture *p_fx_common_color_or_texture;

};


struct powergl_collada_bind_material_technique_common_t {

  complex_element _base;

	powergl_collada_instance_material **ch_instance_material; size_t n_instance_material;

  powergl_collada_bind_material *p_bind_material;

};


struct powergl_collada_bind_material_t {

  complex_element _base;

	powergl_collada_bind_material_technique_common *c_bind_material_technique_common;

  powergl_collada_instance_geometry *p_instance_geometry;

};

struct powergl_collada_material_t {

  complex_element _base;

	powergl_collada_string a_id;
	powergl_collada_string a_name;

	powergl_collada_instance_effect *c_instance_effect;

  powergl_collada_library_materials *p_library_materials;

};


struct powergl_collada_instance_material_t {

  complex_element _base;

  powergl_collada_string a_sid;
  powergl_collada_string a_name;
  powergl_collada_string a_symbol;
  powergl_collada_string a_target;

  ptr_complex_element r_material;

  powergl_collada_bind_material_technique_common *p_bind_material_technique_common;

};


struct powergl_collada_instance_effect_t {

  complex_element _base;

  powergl_collada_string a_sid;
  powergl_collada_string a_name;
  powergl_collada_string a_url;

  ptr_complex_element r_effect;

  powergl_collada_material *p_material;

};


struct powergl_collada_instance_light_t {

  complex_element _base;

  powergl_collada_string a_sid;
  powergl_collada_string a_name;
  powergl_collada_string a_url;

  ptr_complex_element r_light;

  powergl_collada_node *p_node;

};


struct powergl_collada_fx_common_color_or_texture_t {

  complex_element _base;

  powergl_collada_targetable_float4 *cc_color;

  powergl_collada_lambert *p_lambert;

};

struct powergl_collada_lambert_t {

  complex_element _base;

  powergl_collada_fx_common_color_or_texture *cc_ambient;
  powergl_collada_fx_common_color_or_texture *cc_diffuse;

  powergl_collada_technique_FX_COMMON *p_technique_FX_COMMON;

};


struct powergl_collada_technique_FX_COMMON_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_sid;

  powergl_collada_lambert *c_lambert;

  powergl_collada_profile_COMMON *p_profile_COMMON;

};


struct powergl_collada_profile_COMMON_t {

  complex_element _base;

  powergl_collada_string a_id;

  powergl_collada_technique_FX_COMMON *c_technique_FX_COMMON;

  powergl_collada_effect *p_effect;

};


struct powergl_collada_effect_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_profile_COMMON **ch_profile_COMMON; size_t n_profile_COMMON;

  powergl_collada_library_effects *p_library_effects;

};


struct powergl_collada_directional_t {

  complex_element _base;

  powergl_collada_targetable_float3 *c_color;

  powergl_collada_light_technique_common *p_light_technique_common;

};


struct powergl_collada_light_technique_common_t {

  complex_element _base;

  powergl_collada_directional *cc_directional;

  powergl_collada_light *p_light;

};


struct powergl_collada_light_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_light_technique_common *c_light_technique_common;

  powergl_collada_library_lights *p_library_lights;

};


struct powergl_collada_library_effects_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_effect **ch_effect; size_t n_effect;

  powergl_collada_collada *p_collada;

};


struct powergl_collada_library_materials_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_material **ch_material; size_t n_material;

  powergl_collada_collada *p_collada;

};


struct powergl_collada_library_lights_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_light **ch_light; size_t n_light;

  powergl_collada_collada *p_collada;

};


struct powergl_collada_input_local_t {

  complex_element _base;

  powergl_collada_string a_semantic;
  powergl_collada_string a_source;

  ptr_complex_element r_source;

  powergl_collada_vertices *p_vertices;

};


struct powergl_collada_input_local_offset_t {

  complex_element _base;

  powergl_collada_uint a_set;
  powergl_collada_uint a_offset;
  powergl_collada_string a_semantic;
  powergl_collada_string a_source;

  ptr_complex_element r_source;
  ptr_complex_element r_vertices;

  powergl_collada_triangles *p_triangles;

};


struct powergl_collada_p_t {

  complex_element _base;
  powergl_collada_list_of_uints _ext;

  powergl_collada_triangles *p_triangles;

};

struct powergl_collada_float_array_t {

  complex_element _base;
  powergl_collada_list_of_floats _ext;

  powergl_collada_string a_id;
  powergl_collada_string a_name;
  powergl_collada_uint a_count;

  powergl_collada_source *p_source;

};


struct powergl_collada_int_array_t {

  complex_element _base;
  powergl_collada_list_of_ints _ext;

  powergl_collada_string a_id;
  powergl_collada_string a_name;
  powergl_collada_uint a_count;

  powergl_collada_source *p_source;

};


struct powergl_collada_param_t {

  complex_element _base;

  powergl_collada_string a_sid;
  powergl_collada_string a_name;
  powergl_collada_string a_type;
  powergl_collada_string a_semantic;

  powergl_collada_accessor *p_accessor;

};


struct powergl_collada_accessor_t {

  complex_element _base;

  powergl_collada_uint a_count;
  powergl_collada_uint a_offset;
  powergl_collada_uint a_stride;
  powergl_collada_string a_source;

  powergl_collada_param **ch_param; size_t n_param;

  ptr_complex_element r_float_array;
  ptr_complex_element r_int_array;

  powergl_collada_source_technique_common *p_source_technique_common;

};


struct powergl_collada_source_technique_common_t {

  complex_element _base;

  powergl_collada_accessor *c_accessor;

  powergl_collada_source *p_source;

};


struct powergl_collada_source_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_float_array *c_float_array;
  powergl_collada_int_array *c_int_array;
  powergl_collada_source_technique_common *c_source_technique_common;

  powergl_collada_mesh *p_mesh;

};


struct powergl_collada_triangles_t {

  complex_element _base;

  powergl_collada_string a_name;
  powergl_collada_uint a_count;

  powergl_collada_input_local_offset **ch_input_local_offset; size_t n_input_local_offset;
  powergl_collada_p *c_p;

  powergl_collada_mesh *p_mesh;

};


struct powergl_collada_vertices_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_input_local **ch_input_local; size_t n_input_local;

  powergl_collada_mesh *p_mesh;

};


struct powergl_collada_mesh_t {

  complex_element _base;

  powergl_collada_source **ch_source; size_t n_source;
  powergl_collada_triangles **ch_triangles; size_t n_triangles;
  powergl_collada_vertices *c_vertices;

  powergl_collada_geometry *p_geometry;

};

struct powergl_collada_orthographic_t {

  complex_element _base;

  powergl_collada_targetable_float *cc_xmag;
  powergl_collada_targetable_float *cc_ymag;
  powergl_collada_targetable_float *c_aspect_ratio;
  powergl_collada_targetable_float *c_znear;
  powergl_collada_targetable_float *c_zfar;

  powergl_collada_optics_technique_common *p_optics_technique_common;

};


struct powergl_collada_perspective_t {

  complex_element _base;

  powergl_collada_targetable_float *cc_xfov;
  powergl_collada_targetable_float *cc_yfov;
  powergl_collada_targetable_float *c_aspect_ratio;
  powergl_collada_targetable_float *c_znear;
  powergl_collada_targetable_float *c_zfar;

  powergl_collada_optics_technique_common *p_optics_technique_common;

};


struct powergl_collada_optics_technique_common_t {

  complex_element _base;

  powergl_collada_perspective *cc_perspective;
  powergl_collada_orthographic *cc_orthographic;

  powergl_collada_optics *p_optics;

};


struct powergl_collada_optics_t {

  complex_element _base;

  powergl_collada_optics_technique_common *c_optics_technique_common;

  powergl_collada_camera *p_camera;

};


struct powergl_collada_camera_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_optics *c_optics;

  powergl_collada_library_cameras *p_library_cameras;

};


struct powergl_collada_geometry_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_mesh *c_mesh;

  powergl_collada_library_geometries *p_library_geometries;

};


struct powergl_collada_lookat_t {

  complex_element _base;
  powergl_collada_float3x3 _ext;

  powergl_collada_string a_sid;

  powergl_collada_node *p_node;

};


struct powergl_collada_matrix_t {

  complex_element _base;
  powergl_collada_float4x4 _ext;

  powergl_collada_string a_sid;

  powergl_collada_node *p_node;

};


struct powergl_collada_rotate_t {

  complex_element _base;
  powergl_collada_targetable_float4 _ext;

  powergl_collada_string a_sid;

  powergl_collada_node *p_node;

};


struct powergl_collada_scale_t {

  complex_element _base;
  powergl_collada_targetable_float3 _ext;

  powergl_collada_string a_sid;

  powergl_collada_node *p_node;

};


struct powergl_collada_translate_t {

  complex_element _base;
  powergl_collada_targetable_float3 _ext;

  powergl_collada_string a_sid;

  powergl_collada_node *p_node;

};


struct powergl_collada_instance_camera_t {

  complex_element _base;

  powergl_collada_string a_sid;
  powergl_collada_string a_name;
  powergl_collada_string a_url;

  ptr_complex_element r_camera;

  powergl_collada_node *p_node;

};


struct powergl_collada_instance_geometry_t {

  complex_element _base;

  powergl_collada_string a_sid;
  powergl_collada_string a_name;
  powergl_collada_string a_url;

  powergl_collada_bind_material *c_bind_material;

  ptr_complex_element r_geometry;

  powergl_collada_node *p_node;

};


struct powergl_collada_instance_node_t {

  complex_element _base;

  powergl_collada_string a_sid;
  powergl_collada_string a_name;
  powergl_collada_string a_url;

  ptr_complex_element r_node;

  powergl_collada_node *p_node;


};


struct powergl_collada_instance_visual_scene_t {

  complex_element _base;

  powergl_collada_string a_sid;
  powergl_collada_string a_name;
  powergl_collada_string a_url;

  ptr_complex_element r_visual_scene ;

  powergl_collada_scene *p_scene;

};


struct powergl_collada_library_cameras_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_camera **ch_camera; size_t n_camera;

  powergl_collada_collada *p_collada;

};


struct powergl_collada_library_geometries_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_geometry **ch_geometry; size_t n_geometry;

  powergl_collada_collada *p_collada;

};


struct powergl_collada_library_visual_scenes_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_visual_scene **ch_visual_scene; size_t n_visual_scene;

  powergl_collada_collada *p_collada;

};


struct powergl_collada_node_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;
  powergl_collada_string a_sid;

  powergl_collada_matrix **ch_matrix; size_t n_matrix;
  powergl_collada_instance_camera **ch_instance_camera; size_t n_instance_camera;
  powergl_collada_instance_light **ch_instance_light; size_t n_instance_light;
  powergl_collada_instance_geometry **ch_instance_geometry; size_t n_instance_geometry;
  powergl_collada_instance_node **ch_instance_node; size_t n_instance_node;
  powergl_collada_node **ch_node; size_t n_node;


  powergl_collada_node *p_node;
  powergl_collada_visual_scene *p_visual_scene;

};


struct powergl_collada_visual_scene_t {

  complex_element _base;

  powergl_collada_string a_id;
  powergl_collada_string a_name;

  powergl_collada_node **ch_node; size_t n_node;

  powergl_collada_library_visual_scenes *p_library_visual_scenes;

};


struct powergl_collada_scene_t {

  complex_element _base;

  powergl_collada_instance_visual_scene *c_instance_visual_scene;

  powergl_collada_collada *p_collada;

};


struct powergl_collada_collada_t {

  complex_element _base;

  powergl_collada_string a_version;
  powergl_collada_string a_xmlns;

  powergl_collada_library_geometries **ch_library_geometries; size_t n_library_geometries;
  powergl_collada_library_cameras **ch_library_cameras; size_t n_library_cameras;
  powergl_collada_library_lights **ch_library_lights; size_t n_library_lights;
	powergl_collada_library_effects **ch_library_effects; size_t n_library_effects;
  powergl_collada_library_materials **ch_library_materials; size_t n_library_materials;
  powergl_collada_library_visual_scenes **ch_library_visual_scenes; size_t n_library_visual_scenes;
  powergl_collada_scene *c_scene;

};

#endif
