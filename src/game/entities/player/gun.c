#include "gun.h"

Gun GunInit(
    const char* sprite, 
    unsigned int ammoCount, 
    unsigned int fireRate, 
    float damage, 
    float accuracy, 
    unsigned int bulletsPerShot, 
    unsigned int reloadSpeed){


    Gun output = {
        ammoCount,
        ammoCount,
        0,
        reloadSpeed,
        damage,
        bulletsPerShot,
        accuracy,
        fireRate,
        0,
        sprite
    };


    return output;
}
