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

typedef struct {
    char *id;
    dom_connector *node;
} id_entry;

static id_entry *g_id_map;
static size_t g_n_id_map;


int powergl_collada_init_node(dom_connector *ptr, dom_connector *parent, const char *name, const char **attr, size_t nattr) {
    g_current_elem = ptr;
    ptr->name = powergl_resize(NULL, (strlen(name) + 1), sizeof(char));
    strcpy(ptr->name, name);
    /////////////
    //init parent's field
    /////
    char flag = 0;

    if(parent != NULL) {
        for(size_t i = 0; i < parent->n_map; ++i) {
            if(parent->map[i].node_type == 0 && strcmp(parent->map[i].name, name) == 0) {
                flag = 1;
                assert(parent->nodes);
                parent->add_child(parent, i, ptr);
                ptr->parent = parent;
            }
        }

        assert(flag); // eger parent icerisinde node lar mevcut ama bu node mevcut degilse
    }

    /////////////
    //init sub nodes
    /////
    ptr->nodes = powergl_resize(NULL, ptr->n_map, sizeof(arr_dom_connector));

    for(size_t i = 0; i < ptr->n_map; i++) {
        ptr->nodes[i].n_node = 0;
        ptr->nodes[i].nodes = NULL;

        switch(ptr->map[i].node_type) {
        case 1: {
            for(size_t j = 0; j < nattr / 2; j++) {
                if(strcmp(ptr->map[i].name, attr[j * 2]) == 0) {
                    dom_connector *newattr = powergl_resize(NULL, 1, sizeof(dom_connector));
                    newattr->parent = ptr;
                    newattr->name = powergl_resize(NULL, (strlen(attr[j * 2]) + 1), sizeof(char));
                    strcpy(newattr->name, attr[j * 2]);
                    ptr->add_child(ptr, i, newattr);
                    ptr->parse_attrib(ptr, i, attr[j * 2 + 1]);
                }
            }
        }
        break;

        case 2: {
            dom_connector *newcontent = powergl_resize(NULL, 1, sizeof(dom_connector));
            newcontent->parent = ptr;
            newcontent->name = powergl_resize(NULL, (strlen("content") + 1), sizeof(char));
            strcpy(newcontent->name, "content");
            ptr->add_child(ptr, i, newcontent);
            g_content_flag = 1;
            g_content_index = i;
            break;
        }

        case 3: {
            dom_connector *newref = powergl_resize(NULL, 1, sizeof(dom_connector));
            newref->parent = ptr;
	    
            newref->name = powergl_resize(NULL, (strlen(ptr->map[i].name) + 1), sizeof(char));
            strcpy(newref->name, ptr->map[i].name);

	    newref->base_type = powergl_resize(NULL, (strlen(ptr->map[i].base_type) + 1), sizeof(char));
            strcpy(newref->base_type, ptr->map[i].base_type);
	    
            ptr->add_child(ptr, i, newref);
            g_ref_content_flag = 1;
            g_ref_index = i;
            g_pending_references = powergl_resize(g_pending_references, ++g_n_pending_reference,  sizeof(dom_connector *));
            g_pending_references[g_n_pending_reference - 1] = newref;

            for(size_t j = 0; j < ptr->n_map; j++) {
                if(ptr->map[j].node_type == 1  &&  strcmp(ptr->map[j].name, ptr->map[g_ref_index].ref_src) == 0) {
                    ptr->nodes[g_ref_index].nodes[0]->value = powergl_resize(NULL, (strlen(ptr->nodes[j].nodes[0]->value) + 1), sizeof(char));
                    strcpy(ptr->nodes[g_ref_index].nodes[0]->value, ptr->nodes[j].nodes[0]->value);
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
    dom_connector *ptr = g_current_elem;
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
            for(size_t i = 0; i < ptr->n_map; i++) {
                if(ptr->map[i].node_type == 2  &&  strcmp(ptr->map[i].name, ptr->map[g_content_index].name) == 0) {
                    ptr->parse_content(ptr, g_content_index, g_content_buffer);
                    free(g_content_buffer);
                    g_content_buffer = NULL;
                    g_content_flag = 0;
                }
            }

            if(g_ref_content_flag == 1) {
                for(size_t j = 0; j < ptr->n_map; j++) {
                    if(ptr->map[j].node_type == 2  &&  strcmp(ptr->map[j].name, ptr->map[g_ref_index].ref_src) == 0) {
                        ptr->nodes[g_ref_index].nodes[0]->value = powergl_resize(NULL, (strlen(ptr->nodes[j].nodes[0]->value) + 1), sizeof(char));
                        strcpy(ptr->nodes[g_ref_index].nodes[0]->value, ptr->nodes[j].nodes[0]->value);
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

static const char *get_attrib_value(dom_connector *node, const char *name){
    for(size_t i = 0; i < node->n_map; ++i){
        if(node->map[i].node_type == 1 && strcmp(node->map[i].name, name) == 0 && node->nodes[i].n_node > 0){
            return node->nodes[i].nodes[0]->value;
        }
    }
    return NULL;
}

static void collect_ids(dom_connector *node){
    const char *id = get_attrib_value(node, "id");
    if(id){
        g_id_map = powergl_resize(g_id_map, ++g_n_id_map, sizeof(id_entry));
        g_id_map[g_n_id_map-1].id = (char*)id;
        g_id_map[g_n_id_map-1].node = node;
    }
    for(size_t i=0;i<node->n_map;++i){
        if(node->map[i].node_type == 0){
            for(size_t j=0;j<node->nodes[i].n_node;++j){
                collect_ids(node->nodes[i].nodes[j]);
            }
        }
    }
}

static dom_connector *find_id(const char *id){
    for(size_t i=0;i<g_n_id_map;++i){
        if(strcmp(g_id_map[i].id, id) == 0) return g_id_map[i].node;
    }
    return NULL;
}

static dom_connector *find_sid(dom_connector *node, const char *sid){
    const char *val = get_attrib_value(node, "sid");
    if(val && strcmp(val, sid) == 0) return node;
    for(size_t i=0;i<node->n_map;++i){
        if(node->map[i].node_type == 0){
            for(size_t j=0;j<node->nodes[i].n_node;++j){
                dom_connector *tmp = find_sid(node->nodes[i].nodes[j], sid);
                if(tmp) return tmp;
            }
        }
    }
    return NULL;
}

static dom_connector *resolve_sid_path(dom_connector *start, char **tokens, size_t count){
    dom_connector *cur = start;
    for(size_t i=0;i<count;++i){
        cur = find_sid(cur, tokens[i]);
        if(!cur) return NULL;
    }
    return cur;
}

static dom_connector *resolve_uri(const char *uri){
    char *copy = powergl_resize(NULL, strlen(uri)+1, sizeof(char));
    strcpy(copy, uri);
    char *tokens[32];
    size_t count=0;
    char *tok = strtok(copy, "/");
    while(tok && count < 32){
        tokens[count++] = tok;
        tok = strtok(NULL, "/");
    }
    dom_connector *node = NULL;
    size_t index=0;
    node = find_id(tokens[0]);
    if(node) index = 1; else { node = find_sid(g_root, tokens[0]); index = 1; }
    if(node) node = resolve_sid_path(node, &tokens[index], count-index);
    free(copy);
    return node;
}

static size_t resolve_pending_references(dom_connector *root){
    g_id_map = NULL;
    g_n_id_map = 0;
    collect_ids(root);
    size_t resolved = 0;
    for(size_t i=0;i<g_n_pending_reference;++i){
        dom_connector *ref = g_pending_references[i];
        if(!ref || !ref->value) continue;
        const char *uri = ref->value;
        if(uri[0]=='#') uri++;
        dom_connector *target = resolve_uri(uri);
        if(target){
            dom_connector *parent = ref->parent;
            for(size_t l=0;l<parent->n_map;++l){
                for(size_t m=0;m<parent->nodes[l].n_node;++m){
                    if(parent->nodes[l].nodes[m] == ref){
                        parent->set_ref(parent, l, target);
                        resolved++;
                        m=parent->nodes[l].n_node; l=parent->n_map;
                    }
                }
            }
        }
    }
    free(g_id_map); g_id_map=NULL; g_n_id_map=0;
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
                size_t resolved = resolve_pending_references(g_root);
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
