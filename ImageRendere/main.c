/*
 *
 * gcc .\main.c .\glad.c -lopengl32 -lglfw3 -lgdi32
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>

// Graphics Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
	int rezX, rezY;
	int **buffer;
	char* windowName;
} WindowSpecs;

int createWindow(WindowSpecs* windowSpecs);
int readImage(WindowSpecs* windowSpecs);
void cleanup();
int check_usage(int argc, char** argv);

int main(int argc, char** argv)
{
	check_useage(argc, argv);

	WindowSpecs windowSpecs = {
		800, 
		600,
		NULL,
		argv[1],
	};

	readImage(&windowSpecs);
	int retVal = createWindow( &windowSpecs );
	cleanup();
	return 0;
}

int createWindow(WindowSpecs* windowSpecs)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Require X Y for image
	GLFWwindow* window = glfwCreateWindow(
			windowSpecs->rezX, windowSpecs->rezY,
			windowSpecs->windowName, NULL, NULL );

	if( !window  ) {
		printf("Faild to create a window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	// Innitializing GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	// Require X Y for image
	// Viewport shows 
	glViewport(0, 0, windowSpecs->rezX, windowSpecs->rezY);

	while( !glfwWindowShouldClose(window) ) {
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
	return 0;
}

int readImage(WindowSpecs* windowSpecs)
{
	FILE* fp = fopen(windowSpecs->windowName, "rb");
	if( !fp ) {
		printf("Could not open image [%s]. Aborting...\n",
				windowSpecs->windowName);
		return errno;
	}
		
}

void cleanup()
{
	glfwTerminate();
}

int check_usage(int argc, char** argv)
{
	if( argc != 2 ) {
		printf("Improper useage\n"
		"\tUseage: [program name] [image name]\n"
		"Image should be in same directory\n");
		return 1;
	}
}
