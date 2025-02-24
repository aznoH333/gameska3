#ifndef ENEMY_COORDINATOR
#define ENEMY_COORDINATOR

#include "stdbool.h"


#define GenericEnemySpawnFunction void (*spawnFunction)(float, float)

void EnemyCoordinatorUpdate();
void EnemyCoordinatorKilledEnemy();
void EnemyCoordinatorStartNewWave(bool spawnEnemies);
void EnemyCoordinatorRegisterEnemy(GenericEnemySpawnFunction); // TODO : more enemy stats
void EnemyCoordinatorInit();
void EnemyCoordinatorDispose();


#endif