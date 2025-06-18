#include <SDL2/SDL.h>
#include <png.h>
#include <string.h>
#include <stdlib.h>
#include "src/window/window.h"
#include "src/rendering/visualscene.h"
#include "src/rendering/object.h"
#include "src/rendering/pipeline.h"

static powergl_object *cube;
static powergl_object *cube_list[1];
static int frame_counter = 0;
static const int max_frames = 10;

static void save_png(const char *filename){
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    int width = vp[2];
    int height = vp[3];
    size_t size = (size_t)width * height * 3;
    unsigned char *pixels = (unsigned char*)malloc(size);
    if(!pixels){
        printf("failed to allocate %zu bytes for screenshot\n", size);
        return;
    }
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    FILE *fp = fopen(filename, "wb");
    if(!fp){
        printf("cannot open %s for writing\n", filename);
        free(pixels);
        return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr){
        printf("failed to create png write struct\n");
        fclose(fp);
        free(pixels);
        return;
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr){
        printf("failed to create png info struct\n");
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);
        free(pixels);
        return;
    }
    if(setjmp(png_jmpbuf(png_ptr))){
        printf("png error writing to %s\n", filename);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        free(pixels);
        return;
    }
    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    png_bytep *row_pointers = malloc(sizeof(png_bytep) * height);
    if(!row_pointers){
        printf("failed to allocate row pointers\n");
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        free(pixels);
        return;
    }
    for(int y = 0; y < height; ++y)
        row_pointers[height - 1 - y] = pixels + y * width * 3;
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    free(row_pointers);
    fclose(fp);
    free(pixels);
}

static int compare_png(const char *a, const char *b){
    powergl_png pa = powergl_png_load(a);
    powergl_png pb = powergl_png_load(b);
    if(!pa.data){
        printf("failed to load image %s\n", a);
        if(pb.data) free(pb.data);
        return 0;
    }
    if(!pb.data){
        printf("failed to load image %s\n", b);
        free(pa.data);
        return 0;
    }
    if(pa.width != pb.width || pa.height != pb.height || pa.color_type != pb.color_type){
        printf("image dimensions or color type differ\n");
        free(pa.data);
        free(pb.data);
        return 0;
    }
    int bpp = (pa.color_type == PNG_COLOR_TYPE_RGB) ? 3 : 4;
    size_t size = (size_t)pa.width * pa.height * bpp;
    int res = memcmp(pa.data, pb.data, size) == 0;
    if(!res)
        printf("image data differs between %s and %s\n", a, b);
    free(pa.data);
    free(pb.data);
    return res;
}

static void scene_create(powergl_visualscene *scene){
    const char *dae = TEST_SRCDIR "/cube.dae";
    powergl_scene_build(scene, dae);
    scene->main_camera = powergl_scene_find(scene, "Camera");
    if(!scene->main_camera)
        scene->main_camera = powergl_camera_default();
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
    if(frame_counter < max_frames){
        char fname[64];
        snprintf(fname, sizeof(fname), "frame_%02d.png", frame_counter);
        save_png(fname);
        char ref[256];
        snprintf(ref, sizeof(ref), "%s/demo_cube.png", TEST_SRCDIR);
        int same = compare_png(fname, ref);
        printf("frame %d %s reference\n", frame_counter, same ? "matches" : "differs from");
        frame_counter++;
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
