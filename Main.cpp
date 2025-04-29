// Draw a  Circle with a radius of 0.8 unit
//#define GLM_ENABLE_EXPERIMENTAL 1

#include <iostream>
#include <fstream>
#include <sstream>

#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/string_cast.hpp>

#include "common/initshader.h"
#include "common/arcball.h"
#include "common/wmhandler.h"
#include "common/CShaderPool.h"
#include "common/CPlayer.h"
#include "common/CEnvironmentManager.h"
#include "common/CEnemy_Bat.h"
#include "common/CEnemy_Slime.h"
#include "common/CEnemy_Boxy.h"
#include "common/CEnemyManager.h"


#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 800 

Arcball g_arcball;

GLuint g_shaderProg;
GLuint g_shaderProg_player;
glm::mat4 g_viewMx = glm::mat4(1.0f);
glm::mat4 g_projMx = glm::mat4(1.0f);
GLfloat g_viewScale = 4.0f;

bool g_bMoving = false;
CPlayer* O_Player;
CEnvironmentManager* O_EnvironmentManager;
CEnemyManager* O_EnemyManager;
//----------------------------------------------------------------------------
void loadScene(void)
{
    // getShader 函式可用於建立 shader program 或取得特定 shader program 的代表 ID 
    //玩家相關的shader設定
    g_shaderProg_player = CShaderPool::instance().getShader("vshader_player.glsl", "fshader_player.glsl");
    O_Player = new CPlayer(g_shaderProg_player);
    //普通物件的shader設定
    g_shaderProg = CShaderPool::instance().getShader("vshader_basic.glsl", "fshader_basic.glsl");
    O_EnvironmentManager=new CEnvironmentManager(g_shaderProg);
    O_EnemyManager = new CEnemyManager(g_shaderProg);
    GLint viewLoc = glGetUniformLocation(g_shaderProg, "mxView"); 	// 取得 MVP 變數的位置
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(g_viewMx));

    g_projMx = glm::ortho(-3.0f, 3.0f, -4.0f, 4.0f, -2.0f, 2.0f);
    GLint projLoc = glGetUniformLocation(g_shaderProg, "mxProj"); 	// 取得 MVP 變數的位置

    
    glClearColor(1.0f, 0.6f, 0.95f, 0.8f); 
}
//----------------------------------------------------------------------------

void render( void )
{
    glClear(GL_COLOR_BUFFER_BIT);   // 先清背景

    // 設定 g_shaderProg (敵人、環境)
    glUseProgram(g_shaderProg);
    GLint viewLoc = glGetUniformLocation(g_shaderProg, "mxView");
    GLint projLoc = glGetUniformLocation(g_shaderProg, "mxProj");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(g_viewMx));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(g_projMx));
    O_EnvironmentManager->drawEnvironment();
    O_EnemyManager->renderAllEnemy();

    // 設定 g_shaderProg_player（玩家）
    glUseProgram(g_shaderProg_player);
    viewLoc = glGetUniformLocation(g_shaderProg_player, "mxView");
    projLoc = glGetUniformLocation(g_shaderProg_player, "mxProj");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(g_viewMx));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(g_projMx));
    O_Player->render();
}
//----------------------------------------------------------------------------
glm::vec3 mainCharPos;
void update(float dt)
{
    O_Player->setPos(mainCharPos);
    O_Player->update(dt, O_EnemyManager->getBulletList());
    O_EnemyManager->updateAllEnemy(dt, O_Player->getBulletList(), O_Player->getPos());
    //環境物件
    O_EnvironmentManager->updateEnvironment(dt);
}

void releaseAll()
{
    delete O_Player;
    delete O_EnvironmentManager;
    delete O_EnemyManager;
}

int main() {
    // ------- 檢查與建立視窗  ---------------  
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 設定 OpenGL 版本與 Core Profile
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //只啟用 OpenGL 3.3 Core Profile（不包含舊版 OpenGL 功能）
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // 禁止視窗大小改變

    // 建立 OpenGL 視窗與該視窗執行時所需的的狀態、資源和環境(context 上下文)
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Draw ", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 設定將這個視窗的資源(OpenGL 的圖形上下文）與當前執行緒綁定，讓該執行緒能夠操作該視窗的資源
    glfwMakeContextCurrent(window);

    // 設定視窗大小, 這樣 OpenGL 才能知道如何將視窗的內容繪製到正確的位置
    // 基本上寬與高設定成視窗的寬與高即可
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    // ---------------------------------------

    // 設定相關事件的 callback 函式，以便事件發生時，能呼叫對應的函式
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);// 視窗大小被改變時
    glfwSetKeyCallback(window, keyCallback);                        // 有鍵盤的按鍵被按下時
    glfwSetMouseButtonCallback(window, mouseButtonCallback);        // 有滑鼠的按鍵被按下時
    glfwSetCursorPosCallback(window, cursorPosCallback);            // 滑鼠在指定的視窗上面移動時

    // 呼叫 loadScene() 建立與載入 GPU 進行描繪的幾何資料 
    loadScene();

    float lastTime = (float)glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime; // 計算前一個 frame 到目前為止經過的時間
        lastTime = currentTime;
        update(deltaTime);      // 呼叫 update 函式，並將 deltaTime 傳入，讓所有動態物件根據時間更新相關內容
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    releaseAll(); // 程式結束前釋放所有的資源
    glfwTerminate();
    return 0;
}