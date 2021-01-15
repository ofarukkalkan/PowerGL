#include "objectlibrary.h"
#include "../collada/collada.h"
#include "../collada/importer.h"
#include "dae2object.h"

powergl_object_library * powergl_object_library_build(const char *file){

#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    printf("the dae file will be parsed = %s \n", file);
#endif
    powergl_collada_core_COLLADA  *root = (powergl_collada_core_COLLADA *)powergl_collada_parse(file);
    powergl_collada_core_scene  *scene = root->c_scene[0];
    powergl_collada_core_InstanceWithExtra  *instance = scene->c_instance_visual_scene[0];
    powergl_collada_core_visual_scene  *vscene =  instance->r_visual_scene;


    size_t size = vscene->n_node;
    powergl_object_library *lib = powergl_resize(NULL, 1, sizeof(powergl_object_library));
    lib->objects = powergl_resize(NULL, size, sizeof(powergl_object *));
    lib->n_object = size;

    for(size_t i = 0; i < size; i++) {
        powergl_collada_core_node  *node = vscene->c_node[i];
        lib->objects[i] = powergl_resize(NULL, 1, sizeof(powergl_object));
	lib->objects[i]->parent = NULL;
	
        powergl_build_object(node, root, lib->objects[i]);

    } // for each node

    return lib;
}

powergl_object * powergl_object_library_find_object(powergl_object_library *lib, const char *id){

  assert(lib);
  
  for(size_t i=0; i < lib->n_object; i++){
    if(strcmp(lib->objects[i]->id, id) == 0){
      return lib->objects[i];
    }
  }

}

