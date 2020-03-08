#include "core.h"
static size_t g_n_supported_collada_core_types;
static supported_type g_supported_collada_core_types[48];
int powergl_collada_core_check_type(const char *this, const char *parent){
for(int i=0; i<g_n_supported_collada_core_types; i++){
if(strcmp(g_supported_collada_core_types[i].name, this) == 0 && strcmp(g_supported_collada_core_types[i].parent, parent) == 0 ){
return i;
}
}
return -1;
}
void* powergl_collada_core_get_instance(const char *this, const char *parent){
int index = powergl_collada_core_check_type(this, parent);
if( index > -1 ) return g_supported_collada_core_types[index].get_instance();
else return NULL;
}
void set_ref_collada_core_COLLADA(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_COLLADA(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_COLLADA(void *obj, size_t index, const char *value){
powergl_collada_core_COLLADA *this = (powergl_collada_core_COLLADA*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_version = strlen(value) + 1;
this->c_version = powergl_resize(NULL, this->n_version, sizeof(char));
strcpy(this->c_version, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_xmlns = strlen(value) + 1;
this->c_xmlns = powergl_resize(NULL, this->n_xmlns, sizeof(char));
strcpy(this->c_xmlns, value);
break;
}
}
void add_child_collada_core_COLLADA(void *obj, size_t index, dom_connector *child){
powergl_collada_core_COLLADA *this = (powergl_collada_core_COLLADA*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_library_geometries = powergl_resize(this->c_library_geometries, ++this->n_library_geometries, sizeof(powergl_collada_core_library_geometries*));
this->c_library_geometries[this->n_library_geometries-1] = (powergl_collada_core_library_geometries*)child;
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_library_cameras = powergl_resize(this->c_library_cameras, ++this->n_library_cameras, sizeof(powergl_collada_core_library_cameras*));
this->c_library_cameras[this->n_library_cameras-1] = (powergl_collada_core_library_cameras*)child;
break;
case 4: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_library_lights = powergl_resize(this->c_library_lights, ++this->n_library_lights, sizeof(powergl_collada_core_library_lights*));
this->c_library_lights[this->n_library_lights-1] = (powergl_collada_core_library_lights*)child;
break;
case 5: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_library_visual_scenes = powergl_resize(this->c_library_visual_scenes, ++this->n_library_visual_scenes, sizeof(powergl_collada_core_library_visual_scenes*));
this->c_library_visual_scenes[this->n_library_visual_scenes-1] = (powergl_collada_core_library_visual_scenes*)child;
break;
case 6: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_scene = powergl_resize(this->c_scene, ++this->n_scene, sizeof(powergl_collada_core_scene*));
this->c_scene[this->n_scene-1] = (powergl_collada_core_scene*)child;
break;
}
}
void* new_collada_core_COLLADA(void){
powergl_collada_core_COLLADA *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_COLLADA));
this->c_version = NULL; this->n_version = 0;
this->c_xmlns = NULL; this->n_xmlns = 0;
this->c_library_geometries = NULL; this->n_library_geometries = 0;
this->c_library_cameras = NULL; this->n_library_cameras = 0;
this->c_library_lights = NULL; this->n_library_lights = 0;
this->c_library_visual_scenes = NULL; this->n_library_visual_scenes = 0;
this->c_scene = NULL; this->n_scene = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[0].map;
this->dom.n_map = g_supported_collada_core_types[0].n_map;
this->dom.add_child = add_child_collada_core_COLLADA;
this->dom.set_ref = set_ref_collada_core_COLLADA;
this->dom.parse_attrib = parse_attrib_collada_core_COLLADA;
this->dom.parse_content = parse_content_collada_core_COLLADA;
return this;
}
void set_ref_collada_core_library_visual_scenes(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_visual_scenes(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_visual_scenes(void *obj, size_t index, const char *value){
powergl_collada_core_library_visual_scenes *this = (powergl_collada_core_library_visual_scenes*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_library_visual_scenes(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_visual_scenes *this = (powergl_collada_core_library_visual_scenes*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_visual_scene = powergl_resize(this->c_visual_scene, ++this->n_visual_scene, sizeof(powergl_collada_core_visual_scene*));
this->c_visual_scene[this->n_visual_scene-1] = (powergl_collada_core_visual_scene*)child;
break;
}
}
void* new_collada_core_library_visual_scenes(void){
powergl_collada_core_library_visual_scenes *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_visual_scenes));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_visual_scene = NULL; this->n_visual_scene = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[1].map;
this->dom.n_map = g_supported_collada_core_types[1].n_map;
this->dom.add_child = add_child_collada_core_library_visual_scenes;
this->dom.set_ref = set_ref_collada_core_library_visual_scenes;
this->dom.parse_attrib = parse_attrib_collada_core_library_visual_scenes;
this->dom.parse_content = parse_content_collada_core_library_visual_scenes;
return this;
}
void set_ref_collada_core_library_cameras(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_cameras(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_cameras(void *obj, size_t index, const char *value){
powergl_collada_core_library_cameras *this = (powergl_collada_core_library_cameras*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_library_cameras(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_cameras *this = (powergl_collada_core_library_cameras*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_camera = powergl_resize(this->c_camera, ++this->n_camera, sizeof(powergl_collada_core_camera*));
this->c_camera[this->n_camera-1] = (powergl_collada_core_camera*)child;
break;
}
}
void* new_collada_core_library_cameras(void){
powergl_collada_core_library_cameras *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_cameras));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_camera = NULL; this->n_camera = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[2].map;
this->dom.n_map = g_supported_collada_core_types[2].n_map;
this->dom.add_child = add_child_collada_core_library_cameras;
this->dom.set_ref = set_ref_collada_core_library_cameras;
this->dom.parse_attrib = parse_attrib_collada_core_library_cameras;
this->dom.parse_content = parse_content_collada_core_library_cameras;
return this;
}
void set_ref_collada_core_library_lights(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_lights(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_lights(void *obj, size_t index, const char *value){
powergl_collada_core_library_lights *this = (powergl_collada_core_library_lights*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_library_lights(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_lights *this = (powergl_collada_core_library_lights*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_light = powergl_resize(this->c_light, ++this->n_light, sizeof(powergl_collada_core_light*));
this->c_light[this->n_light-1] = (powergl_collada_core_light*)child;
break;
}
}
void* new_collada_core_library_lights(void){
powergl_collada_core_library_lights *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_lights));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_light = NULL; this->n_light = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[3].map;
this->dom.n_map = g_supported_collada_core_types[3].n_map;
this->dom.add_child = add_child_collada_core_library_lights;
this->dom.set_ref = set_ref_collada_core_library_lights;
this->dom.parse_attrib = parse_attrib_collada_core_library_lights;
this->dom.parse_content = parse_content_collada_core_library_lights;
return this;
}
void set_ref_collada_core_library_geometries(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_library_geometries(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_library_geometries(void *obj, size_t index, const char *value){
powergl_collada_core_library_geometries *this = (powergl_collada_core_library_geometries*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_library_geometries(void *obj, size_t index, dom_connector *child){
powergl_collada_core_library_geometries *this = (powergl_collada_core_library_geometries*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_geometry = powergl_resize(this->c_geometry, ++this->n_geometry, sizeof(powergl_collada_core_geometry*));
this->c_geometry[this->n_geometry-1] = (powergl_collada_core_geometry*)child;
break;
}
}
void* new_collada_core_library_geometries(void){
powergl_collada_core_library_geometries *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_library_geometries));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_geometry = NULL; this->n_geometry = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[4].map;
this->dom.n_map = g_supported_collada_core_types[4].n_map;
this->dom.add_child = add_child_collada_core_library_geometries;
this->dom.set_ref = set_ref_collada_core_library_geometries;
this->dom.parse_attrib = parse_attrib_collada_core_library_geometries;
this->dom.parse_content = parse_content_collada_core_library_geometries;
return this;
}
void set_ref_collada_core_scene(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_scene(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_scene(void *obj, size_t index, const char *value){
}
void add_child_collada_core_scene(void *obj, size_t index, dom_connector *child){
powergl_collada_core_scene *this = (powergl_collada_core_scene*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_instance_visual_scene = powergl_resize(this->c_instance_visual_scene, ++this->n_instance_visual_scene, sizeof(powergl_collada_core_InstanceWithExtra*));
this->c_instance_visual_scene[this->n_instance_visual_scene-1] = (powergl_collada_core_InstanceWithExtra*)child;
break;
}
}
void* new_collada_core_scene(void){
powergl_collada_core_scene *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_scene));
this->c_instance_visual_scene = NULL; this->n_instance_visual_scene = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[5].map;
this->dom.n_map = g_supported_collada_core_types[5].n_map;
this->dom.add_child = add_child_collada_core_scene;
this->dom.set_ref = set_ref_collada_core_scene;
this->dom.parse_attrib = parse_attrib_collada_core_scene;
this->dom.parse_content = parse_content_collada_core_scene;
return this;
}
void set_ref_collada_core_visual_scene(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_visual_scene(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_visual_scene(void *obj, size_t index, const char *value){
powergl_collada_core_visual_scene *this = (powergl_collada_core_visual_scene*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_visual_scene(void *obj, size_t index, dom_connector *child){
powergl_collada_core_visual_scene *this = (powergl_collada_core_visual_scene*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_node = powergl_resize(this->c_node, ++this->n_node, sizeof(powergl_collada_core_node*));
this->c_node[this->n_node-1] = (powergl_collada_core_node*)child;
break;
}
}
void* new_collada_core_visual_scene(void){
powergl_collada_core_visual_scene *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_visual_scene));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_node = NULL; this->n_node = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[6].map;
this->dom.n_map = g_supported_collada_core_types[6].n_map;
this->dom.add_child = add_child_collada_core_visual_scene;
this->dom.set_ref = set_ref_collada_core_visual_scene;
this->dom.parse_attrib = parse_attrib_collada_core_visual_scene;
this->dom.parse_content = parse_content_collada_core_visual_scene;
return this;
}
void set_ref_collada_core_geometry(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_geometry(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_geometry(void *obj, size_t index, const char *value){
powergl_collada_core_geometry *this = (powergl_collada_core_geometry*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_geometry(void *obj, size_t index, dom_connector *child){
powergl_collada_core_geometry *this = (powergl_collada_core_geometry*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_mesh = powergl_resize(this->c_mesh, ++this->n_mesh, sizeof(powergl_collada_core_mesh*));
this->c_mesh[this->n_mesh-1] = (powergl_collada_core_mesh*)child;
break;
}
}
void* new_collada_core_geometry(void){
powergl_collada_core_geometry *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_geometry));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_mesh = NULL; this->n_mesh = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[7].map;
this->dom.n_map = g_supported_collada_core_types[7].n_map;
this->dom.add_child = add_child_collada_core_geometry;
this->dom.set_ref = set_ref_collada_core_geometry;
this->dom.parse_attrib = parse_attrib_collada_core_geometry;
this->dom.parse_content = parse_content_collada_core_geometry;
return this;
}
void set_ref_collada_core_mesh(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_mesh(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_mesh(void *obj, size_t index, const char *value){
}
void add_child_collada_core_mesh(void *obj, size_t index, dom_connector *child){
powergl_collada_core_mesh *this = (powergl_collada_core_mesh*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_source = powergl_resize(this->c_source, ++this->n_source, sizeof(powergl_collada_core_source*));
this->c_source[this->n_source-1] = (powergl_collada_core_source*)child;
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_vertices = powergl_resize(this->c_vertices, ++this->n_vertices, sizeof(powergl_collada_core_vertices*));
this->c_vertices[this->n_vertices-1] = (powergl_collada_core_vertices*)child;
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_triangles = powergl_resize(this->c_triangles, ++this->n_triangles, sizeof(powergl_collada_core_triangles*));
this->c_triangles[this->n_triangles-1] = (powergl_collada_core_triangles*)child;
break;
}
}
void* new_collada_core_mesh(void){
powergl_collada_core_mesh *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_mesh));
this->c_source = NULL; this->n_source = 0;
this->c_vertices = NULL; this->n_vertices = 0;
this->c_triangles = NULL; this->n_triangles = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[8].map;
this->dom.n_map = g_supported_collada_core_types[8].n_map;
this->dom.add_child = add_child_collada_core_mesh;
this->dom.set_ref = set_ref_collada_core_mesh;
this->dom.parse_attrib = parse_attrib_collada_core_mesh;
this->dom.parse_content = parse_content_collada_core_mesh;
return this;
}
void set_ref_collada_core_source(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_source(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_source(void *obj, size_t index, const char *value){
powergl_collada_core_source *this = (powergl_collada_core_source*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_source(void *obj, size_t index, dom_connector *child){
powergl_collada_core_source *this = (powergl_collada_core_source*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_float_array = powergl_resize(this->c_float_array, ++this->n_float_array, sizeof(powergl_collada_core_float_array*));
this->c_float_array[this->n_float_array-1] = (powergl_collada_core_float_array*)child;
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_int_array = powergl_resize(this->c_int_array, ++this->n_int_array, sizeof(powergl_collada_core_int_array*));
this->c_int_array[this->n_int_array-1] = (powergl_collada_core_int_array*)child;
break;
case 4: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_technique_common = powergl_resize(this->c_technique_common, ++this->n_technique_common, sizeof(powergl_collada_core_source_technique_common*));
this->c_technique_common[this->n_technique_common-1] = (powergl_collada_core_source_technique_common*)child;
break;
}
}
void* new_collada_core_source(void){
powergl_collada_core_source *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_source));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_float_array = NULL; this->n_float_array = 0;
this->c_int_array = NULL; this->n_int_array = 0;
this->c_technique_common = NULL; this->n_technique_common = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[9].map;
this->dom.n_map = g_supported_collada_core_types[9].n_map;
this->dom.add_child = add_child_collada_core_source;
this->dom.set_ref = set_ref_collada_core_source;
this->dom.parse_attrib = parse_attrib_collada_core_source;
this->dom.parse_content = parse_content_collada_core_source;
return this;
}
void set_ref_collada_core_accessor(void *obj, size_t index, dom_connector *ptr){
powergl_collada_core_accessor *this = (powergl_collada_core_accessor*)obj;
switch(index){
case 5: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_float_array = (powergl_collada_core_float_array*)ptr;
break;
case 6: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_int_array = (powergl_collada_core_int_array*)ptr;
break;
}
}
void parse_content_collada_core_accessor(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_accessor(void *obj, size_t index, const char *value){
powergl_collada_core_accessor *this = (powergl_collada_core_accessor*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_source = strlen(value) + 1;
this->c_source = powergl_resize(NULL, this->n_source, sizeof(char));
strcpy(this->c_source, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->c_count = strtoul( value, NULL, 10 );
break;
case 2: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->c_offset = strtoul( value, NULL, 10 );
break;
case 3: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->c_stride = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_accessor(void *obj, size_t index, dom_connector *child){
powergl_collada_core_accessor *this = (powergl_collada_core_accessor*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 4: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_param = powergl_resize(this->c_param, ++this->n_param, sizeof(powergl_collada_core_param*));
this->c_param[this->n_param-1] = (powergl_collada_core_param*)child;
break;
case 5: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 6: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_accessor(void){
powergl_collada_core_accessor *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_accessor));
this->c_source = NULL; this->n_source = 0;
this->c_count = 0;
this->c_offset = 0;
this->c_stride = 0;
this->c_param = NULL; this->n_param = 0;
this->r_float_array = NULL;
this->r_int_array = NULL;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[10].map;
this->dom.n_map = g_supported_collada_core_types[10].n_map;
this->dom.add_child = add_child_collada_core_accessor;
this->dom.set_ref = set_ref_collada_core_accessor;
this->dom.parse_attrib = parse_attrib_collada_core_accessor;
this->dom.parse_content = parse_content_collada_core_accessor;
return this;
}
void set_ref_collada_core_param(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_param(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_param(void *obj, size_t index, const char *value){
powergl_collada_core_param *this = (powergl_collada_core_param*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_sid = strlen(value) + 1;
this->c_sid = powergl_resize(NULL, this->n_sid, sizeof(char));
strcpy(this->c_sid, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
case 2: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_type = strlen(value) + 1;
this->c_type = powergl_resize(NULL, this->n_type, sizeof(char));
strcpy(this->c_type, value);
break;
case 3: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_semantic = strlen(value) + 1;
this->c_semantic = powergl_resize(NULL, this->n_semantic, sizeof(char));
strcpy(this->c_semantic, value);
break;
}
}
void add_child_collada_core_param(void *obj, size_t index, dom_connector *child){
powergl_collada_core_param *this = (powergl_collada_core_param*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_param(void){
powergl_collada_core_param *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_param));
this->c_sid = NULL; this->n_sid = 0;
this->c_name = NULL; this->n_name = 0;
this->c_type = NULL; this->n_type = 0;
this->c_semantic = NULL; this->n_semantic = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[11].map;
this->dom.n_map = g_supported_collada_core_types[11].n_map;
this->dom.add_child = add_child_collada_core_param;
this->dom.set_ref = set_ref_collada_core_param;
this->dom.parse_attrib = parse_attrib_collada_core_param;
this->dom.parse_content = parse_content_collada_core_param;
return this;
}
void set_ref_collada_core_float_array(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_float_array(void *obj, size_t index, const char *value){
powergl_collada_core_float_array *this = (powergl_collada_core_float_array*)obj;
switch(index){
case 0: powergl_collada_parse_content(this->dom.nodes, index, value);
this->content  = powergl_collada_parse_floats(value, &this->n_content);
break;
}
}
void parse_attrib_collada_core_float_array(void *obj, size_t index, const char *value){
powergl_collada_core_float_array *this = (powergl_collada_core_float_array*)obj;
switch(index){
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 2: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
case 3: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->c_count = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_float_array(void *obj, size_t index, dom_connector *child){
powergl_collada_core_float_array *this = (powergl_collada_core_float_array*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_float_array(void){
powergl_collada_core_float_array *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_float_array));
this->content = NULL; this->n_content = 0;
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_count = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[12].map;
this->dom.n_map = g_supported_collada_core_types[12].n_map;
this->dom.add_child = add_child_collada_core_float_array;
this->dom.set_ref = set_ref_collada_core_float_array;
this->dom.parse_attrib = parse_attrib_collada_core_float_array;
this->dom.parse_content = parse_content_collada_core_float_array;
return this;
}
void set_ref_collada_core_int_array(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_int_array(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_int_array(void *obj, size_t index, const char *value){
powergl_collada_core_int_array *this = (powergl_collada_core_int_array*)obj;
switch(index){
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 2: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
case 3: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->c_count = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_int_array(void *obj, size_t index, dom_connector *child){
powergl_collada_core_int_array *this = (powergl_collada_core_int_array*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_int_array(void){
powergl_collada_core_int_array *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_int_array));
this->content = NULL; this->n_content = 0;
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_count = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[13].map;
this->dom.n_map = g_supported_collada_core_types[13].n_map;
this->dom.add_child = add_child_collada_core_int_array;
this->dom.set_ref = set_ref_collada_core_int_array;
this->dom.parse_attrib = parse_attrib_collada_core_int_array;
this->dom.parse_content = parse_content_collada_core_int_array;
return this;
}
void set_ref_collada_core_vertices(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_vertices(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_vertices(void *obj, size_t index, const char *value){
powergl_collada_core_vertices *this = (powergl_collada_core_vertices*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_vertices(void *obj, size_t index, dom_connector *child){
powergl_collada_core_vertices *this = (powergl_collada_core_vertices*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_input = powergl_resize(this->c_input, ++this->n_input, sizeof(powergl_collada_core_input_local*));
this->c_input[this->n_input-1] = (powergl_collada_core_input_local*)child;
break;
}
}
void* new_collada_core_vertices(void){
powergl_collada_core_vertices *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_vertices));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_input = NULL; this->n_input = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[14].map;
this->dom.n_map = g_supported_collada_core_types[14].n_map;
this->dom.add_child = add_child_collada_core_vertices;
this->dom.set_ref = set_ref_collada_core_vertices;
this->dom.parse_attrib = parse_attrib_collada_core_vertices;
this->dom.parse_content = parse_content_collada_core_vertices;
return this;
}
void set_ref_collada_core_triangles(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_triangles(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_triangles(void *obj, size_t index, const char *value){
powergl_collada_core_triangles *this = (powergl_collada_core_triangles*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->c_count = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_triangles(void *obj, size_t index, dom_connector *child){
powergl_collada_core_triangles *this = (powergl_collada_core_triangles*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_input = powergl_resize(this->c_input, ++this->n_input, sizeof(powergl_collada_core_input_local_offset*));
this->c_input[this->n_input-1] = (powergl_collada_core_input_local_offset*)child;
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_p = powergl_resize(this->c_p, ++this->n_p, sizeof(powergl_collada_core_ListOfUInts*));
this->c_p[this->n_p-1] = (powergl_collada_core_ListOfUInts*)child;
break;
}
}
void* new_collada_core_triangles(void){
powergl_collada_core_triangles *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_triangles));
this->c_name = NULL; this->n_name = 0;
this->c_count = 0;
this->c_input = NULL; this->n_input = 0;
this->c_p = NULL; this->n_p = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[15].map;
this->dom.n_map = g_supported_collada_core_types[15].n_map;
this->dom.add_child = add_child_collada_core_triangles;
this->dom.set_ref = set_ref_collada_core_triangles;
this->dom.parse_attrib = parse_attrib_collada_core_triangles;
this->dom.parse_content = parse_content_collada_core_triangles;
return this;
}
void set_ref_collada_core_light(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_light(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_light(void *obj, size_t index, const char *value){
powergl_collada_core_light *this = (powergl_collada_core_light*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_light(void *obj, size_t index, dom_connector *child){
powergl_collada_core_light *this = (powergl_collada_core_light*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_technique_common = powergl_resize(this->c_technique_common, ++this->n_technique_common, sizeof(powergl_collada_core_light_technique_common*));
this->c_technique_common[this->n_technique_common-1] = (powergl_collada_core_light_technique_common*)child;
break;
}
}
void* new_collada_core_light(void){
powergl_collada_core_light *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_light));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_technique_common = NULL; this->n_technique_common = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[16].map;
this->dom.n_map = g_supported_collada_core_types[16].n_map;
this->dom.add_child = add_child_collada_core_light;
this->dom.set_ref = set_ref_collada_core_light;
this->dom.parse_attrib = parse_attrib_collada_core_light;
this->dom.parse_content = parse_content_collada_core_light;
return this;
}
void set_ref_collada_core_directional(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_directional(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_directional(void *obj, size_t index, const char *value){
}
void add_child_collada_core_directional(void *obj, size_t index, dom_connector *child){
powergl_collada_core_directional *this = (powergl_collada_core_directional*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_color = powergl_resize(this->c_color, ++this->n_color, sizeof(powergl_collada_core_targetable_floats*));
this->c_color[this->n_color-1] = (powergl_collada_core_targetable_floats*)child;
break;
}
}
void* new_collada_core_directional(void){
powergl_collada_core_directional *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_directional));
this->c_color = NULL; this->n_color = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[17].map;
this->dom.n_map = g_supported_collada_core_types[17].n_map;
this->dom.add_child = add_child_collada_core_directional;
this->dom.set_ref = set_ref_collada_core_directional;
this->dom.parse_attrib = parse_attrib_collada_core_directional;
this->dom.parse_content = parse_content_collada_core_directional;
return this;
}
void set_ref_collada_core_camera(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_camera(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_camera(void *obj, size_t index, const char *value){
powergl_collada_core_camera *this = (powergl_collada_core_camera*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_camera(void *obj, size_t index, dom_connector *child){
powergl_collada_core_camera *this = (powergl_collada_core_camera*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_optics = powergl_resize(this->c_optics, ++this->n_optics, sizeof(powergl_collada_core_optics*));
this->c_optics[this->n_optics-1] = (powergl_collada_core_optics*)child;
break;
}
}
void* new_collada_core_camera(void){
powergl_collada_core_camera *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_camera));
this->c_id = NULL; this->n_id = 0;
this->c_name = NULL; this->n_name = 0;
this->c_optics = NULL; this->n_optics = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[18].map;
this->dom.n_map = g_supported_collada_core_types[18].n_map;
this->dom.add_child = add_child_collada_core_camera;
this->dom.set_ref = set_ref_collada_core_camera;
this->dom.parse_attrib = parse_attrib_collada_core_camera;
this->dom.parse_content = parse_content_collada_core_camera;
return this;
}
void set_ref_collada_core_optics(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_optics(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_optics(void *obj, size_t index, const char *value){
}
void add_child_collada_core_optics(void *obj, size_t index, dom_connector *child){
powergl_collada_core_optics *this = (powergl_collada_core_optics*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_technique_common = powergl_resize(this->c_technique_common, ++this->n_technique_common, sizeof(powergl_collada_core_optics_technique_common*));
this->c_technique_common[this->n_technique_common-1] = (powergl_collada_core_optics_technique_common*)child;
break;
}
}
void* new_collada_core_optics(void){
powergl_collada_core_optics *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_optics));
this->c_technique_common = NULL; this->n_technique_common = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[19].map;
this->dom.n_map = g_supported_collada_core_types[19].n_map;
this->dom.add_child = add_child_collada_core_optics;
this->dom.set_ref = set_ref_collada_core_optics;
this->dom.parse_attrib = parse_attrib_collada_core_optics;
this->dom.parse_content = parse_content_collada_core_optics;
return this;
}
void set_ref_collada_core_perspective(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_perspective(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_perspective(void *obj, size_t index, const char *value){
}
void add_child_collada_core_perspective(void *obj, size_t index, dom_connector *child){
powergl_collada_core_perspective *this = (powergl_collada_core_perspective*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_xfov = powergl_resize(this->c_xfov, ++this->n_xfov, sizeof(powergl_collada_core_targetable_float*));
this->c_xfov[this->n_xfov-1] = (powergl_collada_core_targetable_float*)child;
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_yfov = powergl_resize(this->c_yfov, ++this->n_yfov, sizeof(powergl_collada_core_targetable_float*));
this->c_yfov[this->n_yfov-1] = (powergl_collada_core_targetable_float*)child;
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_aspect_ratio = powergl_resize(this->c_aspect_ratio, ++this->n_aspect_ratio, sizeof(powergl_collada_core_targetable_float*));
this->c_aspect_ratio[this->n_aspect_ratio-1] = (powergl_collada_core_targetable_float*)child;
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_znear = powergl_resize(this->c_znear, ++this->n_znear, sizeof(powergl_collada_core_targetable_float*));
this->c_znear[this->n_znear-1] = (powergl_collada_core_targetable_float*)child;
break;
case 4: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_zfar = powergl_resize(this->c_zfar, ++this->n_zfar, sizeof(powergl_collada_core_targetable_float*));
this->c_zfar[this->n_zfar-1] = (powergl_collada_core_targetable_float*)child;
break;
}
}
void* new_collada_core_perspective(void){
powergl_collada_core_perspective *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_perspective));
this->c_xfov = NULL; this->n_xfov = 0;
this->c_yfov = NULL; this->n_yfov = 0;
this->c_aspect_ratio = NULL; this->n_aspect_ratio = 0;
this->c_znear = NULL; this->n_znear = 0;
this->c_zfar = NULL; this->n_zfar = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[20].map;
this->dom.n_map = g_supported_collada_core_types[20].n_map;
this->dom.add_child = add_child_collada_core_perspective;
this->dom.set_ref = set_ref_collada_core_perspective;
this->dom.parse_attrib = parse_attrib_collada_core_perspective;
this->dom.parse_content = parse_content_collada_core_perspective;
return this;
}
void set_ref_collada_core_node(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_node(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_node(void *obj, size_t index, const char *value){
powergl_collada_core_node *this = (powergl_collada_core_node*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_id = strlen(value) + 1;
this->c_id = powergl_resize(NULL, this->n_id, sizeof(char));
strcpy(this->c_id, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_sid = strlen(value) + 1;
this->c_sid = powergl_resize(NULL, this->n_sid, sizeof(char));
strcpy(this->c_sid, value);
break;
case 2: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
}
}
void add_child_collada_core_node(void *obj, size_t index, dom_connector *child){
powergl_collada_core_node *this = (powergl_collada_core_node*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_matrix = powergl_resize(this->c_matrix, ++this->n_matrix, sizeof(powergl_collada_core_targetable_floats*));
this->c_matrix[this->n_matrix-1] = (powergl_collada_core_targetable_floats*)child;
break;
case 4: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_instance_camera = powergl_resize(this->c_instance_camera, ++this->n_instance_camera, sizeof(powergl_collada_core_InstanceWithExtra*));
this->c_instance_camera[this->n_instance_camera-1] = (powergl_collada_core_InstanceWithExtra*)child;
break;
case 5: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_instance_light = powergl_resize(this->c_instance_light, ++this->n_instance_light, sizeof(powergl_collada_core_InstanceWithExtra*));
this->c_instance_light[this->n_instance_light-1] = (powergl_collada_core_InstanceWithExtra*)child;
break;
case 6: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_instance_geometry = powergl_resize(this->c_instance_geometry, ++this->n_instance_geometry, sizeof(powergl_collada_core_InstanceWithExtra*));
this->c_instance_geometry[this->n_instance_geometry-1] = (powergl_collada_core_InstanceWithExtra*)child;
break;
}
}
void* new_collada_core_node(void){
powergl_collada_core_node *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_node));
this->c_id = NULL; this->n_id = 0;
this->c_sid = NULL; this->n_sid = 0;
this->c_name = NULL; this->n_name = 0;
this->c_matrix = NULL; this->n_matrix = 0;
this->c_instance_camera = NULL; this->n_instance_camera = 0;
this->c_instance_light = NULL; this->n_instance_light = 0;
this->c_instance_geometry = NULL; this->n_instance_geometry = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[21].map;
this->dom.n_map = g_supported_collada_core_types[21].n_map;
this->dom.add_child = add_child_collada_core_node;
this->dom.set_ref = set_ref_collada_core_node;
this->dom.parse_attrib = parse_attrib_collada_core_node;
this->dom.parse_content = parse_content_collada_core_node;
return this;
}
void set_ref_collada_core_source_technique_common(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_source_technique_common(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_source_technique_common(void *obj, size_t index, const char *value){
}
void add_child_collada_core_source_technique_common(void *obj, size_t index, dom_connector *child){
powergl_collada_core_source_technique_common *this = (powergl_collada_core_source_technique_common*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_accessor = powergl_resize(this->c_accessor, ++this->n_accessor, sizeof(powergl_collada_core_accessor*));
this->c_accessor[this->n_accessor-1] = (powergl_collada_core_accessor*)child;
break;
}
}
void* new_collada_core_source_technique_common(void){
powergl_collada_core_source_technique_common *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_source_technique_common));
this->c_accessor = NULL; this->n_accessor = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[22].map;
this->dom.n_map = g_supported_collada_core_types[22].n_map;
this->dom.add_child = add_child_collada_core_source_technique_common;
this->dom.set_ref = set_ref_collada_core_source_technique_common;
this->dom.parse_attrib = parse_attrib_collada_core_source_technique_common;
this->dom.parse_content = parse_content_collada_core_source_technique_common;
return this;
}
void set_ref_collada_core_light_technique_common(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_light_technique_common(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_light_technique_common(void *obj, size_t index, const char *value){
}
void add_child_collada_core_light_technique_common(void *obj, size_t index, dom_connector *child){
powergl_collada_core_light_technique_common *this = (powergl_collada_core_light_technique_common*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_directional = powergl_resize(this->c_directional, ++this->n_directional, sizeof(powergl_collada_core_directional*));
this->c_directional[this->n_directional-1] = (powergl_collada_core_directional*)child;
break;
}
}
void* new_collada_core_light_technique_common(void){
powergl_collada_core_light_technique_common *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_light_technique_common));
this->c_directional = NULL; this->n_directional = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[23].map;
this->dom.n_map = g_supported_collada_core_types[23].n_map;
this->dom.add_child = add_child_collada_core_light_technique_common;
this->dom.set_ref = set_ref_collada_core_light_technique_common;
this->dom.parse_attrib = parse_attrib_collada_core_light_technique_common;
this->dom.parse_content = parse_content_collada_core_light_technique_common;
return this;
}
void set_ref_collada_core_optics_technique_common(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_optics_technique_common(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_optics_technique_common(void *obj, size_t index, const char *value){
}
void add_child_collada_core_optics_technique_common(void *obj, size_t index, dom_connector *child){
powergl_collada_core_optics_technique_common *this = (powergl_collada_core_optics_technique_common*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
this->c_perspective = powergl_resize(this->c_perspective, ++this->n_perspective, sizeof(powergl_collada_core_perspective*));
this->c_perspective[this->n_perspective-1] = (powergl_collada_core_perspective*)child;
break;
}
}
void* new_collada_core_optics_technique_common(void){
powergl_collada_core_optics_technique_common *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_optics_technique_common));
this->c_perspective = NULL; this->n_perspective = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[24].map;
this->dom.n_map = g_supported_collada_core_types[24].n_map;
this->dom.add_child = add_child_collada_core_optics_technique_common;
this->dom.set_ref = set_ref_collada_core_optics_technique_common;
this->dom.parse_attrib = parse_attrib_collada_core_optics_technique_common;
this->dom.parse_content = parse_content_collada_core_optics_technique_common;
return this;
}
void set_ref_collada_core_InstanceWithExtra(void *obj, size_t index, dom_connector *ptr){
powergl_collada_core_InstanceWithExtra *this = (powergl_collada_core_InstanceWithExtra*)obj;
switch(index){
case 3: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_geometry = (powergl_collada_core_geometry*)ptr;
break;
case 4: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_camera = (powergl_collada_core_camera*)ptr;
break;
case 5: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_light = (powergl_collada_core_light*)ptr;
break;
case 6: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_visual_scene = (powergl_collada_core_visual_scene*)ptr;
break;
}
}
void parse_content_collada_core_InstanceWithExtra(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_InstanceWithExtra(void *obj, size_t index, const char *value){
powergl_collada_core_InstanceWithExtra *this = (powergl_collada_core_InstanceWithExtra*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_sid = strlen(value) + 1;
this->c_sid = powergl_resize(NULL, this->n_sid, sizeof(char));
strcpy(this->c_sid, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_name = strlen(value) + 1;
this->c_name = powergl_resize(NULL, this->n_name, sizeof(char));
strcpy(this->c_name, value);
break;
case 2: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_url = strlen(value) + 1;
this->c_url = powergl_resize(NULL, this->n_url, sizeof(char));
strcpy(this->c_url, value);
break;
}
}
void add_child_collada_core_InstanceWithExtra(void *obj, size_t index, dom_connector *child){
powergl_collada_core_InstanceWithExtra *this = (powergl_collada_core_InstanceWithExtra*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 4: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 5: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 6: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_InstanceWithExtra(void){
powergl_collada_core_InstanceWithExtra *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_InstanceWithExtra));
this->c_sid = NULL; this->n_sid = 0;
this->c_name = NULL; this->n_name = 0;
this->c_url = NULL; this->n_url = 0;
this->r_geometry = NULL;
this->r_camera = NULL;
this->r_light = NULL;
this->r_visual_scene = NULL;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[25].map;
this->dom.n_map = g_supported_collada_core_types[25].n_map;
this->dom.add_child = add_child_collada_core_InstanceWithExtra;
this->dom.set_ref = set_ref_collada_core_InstanceWithExtra;
this->dom.parse_attrib = parse_attrib_collada_core_InstanceWithExtra;
this->dom.parse_content = parse_content_collada_core_InstanceWithExtra;
return this;
}
void set_ref_collada_core_input_local_offset(void *obj, size_t index, dom_connector *ptr){
powergl_collada_core_input_local_offset *this = (powergl_collada_core_input_local_offset*)obj;
switch(index){
case 4: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_source = (powergl_collada_core_source*)ptr;
break;
case 5: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_vertices = (powergl_collada_core_vertices*)ptr;
break;
}
}
void parse_content_collada_core_input_local_offset(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_input_local_offset(void *obj, size_t index, const char *value){
powergl_collada_core_input_local_offset *this = (powergl_collada_core_input_local_offset*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_semantic = strlen(value) + 1;
this->c_semantic = powergl_resize(NULL, this->n_semantic, sizeof(char));
strcpy(this->c_semantic, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_source = strlen(value) + 1;
this->c_source = powergl_resize(NULL, this->n_source, sizeof(char));
strcpy(this->c_source, value);
break;
case 2: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->c_set = strtoul( value, NULL, 10 );
break;
case 3: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->c_offset = strtoul( value, NULL, 10 );
break;
}
}
void add_child_collada_core_input_local_offset(void *obj, size_t index, dom_connector *child){
powergl_collada_core_input_local_offset *this = (powergl_collada_core_input_local_offset*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 3: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 4: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 5: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_input_local_offset(void){
powergl_collada_core_input_local_offset *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_input_local_offset));
this->c_semantic = NULL; this->n_semantic = 0;
this->c_source = NULL; this->n_source = 0;
this->c_set = 0;
this->c_offset = 0;
this->r_source = NULL;
this->r_vertices = NULL;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[26].map;
this->dom.n_map = g_supported_collada_core_types[26].n_map;
this->dom.add_child = add_child_collada_core_input_local_offset;
this->dom.set_ref = set_ref_collada_core_input_local_offset;
this->dom.parse_attrib = parse_attrib_collada_core_input_local_offset;
this->dom.parse_content = parse_content_collada_core_input_local_offset;
return this;
}
void set_ref_collada_core_input_local(void *obj, size_t index, dom_connector *ptr){
powergl_collada_core_input_local *this = (powergl_collada_core_input_local*)obj;
switch(index){
case 2: powergl_collada_set_ref(this->dom.nodes, index, ptr);
this->r_source = (powergl_collada_core_source*)ptr;
break;
}
}
void parse_content_collada_core_input_local(void *obj, size_t index, const char *value){
}
void parse_attrib_collada_core_input_local(void *obj, size_t index, const char *value){
powergl_collada_core_input_local *this = (powergl_collada_core_input_local*)obj;
switch(index){
case 0: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_semantic = strlen(value) + 1;
this->c_semantic = powergl_resize(NULL, this->n_semantic, sizeof(char));
strcpy(this->c_semantic, value);
break;
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_source = strlen(value) + 1;
this->c_source = powergl_resize(NULL, this->n_source, sizeof(char));
strcpy(this->c_source, value);
break;
}
}
void add_child_collada_core_input_local(void *obj, size_t index, dom_connector *child){
powergl_collada_core_input_local *this = (powergl_collada_core_input_local*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 2: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_input_local(void){
powergl_collada_core_input_local *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_input_local));
this->c_semantic = NULL; this->n_semantic = 0;
this->c_source = NULL; this->n_source = 0;
this->r_source = NULL;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[27].map;
this->dom.n_map = g_supported_collada_core_types[27].n_map;
this->dom.add_child = add_child_collada_core_input_local;
this->dom.set_ref = set_ref_collada_core_input_local;
this->dom.parse_attrib = parse_attrib_collada_core_input_local;
this->dom.parse_content = parse_content_collada_core_input_local;
return this;
}
void set_ref_collada_core_ListOfUInts(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_ListOfUInts(void *obj, size_t index, const char *value){
powergl_collada_core_ListOfUInts *this = (powergl_collada_core_ListOfUInts*)obj;
switch(index){
case 0: powergl_collada_parse_content(this->dom.nodes, index, value);
this->content  = powergl_collada_parse_uints(value, &this->n_content);
break;
}
}
void parse_attrib_collada_core_ListOfUInts(void *obj, size_t index, const char *value){
}
void add_child_collada_core_ListOfUInts(void *obj, size_t index, dom_connector *child){
powergl_collada_core_ListOfUInts *this = (powergl_collada_core_ListOfUInts*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_ListOfUInts(void){
powergl_collada_core_ListOfUInts *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_ListOfUInts));
this->content = NULL; this->n_content = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[28].map;
this->dom.n_map = g_supported_collada_core_types[28].n_map;
this->dom.add_child = add_child_collada_core_ListOfUInts;
this->dom.set_ref = set_ref_collada_core_ListOfUInts;
this->dom.parse_attrib = parse_attrib_collada_core_ListOfUInts;
this->dom.parse_content = parse_content_collada_core_ListOfUInts;
return this;
}
void set_ref_collada_core_targetable_floats(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_targetable_floats(void *obj, size_t index, const char *value){
powergl_collada_core_targetable_floats *this = (powergl_collada_core_targetable_floats*)obj;
switch(index){
case 0: powergl_collada_parse_content(this->dom.nodes, index, value);
this->content  = powergl_collada_parse_floats(value, &this->n_content);
break;
}
}
void parse_attrib_collada_core_targetable_floats(void *obj, size_t index, const char *value){
powergl_collada_core_targetable_floats *this = (powergl_collada_core_targetable_floats*)obj;
switch(index){
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_sid = strlen(value) + 1;
this->c_sid = powergl_resize(NULL, this->n_sid, sizeof(char));
strcpy(this->c_sid, value);
break;
}
}
void add_child_collada_core_targetable_floats(void *obj, size_t index, dom_connector *child){
powergl_collada_core_targetable_floats *this = (powergl_collada_core_targetable_floats*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_targetable_floats(void){
powergl_collada_core_targetable_floats *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_targetable_floats));
this->content = NULL; this->n_content = 0;
this->c_sid = NULL; this->n_sid = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[29].map;
this->dom.n_map = g_supported_collada_core_types[29].n_map;
this->dom.add_child = add_child_collada_core_targetable_floats;
this->dom.set_ref = set_ref_collada_core_targetable_floats;
this->dom.parse_attrib = parse_attrib_collada_core_targetable_floats;
this->dom.parse_content = parse_content_collada_core_targetable_floats;
return this;
}
void set_ref_collada_core_targetable_float(void *obj, size_t index, dom_connector *ptr){
}
void parse_content_collada_core_targetable_float(void *obj, size_t index, const char *value){
powergl_collada_core_targetable_float *this = (powergl_collada_core_targetable_float*)obj;
switch(index){
case 0: powergl_collada_parse_content(this->dom.nodes, index, value);
this->content  = powergl_collada_parse_floats(value, &this->n_content);
break;
}
}
void parse_attrib_collada_core_targetable_float(void *obj, size_t index, const char *value){
powergl_collada_core_targetable_float *this = (powergl_collada_core_targetable_float*)obj;
switch(index){
case 1: powergl_collada_parse_attrib(this->dom.nodes, index, value);
this->n_sid = strlen(value) + 1;
this->c_sid = powergl_resize(NULL, this->n_sid, sizeof(char));
strcpy(this->c_sid, value);
break;
}
}
void add_child_collada_core_targetable_float(void *obj, size_t index, dom_connector *child){
powergl_collada_core_targetable_float *this = (powergl_collada_core_targetable_float*)obj;
switch(index){
case 0: powergl_collada_add_child(this->dom.nodes, index, child);
break;
case 1: powergl_collada_add_child(this->dom.nodes, index, child);
break;
}
}
void* new_collada_core_targetable_float(void){
powergl_collada_core_targetable_float *this = powergl_resize(NULL, 1, sizeof(powergl_collada_core_targetable_float));
this->content = NULL; this->n_content = 0;
this->c_sid = NULL; this->n_sid = 0;
this->dom.nodes = NULL;
this->dom.map = g_supported_collada_core_types[30].map;
this->dom.n_map = g_supported_collada_core_types[30].n_map;
this->dom.add_child = add_child_collada_core_targetable_float;
this->dom.set_ref = set_ref_collada_core_targetable_float;
this->dom.parse_attrib = parse_attrib_collada_core_targetable_float;
this->dom.parse_content = parse_content_collada_core_targetable_float;
return this;
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
map_dom_connector map[] = {{ "version", "char*", 1 },{ "xmlns", "char*", 1 },{ "library_geometries", NULL, 0 },{ "library_cameras", NULL, 0 },{ "library_lights", NULL, 0 },{ "library_visual_scenes", NULL, 0 },{ "scene", NULL, 0 },};
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
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "visual_scene", NULL, 0 },};
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
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "camera", NULL, 0 },};
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
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "light", NULL, 0 },};
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
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "geometry", NULL, 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[4].n_map = size;
g_supported_collada_core_types[4].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_COLLADA_scene(){
char str[] = "scene";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[5].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[5].name, str, size * sizeof(char));
char str_parent[] = "COLLADA";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[5].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[5].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[5].get_instance = new_collada_core_scene;
map_dom_connector map[] = {{ "instance_visual_scene", "InstanceWithExtra", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[5].n_map = size;
g_supported_collada_core_types[5].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_visual_scenes_visual_scene(){
char str[] = "visual_scene";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[6].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[6].name, str, size * sizeof(char));
char str_parent[] = "library_visual_scenes";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[6].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[6].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[6].get_instance = new_collada_core_visual_scene;
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "node", NULL, 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[6].n_map = size;
g_supported_collada_core_types[6].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_geometries_geometry(){
char str[] = "geometry";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[7].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[7].name, str, size * sizeof(char));
char str_parent[] = "library_geometries";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[7].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[7].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[7].get_instance = new_collada_core_geometry;
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "mesh", NULL, 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[7].n_map = size;
g_supported_collada_core_types[7].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_geometry_mesh(){
char str[] = "mesh";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[8].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[8].name, str, size * sizeof(char));
char str_parent[] = "geometry";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[8].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[8].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[8].get_instance = new_collada_core_mesh;
map_dom_connector map[] = {{ "source", NULL, 0 },{ "vertices", NULL, 0 },{ "triangles", NULL, 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[8].n_map = size;
g_supported_collada_core_types[8].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_mesh_source(){
char str[] = "source";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[9].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[9].name, str, size * sizeof(char));
char str_parent[] = "mesh";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[9].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[9].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[9].get_instance = new_collada_core_source;
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "float_array", NULL, 0 },{ "int_array", NULL, 0 },{ "technique_common", "source_technique_common", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[9].n_map = size;
g_supported_collada_core_types[9].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_technique_common_accessor(){
char str[] = "accessor";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[10].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[10].name, str, size * sizeof(char));
char str_parent[] = "technique_common";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[10].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[10].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[10].get_instance = new_collada_core_accessor;
map_dom_connector map[] = {{ "source", "char*", 1 },{ "count", "size_t", 1 },{ "offset", "size_t", 1 },{ "stride", "size_t", 1 },{ "param", NULL, 0 },{ "source", "float_array", 3 },{ "source", "int_array", 3 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[10].n_map = size;
g_supported_collada_core_types[10].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_accessor_param(){
char str[] = "param";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[11].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[11].name, str, size * sizeof(char));
char str_parent[] = "accessor";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[11].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[11].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[11].get_instance = new_collada_core_param;
map_dom_connector map[] = {{ "sid", "char*", 1 },{ "name", "char*", 1 },{ "type", "char*", 1 },{ "semantic", "char*", 1 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[11].n_map = size;
g_supported_collada_core_types[11].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_source_float_array(){
char str[] = "float_array";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[12].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[12].name, str, size * sizeof(char));
char str_parent[] = "source";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[12].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[12].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[12].get_instance = new_collada_core_float_array;
map_dom_connector map[] = {{ "content", "double*", 2 },{ "id", "char*", 1 },{ "name", "char*", 1 },{ "count", "size_t", 1 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[12].n_map = size;
g_supported_collada_core_types[12].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_source_int_array(){
char str[] = "int_array";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[13].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[13].name, str, size * sizeof(char));
char str_parent[] = "source";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[13].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[13].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[13].get_instance = new_collada_core_int_array;
map_dom_connector map[] = {{ "content", "int*", 2 },{ "id", "char*", 1 },{ "name", "char*", 1 },{ "count", "size_t", 1 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[13].n_map = size;
g_supported_collada_core_types[13].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_mesh_vertices(){
char str[] = "vertices";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[14].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[14].name, str, size * sizeof(char));
char str_parent[] = "mesh";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[14].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[14].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[14].get_instance = new_collada_core_vertices;
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "input", "input_local", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[14].n_map = size;
g_supported_collada_core_types[14].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_mesh_triangles(){
char str[] = "triangles";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[15].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[15].name, str, size * sizeof(char));
char str_parent[] = "mesh";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[15].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[15].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[15].get_instance = new_collada_core_triangles;
map_dom_connector map[] = {{ "name", "char*", 1 },{ "count", "size_t", 1 },{ "input", "input_local_offset", 0 },{ "p", "ListOfUInts", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[15].n_map = size;
g_supported_collada_core_types[15].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_lights_light(){
char str[] = "light";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[16].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[16].name, str, size * sizeof(char));
char str_parent[] = "library_lights";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[16].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[16].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[16].get_instance = new_collada_core_light;
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "technique_common", "light_technique_common", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[16].n_map = size;
g_supported_collada_core_types[16].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_technique_common_directional(){
char str[] = "directional";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[17].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[17].name, str, size * sizeof(char));
char str_parent[] = "technique_common";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[17].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[17].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[17].get_instance = new_collada_core_directional;
map_dom_connector map[] = {{ "color", "targetable_floats", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[17].n_map = size;
g_supported_collada_core_types[17].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_library_cameras_camera(){
char str[] = "camera";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[18].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[18].name, str, size * sizeof(char));
char str_parent[] = "library_cameras";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[18].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[18].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[18].get_instance = new_collada_core_camera;
map_dom_connector map[] = {{ "id", "char*", 1 },{ "name", "char*", 1 },{ "optics", NULL, 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[18].n_map = size;
g_supported_collada_core_types[18].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_camera_optics(){
char str[] = "optics";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[19].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[19].name, str, size * sizeof(char));
char str_parent[] = "camera";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[19].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[19].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[19].get_instance = new_collada_core_optics;
map_dom_connector map[] = {{ "technique_common", "optics_technique_common", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[19].n_map = size;
g_supported_collada_core_types[19].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_technique_common_perspective(){
char str[] = "perspective";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[20].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[20].name, str, size * sizeof(char));
char str_parent[] = "technique_common";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[20].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[20].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[20].get_instance = new_collada_core_perspective;
map_dom_connector map[] = {{ "xfov", "targetable_float", 0 },{ "yfov", "targetable_float", 0 },{ "aspect_ratio", "targetable_float", 0 },{ "znear", "targetable_float", 0 },{ "zfar", "targetable_float", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[20].n_map = size;
g_supported_collada_core_types[20].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_visual_scene_node(){
char str[] = "node";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[21].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[21].name, str, size * sizeof(char));
char str_parent[] = "visual_scene";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[21].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[21].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[21].get_instance = new_collada_core_node;
map_dom_connector map[] = {{ "id", "char*", 1 },{ "sid", "char*", 1 },{ "name", "char*", 1 },{ "matrix", "targetable_floats", 0 },{ "instance_camera", "InstanceWithExtra", 0 },{ "instance_light", "InstanceWithExtra", 0 },{ "instance_geometry", "InstanceWithExtra", 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[21].n_map = size;
g_supported_collada_core_types[21].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_source_technique_common(){
char str[] = "source_technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[22].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[22].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[22].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[22].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[22].get_instance = new_collada_core_source_technique_common;
map_dom_connector map[] = {{ "accessor", NULL, 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[22].n_map = size;
g_supported_collada_core_types[22].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_light_technique_common(){
char str[] = "light_technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[23].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[23].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[23].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[23].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[23].get_instance = new_collada_core_light_technique_common;
map_dom_connector map[] = {{ "directional", NULL, 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[23].n_map = size;
g_supported_collada_core_types[23].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_optics_technique_common(){
char str[] = "optics_technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[24].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[24].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[24].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[24].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[24].get_instance = new_collada_core_optics_technique_common;
map_dom_connector map[] = {{ "perspective", NULL, 0 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[24].n_map = size;
g_supported_collada_core_types[24].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_InstanceWithExtra(){
char str[] = "InstanceWithExtra";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[25].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[25].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[25].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[25].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[25].get_instance = new_collada_core_InstanceWithExtra;
map_dom_connector map[] = {{ "sid", "char*", 1 },{ "name", "char*", 1 },{ "url", "char*", 1 },{ "url", "geometry", 3 },{ "url", "camera", 3 },{ "url", "light", 3 },{ "url", "visual_scene", 3 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[25].n_map = size;
g_supported_collada_core_types[25].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_input_local_offset(){
char str[] = "input_local_offset";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[26].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[26].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[26].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[26].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[26].get_instance = new_collada_core_input_local_offset;
map_dom_connector map[] = {{ "semantic", "char*", 1 },{ "source", "char*", 1 },{ "set", "size_t", 1 },{ "offset", "size_t", 1 },{ "source", "source", 3 },{ "source", "vertices", 3 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[26].n_map = size;
g_supported_collada_core_types[26].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_input_local(){
char str[] = "input_local";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[27].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[27].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[27].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[27].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[27].get_instance = new_collada_core_input_local;
map_dom_connector map[] = {{ "semantic", "char*", 1 },{ "source", "char*", 1 },{ "source", "source", 3 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[27].n_map = size;
g_supported_collada_core_types[27].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_ListOfUInts(){
char str[] = "ListOfUInts";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[28].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[28].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[28].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[28].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[28].get_instance = new_collada_core_ListOfUInts;
map_dom_connector map[] = {{ "content", "size_t*", 2 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[28].n_map = size;
g_supported_collada_core_types[28].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_targetable_floats(){
char str[] = "targetable_floats";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[29].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[29].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[29].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[29].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[29].get_instance = new_collada_core_targetable_floats;
map_dom_connector map[] = {{ "content", "double*", 2 },{ "sid", "char*", 1 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[29].n_map = size;
g_supported_collada_core_types[29].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_0_targetable_float(){
char str[] = "targetable_float";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[30].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[30].name, str, size * sizeof(char));
char str_parent[] = "0";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[30].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[30].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[30].get_instance = new_collada_core_targetable_float;
map_dom_connector map[] = {{ "content", "double*", 2 },{ "sid", "char*", 1 },};
size = sizeof map / sizeof(map_dom_connector);
g_supported_collada_core_types[30].n_map = size;
g_supported_collada_core_types[30].map = powergl_resize(NULL, size, sizeof(map_dom_connector));
memcpy(g_supported_collada_core_types[g_n_supported_collada_core_types++].map, map, size * sizeof(map_dom_connector));
}
static void support_collada_core_type_source_technique_common(){
char str[] = "technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[31].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[31].name, str, size * sizeof(char));
char str_parent[] = "source";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[31].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[31].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[31].get_instance = new_collada_core_source_technique_common;
g_supported_collada_core_types[31].n_map = g_supported_collada_core_types[22].n_map;
g_supported_collada_core_types[31].map = g_supported_collada_core_types[22].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_light_technique_common(){
char str[] = "technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[32].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[32].name, str, size * sizeof(char));
char str_parent[] = "light";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[32].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[32].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[32].get_instance = new_collada_core_light_technique_common;
g_supported_collada_core_types[32].n_map = g_supported_collada_core_types[23].n_map;
g_supported_collada_core_types[32].map = g_supported_collada_core_types[23].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_optics_technique_common(){
char str[] = "technique_common";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[33].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[33].name, str, size * sizeof(char));
char str_parent[] = "optics";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[33].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[33].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[33].get_instance = new_collada_core_optics_technique_common;
g_supported_collada_core_types[33].n_map = g_supported_collada_core_types[24].n_map;
g_supported_collada_core_types[33].map = g_supported_collada_core_types[24].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_triangles_input(){
char str[] = "input";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[34].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[34].name, str, size * sizeof(char));
char str_parent[] = "triangles";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[34].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[34].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[34].get_instance = new_collada_core_input_local_offset;
g_supported_collada_core_types[34].n_map = g_supported_collada_core_types[26].n_map;
g_supported_collada_core_types[34].map = g_supported_collada_core_types[26].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_vertices_input(){
char str[] = "input";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[35].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[35].name, str, size * sizeof(char));
char str_parent[] = "vertices";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[35].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[35].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[35].get_instance = new_collada_core_input_local;
g_supported_collada_core_types[35].n_map = g_supported_collada_core_types[27].n_map;
g_supported_collada_core_types[35].map = g_supported_collada_core_types[27].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_instance_camera(){
char str[] = "instance_camera";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[36].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[36].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[36].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[36].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[36].get_instance = new_collada_core_InstanceWithExtra;
g_supported_collada_core_types[36].n_map = g_supported_collada_core_types[25].n_map;
g_supported_collada_core_types[36].map = g_supported_collada_core_types[25].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_instance_geometry(){
char str[] = "instance_geometry";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[37].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[37].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[37].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[37].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[37].get_instance = new_collada_core_InstanceWithExtra;
g_supported_collada_core_types[37].n_map = g_supported_collada_core_types[25].n_map;
g_supported_collada_core_types[37].map = g_supported_collada_core_types[25].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_instance_light(){
char str[] = "instance_light";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[38].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[38].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[38].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[38].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[38].get_instance = new_collada_core_InstanceWithExtra;
g_supported_collada_core_types[38].n_map = g_supported_collada_core_types[25].n_map;
g_supported_collada_core_types[38].map = g_supported_collada_core_types[25].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_scene_instance_visual_scene(){
char str[] = "instance_visual_scene";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[39].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[39].name, str, size * sizeof(char));
char str_parent[] = "scene";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[39].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[39].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[39].get_instance = new_collada_core_InstanceWithExtra;
g_supported_collada_core_types[39].n_map = g_supported_collada_core_types[25].n_map;
g_supported_collada_core_types[39].map = g_supported_collada_core_types[25].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_triangles_p(){
char str[] = "p";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[40].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[40].name, str, size * sizeof(char));
char str_parent[] = "triangles";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[40].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[40].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[40].get_instance = new_collada_core_ListOfUInts;
g_supported_collada_core_types[40].n_map = g_supported_collada_core_types[28].n_map;
g_supported_collada_core_types[40].map = g_supported_collada_core_types[28].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_directional_color(){
char str[] = "color";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[41].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[41].name, str, size * sizeof(char));
char str_parent[] = "directional";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[41].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[41].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[41].get_instance = new_collada_core_targetable_floats;
g_supported_collada_core_types[41].n_map = g_supported_collada_core_types[29].n_map;
g_supported_collada_core_types[41].map = g_supported_collada_core_types[29].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_node_matrix(){
char str[] = "matrix";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[42].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[42].name, str, size * sizeof(char));
char str_parent[] = "node";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[42].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[42].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[42].get_instance = new_collada_core_targetable_floats;
g_supported_collada_core_types[42].n_map = g_supported_collada_core_types[29].n_map;
g_supported_collada_core_types[42].map = g_supported_collada_core_types[29].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_xfov(){
char str[] = "xfov";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[43].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[43].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[43].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[43].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[43].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[43].n_map = g_supported_collada_core_types[30].n_map;
g_supported_collada_core_types[43].map = g_supported_collada_core_types[30].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_yfov(){
char str[] = "yfov";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[44].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[44].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[44].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[44].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[44].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[44].n_map = g_supported_collada_core_types[30].n_map;
g_supported_collada_core_types[44].map = g_supported_collada_core_types[30].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_aspect_ratio(){
char str[] = "aspect_ratio";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[45].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[45].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[45].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[45].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[45].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[45].n_map = g_supported_collada_core_types[30].n_map;
g_supported_collada_core_types[45].map = g_supported_collada_core_types[30].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_znear(){
char str[] = "znear";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[46].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[46].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[46].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[46].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[46].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[46].n_map = g_supported_collada_core_types[30].n_map;
g_supported_collada_core_types[46].map = g_supported_collada_core_types[30].map;
g_n_supported_collada_core_types++;
}
static void support_collada_core_type_perspective_zfar(){
char str[] = "zfar";
size_t size = sizeof str / sizeof(char);
g_supported_collada_core_types[47].name = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[47].name, str, size * sizeof(char));
char str_parent[] = "perspective";
size = sizeof str_parent / sizeof(char);
g_supported_collada_core_types[47].parent = powergl_resize(NULL, size, sizeof(char));
memcpy(g_supported_collada_core_types[47].parent, str_parent, size * sizeof(char));
g_supported_collada_core_types[47].get_instance = new_collada_core_targetable_float;
g_supported_collada_core_types[47].n_map = g_supported_collada_core_types[30].n_map;
g_supported_collada_core_types[47].map = g_supported_collada_core_types[30].map;
g_n_supported_collada_core_types++;
}
void powergl_collada_core_init(){
support_collada_core_type_COLLADA_COLLADA();
support_collada_core_type_COLLADA_library_visual_scenes();
support_collada_core_type_COLLADA_library_cameras();
support_collada_core_type_COLLADA_library_lights();
support_collada_core_type_COLLADA_library_geometries();
support_collada_core_type_COLLADA_scene();
support_collada_core_type_library_visual_scenes_visual_scene();
support_collada_core_type_library_geometries_geometry();
support_collada_core_type_geometry_mesh();
support_collada_core_type_mesh_source();
support_collada_core_type_technique_common_accessor();
support_collada_core_type_accessor_param();
support_collada_core_type_source_float_array();
support_collada_core_type_source_int_array();
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
support_collada_core_type_node_instance_camera();
support_collada_core_type_node_instance_geometry();
support_collada_core_type_node_instance_light();
support_collada_core_type_scene_instance_visual_scene();
support_collada_core_type_triangles_p();
support_collada_core_type_directional_color();
support_collada_core_type_node_matrix();
support_collada_core_type_perspective_xfov();
support_collada_core_type_perspective_yfov();
support_collada_core_type_perspective_aspect_ratio();
support_collada_core_type_perspective_znear();
support_collada_core_type_perspective_zfar();
}
