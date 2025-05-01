#include "CBoss.h"

CBoss::CBoss(GLuint shaderID) : CEnemy(shaderID) {
    _pShape = new CBossShape(shaderID); // �{�b CBossShape �i�H�Q��@ CEnemyShape ��
    _pShape->setShaderIDAtOnce();
    _pShape->setupVertexAttributesAtOnce();

    _moveSpeed = 0.4f;
    _hp = 100;
    _attackInterval = 3.0f;
    _attackTimer = 1.0f;
    _stage = 1;
}
CBoss::~CBoss() {

}

void CBoss::update(float dt, glm::vec3 playerPos) {
    // ���q�̾ڦ�q�ܤ�
    if (_hp <= 70) _stage = 2;
    if (_hp <= 30) _stage = 3;

    // �����޿�
    if (_stage == 1) {
        // �@���G�b y=3.5 �����k�ư�
        static float direction = 1.0f;
        _position.y = 3.5f;
        _position.x += direction * _moveSpeed * dt;

        // ��F���k��ɴN�ϦV�]���]��ɬO ��2.5�^
        if (_position.x > 2.5f) direction = -1.0f;
        if (_position.x < -2.5f) direction = 1.0f;
    }
    else if (_stage == 2) {
        // �G���G�ݦb�T�w��m (0, 3.5)
        _position = glm::vec3(0.0f, 3.5f, 0.0f);
    }
    else if (_stage == 3) {
        // �T���G���ʨ�e������ (0, 0)
        _position = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // ��s�Ϊ��P�����p�ɾ�
    static_cast<CBossShape*>(_pShape)->setStage(_stage);
    _pShape->updateAtOnce(_position, dt);
    _attackTimer += dt;
}


std::vector<CEnemyBullet*> CBoss::shoot(glm::vec3 targetPos) {
    std::cout << "Stage: " << _stage << ", Timer: " << _attackTimer << std::endl;
    std::vector<CEnemyBullet*> bullets;
    glm::vec3 dir = glm::normalize(targetPos - _position);
    
    //�@�������Ҧ�
    if (_stage == 1) {
        float baseAngle = atan2(dir.y, dir.x); // ���a��V����
        std::vector<float> angles = { -60, -30, 30, 60 }; // �۹﨤��

        for (float a : angles) {
            //�ھڦC��̧ǻs�y���סA�åͦ���V�u
            float angleRad = baseAngle + glm::radians(a);
            glm::vec3 bulletDir = glm::vec3(cos(angleRad), sin(angleRad), 0.0f);
            bullets.push_back(new CEnemyBullet(_position, bulletDir,2.5f,_shaderID));
        }
    }
    //�G�������Ҧ�
    if (_stage == 2) {
        float offset = glm::radians(static_cast<float>((rand() % 21) - 10)); // ��10�X �L��
        for (int i = -15; i <= -3; i=i+2) {
            float baseAngle = glm::radians(i * 10.0f); // -120�X ~ -60�X
            float finalAngle = baseAngle + offset;
            glm::vec3 dir = glm::vec3(cos(finalAngle), sin(finalAngle), 0.0f);
            bullets.push_back(new CEnemyBullet(_position, dir, 2.5f, _shaderID));
        }
    }
    //�T�������Ҧ�
    if (_stage == 3) {
        static float rotAngle = 0.0f;
        float angleRad = glm::radians(rotAngle);
        glm::vec3 upDir = glm::vec3(cos(angleRad), sin(angleRad), 0.0f);
        glm::vec3 downDir = -upDir;

        bullets.push_back(new CEnemyBullet(_position, upDir,3.0f, _shaderID));
        bullets.push_back(new CEnemyBullet(_position, downDir, 3.0f, _shaderID));

        rotAngle += 2.0f; // �C������ 1 ��
    }

    return bullets;
}
bool CBoss::readyToShoot() {
    if (_stage == 1&& _attackTimer >= _attackInterval)
    {
        _attackTimer = 0.0f;
        return true;
    }
    else if(_stage == 2 && _attackTimer >= 0.5f)
    {
        _attackTimer = 0.0f;
        return true;
    }
    else if (_stage == 3 && _attackTimer >= 0.1f)
    {
        _attackTimer = 0.0f;
        return true;
    }
    else
    {
        return false;
    }
}