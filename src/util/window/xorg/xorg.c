#include "xorg.h"
#include <stdio.h>

enum msgSource
	{
		SOURCE_API = 0x8246,
		SOURCE_SYSTEM = 0x8247,
		SOURCE_SHADER_COMPILER = 0x8248,
		SOURCE_THIRD_PARTY = 0x8249,
		SOURCE_APPLICATION = 0x824A,
		SOURCE_OTHER = 0x824B,
	};

enum msgType
	{
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

enum msgSeverity
	{
		SEVERITY_HIGH = 0x9146,
		SEVERITY_MEDIUM = 0x9147,
		SEVERITY_LOW = 0x9148,
		SEVERITY_NOTIFICATION = 0x826B,
	};

void errorCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,const GLvoid *userParam )                                                                      
{                                                                                                                                                       
	printf( "\nSource = [ %d ] \n", (int) source);                                                                                                                                                                 
	printf( "Type = [ %d ]\n", (int) type);                                                                                                                                                               
	printf(	"Severity = [ %d ]\n",(int) severity );                                                                                                                                                                
	printf(	"ID = [ %d ]\n",(int) id);                                                                                                                                                              
	printf(	"Msg = [ %s ]\n",(const char*)message);                                                                                                                                                                    
}  

int powergl_util_window_xorg_create( powergl_util_window_xorg *wnd ){

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

int powergl_util_window_xorg_run( powergl_util_window_xorg *wnd ) {

	

  XEvent event;
  
	glDebugMessageCallback(errorCallback, NULL);
	glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE );  
	glEnable(GL_DEBUG_OUTPUT);	
  
  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_MULTISAMPLE);
  glClearColor(0.3f,0.6f,0.9f,1.0f);

	powergl_util_app_create( &wnd->_base.root_app );
  
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

	powergl_util_app_run( &wnd->_base.root_app );
    
  glXSwapBuffers(wnd->display,wnd->window);
  
  goto here;

 exit:

  return 1;
}
