// -*- C++ -*-
/*!
 * @file  AzureKinectToPC.h
 * @brief Point Cloud Grabber RTC Using Microsoft Azure Kinect DK
 * @date  $Date$
 *
 * $Id$
 */

#ifndef AZUREKINECTTOPC_H
#define AZUREKINECTTOPC_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"
#include "pointcloudStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include <string>
#include <map>
#include <Eigen/Geometry>
#include <k4a/k4a.hpp>

/*!
 * @class AzureKinectToPC
 * @brief Point Cloud Grabber RTC Using Microsoft Azure Kinect DK
 *
 */
class AzureKinectToPC
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  AzureKinectToPC(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~AzureKinectToPC();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  deviceId
   * - DefaultValue: 0
   */
  short int m_deviceId;
  /*!
   * 
   * - Name:  depthMode
   * - DefaultValue: WFOV_2X2BINNED
   */
  std::string m_depthMode;
  /*!
   * 
   * - Name:  alignTo
   * - DefaultValue: depth
   */
  std::string m_alignTo;
  /*!
   * 
   * - Name:  colorResolution
   * - DefaultValue: 720P
   */
  std::string m_colorResolution;
  /*!
   * 
   * - Name:  cameraFps
   * - DefaultValue: 30
   */
  short int m_cameraFps;
  /*!
   * 
   * - Name:  transX
   * - DefaultValue: 0.0
   */
  float m_transX;
  /*!
   * 
   * - Name:  transY
   * - DefaultValue: 0.0
   */
  float m_transY;
  /*!
   * 
   * - Name:  transZ
   * - DefaultValue: 0.0
   */
  float m_transZ;
  /*!
   * 
   * - Name:  rotX
   * - DefaultValue: 0.0
   */
  float m_rotX;
  /*!
   * 
   * - Name:  rotY
   * - DefaultValue: 0.0
   */
  float m_rotY;
  /*!
   * 
   * - Name:  rotZ
   * - DefaultValue: 0.0
   */
  float m_rotZ;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedString m_command;
  /*!
   */
  RTC::InPort<RTC::TimedString> m_commandIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  PointCloudTypes::PointCloud m_pc;
  /*!
   */
  RTC::OutPort<PointCloudTypes::PointCloud> m_pcOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>
   bool m_coordinateTransformation;
   Eigen::Affine3f m_transform;
   int m_fpsCounter;
   std::chrono::steady_clock::time_point m_steadyStart;
   std::chrono::steady_clock::time_point m_steadyEnd;
   bool m_running;
   k4a::device m_dev;
   k4a::transformation m_transformation;
   bool m_alignToDepth;

   std::map<std::string, k4a_depth_mode_t> m_depthModeMap;
   std::map<short, k4a_fps_t> m_cameraFpsMap;
   std::map<std::string, k4a_color_resolution_t> m_colorResolutionMap;
   std::map<std::string, bool> m_alignToMap;
};


extern "C"
{
  DLL_EXPORT void AzureKinectToPCInit(RTC::Manager* manager);
};

#endif // AZUREKINECTTOPC_H
