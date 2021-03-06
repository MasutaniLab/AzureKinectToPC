﻿// -*- C++ -*-
/*!
 * @file  AzureKinectToPC.cpp
 * @brief Point Cloud Grabber RTC Using Microsoft Azure Kinect DK
 * @date $Date$
 *
 * $Id$
 */

#define _USE_MATH_DEFINES
#include "AzureKinectToPC.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;
using namespace Eigen;

const float FLT_NAN = std::numeric_limits<float>::quiet_NaN();

// Module specification
// <rtc-template block="module_spec">
static const char* azurekinecttopc_spec[] =
  {
    "implementation_id", "AzureKinectToPC",
    "type_name",         "AzureKinectToPC",
    "description",       "Point Cloud Grabber RTC Using Microsoft Azure Kinect DK",
    "version",           "1.0.0",
    "vendor",            "MasutaniLab",
    "category",          "PointCloud",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.deviceId", "0",
    "conf.default.depthMode", "WFOV_2X2BINNED",
    "conf.default.alignTo", "depth",
    "conf.default.colorResolution", "720P",
    "conf.default.cameraFps", "30",
    "conf.default.transX", "0.0",
    "conf.default.transY", "0.0",
    "conf.default.transZ", "0.0",
    "conf.default.rotX", "0.0",
    "conf.default.rotY", "0.0",
    "conf.default.rotZ", "0.0",
    "conf.default.noColorInvalid", "1",

    // Widget
    "conf.__widget__.deviceId", "text",
    "conf.__widget__.depthMode", "radio",
    "conf.__widget__.alignTo", "radio",
    "conf.__widget__.colorResolution", "radio",
    "conf.__widget__.cameraFps", "radio",
    "conf.__widget__.transX", "text",
    "conf.__widget__.transY", "text",
    "conf.__widget__.transZ", "text",
    "conf.__widget__.rotX", "text",
    "conf.__widget__.rotY", "text",
    "conf.__widget__.rotZ", "text",
    "conf.__widget__.noColorInvalid", "radio",
    // Constraints
    "conf.__constraints__.depthMode", "(OFF,NFOV_2X2BINNED,NFOV_UNBINNED,WFOV_2X2BINNED,WFOV_UNBINNED,PASSIVE_IR)",
    "conf.__constraints__.alignTo", "(depth,color)",
    "conf.__constraints__.colorResolution", "(OFF,720P,1080P,1440P,1536P,2160P,3072P)",
    "conf.__constraints__.cameraFps", "(5,15,30)",
    "conf.__constraints__.noColorInvalid", "(0,1)",

    "conf.__type__.deviceId", "short",
    "conf.__type__.depthMode", "string",
    "conf.__type__.alignTo", "string",
    "conf.__type__.colorResolution", "string",
    "conf.__type__.cameraFps", "short",
    "conf.__type__.transX", "float",
    "conf.__type__.transY", "float",
    "conf.__type__.transZ", "float",
    "conf.__type__.rotX", "float",
    "conf.__type__.rotY", "float",
    "conf.__type__.rotZ", "float",
    "conf.__type__.noColorInvalid", "short",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AzureKinectToPC::AzureKinectToPC(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_commandIn("command", m_command),
    m_pcOut("pc", m_pc)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
AzureKinectToPC::~AzureKinectToPC()
{
}



RTC::ReturnCode_t AzureKinectToPC::onInitialize()
{
  RTC_INFO(("onInitialize()"));
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("command", m_commandIn);
  
  // Set OutPort buffer
  addOutPort("pc", m_pcOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("deviceId", m_deviceId, "0");
  bindParameter("depthMode", m_depthMode, "WFOV_2X2BINNED");
  bindParameter("alignTo", m_alignTo, "depth");
  bindParameter("colorResolution", m_colorResolution, "720P");
  bindParameter("cameraFps", m_cameraFps, "30");
  bindParameter("transX", m_transX, "0.0");
  bindParameter("transY", m_transY, "0.0");
  bindParameter("transZ", m_transZ, "0.0");
  bindParameter("rotX", m_rotX, "0.0");
  bindParameter("rotY", m_rotY, "0.0");
  bindParameter("rotZ", m_rotZ, "0.0");
  bindParameter("noColorInvalid", m_noColorInvalid, "1");
  // </rtc-template>

  m_depthModeMap = {
    {"OFF", K4A_DEPTH_MODE_OFF},
    {"NFOV_2X2BINNED", K4A_DEPTH_MODE_NFOV_2X2BINNED},
    {"NFOV_UNBINNED", K4A_DEPTH_MODE_NFOV_UNBINNED},
    {"WFOV_2X2BINNED", K4A_DEPTH_MODE_WFOV_2X2BINNED},
    {"WFOV_UNBINNED", K4A_DEPTH_MODE_WFOV_UNBINNED},
    {"PASSIVE_IR", K4A_DEPTH_MODE_PASSIVE_IR},
  };
  m_cameraFpsMap = {
    {5, K4A_FRAMES_PER_SECOND_5},
    {15, K4A_FRAMES_PER_SECOND_15},
    {30, K4A_FRAMES_PER_SECOND_30},
  };
  m_colorResolutionMap = {
    {"OFF", K4A_COLOR_RESOLUTION_OFF},
    {"720P", K4A_COLOR_RESOLUTION_720P},
    {"1080P", K4A_COLOR_RESOLUTION_1080P},
    {"1440P", K4A_COLOR_RESOLUTION_1440P},
    {"1536P", K4A_COLOR_RESOLUTION_1536P},
    {"2160P", K4A_COLOR_RESOLUTION_2160P},
    {"3072P", K4A_COLOR_RESOLUTION_3072P},
  };
  m_alignToMap = {
    {"depth", true},
    {"color", false},
  };
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AzureKinectToPC::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPC::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPC::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t AzureKinectToPC::onActivated(RTC::UniqueId ec_id)
{
  RTC_INFO(("onActivated()"));
  try {
    if (m_rotX == 0 && m_rotY == 0 && m_rotZ == 0 && m_transX == 0 && m_transY == 0 && m_transZ == 0) {
      m_coordinateTransformation = false;
    } else {
      m_coordinateTransformation = true;
      const float M_PIF = float(M_PI);
      float radX = m_rotX * M_PIF / 180;
      float radY = m_rotY * M_PIF / 180;
      float radZ = m_rotZ * M_PIF / 180;
      m_transform
        = Translation3f(m_transX, m_transY, m_transZ)
        * AngleAxisf(radZ, Vector3f::UnitZ())
        * AngleAxisf(radY, Vector3f::UnitY())
        * AngleAxisf(radX, Vector3f::UnitX());
      cout << "m_transform:" << endl << m_transform.matrix() << endl;
    }

    k4a_device_configuration_t config(K4A_DEVICE_CONFIG_INIT_DISABLE_ALL);
    if (m_depthModeMap.count(m_depthMode) == 0) {
      RTC_ERROR(("depthMode: %s は非対応", m_depthMode.c_str()));
      return RTC::RTC_ERROR;
    }    
    config.depth_mode = m_depthModeMap[m_depthMode];

    if (m_cameraFpsMap.count(m_cameraFps) == 0) {
      RTC_ERROR(("cameraFps: %d は非対応", m_cameraFps));
      return RTC::RTC_ERROR;
    }
    config.camera_fps = m_cameraFpsMap[m_cameraFps];

    config.color_format = K4A_IMAGE_FORMAT_COLOR_BGRA32;

    if (m_colorResolutionMap.count(m_colorResolution) == 0) {
      RTC_ERROR(("colorResolution: %s は非対応", m_colorResolution.c_str()));
      return RTC::RTC_ERROR;
    }
    config.color_resolution = m_colorResolutionMap[m_colorResolution];

    if (m_alignToMap.count(m_alignTo) == 0) {
      RTC_ERROR(("alignTo: %s は無効", m_alignTo.c_str()));
      return RTC::RTC_ERROR;
    }
    m_alignToDepth = m_alignToMap[m_alignTo];

    config.synchronized_images_only = true;

    m_dev = k4a::device::open(m_deviceId);
    m_dev.start_cameras(&config);
    k4a::calibration calibration = m_dev.get_calibration(config.depth_mode, config.color_resolution);
    m_transformation = k4a::transformation(calibration);

    m_pc.type = "xyzrgb";
    m_pc.fields.length(6);
    m_pc.fields[0].name = "x";
    m_pc.fields[0].offset = 0;
    m_pc.fields[0].data_type = PointCloudTypes::FLOAT32;
    m_pc.fields[0].count = 4;
    m_pc.fields[1].name = "y";
    m_pc.fields[1].offset = 4;
    m_pc.fields[1].data_type = PointCloudTypes::FLOAT32;
    m_pc.fields[1].count = 4;
    m_pc.fields[2].name = "z";
    m_pc.fields[2].offset = 8;
    m_pc.fields[2].data_type = PointCloudTypes::FLOAT32;
    m_pc.fields[2].count = 4;
    m_pc.fields[3].name = "b";
    m_pc.fields[3].offset = 12;
    m_pc.fields[3].data_type = PointCloudTypes::UINT8;
    m_pc.fields[3].count = 1;
    m_pc.fields[4].name = "g";
    m_pc.fields[4].offset = 13;
    m_pc.fields[4].data_type = PointCloudTypes::UINT8;
    m_pc.fields[4].count = 1;
    m_pc.fields[5].name = "r";
    m_pc.fields[5].offset = 14;
    m_pc.fields[5].data_type = PointCloudTypes::UINT8;
    m_pc.fields[5].count = 1;
    m_pc.is_bigendian = false;
    m_pc.point_step = 16;
    m_pc.is_dense = false;

    m_steadyStart = chrono::steady_clock::now();
    m_fpsCounter = 0;
    m_running = true;
  } catch (const std::exception& e) {
    RTC_ERROR((e.what()));
    return RTC::RTC_ERROR;
  } catch (...) {
    RTC_ERROR(("An exception occurred in onActivated()"));
    return RTC::RTC_ERROR;
  }

  return RTC::RTC_OK;
}


RTC::ReturnCode_t AzureKinectToPC::onDeactivated(RTC::UniqueId ec_id)
{
  RTC_INFO(("onDeactivated()"));
  if (m_dev) {
    m_transformation.destroy();
    m_dev.close();
  }
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AzureKinectToPC::onExecute(RTC::UniqueId ec_id)
{
  if (m_commandIn.isNew()) {
    m_commandIn.read();
    string s = m_command.data;
    if (s == "start") {
      m_running = true;
      RTC_INFO(("m_running = true"));
    } else if (s == "stop") {
      m_running = false;
      RTC_INFO(("m_running = false"));
    } else {
      RTC_ERROR(("未知のコマンド: %s", s.c_str()));
      return RTC::RTC_ERROR;
    }
  }
  if (m_running) {
    try {
      k4a::capture capture;
      if (!m_dev.get_capture(&capture, std::chrono::milliseconds(0))) {
        return RTC::RTC_OK;
      }

      k4a::image depthImage = capture.get_depth_image();
      if (depthImage == nullptr) {
        RTC_ERROR(("キャプチャから深度画像の取得に失敗"));
        return RTC::RTC_ERROR;
      }

      k4a::image colorImage = capture.get_color_image();
      if (colorImage == nullptr) {
        RTC_ERROR(("キャプチャからカラー画像の取得に失敗"));
        return RTC::RTC_ERROR;
      }

      int width, height;
      k4a::image newDepthImage = nullptr;
      k4a::image newColorImage = nullptr;
      if (m_alignToDepth) {
        width = depthImage.get_width_pixels();
        height = depthImage.get_height_pixels();
        newDepthImage = depthImage;
        newColorImage = k4a::image::create(
          K4A_IMAGE_FORMAT_COLOR_BGRA32,
          width, height, width * 4 * (int)sizeof(uint8_t));
      } else {
        width = colorImage.get_width_pixels();
        height = colorImage.get_height_pixels();
        newDepthImage = k4a::image::create(
          K4A_IMAGE_FORMAT_DEPTH16,
          width, height, width * (int)sizeof(uint16_t));
        newColorImage = colorImage;
      }

      k4a::image pointCloudImage = nullptr;
      pointCloudImage = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM,
        width, height, width * 3 * (int)sizeof(int16_t));

      if (m_alignToDepth) {
        m_transformation.color_image_to_depth_camera(
          depthImage, colorImage, &newColorImage);
        m_transformation.depth_image_to_point_cloud(
          newDepthImage, K4A_CALIBRATION_TYPE_DEPTH, & pointCloudImage);
      } else {
        m_transformation.depth_image_to_color_camera(depthImage, &newDepthImage);
        m_transformation.depth_image_to_point_cloud(
          newDepthImage, K4A_CALIBRATION_TYPE_COLOR, &pointCloudImage);
      }

      m_pc.width = width;
      m_pc.height = height;
      m_pc.row_step = m_pc.point_step * m_pc.width;
      m_pc.data.length(m_pc.height * m_pc.row_step);

      int16_t* pointCloudImageData = (int16_t*)(void*)pointCloudImage.get_buffer();
      float* newColorImageData = reinterpret_cast<float*>(newColorImage.get_buffer());
      
      float* dstCloud = (float*)m_pc.data.get_buffer();

      const uint32_t noColorInt = 0;
      const float noColor = *reinterpret_cast<const float*>(&noColorInt);

      if (m_alignToDepth && m_noColorInvalid) {
        //色情報のない点は無効扱い
        for (int i = 0; i < width * height; i++) {
          if (newColorImageData[i] == noColor) {
            dstCloud[0] = FLT_NAN;
            dstCloud[1] = FLT_NAN;
            dstCloud[2] = FLT_NAN;
          } else {
            //XYZ
            float x = pointCloudImageData[3 * i + 0] / 1000.0f;
            float y = pointCloudImageData[3 * i + 1] / 1000.0f;
            float z = pointCloudImageData[3 * i + 2] / 1000.0f;
            //XYZ
            //座標変換の前にy軸とz軸を反転させる
            Vector3f tmp(x, -y, -z);
            if (m_coordinateTransformation) {
              tmp = m_transform * tmp;
            }

            dstCloud[0] = tmp(0);
            dstCloud[1] = tmp(1);
            dstCloud[2] = tmp(2);
          }
          dstCloud[3] = newColorImageData[i];
          dstCloud += 4;
        }
      } else {
        //色情報がない点の座標はそのまま
        for (int i = 0; i < width * height; i++) {
          //XYZ
          float x = pointCloudImageData[3 * i + 0] / 1000.0f;
          float y = pointCloudImageData[3 * i + 1] / 1000.0f;
          float z = pointCloudImageData[3 * i + 2] / 1000.0f;
          //XYZ
          //座標変換の前にy軸とz軸を反転させる
          Vector3f tmp(x, -y, -z);
          if (m_coordinateTransformation) {
            tmp = m_transform * tmp;
          }

          dstCloud[0] = tmp(0);
          dstCloud[1] = tmp(1);
          dstCloud[2] = tmp(2);
          dstCloud[3] = newColorImageData[i];
#if 0
          //デバッグのため対応する色情報のない点を赤色にする
          const uint32_t redInt = 0xff0000;
          const float red = *reinterpret_cast<const float*>(&redInt);
          if (newColorImageData[i] == noColor) {
            dstCloud[3] = red;
          }
#endif
          dstCloud += 4;
        }
      }

      m_pcOut.write();

      m_fpsCounter++;
      m_steadyEnd = chrono::steady_clock::now();
      double timeSec = std::chrono::duration<double>(m_steadyEnd - m_steadyStart).count();
      if (timeSec >= 1) {
        RTC_INFO(("%f fps", m_fpsCounter / timeSec));
        m_steadyStart = m_steadyEnd;
        m_fpsCounter = 0;
      }
    } catch (const std::exception& e) {
      RTC_ERROR((e.what()));
      return RTC::RTC_ERROR;
    } catch (...) {
      RTC_ERROR(("An exception occurred in onExecute()"));
      return RTC::RTC_ERROR;
    }
  }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AzureKinectToPC::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPC::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPC::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPC::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPC::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AzureKinectToPCInit(RTC::Manager* manager)
  {
    coil::Properties profile(azurekinecttopc_spec);
    manager->registerFactory(profile,
                             RTC::Create<AzureKinectToPC>,
                             RTC::Delete<AzureKinectToPC>);
  }
  
};


