#include "visualscene.h"

#include "../powergl.h"
#include "../collada/collada.h"
#include "../collada/importer.h"
#include "dae2object.h"

#include <stdio.h>
#include <string.h>


void powergl_scene_build(powergl_visualscene *this, const char *file) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    printf("the dae file will be parsed = %s \n", file);
#endif
    powergl_collada_core_COLLADA  *root = (powergl_collada_core_COLLADA *)powergl_collada_parse(file);
    powergl_collada_core_scene  *scene = root->c_scene[0];
    powergl_collada_core_InstanceWithExtra  *instance = scene->c_instance_visual_scene[0];
    powergl_collada_core_visual_scene  *vscene =  instance->r_visual_scene;

    
    size_t size = vscene->n_node;
    this->objects = powergl_resize(NULL, size, sizeof(powergl_object *));
    this->n_object = size;
    this->main_camera = NULL;
    this->main_light = NULL;

    for(size_t i = 0; i < size; i++) {
        powergl_collada_core_node  *node = vscene->c_node[i];
        this->objects[i] = powergl_resize(NULL, 1, sizeof(powergl_object));
	this->objects[i]->parent = NULL;
	
        powergl_build_object(node, root, this->objects[i]);

    } // for each node
}

static powergl_object *find_object(powergl_object *root, const char *id){

  powergl_object *res = NULL;

  if(strcmp(id, root->id) == 0){
    return root;
  }

  for(size_t i = 0; i < root->n_object; i++) {
    res = find_object(root->objects[i], id);
    if( res != NULL) {
      return res;
    }   
  }

  return NULL;
}

powergl_object *powergl_scene_find(powergl_visualscene *scene, const char *id) {
  powergl_object *res = NULL;
  
  for(size_t i = 0; i < scene->n_object; i++) {
      
    res = find_object(scene->objects[i], id);
    if( res != NULL) {
      return res;
    }
  }

  return NULL;
}
