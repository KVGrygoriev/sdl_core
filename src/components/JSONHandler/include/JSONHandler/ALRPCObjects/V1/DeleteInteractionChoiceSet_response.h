#ifndef NSAPPLINKRPC_DELETEINTERACTIONCHOICESET_RESPONSE_INCLUDE
#define NSAPPLINKRPC_DELETEINTERACTIONCHOICESET_RESPONSE_INCLUDE

#include "JSONHandler/ALRPCResponse.h"

/*
  interface Ford Sync RAPI
  version   1.2
  date      2011-05-17
  generated at  Thu Jan 24 06:36:21 2013
  source stamp  Thu Jan 24 06:35:34 2013
  author    robok0der
*/

namespace NsAppLinkRPC
{
    class DeleteInteractionChoiceSet_response : public ALRPCResponse
    {
    public:
        DeleteInteractionChoiceSet_response(const DeleteInteractionChoiceSet_response& c);
        DeleteInteractionChoiceSet_response(void);

        virtual ~DeleteInteractionChoiceSet_response(void);

        DeleteInteractionChoiceSet_response& operator =(const DeleteInteractionChoiceSet_response&);

        bool checkIntegrity(void);

    private:
        friend class DeleteInteractionChoiceSet_responseMarshaller;
    };
}

#endif
