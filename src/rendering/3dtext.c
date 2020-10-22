#include "3dtext.h"
#include "../collada/parse_utils.h"
#include "object.h"

void powergl_3dtext_build(powergl_3dtext *text, powergl_3dtext_config cfg, powergl_object_library *lib, const char *str){

  size_t str_size = strlen(str);

  assert(str_size);
  
  text->root = powergl_resize(NULL, 1, sizeof(powergl_object));
  text->str = powergl_resize(NULL, str_size, sizeof(char));
  text->n_char = str_size;
  text->cfg = cfg;

  
  for(size_t i=0; i < str_size; i++){

    for(size_t j=0; j < lib->n_object; j++){

      assert(strlen(lib->objects[j]->id) >= 2);

      size_t n_parsed = 0;
      size_t *parsed = NULL;
      parsed = powergl_collada_parse_uints(lib->objects[j]->id, &n_parsed);

      assert(n_parsed);

      // en son burda kaldim, char dizisinden sayi elde edip onu
      if( parsed[0] == (size_t)str[i]){
	powergl_object_geometry_append(text->root, lib->objects[j]);
	text->str[i] = str[i];
	break;
      }
	 
    }

  }

  
}
