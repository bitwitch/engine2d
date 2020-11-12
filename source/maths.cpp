#include <stdio.h>
#include "maths.h"


bool test_intersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2, 
                    glm::vec2 *intersection) 
{

    // handle paralell vertical lines
    if (a1.x == a2.x) {
        if (b1.x == b2.x) {
            if (a1.x != b1.x) return false;

            if (std::fmin(a1.y, a2.y) > std::fmax(b1.y, b2.y) ||
                std::fmax(a1.y, a2.y) < std::fmin(b1.y, b2.y)) 
            {
                return false;
            }

            intersection->x = a1.x; 
            intersection->y = a2.y; // they actually intersect a bunch of places, but....
            return true;
        }
    }
    
    float intersect_x, intersect_y;

    // handle a single vertical line (avoid division by zero)
    if (a1.x == a2.x) {
        float slope_b = (b2.y - b1.y) / (b2.x - b1.x);
        float intercept_b = b1.y - slope_b * b1.x;
        intersect_x = a1.x; 
        intersect_y = slope_b * intersect_x + intercept_b;
    } else if (b1.x == b2.x) {
        float slope_a = (a2.y - a1.y) / (a2.x - a1.x);
        float intercept_a = a1.y - slope_a * a1.x;
        intersect_x = b1.x;
        intersect_y = slope_a * intersect_x + intercept_a;
    } else {
        float slope_a = (a2.y - a1.y) / (a2.x - a1.x);
        float slope_b = (b2.y - b1.y) / (b2.x - b1.x);
        float intercept_a = a1.y - slope_a * a1.x;
        float intercept_b = b1.y - slope_b * b1.x;
        intersect_x = (intercept_b - intercept_a) / (slope_a - slope_b);
        intersect_y = slope_a * intersect_x + intercept_a;
    }

    // is intersect point on line segment a 
    if (intersect_x < std::fmin(a1.x, a2.x) || intersect_x > std::fmax(a1.x, a2.x)) 
        return false;
    if (intersect_y < std::fmin(a1.y, a2.y) || intersect_y > std::fmax(a1.y, a2.y)) 
        return false;

    // is intersect point on line segment b
    if (intersect_x < std::fmin(b1.x, b2.x) || intersect_x > std::fmax(b1.x, b2.x)) 
        return false;
    if (intersect_y < std::fmin(b1.y, b2.y) || intersect_y > std::fmax(b1.y, b2.y)) 
        return false;

    intersection->x = intersect_x;
    intersection->y = intersect_y;
    return true;
}


float segment_percentage(glm::vec2 start, glm::vec2 stop, glm::vec2 p) {
    float a,b; 

    a = abs(stop.x - start.x);
    b = abs(stop.y - start.y);
    float total_length = sqrt(a*a + b*b);

    a = abs(p.x - start.x);
    b = abs(p.y - start.y);
    float start_to_p_length = sqrt(a*a + b*b);

    float epsilon = 0.0001f; // make sure player moves outside of wall
    return std::fmax(0.0f, (start_to_p_length / total_length) - epsilon);
}


