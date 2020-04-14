﻿// -*- C++ -*-
/*!
 * @file  AzureKinectToPCTest.h
 * @brief Point Cloud Grabber RTC Using Microsoft Azure Kinect DK
 * @date  $Date$
 *
 * $Id$
 */

#ifndef AZUREKINECTTOPC_TEST__H
#define AZUREKINECTTOPC_TEST_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">
#include "BasicDataTypeSVC_impl.h"
#include "pointcloudSVC_impl.h"

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
using namespace PointCloudTypes;
// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

/*!
 * @class AzureKinectToPCTest
 * @brief Point Cloud Grabber RTC Using Microsoft Azure Kinect DK
 *
 */
class AzureKinectToPCTest
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  AzureKinectToPCTest(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~AzureKinectToPCTest();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
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
   * former rtc_stopping_entry()
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
   * former rtc_active_entry()
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
   * former rtc_active_exit()
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
   * former rtc_active_do()
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
   * former rtc_aborting_entry()
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
   * former rtc_error_do()
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
   * This is same but different the former rtc_init_entry()
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
   * no corresponding operation exists in OpenRTm-aist-0.2.0
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
   * no corresponding operation exists in OpenRTm-aist-0.2.0
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
   * - Name:  colorFormat
   * - DefaultValue: BGRA32
   */
  std::string m_colorFormat;
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
  double m_transX;
  /*!
   * 
   * - Name:  transY
   * - DefaultValue: 0.0
   */
  double m_transY;
  /*!
   * 
   * - Name:  transZ
   * - DefaultValue: 0.0
   */
  double m_transZ;
  /*!
   * 
   * - Name:  rotX
   * - DefaultValue: 0.0
   */
  double m_rotX;
  /*!
   * 
   * - Name:  rotY
   * - DefaultValue: 0.0
   */
  double m_rotY;
  /*!
   * 
   * - Name:  rotZ
   * - DefaultValue: 0.0
   */
  double m_rotZ;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  PointCloudTypes::PointCloud m_pc;
  /*!
   */
  RTC::InPort<PointCloudTypes::PointCloud> m_pcIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedString m_command;
  /*!
   */
  RTC::OutPort<RTC::TimedString> m_commandOut;
  
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

};


extern "C"
{
  DLL_EXPORT void AzureKinectToPCTestInit(RTC::Manager* manager);
};

#endif // AZUREKINECTTOPC_TEST_H