// -*- C++ -*-
/*!
 * @file  AzureKinectToPCTest.cpp
 * @brief Point Cloud Grabber RTC Using Microsoft Azure Kinect DK
 * @date $Date$
 *
 * $Id$
 */

#include "AzureKinectToPCTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* azurekinecttopc_spec[] =
  {
    "implementation_id", "AzureKinectToPCTest",
    "type_name",         "AzureKinectToPCTest",
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
    "conf.default.colorFormat", "BGRA32",
    "conf.default.colorResolution", "720P",
    "conf.default.cameraFps", "30",
    "conf.default.transX", "0.0",
    "conf.default.transY", "0.0",
    "conf.default.transZ", "0.0",
    "conf.default.rotX", "0.0",
    "conf.default.rotY", "0.0",
    "conf.default.rotZ", "0.0",

    // Widget
    "conf.__widget__.deviceId", "text",
    "conf.__widget__.depthMode", "radio",
    "conf.__widget__.colorFormat", "radio",
    "conf.__widget__.colorResolution", "radio",
    "conf.__widget__.cameraFps", "radio",
    "conf.__widget__.transX", "text",
    "conf.__widget__.transY", "text",
    "conf.__widget__.transZ", "text",
    "conf.__widget__.rotX", "text",
    "conf.__widget__.rotY", "text",
    "conf.__widget__.rotZ", "text",
    // Constraints
    "conf.__constraints__.depthMode", "(OFF,NFOV_2X2BINNED,NFOV_UNBINNED,WFOV_2X2BINNED,WFOV_UNBINNED,PASSIVE_IR)",
    "conf.__constraints__.colorFormat", "(MJPG,NV12,YUY2,BGRA32)",
    "conf.__constraints__.colorResolution", "(OFF,720P,1080P,1440P,1536P,2160P,3072P)",
    "conf.__constraints__.cameraFps", "(5,15,30)",

    "conf.__type__.deviceId", "short",
    "conf.__type__.depthMode", "string",
    "conf.__type__.colorFormat", "string",
    "conf.__type__.colorResolution", "string",
    "conf.__type__.cameraFps", "short",
    "conf.__type__.transX", "float",
    "conf.__type__.transY", "float",
    "conf.__type__.transZ", "float",
    "conf.__type__.rotX", "float",
    "conf.__type__.rotY", "float",
    "conf.__type__.rotZ", "float",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
AzureKinectToPCTest::AzureKinectToPCTest(RTC::Manager* manager)
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
AzureKinectToPCTest::~AzureKinectToPCTest()
{
}



RTC::ReturnCode_t AzureKinectToPCTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("pc", m_pcIn);
  
  // Set OutPort buffer
  addOutPort("command", m_commandOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("deviceId", m_deviceId, "0");
  bindParameter("depthMode", m_depthMode, "WFOV_2X2BINNED");
  bindParameter("colorFormat", m_colorFormat, "BGRA32");
  bindParameter("colorResolution", m_colorResolution, "720P");
  bindParameter("cameraFps", m_cameraFps, "30");
  bindParameter("transX", m_transX, "0.0");
  bindParameter("transY", m_transY, "0.0");
  bindParameter("transZ", m_transZ, "0.0");
  bindParameter("rotX", m_rotX, "0.0");
  bindParameter("rotY", m_rotY, "0.0");
  bindParameter("rotZ", m_rotZ, "0.0");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AzureKinectToPCTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPCTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPCTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t AzureKinectToPCTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AzureKinectToPCTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AzureKinectToPCTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t AzureKinectToPCTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPCTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPCTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPCTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t AzureKinectToPCTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void AzureKinectToPCTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(azurekinecttopc_spec);
    manager->registerFactory(profile,
                             RTC::Create<AzureKinectToPCTest>,
                             RTC::Delete<AzureKinectToPCTest>);
  }
  
};


