#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

class Fbo {
 public:
  Fbo(int width, int height);
  ~Fbo();
  void bindFBO();
  void unbindFBO();

  GLuint getFbo();
  GLuint getFboTexture();

 private:
  void createFbo(int width, int height);

 private:
  GLuint fbo_;
  GLuint fbo_texture_;
  int width_;
  int height_;
};