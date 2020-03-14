#ifndef _powergl_asset_collada_parse_utils_h
#define _powergl_asset_collada_parse_utils_h

#include <stddef.h>

size_t *powergl_collada_parse_uints(const char *string, size_t *value_size_ptr);
double *powergl_collada_parse_floats(const char *string, size_t *value_size_ptr);
#endif
