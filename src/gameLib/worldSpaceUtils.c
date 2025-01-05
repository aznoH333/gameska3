#include "worldSpaceUtils.h"
#include "math.h"


float directionTowards(float startX, float startY, float targetX, float targetY){
    return atan2(targetY - startY, targetX - startX);
}


float squaresCollide(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2){
    return 
        x1 + w1 > x2 && x2 + w2 > x1 &&
        y1 + h1 > y2 && y2 + h2 > y1;
}
