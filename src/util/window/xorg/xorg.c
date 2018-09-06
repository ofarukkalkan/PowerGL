#include "xorg.h"
#include <stdio.h>

// internal fields
static powergl_util_window_xorg** g_powergl_util_window_xorg;
static size_t n_powergl_util_window_xorg;
static size_t i_powergl_util_window_xorg;
static int f_powergl_util_window_xorg;

int powergl_util_window_xorg_check_init(void){
 if(f_powergl_util_window_xorg != 1){
    fprintf(stderr,"powergl_util_window_xorg is not initialised");
    return 0;
 }else return 1;
}

int powergl_util_window_xorg_init(void){
  if(powergl_util_window_xorg_check_init()){
    return 1;
  }else{
    g_powergl_util_window_xorg = NULL;
    n_powergl_util_window_xorg = 0;
    i_powergl_util_window_xorg = 0;
    f_powergl_util_window_xorg = 1;
    return 1;
  }
}

int powergl_util_window_xorg_finish(void){
  if(powergl_util_window_xorg_check_init()){
    
    if(powergl_util_window_xorg_delete_all()){
      g_powergl_util_window_xorg = NULL;
      n_powergl_util_window_xorg = 0;
      i_powergl_util_window_xorg = 0;
      f_powergl_util_window_xorg = 0;
      return 1;
    }else return 0;
  }else return 0;
}

powergl_util_window_xorg* powergl_util_window_xorg_new(void){
  if(powergl_util_window_xorg_init()){
  
    powergl_util_window_xorg* wnd = NULL;
    wnd = powergl_resize(NULL,sizeof(powergl_util_window_xorg));
    wnd->_base.create = powergl_util_window_xorg_create;
    wnd->_base.run = powergl_util_window_xorg_run;

    g_powergl_util_window_xorg = powergl_resize(g_powergl_util_window_xorg,
					sizeof(powergl_util_window_xorg) * ++n_powergl_util_window_xorg );
  
    size_t new_index = n_powergl_util_window_xorg - 1;
    powergl_util_window_xorg_set_index(new_index);

    g_powergl_util_window_xorg[new_index] = wnd;
  
    return wnd;
  }else return NULL;
}

int powergl_util_window_xorg_delete(void){
  if(powergl_util_window_xorg_check_init()){
    
    size_t i = powergl_util_window_xorg_get_index();
    if(g_powergl_util_window_xorg[i]){
      free(g_powergl_util_window_xorg[i]);
      g_powergl_util_window_xorg[i] = NULL;
      powergl_util_window_xorg_set_index(i-1);
      return 1;
    }else {
      fprintf(stderr,"could not deleted index %ld of powergl_util_window_xorg",i);
      return 0;
    }
  }else return 0;
}

int powergl_util_window_xorg_delete_all(void){
  if(powergl_util_window_xorg_check_init()){
    
    for(int i = 0; i < n_powergl_util_window_xorg; ++i){
      int result = powergl_util_window_xorg_set_index(i);
      if(!result) return 0;     
      result = powergl_util_window_xorg_delete();
      if(!result) return 0;
    }

    if(g_powergl_util_window_xorg){
      free(g_powergl_util_window_xorg);
      g_powergl_util_window_xorg = NULL;
      return 1;
    }else {
      fprintf(stderr,"could not deleted powergl_util_window_xorg");
      return 0;
    }
  }else return 0;
}

int powergl_util_window_xorg_set_index(size_t i){
  if(powergl_util_window_xorg_check_init()){
    
    if(i >= n_powergl_util_window_xorg){
      fprintf(stderr,"index is not valid");
      return 0;
    }else{
      i_powergl_util_window_xorg = i;
      return 1;
    }
  }else return 0;
}

size_t powergl_util_window_xorg_get_index(){
  return i_powergl_util_window_xorg;
}

powergl_util_window_xorg* powergl_util_window_xorg_get_ptr(){
  return g_powergl_util_window_xorg[powergl_util_window_xorg_get_index()];
}

int powergl_util_window_xorg_create(void){

  if(!powergl_util_window_xorg_check_init()){
    return 0;
  }

  powergl_util_window_xorg* wnd = g_powergl_util_window_xorg[powergl_util_window_xorg_get_index()];
  
  int fbattribs[] = {
    GLX_CONFIG_CAVEAT,GLX_NONE,
    GLX_BUFFER_SIZE,32,
    GLX_DRAWABLE_TYPE,GLX_WINDOW_BIT,
    GLX_X_VISUAL_TYPE,GLX_TRUE_COLOR,
    GLX_STEREO,False,
    //GLX_SAMPLES,8,
    //GLX_SAMPLE_BUFFERS,1,
    GLX_DOUBLEBUFFER,True,
    GLX_RENDER_TYPE,GLX_RGBA_BIT,
    GLX_RED_SIZE,8,
    GLX_GREEN_SIZE,8,
    GLX_BLUE_SIZE,8,
    GLX_ALPHA_SIZE,8,
    GLX_DEPTH_SIZE,24,
    GLX_STENCIL_SIZE, 8,   
    None
  };
  GLXFBConfig *fbconfigs;
  int count;
  XVisualInfo  *visualinfo;
  XSetWindowAttributes windowattribs;
  Window rootwindow;
  int contextattribs[]={
    GLX_CONTEXT_MAJOR_VERSION_ARB,3,
    GLX_CONTEXT_MINOR_VERSION_ARB,3,
    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
    None
  };
  Bool result;

  /* X Server e baglanma */
  wnd->display = XOpenDisplay(NULL);
  if(wnd->display!=NULL){
    fprintf(stdout,"\nX Server baglantisi basarili");
  }else{
    fprintf(stderr,"\nhata : X Server baglantisi basarisiz");
    return 0;
  }
  /* suan ki ekran id sini elde etme */
  wnd->screenid = DefaultScreen(wnd->display);
  fprintf(stderr,"\nEkran id : %d",wnd->screenid);

  /* verilen ozelliklerle eslesen frame buffer formatlarini getir */
  fbconfigs = glXChooseFBConfig (wnd->display,wnd->screenid, fbattribs,&count );
  if(count){
    fprintf(stdout,"\nEslesen fbconfig sayisi : %d", count);
    /* ilkini sec (ne oldugu belli degil !) */
    wnd->fbconfig=fbconfigs[0];
  }else{
    fprintf(stderr,"\nhata : eslesen fbconfig yok");
    return 0;
  }

  visualinfo = glXGetVisualFromFBConfig(wnd->display,wnd->fbconfig);
  fprintf(stderr,"\nsecilen visual id : 0x%x",(unsigned int)visualinfo->visualid);

  /* eslesen fbconfigleri temizle */
  XFree(fbconfigs);

  /* ana pencereyi elde etme */
  rootwindow = RootWindow(wnd->display,wnd->screenid);

  /* color map olustur */
  wnd->colormap = XCreateColormap(wnd->display,rootwindow,visualinfo->visual,AllocNone);

  /* test penceresinin ozelliklerini ayarla */
  windowattribs.colormap = wnd->colormap;
  windowattribs.background_pixmap = None;
  windowattribs.border_pixel = 0;
  windowattribs.event_mask = StructureNotifyMask;

  /* test penceresini olustur */
  wnd->window =
    XCreateWindow(
		  wnd->display,rootwindow,
		  0,0,
		  640,480,0,
		  visualinfo->depth, InputOutput,
		  visualinfo->visual,
		  CWBorderPixel|CWColormap|CWEventMask,
		  &windowattribs
		  );

  if(wnd->window){
    fprintf(stdout,"\ntest penceresi olusturuldu");
  }else{
    fprintf(stderr,"\nhata : test penceresi olusturulamadi");
    return 0;
  }
  XFree(visualinfo);

  /* event lara kaydolma */
  XSelectInput(wnd->display, wnd->window, ExposureMask | ButtonPressMask);

  
  /* pencereyi ekrena getirme */
  XMapWindow(wnd->display,wnd->window);

  /* context olusturma */  
  PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
  glXCreateContextAttribsARB = (PFNGLXCREATECONTEXTATTRIBSARBPROC)glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
  wnd->context = glXCreateContextAttribsARB(wnd->display,wnd->fbconfig,0,True,contextattribs);
  if(wnd->context){
    fprintf(stdout,"\ncontext olusturuldu");
  }else{
    fprintf(stderr,"\nhata : context olusturulamadi");
    return 0;
  }

  /* context baglama */
  result = glXMakeCurrent(wnd->display,wnd->window,wnd->context);
  if(result){
    fprintf(stdout,"\ncontext baglandi");
  }else{
    fprintf(stderr,"\nhata : context baglanamadi");
    return 0;
  }

  /* vsync ayarlama */
  PFNGLXSWAPINTERVALMESAPROC glXSwapIntervalMESA;
  glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress( (const GLubyte*)"glXSwapIntervalMESA");

  if ( glXSwapIntervalMESA != NULL ) {
    glXSwapIntervalMESA(0);
  }else{
    fprintf(stderr,"\nhata : swap interval ayarlanamadi");
    return 0;
  }
  return 1;

}

int powergl_util_window_xorg_run(void){
  if(!powergl_util_window_xorg_check_init()){
    return 0;
  }

  powergl_util_window_xorg* wnd = g_powergl_util_window_xorg[powergl_util_window_xorg_get_index()];

  XEvent event;
  /*
    glDebugMessageCallback(glErrorCallback, NULL);
    glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE );  
    glEnable(GL_DEBUG_OUTPUT);	
  */
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_MULTISAMPLE);
  glClearColor(0.3f,0.6f,0.9f,1.0f);
  
 here:

  while (XPending(wnd->display) > 0){
    XNextEvent(wnd->display,&event);
    
    switch(event.type){
    case ButtonPress:
      /* running=0; */
      printf("butona basildi");
      goto exit;
    case Expose:
      ;
    }
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  glXSwapBuffers(wnd->display,wnd->window);
  
  goto here;

 exit:

  return 1;
}
