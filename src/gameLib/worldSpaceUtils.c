#include "worldSpaceUtils.h"
#include "math.h"


float directionTowards(float startX, float startY, float targetX, float targetY){
    return atan2(targetY - startY, targetX - startX);
}
