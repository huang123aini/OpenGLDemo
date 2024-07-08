#pragma once

#ifndef AVM_ACONFIG_H
#define AVM_ACONFIG_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct ARota {
  float yaw;
  float pitch;
  float roll;
  ARota() {
    yaw = 0.0f;
    pitch = 0.0f;
    roll = 0.0f;
  }
};

struct APoint {
  float x;
  float y;
  float z;
  APoint() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }
};

struct CarCameraConfig {
  int name;
  float xi;
  float fx;
  float fy;
  float cx;
  float cy;
  float distortion1;
  float distortion2;
  float distortion3;
  float distortion4;
  int image_width;
  int image_height;
  int image_format;
  ARota rotation;
  APoint translation;
};

// 车身数据
struct CarConfig {
  float wheelbase;         // 轴距
  float wheeltrackF;       // 前轮距
  float wheeltrackR;       // 后轮距
  float overhangF;         // 车头到前轴的距离
  float overhangR;         // 车尾到后轴的距离
  float wheeldiameter;     // 轮子直径
  float wheelwidth;        // 轮子宽度
  float overalllength;     // 汽车长度
  float overallwidth;      // 汽车宽度
  float overallhigh;       // 汽车宽度
  float minturningradius;  //
  float maxgradeability;
  float maxsteeringangle;          // 最大方向盘转角
  float steer_transmission_ratio;  // 方向盘转角轮转角转换率
};

struct ACarTransform {
  glm::vec3 pos;
  glm::vec3 scale;
  glm::vec3 rot;
};

enum CAR_CONFIG {
  MAKE_EMPTY_CONFIG = 0,
  MAKE_FRONT_CONFIG,
  MAKE_RIGHT_CONFIG,
  MAKE_REAR_CONFIG,
  MAKE_LEFT_CONFIG,
};

#define ACFG AVMConfig::getIns()

class AVMConfig {
  friend class AVMParseAVM;

 public:
  static AVMConfig *_s_cfg_ins;
  static AVMConfig *getIns();

  // 模型的缩放尺寸
  static float m_car_model_scale;
  static float transition(float _v);

  AVMConfig();
  ~AVMConfig();

  void init();

  void addCameraDefaultConfig();

  std::vector<CarCameraConfig> car_camera_configs;

  inline int getWidth() { return mWidth; }
  inline int getHeight() { return mHeight; }

  inline int getCameraWidth() { return mCameraWidth; }
  inline int getCameraHeight() { return mCameraHeight; }

  inline int getSeparatorWidth() { return mSeparatorWidth; }

  inline int getLeftSceneX() { return mLeftSceneX; }
  inline int getLeftSceneY() { return mLeftSceneY; }
  inline int getLeftSceneWidth() { return mLeftSceneWidth; }
  inline int getLeftSceneHeight() { return mLeftSceneHeight; }

  inline int getRightSceneX() { return mRightSceneX; }
  inline int getRightSceneY() { return mRightSceneY; }
  inline int getRightSceneWidth() { return mRightSceneWidth; }
  inline int getRightSceneHeight() { return mRightSceneHeight; }

  // 返回视点，用于构建相机
  //   ABool getViewData(ACChars _type, ViewData &mViewData);

  //   ACChars getSourcePath();
  //   ACChars getSourcePathGUI();

  //   ACChars getCameraDataPath();
  //   void setCameraDataPath(ACChars path);

  CarCameraConfig &getCameraConfig(CAR_CONFIG type);

  CarConfig &getCarConfig();
  glm::mat4 &getCameraMat44(CAR_CONFIG type);

  inline float getCveralllengthHalf() { return mCveralllengthHalf; }
  inline float getCverallwidthHalf() { return mCverallwidthHalf; }
  inline float getMoveLength() { return mMoveLength; }

 private:
  void make_car_config();
  void make_front_config();
  void make_right_config();
  void make_back_config();
  void make_left_config();

 private:
  // 主屏幕宽高
  int mWidth;
  int mHeight;
  // 鱼眼摄像头宽高
  int mCameraWidth;
  int mCameraHeight;
  int mSeparatorWidth;

  int mLeftSceneX;
  int mLeftSceneY;
  int mLeftSceneWidth;
  int mLeftSceneHeight;
  int mRightSceneX;
  int mRightSceneY;
  int mRightSceneWidth;
  int mRightSceneHeight;

  // 四个鱼眼摄像头去畸变的矩阵
  glm::mat4 mFrontMat4;
  glm::mat4 mRightMat4;
  glm::mat4 mBackMat4;
  glm::mat4 mLeftMat4;
  // 车身信息
  float mCveralllengthHalf;
  float mCverallwidthHalf;
  float mMoveLength;

  CarConfig mCarConfig;
  CarCameraConfig mCarCameraFront;
  CarCameraConfig mCarCameraRight;
  CarCameraConfig mCarCameraBack;
  CarCameraConfig mCarCameraLeft;
  // 预设的视角
  // std::map<AString, ViewData> mEyeMap;

 public:
  std::string mCarName;

  ACarTransform mLeftCarTransform;
  ACarTransform mRightCarTransform;

  int mSampleEn;
  int mSampleInterval;
  std::string mSamplePath;
  /* 车身数据设置 */
  int mCarStaTransparent;
  /* 2d视野 */
  float m2DFrontPoint[6];
  float m2DBackPoint[6];
};

#endif  // AVM_ACONFIG_H
