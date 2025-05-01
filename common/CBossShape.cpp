#include "CBossShape.h"

CBossShape::CBossShape(GLuint shaderID):CEnemyShape(shaderID) {
    //一階，兩個圓
    _outerCircle = new CCircle(24);
    _innerCircle = new CCircle(24);
    
    _outerCircle->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
    _innerCircle->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
    _outerCircle->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    _innerCircle->setColor(glm::vec3(1.0f, 1.0f, 0.0f));
    _innerCircle->setScale(glm::vec3(0.5f, 0.5f, 1.0f));
    //二階，兩個星
    _outerStar = new CStar(4, 1.0f, 0.5f);  // 四角星
    _innerStar = new CStar(4, 0.5f, 0.25f); // 黃色的內部星星

    _outerStar->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
    _innerStar->setPos(glm::vec3(0.0f, 0.0f, 0.0f));
    _outerStar->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    _innerStar->setColor(glm::vec3(1.0f, 1.0f, 0.0f));
    //三階，長翅膀
    _leftWing = new CTriangle();
    _rightWing = new CTriangle();
    _leftWing->setPos(glm::vec3(-0.5f, 0.5f, 0.0f));
    _rightWing->setPos(glm::vec3(0.5f, 0.5f, 0.0f));
    _leftWing->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    _leftWing->setRotZ(45);
    _rightWing->setColor(glm::vec3(1.0f, 0.0f, 0.0f));
    _rightWing->setRotZ(-45);
}

CBossShape::~CBossShape() {
    if (_outerCircle) delete _outerCircle;
    if (_innerCircle)delete _innerCircle;
    if (_outerStar)delete _outerStar;
    if (_innerStar)delete _innerStar;
    if (_leftWing)delete _leftWing;
    if (_rightWing)delete _rightWing;
}
void CBossShape::setupVertexAttributesAtOnce() {
    _outerCircle->setupVertexAttributes();
    _innerCircle->setupVertexAttributes();
    _outerStar->setupVertexAttributes();
    _innerStar->setupVertexAttributes();
    _leftWing->setupVertexAttributes();
    _rightWing->setupVertexAttributes();
}
void CBossShape::setShaderIDAtOnce() {
    _outerCircle->setShaderID(_shaderID);
    _innerCircle->setShaderID(_shaderID);
    _outerStar->setShaderID(_shaderID);
    _innerStar->setShaderID(_shaderID);
    _leftWing->setShaderID(_shaderID);
    _rightWing->setShaderID(_shaderID);
}

void CBossShape::setStage(int stage) {
    _stage = stage;
}


void CBossShape::updateAtOnce(glm::vec3 pos, float dt) {
    _outerCircle->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _innerCircle->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));

    _outerStar->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _innerStar->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));

    // 設定翅膀位置與旋轉
    _leftWing->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
    _rightWing->setTransformMatrix(glm::translate(glm::mat4(1.0f), pos));
}

void CBossShape::drawAtOnce() {
    switch (_stage) {
    case 1:
        _outerCircle->draw();
        _innerCircle->draw();
        break;
    case 2:
        
        _outerStar->draw();
        _innerStar->draw();
        break;
    case 3:
        _outerStar->draw();
        _innerStar->draw();
        
        _leftWing->draw();
        _rightWing->draw();
        break;
    }
}


