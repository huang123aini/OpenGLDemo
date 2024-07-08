
#include "AvmConfig.h"

AVMConfig *AVMConfig::_s_cfg_ins = nullptr;
AVMConfig *AVMConfig::getIns() {
  if (_s_cfg_ins == nullptr) {
    _s_cfg_ins = new AVMConfig();
    _s_cfg_ins->init();
  }
  return _s_cfg_ins;
}

void AVMConfig::addCameraDefaultConfig() {
  CarCameraConfig carCameraFront{};
  CarCameraConfig carCameraRight{};
  CarCameraConfig carCameraBack{};
  CarCameraConfig carCameraLeft{};

  // 标定数据输入
  mCarConfig.wheelbase = 2.703f;
  mCarConfig.wheeltrackF = 1.554f;
  mCarConfig.wheeltrackR = 1.554f;
  mCarConfig.overhangF = 0.925f;
  mCarConfig.overhangR = 0.948f;
  mCarConfig.wheeldiameter = 0.701f;
  mCarConfig.wheelwidth = 0.233f;
  mCarConfig.overalllength = 4.576f;
  mCarConfig.overallwidth = 1.788f;
  mCarConfig.overallhigh = 0.0f;
  mCarConfig.minturningradius = 0.0f;
  mCarConfig.maxgradeability = 0.0f;
  mCarConfig.maxsteeringangle = 0.0f;
  mCarConfig.steer_transmission_ratio = 15.784587; /* 新增 */

  // 前
  carCameraFront.xi = 1.2254082f;
  carCameraFront.fx = 627.851929f;
  carCameraFront.fy = 628.302795f;
  carCameraFront.cx = 642.351501f;
  carCameraFront.cy = 363.658875f;
  carCameraFront.distortion1 = 0.46075666f;
  carCameraFront.distortion2 = -0.363318592f;
  carCameraFront.distortion3 = 0.00137124187f;
  carCameraFront.distortion4 = 0.0018751655f;
  carCameraFront.image_width = 1280;
  carCameraFront.image_height = 720;
  carCameraFront.image_format = 0;
  carCameraFront.rotation.yaw = -1.58011377f;
  carCameraFront.rotation.pitch = -0.011590491f;
  carCameraFront.rotation.roll = -1.83781123f;
  carCameraFront.translation.x = 3.63148785f;
  carCameraFront.translation.y = 0.0193210077f;
  carCameraFront.translation.z = 0.683597147f;

  mCarCameraFront = carCameraFront;

  // 右
  carCameraRight.xi = 1.22548974f;
  carCameraRight.fx = 625.465942f;
  carCameraRight.fy = 626.139954f;
  carCameraRight.cx = 638.865906f;
  carCameraRight.cy = 363.372314f;
  carCameraRight.distortion1 = 0.463195831f;
  carCameraRight.distortion2 = -0.367022753f;
  carCameraRight.distortion3 = 0.00196991418f;
  carCameraRight.distortion4 = -0.000852097757f;
  carCameraRight.image_width = 1280;
  carCameraRight.image_height = 720;
  carCameraRight.image_format = 0;
  carCameraRight.rotation.yaw = -3.11472702f;
  carCameraRight.rotation.pitch = 0.028744394f;
  carCameraRight.rotation.roll = -2.20842862f;
  carCameraRight.translation.x = 1.95512271f;
  carCameraRight.translation.y = -1.00031865f;
  carCameraRight.translation.z = 1.12296534f;

  mCarCameraRight = carCameraRight;

  // 后
  carCameraBack.xi = 1.22951078f;
  carCameraBack.fx = 630.048157f;
  carCameraBack.fy = 630.521729f;
  carCameraBack.cx = 634.910522f;
  carCameraBack.cy = 358.917786f;
  carCameraBack.distortion1 = 0.464009881f;
  carCameraBack.distortion2 = -0.368696541f;
  carCameraBack.distortion3 = 0.00023990075f;
  carCameraBack.distortion4 = -0.00288418122f;
  carCameraBack.image_width = 1280;
  carCameraBack.image_height = 720;
  carCameraBack.image_format = 0;
  carCameraBack.rotation.yaw = 1.57682931f;
  carCameraBack.rotation.pitch = 0.0154793123f;
  carCameraBack.rotation.roll = -2.06955218f;
  carCameraBack.translation.x = -0.903505921f;
  carCameraBack.translation.y = 0.0607340448f;
  carCameraBack.translation.z = 0.951247454f;

  mCarCameraBack = carCameraBack;

  // 左
  carCameraLeft.xi = 1.23422527f;
  carCameraLeft.fx = 628.920227f;
  carCameraLeft.fy = 629.546631f;
  carCameraLeft.cx = 636.439392f;
  carCameraLeft.cy = 360.536652f;
  carCameraLeft.distortion1 = 0.468900889f;
  carCameraLeft.distortion2 = -0.370492578f;
  carCameraLeft.distortion3 = 0.000727081555f;
  carCameraLeft.distortion4 = -0.00256385f;
  carCameraLeft.image_width = 1280;
  carCameraLeft.image_height = 720;
  carCameraLeft.image_format = 0;
  carCameraLeft.rotation.yaw = -0.00451866537f;
  carCameraLeft.rotation.pitch = 0.00639821915f;
  carCameraLeft.rotation.roll = -2.26109624f;
  carCameraLeft.translation.x = 1.9537102f;
  carCameraLeft.translation.y = 1.09413087f;
  carCameraLeft.translation.z = 1.10687876f;

  mCarCameraLeft = carCameraLeft;

  car_camera_configs.push_back(carCameraFront);
  car_camera_configs.push_back(carCameraRight);
  car_camera_configs.push_back(carCameraBack);
  car_camera_configs.push_back(carCameraLeft);

  make_front_config();
  make_right_config();
  make_back_config();
  make_left_config();
}

float AVMConfig::m_car_model_scale = 1.0f;
float AVMConfig::transition(float _v) { return _v * m_car_model_scale; }

AVMConfig::AVMConfig() { AVMConfig::m_car_model_scale = 1.0f; }

AVMConfig::~AVMConfig() {  // mEyeMap.clear();
}

void AVMConfig::init() { addCameraDefaultConfig(); }

CarCameraConfig &AVMConfig::getCameraConfig(CAR_CONFIG type) {
  switch (type) {
    case MAKE_FRONT_CONFIG:
      return mCarCameraFront;
    case MAKE_RIGHT_CONFIG:
      return mCarCameraRight;
    case MAKE_REAR_CONFIG:
      return mCarCameraBack;
    default:
      break;
  }
  return mCarCameraLeft;
}

CarConfig &AVMConfig::getCarConfig() { return mCarConfig; }

glm::mat4 &AVMConfig::getCameraMat44(CAR_CONFIG type) {
  switch (type) {
    case MAKE_FRONT_CONFIG:
      return mFrontMat4;
    case MAKE_RIGHT_CONFIG:
      return mRightMat4;
    case MAKE_REAR_CONFIG:
      return mBackMat4;
    default:
      break;
  }
  return mLeftMat4;
}

void AVMConfig::make_car_config() {
  mCveralllengthHalf = mCarConfig.overalllength * 0.5f;
  mCverallwidthHalf = mCarConfig.overallwidth * 0.5f;
  mMoveLength = mCarConfig.wheelbase / 2.0f;
}

void AVMConfig::make_front_config() {
  glm::mat4 rot_p(1.0f);
  rot_p = glm::rotate(rot_p, mCarCameraFront.rotation.pitch,
                      glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 rot_y(1.0f);
  rot_y = glm::rotate(rot_y, mCarCameraFront.rotation.yaw,
                      glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 rot_r(1.0f);
  rot_r = glm::rotate(rot_r, mCarCameraFront.rotation.roll,
                      glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 rot = glm::inverse(rot_y * rot_p * rot_r);
  mFrontMat4 = glm::translate(rot, glm::vec3(-mCarCameraFront.translation.x,
                                             -mCarCameraFront.translation.y,
                                             -mCarCameraFront.translation.z));
  // 图像宽高目前以前置摄像头为准
  mCameraWidth = mCarCameraFront.image_width;
  mCameraHeight = mCarCameraFront.image_height;
}

void AVMConfig::make_right_config() {
  glm::mat4 rot_p(1.f);
  rot_p = glm::rotate(rot_p, mCarCameraRight.rotation.pitch,
                      glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 rot_y(1.f);
  rot_y = glm::rotate(rot_y, mCarCameraRight.rotation.yaw,
                      glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 rot_r(1.f);
  rot_r = glm::rotate(rot_r, mCarCameraRight.rotation.roll,
                      glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 rot = glm::inverse(rot_y * rot_p * rot_r);
  mRightMat4 = glm::translate(rot, glm::vec3(-mCarCameraRight.translation.x,
                                             -mCarCameraRight.translation.y,
                                             -mCarCameraRight.translation.z));
}

void AVMConfig::make_back_config() {
  glm::mat4 rot_p(1.f);
  rot_p = glm::rotate(rot_p, mCarCameraBack.rotation.pitch,
                      glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 rot_y(1.f);
  rot_y = glm::rotate(rot_y, mCarCameraBack.rotation.yaw,
                      glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 rot_r(1.f);
  rot_r = glm::rotate(rot_r, mCarCameraBack.rotation.roll,
                      glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 rot = glm::inverse(rot_y * rot_p * rot_r);
  mBackMat4 = glm::translate(rot, glm::vec3(-mCarCameraBack.translation.x,
                                            -mCarCameraBack.translation.y,
                                            -mCarCameraBack.translation.z));
}

void AVMConfig::make_left_config() {
  glm::mat4 rot_p(1.f);
  rot_p = glm::rotate(rot_p, mCarCameraLeft.rotation.pitch,
                      glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 rot_y(1.f);
  rot_y = glm::rotate(rot_y, mCarCameraLeft.rotation.yaw,
                      glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 rot_r(1.f);
  rot_r = glm::rotate(rot_r, mCarCameraLeft.rotation.roll,
                      glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 rot = glm::inverse(rot_y * rot_p * rot_r);
  mLeftMat4 = glm::translate(rot, glm::vec3(-mCarCameraLeft.translation.x,
                                            -mCarCameraLeft.translation.y,
                                            -mCarCameraLeft.translation.z));
}
