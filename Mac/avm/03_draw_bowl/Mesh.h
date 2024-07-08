#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

typedef struct V2_T0 {
  float x;
  float y;
  float t0x;
  float t0y;
} V2_T0;

class Mesh {
 public:
  Mesh();
  ~Mesh();
  void createQuadMesh(float x, float y, float w, float h);

  unsigned int getVao() { return VAO; }

 private:
  unsigned int VBO, VAO, EBO;
};