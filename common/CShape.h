#pragma once
#include <glm/glm.hpp>


class CShape
{
public:
	CShape();
	virtual ~CShape();
	virtual void draw();
	virtual void reset();
	virtual void update(float dt);
	void setupVertexAttributes();
	void setShaderID(GLuint shaderID);
	void setColor(glm::vec3 vColor); // �]�w�ҫ����C��
	void setScale(glm::vec3 vScale); // �]�w�ҫ����Y���
	void setPos(glm::vec3 vPt); // �]�w�ҫ�����m
	void setRotX(float angle); // �]�w�ҫ���X�b���ਤ��
	void setRotY(float angle); // �]�w�ҫ���Y�b���ਤ��
	void setRotZ(float angle); // �]�w�ҫ���Z�b���ਤ��
	void setTransformMatrix(glm::mat4 mxMatrix);
	void updateMatrix();

	glm::mat4 getModelMatrix();
	GLuint getShaderProgram();

protected:
	int _vtxCount, _vtxAttrCount, _idxCount; // ���I�ơB���I�ݩʼơB�I�����ޭȼ�
	GLfloat* _points;
	GLuint* _idx;

	GLuint _vao, _vbo, _ebo;
	GLuint _shaderProg, _rotAxis;
	GLint _modelMxLoc;
	bool _bRotation, _bScale, _bPos;
	bool _bTransform, _bOnTransform;
	// _bTransform : true �N���]�w�s���ഫ�x�}
	// _bOnTransform : true �N���g�]�w�L�ഫ�x�}�A�Ω�P�_�O�_�ݭn��s model matrix

	glm::vec3 _color;
	glm::vec3 _scale;	// �ҫ����Y���
	glm::vec3 _pos;		// �ҫ�����m
	GLfloat _rotX, _rotY, _rotZ; // �ҫ������ਤ��
	glm::mat4 _mxRotX, _mxRotY, _mxRotZ, _mxRotation, _mxScale, _mxPos, _mxTRS;
	glm::mat4 _mxTransform, _mxFinal;
};