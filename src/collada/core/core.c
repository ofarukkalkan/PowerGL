#include "core.h"
static size_t g_n_supported_collada_core_types;
static supported_type g_supported_collada_core_types[59];
static int g_collara_core_is_init;

int powergl_collada_core_check_type(const char *ptr, const char *parent){
for(size_t i=0; i<g_n_supported_collada_core_types; i++){
if(strcmp(g_supported_collada_core_types[i].name, ptr) == 0 && strcmp(g_supported_collada_core_types[i].parent, parent) == 0 ){
return i;
}
}
return -1;
}
void* powergl_collada_core_get_instance(const char *ptr, const char *parent){
int index = powergl_collada_core_check_type(ptr, parent);
if( index > -1 ) return g_supported_collada_core_types[index].get_instance();
else return NULL;
}
void set_ref_collada_core_COLLADA(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_COLLADA(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_COLLADA(void *obj, size_t index, const char *value){
powergl_collada_core_COLLADA *ptr = (powergl_collada_core_COLLADA*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_version = strlen(value) + 1;
ptr->c_version = powergl_resize(NULL, ptr->n_version, sizeof(char));
strcpy(ptr->c_version, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_xmlns = strlen(value) + 1;
ptr->c_xmlns = powergl_resize(NULL, ptr->n_xmlns, sizeof(char));
strcpy(ptr->c_xmlns, value);
break;
}
}
void add_child_collada_core_COLLADA(void *obj, size_t index, dom_connector *child){
powergl_collada_core_COLLADA *ptr = (powergl_collada_core_COLLADA*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_library_animations = powergl_resize(ptr->c_library_animations, ++ptr->n_library_animations, sizeof(powergl_collada_core_library_animations*));
ptr->c_library_animations[ptr->n_library_animations-1] = (powergl_collada_core_library_animations*)child;
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_library_geometries = powergl_resize(ptr->c_library_geometries, ++ptr->n_library_geometries, sizeof(powergl_collada_core_library_geometries*));
ptr->c_library_geometries[ptr->n_library_geometries-1] = (powergl_collada_core_library_geometries*)child;
break;
case 4: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_library_cameras = powergl_resize(ptr->c_library_cameras, ++ptr->n_library_cameras, sizeof(powergl_collada_core_library_cameras*));
ptr->c_library_cameras[ptr->n_library_cameras-1] = (powergl_collada_core_library_cameras*)child;
break;
case 5: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_library_lights = powergl_resize(ptr->c_library_lights, ++ptr->n_library_lights, sizeof(powergl_collada_core_library_lights*));
ptr->c_library_lights[ptr->n_library_lights-1] = (powergl_collada_core_library_lights*)child;
break;
case 6: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_library_visual_scenes = powergl_resize(ptr->c_library_visual_scenes, ++ptr->n_library_visual_scenes, sizeof(powergl_collada_core_library_visual_scenes*));
ptr->c_library_visual_scenes[ptr->n_library_visual_scenes-1] = (powergl_collada_core_library_visual_scenes*)child;
break;
case 7: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_scene = powergl_resize(ptr->c_scene, ++ptr->n_scene, sizeof(powergl_collada_core_scene*));
ptr->c_scene[ptr->n_scene-1] = (powergl_collada_core_scene*)child;
break;
}
}
void* new_collada_core_COLLADA(void){
powergl_collada_core_COLLADA *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_COLLADA));
ptr->c_version = NULL; ptr->n_version = 0;
ptr->c_xmlns = NULL; ptr->n_xmlns = 0;
ptr->c_library_animations = NULL; ptr->n_library_animations = 0;
ptr->c_library_geometries = NULL; ptr->n_library_geometries = 0;
ptr->c_library_cameras = NULL; ptr->n_library_cameras = 0;
ptr->c_library_lights = NULL; ptr->n_library_lights = 0;
ptr->c_library_visual_scenes = NULL; ptr->n_library_visual_scenes = 0;
ptr->c_scene = NULL; ptr->n_scene = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[0].map;
ptr->dom.n_map = g_supported_collada_core_types[0].n_map;
ptr->dom.add_child = add_child_collada_core_COLLADA;
ptr->dom.set_ref = set_ref_collada_core_COLLADA;
ptr->dom.parse_attrib = parse_attrib_collada_core_COLLADA;
ptr->dom.parse_content = parse_content_collada_core_COLLADA;
return ptr;
}
void set_ref_collada_core_library_visual_scenes(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_visual_scenes(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_visual_scenes(void *obj, size_t index, const char *value){
powergl_collada_core_library_visual_scenes *ptr = (powergl_collada_core_library_visual_scenes*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_library_visual_scenes(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_visual_scenes *ptr = (powergl_collada_core_library_visual_scenes*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_visual_scene = powergl_resize(ptr->c_visual_scene, ++ptr->n_visual_scene, sizeof(powergl_collada_core_visual_scene*));
ptr->c_visual_scene[ptr->n_visual_scene-1] = (powergl_collada_core_visual_scene*)child;
break;
}
}
void* new_collada_core_library_visual_scenes(void){
powergl_collada_core_library_visual_scenes *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_visual_scenes));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_visual_scene = NULL; ptr->n_visual_scene = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[1].map;
ptr->dom.n_map = g_supported_collada_core_types[1].n_map;
ptr->dom.add_child = add_child_collada_core_library_visual_scenes;
ptr->dom.set_ref = set_ref_collada_core_library_visual_scenes;
ptr->dom.parse_attrib = parse_attrib_collada_core_library_visual_scenes;
ptr->dom.parse_content = parse_content_collada_core_library_visual_scenes;
return ptr;
}
void set_ref_collada_core_library_cameras(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_cameras(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_cameras(void *obj, size_t index, const char *value){
powergl_collada_core_library_cameras *ptr = (powergl_collada_core_library_cameras*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_library_cameras(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_cameras *ptr = (powergl_collada_core_library_cameras*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_camera = powergl_resize(ptr->c_camera, ++ptr->n_camera, sizeof(powergl_collada_core_camera*));
ptr->c_camera[ptr->n_camera-1] = (powergl_collada_core_camera*)child;
break;
}
}
void* new_collada_core_library_cameras(void){
powergl_collada_core_library_cameras *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_cameras));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_camera = NULL; ptr->n_camera = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[2].map;
ptr->dom.n_map = g_supported_collada_core_types[2].n_map;
ptr->dom.add_child = add_child_collada_core_library_cameras;
ptr->dom.set_ref = set_ref_collada_core_library_cameras;
ptr->dom.parse_attrib = parse_attrib_collada_core_library_cameras;
ptr->dom.parse_content = parse_content_collada_core_library_cameras;
return ptr;
}
void set_ref_collada_core_library_lights(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_lights(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_lights(void *obj, size_t index, const char *value){
powergl_collada_core_library_lights *ptr = (powergl_collada_core_library_lights*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_library_lights(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_lights *ptr = (powergl_collada_core_library_lights*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_light = powergl_resize(ptr->c_light, ++ptr->n_light, sizeof(powergl_collada_core_light*));
ptr->c_light[ptr->n_light-1] = (powergl_collada_core_light*)child;
break;
}
}
void* new_collada_core_library_lights(void){
powergl_collada_core_library_lights *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_lights));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_light = NULL; ptr->n_light = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[3].map;
ptr->dom.n_map = g_supported_collada_core_types[3].n_map;
ptr->dom.add_child = add_child_collada_core_library_lights;
ptr->dom.set_ref = set_ref_collada_core_library_lights;
ptr->dom.parse_attrib = parse_attrib_collada_core_library_lights;
ptr->dom.parse_content = parse_content_collada_core_library_lights;
return ptr;
}
void set_ref_collada_core_library_geometries(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_geometries(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_geometries(void *obj, size_t index, const char *value){
powergl_collada_core_library_geometries *ptr = (powergl_collada_core_library_geometries*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_library_geometries(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_geometries *ptr = (powergl_collada_core_library_geometries*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_geometry = powergl_resize(ptr->c_geometry, ++ptr->n_geometry, sizeof(powergl_collada_core_geometry*));
ptr->c_geometry[ptr->n_geometry-1] = (powergl_collada_core_geometry*)child;
break;
}
}
void* new_collada_core_library_geometries(void){
powergl_collada_core_library_geometries *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_geometries));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_geometry = NULL; ptr->n_geometry = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[4].map;
ptr->dom.n_map = g_supported_collada_core_types[4].n_map;
ptr->dom.add_child = add_child_collada_core_library_geometries;
ptr->dom.set_ref = set_ref_collada_core_library_geometries;
ptr->dom.parse_attrib = parse_attrib_collada_core_library_geometries;
ptr->dom.parse_content = parse_content_collada_core_library_geometries;
return ptr;
}
void set_ref_collada_core_library_animations(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_animations(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_animations(void *obj, size_t index, const char *value){
powergl_collada_core_library_animations *ptr = (powergl_collada_core_library_animations*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_library_animations(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_animations *ptr = (powergl_collada_core_library_animations*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_animation = powergl_resize(ptr->c_animation, ++ptr->n_animation, sizeof(powergl_collada_core_animation*));
ptr->c_animation[ptr->n_animation-1] = (powergl_collada_core_animation*)child;
break;
}
}
void* new_collada_core_library_animations(void){
powergl_collada_core_library_animations *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_animations));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_animation = NULL; ptr->n_animation = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[5].map;
ptr->dom.n_map = g_supported_collada_core_types[5].n_map;
ptr->dom.add_child = add_child_collada_core_library_animations;
ptr->dom.set_ref = set_ref_collada_core_library_animations;
ptr->dom.parse_attrib = parse_attrib_collada_core_library_animations;
ptr->dom.parse_content = parse_content_collada_core_library_animations;
return ptr;
}
void set_ref_collada_core_scene(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_scene(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_scene(void *obj, size_t index, const char *value){
}
void add_child_collada_core_scene(void *obj, size_t index, dom_connector *child){
powergl_collada_core_scene *ptr = (powergl_collada_core_scene*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_instance_visual_scene = powergl_resize(ptr->c_instance_visual_scene, ++ptr->n_instance_visual_scene, sizeof(powergl_collada_core_InstanceWithExtra*));
ptr->c_instance_visual_scene[ptr->n_instance_visual_scene-1] = (powergl_collada_core_InstanceWithExtra*)child;
break;
}
}
void* new_collada_core_scene(void){
powergl_collada_core_scene *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_scene));
ptr->c_instance_visual_scene = NULL; ptr->n_instance_visual_scene = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[6].map;
ptr->dom.n_map = g_supported_collada_core_types[6].n_map;
ptr->dom.add_child = add_child_collada_core_scene;
ptr->dom.set_ref = set_ref_collada_core_scene;
ptr->dom.parse_attrib = parse_attrib_collada_core_scene;
ptr->dom.parse_content = parse_content_collada_core_scene;
return ptr;
}
void set_ref_collada_core_visual_scene(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_visual_scene(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_visual_scene(void *obj, size_t index, const char *value){
powergl_collada_core_visual_scene *ptr = (powergl_collada_core_visual_scene*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_visual_scene(void *obj, size_t index, dom_connector *child){
powergl_collada_core_visual_scene *ptr = (powergl_collada_core_visual_scene*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_node = powergl_resize(ptr->c_node, ++ptr->n_node, sizeof(powergl_collada_core_node*));
ptr->c_node[ptr->n_node-1] = (powergl_collada_core_node*)child;
break;
}
}
void* new_collada_core_visual_scene(void){
powergl_collada_core_visual_scene *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_visual_scene));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_node = NULL; ptr->n_node = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[7].map;
ptr->dom.n_map = g_supported_collada_core_types[7].n_map;
ptr->dom.add_child = add_child_collada_core_visual_scene;
ptr->dom.set_ref = set_ref_collada_core_visual_scene;
ptr->dom.parse_attrib = parse_attrib_collada_core_visual_scene;
ptr->dom.parse_content = parse_content_collada_core_visual_scene;
return ptr;
}
void set_ref_collada_core_animation(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_animation(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_animation(void *obj, size_t index, const char *value){
powergl_collada_core_animation *ptr = (powergl_collada_core_animation*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_animation(void *obj, size_t index, dom_connector *child){
powergl_collada_core_animation *ptr = (powergl_collada_core_animation*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_source = powergl_resize(ptr->c_source, ++ptr->n_source, sizeof(powergl_collada_core_source*));
ptr->c_source[ptr->n_source-1] = (powergl_collada_core_source*)child;
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_sampler = powergl_resize(ptr->c_sampler, ++ptr->n_sampler, sizeof(powergl_collada_core_sampler*));
ptr->c_sampler[ptr->n_sampler-1] = (powergl_collada_core_sampler*)child;
break;
case 4: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_channel = powergl_resize(ptr->c_channel, ++ptr->n_channel, sizeof(powergl_collada_core_channel*));
ptr->c_channel[ptr->n_channel-1] = (powergl_collada_core_channel*)child;
break;
}
}
void* new_collada_core_animation(void){
powergl_collada_core_animation *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_animation));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_source = NULL; ptr->n_source = 0;
ptr->c_sampler = NULL; ptr->n_sampler = 0;
ptr->c_channel = NULL; ptr->n_channel = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[8].map;
ptr->dom.n_map = g_supported_collada_core_types[8].n_map;
ptr->dom.add_child = add_child_collada_core_animation;
ptr->dom.set_ref = set_ref_collada_core_animation;
ptr->dom.parse_attrib = parse_attrib_collada_core_animation;
ptr->dom.parse_content = parse_content_collada_core_animation;
return ptr;
}
void set_ref_collada_core_sampler(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_sampler(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_sampler(void *obj, size_t index, const char *value){
powergl_collada_core_sampler *ptr = (powergl_collada_core_sampler*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
}
}
void add_child_collada_core_sampler(void *obj, size_t index, dom_connector *child){
powergl_collada_core_sampler *ptr = (powergl_collada_core_sampler*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_input = powergl_resize(ptr->c_input, ++ptr->n_input, sizeof(powergl_collada_core_input_local*));
ptr->c_input[ptr->n_input-1] = (powergl_collada_core_input_local*)child;
break;
}
}
void* new_collada_core_sampler(void){
powergl_collada_core_sampler *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_sampler));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_input = NULL; ptr->n_input = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[9].map;
ptr->dom.n_map = g_supported_collada_core_types[9].n_map;
ptr->dom.add_child = add_child_collada_core_sampler;
ptr->dom.set_ref = set_ref_collada_core_sampler;
ptr->dom.parse_attrib = parse_attrib_collada_core_sampler;
ptr->dom.parse_content = parse_content_collada_core_sampler;
return ptr;
}
void set_ref_collada_core_channel(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_channel(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_channel(void *obj, size_t index, const char *value){
powergl_collada_core_channel *ptr = (powergl_collada_core_channel*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_source = strlen(value) + 1;
ptr->c_source = powergl_resize(NULL, ptr->n_source, sizeof(char));
strcpy(ptr->c_source, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_target = strlen(value) + 1;
ptr->c_target = powergl_resize(NULL, ptr->n_target, sizeof(char));
strcpy(ptr->c_target, value);
break;
}
}
void add_child_collada_core_channel(void *obj, size_t index, dom_connector *child){
powergl_collada_core_channel *ptr = (powergl_collada_core_channel*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_channel(void){
powergl_collada_core_channel *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_channel));
ptr->c_source = NULL; ptr->n_source = 0;
ptr->c_target = NULL; ptr->n_target = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[10].map;
ptr->dom.n_map = g_supported_collada_core_types[10].n_map;
ptr->dom.add_child = add_child_collada_core_channel;
ptr->dom.set_ref = set_ref_collada_core_channel;
ptr->dom.parse_attrib = parse_attrib_collada_core_channel;
ptr->dom.parse_content = parse_content_collada_core_channel;
return ptr;
}
void set_ref_collada_core_geometry(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_geometry(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_geometry(void *obj, size_t index, const char *value){
powergl_collada_core_geometry *ptr = (powergl_collada_core_geometry*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_geometry(void *obj, size_t index, dom_connector *child){
powergl_collada_core_geometry *ptr = (powergl_collada_core_geometry*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_mesh = powergl_resize(ptr->c_mesh, ++ptr->n_mesh, sizeof(powergl_collada_core_mesh*));
ptr->c_mesh[ptr->n_mesh-1] = (powergl_collada_core_mesh*)child;
break;
}
}
void* new_collada_core_geometry(void){
powergl_collada_core_geometry *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_geometry));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_mesh = NULL; ptr->n_mesh = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[11].map;
ptr->dom.n_map = g_supported_collada_core_types[11].n_map;
ptr->dom.add_child = add_child_collada_core_geometry;
ptr->dom.set_ref = set_ref_collada_core_geometry;
ptr->dom.parse_attrib = parse_attrib_collada_core_geometry;
ptr->dom.parse_content = parse_content_collada_core_geometry;
return ptr;
}
void set_ref_collada_core_mesh(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_mesh(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_mesh(void *obj, size_t index, const char *value){
}
void add_child_collada_core_mesh(void *obj, size_t index, dom_connector *child){
powergl_collada_core_mesh *ptr = (powergl_collada_core_mesh*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_source = powergl_resize(ptr->c_source, ++ptr->n_source, sizeof(powergl_collada_core_source*));
ptr->c_source[ptr->n_source-1] = (powergl_collada_core_source*)child;
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_vertices = powergl_resize(ptr->c_vertices, ++ptr->n_vertices, sizeof(powergl_collada_core_vertices*));
ptr->c_vertices[ptr->n_vertices-1] = (powergl_collada_core_vertices*)child;
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_triangles = powergl_resize(ptr->c_triangles, ++ptr->n_triangles, sizeof(powergl_collada_core_triangles*));
ptr->c_triangles[ptr->n_triangles-1] = (powergl_collada_core_triangles*)child;
break;
}
}
void* new_collada_core_mesh(void){
powergl_collada_core_mesh *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_mesh));
ptr->c_source = NULL; ptr->n_source = 0;
ptr->c_vertices = NULL; ptr->n_vertices = 0;
ptr->c_triangles = NULL; ptr->n_triangles = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[12].map;
ptr->dom.n_map = g_supported_collada_core_types[12].n_map;
ptr->dom.add_child = add_child_collada_core_mesh;
ptr->dom.set_ref = set_ref_collada_core_mesh;
ptr->dom.parse_attrib = parse_attrib_collada_core_mesh;
ptr->dom.parse_content = parse_content_collada_core_mesh;
return ptr;
}
void set_ref_collada_core_accessor(void *obj, size_t index, dom_connector *ptr){
powergl_collada_core_accessor *ptr = (powergl_collada_core_accessor*)obj;
switch(index){
case 5: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_float_array = (powergl_collada_core_float_array*)ptr;
break;
case 6: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_Name_array = (powergl_collada_core_Name_array*)ptr;
break;
}
}
void parse_content_collada_core_accessor(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_accessor(void *obj, size_t index, const char *value){
powergl_collada_core_accessor *ptr = (powergl_collada_core_accessor*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_source = strlen(value) + 1;
ptr->c_source = powergl_resize(NULL, ptr->n_source, sizeof(char));
strcpy(ptr->c_source, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->c_count = strtoul( value, NULL, 10 );
break;
case 2: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->c_offset = strtoul( value, NULL, 10 );
break;
case 3: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->c_stride = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_accessor(void *obj, size_t index, dom_connector *child){
powergl_collada_core_accessor *ptr = (powergl_collada_core_accessor*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 4: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_param = powergl_resize(ptr->c_param, ++ptr->n_param, sizeof(powergl_collada_core_param*));
ptr->c_param[ptr->n_param-1] = (powergl_collada_core_param*)child;
break;
case 5: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 6: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_accessor(void){
powergl_collada_core_accessor *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_accessor));
ptr->c_source = NULL; ptr->n_source = 0;
ptr->c_count = 0;
ptr->c_offset = 0;
ptr->c_stride = 0;
ptr->c_param = NULL; ptr->n_param = 0;
ptr->r_float_array = NULL;
ptr->r_Name_array = NULL;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[13].map;
ptr->dom.n_map = g_supported_collada_core_types[13].n_map;
ptr->dom.add_child = add_child_collada_core_accessor;
ptr->dom.set_ref = set_ref_collada_core_accessor;
ptr->dom.parse_attrib = parse_attrib_collada_core_accessor;
ptr->dom.parse_content = parse_content_collada_core_accessor;
return ptr;
}
void set_ref_collada_core_param(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_param(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_param(void *obj, size_t index, const char *value){
powergl_collada_core_param *ptr = (powergl_collada_core_param*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_sid = strlen(value) + 1;
ptr->c_sid = powergl_resize(NULL, ptr->n_sid, sizeof(char));
strcpy(ptr->c_sid, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
case 2: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_type = strlen(value) + 1;
ptr->c_type = powergl_resize(NULL, ptr->n_type, sizeof(char));
strcpy(ptr->c_type, value);
break;
case 3: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_semantic = strlen(value) + 1;
ptr->c_semantic = powergl_resize(NULL, ptr->n_semantic, sizeof(char));
strcpy(ptr->c_semantic, value);
break;
}
}
void add_child_collada_core_param(void *obj, size_t index, dom_connector *child){
powergl_collada_core_param *ptr = (powergl_collada_core_param*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_param(void){
powergl_collada_core_param *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_param));
ptr->c_sid = NULL; ptr->n_sid = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_type = NULL; ptr->n_type = 0;
ptr->c_semantic = NULL; ptr->n_semantic = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[14].map;
ptr->dom.n_map = g_supported_collada_core_types[14].n_map;
ptr->dom.add_child = add_child_collada_core_param;
ptr->dom.set_ref = set_ref_collada_core_param;
ptr->dom.parse_attrib = parse_attrib_collada_core_param;
ptr->dom.parse_content = parse_content_collada_core_param;
return ptr;
}
void set_ref_collada_core_float_array(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_float_array(void *obj, size_t index, const char *value){
powergl_collada_core_float_array *ptr = (powergl_collada_core_float_array*)obj;
switch(index){
case 0: powergl_collada_parse_content(ptr->dom.nodes, index, value);
ptr->content  = powergl_collada_parse_floats(value, &ptr->n_content);
break;
}
}
void parse_attrib_collada_core_float_array(void *obj, size_t index, const char *value){
powergl_collada_core_float_array *ptr = (powergl_collada_core_float_array*)obj;
switch(index){
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 2: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
case 3: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->c_count = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_float_array(void *obj, size_t index, dom_connector *child){
powergl_collada_core_float_array *ptr = (powergl_collada_core_float_array*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_float_array(void){
powergl_collada_core_float_array *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_float_array));
ptr->content = NULL; ptr->n_content = 0;
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_count = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[15].map;
ptr->dom.n_map = g_supported_collada_core_types[15].n_map;
ptr->dom.add_child = add_child_collada_core_float_array;
ptr->dom.set_ref = set_ref_collada_core_float_array;
ptr->dom.parse_attrib = parse_attrib_collada_core_float_array;
ptr->dom.parse_content = parse_content_collada_core_float_array;
return ptr;
}
void set_ref_collada_core_Name_array(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_Name_array(void *obj, size_t index, const char *value){
powergl_collada_core_Name_array *ptr = (powergl_collada_core_Name_array*)obj;
switch(index){
case 0: powergl_collada_parse_content(ptr->dom.nodes, index, value);
ptr->content  = powergl_collada_parse_names(value, &ptr->n_content);
break;
}
}
void parse_attrib_collada_core_Name_array(void *obj, size_t index, const char *value){
powergl_collada_core_Name_array *ptr = (powergl_collada_core_Name_array*)obj;
switch(index){
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 2: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
case 3: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->c_count = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_Name_array(void *obj, size_t index, dom_connector *child){
powergl_collada_core_Name_array *ptr = (powergl_collada_core_Name_array*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_Name_array(void){
powergl_collada_core_Name_array *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_Name_array));
ptr->content = NULL; ptr->n_content = 0;
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_count = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[16].map;
ptr->dom.n_map = g_supported_collada_core_types[16].n_map;
ptr->dom.add_child = add_child_collada_core_Name_array;
ptr->dom.set_ref = set_ref_collada_core_Name_array;
ptr->dom.parse_attrib = parse_attrib_collada_core_Name_array;
ptr->dom.parse_content = parse_content_collada_core_Name_array;
return ptr;
}
void set_ref_collada_core_vertices(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_vertices(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_vertices(void *obj, size_t index, const char *value){
powergl_collada_core_vertices *ptr = (powergl_collada_core_vertices*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_vertices(void *obj, size_t index, dom_connector *child){
powergl_collada_core_vertices *ptr = (powergl_collada_core_vertices*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_input = powergl_resize(ptr->c_input, ++ptr->n_input, sizeof(powergl_collada_core_input_local*));
ptr->c_input[ptr->n_input-1] = (powergl_collada_core_input_local*)child;
break;
}
}
void* new_collada_core_vertices(void){
powergl_collada_core_vertices *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_vertices));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_input = NULL; ptr->n_input = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[17].map;
ptr->dom.n_map = g_supported_collada_core_types[17].n_map;
ptr->dom.add_child = add_child_collada_core_vertices;
ptr->dom.set_ref = set_ref_collada_core_vertices;
ptr->dom.parse_attrib = parse_attrib_collada_core_vertices;
ptr->dom.parse_content = parse_content_collada_core_vertices;
return ptr;
}
void set_ref_collada_core_triangles(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_triangles(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_triangles(void *obj, size_t index, const char *value){
powergl_collada_core_triangles *ptr = (powergl_collada_core_triangles*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->c_count = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_triangles(void *obj, size_t index, dom_connector *child){
powergl_collada_core_triangles *ptr = (powergl_collada_core_triangles*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_input = powergl_resize(ptr->c_input, ++ptr->n_input, sizeof(powergl_collada_core_input_local_offset*));
ptr->c_input[ptr->n_input-1] = (powergl_collada_core_input_local_offset*)child;
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_p = powergl_resize(ptr->c_p, ++ptr->n_p, sizeof(powergl_collada_core_ListOfUInts*));
ptr->c_p[ptr->n_p-1] = (powergl_collada_core_ListOfUInts*)child;
break;
}
}
void* new_collada_core_triangles(void){
powergl_collada_core_triangles *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_triangles));
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_count = 0;
ptr->c_input = NULL; ptr->n_input = 0;
ptr->c_p = NULL; ptr->n_p = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[18].map;
ptr->dom.n_map = g_supported_collada_core_types[18].n_map;
ptr->dom.add_child = add_child_collada_core_triangles;
ptr->dom.set_ref = set_ref_collada_core_triangles;
ptr->dom.parse_attrib = parse_attrib_collada_core_triangles;
ptr->dom.parse_content = parse_content_collada_core_triangles;
return ptr;
}
void set_ref_collada_core_light(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_light(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_light(void *obj, size_t index, const char *value){
powergl_collada_core_light *ptr = (powergl_collada_core_light*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_light(void *obj, size_t index, dom_connector *child){
powergl_collada_core_light *ptr = (powergl_collada_core_light*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_technique_common = powergl_resize(ptr->c_technique_common, ++ptr->n_technique_common, sizeof(powergl_collada_core_light_technique_common*));
ptr->c_technique_common[ptr->n_technique_common-1] = (powergl_collada_core_light_technique_common*)child;
break;
}
}
void* new_collada_core_light(void){
powergl_collada_core_light *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_light));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_technique_common = NULL; ptr->n_technique_common = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[19].map;
ptr->dom.n_map = g_supported_collada_core_types[19].n_map;
ptr->dom.add_child = add_child_collada_core_light;
ptr->dom.set_ref = set_ref_collada_core_light;
ptr->dom.parse_attrib = parse_attrib_collada_core_light;
ptr->dom.parse_content = parse_content_collada_core_light;
return ptr;
}
void set_ref_collada_core_directional(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_directional(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_directional(void *obj, size_t index, const char *value){
}
void add_child_collada_core_directional(void *obj, size_t index, dom_connector *child){
powergl_collada_core_directional *ptr = (powergl_collada_core_directional*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_color = powergl_resize(ptr->c_color, ++ptr->n_color, sizeof(powergl_collada_core_targetable_floats*));
ptr->c_color[ptr->n_color-1] = (powergl_collada_core_targetable_floats*)child;
break;
}
}
void* new_collada_core_directional(void){
powergl_collada_core_directional *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_directional));
ptr->c_color = NULL; ptr->n_color = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[20].map;
ptr->dom.n_map = g_supported_collada_core_types[20].n_map;
ptr->dom.add_child = add_child_collada_core_directional;
ptr->dom.set_ref = set_ref_collada_core_directional;
ptr->dom.parse_attrib = parse_attrib_collada_core_directional;
ptr->dom.parse_content = parse_content_collada_core_directional;
return ptr;
}
void set_ref_collada_core_camera(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_camera(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_camera(void *obj, size_t index, const char *value){
powergl_collada_core_camera *ptr = (powergl_collada_core_camera*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_camera(void *obj, size_t index, dom_connector *child){
powergl_collada_core_camera *ptr = (powergl_collada_core_camera*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_optics = powergl_resize(ptr->c_optics, ++ptr->n_optics, sizeof(powergl_collada_core_optics*));
ptr->c_optics[ptr->n_optics-1] = (powergl_collada_core_optics*)child;
break;
}
}
void* new_collada_core_camera(void){
powergl_collada_core_camera *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_camera));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_optics = NULL; ptr->n_optics = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[21].map;
ptr->dom.n_map = g_supported_collada_core_types[21].n_map;
ptr->dom.add_child = add_child_collada_core_camera;
ptr->dom.set_ref = set_ref_collada_core_camera;
ptr->dom.parse_attrib = parse_attrib_collada_core_camera;
ptr->dom.parse_content = parse_content_collada_core_camera;
return ptr;
}
void set_ref_collada_core_optics(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_optics(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_optics(void *obj, size_t index, const char *value){
}
void add_child_collada_core_optics(void *obj, size_t index, dom_connector *child){
powergl_collada_core_optics *ptr = (powergl_collada_core_optics*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_technique_common = powergl_resize(ptr->c_technique_common, ++ptr->n_technique_common, sizeof(powergl_collada_core_optics_technique_common*));
ptr->c_technique_common[ptr->n_technique_common-1] = (powergl_collada_core_optics_technique_common*)child;
break;
}
}
void* new_collada_core_optics(void){
powergl_collada_core_optics *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_optics));
ptr->c_technique_common = NULL; ptr->n_technique_common = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[22].map;
ptr->dom.n_map = g_supported_collada_core_types[22].n_map;
ptr->dom.add_child = add_child_collada_core_optics;
ptr->dom.set_ref = set_ref_collada_core_optics;
ptr->dom.parse_attrib = parse_attrib_collada_core_optics;
ptr->dom.parse_content = parse_content_collada_core_optics;
return ptr;
}
void set_ref_collada_core_perspective(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_perspective(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_perspective(void *obj, size_t index, const char *value){
}
void add_child_collada_core_perspective(void *obj, size_t index, dom_connector *child){
powergl_collada_core_perspective *ptr = (powergl_collada_core_perspective*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_xfov = powergl_resize(ptr->c_xfov, ++ptr->n_xfov, sizeof(powergl_collada_core_targetable_float*));
ptr->c_xfov[ptr->n_xfov-1] = (powergl_collada_core_targetable_float*)child;
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_yfov = powergl_resize(ptr->c_yfov, ++ptr->n_yfov, sizeof(powergl_collada_core_targetable_float*));
ptr->c_yfov[ptr->n_yfov-1] = (powergl_collada_core_targetable_float*)child;
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_aspect_ratio = powergl_resize(ptr->c_aspect_ratio, ++ptr->n_aspect_ratio, sizeof(powergl_collada_core_targetable_float*));
ptr->c_aspect_ratio[ptr->n_aspect_ratio-1] = (powergl_collada_core_targetable_float*)child;
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_znear = powergl_resize(ptr->c_znear, ++ptr->n_znear, sizeof(powergl_collada_core_targetable_float*));
ptr->c_znear[ptr->n_znear-1] = (powergl_collada_core_targetable_float*)child;
break;
case 4: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_zfar = powergl_resize(ptr->c_zfar, ++ptr->n_zfar, sizeof(powergl_collada_core_targetable_float*));
ptr->c_zfar[ptr->n_zfar-1] = (powergl_collada_core_targetable_float*)child;
break;
}
}
void* new_collada_core_perspective(void){
powergl_collada_core_perspective *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_perspective));
ptr->c_xfov = NULL; ptr->n_xfov = 0;
ptr->c_yfov = NULL; ptr->n_yfov = 0;
ptr->c_aspect_ratio = NULL; ptr->n_aspect_ratio = 0;
ptr->c_znear = NULL; ptr->n_znear = 0;
ptr->c_zfar = NULL; ptr->n_zfar = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[23].map;
ptr->dom.n_map = g_supported_collada_core_types[23].n_map;
ptr->dom.add_child = add_child_collada_core_perspective;
ptr->dom.set_ref = set_ref_collada_core_perspective;
ptr->dom.parse_attrib = parse_attrib_collada_core_perspective;
ptr->dom.parse_content = parse_content_collada_core_perspective;
return ptr;
}
void set_ref_collada_core_node(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_node(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_node(void *obj, size_t index, const char *value){
powergl_collada_core_node *ptr = (powergl_collada_core_node*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_sid = strlen(value) + 1;
ptr->c_sid = powergl_resize(NULL, ptr->n_sid, sizeof(char));
strcpy(ptr->c_sid, value);
break;
case 2: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_node(void *obj, size_t index, dom_connector *child){
powergl_collada_core_node *ptr = (powergl_collada_core_node*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_node = powergl_resize(ptr->c_node, ++ptr->n_node, sizeof(powergl_collada_core_node*));
ptr->c_node[ptr->n_node-1] = (powergl_collada_core_node*)child;
break;
case 4: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_matrix = powergl_resize(ptr->c_matrix, ++ptr->n_matrix, sizeof(powergl_collada_core_targetable_floats*));
ptr->c_matrix[ptr->n_matrix-1] = (powergl_collada_core_targetable_floats*)child;
break;
case 5: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_rotate = powergl_resize(ptr->c_rotate, ++ptr->n_rotate, sizeof(powergl_collada_core_targetable_floats*));
ptr->c_rotate[ptr->n_rotate-1] = (powergl_collada_core_targetable_floats*)child;
break;
case 6: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_scale = powergl_resize(ptr->c_scale, ++ptr->n_scale, sizeof(powergl_collada_core_targetable_floats*));
ptr->c_scale[ptr->n_scale-1] = (powergl_collada_core_targetable_floats*)child;
break;
case 7: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_translate = powergl_resize(ptr->c_translate, ++ptr->n_translate, sizeof(powergl_collada_core_targetable_floats*));
ptr->c_translate[ptr->n_translate-1] = (powergl_collada_core_targetable_floats*)child;
break;
case 8: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_instance_camera = powergl_resize(ptr->c_instance_camera, ++ptr->n_instance_camera, sizeof(powergl_collada_core_InstanceWithExtra*));
ptr->c_instance_camera[ptr->n_instance_camera-1] = (powergl_collada_core_InstanceWithExtra*)child;
break;
case 9: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_instance_light = powergl_resize(ptr->c_instance_light, ++ptr->n_instance_light, sizeof(powergl_collada_core_InstanceWithExtra*));
ptr->c_instance_light[ptr->n_instance_light-1] = (powergl_collada_core_InstanceWithExtra*)child;
break;
case 10: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_instance_geometry = powergl_resize(ptr->c_instance_geometry, ++ptr->n_instance_geometry, sizeof(powergl_collada_core_InstanceWithExtra*));
ptr->c_instance_geometry[ptr->n_instance_geometry-1] = (powergl_collada_core_InstanceWithExtra*)child;
break;
}
}
void* new_collada_core_node(void){
powergl_collada_core_node *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_node));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_sid = NULL; ptr->n_sid = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_node = NULL; ptr->n_node = 0;
ptr->c_matrix = NULL; ptr->n_matrix = 0;
ptr->c_rotate = NULL; ptr->n_rotate = 0;
ptr->c_scale = NULL; ptr->n_scale = 0;
ptr->c_translate = NULL; ptr->n_translate = 0;
ptr->c_instance_camera = NULL; ptr->n_instance_camera = 0;
ptr->c_instance_light = NULL; ptr->n_instance_light = 0;
ptr->c_instance_geometry = NULL; ptr->n_instance_geometry = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[24].map;
ptr->dom.n_map = g_supported_collada_core_types[24].n_map;
ptr->dom.add_child = add_child_collada_core_node;
ptr->dom.set_ref = set_ref_collada_core_node;
ptr->dom.parse_attrib = parse_attrib_collada_core_node;
ptr->dom.parse_content = parse_content_collada_core_node;
return ptr;
}
void set_ref_collada_core_source_technique_common(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_source_technique_common(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_source_technique_common(void *obj, size_t index, const char *value){
}
void add_child_collada_core_source_technique_common(void *obj, size_t index, dom_connector *child){
powergl_collada_core_source_technique_common *ptr = (powergl_collada_core_source_technique_common*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_accessor = powergl_resize(ptr->c_accessor, ++ptr->n_accessor, sizeof(powergl_collada_core_accessor*));
ptr->c_accessor[ptr->n_accessor-1] = (powergl_collada_core_accessor*)child;
break;
}
}
void* new_collada_core_source_technique_common(void){
powergl_collada_core_source_technique_common *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_source_technique_common));
ptr->c_accessor = NULL; ptr->n_accessor = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[25].map;
ptr->dom.n_map = g_supported_collada_core_types[25].n_map;
ptr->dom.add_child = add_child_collada_core_source_technique_common;
ptr->dom.set_ref = set_ref_collada_core_source_technique_common;
ptr->dom.parse_attrib = parse_attrib_collada_core_source_technique_common;
ptr->dom.parse_content = parse_content_collada_core_source_technique_common;
return ptr;
}
void set_ref_collada_core_light_technique_common(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_light_technique_common(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_light_technique_common(void *obj, size_t index, const char *value){
}
void add_child_collada_core_light_technique_common(void *obj, size_t index, dom_connector *child){
powergl_collada_core_light_technique_common *ptr = (powergl_collada_core_light_technique_common*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_directional = powergl_resize(ptr->c_directional, ++ptr->n_directional, sizeof(powergl_collada_core_directional*));
ptr->c_directional[ptr->n_directional-1] = (powergl_collada_core_directional*)child;
break;
}
}
void* new_collada_core_light_technique_common(void){
powergl_collada_core_light_technique_common *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_light_technique_common));
ptr->c_directional = NULL; ptr->n_directional = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[26].map;
ptr->dom.n_map = g_supported_collada_core_types[26].n_map;
ptr->dom.add_child = add_child_collada_core_light_technique_common;
ptr->dom.set_ref = set_ref_collada_core_light_technique_common;
ptr->dom.parse_attrib = parse_attrib_collada_core_light_technique_common;
ptr->dom.parse_content = parse_content_collada_core_light_technique_common;
return ptr;
}
void set_ref_collada_core_optics_technique_common(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_optics_technique_common(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_optics_technique_common(void *obj, size_t index, const char *value){
}
void add_child_collada_core_optics_technique_common(void *obj, size_t index, dom_connector *child){
powergl_collada_core_optics_technique_common *ptr = (powergl_collada_core_optics_technique_common*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_perspective = powergl_resize(ptr->c_perspective, ++ptr->n_perspective, sizeof(powergl_collada_core_perspective*));
ptr->c_perspective[ptr->n_perspective-1] = (powergl_collada_core_perspective*)child;
break;
}
}
void* new_collada_core_optics_technique_common(void){
powergl_collada_core_optics_technique_common *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_optics_technique_common));
ptr->c_perspective = NULL; ptr->n_perspective = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[27].map;
ptr->dom.n_map = g_supported_collada_core_types[27].n_map;
ptr->dom.add_child = add_child_collada_core_optics_technique_common;
ptr->dom.set_ref = set_ref_collada_core_optics_technique_common;
ptr->dom.parse_attrib = parse_attrib_collada_core_optics_technique_common;
ptr->dom.parse_content = parse_content_collada_core_optics_technique_common;
return ptr;
}
void set_ref_collada_core_InstanceWithExtra(void *obj, size_t index, dom_connector *ptr){
powergl_collada_core_InstanceWithExtra *ptr = (powergl_collada_core_InstanceWithExtra*)obj;
switch(index){
case 3: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_geometry = (powergl_collada_core_geometry*)ptr;
break;
case 4: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_camera = (powergl_collada_core_camera*)ptr;
break;
case 5: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_light = (powergl_collada_core_light*)ptr;
break;
case 6: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_visual_scene = (powergl_collada_core_visual_scene*)ptr;
break;
}
}
void parse_content_collada_core_InstanceWithExtra(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_InstanceWithExtra(void *obj, size_t index, const char *value){
powergl_collada_core_InstanceWithExtra *ptr = (powergl_collada_core_InstanceWithExtra*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_sid = strlen(value) + 1;
ptr->c_sid = powergl_resize(NULL, ptr->n_sid, sizeof(char));
strcpy(ptr->c_sid, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
case 2: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_url = strlen(value) + 1;
ptr->c_url = powergl_resize(NULL, ptr->n_url, sizeof(char));
strcpy(ptr->c_url, value);
break;
}
}
void add_child_collada_core_InstanceWithExtra(void *obj, size_t index, dom_connector *child){
powergl_collada_core_InstanceWithExtra *ptr = (powergl_collada_core_InstanceWithExtra*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 4: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 5: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 6: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_InstanceWithExtra(void){
powergl_collada_core_InstanceWithExtra *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_InstanceWithExtra));
ptr->c_sid = NULL; ptr->n_sid = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_url = NULL; ptr->n_url = 0;
ptr->r_geometry = NULL;
ptr->r_camera = NULL;
ptr->r_light = NULL;
ptr->r_visual_scene = NULL;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[28].map;
ptr->dom.n_map = g_supported_collada_core_types[28].n_map;
ptr->dom.add_child = add_child_collada_core_InstanceWithExtra;
ptr->dom.set_ref = set_ref_collada_core_InstanceWithExtra;
ptr->dom.parse_attrib = parse_attrib_collada_core_InstanceWithExtra;
ptr->dom.parse_content = parse_content_collada_core_InstanceWithExtra;
return ptr;
}
void set_ref_collada_core_source(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_source(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_source(void *obj, size_t index, const char *value){
powergl_collada_core_source *ptr = (powergl_collada_core_source*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_id = strlen(value) + 1;
ptr->c_id = powergl_resize(NULL, ptr->n_id, sizeof(char));
strcpy(ptr->c_id, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_name = strlen(value) + 1;
ptr->c_name = powergl_resize(NULL, ptr->n_name, sizeof(char));
strcpy(ptr->c_name, value);
break;
}
}
void add_child_collada_core_source(void *obj, size_t index, dom_connector *child){
powergl_collada_core_source *ptr = (powergl_collada_core_source*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_float_array = powergl_resize(ptr->c_float_array, ++ptr->n_float_array, sizeof(powergl_collada_core_float_array*));
ptr->c_float_array[ptr->n_float_array-1] = (powergl_collada_core_float_array*)child;
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_Name_array = powergl_resize(ptr->c_Name_array, ++ptr->n_Name_array, sizeof(powergl_collada_core_Name_array*));
ptr->c_Name_array[ptr->n_Name_array-1] = (powergl_collada_core_Name_array*)child;
break;
case 4: powergl_collada_add_child(ptr->dom.nodes, index, child);
ptr->c_technique_common = powergl_resize(ptr->c_technique_common, ++ptr->n_technique_common, sizeof(powergl_collada_core_source_technique_common*));
ptr->c_technique_common[ptr->n_technique_common-1] = (powergl_collada_core_source_technique_common*)child;
break;
}
}
void* new_collada_core_source(void){
powergl_collada_core_source *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_source));
ptr->c_id = NULL; ptr->n_id = 0;
ptr->c_name = NULL; ptr->n_name = 0;
ptr->c_float_array = NULL; ptr->n_float_array = 0;
ptr->c_Name_array = NULL; ptr->n_Name_array = 0;
ptr->c_technique_common = NULL; ptr->n_technique_common = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[29].map;
ptr->dom.n_map = g_supported_collada_core_types[29].n_map;
ptr->dom.add_child = add_child_collada_core_source;
ptr->dom.set_ref = set_ref_collada_core_source;
ptr->dom.parse_attrib = parse_attrib_collada_core_source;
ptr->dom.parse_content = parse_content_collada_core_source;
return ptr;
}
void set_ref_collada_core_input_local_offset(void *obj, size_t index, dom_connector *ptr){
powergl_collada_core_input_local_offset *ptr = (powergl_collada_core_input_local_offset*)obj;
switch(index){
case 4: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_mesh_source = (powergl_collada_core_source*)ptr;
break;
case 5: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_vertices = (powergl_collada_core_vertices*)ptr;
break;
}
}
void parse_content_collada_core_input_local_offset(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_input_local_offset(void *obj, size_t index, const char *value){
powergl_collada_core_input_local_offset *ptr = (powergl_collada_core_input_local_offset*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_semantic = strlen(value) + 1;
ptr->c_semantic = powergl_resize(NULL, ptr->n_semantic, sizeof(char));
strcpy(ptr->c_semantic, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_source = strlen(value) + 1;
ptr->c_source = powergl_resize(NULL, ptr->n_source, sizeof(char));
strcpy(ptr->c_source, value);
break;
case 2: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->c_set = strtoul( value, NULL, 10 );
break;
case 3: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->c_offset = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_input_local_offset(void *obj, size_t index, dom_connector *child){
powergl_collada_core_input_local_offset *ptr = (powergl_collada_core_input_local_offset*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 4: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 5: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_input_local_offset(void){
powergl_collada_core_input_local_offset *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_input_local_offset));
ptr->c_semantic = NULL; ptr->n_semantic = 0;
ptr->c_source = NULL; ptr->n_source = 0;
ptr->c_set = 0;
ptr->c_offset = 0;
ptr->r_mesh_source = NULL;
ptr->r_vertices = NULL;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[30].map;
ptr->dom.n_map = g_supported_collada_core_types[30].n_map;
ptr->dom.add_child = add_child_collada_core_input_local_offset;
ptr->dom.set_ref = set_ref_collada_core_input_local_offset;
ptr->dom.parse_attrib = parse_attrib_collada_core_input_local_offset;
ptr->dom.parse_content = parse_content_collada_core_input_local_offset;
return ptr;
}
void set_ref_collada_core_input_local(void *obj, size_t index, dom_connector *ptr){
powergl_collada_core_input_local *ptr = (powergl_collada_core_input_local*)obj;
switch(index){
case 2: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_mesh_source = (powergl_collada_core_source*)ptr;
break;
case 3: powergl_collada_set_ref(ptr->dom.nodes, index, ptr);
ptr->r_anim_source = (powergl_collada_core_source*)ptr;
break;
}
}
void parse_content_collada_core_input_local(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_input_local(void *obj, size_t index, const char *value){
powergl_collada_core_input_local *ptr = (powergl_collada_core_input_local*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_semantic = strlen(value) + 1;
ptr->c_semantic = powergl_resize(NULL, ptr->n_semantic, sizeof(char));
strcpy(ptr->c_semantic, value);
break;
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_source = strlen(value) + 1;
ptr->c_source = powergl_resize(NULL, ptr->n_source, sizeof(char));
strcpy(ptr->c_source, value);
break;
}
}
void add_child_collada_core_input_local(void *obj, size_t index, dom_connector *child){
powergl_collada_core_input_local *ptr = (powergl_collada_core_input_local*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_input_local(void){
powergl_collada_core_input_local *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_input_local));
ptr->c_semantic = NULL; ptr->n_semantic = 0;
ptr->c_source = NULL; ptr->n_source = 0;
ptr->r_mesh_source = NULL;
ptr->r_anim_source = NULL;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[31].map;
ptr->dom.n_map = g_supported_collada_core_types[31].n_map;
ptr->dom.add_child = add_child_collada_core_input_local;
ptr->dom.set_ref = set_ref_collada_core_input_local;
ptr->dom.parse_attrib = parse_attrib_collada_core_input_local;
ptr->dom.parse_content = parse_content_collada_core_input_local;
return ptr;
}
void set_ref_collada_core_ListOfUInts(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_ListOfUInts(void *obj, size_t index, const char *value){
powergl_collada_core_ListOfUInts *ptr = (powergl_collada_core_ListOfUInts*)obj;
switch(index){
case 0: powergl_collada_parse_content(ptr->dom.nodes, index, value);
ptr->content  = powergl_collada_parse_uints(value, &ptr->n_content);
break;
}
}
void parse_attrib_collada_core_ListOfUInts(void *obj, size_t index, const char *value){
}
void add_child_collada_core_ListOfUInts(void *obj, size_t index, dom_connector *child){
powergl_collada_core_ListOfUInts *ptr = (powergl_collada_core_ListOfUInts*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_ListOfUInts(void){
powergl_collada_core_ListOfUInts *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_ListOfUInts));
ptr->content = NULL; ptr->n_content = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[32].map;
ptr->dom.n_map = g_supported_collada_core_types[32].n_map;
ptr->dom.add_child = add_child_collada_core_ListOfUInts;
ptr->dom.set_ref = set_ref_collada_core_ListOfUInts;
ptr->dom.parse_attrib = parse_attrib_collada_core_ListOfUInts;
ptr->dom.parse_content = parse_content_collada_core_ListOfUInts;
return ptr;
}
void set_ref_collada_core_targetable_floats(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_targetable_floats(void *obj, size_t index, const char *value){
powergl_collada_core_targetable_floats *ptr = (powergl_collada_core_targetable_floats*)obj;
switch(index){
case 0: powergl_collada_parse_content(ptr->dom.nodes, index, value);
ptr->content  = powergl_collada_parse_floats(value, &ptr->n_content);
break;
}
}
void parse_attrib_collada_core_targetable_floats(void *obj, size_t index, const char *value){
powergl_collada_core_targetable_floats *ptr = (powergl_collada_core_targetable_floats*)obj;
switch(index){
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_sid = strlen(value) + 1;
ptr->c_sid = powergl_resize(NULL, ptr->n_sid, sizeof(char));
strcpy(ptr->c_sid, value);
break;
}
}
void add_child_collada_core_targetable_floats(void *obj, size_t index, dom_connector *child){
powergl_collada_core_targetable_floats *ptr = (powergl_collada_core_targetable_floats*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_targetable_floats(void){
powergl_collada_core_targetable_floats *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_targetable_floats));
ptr->content = NULL; ptr->n_content = 0;
ptr->c_sid = NULL; ptr->n_sid = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[33].map;
ptr->dom.n_map = g_supported_collada_core_types[33].n_map;
ptr->dom.add_child = add_child_collada_core_targetable_floats;
ptr->dom.set_ref = set_ref_collada_core_targetable_floats;
ptr->dom.parse_attrib = parse_attrib_collada_core_targetable_floats;
ptr->dom.parse_content = parse_content_collada_core_targetable_floats;
return ptr;
}
void set_ref_collada_core_targetable_float(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_targetable_float(void *obj, size_t index, const char *value){
powergl_collada_core_targetable_float *ptr = (powergl_collada_core_targetable_float*)obj;
switch(index){
case 0: powergl_collada_parse_content(ptr->dom.nodes, index, value);
ptr->content  = powergl_collada_parse_floats(value, &ptr->n_content);
break;
}
}
void parse_attrib_collada_core_targetable_float(void *obj, size_t index, const char *value){
powergl_collada_core_targetable_float *ptr = (powergl_collada_core_targetable_float*)obj;
switch(index){
case 1: powergl_collada_parse_attrib(ptr->dom.nodes, index, value);
ptr->n_sid = strlen(value) + 1;
ptr->c_sid = powergl_resize(NULL, ptr->n_sid, sizeof(char));
strcpy(ptr->c_sid, value);
break;
}
}
void add_child_collada_core_targetable_float(void *obj, size_t index, dom_connector *child){
powergl_collada_core_targetable_float *ptr = (powergl_collada_core_targetable_float*)obj;
switch(index){
case 0: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(ptr->dom.nodes, index, child);
break;
}
}
void* new_collada_core_targetable_float(void){
powergl_collada_core_targetable_float *ptr = powergl_resize(NULL, 1, sizeof(powergl_collada_core_targetable_float));
ptr->content = NULL; ptr->n_content = 0;
ptr->c_sid = NULL; ptr->n_sid = 0;
ptr->dom.nodes = NULL;
ptr->dom.map = g_supported_collada_core_types[34].map;
ptr->dom.n_map = g_supported_collada_core_types[34].n_map;
ptr->dom.add_child = add_child_collada_core_targetable_float;
ptr->dom.set_ref = set_ref_collada_core_targetable_float;
ptr->dom.parse_attrib = parse_attrib_collada_core_targetable_float;
ptr->dom.parse_content = parse_content_collada_core_targetable_float;
return ptr;
}
static void support_collada_core_type_COLLADA_COLLADA(){
char str[] = "COLLADA";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[0].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[0].name, str, size * sizeof(char));
char str_parent[] = "COLLADA";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[0].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[0].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[0].get_instance = new_collada_core_COLLADA;
map_dom_connector map[] = {{ "char*", "version", 1, NULL},{ "char*", "xmlns", 1, NULL},{ NULL, "library_animations", 0, NULL},{ NULL, "library_geometries", 0, NULL},{ NULL, "library_cameras", 0, NULL},{ NULL, "library_lights", 0, NULL},{ NULL, "library_visual_scenes", 0, NULL},{ NULL, "scene", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[0].n_map = size;
g_supported_collada_core_types[0].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_COLLADA_library_visual_scenes(){
char str[] = "library_visual_scenes";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[1].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[1].name, str, size * sizeof(char));
char str_parent[] = "COLLADA";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[1].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[1].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[1].get_instance = new_collada_core_library_visual_scenes;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "visual_scene", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[1].n_map = size;
g_supported_collada_core_types[1].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_COLLADA_library_cameras(){
char str[] = "library_cameras";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[2].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[2].name, str, size * sizeof(char));
char str_parent[] = "COLLADA";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[2].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[2].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[2].get_instance = new_collada_core_library_cameras;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "camera", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[2].n_map = size;
g_supported_collada_core_types[2].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_COLLADA_library_lights(){
char str[] = "library_lights";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[3].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[3].name, str, size * sizeof(char));
char str_parent[] = "COLLADA";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[3].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[3].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[3].get_instance = new_collada_core_library_lights;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "light", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[3].n_map = size;
g_supported_collada_core_types[3].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_COLLADA_library_geometries(){
char str[] = "library_geometries";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[4].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[4].name, str, size * sizeof(char));
char str_parent[] = "COLLADA";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[4].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[4].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[4].get_instance = new_collada_core_library_geometries;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "geometry", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[4].n_map = size;
g_supported_collada_core_types[4].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_COLLADA_library_animations(){
char str[] = "library_animations";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[5].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[5].name, str, size * sizeof(char));
char str_parent[] = "COLLADA";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[5].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[5].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[5].get_instance = new_collada_core_library_animations;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "animation", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[5].n_map = size;
g_supported_collada_core_types[5].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_COLLADA_scene(){
char str[] = "scene";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[6].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[6].name, str, size * sizeof(char));
char str_parent[] = "COLLADA";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[6].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[6].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[6].get_instance = new_collada_core_scene;
map_dom_connector map[] = {{ "InstanceWithExtra", "instance_visual_scene", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[6].n_map = size;
g_supported_collada_core_types[6].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_visual_scenes_visual_scene(){
char str[] = "visual_scene";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[7].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[7].name, str, size * sizeof(char));
char str_parent[] = "library_visual_scenes";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[7].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[7].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[7].get_instance = new_collada_core_visual_scene;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "node", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[7].n_map = size;
g_supported_collada_core_types[7].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_animations_animation(){
char str[] = "animation";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[8].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[8].name, str, size * sizeof(char));
char str_parent[] = "library_animations";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[8].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[8].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[8].get_instance = new_collada_core_animation;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ "source", "source", 0, NULL},{ NULL, "sampler", 0, NULL},{ NULL, "channel", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[8].n_map = size;
g_supported_collada_core_types[8].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_animation_sampler(){
char str[] = "sampler";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[9].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[9].name, str, size * sizeof(char));
char str_parent[] = "animation";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[9].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[9].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[9].get_instance = new_collada_core_sampler;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "input_local", "input", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[9].n_map = size;
g_supported_collada_core_types[9].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_animation_channel(){
char str[] = "channel";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[10].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[10].name, str, size * sizeof(char));
char str_parent[] = "animation";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[10].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[10].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[10].get_instance = new_collada_core_channel;
map_dom_connector map[] = {{ "char*", "source", 1, NULL},{ "char*", "target", 1, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[10].n_map = size;
g_supported_collada_core_types[10].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_geometries_geometry(){
char str[] = "geometry";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[11].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[11].name, str, size * sizeof(char));
char str_parent[] = "library_geometries";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[11].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[11].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[11].get_instance = new_collada_core_geometry;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "mesh", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[11].n_map = size;
g_supported_collada_core_types[11].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_geometry_mesh(){
char str[] = "mesh";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[12].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[12].name, str, size * sizeof(char));
char str_parent[] = "geometry";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[12].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[12].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[12].get_instance = new_collada_core_mesh;
map_dom_connector map[] = {{ "source", "source", 0, NULL},{ NULL, "vertices", 0, NULL},{ NULL, "triangles", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[12].n_map = size;
g_supported_collada_core_types[12].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_technique_common_accessor(){
char str[] = "accessor";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[13].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[13].name, str, size * sizeof(char));
char str_parent[] = "technique_common";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[13].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[13].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[13].get_instance = new_collada_core_accessor;
map_dom_connector map[] = {{ "char*", "source", 1, NULL},{ "size_t", "count", 1, NULL},{ "size_t", "offset", 1, NULL},{ "size_t", "stride", 1, NULL},{ NULL, "param", 0, NULL},{ "float_array", "float_array", 3, "source"},{ "Name_array", "Name_array", 3, "source"},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[13].n_map = size;
g_supported_collada_core_types[13].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_accessor_param(){
char str[] = "param";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[14].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[14].name, str, size * sizeof(char));
char str_parent[] = "accessor";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[14].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[14].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[14].get_instance = new_collada_core_param;
map_dom_connector map[] = {{ "char*", "sid", 1, NULL},{ "char*", "name", 1, NULL},{ "char*", "type", 1, NULL},{ "char*", "semantic", 1, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[14].n_map = size;
g_supported_collada_core_types[14].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_source_float_array(){
char str[] = "float_array";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[15].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[15].name, str, size * sizeof(char));
char str_parent[] = "source";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[15].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[15].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[15].get_instance = new_collada_core_float_array;
map_dom_connector map[] = {{ "double*", "content", 2, NULL},{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ "size_t", "count", 1, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[15].n_map = size;
g_supported_collada_core_types[15].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_source_Name_array(){
char str[] = "Name_array";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[16].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[16].name, str, size * sizeof(char));
char str_parent[] = "source";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[16].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[16].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[16].get_instance = new_collada_core_Name_array;
map_dom_connector map[] = {{ "char**", "content", 2, NULL},{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ "size_t", "count", 1, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[16].n_map = size;
g_supported_collada_core_types[16].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_mesh_vertices(){
char str[] = "vertices";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[17].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[17].name, str, size * sizeof(char));
char str_parent[] = "mesh";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[17].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[17].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[17].get_instance = new_collada_core_vertices;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ "input_local", "input", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[17].n_map = size;
g_supported_collada_core_types[17].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_mesh_triangles(){
char str[] = "triangles";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[18].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[18].name, str, size * sizeof(char));
char str_parent[] = "mesh";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[18].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[18].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[18].get_instance = new_collada_core_triangles;
map_dom_connector map[] = {{ "char*", "name", 1, NULL},{ "size_t", "count", 1, NULL},{ "input_local_offset", "input", 0, NULL},{ "ListOfUInts", "p", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[18].n_map = size;
g_supported_collada_core_types[18].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_lights_light(){
char str[] = "light";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[19].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[19].name, str, size * sizeof(char));
char str_parent[] = "library_lights";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[19].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[19].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[19].get_instance = new_collada_core_light;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ "light_technique_common", "technique_common", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[19].n_map = size;
g_supported_collada_core_types[19].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_technique_common_directional(){
char str[] = "directional";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[20].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[20].name, str, size * sizeof(char));
char str_parent[] = "technique_common";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[20].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[20].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[20].get_instance = new_collada_core_directional;
map_dom_connector map[] = {{ "targetable_floats", "color", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[20].n_map = size;
g_supported_collada_core_types[20].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_cameras_camera(){
char str[] = "camera";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[21].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[21].name, str, size * sizeof(char));
char str_parent[] = "library_cameras";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[21].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[21].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[21].get_instance = new_collada_core_camera;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "optics", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[21].n_map = size;
g_supported_collada_core_types[21].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_camera_optics(){
char str[] = "optics";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[22].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[22].name, str, size * sizeof(char));
char str_parent[] = "camera";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[22].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[22].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[22].get_instance = new_collada_core_optics;
map_dom_connector map[] = {{ "optics_technique_common", "technique_common", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[22].n_map = size;
g_supported_collada_core_types[22].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_technique_common_perspective(){
char str[] = "perspective";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[23].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[23].name, str, size * sizeof(char));
char str_parent[] = "technique_common";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[23].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[23].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[23].get_instance = new_collada_core_perspective;
map_dom_connector map[] = {{ "targetable_float", "xfov", 0, NULL},{ "targetable_float", "yfov", 0, NULL},{ "targetable_float", "aspect_ratio", 0, NULL},{ "targetable_float", "znear", 0, NULL},{ "targetable_float", "zfar", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[23].n_map = size;
g_supported_collada_core_types[23].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_visual_scene_node(){
char str[] = "node";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[24].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[24].name, str, size * sizeof(char));
char str_parent[] = "visual_scene";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[24].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[24].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[24].get_instance = new_collada_core_node;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "sid", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "node", 0, NULL},{ "targetable_floats", "matrix", 0, NULL},{ "targetable_floats", "rotate", 0, NULL},{ "targetable_floats", "scale", 0, NULL},{ "targetable_floats", "translate", 0, NULL},{ "InstanceWithExtra", "instance_camera", 0, NULL},{ "InstanceWithExtra", "instance_light", 0, NULL},{ "InstanceWithExtra", "instance_geometry", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[24].n_map = size;
g_supported_collada_core_types[24].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_source_technique_common(){
char str[] = "source_technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[25].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[25].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[25].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[25].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[25].get_instance = new_collada_core_source_technique_common;
map_dom_connector map[] = {{ NULL, "accessor", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[25].n_map = size;
g_supported_collada_core_types[25].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_light_technique_common(){
char str[] = "light_technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[26].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[26].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[26].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[26].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[26].get_instance = new_collada_core_light_technique_common;
map_dom_connector map[] = {{ NULL, "directional", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[26].n_map = size;
g_supported_collada_core_types[26].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_optics_technique_common(){
char str[] = "optics_technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[27].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[27].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[27].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[27].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[27].get_instance = new_collada_core_optics_technique_common;
map_dom_connector map[] = {{ NULL, "perspective", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[27].n_map = size;
g_supported_collada_core_types[27].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_InstanceWithExtra(){
char str[] = "InstanceWithExtra";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[28].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[28].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[28].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[28].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[28].get_instance = new_collada_core_InstanceWithExtra;
map_dom_connector map[] = {{ "char*", "sid", 1, NULL},{ "char*", "name", 1, NULL},{ "char*", "url", 1, NULL},{ "geometry", "geometry", 3, "url"},{ "camera", "camera", 3, "url"},{ "light", "light", 3, "url"},{ "visual_scene", "visual_scene", 3, "url"},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[28].n_map = size;
g_supported_collada_core_types[28].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_source(){
char str[] = "source";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[29].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[29].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[29].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[29].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[29].get_instance = new_collada_core_source;
map_dom_connector map[] = {{ "char*", "id", 1, NULL},{ "char*", "name", 1, NULL},{ NULL, "float_array", 0, NULL},{ NULL, "Name_array", 0, NULL},{ "source_technique_common", "technique_common", 0, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[29].n_map = size;
g_supported_collada_core_types[29].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_input_local_offset(){
char str[] = "input_local_offset";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[30].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[30].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[30].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[30].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[30].get_instance = new_collada_core_input_local_offset;
map_dom_connector map[] = {{ "char*", "semantic", 1, NULL},{ "char*", "source", 1, NULL},{ "size_t", "set", 1, NULL},{ "size_t", "offset", 1, NULL},{ "source", "mesh_source", 3, "source"},{ "vertices", "vertices", 3, "source"},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[30].n_map = size;
g_supported_collada_core_types[30].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_input_local(){
char str[] = "input_local";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[31].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[31].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[31].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[31].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[31].get_instance = new_collada_core_input_local;
map_dom_connector map[] = {{ "char*", "semantic", 1, NULL},{ "char*", "source", 1, NULL},{ "source", "mesh_source", 3, "source"},{ "source", "anim_source", 3, "source"},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[31].n_map = size;
g_supported_collada_core_types[31].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_ListOfUInts(){
char str[] = "ListOfUInts";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[32].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[32].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[32].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[32].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[32].get_instance = new_collada_core_ListOfUInts;
map_dom_connector map[] = {{ "size_t*", "content", 2, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[32].n_map = size;
g_supported_collada_core_types[32].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_targetable_floats(){
char str[] = "targetable_floats";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[33].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[33].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[33].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[33].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[33].get_instance = new_collada_core_targetable_floats;
map_dom_connector map[] = {{ "double*", "content", 2, NULL},{ "char*", "sid", 1, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[33].n_map = size;
g_supported_collada_core_types[33].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_targetable_float(){
char str[] = "targetable_float";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[34].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[34].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[34].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[34].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[34].get_instance = new_collada_core_targetable_float;
map_dom_connector map[] = {{ "double*", "content", 2, NULL},{ "char*", "sid", 1, NULL},};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[34].n_map = size;
g_supported_collada_core_types[34].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_source_technique_common(){
char str[] = "technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[35].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[35].name, str, size * sizeof(char));
char str_parent[] = "source";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[35].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[35].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[35].get_instance = new_collada_core_source_technique_common;
g_supported_collada_core_types[35].n_map = g_supported_collada_core_types[25].n_map;
g_supported_collada_core_types[35].map = g_supported_collada_core_types[25].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_light_technique_common(){
char str[] = "technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[36].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[36].name, str, size * sizeof(char));
char str_parent[] = "light";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[36].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[36].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[36].get_instance = new_collada_core_light_technique_common;
g_supported_collada_core_types[36].n_map = g_supported_collada_core_types[26].n_map;
g_supported_collada_core_types[36].map = g_supported_collada_core_types[26].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_optics_technique_common(){
char str[] = "technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[37].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[37].name, str, size * sizeof(char));
char str_parent[] = "optics";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[37].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[37].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[37].get_instance = new_collada_core_optics_technique_common;
g_supported_collada_core_types[37].n_map = g_supported_collada_core_types[27].n_map;
g_supported_collada_core_types[37].map = g_supported_collada_core_types[27].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_triangles_input(){
char str[] = "input";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[38].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[38].name, str, size * sizeof(char));
char str_parent[] = "triangles";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[38].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[38].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[38].get_instance = new_collada_core_input_local_offset;
g_supported_collada_core_types[38].n_map = g_supported_collada_core_types[30].n_map;
g_supported_collada_core_types[38].map = g_supported_collada_core_types[30].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_vertices_input(){
char str[] = "input";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[39].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[39].name, str, size * sizeof(char));
char str_parent[] = "vertices";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[39].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[39].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[39].get_instance = new_collada_core_input_local;
g_supported_collada_core_types[39].n_map = g_supported_collada_core_types[31].n_map;
g_supported_collada_core_types[39].map = g_supported_collada_core_types[31].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_sampler_input(){
char str[] = "input";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[40].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[40].name, str, size * sizeof(char));
char str_parent[] = "sampler";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[40].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[40].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[40].get_instance = new_collada_core_input_local;
g_supported_collada_core_types[40].n_map = g_supported_collada_core_types[31].n_map;
g_supported_collada_core_types[40].map = g_supported_collada_core_types[31].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_mesh_source(){
char str[] = "source";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[41].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[41].name, str, size * sizeof(char));
char str_parent[] = "mesh";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[41].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[41].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[41].get_instance = new_collada_core_source;
g_supported_collada_core_types[41].n_map = g_supported_collada_core_types[29].n_map;
g_supported_collada_core_types[41].map = g_supported_collada_core_types[29].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_animation_source(){
char str[] = "source";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[42].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[42].name, str, size * sizeof(char));
char str_parent[] = "animation";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[42].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[42].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[42].get_instance = new_collada_core_source;
g_supported_collada_core_types[42].n_map = g_supported_collada_core_types[29].n_map;
g_supported_collada_core_types[42].map = g_supported_collada_core_types[29].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_instance_camera(){
char str[] = "instance_camera";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[43].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[43].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[43].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[43].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[43].get_instance = new_collada_core_InstanceWithExtra;
g_supported_collada_core_types[43].n_map = g_supported_collada_core_types[28].n_map;
g_supported_collada_core_types[43].map = g_supported_collada_core_types[28].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_instance_geometry(){
char str[] = "instance_geometry";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[44].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[44].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[44].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[44].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[44].get_instance = new_collada_core_InstanceWithExtra;
g_supported_collada_core_types[44].n_map = g_supported_collada_core_types[28].n_map;
g_supported_collada_core_types[44].map = g_supported_collada_core_types[28].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_instance_light(){
char str[] = "instance_light";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[45].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[45].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[45].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[45].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[45].get_instance = new_collada_core_InstanceWithExtra;
g_supported_collada_core_types[45].n_map = g_supported_collada_core_types[28].n_map;
g_supported_collada_core_types[45].map = g_supported_collada_core_types[28].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_scene_instance_visual_scene(){
char str[] = "instance_visual_scene";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[46].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[46].name, str, size * sizeof(char));
char str_parent[] = "scene";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[46].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[46].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[46].get_instance = new_collada_core_InstanceWithExtra;
g_supported_collada_core_types[46].n_map = g_supported_collada_core_types[28].n_map;
g_supported_collada_core_types[46].map = g_supported_collada_core_types[28].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_triangles_p(){
char str[] = "p";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[47].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[47].name, str, size * sizeof(char));
char str_parent[] = "triangles";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[47].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[47].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[47].get_instance = new_collada_core_ListOfUInts;
g_supported_collada_core_types[47].n_map = g_supported_collada_core_types[32].n_map;
g_supported_collada_core_types[47].map = g_supported_collada_core_types[32].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_directional_color(){
char str[] = "color";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[48].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[48].name, str, size * sizeof(char));
char str_parent[] = "directional";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[48].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[48].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[48].get_instance = new_collada_core_targetable_floats;
g_supported_collada_core_types[48].n_map = g_supported_collada_core_types[33].n_map;
g_supported_collada_core_types[48].map = g_supported_collada_core_types[33].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_matrix(){
char str[] = "matrix";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[49].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[49].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[49].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[49].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[49].get_instance = new_collada_core_targetable_floats;
g_supported_collada_core_types[49].n_map = g_supported_collada_core_types[33].n_map;
g_supported_collada_core_types[49].map = g_supported_collada_core_types[33].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_rotate(){
char str[] = "rotate";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[50].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[50].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[50].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[50].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[50].get_instance = new_collada_core_targetable_floats;
g_supported_collada_core_types[50].n_map = g_supported_collada_core_types[33].n_map;
g_supported_collada_core_types[50].map = g_supported_collada_core_types[33].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_scale(){
char str[] = "scale";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[51].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[51].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[51].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[51].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[51].get_instance = new_collada_core_targetable_floats;
g_supported_collada_core_types[51].n_map = g_supported_collada_core_types[33].n_map;
g_supported_collada_core_types[51].map = g_supported_collada_core_types[33].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_translate(){
char str[] = "translate";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[52].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[52].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[52].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[52].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[52].get_instance = new_collada_core_targetable_floats;
g_supported_collada_core_types[52].n_map = g_supported_collada_core_types[33].n_map;
g_supported_collada_core_types[52].map = g_supported_collada_core_types[33].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_xfov(){
char str[] = "xfov";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[53].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[53].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[53].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[53].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[53].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[53].n_map = g_supported_collada_core_types[34].n_map;
g_supported_collada_core_types[53].map = g_supported_collada_core_types[34].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_yfov(){
char str[] = "yfov";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[54].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[54].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[54].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[54].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[54].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[54].n_map = g_supported_collada_core_types[34].n_map;
g_supported_collada_core_types[54].map = g_supported_collada_core_types[34].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_aspect_ratio(){
char str[] = "aspect_ratio";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[55].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[55].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[55].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[55].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[55].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[55].n_map = g_supported_collada_core_types[34].n_map;
g_supported_collada_core_types[55].map = g_supported_collada_core_types[34].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_znear(){
char str[] = "znear";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[56].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[56].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[56].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[56].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[56].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[56].n_map = g_supported_collada_core_types[34].n_map;
g_supported_collada_core_types[56].map = g_supported_collada_core_types[34].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_zfar(){
char str[] = "zfar";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[57].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[57].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[57].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[57].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[57].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[57].n_map = g_supported_collada_core_types[34].n_map;
g_supported_collada_core_types[57].map = g_supported_collada_core_types[34].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_node(){
char str[] = "node";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[58].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[58].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[58].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[58].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[58].get_instance = new_collada_core_node;
g_supported_collada_core_types[58].n_map = g_supported_collada_core_types[58].n_map;
g_supported_collada_core_types[58].map = g_supported_collada_core_types[58].map;
g_n_supported_collada_core_types++;
}
void powergl_collada_core_init(){
support_collada_core_type_COLLADA_COLLADA();
support_collada_core_type_COLLADA_library_visual_scenes();
support_collada_core_type_COLLADA_library_cameras();
support_collada_core_type_COLLADA_library_lights();
support_collada_core_type_COLLADA_library_geometries();
support_collada_core_type_COLLADA_library_animations();
support_collada_core_type_COLLADA_scene();
support_collada_core_type_library_visual_scenes_visual_scene();
support_collada_core_type_library_animations_animation();
support_collada_core_type_animation_sampler();
support_collada_core_type_animation_channel();
support_collada_core_type_library_geometries_geometry();
support_collada_core_type_geometry_mesh();
support_collada_core_type_technique_common_accessor();
support_collada_core_type_accessor_param();
support_collada_core_type_source_float_array();
support_collada_core_type_source_Name_array();
support_collada_core_type_mesh_vertices();
support_collada_core_type_mesh_triangles();
support_collada_core_type_library_lights_light();
support_collada_core_type_technique_common_directional();
support_collada_core_type_library_cameras_camera();
support_collada_core_type_camera_optics();
support_collada_core_type_technique_common_perspective();
support_collada_core_type_visual_scene_node();
support_collada_core_type_0_source_technique_common();
support_collada_core_type_0_light_technique_common();
support_collada_core_type_0_optics_technique_common();
support_collada_core_type_0_InstanceWithExtra();
support_collada_core_type_0_source();
support_collada_core_type_0_input_local_offset();
support_collada_core_type_0_input_local();
support_collada_core_type_0_ListOfUInts();
support_collada_core_type_0_targetable_floats();
support_collada_core_type_0_targetable_float();
support_collada_core_type_source_technique_common();
support_collada_core_type_light_technique_common();
support_collada_core_type_optics_technique_common();
support_collada_core_type_triangles_input();
support_collada_core_type_vertices_input();
support_collada_core_type_sampler_input();
support_collada_core_type_mesh_source();
support_collada_core_type_animation_source();
support_collada_core_type_node_instance_camera();
support_collada_core_type_node_instance_geometry();
support_collada_core_type_node_instance_light();
support_collada_core_type_scene_instance_visual_scene();
support_collada_core_type_triangles_p();
support_collada_core_type_directional_color();
support_collada_core_type_node_matrix();
support_collada_core_type_node_rotate();
support_collada_core_type_node_scale();
support_collada_core_type_node_translate();
support_collada_core_type_perspective_xfov();
support_collada_core_type_perspective_yfov();
support_collada_core_type_perspective_aspect_ratio();
support_collada_core_type_perspective_znear();
support_collada_core_type_perspective_zfar();
support_collada_core_type_node_node();
}
