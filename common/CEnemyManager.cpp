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
        enemy->update(deltaTime);

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
        }
        else {
            //在這裡檢查readyToShoot
            if (enemy->readyToShoot()) {
                CEnemyBullet* bullet = enemy->shoot(playerPos);
                _EnemyBullets.add(bullet);
            }
            ++it;
        }
    }
    _EnemyBullets.update(deltaTime);
    
}



void CEnemyManager::renderAllEnemy() {
    for (CEnemy* enemy : _enemys) {
        enemy->render();
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
