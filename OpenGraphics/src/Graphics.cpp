#include "Graphics.h"

using namespace std;


void RasterizeTriangle(Triangle& triangle, Image& image)
{
	Vertex& v1 = triangle.vertices[0];
	Vertex& v2 = triangle.vertices[1];
	Vertex& v3 = triangle.vertices[2];


	DrawLine(v1, v2, image);
	DrawLine(v2, v3, image);
	DrawLine(v1, v3, image);

}

void DrawLine(Vertex v1, Vertex v2, Image& image)
{
	float a = v2.x - v1.x, b = v2.y - v1.y;
	float distance = 1 / Distance(v1, v2);


	for (float t = 0; t <= 1; t += distance)
	{
		const int x = v1.x + a * t;
		const int y = v1.y + b * t;

		image[x][y].r = 255;
	}
}


void ConvertTo1D(vector<vector<Pixel>>& image, unsigned char* pixels)
{
	memset(pixels, 0, WIDTH * HEIGHT * 3);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int index = (y * WIDTH + x) * 3;
			pixels[index] = image[x][y].r;
			pixels[index + 1] = image[x][y].g;
			pixels[index + 2] = image[x][y].b;
		}
	}
}

void PrintMatrix(vector<vector<Pixel>>& image)
{
	for (size_t i = 0; i < image.size(); i++)
	{
		for (size_t j = 0; j < image[0].size(); j++)
			cout << "(" << (int)image[i][j].r << " , " << (int)image[i][j].g << " , " << (int)image[i][j].b << ")"
			<< " ";

		cout << endl;
	}
}



void checkGLError(){
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::string errorString;
		switch (error) {
		case GL_INVALID_ENUM:
			errorString = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_VALUE:
			errorString = "GL_INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION:
			errorString = "GL_INVALID_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			errorString = "GL_OUT_OF_MEMORY";
			break;
		default:
			errorString = "UNKNOWN_ERROR";
			break;
		}
		cout << "OpenGL Error: " << errorString.c_str() << endl;
	}
}


float Distance(Vertex& v1, Vertex& v2)
{
	return sqrt(powf((v1.x - v2.x), 2) + powf((v1.y - v2.y), 2));
}