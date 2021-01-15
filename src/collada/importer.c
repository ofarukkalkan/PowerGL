#include <errno.h>
#include <string.h>
#include <expat.h>

#include "importer.h"
#include "exporter.h"

#define DEBUG_OUTPUT 1

/* static globals */
dom_connector *g_root;
static size_t g_current_depth;
static int g_undefined_element_flag;
static const char *g_current_elem_tag;
static dom_connector *g_current_elem;
static dom_connector **g_pending_references;
static size_t g_n_pending_reference;
static int g_parser_status; // 0 : elemstart , 1 : chardata , 2 : elemend
static char *g_content_buffer;
static char g_content_flag;
static size_t g_content_index;
static char g_ref_content_flag;
static size_t g_ref_index;


int powergl_collada_init_node(dom_connector *this, dom_connector *parent, const char *name, const char **attr, size_t nattr) {
    g_current_elem = this;
    this->name = powergl_resize(NULL, (strlen(name) + 1), sizeof(char));
    strcpy(this->name, name);
    /////////////
    //init parent's field
    /////
    char flag = 0;

    if(parent != NULL) {
        for(size_t i = 0; i < parent->n_map; ++i) {
            if(parent->map[i].node_type == 0 && strcmp(parent->map[i].name, name) == 0) {
                flag = 1;
                assert(parent->nodes);
                parent->add_child(parent, i, this);
                this->parent = parent;
            }
        }

        assert(flag); // eger parent icerisinde node lar mevcut ama bu node mevcut degilse
    }

    /////////////
    //init sub nodes
    /////
    this->nodes = powergl_resize(NULL, this->n_map, sizeof(arr_dom_connector));

    for(size_t i = 0; i < this->n_map; i++) {
        this->nodes[i].n_node = 0;
        this->nodes[i].nodes = NULL;

        switch(this->map[i].node_type) {
        case 1: {
            for(size_t j = 0; j < nattr / 2; j++) {
                if(strcmp(this->map[i].name, attr[j * 2]) == 0) {
                    dom_connector *newattr = powergl_resize(NULL, 1, sizeof(dom_connector));
                    newattr->parent = this;
                    newattr->name = powergl_resize(NULL, (strlen(attr[j * 2]) + 1), sizeof(char));
                    strcpy(newattr->name, attr[j * 2]);
                    this->add_child(this, i, newattr);
                    this->parse_attrib(this, i, attr[j * 2 + 1]);
                }
            }
        }
        break;

        case 2: {
            dom_connector *newcontent = powergl_resize(NULL, 1, sizeof(dom_connector));
            newcontent->parent = this;
            newcontent->name = powergl_resize(NULL, (strlen("content") + 1), sizeof(char));
            strcpy(newcontent->name, "content");
            this->add_child(this, i, newcontent);
            g_content_flag = 1;
            g_content_index = i;
            break;
        }

        case 3: {
            dom_connector *newref = powergl_resize(NULL, 1, sizeof(dom_connector));
            newref->parent = this;
	    
            newref->name = powergl_resize(NULL, (strlen(this->map[i].name) + 1), sizeof(char));
            strcpy(newref->name, this->map[i].name);

	    newref->base_type = powergl_resize(NULL, (strlen(this->map[i].base_type) + 1), sizeof(char));
            strcpy(newref->base_type, this->map[i].base_type);
	    
            this->add_child(this, i, newref);
            g_ref_content_flag = 1;
            g_ref_index = i;
            g_pending_references = powergl_resize(g_pending_references, ++g_n_pending_reference,  sizeof(dom_connector *));
            g_pending_references[g_n_pending_reference - 1] = newref;

            for(size_t j = 0; j < this->n_map; j++) {
                if(this->map[j].node_type == 1  &&  strcmp(this->map[j].name, this->map[g_ref_index].ref_src) == 0) {
                    this->nodes[g_ref_index].nodes[0]->value = powergl_resize(NULL, (strlen(this->nodes[j].nodes[0]->value) + 1), sizeof(char));
                    strcpy(this->nodes[g_ref_index].nodes[0]->value, this->nodes[j].nodes[0]->value);
                    g_ref_content_flag = 0;
                }
            }
        }
        }
    }

    return 0;
}

static void elemend(void *userdata, const char *elem) {
    g_parser_status = 2;
    dom_connector *this = g_current_elem;
    dom_connector *parent = g_current_elem->parent;

    if(parent == NULL && strcmp(elem, "COLLADA") == 0) {
        g_undefined_element_flag = 0;
#if DEBUG_OUTPUT
        printf("%s\n",  g_current_elem->name);
#endif
        g_current_depth--;
        return;
    } else if(parent != NULL) {
        g_undefined_element_flag = powergl_collada_core_check_type(elem, parent->name);
    }

    if(g_undefined_element_flag > -1) {
        if(g_content_flag == 1) {
            for(size_t i = 0; i < this->n_map; i++) {
                if(this->map[i].node_type == 2  &&  strcmp(this->map[i].name, this->map[g_content_index].name) == 0) {
                    this->parse_content(this, g_content_index, g_content_buffer);
                    free(g_content_buffer);
                    g_content_buffer = NULL;
                    g_content_flag = 0;
                }
            }

            if(g_ref_content_flag == 1) {
                for(size_t j = 0; j < this->n_map; j++) {
                    if(this->map[j].node_type == 2  &&  strcmp(this->map[j].name, this->map[g_ref_index].ref_src) == 0) {
                        this->nodes[g_ref_index].nodes[0]->value = powergl_resize(NULL, (strlen(this->nodes[j].nodes[0]->value) + 1), sizeof(char));
                        strcpy(this->nodes[g_ref_index].nodes[0]->value, this->nodes[j].nodes[0]->value);
                        g_ref_content_flag = 0;
                    }
                }
            }
        }

#if DEBUG_OUTPUT
        printf("old g_current_elem = %s\n", g_current_elem->name);
#endif
        g_current_elem = g_current_elem->parent;
#if DEBUG_OUTPUT
        printf("new g_current_elem = %s\n", g_current_elem->name);
#endif
    }

    g_current_depth--;
}



static void chardata(void *userdata, const XML_Char *string, int len) {
    if(g_undefined_element_flag == -1) {
        return;
    }

    // bu fonksiyonda string komple geldigi icin parse edilirken kontroller eklenecek !
    if(g_content_flag == 1) {
        if(g_parser_status == 1) {    // eger onceki asamada chardata calistiysa onceki ile burdaki string i birlestir
            g_content_buffer = powergl_resize(g_content_buffer, (strlen(g_content_buffer) + len + 1), sizeof(char));
            strncat(g_content_buffer, string, len);
        } else {
            g_content_buffer = powergl_resize(NULL, (len + 1),  sizeof(char));
            strncpy(g_content_buffer, string, len);
        }

#if DEBUG_OUTPUT

        for(size_t tab_count = 0; tab_count < g_current_depth; ++tab_count) {
            printf("  ");
        }

        printf("%.*s\n", len, string);
#endif
    }

    g_parser_status = 1;
}

static void elemstart(void *userdata, const char *elem, const char **attr) {
    g_current_elem_tag = elem;
    g_parser_status = 0;
    g_undefined_element_flag = -1;
    size_t nattr = XML_GetSpecifiedAttributeCount((XML_Parser) userdata);
    dom_connector *parent = g_current_elem;
    dom_connector *inst;

    if(parent != NULL) {
        inst = powergl_collada_core_get_instance(elem, parent->name);
    } else if(strcmp(elem, "COLLADA") == 0) {
        inst = powergl_collada_core_get_instance(elem, "COLLADA");
        inst->parent = NULL;
        g_root = inst;
    }

    if(inst != NULL) {
        g_undefined_element_flag = powergl_collada_init_node(inst, parent, elem, attr, nattr);
    }

#if DEBUG_OUTPUT

    if(g_undefined_element_flag == -1) {
        fprintf(stderr, "%s element is not defined\n", g_current_elem_tag);
    } else {
        fprintf(stdout, "init current elem= %s\n", g_current_elem_tag);
    }

#endif
    g_current_depth++;
}
/*
static int resolve_refs( dom_connector *root, int n_resolved ) {
  size_t resolved;
  for(size_t i=0; i<g_n_pending_reference; i++){
    printf("pending ref -> name = %s\t value = %s\n", g_pending_references[i]->name, g_pending_references[i]->value );

  }

  return resolvd;
}
*/
static size_t resolve_refs(dom_connector *root, int n_resolved) {
    size_t resolved = 0;

    for(size_t i = 0; i < root->n_map; ++i) {
        if(n_resolved + resolved == g_n_pending_reference) {
            return resolved;
        } else {
            if(root->map[i].node_type == 0) {
                for(size_t j = 0; j < root->nodes[i].n_node; j++) {
                    resolved += resolve_refs(root->nodes[i].nodes[j], n_resolved + resolved);
                }
            }
        }
    }

    if(n_resolved + resolved == g_n_pending_reference) {
      return n_resolved + resolved;
    } else {
      
      for(size_t i = 0; i < g_n_pending_reference; i++) {
	
	if(g_pending_references[i]->value[0] == '#') {
	  // URI fragment Addressing
	  for(size_t j = 0; j < root->n_map; j++) {

	    if(root->map[j].node_type == 1) { // if current node is attrib 

	      for(size_t k = 0; k  < root->nodes[j].n_node; k++) {
		// normally attribs has only 1 child so we use the first child.

		if(strcmp("id", root->nodes[j].nodes[k]->name) == 0) {
		  
		  if(strcmp((g_pending_references[i]->value + sizeof(char)), root->nodes[j].nodes[k]->value) == 0) {
		    // '+ sizeof(char)' is used to skip '#' character
		    
		    if(strcmp(g_pending_references[i]->base_type, root->name) == 0) {
		      // turleri kontrol et. cunku id ler uyusmasina ragmen yanlis referans kullanilmis olabilir
		      
		      dom_connector *parent = g_pending_references[i]->parent;
		      
		      // burada referansa sahip olan elementin set_ref fonksiyonu cagriliyor. neden direk ref uzerinden yapilmamasi ise implementastondan kaynakli.
		      // sadece element turlerinin fonksyionlari var
		      // attribute, content ve ref turlerinin kendine ait fonksyionlari yok
		      
		      int resolve_flag = 0;
		      
		      for(size_t l = 0; l < parent->n_map; l++) {

			

			if(parent->map[l].node_type == 3 && strcmp(parent->map[l].base_type, g_pending_references[i]->base_type) == 0) {

			  
			  parent->set_ref(parent, l, root);
			  
#if DEBUG_OUTPUT
			  printf("\n[ref type ptr][%s\t%s\t%p] == \n[src type ptr][%s\t%s\t%p] -> ref resolved\n",
				 g_pending_references[i]->value, g_pending_references[i]->name,  g_pending_references[i]->ref,
				 root->nodes[j].nodes[k]->value, root->name, root);
#endif
			  
			  resolve_flag = 1;
			  
			} else {
#if DEBUG_OUTPUT
			  printf("\n[ref type ptr][%s\t%s\t%p] == \n[src type ptr][%s\t%s\t%p] -> ref unresolved, parent->map[l].base_type != g_pending_references[i]->name\n",
				 g_pending_references[i]->value, g_pending_references[i]->name, g_pending_references[i]->ref,
				 root->nodes[j].nodes[k]->value, root->name, root);
#endif
			}
		      }

		      
		      if(resolve_flag == 1){
			return 1 + resolved;
		      }

		    } else {
#if DEBUG_OUTPUT
		      printf("\n[ref type ptr][%s\t%s\t%p] == \n[src type ptr][%s\t%s\t%p] -> ref unresolved, root->name != g_pending_references[i]->name\n",
			     g_pending_references[i]->value, g_pending_references[i]->name,  g_pending_references[i]->ref,
			     root->nodes[j].nodes[k]->value, root->name, root);
#endif
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }

    return resolved;
}

dom_connector *powergl_collada_parse(const char *filename) {
    XML_Parser p;
    FILE *f;
    size_t fsize;
    char *string;
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
            /* puts(string); */
            /* init globals */
	    g_current_elem = NULL;
            g_current_depth = 0;
	    g_parser_status = 0;
            g_pending_references = NULL;
            g_n_pending_reference = 0;
	    g_current_elem_tag = NULL;
	    g_content_index = 0;
	    g_ref_index = 0;

	    // TODO : we need to be sure here we have enough supported element type to parse file, to do so pre-check all types in dae file
	    // when powergl_collada_core_init is called it inits all core types and increments supported type counter so we can check it if we did init

	    int type_index = powergl_collada_core_check_type("COLLADA", "COLLADA");
	    if(type_index < 0){
	      powergl_collada_core_init();
	    }

            
            /* printf("\n-------------PARSING DOCUMENT\n"); */
            /* create parser and parse */
            p = XML_ParserCreate(NULL);
            assert(p);
            XML_UseParserAsHandlerArg(p);
            XML_SetElementHandler(p, elemstart, elemend);
            XML_SetCharacterDataHandler(p, chardata);

            if(!XML_Parse(p, string, fsize, -1)) {
                fprintf(stderr, "Parse error at line %lu:\n%s\n", XML_GetCurrentLineNumber(p), XML_ErrorString(XML_GetErrorCode(p)));
            } else {
#if DEBUG_OUTPUT
                printf("\n\n\n\n");
                printf("\n-------------EXPORTING DOCUMENT\n");
                printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
                powergl_collada_print_element(stdout, g_root, 0);
                powergl_collada_export_dae_file(g_root, "exported.dae");
                printf("\n\n\n\n");
                printf("\n-----------------RESOLVING REFERENCES\n");
                printf("pending refs = %lu\n", g_n_pending_reference);
#endif
                size_t resolved = resolve_refs(g_root, 0);
#if DEBUG_OUTPUT
                printf("\nresolved refs = %lu", resolved);
                printf("\n\n\n\n");
#endif
            }

            /* cleaning */
            free(g_pending_references);
            g_pending_references = NULL;
            XML_ParserFree(p);
            p = NULL;
            free(string);
            string = NULL;
        }
    }

    return g_root;
}

#undef DEBUG_OUTPUT
