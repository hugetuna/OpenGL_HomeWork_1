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
//�μȮɫ��ШӧR��NODE
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
//�ήɶ��@����s�Ҧ��l�u����m
void CBulletList::update(float deltaTime) {
    BulletNode* current;
    BulletNode* prev = nullptr;
    current = head;
    while (current != nullptr) {
        //��s�ñ��ʫ��w
        current->bullet->update(deltaTime);

        if (!current->bullet->isActive()) {
            //�]�m�ݧR�����СA�çQ��prev��current�����_�X
            BulletNode* toDelete = current;
            if (prev) {
                prev->next = current->next;
            }
            //�Ĥ@��node�N�n�R��������
            else {
                head = current->next;
            }
            current = current->next;
            delete toDelete->bullet;
            delete toDelete;
            std::cout << "�R���l�u\n";
        }
        else {
            prev = current;
            current = current->next;
        }
    }
}
//�e�X�Ҧ��l�u
void CBulletList::draw() {
    BulletNode* current;
    current = head;
    while (current != nullptr) {
        current->bullet->draw();
        current = current->next;
    }
}
