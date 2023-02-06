#include "Graphics.h"

using namespace std;

bool IntersectTriangle(Triangle& triangle, Vector3 point)
{
	Vector3& a = triangle.vertices[0];
	Vector3& b = triangle.vertices[1];
	Vector3& c = triangle.vertices[2];

	Vector3 ca = c - a;
	Vector3 ba = b - a;
	Vector3 pa = point - a;

	float weight1 = ((a.x * ca.y) + (pa.y * ca.x) - (point.x * ca.y)) / ((ba.y * ca.x) - (ba.x * ca.y));
	float weight2 = (point.y - a.y - (weight1 * ba.y)) / (ca.y);
	return weight1 >= 0 && weight2 >= 0 && (weight1 + weight2) <= 1;
}

Vector3 lightPos{ 500, 500, -2000 };

void RasterizeTriangle(Triangle& triangle, Image& image)
{
	Vector3& v1 = triangle.vertices[0];
	Vector3& v2 = triangle.vertices[1];
	Vector3& v3 = triangle.vertices[2];

	DrawLine(v1, v2, image, Color{ 255,255,255 });
	DrawLine(v2, v3, image, Color{ 255,255,255 });
	DrawLine(v1, v3, image, Color{ 255,255,255 });

	Vector3 v1v2Dir = v2 - v1;
	Vector3 v1v3Dir = v3 - v1;
	Vector3 normal = v1v2Dir % v1v3Dir;
	normal = normal + v1;
	normal.Normalize();
	Vector3 lightDir = lightPos - v1;
	lightDir = Vector3{ 0.0f, 0.5f, 1.5f };
	lightDir = lightDir + v1;
	lightDir.Normalize();
	float lightIntensity = clamp((normal ^ lightDir), 0.0f, 1.0f) * 255.0f;

	DrawLine(v1, v1 + normal, image, Color{ 255,0,0 });
	Color c = { lightIntensity, lightIntensity, lightIntensity };

	Vector3 bottomLeft = Vector3{ min(v1.x,min(v2.x,v3.x)) , min(v1.y,min(v2.y,v3.y)), 0 };
	Vector3 topRight = Vector3{ max(v1.x,max(v2.x,v3.x)) , max(v1.y,max(v2.y,v3.y)), 0 };

	for (int i = bottomLeft.x; i < topRight.x; i++)
		for (int j = bottomLeft.y; j < topRight.y; j++)
			if (i < 0 || i >= WIDTH || j < 0 || j >= HEIGHT)
				continue;
			else if (IntersectTriangle(triangle, Vector3{ (float)i,(float)j,0 }))
				image[i][j] = c;


}



void DrawLine(Vector3 v1, Vector3 v2, Image& image, Color c)
{
	float a = v2.x - v1.x, b = v2.y - v1.y;
	float distance = 1 / Distance(v1, v2);


	for (float t = 0; t <= 1; t += distance)
	{
		const int x = v1.x + a * t;
		const int y = v1.y + b * t;

		if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
			image[x][y] = c;
	}
}


void ConvertTo1D(vector<vector<Color>>& image, unsigned char* pixels)
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

void PrintMatrix(vector<vector<Color>>& image)
{
	for (size_t i = 0; i < image.size(); i++)
	{
		for (size_t j = 0; j < image[0].size(); j++)
			cout << "(" << (int)image[i][j].r << " , " << (int)image[i][j].g << " , " << (int)image[i][j].b << ")"
			<< " ";

		cout << endl;
	}
}



void checkGLError() {
	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR) {
		string errorString;
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





vector<Triangle> ReadObjModel(string file, int scalingFactorX, int scalingFactorY)
{
	vector<Vector3> vertices;
	vector<Triangle> triangles;
	ifstream objFile(file);
	if (!objFile.is_open())
		cerr << "Error: Could not open file." << endl;

	string line;
	while (getline(objFile, line))
	{
		istringstream lineStream(line);
		string lineType;
		lineStream >> lineType;

		if (lineType == "v")
		{
			float x, y, z;
			lineStream >> x >> y >> z;
			vertices.push_back(Vector3{ x * (scalingFactorX / 2),y * (scalingFactorY / 2),z });
		}
		else if (lineType == "f")
		{
			unsigned int a, b, c;
			char discard;
			unsigned int discardI;
			lineStream >> a >> discard >> discardI >> discard >> discardI
				>> b >> discard >> discardI >> discard >> discardI >> c;
			triangles.push_back(Triangle{ vertices[a - 1], vertices[b - 1], vertices[c - 1] });
		}
	}


	objFile.close();
	return triangles;
}

float Distance(Vector3& v1, Vector3& v2)
{
	return sqrt(powf((v1.x - v2.x), 2) + powf((v1.y - v2.y), 2));
}

void TranslateTriangle(Triangle& triangle, Vector3& vec)
{
	for (auto& vertex : triangle.vertices)
	{
		vertex.x += vec.x;
		vertex.y += vec.y;
		vertex.z += vec.z;
	}
}

void TranslateModel(vector<Triangle>& triangles, Vector3 vec)
{
	for (auto& triangle : triangles)
		TranslateTriangle(triangle, vec);
}