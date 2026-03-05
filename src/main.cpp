#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

#include <iostream>
#include <cstring>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

float perspectiveMatrix[16];
const float fFrustumScale = 1.0f;

Shader* ourShaderptr;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GLFW Application", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    Shader ourShader("../src/shaders/vertexShader.vert","../src/shaders/fragmentShader.frag");
    ourShaderptr = &ourShader;
    ourShader.use();
    ourShader.setFloat("loopDuration", 5.0f);

    float fzNear = 0.5f; float fzFar = 3.0f;

    memset(perspectiveMatrix, 0, sizeof(float) * 16);

    perspectiveMatrix[0] = fFrustumScale;
    perspectiveMatrix[5] = fFrustumScale;
    perspectiveMatrix[10] = (fzFar + fzNear) / (fzNear - fzFar);
    perspectiveMatrix[14] = (2 * fzFar * fzNear) / (fzNear - fzFar);
    perspectiveMatrix[11] = -1.0f;

    ourShader.setMat4("perspectiveMatrix", perspectiveMatrix);

    //enable ace culling
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    const float vertexData[] = {
        0.25f,  0.25f, -1.25f, 1.0f,
        0.25f, -0.25f, -1.25f, 1.0f,
        -0.25f,  0.25f, -1.25f, 1.0f,

        0.25f, -0.25f, -1.25f, 1.0f,
        -0.25f, -0.25f, -1.25f, 1.0f,
        -0.25f,  0.25f, -1.25f, 1.0f,

        0.25f,  0.25f, -2.75f, 1.0f,
        -0.25f,  0.25f, -2.75f, 1.0f,
        0.25f, -0.25f, -2.75f, 1.0f,

        0.25f, -0.25f, -2.75f, 1.0f,
        -0.25f,  0.25f, -2.75f, 1.0f,
        -0.25f, -0.25f, -2.75f, 1.0f,

        -0.25f,  0.25f, -1.25f, 1.0f,
        -0.25f, -0.25f, -1.25f, 1.0f,
        -0.25f, -0.25f, -2.75f, 1.0f,

        -0.25f,  0.25f, -1.25f, 1.0f,
        -0.25f, -0.25f, -2.75f, 1.0f,
        -0.25f,  0.25f, -2.75f, 1.0f,

        0.25f,  0.25f, -1.25f, 1.0f,
        0.25f, -0.25f, -2.75f, 1.0f,
        0.25f, -0.25f, -1.25f, 1.0f,

        0.25f,  0.25f, -1.25f, 1.0f,
        0.25f,  0.25f, -2.75f, 1.0f,
        0.25f, -0.25f, -2.75f, 1.0f,

        0.25f,  0.25f, -2.75f, 1.0f,
        0.25f,  0.25f, -1.25f, 1.0f,
        -0.25f,  0.25f, -1.25f, 1.0f,

        0.25f,  0.25f, -2.75f, 1.0f,
        -0.25f,  0.25f, -1.25f, 1.0f,
        -0.25f,  0.25f, -2.75f, 1.0f,

        0.25f, -0.25f, -2.75f, 1.0f,
        -0.25f, -0.25f, -1.25f, 1.0f,
        0.25f, -0.25f, -1.25f, 1.0f,

        0.25f, -0.25f, -2.75f, 1.0f,
        -0.25f, -0.25f, -2.75f, 1.0f,
        -0.25f, -0.25f, -1.25f, 1.0f,




        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.8f, 0.8f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,

        0.8f, 0.8f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,
        0.8f, 0.8f, 0.8f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,

        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,

        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,

    };
    size_t colorData = sizeof(vertexData) / 2;

    unsigned int VBO,VAO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);   
    glBindVertexArray(VAO);
    
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(colorData));
    glBindVertexArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle
        ourShader.use();
        
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    perspectiveMatrix[0] = fFrustumScale / (width / (float)height);
	perspectiveMatrix[5] = fFrustumScale;

    ourShaderptr->use();
	ourShaderptr->setMat4("perspectiveMatrix", perspectiveMatrix);

    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}