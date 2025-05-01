#pragma once
#include <vector>
#include "CEnemyBullet.h"

struct EnemyBulletNode {
    CEnemyBullet* bullet;
    EnemyBulletNode* next;

    EnemyBulletNode(CEnemyBullet* b) : bullet(b), next(nullptr) {}
};

class CEnemyBulletList {
public:
    CEnemyBulletList();
    ~CEnemyBulletList();

    void add(std::vector<CEnemyBullet*>& bullets);
    void update(float deltaTime);
    void draw();
    EnemyBulletNode* getHead() const { return head; }
    CEnemyBulletList(const CEnemyBulletList&) = delete;
    CEnemyBulletList& operator=(const CEnemyBulletList&) = delete;
private:
    EnemyBulletNode* head;
};
