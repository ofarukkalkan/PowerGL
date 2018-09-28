#include "xorg.h"
#include <stdio.h>

#define DEBUG_OUTPUT 0

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

void errorCallback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const GLvoid *userParam ) {
  fprintf(stderr, "\nSource = [ %d ] \n", ( int ) source );
  fprintf(stderr, "Type = [ %d ]\n", ( int ) type );
  fprintf(stderr, "Severity = [ %d ]\n", ( int ) severity );
  fprintf(stderr, "ID = [ %d ]\n", ( int ) id );
  fprintf(stderr, "Msg = [ %s ]\n", ( const char * )message );
}

int powergl_util_window_xorg_create( powergl_util_window_xorg *wnd ) {

  int fbattribs[] = {
    GLX_CONFIG_CAVEAT, GLX_NONE,
    GLX_BUFFER_SIZE, 32,
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
    GLX_STEREO, False,
    //GLX_SAMPLES,8,
    //GLX_SAMPLE_BUFFERS,1,
    GLX_DOUBLEBUFFER, True,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_RED_SIZE, 8,
    GLX_GREEN_SIZE, 8,
    GLX_BLUE_SIZE, 8,
    GLX_ALPHA_SIZE, 8,
    GLX_DEPTH_SIZE, 24,
    GLX_STENCIL_SIZE, 8,
    None
  };
  GLXFBConfig *fbconfigs;
  int count;
  XVisualInfo  *visualinfo;
  XSetWindowAttributes windowattribs;
  Window rootwindow;
  int contextattribs[] = {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
    GLX_CONTEXT_MINOR_VERSION_ARB, 3,
    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
    None
  };
  Bool result;

  /* X Server e baglanma */
  wnd->display = XOpenDisplay( NULL );
  if ( wnd->display != NULL ) {
#if DEBUG_OUTPUT
    fprintf( stdout, "X Server baglantisi basarili\n" );
#endif
  } else {
    fprintf( stderr, "hata : X Server baglantisi basarisiz\n" );
    return 0;
  }
  /* suan ki ekran id sini elde etme */
  wnd->screenid = DefaultScreen( wnd->display );
#if DEBUG_OUTPUT
  fprintf( stdout, "Ekran id : %d\n", wnd->screenid );
#endif
  /* verilen ozelliklerle eslesen frame buffer formatlarini getir */
  fbconfigs = glXChooseFBConfig( wnd->display, wnd->screenid, fbattribs, &count );
  if ( count ) {
#if DEBUG_OUTPUT
    fprintf( stdout, "Eslesen fbconfig sayisi : %d\n", count );
#endif
    /* ilkini sec (ne oldugu belli degil !) */
    wnd->fbconfig = fbconfigs[0];
  } else {
    fprintf( stderr, "hata : eslesen fbconfig yok\n" );
    return 0;
  }

  visualinfo = glXGetVisualFromFBConfig( wnd->display, wnd->fbconfig );
#if DEBUG_OUTPUT
  fprintf( stdout, "secilen visual id : 0x%x\n", ( unsigned int )visualinfo->visualid );
#endif
  /* eslesen fbconfigleri temizle */
  XFree( fbconfigs );

  /* ana pencereyi elde etme */
  rootwindow = RootWindow( wnd->display, wnd->screenid );

  /* color map olustur */
  wnd->colormap = XCreateColormap( wnd->display, rootwindow, visualinfo->visual, AllocNone );

  /* test penceresinin ozelliklerini ayarla */
  windowattribs.colormap = wnd->colormap;
  windowattribs.background_pixmap = None;
  windowattribs.border_pixel = 0;
  windowattribs.event_mask = StructureNotifyMask;

  /* test penceresini olustur */
  wnd->window =
    XCreateWindow(
		  wnd->display, rootwindow,
		  0, 0,
		  640, 480, 0,
		  visualinfo->depth, InputOutput,
		  visualinfo->visual,
		  CWBorderPixel | CWColormap | CWEventMask,
		  &windowattribs
		  );

  if ( wnd->window ) {
#if DEBUG_OUTPUT
    fprintf( stdout, "test penceresi olusturuldu\n" );
#endif
  } else {
    fprintf( stderr, "hata : test penceresi olusturulamadi\n" );
    return 0;
  }
  XFree( visualinfo );

  /* event lara kaydolma */
  XSelectInput( wnd->display, wnd->window, ExposureMask | ButtonPressMask );


  /* pencereyi ekrena getirme */
  XMapWindow( wnd->display, wnd->window );

  /* context olusturma */
  PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
  glXCreateContextAttribsARB = ( PFNGLXCREATECONTEXTATTRIBSARBPROC )glXGetProcAddressARB( ( const GLubyte * ) "glXCreateContextAttribsARB" );
  wnd->context = glXCreateContextAttribsARB( wnd->display, wnd->fbconfig, 0, True, contextattribs );
  if ( wnd->context ) {
#if DEBUG_OUTPUT
    fprintf( stdout, "context olusturuldu\n" );
#endif
  } else {
    fprintf( stderr, "hata : context olusturulamadi\n" );
    return 0;
  }

  /* context baglama */
  result = glXMakeCurrent( wnd->display, wnd->window, wnd->context );
  if ( result ) {
#if DEBUG_OUTPUT
    fprintf( stdout, "context baglandi\n" );
#endif
  } else {
    fprintf( stderr, "hata : context baglanamadi\n" );
    return 0;
  }

  /* vsync ayarlama */
  PFNGLXSWAPINTERVALMESAPROC glXSwapIntervalMESA;
  glXSwapIntervalMESA = ( PFNGLXSWAPINTERVALMESAPROC )glXGetProcAddress( ( const GLubyte * )"glXSwapIntervalMESA" );

  if ( glXSwapIntervalMESA != NULL ) {
    glXSwapIntervalMESA( 0 );
  } else {
    fprintf( stderr, "hata : swap interval ayarlanamadi\n" );
    return 0;
  }
  return 1;

}

int powergl_util_window_xorg_run( powergl_util_window_xorg *wnd ) {

  XEvent event;

  glDebugMessageCallback( errorCallback, NULL );
  glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE );
  glEnable( GL_DEBUG_OUTPUT );

  glEnable( GL_DEPTH_TEST );
  //glEnable(GL_MULTISAMPLE);
  glClearColor( 0.3f, 0.6f, 0.9f, 1.0f );

  powergl_util_app_create( &wnd->_base.root_app );

 here:

  while ( XPending( wnd->display ) > 0 ) {
    XNextEvent( wnd->display, &event );

    switch ( event.type ) {
    case ButtonPress:
      /* running=0; */
      printf( "butona basildi" );
      goto exit;
    case Expose:
      ;
    }
  }

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  powergl_util_app_run( &wnd->_base.root_app );

  glXSwapBuffers( wnd->display, wnd->window );

  goto here;

 exit:

  return 1;
}
