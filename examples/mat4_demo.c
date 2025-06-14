#include <stdio.h>
#include "src/math/mat4x4.h"
#include "src/math/vec3.h"

static void print_matrix(const char *name, powergl_mat4 m) {
    printf("%s:\n", name);
    for (int i=0; i<4; ++i) {
        printf("[ %f %f %f %f ]\n", m.c[0].r[i], m.c[1].r[i], m.c[2].r[i], m.c[3].r[i]);
    }
}

int main() {
    powergl_mat4 ident = powergl_mat4_ident();
    powergl_vec3 scalev = {2.0f, 3.0f, 4.0f};
    powergl_mat4 scaled = powergl_mat4_scale(ident, scalev);
    print_matrix("scaled", scaled);

    powergl_mat4 b = powergl_mat4_ident();
    b.c[0].r[3] = 2.0f; // modify w of column 0
    powergl_mat4 prod = powergl_mat4_mul(ident, b);
    print_matrix("mul", prod);

    powergl_mat4 inv = powergl_mat4_inv(scaled);
    print_matrix("inverse", inv);
    return 0;
}
