#ifndef INTERACTION_TYPES
#define INTERACTION_TYPES

enum InteractionType{
    INTERACTION_DEAL_DAMAGE,
    INTERACTION_PUSH,
    INTERACTION_GIVE_MONEY,
};
typedef enum InteractionType InteractionType;

struct ObjectInteractionPushData{
    float pushX;
    float pushY;
    float pushValue;
};
typedef struct ObjectInteractionPushData ObjectInteractionPushData;

#endif