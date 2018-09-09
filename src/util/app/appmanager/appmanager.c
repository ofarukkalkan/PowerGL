#include "appmanager.h"

#include <string.h>
#include <stdio.h>
// linux
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>

#define APP_FOLDER "/home/omerfaruk/powergl/apps"

void find_apps_from_folder(){
  DIR *dp;
  struct dirent *ep;

  dp = opendir (APP_FOLDER);
  if (dp != NULL)
    {
      while (ep = readdir (dp)){
        puts (ep->d_name);
      }
      (void) closedir (dp);
    }
  else
    perror ("Couldn't open the directory");
}

/* int load_new_apps(void){ */
/*   void* dl_handle; */
/*   char* error; */
/*   powergl_util_app* (*new_func)(void); */

  
/*   find_apps_from_folder(); */
 
/*   // Open the shared object */
/*   dl_handle = dlopen( , RTLD_LAZY ); */
/*   if (!dl_handle) { */
/*     printf( "!!! %s\n", dlerror() ); */
/*     return; */
/*   } */
 
/*   // Resolve the symbol (method) from the object */
/*   new_func = dlsym( dl_handle, method ); */
/*   error = dlerror(); */
/*   if (error != NULL) { */
/*     printf( "!!! %s\n", error ); */
/*     return; */
/*   } */
 
/*   // Call the resolved method */
/*   (*func)(argument); */
 
/*     // Close the object  */
/*   dlclose( dl_handle ); */
/* } */

int create(void){
  find_apps_from_folder();
}

int run(void){

}

powergl_util_app_appmanager* powergl_util_app_appmanager_new(void){
  powergl_util_app_appmanager* mng = NULL;
  mng = powergl_resize(NULL,sizeof(powergl_util_app_appmanager));
  mng->_base.create = create;
  mng->_base.run = run;

  return mng;
}
