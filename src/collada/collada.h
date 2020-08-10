#ifndef _powergl_asset_collada_core_h
#define _powergl_asset_collada_core_h
#include "dom_connector.h"
typedef struct powergl_collada_core_COLLADA_t powergl_collada_core_COLLADA;
typedef struct powergl_collada_core_library_visual_scenes_t powergl_collada_core_library_visual_scenes;
typedef struct powergl_collada_core_library_cameras_t powergl_collada_core_library_cameras;
typedef struct powergl_collada_core_library_lights_t powergl_collada_core_library_lights;
typedef struct powergl_collada_core_library_geometries_t powergl_collada_core_library_geometries;
typedef struct powergl_collada_core_library_animations_t powergl_collada_core_library_animations;
typedef struct powergl_collada_core_scene_t powergl_collada_core_scene;
typedef struct powergl_collada_core_visual_scene_t powergl_collada_core_visual_scene;
typedef struct powergl_collada_core_animation_t powergl_collada_core_animation;
typedef struct powergl_collada_core_sampler_t powergl_collada_core_sampler;
typedef struct powergl_collada_core_channel_t powergl_collada_core_channel;
typedef struct powergl_collada_core_geometry_t powergl_collada_core_geometry;
typedef struct powergl_collada_core_mesh_t powergl_collada_core_mesh;
typedef struct powergl_collada_core_accessor_t powergl_collada_core_accessor;
typedef struct powergl_collada_core_param_t powergl_collada_core_param;
typedef struct powergl_collada_core_float_array_t powergl_collada_core_float_array;
typedef struct powergl_collada_core_Name_array_t powergl_collada_core_Name_array;
typedef struct powergl_collada_core_vertices_t powergl_collada_core_vertices;
typedef struct powergl_collada_core_triangles_t powergl_collada_core_triangles;
typedef struct powergl_collada_core_light_t powergl_collada_core_light;
typedef struct powergl_collada_core_directional_t powergl_collada_core_directional;
typedef struct powergl_collada_core_camera_t powergl_collada_core_camera;
typedef struct powergl_collada_core_optics_t powergl_collada_core_optics;
typedef struct powergl_collada_core_perspective_t powergl_collada_core_perspective;
typedef struct powergl_collada_core_node_t powergl_collada_core_node;
typedef struct powergl_collada_core_source_technique_common_t powergl_collada_core_source_technique_common;
typedef struct powergl_collada_core_light_technique_common_t powergl_collada_core_light_technique_common;
typedef struct powergl_collada_core_optics_technique_common_t powergl_collada_core_optics_technique_common;
typedef struct powergl_collada_core_InstanceWithExtra_t powergl_collada_core_InstanceWithExtra;
typedef struct powergl_collada_core_source_t powergl_collada_core_source;
typedef struct powergl_collada_core_input_local_offset_t powergl_collada_core_input_local_offset;
typedef struct powergl_collada_core_input_local_t powergl_collada_core_input_local;
typedef struct powergl_collada_core_ListOfUInts_t powergl_collada_core_ListOfUInts;
typedef struct powergl_collada_core_targetable_floats_t powergl_collada_core_targetable_floats;
typedef struct powergl_collada_core_targetable_float_t powergl_collada_core_targetable_float;
struct powergl_collada_core_COLLADA_t {
dom_connector dom;
char* c_version; size_t n_version;
char* c_xmlns; size_t n_xmlns;
powergl_collada_core_library_animations** c_library_animations; size_t n_library_animations;
powergl_collada_core_library_geometries** c_library_geometries; size_t n_library_geometries;
powergl_collada_core_library_cameras** c_library_cameras; size_t n_library_cameras;
powergl_collada_core_library_lights** c_library_lights; size_t n_library_lights;
powergl_collada_core_library_visual_scenes** c_library_visual_scenes; size_t n_library_visual_scenes;
powergl_collada_core_scene** c_scene; size_t n_scene;
};
struct powergl_collada_core_library_visual_scenes_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_visual_scene** c_visual_scene; size_t n_visual_scene;
};
struct powergl_collada_core_library_cameras_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_camera** c_camera; size_t n_camera;
};
struct powergl_collada_core_library_lights_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_light** c_light; size_t n_light;
};
struct powergl_collada_core_library_geometries_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_geometry** c_geometry; size_t n_geometry;
};
struct powergl_collada_core_library_animations_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_animation** c_animation; size_t n_animation;
};
struct powergl_collada_core_scene_t {
dom_connector dom;
powergl_collada_core_InstanceWithExtra** c_instance_visual_scene; size_t n_instance_visual_scene;
};
struct powergl_collada_core_visual_scene_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_node** c_node; size_t n_node;
};
struct powergl_collada_core_animation_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_source** c_source; size_t n_source;
powergl_collada_core_sampler** c_sampler; size_t n_sampler;
powergl_collada_core_channel** c_channel; size_t n_channel;
};
struct powergl_collada_core_sampler_t {
dom_connector dom;
char* c_id; size_t n_id;
powergl_collada_core_input_local** c_input; size_t n_input;
};
struct powergl_collada_core_channel_t {
dom_connector dom;
char* c_source; size_t n_source;
char* c_target; size_t n_target;
};
struct powergl_collada_core_geometry_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_mesh** c_mesh; size_t n_mesh;
};
struct powergl_collada_core_mesh_t {
dom_connector dom;
powergl_collada_core_source** c_source; size_t n_source;
powergl_collada_core_vertices** c_vertices; size_t n_vertices;
powergl_collada_core_triangles** c_triangles; size_t n_triangles;
};
struct powergl_collada_core_accessor_t {
dom_connector dom;
char* c_source; size_t n_source;
size_t c_count;
size_t c_offset;
size_t c_stride;
powergl_collada_core_param** c_param; size_t n_param;
powergl_collada_core_float_array* r_float_array;
powergl_collada_core_Name_array* r_Name_array;
};
struct powergl_collada_core_param_t {
dom_connector dom;
char* c_sid; size_t n_sid;
char* c_name; size_t n_name;
char* c_type; size_t n_type;
char* c_semantic; size_t n_semantic;
};
struct powergl_collada_core_float_array_t {
dom_connector dom;
double* content; size_t n_content;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
size_t c_count;
};
struct powergl_collada_core_Name_array_t {
dom_connector dom;
char** content; size_t n_content;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
size_t c_count;
};
struct powergl_collada_core_vertices_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_input_local** c_input; size_t n_input;
};
struct powergl_collada_core_triangles_t {
dom_connector dom;
char* c_name; size_t n_name;
size_t c_count;
powergl_collada_core_input_local_offset** c_input; size_t n_input;
powergl_collada_core_ListOfUInts** c_p; size_t n_p;
};
struct powergl_collada_core_light_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_light_technique_common** c_technique_common; size_t n_technique_common;
};
struct powergl_collada_core_directional_t {
dom_connector dom;
powergl_collada_core_targetable_floats** c_color; size_t n_color;
};
struct powergl_collada_core_camera_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_optics** c_optics; size_t n_optics;
};
struct powergl_collada_core_optics_t {
dom_connector dom;
powergl_collada_core_optics_technique_common** c_technique_common; size_t n_technique_common;
};
struct powergl_collada_core_perspective_t {
dom_connector dom;
powergl_collada_core_targetable_float** c_xfov; size_t n_xfov;
powergl_collada_core_targetable_float** c_yfov; size_t n_yfov;
powergl_collada_core_targetable_float** c_aspect_ratio; size_t n_aspect_ratio;
powergl_collada_core_targetable_float** c_znear; size_t n_znear;
powergl_collada_core_targetable_float** c_zfar; size_t n_zfar;
};
struct powergl_collada_core_node_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_sid; size_t n_sid;
char* c_name; size_t n_name;
powergl_collada_core_node** c_node; size_t n_node;
powergl_collada_core_targetable_floats** c_matrix; size_t n_matrix;
powergl_collada_core_targetable_floats** c_rotate; size_t n_rotate;
powergl_collada_core_targetable_floats** c_scale; size_t n_scale;
powergl_collada_core_targetable_floats** c_translate; size_t n_translate;
powergl_collada_core_InstanceWithExtra** c_instance_camera; size_t n_instance_camera;
powergl_collada_core_InstanceWithExtra** c_instance_light; size_t n_instance_light;
powergl_collada_core_InstanceWithExtra** c_instance_geometry; size_t n_instance_geometry;
};
struct powergl_collada_core_source_technique_common_t {
dom_connector dom;
powergl_collada_core_accessor** c_accessor; size_t n_accessor;
};
struct powergl_collada_core_light_technique_common_t {
dom_connector dom;
powergl_collada_core_directional** c_directional; size_t n_directional;
};
struct powergl_collada_core_optics_technique_common_t {
dom_connector dom;
powergl_collada_core_perspective** c_perspective; size_t n_perspective;
};
struct powergl_collada_core_InstanceWithExtra_t {
dom_connector dom;
char* c_sid; size_t n_sid;
char* c_name; size_t n_name;
char* c_url; size_t n_url;
powergl_collada_core_geometry* r_geometry;
powergl_collada_core_camera* r_camera;
powergl_collada_core_light* r_light;
powergl_collada_core_visual_scene* r_visual_scene;
};
struct powergl_collada_core_source_t {
dom_connector dom;
char* c_id; size_t n_id;
char* c_name; size_t n_name;
powergl_collada_core_float_array** c_float_array; size_t n_float_array;
powergl_collada_core_Name_array** c_Name_array; size_t n_Name_array;
powergl_collada_core_source_technique_common** c_technique_common; size_t n_technique_common;
};
struct powergl_collada_core_input_local_offset_t {
dom_connector dom;
char* c_semantic; size_t n_semantic;
char* c_source; size_t n_source;
size_t c_set;
size_t c_offset;
powergl_collada_core_source* r_mesh_source;
powergl_collada_core_vertices* r_vertices;
};
struct powergl_collada_core_input_local_t {
dom_connector dom;
char* c_semantic; size_t n_semantic;
char* c_source; size_t n_source;
powergl_collada_core_source* r_mesh_source;
powergl_collada_core_source* r_anim_source;
};
struct powergl_collada_core_ListOfUInts_t {
dom_connector dom;
size_t* content; size_t n_content;
};
struct powergl_collada_core_targetable_floats_t {
dom_connector dom;
double* content; size_t n_content;
char* c_sid; size_t n_sid;
};
struct powergl_collada_core_targetable_float_t {
dom_connector dom;
double* content; size_t n_content;
char* c_sid; size_t n_sid;
};
#endif