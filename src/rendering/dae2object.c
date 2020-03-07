#include "dae2object.h"

static const size_t powergl_vertex_offset = 0;
static const size_t powergl_normal_offset = 1;
static const size_t powergl_color_offset = 2;
static const size_t powergl_vertex_input_supported = 3;

static float to_radians( float degrees )
{
    return degrees * ( 3.141592f / 180.0f );
}

void powergl_build_geometry_triangle_index( powergl_rendering_geometry *geo, powergl_collada_core_triangles *triangles, powergl_collada_core_input_local_offset *vertex_input, powergl_collada_core_input_local_offset  *color_input, powergl_collada_core_input_local_offset  *normal_input )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    // how many triangles are there in _ imported file _
    size_t p_count = triangles->c_count;
    // offset values for each vertex attribute
    size_t vertex_offset = vertex_input->c_offset;
    size_t color_offset;
    size_t normal_offset;
    if ( color_input != NULL )
        {
            color_offset = color_input->c_offset;
        }
    else
        {
            fprintf(stderr, "no color input found \n" );
        }
    if ( normal_input != NULL )
        {
            normal_offset = normal_input->c_offset;
        }
    else
        {
            fprintf(stderr, "no normal input found \n" );
        }
    // vertex count 3 = triangle has 3 vertex
    size_t vertex_count = 3 * p_count;
    // total index count
    size_t n_index = vertex_count * powergl_vertex_input_supported;
    geo->index = powergl_resize( NULL, sizeof( GLuint ) * n_index );
    // get xml collada_type that contains index values
    powergl_collada_core_ListOfUInts  *p_arr = triangles->c_p[0];
    // each triangle has how many vertex attribute in _ imported file _
    size_t input_count = p_arr->n_content / ( 3 * p_count );
    for ( size_t l = 0; l < vertex_count; l++ )
        {
            // this index array is building vbo, ibo and cbo sources
            geo->index[ l * powergl_vertex_input_supported + powergl_vertex_offset ] = p_arr->content[ l * input_count  + vertex_offset ];
            if ( normal_input != NULL )
                {
                    geo->index[ l * powergl_vertex_input_supported + powergl_normal_offset ] = p_arr->content[ l * input_count  + normal_offset ];
                }
            if ( color_input != NULL )
                {
                    geo->index[ l * powergl_vertex_input_supported + powergl_color_offset ] = p_arr->content[ l * input_count  + color_offset ];
                }
#if DEBUG_OUTPUT
            printf( "%u %u %u ", geo->index[ l * powergl_vertex_input_supported +  powergl_vertex_offset ], geo->index[ l * powergl_vertex_input_supported + powergl_normal_offset], geo->index[ l * powergl_vertex_input_supported + powergl_color_offset] );
#endif
        } // copy indices from p collada_type for each vertex
    geo->index_flag = 1;
    geo->n_index = n_index;
}

void powergl_build_geometry_triangle_color( powergl_rendering_geometry *geo, powergl_collada_core_triangles  *triangles, powergl_collada_core_input_local_offset  *color_input )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    powergl_collada_core_source *src = color_input->r_source;
    powergl_collada_core_accessor *srcAcc = src->c_technique_common[0]->c_accessor[0];
    if ( srcAcc->r_float_array != NULL )
        {
            powergl_collada_core_float_array  *float_arr =  srcAcc->r_float_array;
            size_t stride = srcAcc->c_stride;
            if ( stride == 0 )
                stride = 1; // stride is must greater than 0 and default is 1
            // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid
            powergl_collada_core_param  **params = srcAcc->c_param;
            int offsets[3] = { -1, -1, -1};
            for ( int k = 0; k < srcAcc->n_param; k++ )
                {
                    if ( strlen( params[k]->c_name ) > 0 )
                        {
                            if ( strncmp( params[k]->c_name, "R", 1 ) == 0 )
                                {
                                    offsets[0] = k;
                                }
                            else if ( strncmp( params[k]->c_name, "G", 1 ) == 0 )
                                {
                                    offsets[1] = k;
                                }
                            else if ( strncmp( params[k]->c_name, "B", 1 ) == 0 )
                                {
                                    offsets[2] = k;
                                }
                        }
                }
            size_t p_count = triangles->c_count;
            size_t vertex_count = p_count * 3;
            geo->color = powergl_resize( NULL, sizeof( powergl_vec3 ) * vertex_count );
            for ( size_t i = 0; i < vertex_count ; i++ )
                {
                    size_t index = geo->index[ i * powergl_vertex_input_supported + powergl_color_offset ];
                    if ( offsets[ 0 ] > -1 )
                        geo->color[ i ].x = float_arr->content[ index * stride + offsets[0] ];
                    if ( offsets[ 1 ] > -1 )
                        geo->color[ i ].y = float_arr->content[ index * stride + offsets[1] ];
                    if ( offsets[ 2 ] > -1 )
                        geo->color[ i ].z = float_arr->content[ index * stride + offsets[2] ];
#if DEBUG_OUTPUT
                    powergl_printvec3( &geo->color[i] );
#endif
                }
            geo->color_flag = 1;
            geo->n_color = vertex_count;
        }
}

void powergl_build_geometry_triangle_normal( powergl_rendering_geometry *geo, powergl_collada_core_triangles  *triangles, powergl_collada_core_input_local_offset  *normal_input )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    powergl_collada_core_source *src = normal_input->r_source;
    powergl_collada_core_accessor *srcAcc = src->c_technique_common[0]->c_accessor[0];
    if ( srcAcc->r_float_array != NULL )
        {
            powergl_collada_core_float_array  *float_arr = srcAcc->r_float_array;
            size_t stride = srcAcc->c_stride;
            if ( stride == 0 )
                stride = 1; // stride is must greater than 0 and default is 1
            // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid
            powergl_collada_core_param  **params = srcAcc->c_param;
            int offsets[3] = { -1, -1, -1};
            for ( int k = 0; k < srcAcc->n_param; k++ )
                {
                    if ( strlen( params[k]->c_name ) > 0 )
                        {
                            if ( strncmp( params[k]->c_name, "X", 1 ) == 0 )
                                {
                                    offsets[0] = k;
                                }
                            else if ( strncmp( params[k]->c_name, "Y", 1 ) == 0 )
                                {
                                    offsets[1] = k;
                                }
                            else if ( strncmp( params[k]->c_name, "Z", 1 ) == 0 )
                                {
                                    offsets[2] = k;
                                }
                        }
                }
            size_t p_count = triangles->c_count;
            size_t vertex_count = p_count * 3;
            geo->normal = powergl_resize( NULL, sizeof( powergl_vec3 ) * vertex_count );
            for ( size_t i = 0; i < vertex_count ; i++ )
                {
                    size_t index = geo->index[ i * powergl_vertex_input_supported + powergl_normal_offset ];
                    if ( offsets[ 0 ] > -1 )
                        geo->normal[ i ].x = float_arr->content[ index * stride + offsets[0] ];
                    if ( offsets[ 1 ] > -1 )
                        geo->normal[ i ].y = float_arr->content[ index * stride + offsets[1] ];
                    if ( offsets[ 2 ] > -1 )
                        geo->normal[ i ].z = float_arr->content[ index * stride + offsets[2] ];
#if DEBUG_OUTPUT
                    powergl_printvec3( &geo->normal[i] );
#endif
                }
            geo->normal_flag = 1;
            geo->n_normal = vertex_count;
        }
}

void powergl_build_geometry_triangle_vertex( powergl_rendering_geometry *geo, powergl_collada_core_triangles  *triangles, powergl_collada_core_input_local_offset  *vertex_input )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    powergl_collada_core_vertices  *vertices = vertex_input->r_vertices;
    if ( vertices->n_input > 0 )
        {
            powergl_collada_core_input_local  *position_input = NULL;
            for ( size_t i = 0; i < vertices->n_input; i++ )
                {
                    if ( strcmp( vertices->c_input[i]->c_semantic, "POSITION" ) == 0 )
                        {
                            position_input = vertices->c_input[i];
                        }
                }
            if ( position_input != NULL )
                {
                    powergl_collada_core_source  *srcPos = position_input->r_source;
                    powergl_collada_core_accessor  *srcPosAcc = srcPos->c_technique_common[0]->c_accessor[0];
                    if ( srcPosAcc->r_float_array != NULL )
                        {
                            powergl_collada_core_float_array  *float_arr = srcPosAcc->r_float_array;
                            size_t stride = srcPosAcc->c_stride;
                            if ( stride == 0 )
                                stride = 1; // stride is must greater than 0 and default is 1
                            // if ( stride * count != ... ) // if stride * count is not equal to float_array or int_array collada_types count it is not valid
                            powergl_collada_core_param  **params = srcPosAcc->c_param;
                            int offsets[3] = { -1, -1, -1};
                            for ( int k = 0; k < srcPosAcc->n_param; k++ )
                                {
                                    if ( strlen( params[k]->c_name) > 0 )
                                        {
                                            if ( strncmp( params[k]->c_name, "X", 1 ) == 0 )
                                                {
                                                    offsets[0] = k;
                                                }
                                            else if ( strncmp( params[k]->c_name, "Y", 1 ) == 0 )
                                                {
                                                    offsets[1] = k;
                                                }
                                            else if ( strncmp( params[k]->c_name, "Z", 1 ) == 0 )
                                                {
                                                    offsets[2] = k;
                                                }
                                        } // if param has a name which is equal to X, Y or Z
                                } // count how many params has name attribute
                            size_t p_count = triangles->c_count;
                            size_t vertex_count = p_count * 3;
                            geo->vertex = powergl_resize( NULL, sizeof( powergl_vec3 ) * vertex_count );
                            for ( size_t i = 0; i < vertex_count ; i++ )
                                {
                                    size_t index = geo->index[ i * powergl_vertex_input_supported + powergl_vertex_offset ];
                                    if ( offsets[ 0 ] > -1 )
                                        geo->vertex[ i ].x = float_arr->content[ index * stride + offsets[0] ];
                                    if ( offsets[ 1 ] > -1 )
                                        geo->vertex[ i ].y = float_arr->content[ index * stride + offsets[1] ];
                                    if ( offsets[ 2 ] > -1 )
                                        geo->vertex[ i ].z = float_arr->content[ index * stride + offsets[2] ];
#if DEBUG_OUTPUT
                                    powergl_printvec3( &geo->vertex[i] );
#endif
                                }
                            geo->vertex_flag = 1;
                            geo->n_vertex = vertex_count;
                        } // if accessor has an array source which is not NULL and triangles has p collada_type which is not NULL
                } // if vertices collada_type has an input collada_type with POSITION semantic
        } // if vertices has an input
}

void powergl_build_geometry_triangle( powergl_rendering_geometry *geo, powergl_collada_core_triangles  *triangles )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    if ( triangles->n_input > 0 )
        {
            powergl_collada_core_input_local_offset  *vertex_input = NULL;
            powergl_collada_core_input_local_offset  *normal_input = NULL;
            powergl_collada_core_input_local_offset  *color_input = NULL;
            for ( size_t i = 0; i < triangles->n_input; i++ )
                {
                    if ( strcmp( triangles->c_input[i]->c_semantic, "VERTEX" ) == 0 )
                        {
                            vertex_input = triangles->c_input[i];
                        }
                    else if ( strcmp( triangles->c_input[i]->c_semantic, "NORMAL" ) == 0 )
                        {
                            normal_input = triangles->c_input[i];
                        }
                    else if ( strcmp( triangles->c_input[i]->c_semantic, "COLOR" ) == 0 )
                        {
                            color_input = triangles->c_input[i];
                        }
                }
            if ( vertex_input != NULL )
                {
                    powergl_build_geometry_triangle_index( geo, triangles, vertex_input, color_input, normal_input );
                    powergl_build_geometry_triangle_vertex( geo, triangles, vertex_input );
                    if ( color_input != NULL )
                        {
                            powergl_build_geometry_triangle_color( geo, triangles, color_input );
                        }
                    if ( normal_input != NULL )
                        {
                            powergl_build_geometry_triangle_normal( geo, triangles, normal_input );
                        }
                }
        } // if triangles collada_type has input collada_types
}

void powergl_build_geometry( powergl_collada_core_node  * node, powergl_rendering_object *obj )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    powergl_collada_core_geometry  *geo =  node->c_instance_geometry[0]->r_geometry;
    powergl_collada_core_mesh  *mesh = geo->c_mesh[0];
    obj->geometry = powergl_resize( NULL, sizeof(powergl_rendering_geometry*) * mesh->n_triangles );
    obj->n_geometry = mesh->n_triangles;
    for ( size_t i = 0; i <  mesh->n_triangles; i++ )
        {
            powergl_collada_core_triangles  *triangle = mesh->c_triangles[i];
            obj->geometry[i] = powergl_resize( NULL, sizeof(powergl_rendering_geometry) );
            powergl_rendering_geometry_create( obj->geometry[i] );
            powergl_build_geometry_triangle( obj->geometry[i], triangle );
        } // if mesh has triangle collada_type
}

void powergl_build_camera( powergl_collada_core_node  * node, powergl_rendering_object *obj )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    powergl_rendering_camera *cam = obj->camera;
    powergl_collada_core_camera  *cam_elem = node->c_instance_camera[0]->r_camera;
    powergl_collada_core_perspective  *pers = cam_elem->c_optics[0]->c_technique_common[0]->c_perspective[0];
    if ( pers != NULL )
        {
            cam->type = 'p';
            if(pers->c_xfov!=NULL) cam->xfov = to_radians( pers->c_xfov[0]->content[0] );
            if(pers->c_yfov!=NULL) cam->yfov = to_radians( pers->c_yfov[0]->content[0] );
            cam->znear = pers->c_znear[0]->content[0];
            cam->zfar = pers->c_zfar[0]->content[0];
            cam->aspect_ratio = pers->c_aspect_ratio[0]->content[0];
        }
    if ( node->n_matrix > 0 )
        {
            powergl_ident4x4( cam->view );
            cam->view_flag = 0;
            powergl_ident4x4( cam->projection );
            cam->projection_flag = 0;
            powergl_ident4x4( cam->vp );
            int result = powergl_inv4x4( ( float * ) &obj->matrix, ( float * ) &cam->view );
            if ( result == 1 )
                {
                    cam->view_flag = 1;
                }
            else
                {
                    powergl_ident4x4( cam->view );
                    powergl_vec3 eye = {0.0f, 0.0f, 4.0f};
                    powergl_vec3 target = {0.0f, 0.0f, 0.0f};
                    powergl_vec3 up = {0.0f, 1.0f, 0.0f};
                    powergl_lookat( cam->view, &eye, &target, &up );
                }
#if DEBUG_OUTPUT
            printf( "view transform\n" );
            powergl_print4x4( cam->view );
#endif
            if ( cam->type == 'p' )
                {
                    if ( pers->c_yfov != NULL )
                        {
                            powergl_perspectiveRH( cam->projection, cam->yfov, cam->aspect_ratio, cam->znear, cam->zfar );
                            cam->projection_flag = 1;
#if DEBUG_OUTPUT
                            printf( "[aspect_ratio = %f] [xfov = %f] [yfov = %f]  [znear = %f] [zfar= %f]\n", cam->aspect_ratio, cam->xfov, cam->yfov, cam->znear, cam->zfar );
#endif
                        }
                    else if ( pers->c_xfov != NULL )
                        {
                            cam->yfov = cam->xfov / cam->aspect_ratio;
                            powergl_perspectiveRH( cam->projection, cam->yfov, cam->aspect_ratio, cam->znear, cam->zfar );
                            cam->projection_flag = 1;
#if DEBUG_OUTPUT
                            printf( "[aspect_ratio = %f] [xfov = %f] [yfov = %f]  [znear = %f] [zfar= %f]\n", cam->aspect_ratio, cam->xfov, cam->yfov, cam->znear, cam->zfar );
#endif
                        }
                    else
                        {
                            powergl_perspectiveRH( cam->projection, 2.16f, 1.33f, 0.1f, 100.0f );
#if DEBUG_OUTPUT
                            printf( "defaults ! [aspect_ratio = %f] [xfov = %f] [yfov = %f]  [znear = %f] [zfar= %f]\n", 1.33f, 2.09f, 1.57f, 0.1f, 100.0f );
#endif
                            cam->projection_flag = 1;
                        }
#if DEBUG_OUTPUT
                    printf( "perspective projection transform\n" );
                    powergl_print4x4( cam->projection );
#endif
                }
        }
}

void powergl_build_light( powergl_collada_core_node * node, powergl_rendering_object *obj )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    //////////////////////////////////////////// color
    powergl_rendering_light *light = obj->light;
    powergl_collada_core_light *light_elem =  node->c_instance_light[0]->r_light;
    powergl_collada_core_light_technique_common  *tc = light_elem->c_technique_common[0];
    if ( tc != NULL && tc->c_directional != NULL )
        {
            powergl_collada_core_directional  *sun = tc->c_directional[0];
            if ( sun-> c_color != NULL)
                {
                    if ( sun->c_color[0]->content != NULL )
                        {
                            for ( size_t i = 0; i < 3; ++i)
                                {
                                    obj->light->color[i] = sun->c_color[0]->content[i];
                                }
                        }
                }
            else
                {
                    for ( size_t i = 0; i < 3; ++i)
                        {
                            obj->light->color[i] = 1.0f;
                        }
                }
#if DEBUG_OUTPUT
            printf("light color\n%g %g %g\n",obj->light->color[0],obj->light->color[1],obj->light->color[2]);
#endif
            obj->light->color_flag = 1;
            ////////////////////////////////////////// direction
            // set w = 0 to get infinite
            // default for collada directional light dir
            GLfloat v[4] = { 0.0f, 0.0f, -1.0f, 0.0f };
            GLfloat result[4];
#if DEBUG_OUTPUT
            printf("light transform matrix\n");
            powergl_print4x4(obj->matrix);
#endif
            powergl_transformvec4(v, obj->matrix, result);
#if DEBUG_OUTPUT
            printf("transformed light coord\n");
            for ( size_t i = 0; i < 4; i++ )
                {
                    printf("%g ",result[i]);
                }
            printf("\n");
#endif
            powergl_vec3 dir = {.x = result[0], .y = result[1], .z = result[2] };
            powergl_vec3 norm_dir;
            powergl_normvec3(&dir, &norm_dir);
            obj->light->dir[0] = norm_dir.x;
            obj->light->dir[1] = norm_dir.y;
            obj->light->dir[2] = norm_dir.z;
#if DEBUG_OUTPUT
            printf("normalized light dir\n%g %g %g\n",obj->light->dir[0],obj->light->dir[1],obj->light->dir[2]);
#endif
            obj->light->type = 'd';
            obj->light->dir_flag = 1;
        }
}

void powergl_build_transform( powergl_collada_core_node * node, powergl_rendering_object *obj )
{
#if DEBUG_OUTPUT
    printf( "%s\n", __func__ );
#endif
    powergl_collada_core_targetable_floats *matrix = node->c_matrix[0];
    for ( size_t i = 0; i < 4; i++ )
        {
            for ( size_t j = 0; j < 4; j++ )
                {
                    obj->matrix[i][j] = ( float ) matrix->content[i * 4 + j];
                }
        }
    powergl_trans4x4( obj->matrix );
#if DEBUG_OUTPUT
    powergl_print4x4( obj->matrix );
#endif
    obj->matrix_flag = 1;
}

void powergl_build_object( powergl_collada_core_node *node, powergl_rendering_object *obj)
{
    if ( node->c_id != NULL )
        {
            obj->id = powergl_resize(NULL, sizeof(char) * (strlen(node->c_id) + 1));
            strcpy(obj->id, node->c_id);
        }
    if ( node->n_matrix > 0 )
        {
            powergl_build_transform( node, obj );
        } // if node has transform
    if ( node->n_instance_geometry > 0 )
        {
            powergl_build_geometry( node, obj );
        } // if node has instance_geometry
    if ( node->n_instance_camera > 0 )
        {
            obj->camera = powergl_resize( NULL, sizeof( powergl_rendering_camera ) );
            powergl_rendering_camera_create( obj->camera );
            powergl_build_camera( node, obj );
        } // if node has instance_camera
    if ( node->n_instance_light > 0 )
        {
            obj->light = powergl_resize( NULL, sizeof( powergl_rendering_light ) );
            powergl_rendering_light_create( obj->light );
            powergl_build_light( node, obj );
        } // if node has instance_light
    /*
    if ( node->n_node > 0 ) {

      obj->children = powergl_resize( NULL, sizeof(powergl_rendering_object*) * node->n_node);
      obj->n_child = node->n_node;

      for ( size_t i = 0; i < node->n_node; i++ ) {

        obj->children[i] = powergl_resize( NULL, sizeof( powergl_rendering_object ) );
        powergl_rendering_object_create( obj->children[i], obj);

        powergl_build_object( node->c_node[i], obj->children[i]);
      }

    }
    */
}
