#pragma once

#include <vector>
#include <cstdlib>     // for rand()
#include <ctime>       // for time()
#include "CEnemy.h"
#include "CEnemy_Bat.h"
#include "CEnemy_Slime.h"
#include "CEnemy_Boxy.h"
#include "CBulletList.h"
#include "CEnemyBulletList.h"
class CEnemyManager {
public:
    CEnemyManager(GLuint shaderID);
    ~CEnemyManager();

    void updateAllEnemy(float deltaTime, CBulletList& playerBullet,glm::vec3 playerPos);
    void renderAllEnemy();
    void spawnEnemy();

private:
    std::vector<CEnemy*> _enemys;
    float _spawnTimer;
    float _spawnInterval;
    //¼Ä¤H¤l¼u¶°
    CEnemyBulletList _EnemyBullets;
    GLuint _shaderID;
};
