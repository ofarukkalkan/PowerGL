#include <gtest/gtest.h>
extern "C" {
#include "src/math/intersect.h"
}

TEST(Intersect, RayTriangleBasic){
    powergl_vec3 mesh[3] = {
        {-1.0f, -1.0f, 0.0f},
        { 1.0f, -1.0f, 0.0f},
        { 0.0f,  1.0f, 0.0f}
    };
    powergl_mat4 mvp = powergl_mat4_ident();
    powergl_vec2 event = {50.0f, 50.0f};
    powergl_vec4 vp = {0.0f, 0.0f, 100.0f, 100.0f};
    powergl_vec3 out;
    int hit = powergl_intersect_ray_tri_mesh(mesh, 3, mvp, event, vp, &out, 0);
    ASSERT_EQ(hit, 1);
    EXPECT_NEAR(out.x, 0.25f, 1e-5f);
    EXPECT_NEAR(out.y, 0.5f, 1e-5f);
    EXPECT_NEAR(out.z, 1.0f, 1e-5f);
}

TEST(Intersect, CullBackface){
    powergl_vec3 mesh[3] = {
        {-1.0f, -1.0f, 0.0f},
        { 1.0f, -1.0f, 0.0f},
        { 0.0f,  1.0f, 0.0f}
    };
    powergl_mat4 mvp = powergl_mat4_ident();
    powergl_vec2 event = {50.0f, 50.0f};
    powergl_vec4 vp = {0.0f, 0.0f, 100.0f, 100.0f};
    powergl_vec3 out;
    int hit = powergl_intersect_ray_tri_mesh(mesh, 3, mvp, event, vp, &out, 1);
    ASSERT_EQ(hit, 0);
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
