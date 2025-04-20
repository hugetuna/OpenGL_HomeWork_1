// CBulletList.h
#pragma once
#include <glm/glm.hpp>
#include "CBullet.h"

struct BulletNode {
    CBullet* bullet;
    BulletNode* next;

    BulletNode(CBullet* b) : bullet(b), next(nullptr) {}
};
class CBulletList {
private:
    BulletNode* head;
public:
    CBulletList();
    ~CBulletList();
    void add(CBullet* bullet);
    void update(float deltaTime);
    void draw();
    CBulletList(const CBulletList&) = delete;
    CBulletList& operator=(const CBulletList&) = delete;
};