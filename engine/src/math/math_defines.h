#ifndef MATH_DEFINES_H
#define MATH_DEFINES_H

#include "idl_defines.h"

// TODO: improve this generic vector.

// n components vector of anytype.
template <u32 L, typename T>
struct vec {
    vec() {
        for (u32 i = 0; i < L; i++) {
            elements[i] = 0;
        }
    }
    f32 elements[L];
    inline T& operator[](u32 index) {
        return elements[index];
    }
    inline const T& operator[](u32 index) const {
        return elements[index];
    }
};

// 2 components vector of 32-bit floating-point numbers.
union vec2 {
    f32 elements[2];  // An array of x, y.
    struct {
        union {
            f32 x, r;  // The first elements.
        };
        union {
            f32 y, g;  // The second elements.
        };
    };
};

// 3 components vector of 32-bit floating-point numbers.
union vec3 {
    f32 elements[3];  // An array of x, y, z.
    struct {
        union {
            f32 x, r;  // The first component.
        };
        union {
            f32 y, g;  // The second component.
        };
        union {
            f32 z, b;  // The third component.
        };
    };
};

// 4 components vector of 32-bit floating-point numbers.
union vec4 {
    f32 elements[4];  // An array of x, y, z, w.
    struct {
        union {
            f32 x, r;  // The first elements.
        };
        union {
            f32 y, g;  // The second elements.
        };
        union {
            f32 z, b;  // The third elements.
        };
        union {
            f32 w, a;  // The fourth elements.
        };
    };
};

// Ensure all vector types are of the correct size.
STATIC_ASSERT(sizeof(vec2) == 8, "Expected vec2 to be 8 byte.");
STATIC_ASSERT(sizeof(vec3) == 12, "Expected vec3 to be 12 byte.");
STATIC_ASSERT(sizeof(vec4) == 16, "Expected vec4 to be 16 byte.");

// 2 components vector of 32-bit unsigned integer numbers.
union vec2i {
    i32 elements[2];  // An array of x, y.
    struct {
        union {
            i32 x, r;  // The first elements.
        };
        union {
            i32 y, g;  // The second elements.
        };
    };
};

// 3 components vector of 32-bit unsigned integer numbers.
union vec3i {
    i32 elements[3];  // An array of x, y, z.
    struct {
        union {
            i32 x, r;  // The first component.
        };
        union {
            i32 y, g;  // The second component.
        };
        union {
            i32 z, b;  // The third component.
        };
    };
};

// 4 components vector of 32-bit unsigned integer numbers.
union vec4i {
    i32 elements[4];  // An array of x, y, z, w.
    struct {
        union {
            i32 x, r;  // The first elements.
        };
        union {
            i32 y, g;  // The second elements.
        };
        union {
            i32 z, b;  // The third elements.
        };
        union {
            i32 w, a;  // The fourth elements.
        };
    };
};

// Ensure all vector types are of the correct size.
STATIC_ASSERT(sizeof(vec2i) == 8, "Expected vec2 to be 8 byte.");
STATIC_ASSERT(sizeof(vec3i) == 12, "Expected vec3 to be 12 byte.");
STATIC_ASSERT(sizeof(vec4i) == 16, "Expected vec4 to be 16 byte.");

// 2 components vector of 32-bit signed integer numbers.
union vec2u {
    u32 elements[2];  // An array of x, y.
    struct {
        union {
            u32 x, r;  // The first elements.
        };
        union {
            u32 y, g;  // The second elements.
        };
    };
};

// 3 components vector of 32-bit signed integer numbers.
union vec3u {
    u32 elements[3];  // An array of x, y, z.
    struct {
        union {
            u32 x, r;  // The first component.
        };
        union {
            u32 y, g;  // The second component.
        };
        union {
            u32 z, b;  // The third component.
        };
    };
};

// 4 components vector of 32-bit signed integer numbers.
union vec4u {
    u32 elements[4];  // An array of x, y, z, w.
    struct {
        union {
            u32 x, r;  // The first elements.
        };
        union {
            u32 y, g;  // The second elements.
        };
        union {
            u32 z, b;  // The third elements.
        };
        union {
            u32 w, a;  // The fourth elements.
        };
    };
};

// Ensure all vector types are of the correct size.
STATIC_ASSERT(sizeof(vec2u) == 8, "Expected vec2 to be 8 byte.");
STATIC_ASSERT(sizeof(vec3u) == 12, "Expected vec3 to be 12 byte.");
STATIC_ASSERT(sizeof(vec4u) == 16, "Expected vec4 to be 16 byte.");

#endif