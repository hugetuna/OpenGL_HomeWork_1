#pragma once
#include <string>
#include <vector>
#include <glew\include\GL\glew.h>
#include "initshader.h"

// �x�s shader ��T�����c
struct ShaderEntry {
    std::string vertexShaderName;
    std::string fragmentShaderName;
    GLuint shaderID;
};

class CShaderPool {
public:
    // ���o����ߤ@�� CShaderPool ��� (Singleton)
    static CShaderPool& instance();

    // �ǤJ vertex �P fragment shader ���W�١A�Y�w�إ߫h�^�ǹ��� shaderID�A
    // �_�h�I�s�~�� createShader �إ߷s shader�A�A�^�� shaderID
    GLuint getShader(const std::string& vertexShaderName, const std::string& fragmentShaderName);

private:
    // �p���غc�l�P�Ѻc�l
    CShaderPool();
    ~CShaderPool();

    // �T������P�����ާ@
    CShaderPool(const CShaderPool&) = delete;
    CShaderPool& operator=(const CShaderPool&) = delete;

    // �ϥ� vector �x�s�Ҧ� shader �����
    std::vector<ShaderEntry> m_shaderEntries;
};
