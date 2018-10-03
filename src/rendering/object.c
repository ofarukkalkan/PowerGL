#include "object.h"
#include "../math/mat4x4.h"

int powergl_rendering_light_create( powergl_rendering_light *light ) {
	

}

int powergl_rendering_camera_create( powergl_rendering_camera *camera ) {

  powergl_zero4x4( camera->view );
  camera->view_flag = 0;

  powergl_zero4x4( camera->projection );
  camera->projection_flag = 0;

  powergl_zero4x4( camera->vp );

}

int powergl_rendering_geometry_create( powergl_rendering_geometry *geometry ) {
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
}

int powergl_rendering_object_create( powergl_rendering_object *obj, powergl_rendering_object *parent ) {
  obj->parent = parent;
  
  obj->matrix_flag = 0;
  obj->rotation_flag = 0;
  
  powergl_zero4x4( obj->matrix );
  powergl_zero4x4( obj->mvp );
  
  obj->geometry = NULL;
  obj->n_geometry = 0;
  
  obj->camera = NULL;
  obj->light = NULL;

  obj->children = NULL;
  obj->n_child = 0;
}

int powergl_rendering_object_rotate( powergl_rendering_object *obj, float axisx,float axisy,float axisz, float radians ) {
  GLfloat rotation[4][4];
  
  powergl_ident4x4(rotation);
  powergl_vec3 rotaxis = {axisx, axisy, axisy};
  powergl_rot4x4(rotation, radians, &rotaxis);
  powergl_rot4x4(obj->matrix, radians, &rotaxis);
  
  for ( size_t i = 0; i < obj->n_geometry; i++ ) {

    if ( obj->geometry[i] != NULL && obj->geometry[i]->normal != NULL ) {
      powergl_rendering_geometry_transform_normals(obj->geometry[i], rotation);
    }
  }
  
  obj->matrix_flag = 1;
}

int powergl_rendering_geometry_transform_normals(powergl_rendering_geometry *geo, GLfloat m[4][4]){
  GLfloat v[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
  GLfloat result[4];
  for ( size_t i=0; i < geo->n_normal; i++ ) {
    v[0] = geo->normal[i].x;
    v[1] = geo->normal[i].y;
    v[2] = geo->normal[i].z;
    powergl_transformvec4(v, m, result);
    geo->normal[i].x = result[0];
    geo->normal[i].y = result[1];
    geo->normal[i].z = result[2];
  }
  geo->normal_flag = 1;
}


int powergl_rendering_object_run( powergl_rendering_object *obj ) {
  
  /* if ( obj->parent == NULL ) { */
  /*   powergl_rendering_object_rotate(obj, 1.0f, 0.0f, 0.0f, 0.001f); */
  /* } */
  
  if ( obj->parent != NULL && obj->parent->matrix_flag == 1 ) {
    obj->matrix_flag = 1;
  }
  
  for ( size_t i = 0; i < obj->n_child; i++ ) {
    powergl_rendering_object_run(obj->children[i]);
  }
  
}
