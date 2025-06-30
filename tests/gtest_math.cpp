#include <gtest/gtest.h>
extern "C" {
#include "src/math/mat4x4.h"
#include "src/math/vec3.h"
}

TEST(Mat4, InverseOfScale) {
    powergl_mat4 m = powergl_mat4_ident();
    powergl_vec3 scalev = {2.0f, 3.0f, 4.0f};
    m = powergl_mat4_scale(m, scalev);

    powergl_mat4 inv = powergl_mat4_inv(m);
    powergl_mat4 prod = powergl_mat4_mul(m, inv);
    powergl_mat4 ident = powergl_mat4_ident();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            ASSERT_NEAR(prod.c[j].r[i], ident.c[j].r[i], 1e-5f);
        }
    }
}

TEST(Vec3, BasicOps) {
    powergl_vec3 v = {1.0f, 2.0f, 3.0f};
    powergl_float_print("val", 1.0f);
    powergl_vec3_print("vec3", v);
    powergl_vec4_print("vec4", (powergl_vec4){1.0f,2.0f,3.0f,4.0f});
    double arr[3] = {1.0, 2.0, 3.0};
    powergl_vec3 cpy;
    powergl_vec3_copy(&cpy, arr, 3);
    EXPECT_FLOAT_EQ(cpy.x, v.x);
    EXPECT_FLOAT_EQ(cpy.y, v.y);
    EXPECT_FLOAT_EQ(cpy.z, v.z);

    powergl_vec3 ones = powergl_vec3_ones();
    powergl_vec3 zeros = powergl_vec3_zeros();
    EXPECT_FLOAT_EQ(powergl_vec3_dot(ones, ones), 3.0f);
    EXPECT_FLOAT_EQ(powergl_vec3_dot(zeros, zeros), 0.0f);

    EXPECT_NEAR(powergl_vec3_len(v), sqrtf(14.0f), 1e-5f);

    powergl_vec3 cross = powergl_vec3_cross(ones, v);
    EXPECT_FLOAT_EQ(cross.x, 1.0f);
    EXPECT_FLOAT_EQ(cross.y, -2.0f);
    EXPECT_FLOAT_EQ(cross.z, 1.0f);

    powergl_vec3 mulv = powergl_vec3_mulv(v, ones);
    EXPECT_FLOAT_EQ(mulv.x, v.x);
    EXPECT_FLOAT_EQ(mulv.y, v.y);
    EXPECT_FLOAT_EQ(mulv.z, v.z);

    powergl_vec3 muls = powergl_vec3_muls(v, 2.0f);
    EXPECT_FLOAT_EQ(muls.x, 2.0f);
    EXPECT_FLOAT_EQ(muls.y, 4.0f);
    EXPECT_FLOAT_EQ(muls.z, 6.0f);

    powergl_vec3 add = powergl_vec3_add(v, ones);
    EXPECT_FLOAT_EQ(add.x, 2.0f);
    EXPECT_FLOAT_EQ(add.y, 3.0f);
    EXPECT_FLOAT_EQ(add.z, 4.0f);

    powergl_vec3 sub = powergl_vec3_sub(v, ones);
    EXPECT_FLOAT_EQ(sub.x, 0.0f);
    EXPECT_FLOAT_EQ(sub.y, 1.0f);
    EXPECT_FLOAT_EQ(sub.z, 2.0f);

    powergl_vec3 div = powergl_vec3_div(v, ones);
    EXPECT_FLOAT_EQ(div.x, v.x);
    EXPECT_FLOAT_EQ(div.y, v.y);
    EXPECT_FLOAT_EQ(div.z, v.z);

    powergl_vec3 norm = powergl_vec3_norm(v);
    float len = powergl_vec3_len(norm);
    EXPECT_NEAR(len, 1.0f, 1e-5f);

    EXPECT_NEAR(powergl_float_to_radians(180.0f), 3.141592f, 1e-5f);
}

TEST(Vec4, BasicOps) {
    powergl_vec4 ones = powergl_vec4_ones();
    powergl_vec4 zeros = powergl_vec4_zeros();
    double arr[4] = {1.0, 2.0, 3.0, 4.0};
    powergl_vec4 cpy;
    powergl_vec4_copy(&cpy, arr, 4);
    EXPECT_FLOAT_EQ(cpy.x, 1.0f);
    EXPECT_FLOAT_EQ(cpy.y, 2.0f);
    EXPECT_FLOAT_EQ(cpy.z, 3.0f);
    EXPECT_FLOAT_EQ(cpy.w, 4.0f);

    powergl_vec4 mulv = powergl_vec4_mulv(cpy, ones);
    EXPECT_FLOAT_EQ(mulv.w, 4.0f);

    powergl_vec4 muls = powergl_vec4_muls(cpy, 2.0f);
    EXPECT_FLOAT_EQ(muls.w, 8.0f);

    powergl_vec4 add = powergl_vec4_add(cpy, zeros);
    EXPECT_FLOAT_EQ(add.z, 3.0f);

    powergl_vec4 sub = powergl_vec4_sub(cpy, zeros);
    EXPECT_FLOAT_EQ(sub.y, 2.0f);

    powergl_vec4 div = powergl_vec4_div(cpy, ones);
    EXPECT_FLOAT_EQ(div.x, 1.0f);
}

TEST(Mat4, Operations) {
    powergl_mat4 tmp = powergl_mat4_ident();
    powergl_mat4_print("ident", tmp);
    double arr[16];
    for(int i=0;i<16;i++) arr[i]=i+1;
    powergl_mat4_copy(&tmp, arr, 16, 1);
    powergl_mat4 zero = powergl_mat4_zero();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_FLOAT_EQ(zero.c[j].r[i], 0.0f);
        }
    }

    powergl_mat4 ident = powergl_mat4_ident();
    powergl_mat4 scaled = powergl_mat4_scale(ident, powergl_vec3_ones());
    powergl_mat4 mul = powergl_mat4_mul(ident, scaled);
    EXPECT_FLOAT_EQ(mul.c[0].r[0], 1.0f);

    powergl_mat4 transposed = powergl_mat4_transpose(mul);
    EXPECT_FLOAT_EQ(transposed.c[0].r[0], mul.c[0].r[0]);

    powergl_mat4 translated = powergl_mat4_translate(ident, (powergl_vec3){1.0f, 2.0f, 3.0f});
    EXPECT_FLOAT_EQ(translated.c[3].r[0], 1.0f);
    EXPECT_FLOAT_EQ(translated.c[3].r[1], 2.0f);
    EXPECT_FLOAT_EQ(translated.c[3].r[2], 3.0f);

    powergl_mat4 scaled2 = powergl_mat4_scale(ident, (powergl_vec3){2.0f, 3.0f, 4.0f});
    EXPECT_FLOAT_EQ(scaled2.c[1].r[1], 3.0f);

    powergl_mat4 rotated = powergl_mat4_rot(ident, (float)M_PI/2.0f, (powergl_vec3){0.0f, 0.0f, 1.0f});
    EXPECT_NEAR(rotated.c[0].r[0], cosf((float)M_PI/2.0f), 1e-5f);

    powergl_mat4 look = powergl_mat4_lookatRH((powergl_vec3){0,0,0}, (powergl_vec3){0,0,-1}, (powergl_vec3){0,1,0});
    EXPECT_FLOAT_EQ(look.c[2].r[2], 1.0f);

    powergl_mat4 persp = powergl_mat4_perspectiveRH((float)M_PI/2.0f, 1.0f, 0.1f, 100.0f);
    EXPECT_LT(persp.c[2].r[2], 0.0f);

    powergl_vec4 v = {1.0f, 2.0f, 3.0f, 1.0f};
    powergl_vec4 vt = powergl_vec4_trans(v, ident);
    EXPECT_FLOAT_EQ(vt.y, 2.0f);
}

TEST(Mat4, UnprojectRoundTrip) {
    powergl_mat4 ident = powergl_mat4_ident();
    powergl_mat4 mvp = powergl_mat4_scale(ident, (powergl_vec3){2.0f,2.0f,2.0f});
    powergl_vec4 vp = {0.0f,0.0f,100.0f,100.0f};
    powergl_vec3 orig = {1.0f,2.0f,3.0f};
    powergl_vec4 win4 = {orig.x, orig.y, orig.z, 1.0f};
    powergl_vec4 proj = powergl_vec4_trans(win4, mvp);
    proj.x = ((proj.x / proj.w) + 1.0f) * 0.5f * vp.z + vp.x;
    proj.y = ((proj.y / proj.w) + 1.0f) * 0.5f * vp.w + vp.y;
    powergl_vec3 screen = {proj.x, proj.y, proj.z/proj.w};
    powergl_vec3 res = powergl_unproject(screen, mvp, vp);
    EXPECT_NEAR(res.x, orig.x, 1e-4f);
    EXPECT_NEAR(res.y, orig.y, 1e-4f);
    EXPECT_NEAR(res.z, orig.z, 1e-4f);
}

TEST(Mat4, Decompose) {
    powergl_vec3 loc = {1.0f, 2.0f, 3.0f};
    powergl_vec3 sca = {2.0f, 3.0f, 4.0f};
    powergl_vec3 rot = {(float)M_PI/6.0f, (float)M_PI/4.0f, (float)M_PI/3.0f};

    powergl_mat4 m = powergl_mat4_ident();
    m = powergl_mat4_scale(m, sca);
    m = powergl_mat4_rot(m, rot.z, (powergl_vec3){0.0f,0.0f,1.0f});
    m = powergl_mat4_rot(m, rot.y, (powergl_vec3){0.0f,1.0f,0.0f});
    m = powergl_mat4_rot(m, rot.x, (powergl_vec3){1.0f,0.0f,0.0f});
    m = powergl_mat4_translate(m, loc);

    powergl_vec3 dloc, drot, dsca;
    powergl_decompose_matrix(m, &dloc, &drot, &dsca);

    EXPECT_NEAR(dloc.x, loc.x, 1e-4f);
    EXPECT_NEAR(dloc.y, loc.y, 1e-4f);
    EXPECT_NEAR(dloc.z, loc.z, 1e-4f);

    EXPECT_NEAR(dsca.x, sca.x, 1e-4f);
    EXPECT_NEAR(dsca.y, sca.y, 1e-4f);
    EXPECT_NEAR(dsca.z, sca.z, 1e-4f);

    EXPECT_NEAR(drot.x, rot.x, 1e-4f);
    EXPECT_NEAR(drot.y, rot.y, 1e-4f);
    EXPECT_NEAR(drot.z, rot.z, 1e-4f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
