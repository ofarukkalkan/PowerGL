#include "dae2object.h"

#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT 1
#endif
static const size_t powergl_vertex_offset = 0;
static const size_t powergl_normal_offset = 1;
static const size_t powergl_color_offset = 2;
static const size_t powergl_vertex_input_supported = 3;

static float to_radians(float degrees) {
  return degrees * (3.141592f / 180.0f);
}

void powergl_build_geometry_triangle_index(powergl_geometry *geo, powergl_collada_core_triangles *triangles, powergl_collada_core_input_local_offset *vertex_input, powergl_collada_core_input_local_offset  *color_input, powergl_collada_core_input_local_offset  *normal_input) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  // how many triangles are there in _ imported file _
  size_t p_count = triangles->c_count;
  // offset values for each vertex attribute
  size_t vertex_offset = vertex_input->c_offset;
  size_t color_offset;
  size_t normal_offset;

  if(color_input != NULL) {
    color_offset = color_input->c_offset;
  } else {
    fprintf(stderr, "no color input found \n");
  }

  if(normal_input != NULL) {
    normal_offset = normal_input->c_offset;
  } else {
    fprintf(stderr, "no normal input found \n");
  }

  // vertex count 3 = triangle has 3 vertex
  size_t vertex_count = 3 * p_count;
  // total index count
  size_t n_index = vertex_count * powergl_vertex_input_supported;
  geo->index = powergl_resize(NULL, n_index, sizeof(GLuint));
  // get xml collada_type that contains index values
  powergl_collada_core_ListOfUInts  *p_arr = triangles->c_p[0];
  // each triangle has how many vertex attribute in _ imported file _
  size_t input_count = p_arr->n_content / (3 * p_count);

  for(size_t l = 0; l < vertex_count; l++) {
    // this index array is building vbo, ibo and cbo sources
    geo->index[ l * powergl_vertex_input_supported + powergl_vertex_offset ] = p_arr->content[ l * input_count  + vertex_offset ];

    if(normal_input != NULL) {
      geo->index[ l * powergl_vertex_input_supported + powergl_normal_offset ] = p_arr->content[ l * input_count  + normal_offset ];
    }

    if(color_input != NULL) {
      geo->index[ l * powergl_vertex_input_supported + powergl_color_offset ] = p_arr->content[ l * input_count  + color_offset ];
    }

  } // copy indices from p collada_type for each vertex

  geo->index_flag = 1;
  geo->n_index = n_index;
}

void powergl_build_geometry_triangle_color(powergl_geometry *geo, powergl_collada_core_triangles  *triangles, powergl_collada_core_input_local_offset  *color_input) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  powergl_collada_core_source *src = color_input->r_source;
  powergl_collada_core_accessor *srcAcc = src->c_technique_common[0]->c_accessor[0];

  if(srcAcc->r_float_array != NULL) {
    powergl_collada_core_float_array  *float_arr =  srcAcc->r_float_array;
    size_t stride = srcAcc->c_stride;

    if(stride == 0) {
      stride = 1;    // stride is must greater than 0 and default is 1
    }

    // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid
    powergl_collada_core_param  **params = srcAcc->c_param;
    size_t offsets[3] = { 0, 0, 0};

    for(size_t k = 0; k < srcAcc->n_param; k++) {
      if(strlen(params[k]->c_name) > 0) {
	if(strncmp(params[k]->c_name, "R", 1) == 0) {
	  offsets[0] = k;
	} else if(strncmp(params[k]->c_name, "G", 1) == 0) {
	  offsets[1] = k;
	} else if(strncmp(params[k]->c_name, "B", 1) == 0) {
	  offsets[2] = k;
	}
      }
    }

    size_t p_count = triangles->c_count;
    size_t vertex_count = p_count * 3;
    geo->color = powergl_resize(NULL, vertex_count, sizeof(powergl_vec3));

    for(size_t i = 0; i < vertex_count ; i++) {
      size_t index = geo->index[ i * powergl_vertex_input_supported + powergl_color_offset ];
      geo->color[ i ].x = float_arr->content[ index * stride + offsets[0] ];
      geo->color[ i ].y = float_arr->content[ index * stride + offsets[1] ];
      geo->color[ i ].z = float_arr->content[ index * stride + offsets[2] ];
    }

    geo->color_flag = 1;
    geo->n_color = vertex_count;
  }
}

void powergl_build_geometry_triangle_normal(powergl_geometry *geo, powergl_collada_core_triangles  *triangles, powergl_collada_core_input_local_offset  *normal_input) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  powergl_collada_core_source *src = normal_input->r_source;
  powergl_collada_core_accessor *srcAcc = src->c_technique_common[0]->c_accessor[0];

  if(srcAcc->r_float_array != NULL) {
    powergl_collada_core_float_array  *float_arr = srcAcc->r_float_array;
    size_t stride = srcAcc->c_stride;

    if(stride == 0) {
      stride = 1;    // stride is must greater than 0 and default is 1
    }

    // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid
    powergl_collada_core_param  **params = srcAcc->c_param;
    size_t offsets[3] = {0, 0, 0};

    for(size_t k = 0; k < srcAcc->n_param; k++) {
      if(strlen(params[k]->c_name) > 0) {
	if(strncmp(params[k]->c_name, "X", 1) == 0) {
	  offsets[0] = k;
	} else if(strncmp(params[k]->c_name, "Y", 1) == 0) {
	  offsets[1] = k;
	} else if(strncmp(params[k]->c_name, "Z", 1) == 0) {
	  offsets[2] = k;
	}
      }
    }

    size_t p_count = triangles->c_count;
    size_t vertex_count = p_count * 3;
    geo->normal = powergl_resize(NULL, vertex_count, sizeof(powergl_vec3));

    for(size_t i = 0; i < vertex_count ; i++) {
      size_t index = geo->index[ i * powergl_vertex_input_supported + powergl_normal_offset ];
      geo->normal[ i ].x = float_arr->content[ index * stride + offsets[0] ];
      geo->normal[ i ].y = float_arr->content[ index * stride + offsets[1] ];
      geo->normal[ i ].z = float_arr->content[ index * stride + offsets[2] ];
    }

    geo->normal_flag = 1;
    geo->n_normal = vertex_count;
  }
}

void powergl_build_geometry_triangle_vertex(powergl_geometry *geo, powergl_collada_core_triangles  *triangles, powergl_collada_core_input_local_offset  *vertex_input) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  powergl_collada_core_vertices  *vertices = vertex_input->r_vertices;

  if(vertices->n_input > 0) {
    powergl_collada_core_input_local  *position_input = NULL;

    for(size_t i = 0; i < vertices->n_input; i++) {
      if(strcmp(vertices->c_input[i]->c_semantic, "POSITION") == 0) {
	position_input = vertices->c_input[i];
      }
    }

    if(position_input != NULL) {
      powergl_collada_core_source  *srcPos = position_input->r_source;
      powergl_collada_core_accessor  *srcPosAcc = srcPos->c_technique_common[0]->c_accessor[0];

      if(srcPosAcc->r_float_array != NULL) {
	powergl_collada_core_float_array  *float_arr = srcPosAcc->r_float_array;
	size_t stride = srcPosAcc->c_stride;

	if(stride == 0) {
	  stride = 1;    // stride is must greater than 0 and default is 1
	}

	// if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid
	powergl_collada_core_param  **params = srcPosAcc->c_param;
	size_t offsets[3] = { 0, 0, 0};

	for(size_t k = 0; k < srcPosAcc->n_param; k++) {
	  if(strlen(params[k]->c_name) > 0) {
	    if(strncmp(params[k]->c_name, "X", 1) == 0) {
	      offsets[0] = k;
	    } else if(strncmp(params[k]->c_name, "Y", 1) == 0) {
	      offsets[1] = k;
	    } else if(strncmp(params[k]->c_name, "Z", 1) == 0) {
	      offsets[2] = k;
	    }
	  } // if param has a name which is equal to X, Y or Z
	} // count how many params has name attribute

	size_t p_count = triangles->c_count;
	size_t vertex_count = p_count * 3;
	geo->vertex = powergl_resize(NULL, vertex_count, sizeof(powergl_vec3));

	for(size_t i = 0; i < vertex_count ; i++) {
	  size_t index = geo->index[ i * powergl_vertex_input_supported + powergl_vertex_offset ];
	  geo->vertex[ i ].x = float_arr->content[ index * stride + offsets[0] ];
	  geo->vertex[ i ].y = float_arr->content[ index * stride + offsets[1] ];
	  geo->vertex[ i ].z = float_arr->content[ index * stride + offsets[2] ];
	}

	geo->vertex_flag = 1;
	geo->n_vertex = vertex_count;
      } // if accessor has an array source which is not NULL and triangles has p collada_type which is not NULL
    } // if vertices collada_type has an input collada_type with POSITION semantic
  } // if vertices has an input
}

void powergl_build_geometry_triangle(powergl_geometry *geo, powergl_collada_core_triangles  *triangles) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif

  if(triangles->n_input > 0) {
    powergl_collada_core_input_local_offset  *vertex_input = NULL;
    powergl_collada_core_input_local_offset  *normal_input = NULL;
    powergl_collada_core_input_local_offset  *color_input = NULL;

    for(size_t i = 0; i < triangles->n_input; i++) {
      if(strcmp(triangles->c_input[i]->c_semantic, "VERTEX") == 0) {
	vertex_input = triangles->c_input[i];
      } else if(strcmp(triangles->c_input[i]->c_semantic, "NORMAL") == 0) {
	normal_input = triangles->c_input[i];
      } else if(strcmp(triangles->c_input[i]->c_semantic, "COLOR") == 0) {
	color_input = triangles->c_input[i];
      }
    }

    if(vertex_input != NULL) {
      powergl_build_geometry_triangle_index(geo, triangles, vertex_input, color_input, normal_input);
      powergl_build_geometry_triangle_vertex(geo, triangles, vertex_input);

      if(color_input != NULL) {
	powergl_build_geometry_triangle_color(geo, triangles, color_input);
      }

      if(normal_input != NULL) {
	powergl_build_geometry_triangle_normal(geo, triangles, normal_input);
      }
    }
  } // if triangles collada_type has input collada_types
}

void powergl_build_geometry(powergl_collada_core_node   *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  powergl_collada_core_geometry  *geo =  node->c_instance_geometry[0]->r_geometry;
  powergl_collada_core_mesh  *mesh = geo->c_mesh[0];
  obj->geometry = powergl_resize(NULL, mesh->n_triangles, sizeof(powergl_geometry *));
  obj->n_geometry = mesh->n_triangles;

  for(size_t i = 0; i <  mesh->n_triangles; i++) {
    powergl_collada_core_triangles  *triangle = mesh->c_triangles[i];
    obj->geometry[i] = powergl_resize(NULL, 1, sizeof(powergl_geometry));
    powergl_build_geometry_triangle(obj->geometry[i], triangle);
  } // if mesh has triangle collada_type
}

void powergl_build_camera(powergl_collada_core_node   *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  powergl_camera *cam = obj->camera;
  powergl_collada_core_camera  *cam_elem = node->c_instance_camera[0]->r_camera;
  powergl_collada_core_perspective  *pers = cam_elem->c_optics[0]->c_technique_common[0]->c_perspective[0];

  if(pers != NULL) {
    cam->type = 'p';

    if(pers->c_xfov != NULL) {
      cam->xfov = to_radians(pers->c_xfov[0]->content[0]);
    }

    if(pers->c_yfov != NULL) {
      cam->yfov = to_radians(pers->c_yfov[0]->content[0]);
    }

    cam->znear = pers->c_znear[0]->content[0];
    cam->zfar = pers->c_zfar[0]->content[0];
    cam->aspect_ratio = pers->c_aspect_ratio[0]->content[0];
  }

  cam->view = powergl_mat4_ident();
  cam->view_flag = 0;
  cam->projection = powergl_mat4_ident();
  cam->projection_flag = 0;
  cam->vp = powergl_mat4_ident();
    
  // if obj's transform is not inverted. (blender does not export a matrix called view transform.
  // but we can use inverse of obj's transform  as view transform)
  cam->view = powergl_mat4_inv(obj->transform);
    
  // if obj's transform is ready to use as view transform.
  // obj->transform[3][2] should has negative sign.
  // cam->view = obj->transform;
    
  /*
    if(result == 1) {
    assert(result);
    } else {
    powergl_ident4x4(&cam->view);
    powergl_vec3 eye = {{0.0f, 0.0f, 4.0f}};
    powergl_vec3 target = {{0.0f, 0.0f, 0.0f}};
    powergl_vec3 up = {{0.0f, 1.0f, 0.0f}};
    powergl_lookat(&cam->view, &eye, &target, &up);
    }
  */
  cam->view_flag = 1;
    
#if DEBUG_OUTPUT
  powergl_mat4_print("view transform", cam->view);
#endif

  // blender does not export any projection matrix. we can get it from its console by calling this func ->
  // bpy.data.objects['Camera'].calc_matrix_camera(1280,720)
  // or we can construct a proj. matrix from params under camera element
  // but there is a problem inside blender dae exporter, it only exports xfov param. so we should convert it to yfov
  if(cam->type == 'p') {
    if(pers->c_yfov != NULL) {
      cam->projection = powergl_mat4_perspectiveRH(cam->yfov, cam->aspect_ratio, cam->znear, cam->zfar);
    } else if(pers->c_xfov != NULL) {
      float tanHalfXfov = tanf(cam->xfov / 2.0f);
      float X = tanHalfXfov * 2.0f * cam->znear;
      float Y = X / cam->aspect_ratio;
      float yfov = 2 * atanf( Y / (2.0f * cam->znear));

      cam->yfov = yfov;
      cam->projection = powergl_mat4_perspectiveRH(cam->yfov, cam->aspect_ratio, cam->znear, cam->zfar);
    } else {
      cam->projection = powergl_mat4_perspectiveRH(2.16f, 1.33f, 0.1f, 100.0f);
    }
    cam->projection_flag = 1;
	
#if DEBUG_OUTPUT
    powergl_float_print("aspect", cam->aspect_ratio);
    powergl_float_print("xfov", cam->xfov);
    powergl_float_print("yfov", cam->yfov);
    powergl_float_print("znear", cam->znear);
    powergl_float_print("zfar", cam->zfar);
    powergl_mat4_print("perspective projection transform", cam->projection);
#endif
  }
}

void powergl_build_light(powergl_collada_core_node *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  //////////////////////////////////////////// color
  powergl_collada_core_light *light_elem =  node->c_instance_light[0]->r_light;
  powergl_collada_core_light_technique_common  *tc = light_elem->c_technique_common[0];

  if(tc != NULL && tc->c_directional != NULL) {
    powergl_collada_core_directional  *sun = tc->c_directional[0];

    if(sun-> c_color != NULL) {
      if(sun->c_color[0]->content != NULL) {
	powergl_vec3_copy(&obj->light->color, sun->c_color[0]->content, sun->c_color[0]->n_content);
      }
    } else {
      obj->light->color.x = 1.0f;
      obj->light->color.y = 1.0f;
      obj->light->color.z = 1.0f;
    }
    obj->light->color_flag = 1;

#if DEBUG_OUTPUT
    powergl_vec3_print("light color", obj->light->color);
#endif
    ////////////////////////////////////////// direction
    // w = 0 set to get infinite. so it does not affect translation part of matrix
    // default collada directional light ->
    powergl_vec4 v = {{0.0f, 0.0f, -1.0f, 0.0f }};
	
    obj->light->dir = powergl_vec3_norm(powergl_vec4_trans(v, obj->transform).xyz);
    obj->light->type = 'd';
    obj->light->dir_flag = 1;

#if DEBUG_OUTPUT
    powergl_vec3_print("normalized light dir", obj->light->dir);
#endif
  }
}

void powergl_build_transform_matrix(powergl_collada_core_node *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  powergl_collada_core_targetable_floats *matrix = node->c_matrix[0];
    
  powergl_mat4_copy(&obj->transform, matrix->content, matrix->n_content, 1);
  obj->matrix_flag = 1;

#if DEBUG_OUTPUT
  powergl_mat4_print(node->c_id, obj->transform);
#endif
}

void powergl_build_transform_TransRotLoc(powergl_collada_core_node *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  obj->transform = powergl_mat4_ident();

  for(size_t i = 0; i < node->n_rotate; i++) {
    // blender sid's = rotationX , rotationY, rotationZ
    if(strcmp(node->c_rotate[i]->c_sid, "rotationX") == 0
       || strcmp(node->c_rotate[i]->c_sid, "rotationY") == 0
       || strcmp(node->c_rotate[i]->c_sid, "rotationZ") == 0) {
      powergl_vec4 rot;
      rot.x = node->c_rotate[i]->content[0];
      rot.y = node->c_rotate[i]->content[1];
      rot.z = node->c_rotate[i]->content[2];
      rot.w = node->c_rotate[i]->content[3];
      rot.w  = to_radians(rot.w);
      obj->transform = powergl_mat4_rot(obj->transform, rot.w, rot.xyz);
    }
  }

  for(size_t i = 0; i < node->n_translate; i++) {
    powergl_vec3 trans;
    powergl_vec3_copy(&trans, node->c_translate[i]->content, node->c_translate[i]->n_content);
    obj->transform = powergl_mat4_translate(obj->transform, trans);
  }
    
  obj->matrix_flag = 1;
    
#if DEBUG_OUTPUT
  powergl_mat4_print(node->c_id, obj->transform);
#endif
}

void powergl_build_object(powergl_collada_core_node *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s -> %s\n", __func__, node->c_id);
#endif

  if(node->c_id != NULL) {
    obj->id = powergl_resize(NULL, (strlen(node->c_id) + 1), sizeof(char));
    strcpy(obj->id, node->c_id);
  }

  if(node->n_matrix > 0) {
    powergl_build_transform_matrix(node, obj);
  } else if(node->n_translate > 0 || node->n_rotate > 0) {
    powergl_build_transform_TransRotLoc(node, obj);
  } else {
    assert(0);
    // init def transform
  }// if node has transform

  if(node->n_instance_geometry > 0) {
    powergl_build_geometry(node, obj);
  } // if node has instance_geometry

  if(node->n_instance_camera > 0) {
    obj->camera = powergl_resize(NULL, 1, sizeof(powergl_camera));
    powergl_build_camera(node, obj);
  } // if node has instance_camera

  if(node->n_instance_light > 0) {
    obj->light = powergl_resize(NULL, 1, sizeof(powergl_light));
    powergl_build_light(node, obj);
  } // if node has instance_light
}
#undef DEBUG_OUTPUT
