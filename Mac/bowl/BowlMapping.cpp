/*
 * @Author: huang123aini aiya123aini@163.com
 * @Date: 2024-06-28 10:47:21
 * @LastEditors: huang123aini aiya123aini@163.com
 * @LastEditTime: 2024-07-05 13:47:23
 * @FilePath: /OpenGL_Demo/Mac/01_bowl/BowlMapping.cpp
 */
#include "BowlMapping.h"

#include <cmath>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/optimum_pow.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "AvmConfig.h"

float pai = 3.141592657932385f;

const float ANGLE = 10.0f;

// bowl model
const unsigned int WIDTH_NUMBER = 40;

const unsigned int LENGTH_NUMBER = 40;

const unsigned int ANGLE_NUMBER = 40;

const unsigned int ROTATION_NUMBER = 30;

const unsigned int HIGH_NUMBER = 15;

// car
const float CAR_LENGTH = 4.950f;
const float CAR_WIDTH = 2.25f;

const float EPSILON = 1e-9;  // 比如说，接受1e-9以内的误差

float fellipse(float a, float b, float x) {
  if (std::fabs(a - x) < EPSILON) {
    return 0.0f;
  }

  float temp = 1.0f - glm::pow2(x) / glm::pow2(a);
  float y = std::pow(glm::pow2(b) * temp, 0.5);
  return y;
}

void BowlMapping::buildEachPoint(float wr, float wrr, float wz) {
  APointTex point{};
  point.world_z = wz;

  // front
  std::vector<APointTex> FrontpointTemp;
  FrontpointTemp.clear();
  point.world_x = CAR_LENGTH / 2.0f + wrr;
  float y_begin = CAR_WIDTH / 2.0f + wrr * glm::sin(glm::radians(ANGLE));
  float y_end = -CAR_WIDTH / 2.0f - wrr * glm::sin(glm::radians(ANGLE));
  float dy = (y_begin - y_end) / WIDTH_NUMBER;
  for (unsigned int j = 0; j <= WIDTH_NUMBER; ++j) {
    point.world_y = y_begin - dy * j;
    calculatePointToUV(point, MAKE_FRONT_CONFIG);
    FrontpointTemp.push_back(point);
  }
  mFrontPointBuffer.push_back(FrontpointTemp);

  // front_right
  std::vector<APointTex> FrontRightpointTemp;
  FrontRightpointTemp.clear();
  APointTex pointa = FrontpointTemp[WIDTH_NUMBER];
  calculatePointToUV(pointa, MAKE_RIGHT_CONFIG);
  FrontRightpointTemp.push_back(pointa);
  float da = (pai / 2.0f - 2.0f * glm::radians(ANGLE)) / ANGLE_NUMBER;
  for (unsigned int j = 1; j <= ANGLE_NUMBER; ++j) {
    float a = wrr;
    float b = wr;
    float x = wrr * glm::cos(glm::radians(ANGLE) + j * da);
    point.world_x = CAR_LENGTH / 2.0f + x;
    point.world_y = -CAR_WIDTH / 2.0f - fellipse(a, b, x) -
                    wrr * glm::sin(glm::radians(ANGLE));
    calculatePointToUV(point, MAKE_RIGHT_CONFIG);
    FrontRightpointTemp.push_back(point);
  }
  mFrontRightPointBuffer.push_back(FrontRightpointTemp);
  // right
  std::vector<APointTex> RightpointTemp;
  RightpointTemp.clear();
  point.world_y = -CAR_WIDTH / 2.0f - wr - wrr * glm::sin(glm::radians(ANGLE));
  float x_begin = CAR_LENGTH / 2.0f;
  float x_end = -CAR_LENGTH / 2.0f;
  float dx = (x_begin - x_end) / LENGTH_NUMBER;
  for (unsigned int j = 0; j <= LENGTH_NUMBER; ++j) {
    point.world_x = x_begin - dx * j;
    calculatePointToUV(point, MAKE_RIGHT_CONFIG);
    RightpointTemp.push_back(point);
  }
  mRightPointBuffer.push_back(RightpointTemp);

  // back_right
  std::vector<APointTex> BackRightpointTemp;
  BackRightpointTemp.clear();
  for (unsigned int j = 0; j <= ANGLE_NUMBER; ++j) {
    point.world_x = -FrontRightpointTemp[ANGLE_NUMBER - j].world_x;
    point.world_y = FrontRightpointTemp[ANGLE_NUMBER - j].world_y;
    calculatePointToUV(point, MAKE_RIGHT_CONFIG);
    BackRightpointTemp.push_back(point);
  }
  mBackRightPointBuffer.push_back(BackRightpointTemp);

  // back
  std::vector<APointTex> BackpointTemp;
  BackpointTemp.clear();
  point.world_x = -CAR_LENGTH / 2.0f - wrr;
  y_begin = -CAR_WIDTH / 2.0f - wrr * glm::sin(glm::radians(ANGLE));
  y_end = CAR_WIDTH / 2.0f + wrr * glm::sin(glm::radians(ANGLE));
  dy = (y_begin - y_end) / WIDTH_NUMBER;
  for (unsigned int j = 0; j <= WIDTH_NUMBER; ++j) {
    point.world_y = y_begin - dy * j;
    calculatePointToUV(point, MAKE_REAR_CONFIG);
    BackpointTemp.push_back(point);
  }
  mBackPointBuffer.push_back(BackpointTemp);

  // back_left
  std::vector<APointTex> BackLeftpointTemp;
  BackLeftpointTemp.clear();
  for (unsigned int j = 0; j <= ANGLE_NUMBER; ++j) {
    point.world_x = -FrontRightpointTemp[j].world_x;
    point.world_y = -FrontRightpointTemp[j].world_y;
    calculatePointToUV(point, MAKE_LEFT_CONFIG);
    BackLeftpointTemp.push_back(point);
  }
  mBackLeftPointBuffer.push_back(BackLeftpointTemp);

  // left
  std::vector<APointTex> LeftpointTemp;
  point.world_y = CAR_WIDTH / 2.0f + wr + wrr * glm::sin(glm::radians(ANGLE));
  x_begin = -CAR_LENGTH / 2.0f;
  x_end = CAR_LENGTH / 2.0f;
  dx = (x_begin - x_end) / LENGTH_NUMBER;
  LeftpointTemp.clear();
  for (unsigned int j = 0; j <= LENGTH_NUMBER; ++j) {
    point.world_x = x_begin - dx * j;
    calculatePointToUV(point, MAKE_LEFT_CONFIG);
    LeftpointTemp.push_back(point);
  }
  mLeftPointBuffer.push_back(LeftpointTemp);

  // front_left
  std::vector<APointTex> FrontLeftpointTemp;
  FrontLeftpointTemp.clear();
  for (unsigned int j = 0; j <= ANGLE_NUMBER; ++j) {
    point.world_x = FrontRightpointTemp[ANGLE_NUMBER - j].world_x;
    point.world_y = -FrontRightpointTemp[ANGLE_NUMBER - j].world_y;
    calculatePointToUV(point, MAKE_LEFT_CONFIG);
    FrontLeftpointTemp.push_back(point);
  }
  mFrontLeftPointBuffer.push_back(FrontLeftpointTemp);
}

void BowlMapping::buildBowlPoint(float rotation) {
  mFrontPointBuffer.clear();
  mFrontRightPointBuffer.clear();
  mRightPointBuffer.clear();
  mBackRightPointBuffer.clear();
  mBackPointBuffer.clear();
  mBackLeftPointBuffer.clear();
  mLeftPointBuffer.clear();
  mFrontLeftPointBuffer.clear();

  if (mBowlMode == BowlMode::REMOTE) {
    for (unsigned int i = 0; i < ROTATION_NUMBER; ++i) {
      float dr = rotation / ROTATION_NUMBER;
      buildEachPoint(i * dr, i * dr * 3.5f, 0.0f);
    }
    for (unsigned int i = 0; i < HIGH_NUMBER; ++i) {
      float dr = rotation / HIGH_NUMBER;
      buildEachPoint(rotation + i * dr, (rotation + i * dr) * 3.5f,
                     pow(i * dr, 3));
    }
  } else {
    for (unsigned int i = 0; i < ROTATION_NUMBER; ++i) {
      float dr = rotation / ROTATION_NUMBER;
      buildEachPoint(i * dr, i * dr * 3.5f, 0.0f);
    }
    for (unsigned int i = 0; i < HIGH_NUMBER; ++i) {
      float dr = rotation / HIGH_NUMBER;
      buildEachPoint(rotation + i * dr, (rotation + i * dr) * 3.5f,
                     pow(10, i * dr) - 1.0f);
    }
  }

  mBowlPointBuffer.clear();
  for (unsigned int i = 0; i < ROTATION_NUMBER + HIGH_NUMBER - 1; ++i) {
    std::vector<APointTex> eachPointBuffer;
    for (unsigned int j = 0; j <= WIDTH_NUMBER; ++j) {
      eachPointBuffer.push_back(mFrontPointBuffer[i][j]);
    }
    for (unsigned int j = 0; j <= ANGLE_NUMBER; ++j) {
      eachPointBuffer.push_back(mFrontRightPointBuffer[i][j]);
    }
    for (unsigned int j = 0; j <= LENGTH_NUMBER; ++j) {
      eachPointBuffer.push_back(mRightPointBuffer[i][j]);
    }
    for (unsigned int j = 0; j <= ANGLE_NUMBER; ++j) {
      eachPointBuffer.push_back(mBackRightPointBuffer[i][j]);
    }
    for (unsigned int j = 0; j <= WIDTH_NUMBER; ++j) {
      eachPointBuffer.push_back(mBackPointBuffer[i][j]);
    }
    for (unsigned int j = 0; j <= ANGLE_NUMBER; ++j) {
      eachPointBuffer.push_back(mBackLeftPointBuffer[i][j]);
    }
    for (unsigned int j = 0; j <= LENGTH_NUMBER; ++j) {
      eachPointBuffer.push_back(mLeftPointBuffer[i][j]);
    }
    for (unsigned int j = 0; j <= ANGLE_NUMBER; ++j) {
      eachPointBuffer.push_back(mFrontLeftPointBuffer[i][j]);
    }
    mBowlPointBuffer.push_back(eachPointBuffer);
  }

  mBowlIndexBuffer.clear();
  int move = mBowlPointBuffer[0].size();
  for (size_t i = 0; i < mBowlPointBuffer.size() - 1; ++i) {
    for (size_t j = 0; j < mBowlPointBuffer[i].size() - 1; ++j) {
      mBowlIndexBuffer.push_back(move * i + j);
      mBowlIndexBuffer.push_back(move * i + move + j);
      mBowlIndexBuffer.push_back(move * i + j + 1);
      mBowlIndexBuffer.push_back(move * i + move + j);
      mBowlIndexBuffer.push_back(move * i + j + 1);
      mBowlIndexBuffer.push_back(move * i + move + j + 1);
    }
  }
}

void BowlMapping::getPointBuffer(std::vector<float> &pointBuffer) {
  pointBuffer.clear();
  for (int i = 0; i < mBowlPointBuffer.size(); ++i) {
    for (int j = 0; j < mBowlPointBuffer[i].size(); ++j) {
      pointBuffer.push_back(mBowlPointBuffer[i][j].world_x);
      pointBuffer.push_back(mBowlPointBuffer[i][j].world_y);
      pointBuffer.push_back(mBowlPointBuffer[i][j].world_z);
      pointBuffer.push_back(mBowlPointBuffer[i][j].texture_u);
      pointBuffer.push_back(mBowlPointBuffer[i][j].texture_v);
    }
  }
}

void BowlMapping::getIndexBuffer(std::vector<unsigned short> &indexBuffer) {
  indexBuffer.assign(mBowlIndexBuffer.begin(), mBowlIndexBuffer.end());
}

std::int32_t BowlMapping::getPointNumber() {
  return mBowlPointBuffer.size() * mBowlPointBuffer[0].size();
}

std::int32_t BowlMapping::getIndexCount() { return mBowlIndexBuffer.size(); }

void BowlMapping::calculatePointToUV(APointTex &point, CAR_CONFIG type) {
  /* 1.获取观察矩阵 世界坐标-->摄像机空间 */
  glm::mat4 viewMatrix = ACFG->getCameraMat44(type);

  /* 2.获取相机参数 */
  CarCameraConfig cameraConfig = ACFG->getCameraConfig(type);
  float halfWheelbase = ACFG->getMoveLength();

  /* 2.计算摄像机空间下坐标 */
  glm::vec4 camera_point =
      viewMatrix * glm::vec4(point.world_x + halfWheelbase, point.world_y,
                             point.world_z, 1.0f);

  /* 3.归一化像素坐标 */
  float x1 =
      camera_point.x /
      (camera_point.z + glm::distance(glm::vec3(camera_point), glm::vec3(0.0)) *
                            cameraConfig.xi);
  float y1 =
      camera_point.y /
      (camera_point.z + glm::distance(glm::vec3(camera_point), glm::vec3(0.0)) *
                            cameraConfig.xi);
  float r2 = pow(x1, 2) + pow(y1, 2);

  /* 4.计算径向形变 */
  float radial_ret_x = x1 * (1.0f + cameraConfig.distortion1 * r2 +
                             cameraConfig.distortion2 * pow(r2, 2));
  float radial_ret_y = y1 * (1.0f + cameraConfig.distortion1 * r2 +
                             cameraConfig.distortion2 * pow(r2, 2));

  /* 5.计算切向形变 */
  float tangential_ret_x = 2.0 * cameraConfig.distortion3 * x1 * y1 +
                           cameraConfig.distortion4 * (r2 + 2.0 * pow(x1, 2));
  float tangential_ret_y = 2.0 * cameraConfig.distortion4 * x1 * y1 +
                           cameraConfig.distortion3 * (r2 + 2.0 * pow(y1, 2));

  /* 6.像素坐标校准 */
  float ret_x = radial_ret_x + tangential_ret_x;
  float ret_y = radial_ret_y + tangential_ret_y;

  /* 7.计算UV值 */
  float u =
      (cameraConfig.fx * ret_x + cameraConfig.cx) / cameraConfig.image_width;
  float v =
      (cameraConfig.fy * ret_y + cameraConfig.cy) / cameraConfig.image_height;
  float deviation_v = 0.0f;
  if (type == MAKE_FRONT_CONFIG) {
    deviation_v = 0.0f;
  } else if (type == MAKE_RIGHT_CONFIG) {
    deviation_v = 0.25f;
  } else if (type == MAKE_REAR_CONFIG) {
    deviation_v = 0.5f;
  } else if (type == MAKE_LEFT_CONFIG) {
    deviation_v = 0.75f;
  }

  /* 8.UV有效性检查 */
  if ((u >= 0 && u <= 1) && (v >= 0 && v <= 1)) {
    point.texture_u = u;
    point.texture_v = v / 4.0f + deviation_v;
  } else {
    point.texture_u = 0.0;
    point.texture_v = 0.0;
  }
}
