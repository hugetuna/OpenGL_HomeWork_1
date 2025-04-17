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

// �ƹ����s���U�� callback function(�^�I�禡) ---------------
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

// �ƹ��b���w�����W���ʮɪ� callback function (�^�I�禡)
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
        // �H�ƹ��Z��(0,0)���Z���@���C�@�Ӽҫ����첾
        float ndc_x = (2.0f * xpos) / width - 1.0f;
        float ndc_y = 1.0f - (2.0f * ypos) / height;
        float world_x = ndc_x * 3.0f;  // ���� ortho �����k -3 ~ 3
        float world_y = ndc_y * 4.0f;  // ���� ortho ���W�U -4 ~ 4
        mainCharPos = glm::vec3(world_x, world_y, 0.0f);

    }
#endif
}
// ---------------------------------------------------------------------------------------
// 
// ������j�p���ܪ� callback function
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// ����L������U�ɪ� callback function (�^�I�禡)
// key : GLFW_KEY_0�B GLFW_KEY_a�BGLFW_KEY_ESCAPE�BGLFW_KEY_SPACE
//       ����w�q�b�o�� https://www.glfw.org/docs/latest/group__keys.html
// action : 
//          GLFW_PRESS�G����Q���U�C
//          GLFW_RELEASE�G����Q����C
//          GLFW_REPEAT�G����Q����Ĳ�o�]�����ɷ|Ĳ�o�h���^
// mods : 
//          GLFW_MOD_SHIFT�GShift ��Q���U�C
//          GLFW_MOD_CONTROL�GCtrl ��Q���U�C
//          GLFW_MOD_ALT�GAlt ��Q���U�C
//          GLFW_MOD_SUPER�GWindows ��� Command ��Q���U�C
//          GLFW_MOD_CAPS_LOCK�GCaps Lock ��Q�ҥΡC
//          GLFW_MOD_NUM_LOCK�GNum Lock ��Q�ҥΡC
// 
//  �`�N�G1. �@�ӫ�����U���}�|���ͨ⦸ keyCallback�A
//           �ھڥ\��ݨD�P�_�O���U�άO�񱼥h����������\��
//        2. �ϥ� glfw �^��r���S�����j�p�g�A���O�Ǧ^�j�g�� ASCII �s�X
//           �f�t�ˬd���k shift ��O�_���U�O�j�g�٬O�p�g(���] caps ��S���Q���U)
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
        default: // �w��^��r���j�p�g�i��B�z
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                // �ˬd Shift ��(���k����U�@��)�O�_�Q���U
                bool isShiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ||
                                      (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
                // �P�_�r���䪺�j�p�g�A�w�]�ϥ���L�O�S�����U CAPS ��
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