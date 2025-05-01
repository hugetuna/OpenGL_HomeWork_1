#include "CEnemyBulletList.h"
#include <iostream>

CEnemyBulletList::CEnemyBulletList() {
    head = nullptr;
}

CEnemyBulletList::~CEnemyBulletList() {
    EnemyBulletNode* current = head;
    while (current) {
        EnemyBulletNode* temp = current;
        delete current->bullet;
        current = current->next;
        delete temp;
    }
}

void CEnemyBulletList::add(std::vector<CEnemyBullet*>& bullets) {
    /*if (bullet) {
        std::cout << "新增一顆敵人子彈！ 位置: ("
            << bullet->getPosition().x << ", "
            << bullet->getPosition().y << ", "
            << bullet->getPosition().z << ")\n";
    }*/
    for (CEnemyBullet* bullet : bullets) {
        EnemyBulletNode* node = new EnemyBulletNode(bullet);
        node->next = head;
        head = node;
    }
    
}

void CEnemyBulletList::update(float deltaTime) {
    EnemyBulletNode* current = head;
    EnemyBulletNode* prev = nullptr;

    while (current) {
        current->bullet->update(deltaTime);

        if (!current->bullet->isActive()) {
            EnemyBulletNode* toDelete = current;
            if (prev) {
                prev->next = current->next;
            }
            else {
                head = current->next;
            }
            current = current->next;
            delete toDelete->bullet;
            delete toDelete;
            std::cout << "刪除敵人子彈\n";
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}

void CEnemyBulletList::draw() {
    EnemyBulletNode* current = head;
    while (current != nullptr) {
        current->bullet->draw();
        current = current->next;
    }
}

