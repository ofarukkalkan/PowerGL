#include <SDL2/SDL.h>
#include "src/window/window.h"
#include "src/rendering/visualscene.h"
#include "src/rendering/object.h"
#include "src/rendering/pipeline.h"

static powergl_object *cube;
static powergl_object *cube_list[1];

static void scene_create(powergl_visualscene *scene){
    const char *dae = TEST_SRCDIR "/cube.dae";
    powergl_scene_build(scene, dae);
    scene->main_camera = powergl_scene_find(scene, "Camera");
    scene->main_light = powergl_scene_find(scene, "Light");
    cube = powergl_scene_find(scene, "Cube");
    cube_list[0] = cube;
    if(scene->main_camera)
        scene->main_camera->event_flag = 1;
    powergl_pipeline_create(&scene->pipeline, cube_list, 1);
}

static void scene_events(powergl_visualscene *scene, SDL_Event *e, float dt){
    if(scene->main_camera)
        powergl_event_handle(scene->main_camera, e, dt);
}

static void scene_run(powergl_visualscene *scene, float dt){
    if(scene->main_camera){
        powergl_object_fps_controller(scene->main_camera, dt);
        powergl_object_update_transform(scene->main_camera, dt);
        powergl_camera_update(scene->main_camera);
    }
    if(cube && scene->main_camera){
        powergl_object_update_mvp(cube, scene->main_camera);
    }
    if(cube){
        powergl_pipeline_render(&scene->pipeline, cube_list, 1, scene->main_light);
    }
}

int main(){
    powergl_visualscene scene = {0};
    scene.create = scene_create;
    scene.run = scene_run;
    scene.handle_events = scene_events;

    powergl_window *wnd = powergl_window_new(&scene);
    if(!powergl_window_create(wnd, 640, 480))
        return 1;
    return powergl_window_run(wnd);
}
