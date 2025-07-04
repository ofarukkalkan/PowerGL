#include <GL/glew.h>
#include "window.h"
#include <png.h>
#include <stdio.h>
#include <stdlib.h>

powergl_window *powergl_window_new_with_backend(powergl_visualscene *scene,
                                               const powergl_window_backend *backend)
{
    powergl_window *wnd = powergl_resize(NULL, 1, sizeof(*wnd));
    wnd->root_scene = scene;
    wnd->backend = backend;
    wnd->backend_data = NULL;
    wnd->width = wnd->height = 0;
    return wnd;
}

powergl_window *powergl_window_new(powergl_visualscene *scene)
{
    extern const powergl_window_backend powergl_window_backend_sdl; /* defined in window_sdl.c */
    return powergl_window_new_with_backend(scene, &powergl_window_backend_sdl);
}

int powergl_window_create(powergl_window *wnd, int width, int height)
{
    wnd->width = width;
    wnd->height = height;
    if(!wnd->backend || !wnd->backend->create)
        return 0;
    return wnd->backend->create(wnd, width, height);
}

int powergl_window_run(powergl_window *wnd)
{
    if(!wnd->backend || !wnd->backend->run)
        return 0;
    return wnd->backend->run(wnd);
}

int powergl_window_poll_event(powergl_window *wnd, powergl_event *ev)
{
    if(!wnd->backend || !wnd->backend->poll_event)
        return 0;
    return wnd->backend->poll_event(wnd, ev);
}

void powergl_window_swap_buffers(powergl_window *wnd)
{
    if(wnd->backend && wnd->backend->swap_buffers)
        wnd->backend->swap_buffers(wnd);
}

void *powergl_window_get_native_window(powergl_window *wnd)
{
    if(wnd->backend && wnd->backend->get_native_window)
        return wnd->backend->get_native_window(wnd);
    return NULL;
}

int powergl_window_screenshot(const char *filename)
{
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    int width = vp[2];
    int height = vp[3];
    size_t size = (size_t)width * height * 4;
    unsigned char *pixels = (unsigned char*)malloc(size);
    if(!pixels){
        fprintf(stderr, "failed to allocate %zu bytes for screenshot\n", size);
        return 0;
    }
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    FILE *fp = fopen(filename, "wb");
    if(!fp){
        fprintf(stderr, "cannot open %s for writing\n", filename);
        free(pixels);
        return 0;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_ptr){
        fprintf(stderr, "failed to create png write struct\n");
        fclose(fp);
        free(pixels);
        return 0;
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr){
        fprintf(stderr, "failed to create png info struct\n");
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);
        free(pixels);
        return 0;
    }
    if(setjmp(png_jmpbuf(png_ptr))){
        fprintf(stderr, "png error writing to %s\n", filename);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        free(pixels);
        return 0;
    }
    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGBA,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);
    png_bytep *row_pointers = malloc(sizeof(png_bytep) * height);
    if(!row_pointers){
        fprintf(stderr, "failed to allocate row pointers\n");
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        free(pixels);
        return 0;
    }
    for(int y = 0; y < height; ++y)
        row_pointers[height - 1 - y] = pixels + y * width * 4;
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    free(row_pointers);
    fclose(fp);
    free(pixels);
    return 1;
}
