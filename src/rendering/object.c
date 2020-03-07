#include "object.h"
#include "../math/mat4x4.h"
#include <string.h>

int powergl_rendering_light_create( powergl_rendering_light *light )
{
    return 0;
}

int powergl_rendering_camera_create( powergl_rendering_camera *camera )
{
    powergl_zero4x4( camera->view );
    camera->view_flag = 0;
    powergl_zero4x4( camera->projection );
    camera->projection_flag = 0;
    powergl_zero4x4( camera->vp );
    return 0;
}

int powergl_rendering_geometry_create( powergl_rendering_geometry *geometry )
{
    geometry->vertex = NULL;
    geometry->vertex_flag = 0;
    geometry->n_vertex = 0;
    geometry->normal = NULL;
    geometry->normal_flag = 0;
    geometry->n_normal = 0;
    geometry->color = NULL;
    geometry->color_flag = 0;
    geometry->n_color = 0;
    geometry->index = NULL;
    geometry->index_flag = 0;
    geometry->n_index = 0;
    return 0;
}

void powergl_rendering_object_create( powergl_rendering_object *obj, powergl_rendering_object *parent )
{
    obj->parent = parent;
    obj->matrix_flag = 0;
    obj->rotation_flag = 0;
    powergl_ident4x4( obj->matrix );
    powergl_ident4x4( obj->mvp );
    obj->geometry = NULL;
    obj->n_geometry = 0;
    obj->camera = NULL;
    obj->light = NULL;
    obj->children = NULL;
    obj->n_child = 0;
    obj->id = NULL;
    obj->name = NULL;
}

void powergl_rendering_light_copy( powergl_rendering_light *dest, const powergl_rendering_light *src)
{
    dest->dir[0] = src->dir[0];
    dest->dir[1] = src->dir[1];
    dest->dir[2] = src->dir[2];
    dest->dir_flag = src->dir_flag;
    dest->color[0] = src->color[0];
    dest->color[1] = src->color[1];
    dest->color[2] = src->color[2];
    dest->color_flag = src->color_flag;
    dest->type = src->type;
}

void powergl_rendering_camera_copy( powergl_rendering_camera *dest, const powergl_rendering_camera *src)
{
    dest->xfov = src->xfov;
    dest->yfov = src->yfov;
    dest->xmag = src->xmag;
    dest->ymag = src->ymag;
    dest->aspect_ratio = src->aspect_ratio;
    dest->znear = src->znear;
    dest->zfar = src->zfar;
    powergl_copy4x4(dest->vp, src->vp);
    powergl_copy4x4(dest->projection, src->projection);
    dest->projection_flag = src->projection_flag;
    powergl_copy4x4(dest->view, src->view);
    dest->view_flag = src->view_flag;
    dest->type = src->type;
}

void powergl_rendering_geometry_copy( powergl_rendering_geometry *dest, const powergl_rendering_geometry *src)
{
    dest->vertex = powergl_resize(NULL, sizeof(powergl_vec3) * src->n_vertex);
    dest->n_vertex = src->n_vertex;
    dest->vertex_flag = src->vertex_flag;
    for ( size_t i = 0; i < src->n_vertex; i++ )
        {
            powergl_copyvec3(&dest->vertex[i], &src->vertex[i]);
        }
    dest->normal = powergl_resize(NULL, sizeof(powergl_vec3) * src->n_normal);
    dest->n_normal = src->n_normal;
    dest->normal_flag = src->normal_flag;
    for ( size_t i = 0; i < src->n_normal; i++ )
        {
            powergl_copyvec3(&dest->normal[i], &src->normal[i]);
        }
    dest->color = powergl_resize(NULL, sizeof(powergl_vec3) * src->n_color);
    dest->n_color = src->n_color;
    dest->color_flag = src->color_flag;
    for ( size_t i = 0; i < src->n_color; i++ )
        {
            powergl_copyvec3(&dest->color[i], &src->color[i]);
        }
    dest->index = powergl_resize(NULL, sizeof(GLuint) * src->n_index);
    dest->n_index = src->n_index;
    dest->index_flag = src->index_flag;
    for ( size_t i = 0; i < src->n_index; i++ )
        {
            dest->index[i] = src->index[i];
        }
}

void powergl_rendering_object_copy( powergl_rendering_object *dest, const powergl_rendering_object *src)
{
    dest->create = src->create;
    dest->run = src->run;
    dest->id = powergl_resize(NULL,sizeof(char) * (strlen(src->id) + 1));
    strcpy(dest->id, src->id);
    powergl_copy4x4(dest->matrix, src->matrix);
    dest->matrix_flag = src->matrix_flag;
    dest->n_geometry = src->n_geometry;
    if ( src->geometry != NULL )
        {
            dest->geometry = powergl_resize(NULL, sizeof(powergl_rendering_geometry*) * src->n_geometry);
            for ( size_t i = 0; i < src->n_geometry; i++ )
                {
                    dest->geometry[i] = powergl_resize(NULL, sizeof(powergl_rendering_geometry));
                    powergl_rendering_geometry_copy(dest->geometry[i], src->geometry[i]);
                }
        }
    if ( src->camera != NULL )
        {
            dest->camera = powergl_resize(NULL, sizeof(powergl_rendering_camera));
            powergl_rendering_camera_copy(dest->camera, src->camera);
        }
    if ( src->light != NULL)
        {
            dest->light = powergl_resize(NULL, sizeof(powergl_rendering_light));
            powergl_rendering_light_copy(dest->light, src->light);
        }
    dest->n_child = src->n_child;
    if ( src->children != NULL )
        {
            dest->children = powergl_resize(NULL, sizeof(powergl_rendering_object*) * src->n_child);
            for ( size_t i = 0; i < src->n_child; i++ )
                {
                    dest->children[i] = powergl_resize(NULL, sizeof(powergl_rendering_object));
                    powergl_rendering_object_copy(dest->children[i], src->children[i]);
                }
        }
    dest->parent = src->parent;
}

int powergl_rendering_object_rotate( powergl_rendering_object *obj, float axisx,float axisy,float axisz, float radians )
{
    GLfloat rotation[4][4];
    powergl_ident4x4(rotation);
    powergl_vec3 rotaxis = {axisx, axisy, axisy};
    powergl_rot4x4(rotation, radians, &rotaxis);
    powergl_rot4x4(obj->matrix, radians, &rotaxis);
    for ( size_t i = 0; i < obj->n_geometry; i++ )
        {
            if ( obj->geometry[i] != NULL && obj->geometry[i]->normal != NULL )
                {
                    powergl_rendering_geometry_transform_normals(obj->geometry[i], rotation);
                }
        }
    obj->matrix_flag = 1;
    return 0;
}

int powergl_rendering_geometry_transform_normals(powergl_rendering_geometry *geo, GLfloat m[4][4])
{
    GLfloat v[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat result[4];
    for ( size_t i=0; i < geo->n_normal; i++ )
        {
            v[0] = geo->normal[i].x;
            v[1] = geo->normal[i].y;
            v[2] = geo->normal[i].z;
            powergl_transformvec4(v, m, result);
            geo->normal[i].x = result[0];
            geo->normal[i].y = result[1];
            geo->normal[i].z = result[2];
        }
    geo->normal_flag = 1;
    return 0;
}


void powergl_rendering_object_run( powergl_rendering_object *obj )
{
    if ( obj->parent != NULL && obj->parent->matrix_flag == 1 )
        {
            obj->matrix_flag = 1;
        }
    for ( size_t i = 0; i < obj->n_child; i++ )
        {
            obj->run(obj->children[i]);
        }
}
