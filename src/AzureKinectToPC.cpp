// -*- C++ -*-
/*!
 * @file  AzureKinectToPC.cpp
 * @brief Point Cloud Grabber RTC Using Microsoft Azure Kinect DK
 * @date $Date$
 *
 * $Id$
 */

#include "AzureKinectToPC.h"

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
    "conf.default.colorFormat", "BGRA32",
    "conf.default.colorResolution", "720P",
    "conf.default.cameraFps", "30",

    // Widget
    "conf.__widget__.deviceId", "text",
    "conf.__widget__.depthMode", "radio",
    "conf.__widget__.colorFormat", "radio",
    "conf.__widget__.colorResolution", "radio",
    "conf.__widget__.cameraFps", "radio",
    // Constraints
    "conf.__constraints__.depthMode", "(OFF,NFOV_2X2BINNED,NFOV_UNBINNED,WFOV_2X2BINNED,WFOV_UNBINNED,PASSIVE_IR)",
    "conf.__constraints__.colorFormat", "(MJPG,NV12,YUY2,BGRA32,DEPTH16,CUSTOM8,CUSTOM16,CUSTOM)",
    "conf.__constraints__.colorResolution", "(OFF,720P,1080P,1440P,1536P,2160P,3072P)",
    "conf.__constraints__.cameraFps", "(5,15,30)",

    "conf.__type__.deviceId", "short",
    "conf.__type__.depthMode", "string",
    "conf.__type__.colorFormat", "string",
    "conf.__type__.colorResolution", "string",
    "conf.__type__.cameraFps", "short",

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
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
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
  bindParameter("colorFormat", m_colorFormat, "BGRA32");
  bindParameter("colorResolution", m_colorResolution, "720P");
  bindParameter("cameraFps", m_cameraFps, "30");
  // </rtc-template>
  
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
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AzureKinectToPC::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t AzureKinectToPC::onExecute(RTC::UniqueId ec_id)
{
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


