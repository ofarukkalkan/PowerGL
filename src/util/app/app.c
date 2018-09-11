#include "app.h"

#include <string.h>
#include <stdio.h>
// linux
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

#define APP_FOLDER "/home/omerfaruk/powergl/apps"
#define APP_FOLDER_R "/home/omerfaruk/powergl/apps/"

// internal fields
static powergl_util_app** g_powergl_util_app;
static void** g_powergl_util_app_dlhandle;
static size_t n_powergl_util_app;
static size_t i_powergl_util_app;
static int f_powergl_util_app;

int powergl_util_app_check_init(void){
 if(f_powergl_util_app != 1){
   fprintf(stderr,"powergl_util_app is not initialised\n");
   return 0;
 }else return 1;
}

int powergl_util_app_init(void){
  if(powergl_util_app_check_init()){
    return 1;
  }else{
    g_powergl_util_app = NULL;
    n_powergl_util_app = 0;
    i_powergl_util_app = 0;
    f_powergl_util_app = 1;
    return 1;
  }
}

int powergl_util_app_finish(void){
  if(powergl_util_app_check_init()){
    
    if(powergl_util_app_delete_all()){
      g_powergl_util_app = NULL;
      n_powergl_util_app = 0;
      i_powergl_util_app = 0;
      f_powergl_util_app = 0;
      return 1;
    }else return 0;
  }else return 0;
}

int powergl_util_app_delete(void){
  if(powergl_util_app_check_init()){
    
    size_t i = powergl_util_app_get_index();
    if(g_powergl_util_app[i]){
      free(g_powergl_util_app[i]);
      dlclose(g_powergl_util_app_dlhandle[i]);
      g_powergl_util_app_dlhandle[i] = NULL;
      g_powergl_util_app[i] = NULL;
      powergl_util_app_set_index(i-1);
      return 1;
    }else {
      fprintf(stderr,"could not deleted index %ld of powergl_util_app\n",i);
      return 0;
    }
  }else return 0;
}

int powergl_util_app_delete_all(void){
  if(powergl_util_app_check_init()){
    
    for(int i = 0; i < n_powergl_util_app; ++i){
      int result = powergl_util_app_set_index(i);
      if(!result) return 0;     
      result = powergl_util_app_delete();
      if(!result) return 0;
    }

    if(g_powergl_util_app){
      free(g_powergl_util_app);
      g_powergl_util_app = NULL;
      return 1;
    }else {
      fprintf(stderr,"could not deleted powergl_util_app");
      return 0;
    }
  }else return 0;
}

int powergl_util_app_set_index(size_t i){
  if(powergl_util_app_check_init()){
    
    if(i >= n_powergl_util_app){
      fprintf(stderr,"index is not valid");
      return 0;
    }else{
      i_powergl_util_app = i;
      return 1;
    }
  }else return 0;
}

size_t powergl_util_app_get_index(){
  return i_powergl_util_app;
}

powergl_util_app* powergl_util_app_get_ptr(){
  return g_powergl_util_app[powergl_util_app_get_index()];
}

powergl_util_app* powergl_util_app_find(const char*app_name){
  for(int i=0; i< n_powergl_util_app;i++){
    if( strcmp(g_powergl_util_app[i]->get_name(), app_name) == 0 ){
      return g_powergl_util_app[i];
    }
  }
}

powergl_util_app* powergl_util_app_new(const char*app_name){

  powergl_util_app *app = NULL;

  if(powergl_util_app_init()){

    void* dl_handle;
    char* error;
    powergl_util_app* (*new_func)(void);
    int (*create_func)(void);
    int (*run_func)(void);
    const char* (*get_name_func)(void);
	
    size_t newsize = strlen(app_name)+strlen(APP_FOLDER_R)+1;
    char* file_path = powergl_resize(NULL,sizeof(char) * newsize);
    file_path[0] = '\0';
    strcat(file_path,APP_FOLDER_R);
    strcat(file_path,app_name);
      
    newsize = strlen(app_name)+strlen("_new")+1;
    char* new_func_name = powergl_resize(NULL,sizeof(char) * newsize);
    new_func_name[0] = '\0';
    strcat(new_func_name,app_name);
    strcat(new_func_name,"_new");

    printf("%s\n",file_path);
 
    // Open the shared object
    dl_handle = dlopen( file_path, RTLD_LAZY );
    if (!dl_handle) {
      printf( "!!! %s\n", dlerror() );
    }else{
      // Resolve the symbol (method) from the object
      new_func = dlsym( dl_handle, new_func_name);
      error = dlerror();
      if (error != NULL) {
	printf( "!!! %s\n", error );
      }

      create_func = dlsym( dl_handle, "create");
      error = dlerror();
      if (error != NULL) {
	printf( "!!! %s\n", error );
      }

      run_func = dlsym( dl_handle, "run");
      error = dlerror();
      if (error != NULL) {
	printf( "!!! %s\n", error );
      }

      get_name_func = dlsym( dl_handle, "get_name");
      error = dlerror();
      if (error != NULL) {
	printf( "!!! %s\n", error );
      }

      // Call the resolved method
      app = new_func();
      if(app){
	app->create = create_func;
	app->run = run_func;
	app->get_name = get_name_func;
	printf("%s is loaded\n",app->get_name());
	  
	g_powergl_util_app = powergl_resize(g_powergl_util_app, sizeof(powergl_util_app*) * ++n_powergl_util_app );
	g_powergl_util_app_dlhandle = powergl_resize(g_powergl_util_app, sizeof(void*) * ++n_powergl_util_app );
	size_t new_index = n_powergl_util_app - 1;
	powergl_util_app_set_index(new_index);

	g_powergl_util_app[new_index] = app;
	g_powergl_util_app_dlhandle[new_index] = dl_handle;
	
      }else{
	fprintf(stderr,"new_func returned NULL");	
      }
    }
	
    free(file_path);
    free(new_func_name);    
      

  }
  return app;
} 
