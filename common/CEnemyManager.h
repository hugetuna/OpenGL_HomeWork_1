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
    //敵人子彈集
    CEnemyBulletList& getBulletList() { return _EnemyBullets; }
private:
    std::vector<CEnemy*> _enemys;
    float _spawnTimer;
    float _spawnInterval;
    //敵人子彈集
    CEnemyBulletList _EnemyBullets;
    GLuint _shaderID;
};
