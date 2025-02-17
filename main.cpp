#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp> // glm::vec3


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    // std::cout << "BRUH MOMENUTM" << std::endl;
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
  
    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL);
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

    glViewport(0, 0, 800, 800);
    // glViewport(10, 10, 400, 300);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // float vertices[] = {
    // std::vector<float> vertices = {

    std::vector<glm::vec3> vertices = {
        // glm::vec3(-0.5f, 0.5f, 0.0f),
        // glm::vec3(-0.5f, -0.5f, 0.0f),
        // glm::vec3(0.5f,  0.5f, 0.0f),
        // glm::vec3(0.5f, -0.5f, 0.0f),
        {0.1+ -0.3f, 0.3f, 0.0f},
        {0.1+ 0.3f,  0.3f, 0.0f},
        {0.1+ -0.3f, -0.3f, 0.0f},
        {0.1+ 0.3f, -0.3f, 0.0f},
    };  


    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices.front(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices.front(), GL_DYNAMIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    uint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    int indices[] = {
        0,1,2,
        1,2,3,
    };
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW); 

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


    // int i = 0;
    bool goingdown = true;
    bool goingright = true;
    int j = 0;
    while(!glfwWindowShouldClose(window))
    {
        j++;
        // if (j % 5 == 0)
        if (true)
        {

            if (vertices[2].y < -1)
            {
                goingdown = false;
                glClearColor(0.8f, 0.2f, 0.2f, 1.0f);
            }
                
            if (vertices[0].y >= 1)
            {
                goingdown = true;
                glClearColor(0.2f, 0.5f, 0.2f, 1.0f);
            }

            if (vertices[1].x > 1)
            {
                goingright = false;
                glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

            }

            if (vertices[0].x < -1)
            {
                goingright = true;
                glClearColor(0.9f, 0.3f, 0.0f, 1.0f);
            }

            for(long unsigned int k=0; k < vertices.size(); k++)
            {
                if (goingdown)
                    vertices[k].y = vertices[k].y-0.005;
                else
                    vertices[k].y = vertices[k].y+0.005;
                
                if (goingright)
                    vertices[k].x = vertices[k].x+0.005;
                else
                    vertices[k].x = vertices[k].x-0.005;

                // std::cout << k << ": " << vertices[k].y << std::endl;
                
            }
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices.front(), GL_DYNAMIC_DRAW);

        }

        processInput(window);

        // if (i % 3 == 0)
        //     glClearColor(0.8f, 0.2f, 0.2f, 1.0f);

        // if (i % 3 == 1)
        //     glClearColor(0.1f, 0.6f, 0.1f, 1.0f);

        // if (i % 3 == 2)
        // glClearColor(0.2f, 0.3f, 0.9f, 1.0f); 

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glBindVertexArray(EBO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();    
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragShader); 

    return 0;
}