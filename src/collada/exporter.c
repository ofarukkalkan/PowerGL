#include "exporter.h"

void powergl_collada_export_dae_file( dom_connector *root, const char *file_name )
{
    FILE *file = fopen( file_name, "w" );
    if ( !file )
        {
            fprintf(stderr, "File opening failed" );
            return;
        }
    fprintf( file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>" );
    powergl_collada_print_element( file, root, 0 );
    fprintf( file, "\n" );
    fclose( file );
}
