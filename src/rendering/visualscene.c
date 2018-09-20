#include "visualscene.h"

#include "../powergl.h"
#include "../asset/collada.h"
#include "../math/mat4x4.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

static float to_radians( float degrees ) {
  return degrees * ( 3.141592f / 180.0f );
}

static void build_geometry_triangle_index( powergl_rendering_geometry *obj, collada_elem( triangles ) *triangles, collada_elem( input_local_offset ) *vertex_input, collada_elem( input_local_offset ) *color_input ) {

  printf( "%s\n", __func__ );

  // how many triangles are there in _ imported file _
  size_t p_count = triangles->a_count.value;

  // each triangle has how many vertex attribute in _ imported file _
  size_t input_count = triangles->n_input_local_offset;

  // currently rendererer supports _ 2 _ vertex input attribute
  size_t input_count_supported = 2;

  // offset values for each vertex attribute
  size_t vertex_offset = vertex_input->a_offset.value;
  size_t color_offset;

  if ( color_input != NULL ) {
    color_offset = color_input->a_offset.value;
  } else {
    printf( "no color input found \n" );
  }

  // vertex count 3 = triangle has 3 vertex
  size_t vertex_count = 3 * p_count;

  // total index count
  size_t n_index = vertex_count * input_count_supported;


  obj->index = powergl_resize( NULL, sizeof( GLuint ) * n_index );


  // get xml collada_elem that contains index values
  collada_elem( p ) *p_arr = triangles->c_p;

  for ( size_t l = 0; l < vertex_count; l++ ) {

    // this index array is building vbo, ibo and cbo sources
    obj->index[ l * input_count_supported + 0 ] = p_arr->_ext.value[ l * input_count  + vertex_offset ];

    if ( color_input != NULL ) {
      obj->index[ l * input_count_supported + 1 ] = p_arr->_ext.value[ l * input_count  + color_offset ];
    }

    printf( "%u %u ", obj->index[ l * input_count_supported + 0 ], obj->index[ l * input_count_supported + 1] );

  } // copy indices from p collada_elem for each vertex

  printf( "\n" );
  obj->index_flag = 1;
  obj->n_index = n_index;

}

static void build_geometry_triangle_color( powergl_rendering_geometry *obj, collada_elem( triangles ) *triangles, collada_elem( input_local_offset ) *color_input ) {

  printf( "%s\n", __func__ );

  collada_elem( source ) *src = ( collada_elem( source ) * )color_input->r_source.ptr;
  collada_elem( accessor ) *srcAcc = src->c_source_technique_common->c_accessor;

  if ( srcAcc->r_float_array.ptr != NULL ) {

    collada_elem( float_array ) *float_arr = ( collada_elem( float_array ) * ) srcAcc->r_float_array.ptr;

    size_t stride = srcAcc->a_stride.value;

    if ( stride == 0 )
      stride = 1; // stride is must greater than 0 and default is 1

    // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_elems count it is not valid

    collada_elem( param ) **params = srcAcc->ch_param;
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

    size_t color_offset = 1;
    size_t p_count = triangles->a_count.value;
    size_t vertex_count = p_count * 3;
    size_t input_count = 2;

    obj->color = powergl_resize( NULL, sizeof( powergl_vec3 ) * vertex_count );

    for ( size_t i = 0; i < vertex_count ; i++ ) {

      size_t index = obj->index[ i * input_count + color_offset ];

      if ( offsets[ 0 ] > -1 )
        obj->color[ i ].x = float_arr->_ext.value[ index * stride + offsets[0] ];
      if ( offsets[ 1 ] > -1 )
        obj->color[ i ].y = float_arr->_ext.value[ index * stride + offsets[1] ];
      if ( offsets[ 2 ] > -1 )
        obj->color[ i ].z = float_arr->_ext.value[ index * stride + offsets[2] ];

      powergl_printvec3( &obj->color[i] );

    }

    obj->color_flag = 1;
    obj->n_color = vertex_count;

  }

}

static void build_geometry_normal( powergl_rendering_geometry *obj, collada_elem( input_local_offset ) *normal_input ) {

  printf( "%s\n", __func__ );
  // planned but not implemented yet
}

static void build_geometry_triangle_vertex( powergl_rendering_geometry *obj, collada_elem( triangles ) *triangles, collada_elem( input_local_offset ) *vertex_input ) {

  printf( "%s\n", __func__ );

  collada_elem( vertices ) *vertices = ( collada_elem( vertices ) * ) vertex_input->r_vertices.ptr;

  if ( vertices->n_input_local > 0 ) {

    collada_elem( input_local ) *position_input = NULL;

    for ( size_t i = 0; i < vertices->n_input_local; i++ ) {

      if ( strcmp( vertices->ch_input_local[i]->a_semantic.value, "POSITION" ) == 0 ) {

        position_input = vertices->ch_input_local[i];

      }

    }

    if ( position_input != NULL ) {

      collada_elem( source ) *srcPos = ( collada_elem( source ) * )position_input->r_source.ptr;
      collada_elem( accessor ) *srcPosAcc = srcPos->c_source_technique_common->c_accessor;

      if ( srcPosAcc->r_float_array.ptr != NULL ) {

        collada_elem( float_array ) *float_arr = ( collada_elem( float_array ) * ) srcPosAcc->r_float_array.ptr;


        size_t stride = srcPosAcc->a_stride.value;

        if ( stride == 0 )
          stride = 1; // stride is must greater than 0 and default is 1

        // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_elems count it is not valid

        collada_elem( param ) **params = srcPosAcc->ch_param;
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



        size_t vertex_offset = 0;
        size_t p_count = triangles->a_count.value;
        size_t vertex_count = p_count * 3;
        size_t input_count = 2;

        obj->vertex = powergl_resize( NULL, sizeof( powergl_vec3 ) * vertex_count );

        for ( size_t i = 0; i < vertex_count ; i++ ) {

          size_t index = obj->index[ i * input_count + vertex_offset ];

          if ( offsets[ 0 ] > -1 )
            obj->vertex[ i ].x = float_arr->_ext.value[ index * stride + offsets[0] ];
          if ( offsets[ 1 ] > -1 )
            obj->vertex[ i ].y = float_arr->_ext.value[ index * stride + offsets[1] ];
          if ( offsets[ 2 ] > -1 )
            obj->vertex[ i ].z = float_arr->_ext.value[ index * stride + offsets[2] ];

          powergl_printvec3( &obj->vertex[i] );

        }

        obj->vertex_flag = 1;
        obj->n_vertex = vertex_count;

      } // if accessor has an array source which is not NULL and triangles has p collada_elem which is not NULL

    } // if vertices collada_elem has an input collada_elem with POSITION semantic

  } // if vertices has an input

}

static void build_geometry_triangle( powergl_rendering_geometry *obj, collada_elem( triangles ) *triangles ) {

  printf( "%s\n", __func__ );

  if ( triangles->n_input_local_offset > 0 ) {

    collada_elem( input_local_offset ) *vertex_input = NULL;
    collada_elem( input_local_offset ) *normal_input = NULL;
    collada_elem( input_local_offset ) *color_input = NULL;

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


      build_geometry_triangle_index( obj, triangles, vertex_input, color_input );
      build_geometry_triangle_vertex( obj, triangles, vertex_input );

      if ( color_input != NULL ) {
        build_geometry_triangle_color( obj, triangles, color_input );
      }

    }

  } // if triangles collada_elem has input collada_elems
}

static void build_geometry( collada_elem( node ) * node, powergl_rendering_geometry *obj ) {

  printf( "%s\n", __func__ );

  collada_elem( geometry ) *geo = ( collada_elem( geometry ) * ) node->ch_instance_geometry[0]->r_geometry.ptr;
  collada_elem( mesh ) *mesh = geo->c_mesh;

  if ( mesh->n_triangles > 0 ) {

    collada_elem( triangles ) *triangles = mesh->ch_triangles[0];

    build_geometry_triangle( obj, triangles );

  } // if mesh has triangle collada_elem

}

static void build_camera( collada_elem( node ) * node, powergl_rendering_object *obj ) {

  printf( "%s\n", __func__ );

  powergl_rendering_camera *cam = obj->camera;
  collada_elem( camera ) *cam_elem = ( collada_elem( camera ) * ) node->ch_instance_camera[0]->r_camera.ptr;
  collada_elem( perspective ) *pers = cam_elem->c_optics->c_optics_technique_common->cc_perspective;
  collada_elem( orthographic ) *orth = cam_elem->c_optics->c_optics_technique_common->cc_orthographic;
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
    printf( "view transform\n" );
    powergl_print4x4( cam->view );

    if ( cam->type == 'p' ) {


      if ( pers->cc_yfov != NULL && cam->yfov < 180.0f && cam->yfov > 0.0f ) {

        powergl_perspectiveRH( cam->projection, cam->yfov, cam->aspect_ratio, cam->znear, cam->zfar );
        cam->projection_flag = 1;
        printf( "[aspect_ratio = %f] [xfov = %f] [yfov = %f]  [znear = %f] [zfar= %f]\n", cam->aspect_ratio, cam->xfov, cam->yfov, cam->znear, cam->zfar );

      } else if ( pers->cc_xfov != NULL && cam->xfov < 180.0f && cam->xfov > 0.0f ) {

        cam->yfov = cam->xfov / cam->aspect_ratio;
        powergl_perspectiveRH( cam->projection, cam->yfov, cam->aspect_ratio, cam->znear, cam->zfar );
        cam->projection_flag = 1;
        printf( "[aspect_ratio = %f] [xfov = %f] [yfov = %f]  [znear = %f] [zfar= %f]\n", cam->aspect_ratio, cam->xfov, cam->yfov, cam->znear, cam->zfar );

      } else {

        powergl_perspectiveRH( cam->projection, 1.57f, 1.33f, 0.1f, 100.0f );
        cam->projection_flag = 1;

      }
      printf( "perspective projection transform\n" );
      powergl_print4x4( cam->projection );

    }

  }

}

static void build_transform( collada_elem( node ) * node, powergl_rendering_object *obj ) {

  printf( "%s\n", __func__ );

  collada_elem( matrix ) *matrix = node->ch_matrix[0];

  for ( size_t i = 0; i < 4; i++ ) {

    for ( size_t j = 0; j < 4; j++ ) {

      obj->matrix[i][j] = ( float ) matrix->_ext.value[i * 4 + j];

    }

  }
  powergl_trans4x4( obj->matrix );
  powergl_print4x4( obj->matrix );
  obj->matrix_flag = 1;

}

static void build_from_dae( powergl_rendering_visualscene *this, const char *file ) {

  printf( "%s\n", __func__ );

  printf( "the dae file will be parsed = %s \n", file );

  collada_elem( collada ) *root = collada_func( parse )( file );
  collada_elem( scene ) *scene = root->c_scene;
  collada_elem( instance_visual_scene ) *instance = scene->c_instance_visual_scene;
  collada_elem( visual_scene ) *vscene = ( collada_elem( visual_scene ) * ) instance->r_visual_scene.ptr;

  size_t size = vscene->n_node;
  this->objects = powergl_resize( NULL, sizeof( powergl_rendering_object * ) * size );
  this->n_object = size;
  this->i_camera = -1;

  for ( size_t i = 0; i < size; i++ ) {

    collada_elem( node ) *node = vscene->ch_node[i];

    this->objects[i] = powergl_resize( NULL, sizeof( powergl_rendering_object ) );
    powergl_rendering_object_create( this->objects[i] );

    if ( node->n_matrix > 0 ) {

      build_transform( node, this->objects[i] );

    } // if node has transform collada_elems

    if ( node->n_instance_geometry > 0 ) {
      this->objects[i]->geometry = powergl_resize( NULL, sizeof( powergl_rendering_geometry ) );
      powergl_rendering_geometry_create( this->objects[i]->geometry );
      build_geometry( node, this->objects[i]->geometry );

    } // if node has instance_geometry collada_elem

    if ( node->n_instance_camera > 0 ) {
      this->objects[i]->camera = powergl_resize( NULL, sizeof( powergl_rendering_camera ) );
      powergl_rendering_camera_create( this->objects[i]->camera );
      build_camera( node, this->objects[i] );
      this->i_camera = i;

    } // if node has instance_camera collada_elem


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

  powergl_rendering_pipeline_render( &vscene->pipeline, vscene->objects, vscene->n_object, vscene->i_camera );

}
