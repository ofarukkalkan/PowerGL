#include "dae2object.h"

#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT 1
#endif

typedef struct tokens_t {
  char **arr;
  size_t n;
} tokens;

tokens parse_sid(const char *str){
  tokens toks;
  toks.arr = NULL;
  toks.n = 0;
  
  size_t j = 0;
  size_t str_length = strlen(str) + 1;
  
  for(size_t i = 0; i < str_length; i++){
    
    if(str[i] == '/' || str[i] == '.' || str[i] == '\0'){
      
      toks.arr = powergl_resize(toks.arr, ++toks.n, sizeof(char*));
      size_t size = i-j;
      toks.arr[toks.n-1] = powergl_resize(NULL, size + 1, sizeof(char));
      
      for(size_t k=0; k < size; k++){
	toks.arr[toks.n-1][k] = str[j++];
      }
      toks.arr[toks.n-1][size] = '\0';
      j++;
    }
  }
  return toks;
}


void powergl_build_animation(powergl_collada_core_library_animations *anim_lib, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  
  obj->animation.n_channel = 0;
  char new_ch_flag = 0;
  size_t ch_index = 0;
  
  for(size_t i=0; i<anim_lib->n_animation; i++){
    
    powergl_collada_core_channel *ch = anim_lib->c_animation[i]->c_channel[0];
    tokens toks = parse_sid(ch->c_target);

    if(strcmp(obj->id, toks.arr[0]) == 0){

      if(strcmp("location", toks.arr[1]) == 0){

	if(strcmp("X", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target = &obj->transform.location.x;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;
 
	} else if(strcmp("Y", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target = &obj->transform.location.y;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;
	  
	} else if(strcmp("Z", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target = &obj->transform.location.z;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;

	} 
		   
      } else if (strcmp("rotationX", toks.arr[1]) == 0){
	
	if(strcmp("ANGLE", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target =  &obj->transform.rotation_x.w;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;
	}

      } else if (strcmp("rotationY", toks.arr[1]) == 0){
	
	if(strcmp("ANGLE", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target =  &obj->transform.rotation_y.w;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;
	}
	
      } else if (strcmp("rotationZ", toks.arr[1]) == 0){
	
	if(strcmp("ANGLE", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target = &obj->transform.rotation_z.w;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;
	}

      } else if(strcmp("scale", toks.arr[1]) == 0){
	
	if(strcmp("X", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target = &obj->transform.scale.x;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;
 
	} else if(strcmp("Y", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target = &obj->transform.scale.y;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;
	  
	} else if(strcmp("Z", toks.arr[2]) == 0){
	  obj->animation.n_channel++;
	  ch_index++;
	  obj->animation.channels[ch_index-1].target = &obj->transform.scale.z;
	  obj->animated_flag = 1;
	  new_ch_flag = 1;

	}
	
      }


      if(new_ch_flag == 1){
	new_ch_flag = 0;
	powergl_collada_core_input_local **inputs = anim_lib->c_animation[i]->c_sampler[0]->c_input;
	    
	for(size_t k=0; k <anim_lib->c_animation[i]->c_sampler[0]->n_input; k++){
	      
	  if(strcmp(inputs[k]->c_semantic, "INPUT") == 0){
	    powergl_collada_core_source *in_pos = inputs[k]->r_anim_source;
	    powergl_collada_core_accessor *in_acc = in_pos->c_technique_common[0]->c_accessor[0];
	    powergl_collada_core_float_array *in_arr = in_acc->r_float_array;

	    size_t count = in_acc->c_count;

	    obj->animation.channels[ch_index-1].inputs = powergl_resize(NULL, count, sizeof(GLfloat));
	    obj->animation.channels[ch_index-1].count = count;

	    for(size_t l=0; l < count; l++){
	      obj->animation.channels[ch_index-1].inputs[l] = (GLfloat)in_arr->content[l];
	    }
		
	  } else if(strcmp(inputs[k]->c_semantic, "OUTPUT") == 0){
	    powergl_collada_core_source *out_pos = inputs[k]->r_anim_source;
	    powergl_collada_core_accessor *out_acc = out_pos->c_technique_common[0]->c_accessor[0];
	    powergl_collada_core_float_array *out_arr = out_acc->r_float_array;
	    	
	    size_t count = out_acc->c_count;

	    obj->animation.channels[ch_index-1].outputs = powergl_resize(NULL, count, sizeof(GLfloat));

	    for(size_t l=0; l < count; l++){
	      if(strcmp("ANGLE", toks.arr[2]) == 0){
		obj->animation.channels[ch_index-1].outputs[l] = powergl_float_to_radians((GLfloat)out_arr->content[l]);
	      } else {
		obj->animation.channels[ch_index-1].outputs[l] = (GLfloat)out_arr->content[l];
	      }
	    }

	  } else if(strcmp(inputs[k]->c_semantic, "INTERPOLATION") == 0){
	    powergl_collada_core_source *int_pos = inputs[k]->r_anim_source;
	    powergl_collada_core_accessor *int_acc = int_pos->c_technique_common[0]->c_accessor[0];
	    powergl_collada_core_Name_array *int_arr = int_acc->r_Name_array;

	    size_t count = int_acc->c_count;

	    obj->animation.channels[ch_index-1].types = powergl_resize(NULL, count, sizeof(char*));

	    for(size_t l=0; l < count; l++){
	      obj->animation.channels[ch_index-1].types[l] = powergl_resize(NULL, strlen(int_arr->content[l]) + 1, sizeof(char));
	      strcpy(obj->animation.channels[ch_index-1].types[l], int_arr->content[l]);
	    }
		
	  }
	}
      }
      
    }

    free(toks.arr);
  }
}


void powergl_build_geometry(powergl_collada_core_node *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  powergl_collada_core_geometry  *geo =  node->c_instance_geometry[0]->r_geometry;
  powergl_collada_core_mesh  *mesh = geo->c_mesh[0];
  
  if(mesh->n_triangles > 0){
	
    powergl_collada_core_triangles *tris = mesh->c_triangles[0];
    powergl_collada_core_ListOfUInts *prim = tris->c_p[0];

    powergl_collada_core_source *pos_src;
    powergl_collada_core_accessor *pos_acc;
    powergl_collada_core_float_array *pos_arr;

    powergl_collada_core_source *norm_src;
    powergl_collada_core_accessor *norm_acc;
    powergl_collada_core_float_array *norm_arr;

    powergl_collada_core_source *color_src;
    powergl_collada_core_accessor *color_acc;
    powergl_collada_core_float_array *color_arr;

    powergl_collada_core_source *texcoord_src;
    powergl_collada_core_accessor *texcoord_acc;
    powergl_collada_core_float_array *texcoord_arr;

	
    char vertex_attrib_enabled = 0;
    char normal_attrib_enabled = 0;
    char color_attrib_enabled = 0;
    char texcoord_attrib_enabled = 0; 
    
    size_t vertex_attrib_offset = 0;
    size_t normal_attrib_offset = 0;
    size_t color_attrib_offset = 0;
    size_t texcoord_attrib_offset = 0;
 
    size_t vertex_attrib_stride = 0;
    size_t normal_attrib_stride = 0;
    size_t color_attrib_stride = 0;
    size_t texcoord_attrib_stride = 0;

    size_t n_enabled_attrib = tris->n_input;

    for(size_t j = 0; j < tris->n_input; j++){
	
      if(strcmp(tris->c_input[j]->c_semantic, "VERTEX") == 0){
	vertex_attrib_offset = j;
	vertex_attrib_enabled = 1;
       
	pos_src = tris->c_input[j]->r_vertices->c_input[0]->r_mesh_source;
	pos_acc = pos_src->c_technique_common[0]->c_accessor[0];
	pos_arr = pos_acc->r_float_array;

	vertex_attrib_stride = pos_acc->c_stride;
	    
      } else if(strcmp(tris->c_input[j]->c_semantic, "NORMAL") == 0){
	normal_attrib_offset = j;
	normal_attrib_enabled = 1;
	
	norm_src = tris->c_input[j]->r_mesh_source;
	norm_acc = norm_src->c_technique_common[0]->c_accessor[0];
	norm_arr = norm_acc->r_float_array;

	normal_attrib_stride = norm_acc->c_stride;
	    
      } else if(strcmp(tris->c_input[j]->c_semantic, "COLOR") == 0){
	color_attrib_offset = j;
	color_attrib_enabled = 1;

	color_src = tris->c_input[j]->r_mesh_source;
	color_acc = color_src->c_technique_common[0]->c_accessor[0];
	color_arr = color_acc->r_float_array;

	color_attrib_stride = color_acc->c_stride;

      } else if(strcmp(tris->c_input[j]->c_semantic, "TEXCOORD") == 0){
	texcoord_attrib_offset = j;
	texcoord_attrib_enabled = 1; 

	texcoord_src = tris->c_input[j]->r_mesh_source;
	texcoord_acc = texcoord_src->c_technique_common[0]->c_accessor[0];
	texcoord_arr = texcoord_acc->r_float_array;

	texcoord_attrib_stride = texcoord_acc->c_stride;

      }
    }


    if(vertex_attrib_enabled == 1){
      obj->geometry.visible_flag = 1;
      obj->geometry.triangles.count = tris->c_count;

      obj->geometry.vertex = powergl_resize(NULL, tris->c_count * 3, sizeof(powergl_vec3));
      obj->geometry.n_vertex = tris->c_count * 3;
      obj->geometry.vertex_flag = 1;
    } else {
      assert(0); // if there's no vertex no reason to continue. At this point importer should warn the user and return
    }
    
    if(color_attrib_enabled == 1){ // color is optional
      obj->geometry.triangles.color = powergl_resize(NULL, tris->c_count * 3, sizeof(powergl_vec3));
      obj->geometry.triangles.n_color = tris->c_count * 3;
      obj->geometry.triangles.color_flag = 1;
    }

    if(normal_attrib_enabled == 1){ // normal is mandatory for lighting calculations
      obj->geometry.triangles.normal = powergl_resize(NULL, tris->c_count * 3, sizeof(powergl_vec3));
      obj->geometry.triangles.n_normal = tris->c_count * 3;
      obj->geometry.triangles.normal_flag = 1;
    }

    if(texcoord_attrib_enabled == 1){ //texcoord is optional
      obj->geometry.triangles.texcoord = powergl_resize(NULL, tris->c_count * 3, sizeof(powergl_vec3));
      obj->geometry.triangles.n_texcoord = tris->c_count * 3;
      obj->geometry.triangles.texcoord_flag = 1;
    }


    size_t pos_index;
    size_t norm_index;
    size_t color_index;
    size_t texcoord_index;
    
    // for each vertex
    for(size_t i = 0; i < tris->c_count * 3; i++){
      
      pos_index = prim->content[i * n_enabled_attrib + vertex_attrib_offset];
      obj->geometry.vertex[i].x = pos_arr->content[pos_index * vertex_attrib_stride + 0];
      obj->geometry.vertex[i].y = pos_arr->content[pos_index * vertex_attrib_stride + 1];
      obj->geometry.vertex[i].z = pos_arr->content[pos_index * vertex_attrib_stride + 2];

      if(normal_attrib_enabled == 1){
	norm_index = prim->content[i * n_enabled_attrib + normal_attrib_offset];
	obj->geometry.triangles.normal[i].x = norm_arr->content[norm_index * normal_attrib_stride + 0];
	obj->geometry.triangles.normal[i].y = norm_arr->content[norm_index * normal_attrib_stride + 1];
	obj->geometry.triangles.normal[i].z = norm_arr->content[norm_index * normal_attrib_stride + 2];
      }

      if(color_attrib_enabled == 1){
	color_index = prim->content[i * n_enabled_attrib + color_attrib_offset];
	obj->geometry.triangles.color[i].x = color_arr->content[color_index * color_attrib_stride + 0];
	obj->geometry.triangles.color[i].y = color_arr->content[color_index * color_attrib_stride + 1];
	obj->geometry.triangles.color[i].z = color_arr->content[color_index * color_attrib_stride + 2];
      }

      if(texcoord_attrib_enabled == 1){
	texcoord_index = prim->content[i * n_enabled_attrib + texcoord_attrib_offset];
	obj->geometry.triangles.texcoord[i].x = texcoord_arr->content[texcoord_index * texcoord_attrib_stride + 0];
	obj->geometry.triangles.texcoord[i].y = texcoord_arr->content[texcoord_index * texcoord_attrib_stride + 1];
      }

      /////////////////////// bounding box
      if(obj->geometry.vertex[i].x < obj->geometry.min_x){
	obj->geometry.min_x = obj->geometry.vertex[i].x;
      }
      if(obj->geometry.vertex[i].y < obj->geometry.min_y){
	obj->geometry.min_y = obj->geometry.vertex[i].y;
      }
      if(obj->geometry.vertex[i].z < obj->geometry.min_z){
	obj->geometry.min_z = obj->geometry.vertex[i].z;
      }
      
      if(obj->geometry.vertex[i].x > obj->geometry.max_x){
	obj->geometry.max_x = obj->geometry.vertex[i].x;
      }
      if(obj->geometry.vertex[i].y > obj->geometry.max_y){
	obj->geometry.max_y = obj->geometry.vertex[i].y;
      }
      if(obj->geometry.vertex[i].z > obj->geometry.max_z){
	obj->geometry.max_z = obj->geometry.vertex[i].z;
      }
      ///////////////////////////////////////////////////

#if DEBUG_OUTPUT
      /*
      powergl_vec3_print("vertex", obj->geometry.vertex[i]);
      powergl_vec3_print("normal", obj->geometry.triangles.normal[i]);
      powergl_vec3_print("color", obj->geometry.triangles.color[i]);
      */
#endif
	    
    }

    // min_x, min_y, min_z
    obj->geometry.bounds[0].x = obj->geometry.min_x;
    obj->geometry.bounds[0].y = obj->geometry.min_y;
    obj->geometry.bounds[0].z = obj->geometry.min_z;
    // min_x, min_y, max_z
    obj->geometry.bounds[1].x = obj->geometry.min_x;
    obj->geometry.bounds[1].y = obj->geometry.min_y;
    obj->geometry.bounds[1].z = obj->geometry.max_z;
    // min_x, max_y, min_z
    obj->geometry.bounds[2].x = obj->geometry.min_x;
    obj->geometry.bounds[2].y = obj->geometry.max_y;
    obj->geometry.bounds[2].z = obj->geometry.min_z;
    // min_x, max_y, max_z
    obj->geometry.bounds[3].x = obj->geometry.min_x;
    obj->geometry.bounds[3].y = obj->geometry.max_y;
    obj->geometry.bounds[3].z = obj->geometry.max_z;
    // max_x, min_y, min_z
    obj->geometry.bounds[4].x = obj->geometry.max_x;
    obj->geometry.bounds[4].y = obj->geometry.min_y;
    obj->geometry.bounds[4].z = obj->geometry.min_z;
    // max_x, min_y, max_z
    obj->geometry.bounds[5].x = obj->geometry.max_x;
    obj->geometry.bounds[5].y = obj->geometry.min_y;
    obj->geometry.bounds[5].z = obj->geometry.max_z;
     // max_x, max_y, min_z
    obj->geometry.bounds[6].x = obj->geometry.max_x;
    obj->geometry.bounds[6].y = obj->geometry.max_y;
    obj->geometry.bounds[6].z = obj->geometry.min_z;
    // max_x, max_y, max_z
    obj->geometry.bounds[7].x = obj->geometry.max_x;
    obj->geometry.bounds[7].y = obj->geometry.max_y;
    obj->geometry.bounds[7].z = obj->geometry.max_z;

#if DEBUG_OUTPUT
    for(size_t i=0; i<8; i++){
      powergl_vec3_print("bounds", obj->geometry.bounds[i]);
    }
#endif

  }
            
}

void build_collider(float bounds[8]){


}

void powergl_build_collider(powergl_object *obj){
  
  
}


void powergl_build_camera(powergl_collada_core_node *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  powergl_collada_core_camera  *cam_elem = node->c_instance_camera[0]->r_camera;
  powergl_collada_core_perspective  *pers = cam_elem->c_optics[0]->c_technique_common[0]->c_perspective[0];

  if(pers != NULL) {
    obj->camera.type = 'p';

    if(pers->c_xfov != NULL) {
      obj->camera.xfov = powergl_float_to_radians(pers->c_xfov[0]->content[0]);
    }

    if(pers->c_yfov != NULL) {
      obj->camera.yfov = powergl_float_to_radians(pers->c_yfov[0]->content[0]);
    }

    obj->camera.znear = pers->c_znear[0]->content[0];
    obj->camera.zfar = pers->c_zfar[0]->content[0];
    obj->camera.aspect_ratio = pers->c_aspect_ratio[0]->content[0];
  }

  obj->camera.view = powergl_mat4_ident();
  obj->camera.view_flag = 0;
  
  obj->camera.projection = powergl_mat4_ident();
  obj->camera.projection_flag = 0;
  
  obj->camera.vp = powergl_mat4_ident();
  obj->camera.vp_flag = 0;
    
  // if obj's transform is not inverted. (blender does not export a matrix called view transform.
  // but we can use inverse of obj's transform  as view transform)

  // if node has only matrix element use this
  // obj->camera.view = powergl_mat4_inv(obj->transform.world);
 
  // if obj's transform is ready to use as view transform.
  // obj->transform.world[3][2] should has negative sign.
  // obj->camera.view = obj->transform.world;
    
  /*
    powergl_vec3 eye = {{0.0f, 0.0f, 4.0f}};
    powergl_vec3 target = {{0.0f, 0.0f, 0.0f}};
    powergl_vec3 up = {{0.0f, 1.0f, 0.0f}};
    powergl_lookat(&obj->camera.view, &eye, &target, &up);
  */
    
#if DEBUG_OUTPUT
  powergl_mat4_print("view transform", obj->camera.view);
#endif

  // blender does not export any projection matrix. we can get it from its console by calling this func ->
  // bpy.data.objects['Camera'].calc_matrix_camera(1280,720)
  // or we can construct a proj. matrix from params under camera element
  // but there is a problem inside blender dae exporter, it only exports xfov param. so we should convert it to yfov
  if(obj->camera.type == 'p') {
    if(pers->c_yfov != NULL) {
      obj->camera.projection = powergl_mat4_perspectiveRH(obj->camera.yfov, obj->camera.aspect_ratio, obj->camera.znear, obj->camera.zfar);
    } else if(pers->c_xfov != NULL) {
      float tanHalfXfov = tanf(obj->camera.xfov / 2.0f);
      float X = tanHalfXfov * 2.0f * obj->camera.znear;
      float Y = X / obj->camera.aspect_ratio;
      float yfov = 2 * atanf( Y / (2.0f * obj->camera.znear));

      obj->camera.yfov = yfov;
      obj->camera.projection = powergl_mat4_perspectiveRH(obj->camera.yfov, obj->camera.aspect_ratio, obj->camera.znear, obj->camera.zfar);
    } else {
      obj->camera.projection = powergl_mat4_perspectiveRH(2.16f, 1.33f, 0.1f, 100.0f);
    }
    obj->camera.projection_flag = 1;

    obj->camera_flag = 1;
    
#if DEBUG_OUTPUT
    powergl_float_print("aspect", obj->camera.aspect_ratio);
    powergl_float_print("xfov", obj->camera.xfov);
    powergl_float_print("yfov", obj->camera.yfov);
    powergl_float_print("znear", obj->camera.znear);
    powergl_float_print("zfar", obj->camera.zfar);
    powergl_mat4_print("perspective projection transform", obj->camera.projection);
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

    if(sun->c_color != NULL) {
      if(sun->c_color[0]->content != NULL) {
	powergl_vec3_copy(&obj->light.color, sun->c_color[0]->content, sun->c_color[0]->n_content);
      }
    } else {
      obj->light.color.x = 1.0f;
      obj->light.color.y = 1.0f;
      obj->light.color.z = 1.0f;
    }
    obj->light.color_flag = 1;

#if DEBUG_OUTPUT
    powergl_vec3_print("light color", obj->light.color);
#endif
    ////////////////////////////////////////// direction
    // w set to 0 to get point at infinite. so it does not affect translation
    // default collada directional light ->
    powergl_vec4 v = {{0.0f, 0.0f, -1.0f, 0.0f }};

    if(obj->parent != NULL){
      
      obj->light.dir = powergl_vec3_norm(powergl_vec4_trans(v, obj->transform.world).xyz);
      
    } else {
      
      obj->light.dir = powergl_vec3_norm(powergl_vec4_trans(v, obj->transform.local).xyz);
      
    }  
    
    obj->light.type = 'd';
    obj->light.dir_flag = 1;

    obj->light_flag = 1;

#if DEBUG_OUTPUT
    powergl_vec3_print("normalized light dir", obj->light.dir);
#endif
  }
}

void powergl_build_transform(powergl_collada_core_node *node, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  obj->transform.local = powergl_mat4_ident();

  for(size_t i = 0; i < node->n_scale; i++) {
    powergl_vec3_copy(&obj->transform.scale, node->c_scale[i]->content, node->c_scale[i]->n_content);
    obj->transform.local = powergl_mat4_scale(obj->transform.local, obj->transform.scale);
  }

  for(size_t i = 0; i < node->n_rotate; i++) {
    // blender sid's = rotationX , rotationY, rotationZ
    // rotation mode should be XYZ in blender
    if(strcmp(node->c_rotate[i]->c_sid, "rotationX") == 0){
      obj->transform.rotation_x = (powergl_vec4){{.x = 1.0f, .y = 0.0f, .z = 0.0f, .w = node->c_rotate[i]->content[3]}};

    }else if(strcmp(node->c_rotate[i]->c_sid, "rotationY") == 0){
      obj->transform.rotation_y = (powergl_vec4){{.x = 0.0f, .y = 1.0f, .z = 0.0f, .w = node->c_rotate[i]->content[3]}};

    }else if(strcmp(node->c_rotate[i]->c_sid, "rotationZ") == 0) {
      obj->transform.rotation_z = (powergl_vec4){{.x = 0.0f, .y = 0.0f, .z = 1.0f, .w = node->c_rotate[i]->content[3]}};
    }
  }

  obj->transform.rotation_x.w = powergl_float_to_radians(obj->transform.rotation_x.w);
  obj->transform.rotation_y.w = powergl_float_to_radians(obj->transform.rotation_y.w);
  obj->transform.rotation_z.w = powergl_float_to_radians(obj->transform.rotation_z.w);
  
  // we get XYZ mode by multiplying in reverse order
  obj->transform.local = powergl_mat4_rot(obj->transform.local, obj->transform.rotation_z.w, obj->transform.rotation_z.xyz);
  obj->transform.local = powergl_mat4_rot(obj->transform.local, obj->transform.rotation_y.w, obj->transform.rotation_y.xyz);
  obj->transform.local = powergl_mat4_rot(obj->transform.local, obj->transform.rotation_x.w, obj->transform.rotation_x.xyz);
	  
  for(size_t i = 0; i < node->n_translate; i++) {
    powergl_vec3_copy(&obj->transform.location, node->c_translate[i]->content, node->c_translate[i]->n_content);
    obj->transform.local = powergl_mat4_translate(obj->transform.local, obj->transform.location);
  }

  if(obj->parent != NULL){

    obj->transform.world = powergl_mat4_mul(obj->parent->transform.world, obj->transform.local);
    
  } else {
    
    obj->transform.world = powergl_mat4_ident();
    
  }

  obj->transform.matrix_flag = 1;
    
#if DEBUG_OUTPUT
  powergl_mat4_print(node->c_id, obj->transform.local);
#endif
}

void powergl_build_object(powergl_collada_core_node  *node, powergl_collada_core_COLLADA *root, powergl_object *obj) {
#if DEBUG_OUTPUT
  printf("\n%s -> %s\n", __func__, node->c_id);
#endif

  if(node->c_id != NULL) {
    obj->id = powergl_resize(NULL, (strlen(node->c_id) + 1), sizeof(char));
    strcpy(obj->id, node->c_id);
  }

  if(node->n_translate > 0 || node->n_rotate > 0) {
    powergl_build_transform(node, obj);
  } else {
    assert(0);
    // init def transform
  }// if node has transform

  if(node->n_instance_geometry > 0) {
    powergl_build_geometry(node, obj);
    powergl_build_collider(obj);
  } // if node has instance_geometry

  if(node->n_instance_camera > 0) {
    powergl_build_camera(node, obj);
  } // if node has instance_camera
  
  if(node->n_instance_light > 0) {
    powergl_build_light(node, obj);
  } // if node has instance_light

  if(root->n_library_animations > 0){
    powergl_collada_core_library_animations *anim_lib = NULL;
    anim_lib = root->c_library_animations[0];
    powergl_build_animation(anim_lib, obj);
  }

  if(node->n_node > 0){

    obj->objects = powergl_resize(NULL, node->n_node, sizeof(powergl_collada_core_node*));
    obj->n_object = node->n_node;

    for(size_t i=0; i < node->n_node; i++){
      
      powergl_object *newobj = powergl_resize(NULL, 1, sizeof(powergl_object));
      newobj->parent = obj;
      obj->objects[i] = newobj;
      
      powergl_build_object(node->c_node[i], root, newobj);
    }
    
  }
  
}
#undef DEBUG_OUTPUT
