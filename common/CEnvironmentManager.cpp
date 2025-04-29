// CEnvironmentManager.cpp
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>  // for rand()
#include <ctime>
#include "CEnvironmentManager.h"

CEnvironmentManager::CEnvironmentManager(GLuint _shader=0){
	_spawnTimer = 0;
	_spawnInterval=2.0f;
	_shaderID = _shader;
	//�ͦ��H���ؤl
	std::srand(static_cast<unsigned>(std::time(nullptr))); // ��l���H���ؤl
}
CEnvironmentManager::~CEnvironmentManager() {
	for (auto cloud : _clouds) {
		delete cloud;
	}
	_clouds.clear();
}
void CEnvironmentManager::updateEnvironment(float deltaTime) {
	_spawnTimer += deltaTime;
	if (_spawnTimer>= _spawnInterval)
	{
		_spawnTimer = 0;
		spawnCloud();
	}
	for (int i = 0; i < _clouds.size(); ) {
		_clouds[i]->update(deltaTime);

		if (_clouds[i]->getPosition().x < -4.5f) {
			delete _clouds[i];                    // �R���O����
			_clouds.erase(_clouds.begin() + i);  // �����o����ơ]���| ++i�A�]���U�@�����ӤF�^
		}
		else {
			++i;  // �u���S���R���ɤ~���U�@��
		}
	}

}
void CEnvironmentManager::drawEnvironment() {
	for (auto cloud : _clouds) {
		cloud->draw();
	}
}
void CEnvironmentManager::spawnCloud() {
	// �H��x�y�СB�H���t��
	float x = -3.0f + static_cast<float>(rand()) / RAND_MAX * 6.0f;  // �b -3 �� 3 ����
	float speed = 1.0f + static_cast<float>(rand()) / RAND_MAX * 0.4f;  // 0.2~0.6

	glm::vec3 pos(x, 4.5, 0.0f);  // �q�e���W��ͦ�
	_clouds.push_back(new CCloud(pos, speed, _shaderID));
}