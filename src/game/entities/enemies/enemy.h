#ifndef ENEMY
#define ENEMY

#include "../../../gameLib/gamelibInclude.h"


enum EnemyType{
    ENEMY_TYPE_UNASIGNED,
    ENEMY_TYPE_GRUNT,
}; typedef enum EnemyType EnemyType ;


struct EnemyData{
    EnemyType type;
    float health;
    float maxHealth;
    int stunTimer;
    float stunPushX;
    float stunPushY;
    float xMovement;
    float yMovement;
    void* enemyExtraData;
    void (*extraUpdate)(WorldObject* this, struct EnemyData* data, void* enemyExtraData);
    void (*extraCollisionUpdate)(WorldObject* this, struct EnemyData* data, void* enemyExtraData, WorldObject* other);
};
typedef struct EnemyData EnemyData;


#define EnemyExtraUpdate void (*)(WorldObject*, EnemyData*, void*)
#define EnemyExtraCollisionUpdate void (*)(WorldObject*, EnemyData*, void*, WorldObject*)
WorldObject* GenericEnemyInit(
    float x, 
    float y, 
    float w, 
    float h, 
    int spriteIndex, 
    float health, 
    EnemyType enemyType, 
    void (*extraUpdate)(WorldObject* this, struct EnemyData* data, void* enemyExtraData), 
    void (*extraCollisionUpdate)(WorldObject* this, struct EnemyData* data, void* enemyExtraData, WorldObject* other),
    void* extraData
);




#endif