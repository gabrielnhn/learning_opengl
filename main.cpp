#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "npy.hpp"


# define M_PI 3.14159265358979323846

float farDistance=500.0f;
auto camera = glm::vec3(0, 0, 3);
auto aim = glm::vec3(0, 0, 0);

double mousex, mousey;
double mousex_last, mousey_last;
int last_mouse_event = GLFW_RELEASE;

double height = 800;
double width = 800;

float speed = 0.02f;

static float yaw = -90.0f; // Start facing forward
static float pitch = 0.0f;
glm::mat4 mvp;

glm::mat3x3 right_transform = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0, 1, 0));


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    glm::vec3 forward = glm::normalize(aim - camera); // Forward direction
    glm::vec3 right = right_transform * forward; // Forward direction

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera -= speed * forward;
        aim -= speed * forward;
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera += speed * forward;
        aim += speed * forward;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera += speed * right;
        aim += speed * right;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera -= speed * right;
        aim -= speed * right;
    }

    glfwGetCursorPos(window, &mousex, &mousey);
   
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        last_mouse_event = 0;
   
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (last_mouse_event == 0)
        {
            mousex_last = mousex;
            mousey_last = mousey;
            last_mouse_event = 1;           
        }
        else
        {   
            float xdiff = (mousex - mousex_last)/width;
            float ydiff = (mousey - mousey_last)/height;
            
            float sensitivity = 50.0f; // Tune sensitivity
            yaw += xdiff * sensitivity;
            pitch -= ydiff * sensitivity; // Invert Y for natural movement

            pitch = glm::clamp(pitch, -89.0f, 89.0f); // Prevent flipping
            
            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

            aim = camera + direction;
            
            mousex_last = mousex;
            mousey_last = mousey;
        }
        
    }
    // std::cout << "AIM: " << aim.x << ", " << aim.y << ", " << aim.z << ", (mousex =" << mousex << std::endl;
}

int main()
{

    const std::string path = "data/data.npy";
    std::cout << "READING: " << path << std::endl;
    npy::npy_data d = npy::read_npy<float>(path);
    d.fortran_order = true;

    std::vector<float> data = d.data;
    std::vector<unsigned long> shape = d.shape;

    // std::cout << "shape: ";
    // for(auto val: shape)
    //     std::cout << val << ", ";

    // std::cout << std::endl;
    // std::cout << "BUT FLOAT VECTOR IS SIZE " << data.size() << std::endl;
    
    // for(int j = 0; j < 4; j++)
    // {
    //     int i = j * shape[0];
    //     std::cout << data[i] << ", " ;
    // }
    
    std::cout << std::endl;
    // return 0;

    // std::vector<glm::vec4> vertices; // Create a vector of glm::vec4
    std::vector<float> vertices; // Create a vector of glm::vec4

    // Convert the column-major data into row-major
    for (size_t i = 0; i < shape[0]; ++i) {
        for (size_t j = 0; j < shape[1]; ++j) {
            size_t index = j * shape[0] + i;  // Convert column-major index
            // vertices.push_back(glm::vec4(data[index], 0.0f, 0.0f, 0.0f)); // Convert to vec4
            vertices.push_back(data[index]); // Convert to vec4
        }
    }


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
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

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  


    // std::vector<glm::vec4> vertices = {
    //     {0.1+ -0.3f, 0.3f, -1.0f, 1.0},
    //     {0.1+ 0.3f,  0.3f, -1.0f, 1.0},
    //     {0.1+ -0.3f, -0.3f, -1.0f, 1.0},
    //     {0.1+ 0.3f, -0.3f, -1.0f, 1.0},
    //     {0.1+ -0.3f, 0.3f, -0.7f, 1.0},
    //     {0.1+ 0.3f,  0.3f, -0.7f, 1.0},
    //     {0.1+ -0.3f, -0.3f, -0.7f, 1.0},
    //     {0.1+ 0.3f, -0.3f, -0.7f, 1.0},
    // };  

    //fuck it perspective

    glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, farDistance);

    glm::mat4 view = glm::lookAt(camera, aim, glm::vec3(0, 1, 0));


    glm::mat4 model = glm::mat4(1.0f);

    mvp = projection * view * model;
    

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);  
    glBindVertexArray(VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);  

    // for (const auto& vertex : vertices) {

    //     // std::cout << vertex.x << ", " << vertex.y << ", " << vertex.z << std::endl;
    //     std::cout << vertex << std::endl;
    // }

    for (size_t i = 0; i < 10; ++i) {
        std::cout << "Vertex " << i << ": "
                  << vertices[i * 4] << ", "
                  << vertices[i * 4 + 1] << ", "
                  << vertices[i * 4 + 2] << ", "
                  << vertices[i * 4 + 3] << std::endl;
    }

    // glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec4), &vertices.front(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices.front(), GL_DYNAMIC_DRAW);

    // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float)*4, (void*)0);
    glEnableVertexAttribArray(0);  

    
    const char *vertexShaderSourceGLSLCode =
        "#version 330 core\n"
        "layout (location = 0) in vec4 vertexPosition; // Expecting vec4 for each vertex\n"
        "uniform mat4 mvp;  // Model-View-Projection matrix\n"
        "out vec4 vertexColor;  // Output color to fragment shader\n"
        "void main()\n"
        "{\n"
        "    vertexColor = vec4(0.5, vertexPosition.w, 0.5, 1.0);\n"  // Pass the position directly to the fragment shader for color"
        "    gl_Position = mvp * vec4(vertexPosition.xyz, 1.0);\n"  // Apply MVP transformation"
        "}\0";

    
    const char *fragShaderSourceGLSLCode = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec4 vertexColor;\n"
        "void main()\n"
        "{\n"
            "FragColor = vertexColor;\n"
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

    glUniform1i(glGetUniformLocation(shaderProgram, "total_vertices"), vertices.size());
    glUniform1i(glGetUniformLocation(shaderProgram, "column_size"), vertices.size()/4);


    glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f, 0.2f, 0.2f, 0.5f);
    while(!glfwWindowShouldClose(window))
    {

        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }

        // remake projection
        view = glm::lookAt(camera, aim, glm::vec3(0, 1, 0));
        glm::mat4 mvp = projection * view * model;
        int mvpLocation = glGetUniformLocation(shaderProgram, "mvp");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));


        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_POINTS, 0, vertices.size());  // Each vertex is 1 float
        glPointSize(10.0f); // Set point size to 10 pixels
        glDrawArrays(GL_POINTS, 0, vertices.size()/4);  // Each vertex is 1 float

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragShader); 

    return 0;
}