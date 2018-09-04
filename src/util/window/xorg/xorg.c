#include "xorg.h"

powergl_util_window_xorg* powergl_util_window_xorg_create(void){
  powergl_util_window_xorg* wnd = NULL;
  wnd = resize();
  
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
    printf("\nX Server baglantisi basarili");
  }else{
    printf("\nhata : X Server baglantisi basarisiz");
    exit(EXIT_FAILURE);
  }
  /* suan ki ekran id sini elde etme */
  wnd->screenid = DefaultScreen(wnd->display);
  printf("\nEkran id : %d",wnd->screenid);

  /* verilen ozelliklerle eslesen frame buffer formatlarini getir */
  fbconfigs = glXChooseFBConfig (wnd->display,wnd->screenid, fbattribs,&count );
  if(count){
    printf("\nEslesen fbconfig sayisi : %d", count);
    /* ilkini sec (ne oldugu belli degil !) */
    wnd->fbconfig=fbconfigs[0];
  }else{
    printf("\nhata : eslesen fbconfig yok");
    exit(EXIT_FAILURE);
  }

  visualinfo = glXGetVisualFromFBConfig(wnd->display,wnd->fbconfig);
  printf("\nsecilen visual id : 0x%x",(unsigned int)visualinfo->visualid);

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
    printf("\ntest penceresi olusturuldu");
  }else{
    printf("\nhata : test penceresi olusturulamadi");
    exit(EXIT_FAILURE);
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
    printf("\ncontext olusturuldu");
  }else{
    printf("\nhata : context olusturulamadi");
    exit(EXIT_FAILURE);
  }

  /* context baglama */
  result = glXMakeCurrent(wnd->display,wnd->window,wnd->context);
  if(result){
    printf("\ncontext baglandi");
  }else{
    printf("\nhata : context baglanamadi");
    exit(EXIT_FAILURE);
  }

  /* vsync ayarlama */
  PFNGLXSWAPINTERVALMESAPROC glXSwapIntervalMESA;
  glXSwapIntervalMESA = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddress( (const GLubyte*)"glXSwapIntervalMESA");

  if ( glXSwapIntervalMESA != NULL ) {
    glXSwapIntervalMESA(0);
  }else{
    printf("\nhata : swap interval ayarlanamadi");
    exit(EXIT_FAILURE);
  }

}
