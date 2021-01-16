#include "3dtext.h"
#include "../collada/parse_utils.h"
#include "object.h"

void powergl_3dtext_bake_geo(powergl_3dtext *text){

  // clear 3dtext objects geometry
  if(text->root->geometry.n_vertex > 0){
    powergl_object_geometry_reset(&text->root->geometry);
  }

  powergl_vec3 offset = powergl_vec3_zeros();

  assert(text->root_node);
  powergl_3dtext_node *iterator = text->root_node;

  powergl_vec3 hspace_vec = powergl_vec3_zeros();
    
  size_t i = 0;
  
  while(iterator != NULL){
    
    // append geo into root object's geometry
    
    powergl_object_geometry_append(&text->root->geometry, iterator->geo, offset);

    hspace_vec.x = text->cfg.hspace + iterator->geo->max_x - iterator->geo->min_x;
    
    offset = powergl_vec3_add(offset, hspace_vec);
    
    iterator = iterator->next;
    i++;
  }
}

void powergl_3dtext_build(powergl_3dtext *text, powergl_3dtext_config cfg, powergl_object_library *lib, const char *str){

  // TODO : free allocated spaces every time text is builded

  size_t str_size = strlen(str);

  assert(str_size);
  assert(text->root);

  powergl_3dtext_node *iterator = NULL;
  powergl_3dtext_node *next = NULL;
  
  if(text->str != NULL){

    iterator = text->root_node;
    
    while(iterator != NULL){
      iterator->geo = NULL;
      iterator->prev = NULL;
      next = iterator->next;
      iterator->next = NULL;
      free(iterator);
      iterator = next;
    }

    text->root_node = NULL;
    free(text->str);
    text->str = NULL;

  }

  text->str = powergl_resize(NULL, str_size, sizeof(char));
  text->n_char = str_size;
  text->cfg = cfg;


  iterator = NULL;
  
  for(size_t i=0; i < str_size; i++){

    for(size_t j=0; j < lib->n_object; j++){

      assert(strlen(lib->objects[j]->id) >= 2);

      size_t n_parsed = 0;
      size_t *parsed = NULL;
      const char * tmp_char_ptr = lib->objects[j]->id + 1;
      parsed = powergl_collada_parse_uints(tmp_char_ptr, &n_parsed);
      assert(n_parsed);
      char char_found = 0;
      
      if( parsed[0] == (size_t)str[i]){
		  
	if(i==0){
	  
	  iterator = powergl_resize(NULL, 1, sizeof(powergl_3dtext_node));
	  text->root_node = iterator;
	  iterator->prev = NULL;
	  
	} else {
	  powergl_3dtext_node *new_node = powergl_resize(NULL, 1, sizeof(powergl_3dtext_node));
	  new_node->prev = iterator;
	  iterator->next = new_node;
	  iterator = new_node;
	}

	iterator->next = NULL;
        iterator->geo = &lib->objects[j]->geometry;
	iterator->letter = str[i];
	
	text->str[i] = str[i];

	char_found = 1;
      }

      free(parsed);
      parsed = NULL;

      if(char_found == 1){
	break;
      }
      
    }

  }

  // en son burada kaldim. bounding box hesaplamalari da duzgun calismiyor. min_x yanlis
  // black screen verdi debug edilecek

  powergl_3dtext_bake_geo(text);

  
}
