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
      
    if(last_obj != objs[i]){
      glUniformMatrix4fv(ppl->uni_matrix, 1, GL_FALSE, obj->transform.mvp.data);
    } else if(obj->transform.mvp_flag == 1){      
      glUniformMatrix4fv(ppl->uni_matrix, 1, GL_FALSE, obj->transform.mvp.data);
      obj->transform.mvp_flag = 0;
    }

    glBindVertexArray(obj->geometry.vao);

    if(obj->geometry.vertex_flag == 1) {
      glBindBuffer(GL_ARRAY_BUFFER, obj->geometry.vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(powergl_vec3) * obj->geometry.n_vertex,  obj->geometry.vertex, GL_STATIC_DRAW);
      obj->geometry.vertex_flag = 0;
    }

    if ( obj->geometry.triangles.color_flag == 1 ) {
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

    glDrawArrays( GL_TRIANGLES, 0, obj->geometry.n_vertex );

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
      
    if(last_obj != objs[i]){
      glUniformMatrix4fv(ppl->uni_matrix, 1, GL_FALSE, obj->transform.mvp.data);
    } else if(obj->transform.mvp_flag == 1){      
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

    glDrawArrays( GL_TRIANGLES, 0, obj->geometry.n_vertex );

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


      
    if(last_obj != objs[i]){
      glUniformMatrix4fv(ppl->uni_matrix, 1, GL_FALSE, obj->transform.mvp.data);
      glUniform1i(ppl->uni_sampler, 0);

    } else if(obj->transform.mvp_flag == 1){      
      glUniformMatrix4fv(ppl->uni_matrix, 1, GL_FALSE, obj->transform.mvp.data);
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

    glDrawArrays( GL_TRIANGLES, 0, obj->geometry.n_vertex );

    last_obj = obj;
        
  }



}

void powergl_pipeline3_render(powergl_pipeline3 *ppl, powergl_object **objs, size_t n_object) {

    if(ppl!=last_ppl3){

      // restore uniforms
      glUseProgram(ppl->gp);

      // restore global states
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    }
      
    render3(ppl, objs, n_object);

    last_ppl3 = ppl;
    
    return;
}

void powergl_pipeline2_render(powergl_pipeline2 *ppl, powergl_object **objs, size_t n_object) {

    if(ppl!=last_ppl2){

      // restore uniforms
      glUseProgram(ppl->gp);

      // restore global states
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    }
      
    render2(ppl, objs, n_object);

    last_ppl2 = ppl;
    
    return;
}


void powergl_pipeline_render(powergl_pipeline *ppl, powergl_object **objs, size_t n_object, powergl_object *main_light) {

    if(ppl!=last_ppl){

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
      glVertexAttribPointer( ppl->nis.index, ppl->nis.size, ppl->nis.type, ppl->nis.normalized, ppl->nis.stride, ppl->nis.offset );

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
