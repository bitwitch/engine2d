#pragma once


 // TODO(shaw): remove dependency on glm
#include "glm_subset.h"

// returns true if the two line segments intersect and false otherwise
// if the line segments intersect, the out parameter "intersection" will be 
// filled with the intersection point
bool test_intersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2, 
                    glm::vec2 *intersection);


// returns the normalized distance along the line segement start->end where an
// intersection with line segment p1->p2 occurs 
// or in other words, the percentage along the line segment from start to stop
// at which point p is located.
float segment_percentage(glm::vec2 start, glm::vec2 stop, glm::vec2 p);


float segment_intersect(glm::vec2 a1, glm::vec2 a2, glm::vec2 b1, glm::vec2 b2);

////
//// Vector2
////
//union Vector2 {
    //struct {
        //float x,y;
    //};
    //struct {
        //float u,v;
    //};
//};

//inline Vector2 
//make_vector2(float x, float y) {
    //Vector2 result;
    //result.x = x;
    //result.y = y;
    //return result;
//}

//inline Vector2 
//operator + (Vector2 a, Vector2 b) {
    //return make_vector2(a.x + b.x, a.y + b.y);
//}

//inline Vector2 
//operator - (Vector2 a, Vector2 b) {
    //return make_vector2(a.x - b.x, a.y - b.y);
//}


////
//// Vector3
////
//union Vector3 {
    //struct {
        //float x,y,z;
    //};
    //struct {
        //float r,g,b;
    //};
//};

//inline Vector3 
//make_vector3(float x, float y, float z) {
    //Vector3 result;
    //result.x = x;
    //result.y = y;
    //result.z = z;
    //return result;
//}


////
//// Matrix 4
////  



