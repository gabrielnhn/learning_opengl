#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // glViewport(0, 0, width, height);
    std::cout << "BRUH MOMENUTM" << std::endl;
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }   

    // glViewport(0, 0, 800, 600);
    // glViewport(10, 10, 400, 300);
    // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    int i = 0;
    int j = 0;
    while(!glfwWindowShouldClose(window))
    {
        j++;
        if (j % 10 == 0)
            i++;
        processInput(window);

        if (i % 3 == 0)
            glClearColor(0.4f, 0.2f, 0.8f, 1.0f);

        if (i % 3 == 1)
            glClearColor(0.1f, 0.2f, 0.5f, 1.0f);

        if (i % 3 == 2)
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    return 0;
}