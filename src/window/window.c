#include "window.h"
#include <stdio.h>
#include <time.h>

enum msgSource {
    SOURCE_API = 0x8246,
    SOURCE_SYSTEM = 0x8247,
    SOURCE_SHADER_COMPILER = 0x8248,
    SOURCE_THIRD_PARTY = 0x8249,
    SOURCE_APPLICATION = 0x824A,
    SOURCE_OTHER = 0x824B,
};

enum msgType {
    TYPE_ERROR = 0x824C,
    TYPE_DEPRECATED_BEHAVIOR = 0x824D,
    TYPE_UNDEFINED_BEHAVIOR = 0x824E,
    TYPE_PORTABILITY = 0x824F,
    TYPE_PERFORMANCE = 0x8250,
    TYPE_OTHER = 0x8251,
    TYPE_MARKER = 0x8268,
    TYPE_PUSH_GROUP = 0x8269,
    TYPE_POP_GROUP = 0x826A,
};

enum msgSeverity {
    SEVERITY_HIGH = 0x9146,
    SEVERITY_MEDIUM = 0x9147,
    SEVERITY_LOW = 0x9148,
    SEVERITY_NOTIFICATION = 0x826B,
};

void errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const GLvoid *userParam) {
    fprintf(stderr, "\nSource = [ %d ] \n", (int) source);
    fprintf(stderr, "Type = [ %d ]\n", (int) type);
    fprintf(stderr, "Severity = [ %d ]\n", (int) severity);
    fprintf(stderr, "ID = [ %d ]\n", (int) id);
    fprintf(stderr, "Msg = [ %u %s ]\n", length, (const char *)message);

    if(userParam) {}
}


powergl_window *powergl_window_new(powergl_visualscene *scene) {
    powergl_window *wnd =  powergl_resize(NULL, 1, sizeof(powergl_window));
    wnd->root_scene = scene;
    return wnd;
}

int powergl_window_create(powergl_window *wnd, int width, int height) {
    //Initialization flag
    int success = 1;
    wnd->window = NULL;
    wnd->width = width;
    wnd->height = height;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = 0;
    } else {
        //Use OpenGL 3.1 core
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        //Create window
        wnd->window = SDL_CreateWindow("PoweGL Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if(wnd->window == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = 0;
        } else {
            //Create context
            wnd->context = SDL_GL_CreateContext(wnd->window);

            if(wnd->context == NULL) {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = 0;
            } else {
                //Initialize GLEW
                glewExperimental = GL_TRUE;
                GLenum glewError = glewInit();

                if(glewError != GLEW_OK) {
                    printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
                }

                //Use Vsync
                if(SDL_GL_SetSwapInterval(1) < 0) {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }
            }
        }
    }

    return success;
}

int powergl_window_run(powergl_window *wnd) {
    glDebugMessageCallback(errorCallback, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_MULTISAMPLE);
    glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
    wnd->root_scene->create(wnd->root_scene);
    float delta_time = 0.0f;
    int quit = 0;
    SDL_Event e;

    struct timespec ts1; // both C11 and POSIX
    struct timespec ts2;
    clock_gettime(CLOCK_REALTIME, &ts1); // POSIX


    while(!quit) {
      	clock_gettime(CLOCK_REALTIME, &ts2);	
	delta_time = ts2.tv_sec + 1e-9*ts2.tv_nsec - (ts1.tv_sec + 1e-9*ts1.tv_nsec);
	
        while(SDL_PollEvent(&e) != 0) {
	  wnd->root_scene->handle_events(wnd->root_scene, &e, delta_time);

            if(e.type == SDL_QUIT) {
                quit = 1;
            }
        }
	

	
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        wnd->root_scene->run(wnd->root_scene, delta_time);
        //Update screen
        SDL_GL_SwapWindow(wnd->window);

	ts1 = ts2;
    }


    return 0;
}
