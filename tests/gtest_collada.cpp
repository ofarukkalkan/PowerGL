#include <gtest/gtest.h>
#include <string>
extern "C" {
#define this this_ptr
#include "src/collada/importer.h"
#include "src/collada/collada.h"
#include "src/rendering/objectlibrary.h"
#include "src/math/mat4x4.h"
#undef this
}

static powergl_collada_core_COLLADA* load_dae(const char* file){
    std::string path = std::string(TEST_SRCDIR) + "/" + file;
    dom_connector* root = powergl_collada_parse(path.c_str());
    return (powergl_collada_core_COLLADA*)root;
}

TEST(ColladaImporter, BasicAttributes){
    auto* root = load_dae("vertexcolored_cube.dae");
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->n_library_cameras, 1u);
    auto* camlib = root->c_library_cameras[0];
    ASSERT_EQ(camlib->n_camera, 1u);
    auto* cam = camlib->c_camera[0];
    EXPECT_STREQ(cam->c_id, "Camera-camera");
    EXPECT_STREQ(cam->c_name, "Camera");
    auto* persp = cam->c_optics[0]->c_technique_common[0]->c_perspective[0];
    EXPECT_STREQ(persp->c_znear[0]->c_sid, "znear");
    EXPECT_NEAR(persp->c_znear[0]->content[0], 0.1, 1e-5);
}

TEST(ColladaImporter, ExportRoundTrip){
    auto* root = load_dae("vertexcolored_cube.dae");
    powergl_collada_export_dae_file(&root->dom, "cube_exported.dae");
    auto* exp = load_dae("cube_exported.dae");
    ASSERT_EQ(exp->n_library_cameras, root->n_library_cameras);
    EXPECT_STREQ(exp->c_library_cameras[0]->c_camera[0]->c_id,
                 root->c_library_cameras[0]->c_camera[0]->c_id);
    EXPECT_STREQ(exp->c_library_visual_scenes[0]->c_visual_scene[0]->c_node[2]->c_name,
                 root->c_library_visual_scenes[0]->c_visual_scene[0]->c_node[2]->c_name);
}

TEST(ObjectImport, AxisConversion){
    std::string path = std::string(TEST_SRCDIR) + "/vertexcolored_cube.dae";
    powergl_object_library *lib = powergl_object_library_build(path.c_str());
    ASSERT_NE(lib, nullptr);
    powergl_object *cube = powergl_object_library_find_object(lib, "Cube");
    ASSERT_NE(cube, nullptr);
    powergl_vec4 v = {cube->geometry.vertex[0].x,
                      cube->geometry.vertex[0].y,
                      cube->geometry.vertex[0].z,
                      1.0f};
    powergl_mat4 w = cube->transform.world;
    EXPECT_NEAR(w.c[0].x, 1.0f, 1e-5f);
    EXPECT_NEAR(w.c[1].y, 0.0f, 1e-5f);
    /* After converting from Z-up to Y-up with -Z forward, the Y and Z axes are
       swapped and Z points forward (positive Y in Blender becomes +Z). */
    EXPECT_NEAR(w.c[1].z, -1.0f, 1e-5f);
    EXPECT_NEAR(w.c[2].y, 1.0f, 1e-5f);
    EXPECT_NEAR(w.c[2].z, 0.0f, 1e-5f);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
