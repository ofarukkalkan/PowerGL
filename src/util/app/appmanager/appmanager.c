#include "appmanager.h"

int create(void){

}

int run(void){

}

powergl_util_app_appmanager* powergl_util_app_appmanager_new(void){
  powergl_util_app_appmanager* mng = NULL;
  mng = powergl_resize(NULL,sizeof(powergl_util_app_appmanager));
  mng->_base.create = create();
  mng->_base.run = run;

  return mng;
}
