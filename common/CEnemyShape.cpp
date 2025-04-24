#include "CEnemyShape.h"

//建構時必須記憶使用的shader
CEnemyShape::CEnemyShape(GLuint shaderID) {
	_shaderID = shaderID;
}
CEnemyShape::~CEnemyShape() {
}
void CEnemyShape::setupVertexAttributesAtOnce() {

}
void CEnemyShape::setShaderIDAtOnce() {

}
void CEnemyShape::updateAtOnce(glm::vec3 pos, float dt) {

}
void CEnemyShape::drawAtOnce() {

}
