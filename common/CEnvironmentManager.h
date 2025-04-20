// CCloud.h
#pragma once
#include <cmath>
#include <glew/include/GL/glew.h>
#include <vector>

#include "CCloud.h"

class CEnvironmentManager {
public:
    CEnvironmentManager(GLuint _shader);
    ~CEnvironmentManager();
    void updateEnvironment(float deltaTime);
    void drawEnvironment();
private:
    std::vector<CCloud*> _clouds;
    float _spawnTimer;       // ������ͦ����ɶ����j
    float _spawnInterval;    // �C�X��ͦ��@����
    GLuint _shaderID;

    void spawnCloud();
};
