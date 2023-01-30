#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

int main()
{
	if(!glewInit())
		cout << "Failed: GLEW Initalizatoin!" << endl;

	if (glfwInit() == GLFW_FALSE)
		cout << "Failed: GLFW Initalizatoin!" << endl;



	return 0;
}