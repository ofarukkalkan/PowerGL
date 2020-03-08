#include "objectlibrary.h"
#include "dae2object.h"
#include "../collada/importer.h"

void powergl_build_lib_from_dae(powergl_objectlibrary *this, const char *file)
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
    printf( "the dae file will be parsed = %s \n", file );
#endif
    powergl_collada_core_COLLADA *root = (powergl_collada_core_COLLADA*)powergl_collada_parse(file);
    powergl_collada_core_scene *scene = root->c_scene[0];
    powergl_collada_core_InstanceWithExtra *instance = scene->c_instance_visual_scene[0];
    powergl_collada_core_visual_scene *vscene = instance->r_visual_scene;
    size_t size = vscene->n_node;
    this->objects = powergl_resize( NULL, size, sizeof( powergl_object * ));
    this->n_object = size;
    this->dae_file = powergl_resize( NULL, ( strlen(file) + 1 ), sizeof(char) );
    strcpy(this->dae_file, file);
    for ( size_t i = 0; i < size; i++ )
        {
            powergl_collada_core_node  *node = vscene->c_node[i];
            this->objects[i] = powergl_resize( NULL, 1, sizeof( powergl_object ) );
            powergl_build_object( node, this->objects[i]);
        } // for each node
}
