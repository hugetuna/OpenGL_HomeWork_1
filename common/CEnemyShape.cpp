#include "CEnemyShape.h"

//建構時必須記憶使用的shader
CEnemyShape::CEnemyShape(GLuint shaderID) {
	_shaderID = shaderID;
}
CEnemyShape::~CEnemyShape() {
}

