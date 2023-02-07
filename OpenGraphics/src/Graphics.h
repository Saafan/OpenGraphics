#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <GLEW/glew.h>

const int WIDTH = 800;
const int HEIGHT = 600;

using namespace std;




struct Color
{
    unsigned char r = 0, g = 0, b = 0;
};

struct Vector3
{
    float x = 0, y = 0, z = 0;
    Color pixel;

    Vector3 operator-(Vector3& b)
    {
        Vector3 res;
        res.x = x - b.x;
        res.y = y - b.y;
        res.z = z - b.z;
        return res;
    }
    
    Vector3 operator+(Vector3& b)
    {
        Vector3 res;
        res.x = x + b.x;
        res.y = y + b.y;
        res.z = z + b.z;
        return res;
    }
    
    Vector3 operator*(Vector3& b)
    {
        Vector3 res;
        res.x = x * b.x;
        res.y = y * b.y;
        res.z = z * b.z;
        return res;
    }

    float operator^(Vector3& b) //Dot Product
    {
        return ((x * b.x) + (y * b.y) + (z * b.z));
    }

    Vector3 operator%(Vector3& b) //Cross Product
    {
        Vector3 res;
        res.x = y * b.z - z * b.y;
        res.y = z * b.x - x * b.z;
        res.z = x * b.y - y * b.x;
        return res;
    }

    float Magnitude()
    {
        return sqrt(x * x + y * y + z * z);
    }

    void Normalize()
    {
        float magn = Magnitude();
        x /= magn;
        y /= magn;
        z /= magn;
    }

};

struct Triangle
{
    Triangle(Vector3 v1, Vector3 v2, Vector3 v3)
    {
        vertices[0] = v1;
        vertices[1] = v2;
        vertices[2] = v3;
    }
    Vector3 vertices[3];
};

typedef vector<vector<Color>> Image;

void checkGLError();

vector<Triangle> ReadObjModel(string file, int scalingFactor);
float Distance(Vector3& v1, Vector3& v2);

bool IntersectTriangle(Triangle& triangle, Vector3 point);

void DrawLine(Vector3 v1, Vector3 v2, Image& image, Color c);
void ConvertTo1D(vector<vector<Color>>& image, unsigned char* pixels);
void RasterizeTriangle(Triangle& triangle, Image& image);
void PrintMatrix(vector<vector<Color>>& image);


void TranslateTriangle(Triangle& triangle, Vector3& vec);
void TranslateModel(vector<Triangle>& triangles, Vector3 vec);

void RotateMode(vector<Triangle>& triangles, Vector3 angles);