#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <string.h>
#include <stdlib.h>
#include "src/event.h"
#include "third_party/nuklear/nuklear.h"
#include "third_party/nuklear/nuklear_sdl_gl3.h"
#include "src/window/window.h"
#include "src/window/headless.h"
#include "src/rendering/visualscene.h"
#include "src/rendering/object.h"
#include "src/rendering/grid.h"
#include "src/rendering/orientation_gizmo.h"
#include "src/rendering/pipeline.h"
#include "src/ui/scene_hierarchy.h"
#include "src/png/png_loader.h"

#define MAX_VERTEX_MEMORY (512 * 1024)
#define MAX_ELEMENT_MEMORY (128 * 1024)

static struct nk_context *nkctx;

static powergl_object *cube;
static powergl_object grid;
static powergl_object gizmo;
static powergl_object *object_list[3];
static int frame_counter = 0;
static const int max_frames = 1;
static int png_mismatch = 0;

static void scene_create(powergl_visualscene *scene){
    const char *dae = TEST_SRCDIR "/vertexcolored_cube.dae";
    powergl_scene_build(scene, dae);
    scene->main_camera = powergl_scene_find(scene, "Camera");
    if(!scene->main_camera)
    {
        scene->main_camera = powergl_camera_default();
        powergl_scene_add_object(scene, scene->main_camera, NULL);
    }
    cube = powergl_scene_find(scene, "Cube");
    object_list[0] = cube;
    powergl_grid_create(&grid, 10);
    object_list[1] = &grid;
    powergl_orientation_gizmo_create(&gizmo);
    object_list[2] = &gizmo;
    if(scene->main_camera)
        scene->main_camera->event_flag = 1;
    powergl_pipeline3_create(&scene->pipeline3, object_list, 3);
}

static void scene_events(powergl_visualscene *scene, powergl_event *e, float dt){
    powergl_scene_handle_picking(scene, e);
    if(scene->main_camera)
        powergl_event_handle(scene->main_camera, e, dt);
}

static void scene_run(powergl_visualscene *scene, float dt){
    if(cube && scene->main_camera)
    {
        powergl_object_fps_controller(scene->main_camera, dt);
        powergl_object_update_transform(scene->main_camera, dt);
        powergl_camera_update(scene->main_camera);
        powergl_object_update_mvp(cube, scene->main_camera);
        powergl_object_update_mvp(&grid, scene->main_camera);
        powergl_orientation_gizmo_update(&gizmo, scene->main_camera);
        size_t count = powergl_enable_grid ? 3 : 2;
        powergl_pipeline3_render(&scene->pipeline3, object_list, count);
        scene->main_camera->camera.vp_flag = 0;
    }


    if(frame_counter < max_frames){
        char fname[64];
        snprintf(fname, sizeof(fname), "frame_%02d.png", frame_counter);
        powergl_window_screenshot(fname);
        char ref[256];
        snprintf(ref, sizeof(ref), "%s/vertexcoloredcube_demo.png", TEST_SRCDIR);
        int same = powergl_png_compare(fname, ref);
        if(!same)
            png_mismatch = 1;
        printf("frame %d %s reference\n", frame_counter, same ? "matches" : "differs from");
        frame_counter++;
    }
}

int main(){
    powergl_visualscene scene = {0};
    setenv("POWERGL_GL_DEBUG", "0", 0);
    const char *grid_env = getenv("POWERGL_ENABLE_GRID");
    if(grid_env && strcmp(grid_env, "0") == 0)
        powergl_enable_grid = 0;
    scene.create = scene_create;
    scene.run = scene_run;
    scene.handle_events = scene_events;

    const char *headless = getenv("POWERGL_HEADLESS");
    if(headless && strcmp(headless, "1") == 0){
        powergl_window *wnd =
            powergl_window_new_with_backend(&scene, &powergl_window_backend_headless);
        if(!powergl_window_create(wnd, 640, 480))
            return 1;
        int ret = powergl_window_run(wnd);
        return ret || png_mismatch;
    } else {
        powergl_window *wnd = powergl_window_new(&scene);
        if(!powergl_window_create(wnd, 640, 480))
            return 1;

        nkctx = nk_sdl_init((SDL_Window *)powergl_window_get_native_window(wnd));
        struct nk_font_atlas *atlas;
        nk_sdl_font_stash_begin(&atlas);
        nk_sdl_font_stash_end();

        wnd->root_scene->create(wnd->root_scene);
        wnd->root_scene->pipeline3.forceUpdate = 1;

        SDL_Event e;
        powergl_event pe;
        int quit = 0;
        Uint64 last_counter = SDL_GetPerformanceCounter();
        Uint64 freq = SDL_GetPerformanceFrequency();

        while(!quit){
            Uint64 current_counter = SDL_GetPerformanceCounter();
            float dt = (float)(current_counter - last_counter) / (float)freq;

            nk_input_begin(nkctx);
            while(SDL_PollEvent(&e)){
                nk_sdl_handle_event(&e);
                powergl_sdl_translate_event(&e, &pe);
                scene.handle_events(&scene, &pe, dt);
                if(pe.type == POWERGL_EVENT_WINDOW_CLOSE)
                    quit = 1;
            }
            nk_input_end(nkctx);

            scene.run(&scene, dt);

            powergl_ui_draw_scene_hierarchy(nkctx, &scene, nk_rect(10,10,250,400));
                                           
            nk_sdl_render(NK_ANTI_ALIASING_OFF, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);

            powergl_window_swap_buffers(wnd);
            last_counter = current_counter;
        }

        nk_sdl_shutdown();
        return png_mismatch;
    }
}
