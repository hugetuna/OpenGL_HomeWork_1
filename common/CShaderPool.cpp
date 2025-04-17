#pragma once
#include "CShaderPool.h"
#include <iostream>

CShaderPool& CShaderPool::instance() {
    static CShaderPool instance;
    return instance;
}

CShaderPool::CShaderPool() {
    // �i�b������L��l�Ƥu�@
}

CShaderPool::~CShaderPool() {
    // �I�s glDeleteProgram ���� shader �귽
     for (const auto& entry : m_shaderEntries) { glDeleteProgram(entry.shaderID); }
}

GLuint CShaderPool::getShader(const std::string& vertexShaderName, const std::string& fragmentShaderName) {
    // ���ˬd vector ���O�_�w�s�b�ۦP shader ��T
    for (const auto& entry : m_shaderEntries) {
        if (entry.vertexShaderName == vertexShaderName && entry.fragmentShaderName == fragmentShaderName) {
            return entry.shaderID;
        }
    }

    // ���s�b�ɡA�I�s�~���禡�إ߷s�� shader
    GLuint shaderID = createShader(vertexShaderName, fragmentShaderName);

    // �x�s�s�� shader ��T�� vector ��
    ShaderEntry newEntry = { vertexShaderName, fragmentShaderName, shaderID };
    m_shaderEntries.push_back(newEntry);

    return shaderID;
}