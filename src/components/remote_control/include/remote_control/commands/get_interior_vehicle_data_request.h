/*
 Copyright (c) 2017, Ford Motor Company
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following
 disclaimer in the documentation and/or other materials provided with the
 distribution.

 Neither the name of the Ford Motor Company nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_COMPONENTS_REMOTE_CONTROL_INCLUDE_REMOTE_CONTROL_COMMANDS_GET_INTERIOR_VEHICLE_DATA_REQUEST_H_
#define SRC_COMPONENTS_REMOTE_CONTROL_INCLUDE_REMOTE_CONTROL_COMMANDS_GET_INTERIOR_VEHICLE_DATA_REQUEST_H_

#include "remote_control/commands/base_command_request.h"
#include "remote_control/event_engine/event.h"
#include "utils/macro.h"

namespace remote_control {

namespace commands {

/**
 * @brief GetInteriorVehicleDataRequest command class
 */
class GetInteriorVehicleDataRequest : public BaseCommandRequest {
 public:
  /**
   * @brief GetInteriorVehicleDataRequest class constructor
   *
   * @param message Message from mobile
   **/
  explicit GetInteriorVehicleDataRequest(
      const application_manager::MessagePtr& message,
      RemotePluginInterface& rc_module);

  /**
   * @brief Execute command
   */
  void Execute() FINAL;

  /**
   * @brief Interface method that is called whenever new event received
   *
   * @param event The received event
   */
  void OnEvent(const rc_event_engine::Event<application_manager::MessagePtr,
                                            std::string>& event);

  /**
   * @brief Check if app wants to proceed with already setup subscription
   * @param request_params request parameters to check
   * @return true if app already subscribed(unsubsribed) for module type but
   * wants to subscribe(unsubscribe) for the same module again
   * otherwise - false
   */
  bool HasRequestExcessiveSubscription(const Json::Value& request_params);

 protected:
  virtual std::string ModuleType(const Json::Value& message);

 private:
  /**
    * @brief Handle subscription to vehicle data
    * @param hmi_response json message with response from HMI
    */
  void ProccessSubscription(const Json::Value& hmi_response);

  /**
   * @brief Cuts off subscribe parameter
   * @param request_params request parameters to handle
   */
  void RemoveExcessiveSubscription(Json::Value& request_params);
};

}  // namespace commands

}  // namespace remote_control

#endif  // SRC_COMPONENTS_REMOTE_CONTROL_INCLUDE_REMOTE_CONTROL_COMMANDS_GET_INTERIOR_VEHICLE_DATA_REQUEST_H_
