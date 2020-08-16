#include <iostream>
#include <GLFW/glfw3.h>

int main ()
{
    GLFWwindow* window;
    if (!glfwInit())
    {
        std::cout << "cant initialize GLFW" << std::endl;
        return 1;
    }

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        std::cout << "couldnt open window" << std::endl;
        return 1;
    }

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window))
    {
        glfwWaitEvents();
    }
    std::cout << "Hello World!" << std::endl;

    return 0;
}