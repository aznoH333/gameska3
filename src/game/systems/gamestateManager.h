#ifndef GAME_STATE_MANAGER
#define GAME_STATE_MANAGER

enum GameState{
    GAME_STATE_GAME,
};
typedef enum GameState GameState;

void GameStateUpdate();
void GameStateSwitch(GameState newState);
void GameStateProgressLevel();


#endif