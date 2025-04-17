#include <iostream>

#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "wmhandler.h"
#include "arcball.h"
#include "CPlayer.h"


#define EXAMPLE 5

extern Arcball g_arcball;
#if EXAMPLE == 1

#elif EXAMPLE == 5

extern GLfloat g_viewScale;
extern CPlayer* O_Player;
extern bool g_bMoving;
extern glm::vec3 mainCharPos;
#endif

// 滑鼠按鈕按下後 callback function(回呼函式) ---------------
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    // Arcball* arcball = static_cast<Arcball*>(glfwGetWindowUserPointer(window));
    g_arcball.onMouseButton(button, action, xpos, ypos);
    //std::cout << "button = " << button << "action = " << action << "mods = " << mods << std::endl;
#if EXAMPLE == 2

#elif EXAMPLE == 5
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (O_Player) {
            O_Player->shoot();
        }   
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        
    }
#endif
}
// ---------------------------------------------------------------------------------------

// 滑鼠在指定視窗上移動時的 callback function (回呼函式)
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    // Arcball* arcball = static_cast<Arcball*>(glfwGetWindowUserPointer(window));
    g_arcball.onCursorMove(xpos, ypos, width, height);
    //std::cout << "x = " << xpos << "y = " << ypos << std::endl;
#if EXAMPLE == 2
#elif EXAMPLE == 5
    if (g_bMoving)
    {
        // 以滑鼠距離(0,0)的距離作為每一個模型的位移
        float ndc_x = (2.0f * xpos) / width - 1.0f;
        float ndc_y = 1.0f - (2.0f * ypos) / height;
        float world_x = ndc_x * 3.0f;  // 對應 ortho 的左右 -3 ~ 3
        float world_y = ndc_y * 4.0f;  // 對應 ortho 的上下 -4 ~ 4
        mainCharPos = glm::vec3(world_x, world_y, 0.0f);

    }
#endif
}
// ---------------------------------------------------------------------------------------
// 
// 當視窗大小改變的 callback function
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// 當鍵盤按鍵按下時的 callback function (回呼函式)
// key : GLFW_KEY_0、 GLFW_KEY_a、GLFW_KEY_ESCAPE、GLFW_KEY_SPACE
//       完整定義在這邊 https://www.glfw.org/docs/latest/group__keys.html
// action : 
//          GLFW_PRESS：按鍵被按下。
//          GLFW_RELEASE：按鍵被釋放。
//          GLFW_REPEAT：按鍵被重複觸發（長按時會觸發多次）
// mods : 
//          GLFW_MOD_SHIFT：Shift 鍵被按下。
//          GLFW_MOD_CONTROL：Ctrl 鍵被按下。
//          GLFW_MOD_ALT：Alt 鍵被按下。
//          GLFW_MOD_SUPER：Windows 鍵或 Command 鍵被按下。
//          GLFW_MOD_CAPS_LOCK：Caps Lock 鍵被啟用。
//          GLFW_MOD_NUM_LOCK：Num Lock 鍵被啟用。
// 
//  注意：1. 一個按鍵按下到放開會產生兩次 keyCallback，
//           根據功能需求判斷是按下或是放掉去執行對應的功能
//        2. 使用 glfw 英文字母沒有分大小寫，都是傳回大寫的 ASCII 編碼
//           搭配檢查左右 shift 鍵是否按下是大寫還是小寫(假設 caps 鍵沒有被按下)
//       
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
            break;

        case GLFW_KEY_SPACE:
#if EXAMPLE == 2
            
#elif EXAMPLE == 5
            if (action == GLFW_PRESS) { g_bMoving = !g_bMoving; }
#endif
            break;
        default: // 針對英文字母大小寫進行處理
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                // 檢查 Shift 鍵(左右兩邊各一個)是否被按下
                bool isShiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ||
                                      (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
                // 判斷字母鍵的大小寫，預設使用鍵盤是沒有按下 CAPS 鍵
                if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
                    char letter = (isShiftPressed) ? ('A' + (key - GLFW_KEY_A)) : ('a' + (key - GLFW_KEY_A));
                    //std::cout << "key = " << letter << std::endl;
#if EXAMPLE == 1    

#elif EXAMPLE == 5
                    switch (letter) {
                    case 'S':
                    case 's':
                        break;
                    case 'L':
                    case 'l':
                        break;
                    }

#endif
                }   
            }
        break;
    }
}