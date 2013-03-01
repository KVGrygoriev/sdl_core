#ifndef NSAPPLINKRPC_UNREGISTERAPPINTERFACE_RESPONSE_INCLUDE
#define NSAPPLINKRPC_UNREGISTERAPPINTERFACE_RESPONSE_INCLUDE

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
    class UnregisterAppInterface_response : public ALRPCResponse
    {
    public:
        UnregisterAppInterface_response(const UnregisterAppInterface_response& c);
        UnregisterAppInterface_response(void);

        virtual ~UnregisterAppInterface_response(void);

        UnregisterAppInterface_response& operator =(const UnregisterAppInterface_response&);

        bool checkIntegrity(void);

    private:
        friend class UnregisterAppInterface_responseMarshaller;
    };
}

#endif
