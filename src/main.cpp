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

    unsigned char* data = new unsigned char[100 * 100 * 3];
    for (int y = 0; y < 100; ++y)
    {
        for (int x = 0; x < 100; ++x)
        {
            data[100 * y *3 + x * 3    ] = 0xff;
            data[100 * y *3 + x * 3 + 1] = 0x00;
            data[100 * y *3 + x * 3 + 2] = 0x00;
        }
    }
    for (int y = 25; y < 75; ++y)
    {
        for (int x = 25; x < 75; ++x)
        {
            data[100 * y *3 + x * 3    ] = 0x00;
            data[100 * y *3 + x * 3 + 1] = 0x00;
            data[100 * y *3 + x * 3 + 2] = 0xff;
        }
    }
    glfwMakeContextCurrent(window);

    GLuint tex_handle;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 100, 100, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // set up orthographic projection
        int window_width, window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window_width, 0, window_height, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        // render whatever we want
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glBegin(GL_QUADS);
            glTexCoord2d(0,0); glVertex2i(0,0);
            glTexCoord2d(1,0); glVertex2i(100,0);
            glTexCoord2d(1,1); glVertex2i(100,100);
            glTexCoord2d(0,1); glVertex2i(0,100);
        glEnd();
        glDisable(GL_TEXTURE_2D);


        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    return 0;
}