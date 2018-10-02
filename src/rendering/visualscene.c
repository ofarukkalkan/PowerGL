#include "visualscene.h"

#include "../powergl.h"
#include "../asset/collada.h"
#include "../math/mat4x4.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#define DEBUG_OUTPUT 0

static const size_t powergl_vertex_offset = 0;
static const size_t powergl_normal_offset = 1;
static const size_t powergl_color_offset = 2;
static const size_t powergl_vertex_input_supported = 3;

static float to_radians( float degrees ) {
  return degrees * ( 3.141592f / 180.0f );
}

static void build_geometry_triangle_index( powergl_rendering_geometry *obj, collada_type( triangles ) *triangles, collada_type( input_local_offset ) *vertex_input, collada_type( input_local_offset ) *color_input, collada_type( input_local_offset ) *normal_input ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  // how many triangles are there in _ imported file _
  size_t p_count = triangles->a_count.value;

  // offset values for each vertex attribute
  size_t vertex_offset = vertex_input->a_offset.value;
  size_t color_offset;
  size_t normal_offset;

  if ( color_input != NULL ) {
    color_offset = color_input->a_offset.value;
  } else {
    fprintf(stderr, "no color input found \n" );
  }

  if ( normal_input != NULL ) {
    normal_offset = normal_input->a_offset.value;
  } else {
    fprintf(stderr, "no normal input found \n" );
  }

  // vertex count 3 = triangle has 3 vertex
  size_t vertex_count = 3 * p_count;

  // total index count
  size_t n_index = vertex_count * powergl_vertex_input_supported;

  obj->index = powergl_resize( NULL, sizeof( GLuint ) * n_index );

  // get xml collada_type that contains index values
  collada_type( p ) *p_arr = triangles->c_p;

  // each triangle has how many vertex attribute in _ imported file _
  size_t input_count = p_arr->_base.value_size / ( 3 * p_count );

  for ( size_t l = 0; l < vertex_count; l++ ) {

    // this index array is building vbo, ibo and cbo sources
    obj->index[ l * powergl_vertex_input_supported + powergl_vertex_offset ] = p_arr->_ext.value[ l * input_count  + vertex_offset ];

    if ( normal_input != NULL ) {
      obj->index[ l * powergl_vertex_input_supported + powergl_normal_offset ] = p_arr->_ext.value[ l * input_count  + normal_offset ];
    }

    if ( color_input != NULL ) {
      obj->index[ l * powergl_vertex_input_supported + powergl_color_offset ] = p_arr->_ext.value[ l * input_count  + color_offset ];
    }
#if DEBUG_OUTPUT
    printf( "%u %u %u ", obj->index[ l * powergl_vertex_input_supported +  powergl_vertex_offset ], obj->index[ l * powergl_vertex_input_supported + powergl_normal_offset], obj->index[ l * powergl_vertex_input_supported + powergl_color_offset] );
#endif

  } // copy indices from p collada_type for each vertex

  obj->index_flag = 1;
  obj->n_index = n_index;

}

static void build_geometry_triangle_color( powergl_rendering_geometry *obj, collada_type( triangles ) *triangles, collada_type( input_local_offset ) *color_input ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  
  collada_type( source ) *src = ( collada_type( source ) * )color_input->r_source.ptr;
  collada_type( accessor ) *srcAcc = src->c_source_technique_common->c_accessor;

  if ( srcAcc->r_float_array.ptr != NULL ) {

    collada_type( float_array ) *float_arr = ( collada_type( float_array ) * ) srcAcc->r_float_array.ptr;

    size_t stride = srcAcc->a_stride.value;

    if ( stride == 0 )
      stride = 1; // stride is must greater than 0 and default is 1

    // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid

    collada_type( param ) **params = srcAcc->ch_param;
    int offsets[3] = { -1, -1, -1};

    for ( int k = 0; k < srcAcc->n_param; k++ ) {

      if ( strlen( params[k]->a_name.value ) > 0 ) {

        if ( strncmp( params[k]->a_name.value, "R", 1 ) == 0 ) {

          offsets[0] = k;

        } else if ( strncmp( params[k]->a_name.value, "G", 1 ) == 0 ) {

          offsets[1] = k;

        } else if ( strncmp( params[k]->a_name.value, "B", 1 ) == 0 ) {

          offsets[2] = k;

        }

      }

    }

    size_t p_count = triangles->a_count.value;
    size_t vertex_count = p_count * 3;

    obj->color = powergl_resize( NULL, sizeof( powergl_vec3 ) * vertex_count );

    for ( size_t i = 0; i < vertex_count ; i++ ) {

      size_t index = obj->index[ i * powergl_vertex_input_supported + powergl_color_offset ];

      if ( offsets[ 0 ] > -1 )
        obj->color[ i ].x = float_arr->_ext.value[ index * stride + offsets[0] ];
      if ( offsets[ 1 ] > -1 )
        obj->color[ i ].y = float_arr->_ext.value[ index * stride + offsets[1] ];
      if ( offsets[ 2 ] > -1 )
        obj->color[ i ].z = float_arr->_ext.value[ index * stride + offsets[2] ];
#if DEBUG_OUTPUT
      powergl_printvec3( &obj->color[i] );
#endif
    }

    obj->color_flag = 1;
    obj->n_color = vertex_count;

  }

}

static void build_geometry_triangle_normal( powergl_rendering_geometry *obj, collada_type( triangles ) *triangles, collada_type( input_local_offset ) *normal_input ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  collada_type( source ) *src = ( collada_type( source ) * )normal_input->r_source.ptr;
  collada_type( accessor ) *srcAcc = src->c_source_technique_common->c_accessor;

  if ( srcAcc->r_float_array.ptr != NULL ) {

    collada_type( float_array ) *float_arr = ( collada_type( float_array ) * ) srcAcc->r_float_array.ptr;

    size_t stride = srcAcc->a_stride.value;

    if ( stride == 0 )
      stride = 1; // stride is must greater than 0 and default is 1

    // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid

    collada_type( param ) **params = srcAcc->ch_param;
    int offsets[3] = { -1, -1, -1};

    for ( int k = 0; k < srcAcc->n_param; k++ ) {

      if ( strlen( params[k]->a_name.value ) > 0 ) {

        if ( strncmp( params[k]->a_name.value, "X", 1 ) == 0 ) {

          offsets[0] = k;

        } else if ( strncmp( params[k]->a_name.value, "Y", 1 ) == 0 ) {

          offsets[1] = k;

        } else if ( strncmp( params[k]->a_name.value, "Z", 1 ) == 0 ) {

          offsets[2] = k;

        }

      }

    }
		
    size_t p_count = triangles->a_count.value;
    size_t vertex_count = p_count * 3;

    obj->normal = powergl_resize( NULL, sizeof( powergl_vec3 ) * vertex_count );

    for ( size_t i = 0; i < vertex_count ; i++ ) {

      size_t index = obj->index[ i * powergl_vertex_input_supported + powergl_normal_offset ];

      if ( offsets[ 0 ] > -1 )
        obj->normal[ i ].x = float_arr->_ext.value[ index * stride + offsets[0] ];
      if ( offsets[ 1 ] > -1 )
        obj->normal[ i ].y = float_arr->_ext.value[ index * stride + offsets[1] ];
      if ( offsets[ 2 ] > -1 )
        obj->normal[ i ].z = float_arr->_ext.value[ index * stride + offsets[2] ];
#if DEBUG_OUTPUT
      powergl_printvec3( &obj->normal[i] );
#endif
    }

    obj->normal_flag = 1;
    obj->n_normal = vertex_count;

  }
	
}

static void build_geometry_triangle_vertex( powergl_rendering_geometry *obj, collada_type( triangles ) *triangles, collada_type( input_local_offset ) *vertex_input ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  collada_type( vertices ) *vertices = ( collada_type( vertices ) * ) vertex_input->r_vertices.ptr;

  if ( vertices->n_input_local > 0 ) {

    collada_type( input_local ) *position_input = NULL;

    for ( size_t i = 0; i < vertices->n_input_local; i++ ) {

      if ( strcmp( vertices->ch_input_local[i]->a_semantic.value, "POSITION" ) == 0 ) {

        position_input = vertices->ch_input_local[i];

      }

    }

    if ( position_input != NULL ) {

      collada_type( source ) *srcPos = ( collada_type( source ) * )position_input->r_source.ptr;
      collada_type( accessor ) *srcPosAcc = srcPos->c_source_technique_common->c_accessor;

      if ( srcPosAcc->r_float_array.ptr != NULL ) {

        collada_type( float_array ) *float_arr = ( collada_type( float_array ) * ) srcPosAcc->r_float_array.ptr;


        size_t stride = srcPosAcc->a_stride.value;

        if ( stride == 0 )
          stride = 1; // stride is must greater than 0 and default is 1

        // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid

        collada_type( param ) **params = srcPosAcc->ch_param;
        int offsets[3] = { -1, -1, -1};

        for ( int k = 0; k < srcPosAcc->n_param; k++ ) {

          if ( strlen( params[k]->a_name.value ) > 0 ) {

            if ( strncmp( params[k]->a_name.value, "X", 1 ) == 0 ) {

              offsets[0] = k;

            } else if ( strncmp( params[k]->a_name.value, "Y", 1 ) == 0 ) {

              offsets[1] = k;

            } else if ( strncmp( params[k]->a_name.value, "Z", 1 ) == 0 ) {

              offsets[2] = k;

            }

          } // if param has a name which is equal to X, Y or Z

        } // count how many params has name attribute


        size_t p_count = triangles->a_count.value;
        size_t vertex_count = p_count * 3;


        obj->vertex = powergl_resize( NULL, sizeof( powergl_vec3 ) * vertex_count );

        for ( size_t i = 0; i < vertex_count ; i++ ) {

          size_t index = obj->index[ i * powergl_vertex_input_supported + powergl_vertex_offset ];

          if ( offsets[ 0 ] > -1 )
            obj->vertex[ i ].x = float_arr->_ext.value[ index * stride + offsets[0] ];
          if ( offsets[ 1 ] > -1 )
            obj->vertex[ i ].y = float_arr->_ext.value[ index * stride + offsets[1] ];
          if ( offsets[ 2 ] > -1 )
            obj->vertex[ i ].z = float_arr->_ext.value[ index * stride + offsets[2] ];
#if DEBUG_OUTPUT
          powergl_printvec3( &obj->vertex[i] );
#endif
        }

        obj->vertex_flag = 1;
        obj->n_vertex = vertex_count;

      } // if accessor has an array source which is not NULL and triangles has p collada_type which is not NULL

    } // if vertices collada_type has an input collada_type with POSITION semantic

  } // if vertices has an input

}

static void build_geometry_triangle( powergl_rendering_geometry *obj, collada_type( triangles ) *triangles ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  if ( triangles->n_input_local_offset > 0 ) {

    collada_type( input_local_offset ) *vertex_input = NULL;
    collada_type( input_local_offset ) *normal_input = NULL;
    collada_type( input_local_offset ) *color_input = NULL;

    for ( size_t i = 0; i < triangles->n_input_local_offset; i++ ) {

      if ( strcmp( triangles->ch_input_local_offset[i]->a_semantic.value, "VERTEX" ) == 0 ) {

        vertex_input = triangles->ch_input_local_offset[i];

      } else if ( strcmp( triangles->ch_input_local_offset[i]->a_semantic.value, "NORMAL" ) == 0 ) {

        normal_input = triangles->ch_input_local_offset[i];

      } else if ( strcmp( triangles->ch_input_local_offset[i]->a_semantic.value, "COLOR" ) == 0 ) {

        color_input = triangles->ch_input_local_offset[i];

      }

    }

    if ( vertex_input != NULL ) {


      build_geometry_triangle_index( obj, triangles, vertex_input, color_input, normal_input );
      build_geometry_triangle_vertex( obj, triangles, vertex_input );

      if ( color_input != NULL ) {
        build_geometry_triangle_color( obj, triangles, color_input );
      }

      if ( normal_input != NULL ) {
        build_geometry_triangle_normal( obj, triangles, normal_input );
      }

    }

  } // if triangles collada_type has input collada_types
}

static void build_geometry( collada_type( node ) * node, powergl_rendering_geometry *obj ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  collada_type( geometry ) *geo = ( collada_type( geometry ) * ) node->ch_instance_geometry[0]->r_geometry.ptr;
  collada_type( mesh ) *mesh = geo->c_mesh;

  if ( mesh->n_triangles > 0 ) {

    collada_type( triangles ) *triangles = mesh->ch_triangles[0];

    build_geometry_triangle( obj, triangles );

  } // if mesh has triangle collada_type

}

static void build_camera( collada_type( node ) * node, powergl_rendering_object *obj ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  powergl_rendering_camera *cam = obj->camera;
  collada_type( camera ) *cam_elem = ( collada_type( camera ) * ) node->ch_instance_camera[0]->r_camera.ptr;
  collada_type( perspective ) *pers = cam_elem->c_optics->c_optics_technique_common->cc_perspective;
  collada_type( orthographic ) *orth = cam_elem->c_optics->c_optics_technique_common->cc_orthographic;
  double *value_ptr = NULL;

  if ( pers != NULL ) {

    cam->type = 'p';

    if ( pers->cc_xfov != NULL ) {
      value_ptr = ( double * ) pers->cc_xfov->_base.value_ptr;
      if ( value_ptr != NULL )
        cam->xfov = to_radians( ( float )( *value_ptr ) );
    }

    if ( pers->cc_yfov != NULL ) {
      value_ptr = ( double * ) pers->cc_yfov->_base.value_ptr;
      if ( value_ptr != NULL )
        cam->yfov = to_radians( ( float )( *value_ptr ) );
    }

    value_ptr = ( double * ) pers->c_znear->_base.value_ptr;
    if ( value_ptr != NULL )
      cam->znear = ( float )( *value_ptr );

    value_ptr = ( double * ) pers->c_zfar->_base.value_ptr;
    if ( value_ptr != NULL )
      cam->zfar = ( float )( *value_ptr );

    value_ptr = ( double * ) pers->c_aspect_ratio->_base.value_ptr;
    if ( value_ptr != NULL )
      cam->aspect_ratio = ( float )( *value_ptr );


  } else if ( orth != NULL ) {

    cam->type = 'o';

    if ( orth->cc_xmag != NULL ) {
      value_ptr = ( double * ) orth->cc_xmag->_base.value_ptr;
      if ( value_ptr != NULL )
        cam->xmag = ( float )( *value_ptr );
    }

    if ( orth->cc_ymag != NULL ) {
      value_ptr = ( double * ) orth->cc_ymag->_base.value_ptr;
      if ( value_ptr != NULL )
        cam->ymag = ( float )( *value_ptr );
    }

    value_ptr = ( double * ) orth->c_znear->_base.value_ptr;
    if ( value_ptr != NULL )
      cam->znear = ( float )( *value_ptr );

    value_ptr = ( double * ) orth->c_zfar->_base.value_ptr;
    if ( value_ptr != NULL )
      cam->zfar = ( float )( *value_ptr );

    value_ptr = ( double * ) orth->c_aspect_ratio->_base.value_ptr;
    if ( value_ptr != NULL )
      cam->aspect_ratio = ( float )( *value_ptr );

  }

  if ( node->n_matrix > 0 ) {

    powergl_ident4x4( cam->view );
    cam->view_flag = 0;

    powergl_ident4x4( cam->projection );
    cam->projection_flag = 0;

    powergl_ident4x4( cam->vp );

    int result = powergl_inv4x4( ( float * ) &obj->matrix, ( float * ) &cam->view );

    if ( result == 1 ) {

      cam->view_flag = 1;

    } else {

      powergl_ident4x4( cam->view );

      powergl_vec3 eye = {0.0f, 0.0f, 4.0f};
      powergl_vec3 target = {0.0f, 0.0f, 0.0f};
      powergl_vec3 up = {0.0f, 1.0f, 0.0f};

      powergl_lookat( cam->view, &eye, &target, &up );

    }
#if DEBUG_OUTPUT
    printf( "view transform\n" );
    powergl_print4x4( cam->view );
#endif


    if ( cam->type == 'p' ) {


      if ( pers->cc_yfov != NULL ) {

        powergl_perspectiveRH( cam->projection, cam->yfov, cam->aspect_ratio, cam->znear, cam->zfar );
        cam->projection_flag = 1;
#if DEBUG_OUTPUT
        printf( "[aspect_ratio = %f] [xfov = %f] [yfov = %f]  [znear = %f] [zfar= %f]\n", cam->aspect_ratio, cam->xfov, cam->yfov, cam->znear, cam->zfar );
#endif
      } else if ( pers->cc_xfov != NULL ) {

        cam->yfov = cam->xfov / cam->aspect_ratio;
        powergl_perspectiveRH( cam->projection, cam->yfov, cam->aspect_ratio, cam->znear, cam->zfar );
        cam->projection_flag = 1;
#if DEBUG_OUTPUT
        printf( "[aspect_ratio = %f] [xfov = %f] [yfov = %f]  [znear = %f] [zfar= %f]\n", cam->aspect_ratio, cam->xfov, cam->yfov, cam->znear, cam->zfar );
#endif
      } else {

        powergl_perspectiveRH( cam->projection, 2.16f, 1.33f, 0.1f, 100.0f );
#if DEBUG_OUTPUT
	printf( "defaults ! [aspect_ratio = %f] [xfov = %f] [yfov = %f]  [znear = %f] [zfar= %f]\n", 1.33f, 2.09f, 1.57f, 0.1f, 100.0f );
#endif
        cam->projection_flag = 1;

      }
#if DEBUG_OUTPUT
      printf( "perspective projection transform\n" );
      powergl_print4x4( cam->projection );
#endif

    }

  }

}

static void build_light( collada_type( node ) * node, powergl_rendering_object *obj ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  //////////////////////////////////////////// color
	
  powergl_rendering_light *light = obj->light;
  collada_type( light ) *light_elem = ( collada_type( light ) * ) node->ch_instance_light[0]->r_light.ptr;
  collada_type( light_technique_common ) *tc = light_elem->c_light_technique_common;
		
  if ( tc != NULL && tc->cc_directional != NULL ) {

    collada_type( directional ) *sun = tc->cc_directional;
		
    if ( sun-> c_color != NULL) {

      if ( sun->c_color->_ext.value != NULL ) {

	double *ptr = sun->c_color->_ext.value;
				
	for ( size_t i = 0; i < 3; ++i) {
					
	  obj->light->color[i] = ptr[i];
				
	}

      }

    } else {
			
      for ( size_t i = 0; i < 3; ++i) {
					
	obj->light->color[i] = 1.0f;

      }
			
    }
#if DEBUG_OUTPUT
    printf("light color\n%g %g %g\n",obj->light->color[0],obj->light->color[1],obj->light->color[2]);
#endif
    obj->light->color_flag = 1;

    ////////////////////////////////////////// direction

    // set w = 0 to get infinite 
    // default for collada directional light dir
    GLfloat v[4] = { 0.0f, 0.0f, -1.0f, 0.0f };
    GLfloat result[4];
#if DEBUG_OUTPUT
    printf("light transform matrix\n");
    powergl_print4x4(obj->matrix);
#endif
    powergl_transformvec4(v, obj->matrix, result);
#if DEBUG_OUTPUT
    printf("transformed light coord\n");
    for ( size_t i = 0; i < 4; i++ ) {
      printf("%g ",result[i]);
    }
    printf("\n");
#endif
    powergl_vec3 dir = {.x = result[0], .y = result[1], .z = result[2] };
    powergl_vec3 norm_dir;
		
    powergl_normvec3(&dir, &norm_dir);
		
    obj->light->dir[0] = norm_dir.x;
    obj->light->dir[1] = norm_dir.y;
    obj->light->dir[2] = norm_dir.z;
#if DEBUG_OUTPUT
    printf("normalized light dir\n%g %g %g\n",obj->light->dir[0],obj->light->dir[1],obj->light->dir[2]);
#endif
    obj->light->type = 'd';

    obj->light->dir_flag = 1;
		
  }
}

static void build_transform( collada_type( node ) * node, powergl_rendering_object *obj ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );
#endif
  collada_type( matrix ) *matrix = node->ch_matrix[0];

  for ( size_t i = 0; i < 4; i++ ) {

    for ( size_t j = 0; j < 4; j++ ) {

      obj->matrix[i][j] = ( float ) matrix->_ext.value[i * 4 + j];

    }

  }
  powergl_trans4x4( obj->matrix );
#if DEBUG_OUTPUT
  powergl_print4x4( obj->matrix );
#endif
  obj->matrix_flag = 1;

}

static void build_objects(powergl_rendering_visualscene *scene ,collada_type(node) *node, powergl_rendering_object *obj){
  
  if ( node->n_matrix > 0 ) {

    build_transform( node, obj );

  } // if node has transform

  if ( node->n_instance_geometry > 0 ) {
    obj->geometry = powergl_resize( NULL, sizeof( powergl_rendering_geometry ) );
    powergl_rendering_geometry_create( obj->geometry );
    build_geometry( node, obj->geometry );

  } // if node has instance_geometry

  if ( node->n_instance_camera > 0 ) {
    obj->camera = powergl_resize( NULL, sizeof( powergl_rendering_camera ) );
    powergl_rendering_camera_create( obj->camera );
    build_camera( node, obj );

    if ( scene->main_camera == NULL ) {
      scene->main_camera = obj;
    }

  } // if node has instance_camera

  if ( node->n_instance_light > 0 ) {
    obj->light = powergl_resize( NULL, sizeof( powergl_rendering_light ) );
    powergl_rendering_light_create( obj->light );
    build_light( node, obj );

    if ( scene->main_light == NULL ) {
      scene->main_light = obj;
    }

  } // if node has instance_light

  if ( node->n_node > 0 ) {
    
    obj->children = powergl_resize( NULL, sizeof(powergl_rendering_object*) * node->n_node);
    obj->n_child = node->n_node;

    for ( size_t i = 0; i < node->n_node; i++ ) {

      obj->children[i] = powergl_resize( NULL, sizeof( powergl_rendering_object ) );
      powergl_rendering_object_create( obj->children[i] );

      build_objects(scene, node->ch_node[i], obj->children[i]);
    }
    
  }
}

static void build_from_dae( powergl_rendering_visualscene *this, const char *file ) {
#if DEBUG_OUTPUT
  printf( "%s\n", __func__ );

  printf( "the dae file will be parsed = %s \n", file );
#endif
  collada_type( collada ) *root = powergl_collada_parse(file);
  collada_type( scene ) *scene = root->c_scene;
  collada_type( instance_visual_scene ) *instance = scene->c_instance_visual_scene;
  collada_type( visual_scene ) *vscene = ( collada_type( visual_scene ) * ) instance->r_visual_scene.ptr;

  size_t size = vscene->n_node;
  this->objects = powergl_resize( NULL, sizeof( powergl_rendering_object * ) * size );
  this->n_object = size;
  this->main_camera = NULL;
  this->main_light = NULL;

  for ( size_t i = 0; i < size; i++ ) {

    collada_type( node ) *node = vscene->ch_node[i];

    this->objects[i] = powergl_resize( NULL, sizeof( powergl_rendering_object ) );
    powergl_rendering_object_create( this->objects[i] );
   
    build_objects(this, node, this->objects[i]);
    
  } // for each node

}


int powergl_rendering_visualscene_create( powergl_rendering_visualscene *vscene, const char *daefile ) {

  build_from_dae( vscene, daefile );
  powergl_rendering_pipeline_create( &vscene->pipeline, vscene->objects, vscene->n_object );
}


int powergl_rendering_visualscene_run( powergl_rendering_visualscene *vscene ) {

  for ( size_t i = 0 ; i < vscene->n_object; i++ ) {

    powergl_rendering_object_run( vscene->objects[i] );

  }

  powergl_rendering_pipeline_render( &vscene->pipeline, vscene->objects, vscene->n_object, vscene->main_camera, vscene->main_light );

}
