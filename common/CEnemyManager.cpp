#include "CEnemyManager.h"
#include <iostream>
CEnemyManager::CEnemyManager(GLuint shaderID)
    : _shaderID(shaderID), _spawnTimer(0.0f), _spawnInterval(2.0f)  // 每兩秒生成一隻
{
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // 隨機種子
}

CEnemyManager::~CEnemyManager() {
    for (CEnemy* enemy : _enemys) {
        delete enemy;
    }
    if (_boss) {
        delete _boss;
        _boss = nullptr;
    }
    _enemys.clear();
}

void CEnemyManager::updateAllEnemy(float deltaTime, CBulletList& playerBullets, glm::vec3 playerPos) {
    _spawnTimer += deltaTime;
    if (_spawnTimer >= _spawnInterval) {
        spawnEnemy();
        _spawnTimer = 0.0f;
    }

    for (auto it = _enemys.begin(); it != _enemys.end(); ) {
        CEnemy* enemy = *it;
        enemy->update(deltaTime, playerPos);

        // 被子彈打到
        for (BulletNode* current = playerBullets.getHead(); current != nullptr; current = current->next) {
            if (current->bullet->isActive()) {
                float dist = glm::length(enemy->getPos() - current->bullet->getPosition());
                if (dist < enemy->getRadius()) {
                    enemy->takeDamage(1);
                    current->bullet->deactivate();
                }
            }
        }

        // 是否死亡
        if (enemy->isDead()) {
            delete enemy;
            it = _enemys.erase(it);
            _point++; // 擊殺數 +1
            //招喚boss
            if (_point >= 5 && !_bossAppeared) {
                _bossAppeared = true;
                _boss = new CBoss(_shaderID);
                _boss->setPos(glm::vec3(0.0f, 4.0f, 0.0f)); // 初始位置可調整
            }
        }
        else {
            //在這裡檢查readyToShoot
            if (enemy->readyToShoot()) {
                std::vector<CEnemyBullet*> bullet = enemy->shoot(playerPos);
                _EnemyBullets.add(bullet);
            }
            ++it;
        }
    }
    //boss獨立計算
    if (_bossAppeared && _boss) {
        _boss->update(deltaTime, playerPos);
        // 檢查玩家子彈擊中 Boss
        for (BulletNode* current = playerBullets.getHead(); current != nullptr; current = current->next) {
            if (current->bullet->isActive()) {
                float dist = glm::length(_boss->getPos() - current->bullet->getPosition());
                if (dist < _boss->getRadius()) {
                    _boss->takeDamage(1);
                    current->bullet->deactivate();
                }
            }
        }
        // Boss 是否死亡
        if (_boss->isDead()) {
            delete _boss;
            _boss = nullptr;
        }
        else {
            if (_boss->readyToShoot()) {
                std::vector<CEnemyBullet*> bossBullets = _boss->shoot(playerPos);
                _EnemyBullets.add(bossBullets);
            }
        }
    }
    _EnemyBullets.update(deltaTime);
    
}



void CEnemyManager::renderAllEnemy() {
    for (CEnemy* enemy : _enemys) {
        enemy->render();
    }
    if (_bossAppeared && _boss) {
        _boss->render();
    }
    _EnemyBullets.draw();
}

void CEnemyManager::spawnEnemy() {
    int type = std::rand() % 3;  // 0:Bat, 1:Slime, 2:Boxy
    CEnemy* newEnemy = nullptr;
    if (_enemys.size()<3)
    {
        switch (type) {
        case 0:
            newEnemy = new CEnemy_Bat(_shaderID);
            break;
        case 1:
            newEnemy = new CEnemy_Slime(_shaderID);
            break;
        case 2:
            newEnemy = new CEnemy_Boxy(_shaderID);
            break;
        }
    }
    if (newEnemy) {
        float x = -3.0f + static_cast<float>(rand()) / RAND_MAX * 6.0f;  // 在 -3 到 3 之間
        float y = static_cast<float>(std::rand() % 200 - 100) / 100.0f;//-1.0~1.0
        newEnemy->setPos(glm::vec3(x, 3, 0.0f));
        _enemys.push_back(newEnemy);
    }
}
