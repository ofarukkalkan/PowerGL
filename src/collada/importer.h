#ifndef _powergl_asset_collada_importer_h
#define _powergl_asset_collada_importer_h

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "collada.h"
#include "core/core.h"


dom_connector *powergl_collada_parse(const char *filename);
void powergl_collada_export_dae_file(dom_connector *root, const char *file_name);
void powergl_collada_delete_dom_connector(dom_connector *elemm, size_t depth);

#endif
