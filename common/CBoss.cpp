#include "CBoss.h"

CBoss::CBoss(GLuint shaderID) : CEnemy(shaderID) {
    _pShape = new CBossShape(shaderID); // 現在 CBossShape 可以被當作 CEnemyShape 用
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
    // 階段依據血量變化
    if (_hp <= 70) _stage = 2;
    if (_hp <= 30) _stage = 3;

    // 移動邏輯
    if (_stage == 1) {
        // 一階：在 y=3.5 的左右滑動
        static float direction = 1.0f;
        _position.y = 3.5f;
        _position.x += direction * _moveSpeed * dt;

        // 到達左右邊界就反向（假設邊界是 ±2.5）
        if (_position.x > 2.5f) direction = -1.0f;
        if (_position.x < -2.5f) direction = 1.0f;
    }
    else if (_stage == 2) {
        // 二階：待在固定位置 (0, 3.5)
        _position = glm::vec3(0.0f, 3.5f, 0.0f);
    }
    else if (_stage == 3) {
        // 三階：移動到畫面中央 (0, 0)
        _position = glm::vec3(0.0f, 0.0f, 0.0f);
    }

    // 更新形狀與攻擊計時器
    static_cast<CBossShape*>(_pShape)->setStage(_stage);
    _pShape->updateAtOnce(_position, dt);
    _attackTimer += dt;
}


std::vector<CEnemyBullet*> CBoss::shoot(glm::vec3 targetPos) {
    std::cout << "Stage: " << _stage << ", Timer: " << _attackTimer << std::endl;
    std::vector<CEnemyBullet*> bullets;
    glm::vec3 dir = glm::normalize(targetPos - _position);
    
    //一階攻擊模式
    if (_stage == 1) {
        float baseAngle = atan2(dir.y, dir.x); // 玩家方向角度
        std::vector<float> angles = { -60, -30, 30, 60 }; // 相對角度

        for (float a : angles) {
            //根據列表依序製造角度，並生成方向彈
            float angleRad = baseAngle + glm::radians(a);
            glm::vec3 bulletDir = glm::vec3(cos(angleRad), sin(angleRad), 0.0f);
            bullets.push_back(new CEnemyBullet(_position, bulletDir,2.5f,_shaderID));
        }
    }
    //二階攻擊模式
    if (_stage == 2) {
        float offset = glm::radians(static_cast<float>((rand() % 21) - 10)); // ±10° 微調
        for (int i = -15; i <= -3; i=i+2) {
            float baseAngle = glm::radians(i * 10.0f); // -120° ~ -60°
            float finalAngle = baseAngle + offset;
            glm::vec3 dir = glm::vec3(cos(finalAngle), sin(finalAngle), 0.0f);
            bullets.push_back(new CEnemyBullet(_position, dir, 2.5f, _shaderID));
        }
    }
    //三階攻擊模式
    if (_stage == 3) {
        static float rotAngle = 0.0f;
        float angleRad = glm::radians(rotAngle);
        glm::vec3 upDir = glm::vec3(cos(angleRad), sin(angleRad), 0.0f);
        glm::vec3 downDir = -upDir;

        bullets.push_back(new CEnemyBullet(_position, upDir,3.0f, _shaderID));
        bullets.push_back(new CEnemyBullet(_position, downDir, 3.0f, _shaderID));

        rotAngle += 2.0f; // 每次旋轉 1 度
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