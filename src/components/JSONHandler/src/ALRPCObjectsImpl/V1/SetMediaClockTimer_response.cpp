#include "../include/JSONHandler/ALRPCObjects/V1/SetMediaClockTimer_response.h"
#include "SetMediaClockTimer_responseMarshaller.h"
#include "../include/JSONHandler/ALRPCObjects/V1/Marshaller.h"

namespace
{
    const int PROTOCOL_VERSION = 1;
}

/*
  interface Ford Sync RAPI
  version   1.2
  date      2011-05-17
  generated at  Thu Jan 24 06:36:21 2013
  source stamp  Thu Jan 24 06:35:34 2013
  author    robok0der
*/

using namespace NsAppLinkRPC;
SetMediaClockTimer_response& SetMediaClockTimer_response::operator =(const SetMediaClockTimer_response& c)
{
    success = c.success;
    resultCode = c.resultCode;
    info = c.info ? new std::string(c.info[0]) : 0;

    return *this;
}

SetMediaClockTimer_response::~SetMediaClockTimer_response(void)
{}

SetMediaClockTimer_response::SetMediaClockTimer_response(const SetMediaClockTimer_response& c)
{
    *this = c;
}

bool SetMediaClockTimer_response::checkIntegrity(void)
{
    return SetMediaClockTimer_responseMarshaller::checkIntegrity(*this);
}

SetMediaClockTimer_response::SetMediaClockTimer_response(void)
    : ALRPCResponse(PROTOCOL_VERSION, Marshaller::METHOD_SETMEDIACLOCKTIMER_RESPONSE)
{}
