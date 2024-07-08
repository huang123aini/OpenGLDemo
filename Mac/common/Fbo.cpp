/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-07-03 14:24:46
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-03 14:38:44
 * @FilePath: /OpenGL_Demo/Mac/avm/01_uyvy_to_fbo/Fbo.cpp
 */
#include "Fbo.h"

#include <iostream>

Fbo::Fbo(int width, int height) : width_(width), height_(height) {
  createFbo(width, height);
}

Fbo::~Fbo() {
  if (fbo_) {
    glDeleteFramebuffers(1, &fbo_);
    fbo_ = 0;
  }
  if (fbo_texture_) {
    glDeleteTextures(1, &fbo_texture_);
    fbo_texture_ = 0;
  }
}

void Fbo::createFbo(int width, int height) {
  GLuint framebuffer;
  glGenFramebuffers(1, &framebuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

  GLuint fboTexture;
  glGenTextures(1, &fboTexture);
  glBindTexture(GL_TEXTURE_2D, fboTexture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)width, (int)height, 0, GL_BGRA,
               GL_UNSIGNED_BYTE, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         fboTexture, 0);

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

  if (status != GL_FRAMEBUFFER_COMPLETE) {
    printf("GL_FRAMEBUFFER_COMPLETE is Error. \n");
  }

  glBindTexture(GL_TEXTURE_2D, 0);

  fbo_texture_ = fboTexture;
  fbo_ = framebuffer;
}
void Fbo::bindFBO() {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
  glViewport(0, 0, width_, height_);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

GLuint Fbo::getFbo() { return fbo_; }
GLuint Fbo::getFboTexture() { return fbo_texture_; }
void Fbo::unbindFBO() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }