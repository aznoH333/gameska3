#ifndef ENEMY_GRUNT
#define ENEMY_GRUNT


struct EnemyGruntData{
    float collisionPushForceX;
    float collisionPushForceY;
};typedef struct EnemyGruntData EnemyGruntData ;


void InitEnemyGrunt(float x, float y);

#endif