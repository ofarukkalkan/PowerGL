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
    this->objects = powergl_resize( NULL, sizeof( powergl_rendering_object * ) * size );
    this->n_object = size;
    this->dae_file = powergl_resize( NULL, sizeof(char) * ( strlen(file) + 1 ) );
    strcpy(this->dae_file, file);
    for ( size_t i = 0; i < size; i++ )
        {
            powergl_collada_core_node  *node = vscene->c_node[i];
            this->objects[i] = powergl_resize( NULL, sizeof( powergl_rendering_object ) );
            powergl_rendering_object_create( this->objects[i], NULL );
            powergl_build_object( node, this->objects[i]);
        } // for each node
}

powergl_rendering_object * powergl_new_object_from_lib(powergl_objectlibrary *lib, const char *id)
{
    for ( size_t i = 0; i < lib->n_object; i++ )
        {
            if ( strcmp(lib->objects[i]->id, id) == 0 )
                {
                    powergl_rendering_object *obj = powergl_resize(NULL, sizeof(powergl_rendering_object));
                    powergl_rendering_object_create( obj, NULL );
                    powergl_rendering_object_copy(obj, lib->objects[i]);
                    return obj;
                }
        }
    return NULL;
}

powergl_rendering_geometry * powergl_get_geometry_from_lib(powergl_objectlibrary *lib, const char *id, size_t geo_index)
{
    for ( size_t i = 0; i < lib->n_object; i++ )
        {
            if ( strcmp(lib->objects[i]->id, id) == 0 )
                {
                    return lib->objects[i]->geometry[geo_index];
                }
        }
    assert(0);
}
