#include "object.h"
#include "../math/mat4x4.h"

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

	geometry->color = NULL;
	geometry->color_flag = 0;
	geometry->n_color = 0;
	
	geometry->index = NULL;
	geometry->index_flag = 0;
	geometry->n_index = 0;
}

int powergl_rendering_object_create( powergl_rendering_object *obj ) {
	obj->matrix_flag = 0;
	powergl_zero4x4( obj->matrix );
	powergl_zero4x4( obj->mvp );
	obj->geometry = NULL;
	obj->camera = NULL;
}

int powergl_rendering_object_run( powergl_rendering_object *obj ) {
	/*
  GLfloat tmp[4][4];
	powergl_vec3 rotaxis={0.0f,1.0f,0.0f};
	powergl_rot4x4(obj->matrix,tmp,0.0011f,&rotaxis);
  obj->matrix_flag=1;
	*/
}
