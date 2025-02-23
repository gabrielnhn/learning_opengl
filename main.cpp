#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

auto camera = glm::vec3(3, 2, 3);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    // std::cout << "BRUH MOMENUTM" << std::endl;
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.x -= 0.1;
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.x += 0.1;

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.z -= 0.1;

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.z += 0.1;

    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        camera.y -= 0.1;

    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        camera.y += 0.1;
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

    std::vector<glm::vec4> vertices = {
        {0.1+ -0.3f, 0.3f, -1.0f, 1.0},
        {0.1+ 0.3f,  0.3f, -1.0f, 1.0},
        {0.1+ -0.3f, -0.3f, -1.0f, 1.0},
        {0.1+ 0.3f, -0.3f, -1.0f, 1.0},
        {0.1+ -0.3f, 0.3f, 1.0f, 1.0},
        {0.1+ 0.3f,  0.3f, 1.0f, 1.0},
        {0.1+ -0.3f, -0.3f, 1.0f, 1.0},
        {0.1+ 0.3f, -0.3f, 1.0f, 1.0},
    };  


    //fuck it perspective

    glm::mat4 projection = glm::perspective(45.0f, 1.0f, 0.1f, 60.0f);
    glm::mat4 view = glm::lookAt(camera, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = projection * view * model;
    

    std::vector<glm::vec3> gl_vertices;

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec4), &vertices.front(), GL_DYNAMIC_DRAW);


    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glEnableVertexAttribArray(0);  

    uint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    std::vector<int> indices = {
        0,1,2,
        1,2,3,
        0,4,6,
        0,2,6,
        2,6,7,
        2,3,7,
        1,3,7,
        1,5,7,
        0,1,4,
        0,1,5,
        4,5,6,
        5,6,7,
    };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(int), &indices.front(), GL_DYNAMIC_DRAW); 

    const char *vertexShaderSourceGLSLCode = "#version 330 core\n"
        // "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 0) in vec4 aPos;\n"
        "uniform mat4 mvp;\n"
        "void main()\n"
        "{\n"
        // "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        // "   gl_Position = mvp * vec4    (aPos, 1.0);\n"
        "   gl_Position = mvp * aPos;\n"
        "}\0";
    
    const char *fragShaderSourceGLSLCode = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
            "FragColor = vec4(0.2f, 0.9f, 0.2f, 1.0f);\n"
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


    int mvpLocation = glGetUniformLocation(shaderProgram, "mvp");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));


    glEnable(GL_DEPTH_TEST);

    // int i = 0;
    // float vx = 0.012;
    float vx = 0;
    // float vy = 0.013;
    float vy = 0;
    // bool goingright = true;
    int j = 0;
    glClearColor(0.2f, 0.2f, 0.2f, 0.5f);
    while(!glfwWindowShouldClose(window))
    {

        j++;
        // if (j % 5 == 0)
        if (true)
        {
            const float BOUND = 5.0f;

            if (vertices[2].y < -BOUND)
            {
                vy = -vy;
                glClearColor(0.8f, 0.2f, 0.2f, 1.0f);
            }
                
            if (vertices[0].y >= BOUND)
            {
                vy = - vy;
                glClearColor(0.2f, 0.5f, 0.2f, 1.0f);
            }

            if (vertices[1].x > BOUND)
            {
                vx = -vx;
                glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

            }

            if (vertices[0].x < -BOUND)
            {
                vx = -vx;
                glClearColor(0.9f, 0.3f, 0.0f, 1.0f);
            }

            for(long unsigned int k=0; k < vertices.size(); k++)
            {
                vertices[k].x += vx;
                vertices[k].y += vy;
             
                // std::cout << k << ": " << vertices[k].y << std::endl;
                
            }

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec4), &vertices.front(), GL_DYNAMIC_DRAW);

        }

        // remake projection
        view = glm::lookAt(camera, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        glm::mat4 mvp = projection * view * model;
        int mvpLocation = glGetUniformLocation(shaderProgram, "mvp");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));


        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();    
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragShader); 

    return 0;
}