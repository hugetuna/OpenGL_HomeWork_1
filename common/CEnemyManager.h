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
    //�ĤH�l�u��
    CEnemyBulletList& getBulletList() { return _EnemyBullets; }
private:
    std::vector<CEnemy*> _enemys;
    int _point = 0;//����
    bool _bossAppeared = false;//CBoss�O�_�X�{�L
    CBoss* _boss = nullptr; // �e�V�ŧi CBoss ���O�A�P���q�ĤH���}
    //�ĤH�ͦ��p�ɾ�
    float _spawnTimer;
    float _spawnInterval;
    //�ĤH�l�u��
    CEnemyBulletList _EnemyBullets;
    GLuint _shaderID;
};
