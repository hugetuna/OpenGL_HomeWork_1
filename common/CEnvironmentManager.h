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
    float _spawnTimer;       // 控制雲朵生成的時間間隔
    float _spawnInterval;    // 每幾秒生成一朵雲
    GLuint _shaderID;

    void spawnCloud();
};
