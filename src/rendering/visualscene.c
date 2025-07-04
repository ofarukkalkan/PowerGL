#include "visualscene.h"

#include "../powergl.h"
#include "../collada/collada.h"
#include "../collada/importer.h"
#include "dae2object.h"

#include <GL/glcorearb.h>
#include <stdio.h>
#include <string.h>


void powergl_scene_build(powergl_visualscene *this, const char *file) {
#if DEBUG_OUTPUT
    printf("%s\n", __func__);
    printf("the dae file will be parsed = %s \n", file);
#endif
    int zup = powergl_collada_is_z_up(file);
    powergl_collada_core_COLLADA  *root = (powergl_collada_core_COLLADA *)powergl_collada_parse(file);
    powergl_collada_core_scene  *scene = root->c_scene[0];
    powergl_collada_core_InstanceWithExtra  *instance = scene->c_instance_visual_scene[0];
    powergl_collada_core_visual_scene  *vscene =  instance->r_visual_scene;

    
    size_t size = vscene->n_node;
    this->objects = powergl_resize(NULL, size, sizeof(powergl_object *));
    this->n_object = size;
    this->main_camera = NULL;
    this->main_light = NULL;

    for(size_t i = 0; i < size; i++) {
        powergl_collada_core_node  *node = vscene->c_node[i];
        this->objects[i] = powergl_resize(NULL, 1, sizeof(powergl_object));
	this->objects[i]->parent = NULL;
	
        powergl_build_object(node, root, this->objects[i], zup);

    } // for each node
}

static powergl_object *find_object(powergl_object *root, const char *id){

  powergl_object *res = NULL;

  if(strcmp(id, root->id) == 0){
    return root;
  }

  for(size_t i = 0; i < root->n_object; i++) {
    res = find_object(root->objects[i], id);
    if( res != NULL) {
      return res;
    }   
  }

  return NULL;
}

powergl_object *powergl_scene_find(powergl_visualscene *scene, const char *id) {
  powergl_object *res = NULL;
  
  for(size_t i = 0; i < scene->n_object; i++) {
      
    res = find_object(scene->objects[i], id);
    if( res != NULL) {
      return res;
    }
  }

  return NULL;
}

static void pick_recursive(powergl_object **objs, size_t n_obj, powergl_vec2 pos,
                           powergl_vec4 vp, powergl_object **best_obj,
                           float *best_dist)
{
  for(size_t i = 0; i < n_obj; ++i){
    powergl_object *obj = objs[i];
    if(obj->n_object > 0)
      pick_recursive(obj->objects, obj->n_object, pos, vp, best_obj, best_dist);

    if(obj->geometry.visible_flag == 0)
      continue;

    for(size_t j = 0; j < obj->geometry.n_vertex; j += 3){
      powergl_vec3 P;
      int hit = powergl_intersect_ray_tri_mesh(&obj->geometry.vertex[j], 3,
                                               obj->transform.mvp, pos, vp,
                                               &P, 0);
      if(hit && P.z >= 0.0f && P.z < *best_dist){
        *best_dist = P.z;
        *best_obj = obj;
      }
    }
  }
}

powergl_object *powergl_scene_pick(powergl_visualscene *scene, powergl_object *cam,
                                   powergl_vec2 mouse, powergl_vec4 viewport,
                                   float *out_dist)
{
  if(!scene || !cam)
    return NULL;

  float dist = 1e30f;
  powergl_object *best = NULL;

  /* ensure MVP matrices are up to date */
  /*for(size_t i=0;i<scene->n_object;i++)
    powergl_object_update_mvp(scene->objects[i], cam);*/

  pick_recursive(scene->objects, scene->n_object, mouse, viewport, &best, &dist);

  if(out_dist)
    *out_dist = dist;
  return best;
}

void powergl_scene_handle_picking(powergl_visualscene *scene, powergl_event *e)
{
  if(!scene || !scene->main_camera || !e)
    return;

  GLint vpdata[4];
  glGetIntegerv(GL_VIEWPORT, vpdata);
  powergl_vec4 vp = {(float)vpdata[0], (float)vpdata[1],
                     (float)vpdata[2], (float)vpdata[3]};
  powergl_vec2 pos = {(float)e->x, (float)e->y};

  if(e->type == POWERGL_EVENT_MOUSE_MOVE){
    powergl_object *hit = powergl_scene_pick(scene, scene->main_camera, pos, vp, NULL);

    /* do not hover the object already selected */
    if(hit == scene->selected_object)
      hit = NULL;

    if(hit != scene->hovered_object){
      if(scene->hovered_object)
        scene->hovered_object->hovered = 0;
      scene->hovered_object = hit;
      if(hit)
        hit->hovered = 1;
    }
  } else if(e->type == POWERGL_EVENT_MOUSE_BUTTON_DOWN &&
            e->button == POWERGL_MOUSE_BUTTON_LEFT){
    powergl_object *hit = powergl_scene_pick(scene, scene->main_camera, pos, vp, NULL);
    if(scene->selected_object && scene->selected_object != hit){
      scene->selected_object->selected = 0;
    }
    scene->selected_object = hit;
    if(hit){
      hit->selected = 1;
      hit->hovered = 0;
      scene->hovered_object = NULL;
    }
  }
}
