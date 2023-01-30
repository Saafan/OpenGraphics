#include "Graphics.h"
#include <GLFW/glfw3.h>

using namespace std;

unsigned char* pixels;
vector<Triangle> triangles;

vector<vector<Pixel>> image(WIDTH, vector<Pixel>(HEIGHT));
void init()
{
	pixels = new unsigned char[WIDTH * HEIGHT * 3];
	memset(pixels, 0, WIDTH * HEIGHT * 3);

	Triangle tri(Vertex{ 200, 200, 0 }, Vertex{ 300, 200, 0 }, Vertex{ 250, 300, 0 });
	triangles.push_back(tri);
	for (auto& triangle : triangles)
	{
		RasterizeTriangle(triangle, image);
	}
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
