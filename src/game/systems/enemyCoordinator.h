#ifndef ENEMY_COORDINATOR
#define ENEMY_COORDINATOR


#define GenericEnemySpawnFunction void (*spawnFunction)(float, float)

void EnemyCoordinatorUpdate();
void EnemyCoordinatorKilledEnemy();
void EnemyCoordinatorStartNewWave();
void EnemyCoordinatorRegisterEnemy(GenericEnemySpawnFunction); // TODO : more enemy stats
void EnemyCoordinatorInit();
void EnemyCoordinatorDispose();


#endif