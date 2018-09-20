#include "pipeline.h"

#include "../math/mat4x4.h"

#include <stdio.h>

int powergl_rendering_pipeline_render( powergl_rendering_pipeline *ppl, powergl_rendering_object **objs, size_t n_object, int i_camera ) {

  if ( i_camera > -1 ) {

    GLfloat tmp[4][4];

    powergl_rendering_object *obj;
    powergl_rendering_geometry *geo;

    glUseProgram( ppl->gp );
    glEnableVertexAttribArray( ppl->vis.index );
    glEnableVertexAttribArray( ppl->cis.index );

    for ( size_t i = 0; i < n_object; ++i ) {

      obj = objs[i];

      if ( obj->geometry == NULL ) {

        continue;

      } else {

        geo = obj->geometry;

      }

      glBindVertexArray( geo->vao );

      if ( objs[i_camera]->camera->view_flag == 1 || objs[i_camera]->camera->projection_flag == 1 || obj->matrix_flag == 1 ) {

        if ( objs[i_camera]->camera->view_flag == 1 || objs[i_camera]->camera->projection_flag == 1 ) {

          powergl_ident4x4( tmp );
          powergl_ident4x4( objs[i_camera]->camera->vp );
          powergl_mult4x4( objs[i_camera]->camera->vp, objs[i_camera]->camera->view, tmp );
          powergl_mult4x4( objs[i_camera]->camera->vp, objs[i_camera]->camera->projection, tmp );

          objs[i_camera]->camera->view_flag = 0;
          objs[i_camera]->camera->projection_flag = 0;

        }

        powergl_ident4x4( tmp );
        powergl_ident4x4( obj->mvp );
        powergl_mult4x4( obj->mvp, obj->matrix, tmp );
        powergl_mult4x4( obj->mvp, objs[i_camera]->camera->vp, tmp );

        obj->matrix_flag = 0;

        glUniformMatrix4fv( ppl->uni_matrix, 1, GL_FALSE, &obj->mvp[0][0] );
        printf( "mvp transformation\n" );
        powergl_print4x4( obj->mvp );

      }

      if ( geo->vertex_flag == 1 ) {
        printf( "vertex buffer filled\n" );
        glBindBuffer( GL_ARRAY_BUFFER, geo->vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( powergl_vec3 ) * geo->n_vertex, geo->vertex, GL_STATIC_DRAW );
        glVertexAttribPointer( ppl->vis.index, ppl->vis.size, ppl->vis.type, ppl->vis.normalized, ppl->vis.stride, ppl->vis.offset );
        geo->vertex_flag = 0;
      }

      if ( geo->color_flag == 1 ) {
        printf( "color buffer filled\n" );
        glBindBuffer( GL_ARRAY_BUFFER, geo->cbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( powergl_vec3 ) * geo->n_color, geo->color, GL_STATIC_DRAW );
        glVertexAttribPointer( ppl->cis.index, ppl->cis.size, ppl->cis.type, ppl->cis.normalized, ppl->cis.stride, ppl->cis.offset );
        geo->color_flag = 0;
      }


      glDrawArrays( GL_TRIANGLES, 0, obj->geometry->n_vertex );
    }

  } else {
    return 0;
  }

  return 1;
}

int powergl_rendering_pipeline_create( powergl_rendering_pipeline *ppl, powergl_rendering_object **objs, size_t n_object ) {

  for ( size_t i = 0; i < n_object; i++ ) {

    if ( objs[i]->geometry ) {

      glGenVertexArrays( 1, &objs[i]->geometry->vao );
      glGenBuffers( 1, &objs[i]->geometry->vbo );
      glGenBuffers( 1, &objs[i]->geometry->cbo );

    }

  }

  /*vertex shader input attibute specs*/

  /* vertex input */
  ppl->vis.index = 0;
  ppl->vis.size = 3;
  ppl->vis.type = GL_FLOAT;
  ppl->vis.normalized = GL_FALSE;
  ppl->vis.stride = 0;
  ppl->vis.offset = 0;

  /* color input */
  ppl->cis.index = 1;
  ppl->cis.size = 3;
  ppl->cis.type = GL_FLOAT;
  ppl->cis.normalized = GL_FALSE;
  ppl->cis.stride = 0;
  ppl->cis.offset = 0;

  /*shader compiler input specs*/
  const GLchar *const vsrc[] = {"#version 330 core\n\
			layout( location = 0 ) in vec3 vPosition;\n\
			layout( location = 1 ) in vec3 vColor;\n\
			out vec3 colorToFs;\n\
			uniform mat4 mvp;\n\
			void main(){\n\
			  colorToFs =  vColor;\n\
			  gl_Position = mvp * vec4( vPosition, 1.0f );\n\
			}"
                               };
  const GLchar *const fsrc[] = {"#version 330 core\n\
			in vec3 colorToFs;\n\
			out vec4 fColor;\n\
			void main(){\n\
			  fColor = vec4( colorToFs ,1.0f );\n\
			}"
                               };
  /*vertex shader*/
  ppl->vs = glCreateShader( GL_VERTEX_SHADER );
  glShaderSource( ppl->vs, 1, vsrc, NULL );
  glCompileShader( ppl->vs );
  /*fragment shader*/
  ppl->fs = glCreateShader( GL_FRAGMENT_SHADER );
  glShaderSource( ppl->fs, 1, fsrc, NULL );
  glCompileShader( ppl->fs );
  /*program*/
  ppl->gp = glCreateProgram();
  glAttachShader( ppl->gp, ppl->vs );
  glAttachShader( ppl->gp, ppl->fs );
  glLinkProgram( ppl->gp );
  /*uniform*/
  /* uniform a verilen string ayri tutulacak  bunun icin biseyler dusun*/
  glUseProgram( ppl->gp );
  ppl->uni_matrix = glGetUniformLocation( ppl->gp, "mvp" );


}
