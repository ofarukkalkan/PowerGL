#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
  char *fields[4];
} node;

typedef struct {
  char *fields[3];
  node *nodes;
  size_t n_node;
} type_supported;

type_supported g_types[60];

size_t g_n_type;

void *powergl_resize(void *ptr, size_t newsize) {
  if(ptr == NULL) {
    ptr = malloc(newsize);
    assert(ptr);
  } else {
    void *tmp_ptr = realloc(ptr, newsize);
    assert(tmp_ptr);
    ptr = tmp_ptr;
  }

  return ptr;
}


void generate_def_header(const char *headerfile, const char *mode, char *def_name) {
  FILE *file = fopen(headerfile, mode);
  char *tmp_ptr;

  if(!file) {
    fprintf(stderr, "File opening failed");
    return;
  }

  fprintf(file,
	  "#ifndef _powergl_asset_%s_h\n"	\
	  "#define _powergl_asset_%s_h\n"	\
	  "#include \"dom_connector.h\"\n"	\
	  , def_name, def_name);

  for(int i = 0; i < g_n_type; i++) {
    if(g_types[i].n_node == 0) {
      continue;
    }

    if(*g_types[i].fields[0] == '0') {
      tmp_ptr = g_types[i].fields[1];
    } else {
      tmp_ptr = g_types[i].fields[0];
    }

    fprintf(file, "typedef struct powergl_%s_%s_t powergl_%s_%s;\n", def_name, tmp_ptr, def_name, tmp_ptr);
  }

  for(int i = 0; i < g_n_type; i++) {
    if(g_types[i].n_node == 0) {
      continue;
    }

    if(*g_types[i].fields[0] == '0') {
      tmp_ptr = g_types[i].fields[1];
    } else {
      tmp_ptr = g_types[i].fields[0];
    }

    fprintf(file,
	    "struct powergl_%s_%s_t {\n"		\
	    "dom_connector dom;\n"			\
	    , def_name, tmp_ptr);

    for(int j = 0; j < g_types[i].n_node; j++) {
      switch(*g_types[i].nodes[j].fields[2]) {
      case '0':
	if(*g_types[i].nodes[j].fields[0] == '0') {
	  tmp_ptr = g_types[i].nodes[j].fields[1];
	} else {
	  tmp_ptr = g_types[i].nodes[j].fields[0];
	}

	fprintf(file,
		"powergl_%s_%s** c_%s; size_t n_%s;\n"		\
		, def_name, tmp_ptr,
		g_types[i].nodes[j].fields[1],
		g_types[i].nodes[j].fields[1]);
	break;

      case '1':
	if(strcmp(g_types[i].nodes[j].fields[0], "size_t") != 0) {
	  fprintf(file,
		  "%s c_%s; size_t n_%s;\n"		\
		  , g_types[i].nodes[j].fields[0],
		  g_types[i].nodes[j].fields[1],
		  g_types[i].nodes[j].fields[1]);
	} else {
	  fprintf(file,
		  "%s c_%s;\n"				\
		  , g_types[i].nodes[j].fields[0],
		  g_types[i].nodes[j].fields[1]);
	}

	break;

      case '2':
	fprintf(file,
		"%s content; size_t n_content;\n"		\
		, g_types[i].nodes[j].fields[0]);
	break;

      case '3':
	fprintf(file,
		"powergl_%s_%s* r_%s;\n"		\
		, def_name, g_types[i].nodes[j].fields[0],
		g_types[i].nodes[j].fields[1]);
	break;

      default:
	assert(0);
      }
    }

    fprintf(file, "};\n");
  }

  fprintf(file, "#endif");
  fclose(file);
}

void generate_imp_header(char *headerfile, char *deffile, char *def_name) {
  FILE *file = fopen(headerfile, "w");
  char *tmp_ptr;
  char *tmp_ptr2;

  if(!file) {
    fprintf(stderr, "File opening failed");
    return;
  }

  char g_field_str[] = "g_supported_collada_core_types";
  char g_n_field_str[] = "g_n_supported_collada_core_types";
  fprintf(file, "#include \"../collada.h\"\n");
  ///////////////////////////////////////////////
  // get instance & check
  fprintf(file, "int powergl_%s_check_type(const char *this, const char *parent);\n", def_name);
  fprintf(file, "void* powergl_%s_get_instance(const char *this, const char *parent);\n", def_name);
  fprintf(file, "void powergl_%s_init();\n", def_name);
  fclose(file);
}


void generate_imp_source(char *sourcefile, char *headerfile, char *def_name) {
  FILE *file = fopen(sourcefile, "w");
  char *tmp_ptr;
  char *tmp_ptr2;

  if(!file) {
    fprintf(stderr, "File opening failed");
    return;
  }

  char g_field_str[] = "g_supported_collada_core_types";
  char g_n_field_str[] = "g_n_supported_collada_core_types";
  size_t i_ref_type;
  int flag = 0;
  fprintf(file, "#include \"%s\"\n", headerfile);
  //////////////////////////////////////////get instance & check
  fprintf(file, "static size_t %s;\n", g_n_field_str);
  fprintf(file, "static supported_type %s[%u];\n", g_field_str, g_n_type);
  fprintf(file, "int powergl_%s_check_type(const char *this, const char *parent){\n"\
	  "for(size_t i=0; i<%s; i++){\n"			\
	  "if(strcmp(%s[i].name, this) == 0 && strcmp(%s[i].parent, parent) == 0 ){\n" \
	  "return i;\n}\n}\nreturn -1;\n}\n", def_name, g_n_field_str, g_field_str, g_field_str);
  fprintf(file, "void* powergl_%s_get_instance(const char *this, const char *parent){\n"\
	  "int index = powergl_%s_check_type(this, parent);\n"\
	  "if( index > -1 ) return %s[index].get_instance();\n" \
	  "else return NULL;\n}\n", def_name, def_name,  g_field_str);

  ////////////////////////////////////////////////
  for(int i = 0; i < g_n_type; i++) {
    if(g_types[i].n_node == 0) {
      continue;
    }

    if(*g_types[i].fields[0] == '0') {
      tmp_ptr = g_types[i].fields[1];
    } else {
      tmp_ptr = g_types[i].fields[0];
    }

    //////////////////////////////////////set_ref
    fprintf(file, "void set_ref_%s_%s(void *obj, size_t index, dom_connector *ptr){\n", def_name, tmp_ptr);

    for(size_t j = 0; j < g_types[i].n_node; j++) {
      if(*g_types[i].nodes[j].fields[2] == '3') {
	flag = 1;
	break;
      }
    }

    if(flag == 1) {
      fprintf(file, "powergl_%s_%s *this = (powergl_%s_%s*)obj;\n", def_name, tmp_ptr, def_name, tmp_ptr);
      fprintf(file, "switch(index){\n");

      for(size_t j = 0; j < g_types[i].n_node; j++) {
	switch(*g_types[i].nodes[j].fields[2]) {
	case '3':
	  fprintf(file, "case %u: powergl_collada_set_ref(this->dom.nodes, index, ptr);\n", j);
	  fprintf(file, "this->r_%s = (powergl_%s_%s*)ptr;\nbreak;\n", g_types[i].nodes[j].fields[1], def_name, g_types[i].nodes[j].fields[0]);
	  break;
	}
      }

      fprintf(file, "}\n");
    }

    fprintf(file, "}\n");
    flag = 0;
    //////////////////////////////////////parse content
    fprintf(file, "void parse_content_%s_%s(void *obj, size_t index, const char *value){\n", def_name, tmp_ptr);

    for(size_t j = 0; j < g_types[i].n_node; j++) {
      if(*g_types[i].nodes[j].fields[2] == '2') {
	flag = 1;
	break;
      }
    }

    if(flag == 1) {
      fprintf(file, "powergl_%s_%s *this = (powergl_%s_%s*)obj;\n", def_name, tmp_ptr, def_name, tmp_ptr);
      fprintf(file, "switch(index){\n");

      for(size_t j = 0; j < g_types[i].n_node; j++) {
	switch(*g_types[i].nodes[j].fields[2]) {
	case '2':
	  if(strcmp(g_types[i].nodes[j].fields[0], "char*") == 0) {
	    fprintf(file, "case %u: powergl_collada_parse_content(this->dom.nodes, index, value);\n", j);
	    fprintf(file, "this->n_content = strlen(value) + 1;\n");
	    fprintf(file, "this->content = powergl_resize(NULL, this->n_content, sizeof(char));\n");
	    fprintf(file, "strcpy(this->content, value);\nbreak;\n");
	  } else if(strcmp(g_types[i].nodes[j].fields[0], "char**") == 0) {
	    fprintf(file, "case %u: powergl_collada_parse_content(this->dom.nodes, index, value);\n", j);
	    fprintf(file, "this->content  = powergl_collada_parse_names(value, &this->n_content);\nbreak;\n");
	  } else if(strcmp(g_types[i].nodes[j].fields[0], "size_t*") == 0) {
	    fprintf(file, "case %u: powergl_collada_parse_content(this->dom.nodes, index, value);\n", j);
	    fprintf(file, "this->content  = powergl_collada_parse_uints(value, &this->n_content);\nbreak;\n");
	  } else if(strcmp(g_types[i].nodes[j].fields[0], "double*") == 0) {
	    fprintf(file, "case %u: powergl_collada_parse_content(this->dom.nodes, index, value);\n", j);
	    fprintf(file, "this->content  = powergl_collada_parse_floats(value, &this->n_content);\nbreak;\n");
	  }

	  break;
	}
      }

      fprintf(file, "}\n");
    }

    fprintf(file, "}\n");
    flag = 0;
    //////////////////////////////////////parse attribs
    fprintf(file, "void parse_attrib_%s_%s(void *obj, size_t index, const char *value){\n", def_name, tmp_ptr);

    for(size_t j = 0; j < g_types[i].n_node; j++) {
      if(*g_types[i].nodes[j].fields[2] == '1') {
	flag = 1;
	break;
      }
    }

    if(flag == 1) {
      fprintf(file, "powergl_%s_%s *this = (powergl_%s_%s*)obj;\n", def_name, tmp_ptr, def_name, tmp_ptr);
      fprintf(file, "switch(index){\n");

      for(size_t j = 0; j < g_types[i].n_node; j++) {
	switch(*g_types[i].nodes[j].fields[2]) {
	case '1':
	  if(strcmp(g_types[i].nodes[j].fields[0], "char*") == 0) {
	    fprintf(file, "case %u: powergl_collada_parse_attrib(this->dom.nodes, index, value);\n", j);
	    fprintf(file, "this->n_%s = strlen(value) + 1;\n", g_types[i].nodes[j].fields[1]);
	    fprintf(file, "this->c_%s = powergl_resize(NULL, this->n_%s, sizeof(char));\n", g_types[i].nodes[j].fields[1], g_types[i].nodes[j].fields[1]);
	    fprintf(file, "strcpy(this->c_%s, value);\nbreak;\n", g_types[i].nodes[j].fields[1]);
	  } else if(strcmp(g_types[i].nodes[j].fields[0], "size_t") == 0) {
	    fprintf(file, "case %u: powergl_collada_parse_attrib(this->dom.nodes, index, value);\n", j);
	    fprintf(file, "this->c_%s = strtoul( value, NULL, 10 );\nbreak;\n", g_types[i].nodes[j].fields[1]);
	  }

	  break;
	}
      }

      fprintf(file, "}\n");
    }

    fprintf(file, "}\n");
    flag = 0;
    //////////////////////////////////////add child
    fprintf(file, "void add_child_%s_%s(void *obj, size_t index, dom_connector *child){\n", def_name, tmp_ptr);
    fprintf(file, "powergl_%s_%s *this = (powergl_%s_%s*)obj;\n", def_name, tmp_ptr, def_name, tmp_ptr);
    fprintf(file, "switch(index){\n");

    for(size_t j = 0; j < g_types[i].n_node; j++) {
      if(*g_types[i].nodes[j].fields[0] == '0') {
	tmp_ptr2 = g_types[i].nodes[j].fields[1];
      } else {
	tmp_ptr2 = g_types[i].nodes[j].fields[0];
      }

      switch(*g_types[i].nodes[j].fields[2]) {
      case '0':
	fprintf(file, "case %u: powergl_collada_add_child(this->dom.nodes, index, child);\n", j);
	fprintf(file, "this->c_%s = powergl_resize(this->c_%s, ++this->n_%s, sizeof(powergl_%s_%s*));\n", g_types[i].nodes[j].fields[1], g_types[i].nodes[j].fields[1], g_types[i].nodes[j].fields[1], def_name, tmp_ptr2);
	fprintf(file, "this->c_%s[this->n_%s-1] = (powergl_%s_%s*)child;\nbreak;\n", g_types[i].nodes[j].fields[1], g_types[i].nodes[j].fields[1], def_name, tmp_ptr2);
	break;

      case '1':
      case '2':
      case '3':
	fprintf(file, "case %u: powergl_collada_add_child(this->dom.nodes, index, child);\nbreak;\n", j);
	break;

      default:
	assert(0);
      }
    }

    fprintf(file, "}\n}\n");
    ///////////////////////////////new
    fprintf(file, "void* new_%s_%s(void){\n", def_name, tmp_ptr);
    fprintf(file, "powergl_%s_%s *this = powergl_resize(NULL, 1, sizeof(powergl_%s_%s));\n", def_name, tmp_ptr, def_name, tmp_ptr);

    for(size_t j = 0; j < g_types[i].n_node; j++) {
      switch(*g_types[i].nodes[j].fields[2]) {
      case '0':
      case '1':
	if(strcmp(g_types[i].nodes[j].fields[0], "size_t") != 0) {
	  fprintf(file, "this->c_%s = NULL; this->n_%s = 0;\n", g_types[i].nodes[j].fields[1], g_types[i].nodes[j].fields[1]);
	} else {
	  fprintf(file, "this->c_%s = 0;\n", g_types[i].nodes[j].fields[1]);
	}

	break;

      case '2':
	fprintf(file, "this->content = NULL; this->n_content = 0;\n");
	break;

      case '3':
	fprintf(file, "this->r_%s = NULL;\n", g_types[i].nodes[j].fields[1]);
	break;

      default:
	assert(0);
      }
    }

    fprintf(file, "this->dom.nodes = NULL;\n");
    fprintf(file, "this->dom.map = %s[%u].map;\n", g_field_str, i);
    fprintf(file, "this->dom.n_map = %s[%u].n_map;\n", g_field_str, i);
    fprintf(file, "this->dom.add_child = add_child_%s_%s;\n", def_name, tmp_ptr);
    fprintf(file, "this->dom.set_ref = set_ref_%s_%s;\n", def_name, tmp_ptr);
    fprintf(file, "this->dom.parse_attrib = parse_attrib_%s_%s;\n", def_name, tmp_ptr);
    fprintf(file, "this->dom.parse_content = parse_content_%s_%s;\n", def_name, tmp_ptr);
    fprintf(file, "return this;\n}\n");
  }

  ///////////////////////////////////////////////////init types
  for(int i = 0; i < g_n_type; i++) {
    if(*g_types[i].fields[1] == '0') {
      tmp_ptr = g_types[i].fields[0];
    } else {
      tmp_ptr = g_types[i].fields[1];
    }

    fprintf(file, "static void support_%s_type_%s_%s(){\n", def_name, g_types[i].fields[2], tmp_ptr);
    fprintf(file, "char str[] = \"%s\";\n", tmp_ptr);
    fprintf(file, "size_t size = sizeof str / sizeof(char);\n");
    fprintf(file, "%s[%u].name = powergl_resize(NULL, size, sizeof(char));\n", g_field_str, i);
    fprintf(file, "memcpy(%s[%u].name, str, size * sizeof(char));\n", g_field_str, i);
    fprintf(file, "char str_parent[] = \"%s\";\n", g_types[i].fields[2]);
    fprintf(file, "size = sizeof str_parent / sizeof(char);\n");
    fprintf(file, "%s[%u].parent = powergl_resize(NULL, size, sizeof(char));\n", g_field_str, i);
    fprintf(file, "memcpy(%s[%u].parent, str_parent, size * sizeof(char));\n", g_field_str, i);

    if(g_types[i].n_node == 0) {
      for(size_t k = 0; k < g_n_type; k++) {
	if(strcmp(g_types[i].fields[0], g_types[k].fields[0]) == 0) {
	  g_types[i].nodes = g_types[k].nodes;
	  g_types[i].n_node = g_types[k].n_node;
	  i_ref_type = k;
	  break;
	}
      }

      fprintf(file, "%s[%u].get_instance = new_%s_%s;\n", g_field_str, i, def_name, g_types[i_ref_type].fields[0]);
      fprintf(file, "%s[%u].n_map = %s[%u].n_map;\n", g_field_str, i, g_field_str, i_ref_type);
      fprintf(file, "%s[%u].map = %s[%u].map;\n", g_field_str, i, g_field_str, i_ref_type);
      fprintf(file, "%s++;\n}\n", g_n_field_str);
    } else {
      fprintf(file, "%s[%u].get_instance = new_%s_%s;\n", g_field_str, i, def_name, tmp_ptr);
      fprintf(file, "map_dom_connector map[] = {");

      for(size_t j = 0; j < g_types[i].n_node; j++) {

	if(*g_types[i].nodes[j].fields[0] != '0') {
	  fprintf(file, "{ \"%s\",", g_types[i].nodes[j].fields[0]);
	} else {
	  fprintf(file, "{ NULL,");
	}
	
	if(*g_types[i].nodes[j].fields[1] != '0') {
	  fprintf(file, " \"%s\",", g_types[i].nodes[j].fields[1]);
	} else {
	  fprintf(file, " NULL,");
	}

	fprintf(file, " %c,", *g_types[i].nodes[j].fields[2]);

	if(*g_types[i].nodes[j].fields[3] != '0') {
	  fprintf(file, " \"%s\"},", g_types[i].nodes[j].fields[3]);
	} else {
	  fprintf(file, " NULL},");
	}
      }

      fprintf(file, "};\n");
      fprintf(file, "size = sizeof map / sizeof(map_dom_connector);\n");
      fprintf(file, "%s[%u].n_map = size;\n", g_field_str, i);
      fprintf(file, "%s[%u].map = powergl_resize(NULL, size, sizeof(map_dom_connector));\n", g_field_str, i);
      fprintf(file, "memcpy(%s[%s++].map, map, size * sizeof(map_dom_connector));\n}\n", g_field_str, g_n_field_str);
    }
  }

  fprintf(file, "void powergl_%s_init(){\n", def_name);

  for(int i = 0; i < g_n_type; i++) {
    if(*g_types[i].fields[1] == '0') {
      tmp_ptr = g_types[i].fields[0];
    } else {
      tmp_ptr = g_types[i].fields[1];
    }

    fprintf(file, "support_%s_type_%s_%s();\n", def_name, g_types[i].fields[2], tmp_ptr);
  }

  fprintf(file, "}\n");
  fclose(file);
}

void print_types() {
  printf("%u supported type---------------------\n", g_n_type);

  for(int i = 0; i < g_n_type; i++) {
    for(int k = 0; k < 3; k++) {
      printf("%s,", g_types[i].fields[k]);
    }

    for(int j = 0; j < g_types[i].n_node; j++) {
      printf("{");

      for(int k = 0; k < 3; k++) {
	printf("%s,", g_types[i].nodes[j].fields[k]);
      }
    }

    printf("\n");
  }
}

int main() {
  FILE *f;
  long fsize;
  char *string;
  size_t i;
  const char *filename = "text";
  /* init local */
  string = NULL;
  fsize = 0;
  f = NULL;
  /* read dae file */
  f = fopen(filename, "rb");

  if(!f) {
    fprintf(stderr, "import edilecek dosya bulunamadi\n");
    /* return NULL; */
  } else {
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);   //same as rewind(f);
    string = malloc(fsize + 1);
    assert(string);

    if(!fread(string, fsize, 1, f)) {
      fprintf(stderr, "dosya okunamadi\n");
      fclose(f);
    } else {
      fclose(f);
      string[fsize] = 0;
      //  puts(string);
    }
  }

  char buffer[20];
  buffer[19] = '\0';
  size_t subsize = 0;
  char status = 0;
  g_n_type = 0;
  size_t i_type = 0;
  size_t i_node = 0;
  size_t i_field = 0;
  // 0 = parsing fields
  // 1 = parsing node

  for(size_t i = 0; i < fsize; i++) {
    if(string[i] == ',' && status == 0) { // new elem found
      buffer[subsize] = '\0';
      g_types[i_type].fields[i_field] = powergl_resize(NULL, (subsize + 1) * sizeof(char));
      strcpy(g_types[i_type].fields[i_field], buffer);
      // printf("%s,",g_types[i_type].fields[i_field]);
      i_field++;
      subsize = 0;
    } else if(string[i] == '{' && status == 0) { // new node found
      buffer[subsize] = '\0';
      g_types[i_type].n_node = 0;
      g_types[i_type].nodes = powergl_resize(NULL, ++g_types[i_type].n_node * sizeof(node));
      // printf("{");
      i_field = 0;
      subsize = 0;
      status++;
    } else if(string[i] == ',' && status == 1) { // new node field found
      buffer[subsize] = '\0';
      g_types[i_type].nodes[i_node].fields[i_field] = powergl_resize(NULL, (subsize + 1) * sizeof(char));
      strcpy(g_types[i_type].nodes[i_node].fields[i_field], buffer);
      // printf("%s,",g_types[i_type].nodes[i_node].fields[i_field]);
      i_field++;
      subsize = 0;
    } else if(string[i] == '{' && status == 1) { // new node found
      buffer[subsize] = '\0';
      g_types[i_type].nodes = powergl_resize(g_types[i_type].nodes, ++g_types[i_type].n_node * sizeof(node));
      //printf("{");
      i_node++;
      i_field = 0;
      subsize = 0;
    } else if(string[i] == '\n') {
      //   printf("\n");
      status = 0;
      i_node = 0;
      i_field = 0;
      i_type++;
    } else {
      buffer[subsize++] = string[i];
    }
  }

  g_n_type = i_type + 1;
  char imp_h[] = "core.h";
  char imp_h_path[] = "../core/core.h";
  char imp_c[] = "core.c";
  char imp_c_path[] = "../core/core.c";
  char def_h_path[] = "../collada.h";
  char def_name[] = "collada_core";
  generate_def_header(def_h_path, "w", def_name);
  generate_imp_header(imp_h_path, def_h_path, def_name);
  generate_imp_source(imp_c_path, imp_h, def_name);
  //  print_types();
  return 0;
}
