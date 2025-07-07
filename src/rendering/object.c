#define __STDC_WANT_LIB_EXT1__ 1

#include "object.h"
#include "../math/mat4x4.h"

#include <string.h>
#include <stdio.h>

#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT 1
#endif

float lerp(float x0, float x1, float t0, float t1, float t) {
  return x0 + ((x1-x0) * (t-t0)) / (t1-t0);
}

void powergl_animation_next(powergl_object *obj, float delta_time){

#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
     
  powergl_animation *anim = &obj->animation;
    
  for(size_t i = 0; i < anim->n_channel; i++){

    float  *pctime = &anim->channels[i].current_time;
    size_t *pckey = &anim->channels[i].current_key;   
    const char *ctype = anim->channels[i].types[*pckey];
      
    *pctime += delta_time;
      
    if(strcmp(ctype, "STEP") == 0){
	
      if(*pctime >= anim->channels[i].inputs[*pckey]){
	  
	*anim->channels[i].target = anim->channels[i].outputs[*pckey];	
	*pckey += 1;

	obj->transform.matrix_flag = 1;

	if(*pckey >= anim->channels[i].count){
	  *pckey = 0;
	  *pctime = 0.0f;
	}
      }
	
    } else if(strcmp(ctype, "LINEAR") == 0){

      if(*pctime >= anim->channels[i].inputs[*pckey+1]){	  
	*pckey += 1;

	if(*pckey >= anim->channels[i].count){
	  *pckey = 0;
	  *pctime = 0.0f;
	} 
      }
	
      *anim->channels[i].target = lerp(anim->channels[i].outputs[*pckey], anim->channels[i].outputs[*pckey+1],
				       anim->channels[i].inputs[*pckey], anim->channels[i].inputs[*pckey+1], *pctime);
      obj->transform.matrix_flag = 1;
	  
    } else {
      fprintf(stderr, "%s -> cant process next keyframe interpolation type = %s\n",
	      __func__ ,ctype);
    }
	
  }
}

void powergl_light_update(powergl_object *obj){


}

void powergl_camera_update(powergl_object *obj){

#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif

  powergl_mat4 rot, rot2;
  powergl_mat4 sca, sca2;
  powergl_mat4 tra, tra2;
  
  if(obj->transform.matrix_flag == 1){

    sca = powergl_mat4_ident();
    sca.c[0].x = 1.0f / obj->transform.scale.x;
    sca.c[1].y = 1.0f / obj->transform.scale.y;
    sca.c[2].z = 1.0f / obj->transform.scale.z;
    
    rot = powergl_mat4_ident();
    rot = powergl_mat4_rot(rot, obj->transform.rotation_z.w, obj->transform.rotation_z.xyz);
    rot = powergl_mat4_rot(rot, obj->transform.rotation_y.w, obj->transform.rotation_y.xyz);
    rot = powergl_mat4_rot(rot, obj->transform.rotation_x.w, obj->transform.rotation_x.xyz);
    rot = powergl_mat4_transpose(rot);

    tra = powergl_mat4_ident();
    tra.c[3].x = -obj->transform.location.x;
    tra.c[3].y = -obj->transform.location.y;
    tra.c[3].z = -obj->transform.location.z;

    obj->camera.view = powergl_mat4_mul(rot, tra);
    obj->camera.view = powergl_mat4_mul(sca, obj->camera.view);
    
    obj->camera.view_flag = 1;
  }

  if(obj->parent !=NULL && obj->parent->transform.matrix_flag == 1){

    sca2 = powergl_mat4_ident();
    sca2.c[0].x = 1.0f / obj->parent->transform.scale.x;
    sca2.c[1].y = 1.0f / obj->parent->transform.scale.y;
    sca2.c[2].z = 1.0f / obj->parent->transform.scale.z;
    
    rot2 = powergl_mat4_ident();
    rot2 = powergl_mat4_rot(rot2, obj->parent->transform.rotation_z.w, obj->parent->transform.rotation_z.xyz);
    rot2 = powergl_mat4_rot(rot2, obj->parent->transform.rotation_y.w, obj->parent->transform.rotation_y.xyz);
    rot2 = powergl_mat4_rot(rot2, obj->parent->transform.rotation_x.w, obj->parent->transform.rotation_x.xyz);
    rot2 = powergl_mat4_transpose(rot2);

    tra2 = powergl_mat4_ident();
    tra2.c[3].x = -obj->parent->transform.location.x;
    tra2.c[3].y = -obj->parent->transform.location.y;
    tra2.c[3].z = -obj->parent->transform.location.z;

    powergl_mat4 tmp = powergl_mat4_mul(rot2, tra2);
    obj->camera.view = powergl_mat4_mul(obj->camera.view, tmp);
    obj->camera.view = powergl_mat4_mul(sca2, obj->camera.view);
    
    obj->camera.view_flag = 1;
  }

  if(obj->camera.view_flag == 1 || obj->camera.projection_flag == 1) {
    
    obj->camera.vp = powergl_mat4_mul(obj->camera.projection, obj->camera.view);
    
    obj->camera.view_flag = 0;
    obj->camera.projection_flag = 0;
    obj->camera.vp_flag = 1;
    
#if DEBUG_OUTPUT
    powergl_mat4_print(obj->id, obj->camera.vp);
#endif
  }
  
}

void powergl_object_update_transform(powergl_object *obj, float delta_time){

#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif

  if(obj->animated_flag == 1){
    
    powergl_animation_next(obj, delta_time);
  }
  
  if(obj->transform.matrix_flag == 1){
    
    obj->transform.local = powergl_mat4_ident();
    obj->transform.local.c[0].x = obj->transform.scale.x;
    obj->transform.local.c[1].y = obj->transform.scale.y;
    obj->transform.local.c[2].z = obj->transform.scale.z;
    obj->transform.local = powergl_mat4_rot(obj->transform.local, obj->transform.rotation_z.w, obj->transform.rotation_z.xyz);
    obj->transform.local = powergl_mat4_rot(obj->transform.local, obj->transform.rotation_y.w, obj->transform.rotation_y.xyz);
    obj->transform.local = powergl_mat4_rot(obj->transform.local, obj->transform.rotation_x.w, obj->transform.rotation_x.xyz);     
    obj->transform.local.c[3].xyz = obj->transform.location;
    
#if DEBUG_OUTPUT
    powergl_mat4_print(obj->id, obj->transform.local);
#endif

  }

  if(obj->parent !=NULL){
    
    if(obj->parent->transform.matrix_flag == 1){
    
      obj->transform.world = powergl_mat4_mul(obj->parent->transform.world, obj->transform.local);
      obj->transform.matrix_flag = 1;

#if DEBUG_OUTPUT
      powergl_mat4_print(obj->id, obj->transform.world);
#endif
    } else {
      obj->transform.world = obj->transform.local;
    }
    
  } else {
    
    obj->transform.world = obj->transform.local;
    
  }


  for(size_t i=0; i < obj->n_object; i++){
    powergl_object_update_transform(obj->objects[i], delta_time);
  }    

}

void powergl_object_update_mvp(powergl_object *obj, powergl_object *cam){
  
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
     
  if(obj->transform.matrix_flag == 1 || cam->camera.vp_flag == 1){
	
    obj->transform.mvp = powergl_mat4_mul(cam->camera.vp, obj->transform.world);
    
    obj->transform.matrix_flag = 0;
    obj->transform.mvp_flag = 1;

#if DEBUG_OUTPUT
    powergl_mat4_print(obj->id, obj->transform.mvp);
#endif
  }

  for(size_t i=0; i < obj->n_object; i++){
    powergl_object_update_mvp(obj->objects[i], cam);
  }    

}

void powergl_object_fps_controller(powergl_object *obj, float delta_time){
  powergl_input_state e = obj->input;
  powergl_vec3 mov;
  mov.x = 0;
  mov.y = 0;
  mov.z = 0;
  float displacement = 10.0f * delta_time;
  
  if(e.key_a_pressed == 1){
    mov.x += -displacement;
  }
  if(e.key_d_pressed == 1){
    mov.x += displacement;
  }

  if(e.key_w_pressed == 1){
    mov.y += displacement;
  }
  if(e.key_s_pressed == 1){
    mov.y += -displacement;
  }

  if(e.key_space_pressed == 1){
    mov.z += displacement;
  }
  if(e.key_lctrl_pressed == 1){
    mov.z += -displacement;
  }
  
  if(mov.x !=0.0f || mov.y !=0.0f || mov.z !=0.0f){
    obj->transform.location = powergl_vec3_add(obj->transform.location, mov);
    powergl_vec3_print("object moved", obj->transform.location);
    obj->transform.matrix_flag = 1;
  }
  
}

void powergl_event_handle(powergl_object *obj, powergl_event *event, float delta_time){

  if(obj->event_flag == 1){

    switch (event->type) {

    case POWERGL_EVENT_KEY_DOWN:

      switch (event->key) {

      case POWERGL_KEY_A:
        obj->input.key_a_pressed = 1;
        break;
      case POWERGL_KEY_D:
        obj->input.key_d_pressed = 1;
        break;
      case POWERGL_KEY_W:
        obj->input.key_w_pressed = 1;
        break;
      case POWERGL_KEY_S:
        obj->input.key_s_pressed = 1;
        break;
      case POWERGL_KEY_SPACE:
        obj->input.key_space_pressed = 1;
        break;
      case POWERGL_KEY_LCTRL:
        obj->input.key_lctrl_pressed = 1;
        break;
      default:
        break;
      }

      break;

    case POWERGL_EVENT_KEY_UP:

      switch (event->key) {

      case POWERGL_KEY_A:
        obj->input.key_a_pressed = 0;
        break;
      case POWERGL_KEY_D:
        obj->input.key_d_pressed = 0;
        break;
      case POWERGL_KEY_W:
        obj->input.key_w_pressed = 0;
        break;
      case POWERGL_KEY_S:
        obj->input.key_s_pressed = 0;
        break;
      case POWERGL_KEY_SPACE:
        obj->input.key_space_pressed = 0;
        break;
      case POWERGL_KEY_LCTRL:
        obj->input.key_lctrl_pressed = 0;
        break;
      default:
        break;
      }

      break;

    default:
      break;

    }
  }
}

void powergl_transform_reset(powergl_transform *trans){
#if DEBUG_OUTPUT
  printf("\n%s\n", __func__);
#endif
  trans->local = powergl_mat4_ident();
  trans->world = powergl_mat4_ident();
  trans->mvp = powergl_mat4_ident();
  trans->location = powergl_vec3_zeros();
  trans->rotation_x = powergl_vec4_zeros();
  trans->rotation_y = powergl_vec4_zeros();
  trans->rotation_z = powergl_vec4_zeros();
  trans->scale = powergl_vec3_ones();

  trans->mvp_flag = 1;
  trans->matrix_flag = 1;

  
#if DEBUG_OUTPUT
  powergl_mat4_print("trasform has reset", trans->local);
#endif

}



void powergl_object_geometry_append(powergl_geometry *dest, powergl_geometry *src, powergl_vec3 offset, powergl_vec3 color){

  // merge vertices
  if(src->n_vertex > 0){

    assert(src->vertex);

    if(dest->n_vertex > 0 ){
    
      assert(dest->vertex);

      dest->vertex = powergl_resize(dest->vertex, src->n_vertex + dest->n_vertex , sizeof(powergl_vec3));


      for(size_t i = dest->n_vertex, j = 0; j <  src->n_vertex; i++, j++){
	dest->vertex[i] = powergl_vec3_add(src->vertex[j], offset);
      }

      
      dest->n_vertex += src->n_vertex;
      dest->vertex_flag = 1;
      dest->triangles.count += src->triangles.count;

    } else {
      // TODO : eger daha once allocate edilmis boyut yeterliyse yeniden allocation yapilmayacak
      dest->vertex = powergl_resize(NULL, src->n_vertex, sizeof(powergl_vec3));
 


#ifdef __STDC_LIB_EXT1__
      set_constraint_handler_s(ignore_handler_s);
      
      errno_t res = memcpy_s(dest->vertex, sizeof(powergl_vec3) * src->n_vertex, src->vertex, sizeof(powergl_vec3) * src->n_vertex);
      if(res!=0){
#if DEBUG_OUTPUT
	fprintf(stderr, "geometry vertex append failed while memcpy ing");
	assert(0);
#endif
      }


#else
      memcpy(dest->vertex, src->vertex, sizeof(powergl_vec3) * src->n_vertex);
      
#endif

      dest->n_vertex = src->n_vertex;
      dest->vertex_flag = 1;
      dest->visible_flag = 1;
      dest->triangles.count = src->triangles.count;
    
      
    }
    
    // merge colors
    if(src->triangles.n_color > 0){
	
      assert(src->triangles.color);

      if(dest->triangles.n_color > 0 ){
    
	assert(dest->triangles.color);

	dest->triangles.color = powergl_resize(dest->triangles.color, src->triangles.n_color + dest->triangles.n_color , sizeof(powergl_vec3));


	for(size_t i = dest->triangles.n_color, j = 0; j <  src->triangles.n_color; i++, j++){
	  dest->triangles.color[i] = color;
	}

      
	dest->triangles.n_color += src->triangles.n_color;
	dest->triangles.color_flag = 1;

      } else {
	// TODO : eger daha once allocate edilmis boyut yeterliyse yeniden allocation yapilmayacak
	dest->triangles.color = powergl_resize(NULL, src->triangles.n_color, sizeof(powergl_vec3));

	for(size_t i=0; i < src->triangles.n_color; i++){
	  dest->triangles.color[i] = color;
	}
      
	dest->triangles.n_color = src->triangles.n_color;
	dest->triangles.color_flag = 1;
      
      }

    } else {

    

#if DEBUG_OUTPUT
      fprintf(stderr, "geometry append failed, because color source is empty");
      assert(0);
#endif
    
    }
    
    
  } else {

    

#if DEBUG_OUTPUT
    fprintf(stderr, "geometry append failed, because vertex source is empty");
    assert(0);
#endif
    
  }

}

void powergl_object_geometry_reset(powergl_geometry *geo){

  if(geo->vertex != NULL){
    free(geo->vertex);
    geo->vertex = NULL;
    // TODO : vertex_flag = 0 islemi problemli olabilir
    geo->vertex_flag = 0;
    geo->n_vertex = 0;
    geo->triangles.count = 0;
    // TODO : eger diger attributeler de kullanilmislarsa onlar da silinecek
    // TODO : bound dizisi ve diger min_? max_? degeleri de resetlenebilir
  }

  if(geo->triangles.color != NULL){
    free(geo->triangles.color);
    geo->triangles.color = NULL;
    geo->triangles.color_flag = 0;
    geo->triangles.n_color = 0;
  }

  geo->primitive_type = GL_TRIANGLES;

}

powergl_object *powergl_camera_default(){
  powergl_object *cam = powergl_resize(NULL, 1, sizeof(powergl_object));
  memset(cam, 0, sizeof(powergl_object));
  cam->id = "Def. Camera";
  cam->name = "Def. Camera";
  cam->camera_flag = 1;
  cam->camera.type = 'p';
  cam->camera.aspect_ratio = 1.0f;
  cam->camera.yfov = powergl_float_to_radians(90.0f);
  cam->camera.xfov = 0.0f;
  cam->camera.znear = 0.1f;
  cam->camera.zfar = 100.0f;

  cam->transform.location = (powergl_vec3){{7.35f,-6.92f, 4.95f}};
  cam->transform.scale = (powergl_vec3){{1.0f, 1.0f, 1.0f}};
  cam->transform.rotation_x = (powergl_vec4){{1.0f,0.0f,0.0f, 1.1f}};
  cam->transform.rotation_y = (powergl_vec4){{0.0f,1.0f,0.0f, 0.0f}};
  cam->transform.rotation_z = (powergl_vec4){{0.0f,0.0f,1.0f, 0.81f}};
  
  cam->transform.local = powergl_mat4_ident();
  cam->transform.local = powergl_mat4_scale(cam->transform.local, cam->transform.scale);
  cam->transform.local = powergl_mat4_rot(cam->transform.local, cam->transform.rotation_z.w, cam->transform.rotation_z.xyz);
  cam->transform.local = powergl_mat4_rot(cam->transform.local, cam->transform.rotation_y.w, cam->transform.rotation_y.xyz);
  cam->transform.local = powergl_mat4_rot(cam->transform.local, cam->transform.rotation_x.w, cam->transform.rotation_x.xyz);
  cam->transform.local = powergl_mat4_translate(cam->transform.local, cam->transform.location);
  cam->transform.matrix_flag = 1;

  cam->camera.projection = powergl_mat4_perspectiveRH(cam->camera.yfov,
                                                      cam->camera.aspect_ratio,
                                                      cam->camera.znear,
                                                      cam->camera.zfar);
  cam->camera.projection_flag = 1;

  cam->camera.vp = powergl_mat4_mul(cam->camera.projection, cam->camera.view);
  cam->camera.vp_flag = 1;

  return cam;
}
