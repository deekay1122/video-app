#include <iostream>
#include <GLFW/glfw3.h>

bool load_frame(const char* filename, int* width, int* height, unsigned char** data);

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

    int frame_width, frame_height;
    unsigned char* frame_data;
    if (!load_frame("/Users/ejiridaisaku/Desktop/BluesInBb.mp4", &frame_width, &frame_height, &frame_data))
    {
        std::cout << "couldnt load video frame" << std::endl;
        return 1;
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // set up orthographic projection
        int window_width, window_height;
        glfwGetFramebufferSize(window, &window_width, &window_height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, window_width, window_height, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        // render whatever we want
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_handle);
        glBegin(GL_QUADS);
            glTexCoord2d(0,0); glVertex2i(200,200);
            glTexCoord2d(1,0); glVertex2i(200 + frame_width, 200);
            glTexCoord2d(1,1); glVertex2i(200 + frame_width, 200 + frame_height);
            glTexCoord2d(0,1); glVertex2i(200, 200 + frame_height);
        glEnd();
        glDisable(GL_TEXTURE_2D);


        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    return 0;
}