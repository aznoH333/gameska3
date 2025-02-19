#ifndef GUN 
#define GUN 


struct Gun{
    unsigned int ammoCount;
    unsigned int maxAmmo;

    unsigned int reloadTimer;
    unsigned int reloadSpeed;

    float damage;
    unsigned int bulletsPerShot;
    float accuracy;

    unsigned int fireRate;
    int fireCooldown;
    const char* sprite;
}; typedef struct Gun Gun;

Gun GunInit(const char* sprite, unsigned int ammoCount, unsigned int fireRate, float damage, float accuracy, unsigned int bulletsPerShot, unsigned int reloadSpeed);


#endif