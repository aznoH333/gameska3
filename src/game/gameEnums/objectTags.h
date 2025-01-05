#ifndef OBJECT_TAGS
#define OBJECT_TAGS

enum ObjectTag{
    OBJECT_TAG_PLAYER = 1,
    OBJECT_TAG_PLAYER_PROJECTILE,
    OBJECT_TAG_ENEMY,
    OBJECT_TAG_ENEMY_PROJECTILE,
};
typedef enum ObjectTag ObjectTag;

#endif