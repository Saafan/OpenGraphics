#include <vector>
#include <iostream>
#include <GLEW/glew.h>

const int WIDTH = 800;
const int HEIGHT = 600;

using namespace std;




struct Pixel
{
    unsigned char r = 0, g = 0, b = 0;
};

struct Vertex
{
    float x = 0, y = 0, z = 0;
    Pixel pixel;
};

struct Triangle
{
    Triangle(Vertex v1, Vertex v2, Vertex v3)
    {
        vertices[0] = v1;
        vertices[1] = v2;
        vertices[2] = v3;
    }
    Vertex vertices[3];
};

typedef vector<vector<Pixel>> Image;

void checkGLError();

float Distance(Vertex& v1, Vertex& v2);
void DrawLine(Vertex v1, Vertex v2, Image& image);
void ConvertTo1D(vector<vector<Pixel>>& image, unsigned char* pixels);
void RasterizeTriangle(Triangle& triangle, Image& image);
void PrintMatrix(vector<vector<Pixel>>& image);
