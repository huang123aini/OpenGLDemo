/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-06-28 10:32:07
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-05 14:45:13
 * @FilePath: /OpenGL_Demo/Mac/01_bowl/BowlModel.h
 */
#pragma once

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <memory>
#include <vector>

#include "../common/Shader.h"
#include "BowlMapping.h"

class BowlModel {
 public:
  BowlModel();
  ~BowlModel();

  void update();

  void setTextureId(unsigned int textureId);

  void renderMeshOnly();
  void renderMeshTexture();

 private:
  std::unique_ptr<BowlMapping> bowl_mapping_;
  std::unique_ptr<Shader> shader_mesh_only_;
  std::unique_ptr<Shader> shader_mesh_texture_;

  unsigned int VBO, VAO, EBO;

  unsigned int texture_id_ = -1;
};