#pragma once

#include <vector>
#include <cstdlib>     // for rand()
#include <ctime>       // for time()
#include "CEnemy.h"
#include "CBoss.h"
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
    int _point = 0;//分數
    bool _bossAppeared = false;//CBoss是否出現過
    CBoss* _boss = nullptr; // 前向宣告 CBoss 類別，與普通敵人分開
    //敵人生成計時器
    float _spawnTimer;
    float _spawnInterval;
    //敵人子彈集
    CEnemyBulletList _EnemyBullets;
    GLuint _shaderID;
};
