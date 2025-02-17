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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f,

        -0.2f, -1.0f, 0.0f,
        0.2f, -0.2f, 0.0f,
        1.0f,  0.2f, 0.0f
    };  

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    // glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind VBO
    // glBindVertexArray(0); // Unbind VAO



    const char *vertexShaderSourceGLSLCode = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    
    const char *fragShaderSourceGLSLCode = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
            "FragColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);\n"
        "}\0";
    

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceGLSLCode, NULL);
    glCompileShader(vertexShader);
    //
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragShaderSourceGLSLCode, NULL);
    glCompileShader(fragShader);
    //
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


    int i = 0;
    int j = 0;
    while(!glfwWindowShouldClose(window))
    {
        j++;
        if (j % 10 == 0)
            i++;
        processInput(window);

        if (i % 3 == 0)
            glClearColor(0.8f, 0.2f, 0.2f, 1.0f);

        if (i % 3 == 1)
            glClearColor(0.1f, 0.6f, 0.1f, 1.0f);

        if (i % 3 == 2)
            glClearColor(0.2f, 0.3f, 0.9f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();    
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragShader); 

    return 0;
}