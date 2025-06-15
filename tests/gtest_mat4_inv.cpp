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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
