#include <stdio.h>
#include "maths.h"

// returns the normalized distance along a where an intersection with b occurs
// or -1 if there is no intersection
float segment_intersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2) {
    float h = (b2.x - b1.x) * (a1.y - a2.y) - (a1.x - a2.x) * (b2.y - b1.y);
    float t1 = ((b1.y - b2.y) * (a1.x - b1.x) + (b2.x - b1.x) * (a1.y - b1.y)) / h;
    float t2 = ((a1.y - a2.y) * (a1.x - b1.x) + (a2.x - a1.x) * (a1.y - b1.y)) / h; 

    float epsilon = 0.0001f;
    if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
    {
        return t1 - epsilon;
    }

    return -1.0f;
}

float lerp(float a, float b, float amt) {
    return (1 - amt) * a + amt * b;
}

glm::vec2 lerp(glm::vec2 a, glm::vec2 b, float amt) {
    return glm::vec2(lerp(a.x, b.x, amt), lerp(a.y, b.y, amt));
}
