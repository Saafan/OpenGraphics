#include "Graphics.h"
#include <GLFW/glfw3.h>

using namespace std;

unsigned char* pixels;
vector<Triangle> triangles;

vector<vector<Color>> image(WIDTH, vector<Color>(HEIGHT));
void init()
{
	pixels = new unsigned char[WIDTH * HEIGHT * 3];
	memset(pixels, 0, WIDTH * HEIGHT * 3);

	triangles = ReadObjModel("model/african_head.obj", WIDTH, HEIGHT);
	TranslateModel(triangles, Vector3{ WIDTH / 2 , HEIGHT / 2, 0.0f });
	for (auto& triangle : triangles)
		RasterizeTriangle(triangle, image);

	ConvertTo1D(image, pixels);
}

int main()
{
	if (glfwInit() == GLFW_FALSE)
		cout << "GLFW Initialization Failed!" << endl;


	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GLFW", nullptr, nullptr);

	if (!window)
		cout << "Couldn't Open Window!" << endl;

	glfwMakeContextCurrent(window);
	init();
	// PrintMatrix(image);
	while (!glfwWindowShouldClose(window))
	{
		checkGLError();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	return 0;
}
