#include "pipeline.h"

#include "../math/mat4x4.h"

#include <stdio.h>

#ifndef DEBUG_OUTPUT
#define DEBUG_OUTPUT 0
#endif

static powergl_pipeline *last_ppl;
static powergl_pipeline2 *last_ppl2;
static powergl_pipeline3 *last_ppl3;
static powergl_object *last_obj;

/* Global toggle for drawing selection outlines */
int powergl_enable_outline = 1;
int powergl_enable_grid = 1;

static void draw_outline(powergl_object *obj){
  // --- PREPARATION ---
  glEnable(GL_STENCIL_TEST);
  glClear(GL_STENCIL_BUFFER_BIT);
  
  
  // --- PASS 1: DRAW THE MAIN OBJECT AND POPULATE THE STENCIL BUFFER ---
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  glStencilFunc(GL_ALWAYS, 1, 0xFF);
  glStencilMask(0xFF);
  glDepthMask(GL_TRUE); 
  glDrawArrays(obj->geometry.primitive_type, 0, obj->geometry.n_vertex);

  // --- PASS 2: DRAW THE OUTLINE ---
  glCullFace(GL_FRONT);

  glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
  glStencilMask(0x00);
  glDepthMask(GL_FALSE);
  glUseProgram(last_ppl3->gpOutline);
  glUniformMatrix4fv(last_ppl3->uni_matrixOutline, 1, GL_FALSE, obj->transform.mvp.data);

  glDrawArrays(obj->geometry.primitive_type, 0, obj->geometry.n_vertex);

  glStencilMask(0xFF);
  glStencilFunc(GL_ALWAYS, 0, 0xFF);
  glDisable(GL_STENCIL_TEST);
  glDepthMask(GL_TRUE);
  glCullFace(GL_BACK); // Reset face culling to the default.
}

static void render3(powergl_pipeline3 *ppl, powergl_object **objs, size_t n_object){

  powergl_object *obj = NULL;
    
  for(size_t i = 0; i < n_object; ++i) {
    obj = objs[i];

    if(obj->n_object > 0){
      render3(ppl, obj->objects, obj->n_object);
    }

    if(obj->geometry.visible_flag == 0){
      continue;
    }
      
    if(last_obj != objs[i] || obj->transform.mvp_flag == 1 || ppl->forceUpdate){
      glUniformMatrix4fv(ppl->uni_matrix, 1, GL_FALSE, obj->transform.mvp.data);
      obj->transform.mvp_flag = 0;
    }

    glBindVertexArray(obj->geometry.vao);

    if(obj->geometry.vertex_flag == 1) {
      glBindBuffer(GL_ARRAY_BUFFER, obj->geometry.vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(powergl_vec3) * obj->geometry.n_vertex,  obj->geometry.vertex, GL_STATIC_DRAW);
      obj->geometry.vertex_flag = 0;
    }

    if ( obj->geometry.triangles.color_flag == 1) {
      glBindBuffer( GL_ARRAY_BUFFER, obj->geometry.cbo );
      glBufferData( GL_ARRAY_BUFFER, sizeof( powergl_vec3 ) * obj->geometry.triangles.n_color, obj->geometry.triangles.color, GL_STATIC_DRAW );
      obj->geometry.triangles.color_flag = 0;
    }


#if DEBUG_OUTPUT
    for(size_t j=0; j < obj->geometry.n_vertex; j++){	      
      powergl_vec4 vec = {.xyz=obj->geometry.vertex[j], .w1 = 1.0f};
      powergl_vec4_print("transformed", powergl_vec4_trans(vec, obj->transform.mvp));
    }
#endif

    if(obj->selected && powergl_enable_outline){
      draw_outline(obj);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDrawArrays(obj->geometry.primitive_type, 0, obj->geometry.n_vertex);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    last_obj = obj;
        
  }



}


static void render2(powergl_pipeline2 *ppl, powergl_object **objs, size_t n_object){

  powergl_object *obj = NULL;
    
  for(size_t i = 0; i < n_object; ++i) {
    obj = objs[i];

    if(obj->n_object > 0){
      render2(ppl, obj->objects, obj->n_object);
    }

    if(obj->geometry.visible_flag == 0){
      continue;
    }
      
    if(last_obj != objs[i] || obj->transform.mvp_flag == 1 || ppl->forceUpdate){
      glUniformMatrix4fv(ppl->uni_matrix, 1, GL_FALSE, obj->transform.mvp.data);
      obj->transform.mvp_flag = 0;
    }

    glBindVertexArray(obj->geometry.vao);

    if(obj->geometry.vertex_flag == 1) {
      glBindBuffer(GL_ARRAY_BUFFER, obj->geometry.vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(powergl_vec3) * obj->geometry.n_vertex,  obj->geometry.vertex, GL_STATIC_DRAW);
      obj->geometry.vertex_flag = 0;
    }


#if DEBUG_OUTPUT
    for(size_t j=0; j < obj->geometry.n_vertex; j++){	      
      powergl_vec4 vec = {.xyz=obj->geometry.vertex[j], .w1 = 1.0f};
      powergl_vec4_print("transformed", powergl_vec4_trans(vec, obj->transform.mvp));
    }
#endif

    if(obj->selected && powergl_enable_outline){
      // draw_outline(obj);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDrawArrays(obj->geometry.primitive_type, 0, obj->geometry.n_vertex);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    last_obj = obj;
        
  }



}

static void render(powergl_pipeline *ppl, powergl_object **objs, size_t n_object){

  powergl_object *obj = NULL;
    
  for(size_t i = 0; i < n_object; ++i) {
    obj = objs[i];

    if(obj->n_object > 0){
      render(ppl, obj->objects, obj->n_object);
    }

    if(obj->geometry.visible_flag == 0){
      continue;
    }


      
    if(last_obj != objs[i] || obj->transform.mvp_flag == 1 || ppl->forceUpdate){
      glUniformMatrix4fv(ppl->uni_matrix, 1, GL_FALSE, obj->transform.mvp.data);
      glUniform1i(ppl->uni_sampler, 0);
      obj->transform.mvp_flag = 0;
    }

    glBindVertexArray(obj->geometry.vao);

    if(obj->geometry.vertex_flag == 1) {
      glBindBuffer(GL_ARRAY_BUFFER, obj->geometry.vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(powergl_vec3) * obj->geometry.n_vertex,  obj->geometry.vertex, GL_STATIC_DRAW);
      obj->geometry.vertex_flag = 0;
    }

    if ( obj->geometry.triangles.normal_flag == 1 ) {
      glBindBuffer( GL_ARRAY_BUFFER, obj->geometry.nbo );
      glBufferData( GL_ARRAY_BUFFER, sizeof( powergl_vec3 ) * obj->geometry.triangles.n_normal, obj->geometry.triangles.normal, GL_STATIC_DRAW );
      obj->geometry.triangles.normal_flag = 0;
    }

    if ( obj->geometry.triangles.color_flag == 1 ) {
      glBindBuffer( GL_ARRAY_BUFFER, obj->geometry.cbo );
      glBufferData( GL_ARRAY_BUFFER, sizeof( powergl_vec3 ) * obj->geometry.triangles.n_color, obj->geometry.triangles.color, GL_STATIC_DRAW );
      obj->geometry.triangles.color_flag = 0;
    }

    if ( obj->geometry.triangles.texcoord_flag == 1 ) {
      glBindBuffer( GL_ARRAY_BUFFER, obj->geometry.tcbo );
      glBufferData( GL_ARRAY_BUFFER, sizeof( powergl_vec3 ) * obj->geometry.triangles.n_texcoord, obj->geometry.triangles.texcoord, GL_STATIC_DRAW );
      obj->geometry.triangles.texcoord_flag = 0;
    }


#if DEBUG_OUTPUT
    for(size_t j=0; j < obj->geometry.n_vertex; j++){	      
      powergl_vec4 vec = {.xyz=obj->geometry.vertex[j], .w1 = 1.0f};
      powergl_vec4_print("transformed", powergl_vec4_trans(vec, obj->transform.mvp));
    }
#endif

    if(obj->selected && powergl_enable_outline){
      // draw_outline(obj);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDrawArrays(obj->geometry.primitive_type, 0, obj->geometry.n_vertex);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    last_obj = obj;
        
  }



}

void powergl_pipeline3_render(powergl_pipeline3 *ppl, powergl_object **objs, size_t n_object) {

    if(ppl!=last_ppl3 || ppl->forceUpdate){
      
      glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
      glClearStencil(0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glEnable (GL_CULL_FACE); 
      glCullFace (GL_BACK);

      // restore uniforms
      glUseProgram(ppl->gp);

      // restore global states
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    }
      
    render3(ppl, objs, n_object);

    /* restore solid mode for subsequent passes (e.g. UI rendering) */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    last_ppl3 = ppl;

    return;
}

void powergl_pipeline2_render(powergl_pipeline2 *ppl, powergl_object **objs, size_t n_object) {

    if(ppl!=last_ppl2 || ppl->forceUpdate){

      // restore uniforms
      glUseProgram(ppl->gp);

      // restore global states
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    }
      
    render2(ppl, objs, n_object);

    /* ensure next passes start in solid mode */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    last_ppl2 = ppl;

    return;
}


void powergl_pipeline_render(powergl_pipeline *ppl, powergl_object **objs, size_t n_object, powergl_object *main_light) {

    if(ppl!=last_ppl || ppl->forceUpdate){

      glClearColor(0.3f, 0.6f, 0.9f, 1.0f);
      glClearStencil(0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
      glEnable(GL_DEPTH_TEST);
      glEnable (GL_CULL_FACE);
      glCullFace (GL_BACK);

      // restore uniforms
      glUseProgram(ppl->gp);

      // restore global states
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    }

    if (main_light->light.color_flag == 1) {
      glUniform3fv( ppl->uni_light_color, 1, main_light->light.color.data);
      main_light->light.color_flag = 0;
    }

    if (main_light->light.dir_flag == 1) {
      glUniform3fv( ppl->uni_light_dir, 1, main_light->light.dir.data);
      main_light->light.dir_flag = 0;
    }

    render(ppl, objs, n_object);

    /* reset to solid mode so subsequent draws (e.g. UI) are unaffected */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    last_ppl = ppl;

    return;
}


void powergl_pipeline3_create_objects(powergl_pipeline3 *ppl, powergl_object **objs, size_t n_obj){

  for(size_t i=0; i<n_obj; i++){

    if(objs[i]->n_object > 0){
      powergl_pipeline3_create_objects(ppl, objs[i]->objects, objs[i]->n_object);
    }

    if(objs[i]->geometry.visible_flag == 1){
      
      glGenVertexArrays(1, &objs[i]->geometry.vao);

      glBindVertexArray(objs[i]->geometry.vao);
      
      glGenBuffers(1, &objs[i]->geometry.vbo);
      glGenBuffers(1, &objs[i]->geometry.cbo);
    
      glEnableVertexAttribArray(ppl->vis.index);
      glEnableVertexAttribArray(ppl->cis.index);


      glBindBuffer(GL_ARRAY_BUFFER, objs[i]->geometry.vbo);
      glVertexAttribPointer( ppl->vis.index, ppl->vis.size, ppl->vis.type, ppl->vis.normalized, ppl->vis.stride, ppl->vis.offset );

      glBindBuffer( GL_ARRAY_BUFFER, objs[i]->geometry.cbo );
      glVertexAttribPointer( ppl->cis.index, ppl->cis.size, ppl->cis.type, ppl->cis.normalized, ppl->cis.stride, ppl->cis.offset );
    

    }


    
  }

}

void powergl_pipeline2_create_objects(powergl_pipeline2 *ppl, powergl_object **objs, size_t n_obj){

  for(size_t i=0; i<n_obj; i++){

    if(objs[i]->n_object > 0){
      powergl_pipeline2_create_objects(ppl, objs[i]->objects, objs[i]->n_object);
    }

    if(objs[i]->geometry.visible_flag == 1){
      
      glGenVertexArrays(1, &objs[i]->geometry.vao);

      glBindVertexArray(objs[i]->geometry.vao);
      
      glGenBuffers(1, &objs[i]->geometry.vbo);
    
      glEnableVertexAttribArray(ppl->vis.index);


      glBindBuffer(GL_ARRAY_BUFFER, objs[i]->geometry.vbo);
      glVertexAttribPointer( ppl->vis.index, ppl->vis.size, ppl->vis.type, ppl->vis.normalized, ppl->vis.stride, ppl->vis.offset );
    

    }


    
  }

}


void powergl_pipeline_create_objects(powergl_pipeline *ppl, powergl_object **objs, size_t n_obj){

  for(size_t i=0; i<n_obj; i++){

    if(objs[i]->n_object > 0){
      powergl_pipeline_create_objects(ppl, objs[i]->objects, objs[i]->n_object);
    }

    if(objs[i]->geometry.visible_flag == 1){
      
      glGenVertexArrays(1, &objs[i]->geometry.vao);

      glBindVertexArray(objs[i]->geometry.vao);
      
      glGenBuffers(1, &objs[i]->geometry.vbo);
      glGenBuffers(1, &objs[i]->geometry.nbo);
      glGenBuffers(1, &objs[i]->geometry.cbo);
      glGenBuffers(1, &objs[i]->geometry.tcbo);
    
      glEnableVertexAttribArray(ppl->vis.index);
      glEnableVertexAttribArray(ppl->nis.index);
      glEnableVertexAttribArray(ppl->cis.index);
      glEnableVertexAttribArray(ppl->tcis.index);

      glBindBuffer(GL_ARRAY_BUFFER, objs[i]->geometry.vbo);
      glVertexAttribPointer( ppl->vis.index, ppl->vis.size, ppl->vis.type, ppl->vis.normalized, ppl->vis.stride, ppl->vis.offset );

      glBindBuffer( GL_ARRAY_BUFFER, objs[i]->geometry.nbo );
      glVertexAttribPointer( ppl->nis.index, ppl->nis.size, ppl->nis.type, ppl->nis.normalized, ppl->nis.stride, ppl->nis.offset );

      glBindBuffer( GL_ARRAY_BUFFER, objs[i]->geometry.cbo );
      glVertexAttribPointer( ppl->cis.index, ppl->cis.size, ppl->cis.type, ppl->cis.normalized, ppl->cis.stride, ppl->cis.offset );

      glBindBuffer( GL_ARRAY_BUFFER, objs[i]->geometry.tcbo );
      glVertexAttribPointer( ppl->tcis.index, ppl->tcis.size, ppl->tcis.type, ppl->tcis.normalized, ppl->tcis.stride, ppl->tcis.offset );
      
      if(objs[i]->textured_flag == 1){

	glGenTextures( 1, &objs[i]->texture.id );
	glActiveTexture(GL_TEXTURE0);
	glBindTexture( GL_TEXTURE_2D, objs[i]->texture.id );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
		      objs[i]->texture.image.width,
		      objs[i]->texture.image.height, 0, 
		      GL_RGBA, GL_UNSIGNED_BYTE,
		      (GLvoid *) objs[i]->texture.image.data );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

      }
    

    }


    
  }

}


void powergl_pipeline3_create(powergl_pipeline3 *ppl, powergl_object **objs, size_t n_obj) {
  
  ppl->forceUpdate = 0;
  /*vertex shader input attibute specs*/
  
  /*vertex input*/
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
  const GLchar *const vsrc[] = { "#version 330 core\n\
    layout( location = 0 ) in vec3 vPosition;\n		\
    layout( location = 1 ) in vec3 vColor;\n		\
    out vec3 colorToFs;\n				\
    uniform mat4 mvp;\n					\
    void main(){\n							\
      vec3 ambient = vec3(0.1f, 0.1f, 0.1f);				\
      colorToFs = ambient + vColor;\n 					\
      gl_Position = mvp * vec4( vPosition, 1.0f );\n			\
    }"
  };
  const GLchar *const fsrc[] = {"#version 330 core\n\
    in vec3 colorToFs;\n				   \
    out vec4 fColor;\n					   \
    void main(){\n						   \
      fColor = vec4(colorToFs, 1.0f);\n				   \
    }"
  };

    /*shader compiler input specs*/
  const GLchar *const vsrcOutline[] = { "#version 330 core\n\
    layout( location = 0 ) in vec3 vPosition;\n		\
    uniform mat4 mvp;\n					\
    void main(){\n							\
       vec3 pos = vPosition;\
       pos *= 1.05; \
      gl_Position = mvp * 1.05 * vec4( pos, 1.0f );\n			\
    }"
  };
  const GLchar *const fsrcOutline[] = {"#version 330 core\n\
    out vec4 fColor;\n					   \
    void main(){\n						   \
      fColor = vec4(0.05, 0.9, 0.2, 1.0);\n				   \
    }"
  };

  /*vertex shader*/
  ppl->vsOutline = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ppl->vsOutline, 1, vsrcOutline, NULL);
  glCompileShader(ppl->vsOutline);
  /*fragment shader*/
  ppl->fsOutline = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ppl->fsOutline, 1, fsrcOutline, NULL);
  glCompileShader(ppl->fsOutline);
  /*program*/
  ppl->gpOutline = glCreateProgram();
  glAttachShader(ppl->gpOutline, ppl->vsOutline);
  glAttachShader(ppl->gpOutline, ppl->fsOutline);
  glLinkProgram(ppl->gpOutline);
  /*uniform*/
  /* uniform a verilen string ayri tutulacak  bunun icin biseyler dusun*/
  glUseProgram(ppl->gpOutline);
  ppl->uni_matrixOutline = glGetUniformLocation(ppl->gpOutline, "mvp");

  /*vertex shader*/
  ppl->vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ppl->vs, 1, vsrc, NULL);
  glCompileShader(ppl->vs);
  /*fragment shader*/
  ppl->fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ppl->fs, 1, fsrc, NULL);
  glCompileShader(ppl->fs);
  /*program*/
  ppl->gp = glCreateProgram();
  glAttachShader(ppl->gp, ppl->vs);
  glAttachShader(ppl->gp, ppl->fs);
  glLinkProgram(ppl->gp);
  /*uniform*/
  /* uniform a verilen string ayri tutulacak  bunun icin biseyler dusun*/
  glUseProgram(ppl->gp);
  ppl->uni_matrix = glGetUniformLocation(ppl->gp, "mvp");

  powergl_pipeline3_create_objects(ppl, objs, n_obj);

  return;
}

void powergl_pipeline2_create(powergl_pipeline2 *ppl, powergl_object **objs, size_t n_obj) {
  ppl->forceUpdate = 0;
  
  /*vertex shader input attibute specs*/
  
  /*vertex input*/
  ppl->vis.index = 0;
  ppl->vis.size = 3;
  ppl->vis.type = GL_FLOAT;
  ppl->vis.normalized = GL_FALSE;
  ppl->vis.stride = 0;
  ppl->vis.offset = 0;
    

  /*shader compiler input specs*/
  const GLchar *const vsrc[] = { "#version 330 core\n\
    layout( location = 0 ) in vec3 vPosition;\n		\
    out vec3 colorToFs;\n				\
    uniform mat4 mvp;\n					\
    void main(){\n							\
      vec3 ambient = vec3(0.1f, 0.1f, 0.1f);				\
      colorToFs = ambient;\n						\
      gl_Position = mvp * vec4( vPosition, 1.0f );\n			\
    }"
  };
  const GLchar *const fsrc[] = {"#version 330 core\n\
    in vec3 colorToFs;\n				   \
    out vec4 fColor;\n					   \
    void main(){\n					   \
      fColor = vec4(colorToFs,1.0f);\n			   \
    }"
  };
  /*vertex shader*/
  ppl->vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ppl->vs, 1, vsrc, NULL);
  glCompileShader(ppl->vs);
  /*fragment shader*/
  ppl->fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ppl->fs, 1, fsrc, NULL);
  glCompileShader(ppl->fs);
  /*program*/
  ppl->gp = glCreateProgram();
  glAttachShader(ppl->gp, ppl->vs);
  glAttachShader(ppl->gp, ppl->fs);
  glLinkProgram(ppl->gp);
  /*uniform*/
  /* uniform a verilen string ayri tutulacak  bunun icin biseyler dusun*/
  glUseProgram(ppl->gp);
  ppl->uni_matrix = glGetUniformLocation(ppl->gp, "mvp");
 
  powergl_pipeline2_create_objects(ppl, objs, n_obj);

  return;
}

void powergl_pipeline_create(powergl_pipeline *ppl, powergl_object **objs, size_t n_obj) {
  ppl->forceUpdate = 0;
  
  /*vertex shader input attibute specs*/
  
  /*vertex input*/
  ppl->vis.index = 0;
  ppl->vis.size = 3;
  ppl->vis.type = GL_FLOAT;
  ppl->vis.normalized = GL_FALSE;
  ppl->vis.stride = 0;
  ppl->vis.offset = 0;
    
  /* normal input */
  ppl->nis.index = 1;
  ppl->nis.size = 3;
  ppl->nis.type = GL_FLOAT;
  ppl->nis.normalized = GL_FALSE;
  ppl->nis.stride = 0;
  ppl->nis.offset = 0;

  /* color input */
  ppl->cis.index = 2;
  ppl->cis.size = 3;
  ppl->cis.type = GL_FLOAT;
  ppl->cis.normalized = GL_FALSE;
  ppl->cis.stride = 0;
  ppl->cis.offset = 0;

  /* texcoord input */
  ppl->tcis.index = 3;
  ppl->tcis.size = 2;
  ppl->tcis.type = GL_FLOAT;
  ppl->tcis.normalized = GL_FALSE;
  ppl->tcis.stride = 0;
  ppl->tcis.offset = 0;

  /*shader compiler input specs*/
  const GLchar *const vsrc[] = { "#version 330 core\n\
    layout( location = 0 ) in vec3 vPosition;\n		\
    layout( location = 1 ) in vec3 vNormal;\n		\
    layout( location = 2 ) in vec3 vColor;\n		\
    layout( location = 3 ) in vec2 vTexCoord;\n		\
    out vec3 colorToFs;\n				\
    out vec2 texCoordToFs;\n				\
    uniform mat4 mvp;\n					\
    uniform vec3 lightColor;\n				\
    uniform vec3 lightDir;\n						\
    void main(){\n							\
      vec3 ambient = vec3(0.1f, 0.1f, 0.1f);				\
      colorToFs = ambient + vColor * ( lightColor * max(dot(vNormal, reflect(lightDir,vNormal)),0) );\n \
      texCoordToFs = vTexCoord;\n			\
      gl_Position = mvp * vec4( vPosition, 1.0f );\n			\
    }"
  };
  const GLchar *const fsrc[] = {"#version 330 core\n\
    in vec3 colorToFs;\n				   \
    in vec2 texCoordToFs;\n				   \
    out vec4 fColor;\n					   \
    uniform sampler2D texUnit;\n			   \
    void main(){\n					   \
      vec4 texColor = texture(texUnit, texCoordToFs);\n	   \
      fColor = texColor;\n				   \
    }"
  };
  /*vertex shader*/
  ppl->vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ppl->vs, 1, vsrc, NULL);
  glCompileShader(ppl->vs);
  /*fragment shader*/
  ppl->fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ppl->fs, 1, fsrc, NULL);
  glCompileShader(ppl->fs);
  /*program*/
  ppl->gp = glCreateProgram();
  glAttachShader(ppl->gp, ppl->vs);
  glAttachShader(ppl->gp, ppl->fs);
  glLinkProgram(ppl->gp);
  /*uniform*/
  /* uniform a verilen string ayri tutulacak  bunun icin biseyler dusun*/
  glUseProgram(ppl->gp);
  ppl->uni_matrix = glGetUniformLocation(ppl->gp, "mvp");
  ppl->uni_light_color = glGetUniformLocation( ppl->gp, "lightColor" );
  ppl->uni_light_dir = glGetUniformLocation( ppl->gp, "lightDir" );
  ppl->uni_sampler = glGetUniformLocation( ppl->gp, "texUnit" );

  powergl_pipeline_create_objects(ppl, objs, n_obj);

  return;
}

void powergl_pipeline_flat_create(powergl_pipeline *ppl, powergl_object **objs, size_t n_obj) {
  ppl->forceUpdate = 0;
  /*vertex shader input attribute specs*/
  /*vertex input*/
  ppl->vis.index = 0;
  ppl->vis.size = 3;
  ppl->vis.type = GL_FLOAT;
  ppl->vis.normalized = GL_FALSE;
  ppl->vis.stride = 0;
  ppl->vis.offset = 0;

  /* normal input */
  ppl->nis.index = 1;
  ppl->nis.size = 3;
  ppl->nis.type = GL_FLOAT;
  ppl->nis.normalized = GL_FALSE;
  ppl->nis.stride = 0;
  ppl->nis.offset = 0;

  /* color input */
  ppl->cis.index = 2;
  ppl->cis.size = 3;
  ppl->cis.type = GL_FLOAT;
  ppl->cis.normalized = GL_FALSE;
  ppl->cis.stride = 0;
  ppl->cis.offset = 0;

  /*shader compiler input specs*/
  const GLchar *const vsrc[] = {
    "#version 330 core\n"
    "layout(location = 0) in vec3 vPosition;\n"
    "layout(location = 1) in vec3 vNormal;\n"
    "out flat vec3 normalToFs;\n"
    "uniform mat4 mvp;\n"
    "void main(){\n"
    "  normalToFs = vNormal;\n"
    "  gl_Position = mvp * vec4(vPosition,1.0);\n"
    "}"
  };
  const GLchar *const fsrc[] = {
    "#version 330 core\n"
    "in flat vec3 normalToFs;\n"
    "out vec4 fColor;\n"
    "uniform vec3 lightColor;\n"
    "uniform vec3 lightDir;\n"
    "void main(){\n"
    "  vec3 ambient = vec3(0.1,0.1,0.1);\n"
    "  float diff = max(dot(normalize(normalToFs), normalize(-lightDir)),0.0);\n"
    "  vec3 result = (ambient + diff * lightColor) * vec3(0.5, 0.5, 0.5);\n"
    "  fColor = vec4(result,1.0);\n"
    "}"
  };

  ppl->vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ppl->vs, 1, vsrc, NULL);
  glCompileShader(ppl->vs);
  ppl->fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ppl->fs, 1, fsrc, NULL);
  glCompileShader(ppl->fs);
  ppl->gp = glCreateProgram();
  glAttachShader(ppl->gp, ppl->vs);
  glAttachShader(ppl->gp, ppl->fs);
  glLinkProgram(ppl->gp);
  glUseProgram(ppl->gp);
  ppl->uni_matrix = glGetUniformLocation(ppl->gp, "mvp");
  ppl->uni_light_color = glGetUniformLocation(ppl->gp, "lightColor");
  ppl->uni_light_dir = glGetUniformLocation(ppl->gp, "lightDir");
  ppl->uni_sampler = -1;

  for(size_t i = 0; i < n_obj; ++i){
    powergl_object_generate_flat_normals(objs[i]);
  }

  powergl_pipeline_create_objects(ppl, objs, n_obj);
}

void powergl_pipeline_gouraud_create(powergl_pipeline *ppl, powergl_object **objs, size_t n_obj) {
  ppl->forceUpdate = 0;
  /*vertex shader input attribute specs*/
  /*vertex input*/
  ppl->vis.index = 0;
  ppl->vis.size = 3;
  ppl->vis.type = GL_FLOAT;
  ppl->vis.normalized = GL_FALSE;
  ppl->vis.stride = 0;
  ppl->vis.offset = 0;

  /* normal input */
  ppl->nis.index = 1;
  ppl->nis.size = 3;
  ppl->nis.type = GL_FLOAT;
  ppl->nis.normalized = GL_FALSE;
  ppl->nis.stride = 0;
  ppl->nis.offset = 0;

  /* color input */
  ppl->cis.index = 2;
  ppl->cis.size = 3;
  ppl->cis.type = GL_FLOAT;
  ppl->cis.normalized = GL_FALSE;
  ppl->cis.stride = 0;
  ppl->cis.offset = 0;

  const GLchar *const vsrc[] = {
    "#version 330 core\n"
    "layout(location = 0) in vec3 vPosition;\n"
    "layout(location = 1) in vec3 vNormal;\n"
    "layout(location = 2) in vec3 vColor;\n"
    "out vec3 colorToFs;\n"
    "uniform mat4 mvp;\n"
    "uniform vec3 lightColor;\n"
    "uniform vec3 lightDir;\n"
    "void main(){\n"
    "  vec3 ambient = vec3(0.1,0.1,0.1);\n"
    "  float diff = max(dot(normalize(vNormal), normalize(-lightDir)),0.0);\n"
    "  colorToFs = (ambient + diff * lightColor) * vColor;\n"
    "  gl_Position = mvp * vec4(vPosition,1.0);\n"
    "}"
  };
  const GLchar *const fsrc[] = {
    "#version 330 core\n"
    "in vec3 colorToFs;\n"
    "out vec4 fColor;\n"
    "void main(){\n"
    "  fColor = vec4(colorToFs,1.0);\n"
    "}"
  };

  ppl->vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ppl->vs, 1, vsrc, NULL);
  glCompileShader(ppl->vs);
  ppl->fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ppl->fs, 1, fsrc, NULL);
  glCompileShader(ppl->fs);
  ppl->gp = glCreateProgram();
  glAttachShader(ppl->gp, ppl->vs);
  glAttachShader(ppl->gp, ppl->fs);
  glLinkProgram(ppl->gp);
  glUseProgram(ppl->gp);
  ppl->uni_matrix = glGetUniformLocation(ppl->gp, "mvp");
  ppl->uni_light_color = glGetUniformLocation(ppl->gp, "lightColor");
  ppl->uni_light_dir = glGetUniformLocation(ppl->gp, "lightDir");
  ppl->uni_sampler = -1;

  powergl_pipeline_create_objects(ppl, objs, n_obj);
}

void powergl_pipeline_lambert_create(powergl_pipeline *ppl, powergl_object **objs, size_t n_obj) {
  ppl->forceUpdate = 0;
  /*vertex shader input attribute specs*/
  /*vertex input*/
  ppl->vis.index = 0;
  ppl->vis.size = 3;
  ppl->vis.type = GL_FLOAT;
  ppl->vis.normalized = GL_FALSE;
  ppl->vis.stride = 0;
  ppl->vis.offset = 0;

  /* normal input */
  ppl->nis.index = 1;
  ppl->nis.size = 3;
  ppl->nis.type = GL_FLOAT;
  ppl->nis.normalized = GL_FALSE;
  ppl->nis.stride = 0;
  ppl->nis.offset = 0;

  /* color input */
  ppl->cis.index = 2;
  ppl->cis.size = 3;
  ppl->cis.type = GL_FLOAT;
  ppl->cis.normalized = GL_FALSE;
  ppl->cis.stride = 0;
  ppl->cis.offset = 0;

  const GLchar *const vsrc[] = {
    "#version 330 core\n"
    "layout(location = 0) in vec3 vPosition;\n"
    "layout(location = 1) in vec3 vNormal;\n"
    "layout(location = 2) in vec3 vColor;\n"
    "out vec3 normalToFs;\n"
    "out vec3 colorToFs;\n"
    "uniform mat4 mvp;\n"
    "void main(){\n"
    "  normalToFs = vNormal;\n"
    "  colorToFs = vColor;\n"
    "  gl_Position = mvp * vec4(vPosition,1.0);\n"
    "}"
  };
  const GLchar *const fsrc[] = {
    "#version 330 core\n"
    "in vec3 normalToFs;\n"
    "in vec3 colorToFs;\n"
    "out vec4 fColor;\n"
    "uniform vec3 lightColor;\n"
    "uniform vec3 lightDir;\n"
    "void main(){\n"
    "  vec3 ambient = vec3(0.1,0.1,0.1);\n"
    "  float diff = max(dot(normalize(normalToFs), normalize(-lightDir)),0.0);\n"
    "  vec3 result = (ambient + diff * lightColor) * colorToFs;\n"
    "  fColor = vec4(result,1.0);\n"
    "}"
  };

  ppl->vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ppl->vs, 1, vsrc, NULL);
  glCompileShader(ppl->vs);
  ppl->fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ppl->fs, 1, fsrc, NULL);
  glCompileShader(ppl->fs);
  ppl->gp = glCreateProgram();
  glAttachShader(ppl->gp, ppl->vs);
  glAttachShader(ppl->gp, ppl->fs);
  glLinkProgram(ppl->gp);
  glUseProgram(ppl->gp);
  ppl->uni_matrix = glGetUniformLocation(ppl->gp, "mvp");
  ppl->uni_light_color = glGetUniformLocation(ppl->gp, "lightColor");
  ppl->uni_light_dir = glGetUniformLocation(ppl->gp, "lightDir");
  ppl->uni_sampler = -1;

  powergl_pipeline_create_objects(ppl, objs, n_obj);
}

void powergl_pipeline_blinnphong_create(powergl_pipeline *ppl, powergl_object **objs, size_t n_obj) {
  ppl->forceUpdate = 0;
  /*vertex shader input attribute specs*/
  /*vertex input*/
  ppl->vis.index = 0;
  ppl->vis.size = 3;
  ppl->vis.type = GL_FLOAT;
  ppl->vis.normalized = GL_FALSE;
  ppl->vis.stride = 0;
  ppl->vis.offset = 0;

  /* normal input */
  ppl->nis.index = 1;
  ppl->nis.size = 3;
  ppl->nis.type = GL_FLOAT;
  ppl->nis.normalized = GL_FALSE;
  ppl->nis.stride = 0;
  ppl->nis.offset = 0;

  /* color input */
  ppl->cis.index = 2;
  ppl->cis.size = 3;
  ppl->cis.type = GL_FLOAT;
  ppl->cis.normalized = GL_FALSE;
  ppl->cis.stride = 0;
  ppl->cis.offset = 0;

  const GLchar *const vsrc[] = {
    "#version 330 core\n"
    "layout(location = 0) in vec3 vPosition;\n"
    "layout(location = 1) in vec3 vNormal;\n"
    "layout(location = 2) in vec3 vColor;\n"
    "out vec3 normalToFs;\n"
    "out vec3 colorToFs;\n"
    "uniform mat4 mvp;\n"
    "void main(){\n"
    "  normalToFs = vNormal;\n"
    "  colorToFs = vColor;\n"
    "  gl_Position = mvp * vec4(vPosition,1.0);\n"
    "}"
  };
  const GLchar *const fsrc[] = {
    "#version 330 core\n"
    "in vec3 normalToFs;\n"
    "in vec3 colorToFs;\n"
    "out vec4 fColor;\n"
    "uniform vec3 lightColor;\n"
    "uniform vec3 lightDir;\n"
    "void main(){\n"
    "  vec3 ambient = vec3(0.1,0.1,0.1);\n"
    "  vec3 norm = normalize(normalToFs);\n"
    "  vec3 ld = normalize(-lightDir);\n"
    "  float diff = max(dot(norm, ld), 0.0);\n"
    "  vec3 viewDir = vec3(0.0,0.0,1.0);\n"
    "  vec3 halfDir = normalize(ld + viewDir);\n"
    "  float spec = pow(max(dot(norm, halfDir), 0.0), 32.0);\n"
    "  vec3 result = (ambient + (diff + spec) * lightColor) * colorToFs;\n"
    "  fColor = vec4(result,1.0);\n"
    "}"
  };

  ppl->vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ppl->vs, 1, vsrc, NULL);
  glCompileShader(ppl->vs);
  ppl->fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ppl->fs, 1, fsrc, NULL);
  glCompileShader(ppl->fs);
  ppl->gp = glCreateProgram();
  glAttachShader(ppl->gp, ppl->vs);
  glAttachShader(ppl->gp, ppl->fs);
  glLinkProgram(ppl->gp);
  glUseProgram(ppl->gp);
  ppl->uni_matrix = glGetUniformLocation(ppl->gp, "mvp");
  ppl->uni_light_color = glGetUniformLocation(ppl->gp, "lightColor");
  ppl->uni_light_dir = glGetUniformLocation(ppl->gp, "lightDir");
  ppl->uni_sampler = -1;

  powergl_pipeline_create_objects(ppl, objs, n_obj);
}

