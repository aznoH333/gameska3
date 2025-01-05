#ifndef ENEMY
#define ENEMY

#include "../../../gameLib/gamelibInclude.h"


enum EnemyType{
    ENEMY_TYPE_UNASIGNED,
    ENEMY_TYPE_GRUNT,
}; typedef enum EnemyType EnemyType ;


struct EnemyData{
    EnemyType type;
    void* enemyExtraData;
    void (*extraUpdate)(WorldObject* this, struct EnemyData* data, void* enemyExtraData);
};
typedef struct EnemyData EnemyData;


#define EnemyExtraUpdate void (*)(WorldObject*, EnemyData*, void*)
WorldObject* GenericEnemyInit(float x, float y, float w, float h, int spriteIndex, EnemyType enemyType, void (*extraUpdate)(WorldObject* this, struct EnemyData* data, void* enemyExtraData), void* extraData);




#endif