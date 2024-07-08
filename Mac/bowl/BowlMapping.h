/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-06-28 10:47:10
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-05 13:51:49
 * @FilePath: /OpenGL_Demo/Mac/bowl/BowlMapping.h
 */

#pragma once

#include <vector>

#include "AvmConfig.h"

struct APointTex {
  float world_x;
  float world_y;
  float world_z;
  float texture_u;
  float texture_v;
  APointTex() {
    world_x = 0.0f;
    world_y = 0.0f;
    world_z = 0.0f;
    texture_u = 0.0f;
    texture_v = 0.0f;
  }
};

enum class BowlMode { REMOTE = 0, PARKING };

class BowlMapping {
 public:
  void buildBowlPoint(float rotation);

  void buildEachRotationPoint(float wx, float wz);

  void buildEachPoint(float wr, float wrr, float wz);

  void calculatePointToUV(APointTex &point, CAR_CONFIG type);

  void getPointBuffer(std::vector<float> &pointBuffer);

  void getIndexBuffer(std::vector<unsigned short> &indexBuffer);
  std::int32_t getPointNumber();
  std::int32_t getIndexCount();
  BowlMode mBowlMode;

 private:
  std::vector<std::vector<APointTex>> mFrontPointBuffer;

  std::vector<std::vector<APointTex>> mFrontRightPointBuffer;

  std::vector<std::vector<APointTex>> mRightPointBuffer;

  std::vector<std::vector<APointTex>> mBackRightPointBuffer;

  std::vector<std::vector<APointTex>> mBackPointBuffer;

  std::vector<std::vector<APointTex>> mBackLeftPointBuffer;

  std::vector<std::vector<APointTex>> mLeftPointBuffer;

  std::vector<std::vector<APointTex>> mFrontLeftPointBuffer;

  // 结果定点数据缓存
  std::vector<std::vector<APointTex>> mBowlPointBuffer;
  // 结果索引数据缓存
  std::vector<unsigned short> mBowlIndexBuffer;
};