#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CShape.h"
#include "initshader.h"

CShape::CShape()
{
	_vtxCount = _vtxAttrCount = _idxCount = 0;
	_vao = 0; _vbo = 0; _ebo = 0;
	_shaderProg = 0;
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_color = glm::vec3(1.0f, 1.0f, 1.0f);
	_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotX = 0.0f; _rotY = 0.0f; _rotZ = 0.0f;
	_rotAxis = 0;
	_bRotation = _bScale = _bPos = _bTransform = _bOnTransform = false;
	_mxScale = glm::mat4(1.0f);
	_mxPos = glm::mat4(1.0f);
	_mxRotX = glm::mat4(1.0f);
	_mxRotY = glm::mat4(1.0f);
	_mxRotZ = glm::mat4(1.0f);
	_mxRotation = glm::mat4(1.0f);
	_mxTRS = glm::mat4(1.0f);
	_mxTransform = glm::mat4(1.0f);
	_mxFinal = glm::mat4(1.0f);
	_modelMxLoc = 0;
	_points = nullptr; _idx = nullptr;
}

CShape::~CShape()
{

}

void CShape::setupVertexAttributes()
{
	// �]�w VAO�BVBO �P EBO
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(_vao);

	// �]�w VBO
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vtxCount * _vtxAttrCount * sizeof(float), _points, GL_STATIC_DRAW);

	// �]�w EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _idxCount * sizeof(GLuint), _idx, GL_STATIC_DRAW);

	// ��m�ݩ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _vtxAttrCount * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	// �C���ݩ�
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _vtxAttrCount * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//�k�V�q�ݩ�
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, _vtxAttrCount * sizeof(float), BUFFER_OFFSET(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//�K�Ϯy���ݩ�
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, _vtxAttrCount * sizeof(float), BUFFER_OFFSET(9 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glBindVertexArray(0); // �Ѱ��� VAO ���j�w
}

void CShape::setShaderID(GLuint shaderID)
{
	_shaderProg = shaderID;
	glUseProgram(_shaderProg);
	_modelMxLoc = glGetUniformLocation(_shaderProg, "mxModel"); 	// ���o MVP �ܼƪ���m
	glUniformMatrix4fv(_modelMxLoc, 1, GL_FALSE, glm::value_ptr(_mxTRS));
}

void CShape::setColor(glm::vec3 vColor)
{
	_color = vColor;
	for (int i = 0; i < _vtxCount; i++) {
		_points[i * _vtxAttrCount + COLOR_OFFSET] = _color.x;
		_points[i * _vtxAttrCount + COLOR_OFFSET + 1] = _color.y;
		_points[i * _vtxAttrCount + COLOR_OFFSET + 2] = _color.z;
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vtxCount * _vtxAttrCount * sizeof(float), _points, GL_STATIC_DRAW);
}

void CShape::draw() {
	glUseProgram(_shaderProg);
	updateMatrix();
	glBindVertexArray(_vao);
	// �w�]���I�s��ڪ�ø�s���O�A�Ѥl���O�M�w�O�_�����I�s glDrawElements()
}

void CShape::update(float dt)
{


}
void CShape::setScale(glm::vec3 vScale)
{
	_scale = vScale;
	_bScale = true;
	_mxScale = glm::scale(glm::mat4(1.0f), _scale);
}

void CShape::setPos(glm::vec3 vPt)
{
	_pos = vPt;
	_bPos = true;
	_mxPos = glm::translate(glm::mat4(1.0f), _pos);
}

void CShape::setRotX(float angle)
{
	_rotX = glm::radians(angle);
	_rotAxis = _rotAxis | 1;
	_mxRotX = glm::rotate(glm::mat4(1.0f), _rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	_mxRotation = _mxRotX;
	_bRotation = true;
}

void CShape::setRotY(float angle)
{
	_rotY = glm::radians(angle);
	_rotAxis = _rotAxis | 2;
	_mxRotY = glm::rotate(glm::mat4(1.0f), _rotY, glm::vec3(0.0f, 1.0f, 0.0f));
	if (_rotAxis & 1)_mxRotation = _mxRotY * _mxRotX;
	else _mxRotation = _mxRotY;
	_bRotation = true;
}

void CShape::setRotZ(float angle)
{
	_rotZ = glm::radians(angle);
	_mxRotZ = glm::rotate(glm::mat4(1.0f), _rotZ, glm::vec3(0.0f, 0.0f, 1.0f));
	if (_rotAxis == 1) _mxRotation = _mxRotZ * _mxRotX;
	else if (_rotAxis == 2) _mxRotation = _mxRotZ * _mxRotY;
	else if (_rotAxis == 3) _mxRotation = _mxRotZ * _mxRotY * _mxRotX;
	else _mxRotation = _mxRotZ;
	_bRotation = true;
}

void CShape::updateMatrix()
{
	if (_bScale || _bPos || _bRotation)
	{
		_mxTRS = _mxPos * _mxRotation * _mxScale;
		if (_bOnTransform == true) _mxFinal = _mxTransform * _mxTRS;
		else _mxFinal = _mxTRS;
		_bScale = _bPos = _bRotation = false;
	}
	if (_bTransform) {
		_mxFinal = _mxTransform * _mxTRS;
		_bTransform = false;
	}
	// �p�h�Ӽҫ��ϥάۦP�� shader program,�]�C�@�Ӽҫ��� mxTRS �����P�A�ҥH�C��frame���n��s
	glUniformMatrix4fv(_modelMxLoc, 1, GL_FALSE, glm::value_ptr(_mxFinal));
}

void CShape::setTransformMatrix(glm::mat4 mxMatrix)
{
	_bOnTransform = _bTransform = true;
	_mxTransform = mxMatrix;
}
glm::mat4 CShape::getModelMatrix() { return _mxFinal; }

GLuint CShape::getShaderProgram() { return _shaderProg; }

void CShape::reset()
{
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_color = glm::vec3(1.0f, 1.0f, 1.0f);
	_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotX = 0.0f; _rotY = 0.0f; _rotZ = 0.0f;
	_rotAxis = 0;
	_bRotation = _bScale = _bPos = _bTransform = _bOnTransform = false;
	_mxScale = glm::mat4(1.0f);
	_mxPos = glm::mat4(1.0f);
	_mxTRS = glm::mat4(1.0f);
	_mxRotX = glm::mat4(1.0f);
	_mxRotY = glm::mat4(1.0f);
	_mxRotZ = glm::mat4(1.0f);
	_mxRotation = glm::mat4(1.0f);
	_mxTransform = glm::mat4(1.0f);
	_mxFinal = glm::mat4(1.0f);
}