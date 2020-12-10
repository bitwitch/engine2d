#include "swordsman.h"
#include "maths.h"

void update_swordsman(Swordsman *sman) {
    //sman->position = lerp(sman->position, sman->target, 0.01);
    //sman->position = lerp(sman->position, sman->target, 0.01);
    if (sman->position.x < 1100)
        sman->position.x += 0.3;
}
