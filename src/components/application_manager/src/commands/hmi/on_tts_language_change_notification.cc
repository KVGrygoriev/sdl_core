/*
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "application_manager/commands/hmi/on_tts_language_change_notification.h"

#include "application_manager/application_impl.h"
#include "application_manager/message_helper.h"
#include "interfaces/MOBILE_API.h"

namespace application_manager {

namespace commands {

OnTTSLanguageChangeNotification::OnTTSLanguageChangeNotification(
    const MessageSharedPtr& message, ApplicationManager& application_manager)
    : NotificationFromHMI(message, application_manager) {}

OnTTSLanguageChangeNotification::~OnTTSLanguageChangeNotification() {}

void OnTTSLanguageChangeNotification::Run() {
  LOG4CXX_AUTO_TRACE(logger_);

  HMICapabilities& hmi_capabilities = application_manager_.hmi_capabilities();

  hmi_capabilities.set_active_tts_language(
      static_cast<hmi_apis::Common_Language::eType>(
          (*message_)[strings::msg_params][strings::language].asInt()));

  /* need to clarify, because unchanged VR
  cause WRONG_LANGUAGE on Register */
  hmi_capabilities.set_active_vr_language(
      static_cast<hmi_apis::Common_Language::eType>(
          (*message_)[strings::msg_params][strings::language].asInt()));

  (*message_)[strings::msg_params][strings::hmi_display_language] =
      hmi_capabilities.active_ui_language();

  (*message_)[strings::params][strings::function_id] =
      static_cast<int32_t>(mobile_apis::FunctionID::OnLanguageChangeID);

  const ApplicationSet& accessor =
      application_manager_.applications().GetData();
  ApplicationSetIt it = accessor.begin();
  for (; accessor.end() != it;) {
    ApplicationSharedPtr app = *it++;
    (*message_)[strings::params][strings::connection_key] = app->app_id();
    SendNotificationToMobile(message_);

    if (static_cast<int>(app->language()) !=
        (*message_)[strings::msg_params][strings::language].asInt()) {
      application_manager_.ManageMobileCommand(
          MessageHelper::GetOnAppInterfaceUnregisteredNotificationToMobile(
              app->app_id(),
              mobile_api::AppInterfaceUnregisteredReason::LANGUAGE_CHANGE),
          commands::Command::ORIGIN_SDL);
      application_manager_.UnregisterApplication(
          app->app_id(), mobile_apis::Result::SUCCESS, false);
    }
  }
}

}  // namespace commands

}  // namespace application_manager
