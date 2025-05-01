#include "CEnemy_Slime.h"

//建構時必須記憶使用的shader
CEnemy_Slime::CEnemy_Slime(GLuint shaderID) : CEnemy(shaderID) {
	_pShape = new CEnemyShape_Slime(shaderID);
	_pShape->setupVertexAttributesAtOnce();
	_pShape->setShaderIDAtOnce();
    _hp = 4;
    _attackInterval = 3;
    _attackTimer = 1;
	_moveSpeed = 0.8f;
    _bAttackWay = true;
}
CEnemy_Slime::~CEnemy_Slime() {
	
}
void CEnemy_Slime::update(float dt, glm::vec3 playerPos) {
	glm::vec3 dir = glm::normalize(playerPos - _position);
	_position += dir * _moveSpeed * dt;
	_pShape->updateAtOnce(_position, dt);
	_attackTimer += dt;
}
std::vector<CEnemyBullet*> CEnemy_Slime::shoot(glm::vec3 targetPos) {
    std::vector<CEnemyBullet*> bullets;

    glm::vec3 up = glm::normalize(glm::vec3(0, 1, 0));
    glm::vec3 upLeft = glm::normalize(glm::vec3(-1.0f, 1, 0));
    glm::vec3 upRight = glm::normalize(glm::vec3(1.0f, 1, 0));
    glm::vec3 down = glm::normalize(glm::vec3(0, -1, 0));
    glm::vec3 downLeft = glm::normalize(glm::vec3(-1.0f, -1, 0));
    glm::vec3 downRight = glm::normalize(glm::vec3(1.0f, -1, 0));
    if (_bAttackWay)//上三角攻擊
    {
        bullets.push_back(new CEnemyBullet(_position, up, 1.0f, _shaderID));
        bullets.push_back(new CEnemyBullet(_position, downLeft, 1.0f, _shaderID));
        bullets.push_back(new CEnemyBullet(_position, downRight, 1.0f, _shaderID));
    }
    else//下三角攻擊
    {
        bullets.push_back(new CEnemyBullet(_position, upLeft, 1.0f, _shaderID));
        bullets.push_back(new CEnemyBullet(_position, upRight, 1.0f, _shaderID));
        bullets.push_back(new CEnemyBullet(_position, down, 1.0f, _shaderID));
    }
    _bAttackWay=!_bAttackWay;
    return bullets;
}
