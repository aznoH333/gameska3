#include "enemyCoordinator.h"
#include "math.h"
#include "gameLib/gamelibInclude.h"
#include "playerManager.h"
#include "terrainSystem.h"
#include <stdlib.h>
#include "game/entitiesInclude.h"



int aliveEnemies;
int spawnTimer = 0;
int difficulity = 1; // TODO : difficulity scaling
Vector* enemyStorage = UNDEFINED;
#define ENEMY_SPAWN_DIST 360.0f


struct EnemyStorage {
    GenericEnemySpawnFunction;
};
typedef struct EnemyStorage EnemyStorage;


void spawnEnemy(){
    // pick coordinates
    WorldObject* player = PlayerManagerGetPlayer();

    if (player == UNDEFINED){
        return;
    }


    bool isSpawnValid = false;
    int spawnX;
    int spawnY;

    do {

        float randomDirection = randomFloatRange(0, PI*2);
        spawnX = player->x + cos(randomDirection) * ENEMY_SPAWN_DIST;
        spawnY = player->y + sin(randomDirection) * ENEMY_SPAWN_DIST;
        isSpawnValid = true;

        if (TerrainCheckCollisions(spawnX, spawnY, 32, 32)){
            isSpawnValid = false;
        }
    }while(!isSpawnValid);


    // select enemy to spawn
    // TODO : this
    EnemyStorage* enemyToSpawn = VectorGet(enemyStorage, 0);


    // spawn enemy
    enemyToSpawn->spawnFunction(spawnX, spawnY);
    
}


void EnemyCoordinatorUpdate(){
    spawnTimer++;

    int enemyCountTarget = 35 + ((difficulity / 5) * 4);
    int nextSpawnTime = 60 - fmin(((difficulity / 10.0f) * 2), 30) + (30 * (aliveEnemies > enemyCountTarget));

    if (spawnTimer >= nextSpawnTime){
        spawnEnemy();
        spawnTimer = 0;
    }
}


void EnemyCoordinatorKilledEnemy(){
    aliveEnemies--;
}


void EnemyCoordinatorStartNewWave(){
    aliveEnemies = 0;
    spawnTimer = 0;
}


void EnemyCoordinatorInit(){
    enemyStorage = VectorInit();
    // TODO : move enemy registry somewhere else or come up with a better system
    EnemyCoordinatorRegisterEnemy(&InitEnemyGrunt);
}


void EnemyCoordinatorDispose(){
    VectorFreeValues(enemyStorage);
}


void EnemyCoordinatorRegisterEnemy(void (*spawnFunction)(float, float)){
    EnemyStorage* storage = malloc(sizeof(EnemyStorage));    
    storage->spawnFunction = spawnFunction;
    VectorAdd(enemyStorage, storage);
}

