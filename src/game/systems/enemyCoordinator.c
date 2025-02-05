#include "enemyCoordinator.h"
#include "math.h"
#include "gameLib/gamelibInclude.h"
#include "playerManager.h"
#include "terrainSystem.h"
#include <stdlib.h>
#include "game/entitiesInclude.h"
#include "game/systems/gamestateManager.h"



int aliveEnemies;
int spawnTimer = 0;
int difficulity = 1; // TODO : difficulity scaling
int enemiesKilled = 0;
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
    aliveEnemies++;
    
}


void EnemyCoordinatorUpdate(){
    spawnTimer++;

    bool isSpawning = enemiesKilled < 40 + (difficulity * 20);
    int enemyCountTarget = 35 + ((difficulity / 5) * 4);
    int nextSpawnTime = 30 - fmin(((difficulity / 10.0f) * 2), 30) + (60 * (aliveEnemies > enemyCountTarget));

    if (spawnTimer >= nextSpawnTime && isSpawning){
        spawnEnemy();
        spawnTimer = 0;
        debugMessage("enemies alive [%d]", aliveEnemies);
    }

    if (!isSpawning && aliveEnemies < 5){
        // go to next level
        GameStateProgressLevel();
    }
}


void EnemyCoordinatorKilledEnemy(){
    aliveEnemies--;
    enemiesKilled++;
}


void EnemyCoordinatorStartNewWave(){
    aliveEnemies = 0;
    spawnTimer = 0;
    enemiesKilled = 0;
    difficulity++;
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

