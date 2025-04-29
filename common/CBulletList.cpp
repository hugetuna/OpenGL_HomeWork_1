#include <cmath>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "CBulletList.h"
#include "initshader.h"


CBulletList::CBulletList() {
    head = nullptr;
}
//用暫時指標來刪除NODE
CBulletList::~CBulletList() {
    BulletNode* current = head;
    while (current) {
        BulletNode* temp = current;
        delete current->bullet;
        current = current->next;
        delete temp;
    }
}
void CBulletList::add(CBullet* bullet) {
    BulletNode* node = new BulletNode(bullet);
    node->next = head;
    head=node;
}
//用時間一次更新所有子彈的位置
void CBulletList::update(float deltaTime) {
    BulletNode* current;
    BulletNode* prev = nullptr;
    current = head;
    while (current != nullptr) {
        //更新並推動指針
        current->bullet->update(deltaTime);

        if (!current->bullet->isActive()) {
            //設置需刪除指標，並利用prev及current指標縫合
            BulletNode* toDelete = current;
            if (prev) {
                prev->next = current->next;
            }
            //第一個node就要刪除的情形
            else {
                head = current->next;
            }
            current = current->next;
            delete toDelete->bullet;
            delete toDelete;
            std::cout << "刪除子彈\n";
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}
//畫出所有子彈
void CBulletList::draw() {
    BulletNode* current;
    current = head;
    while (current != nullptr) {
        current->bullet->draw();
        current = current->next;
    }
}
