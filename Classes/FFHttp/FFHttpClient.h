//
//  FFHttpClient.h
//  Carrier
//
//  Created by pig on 14-10-13.
//
//

#ifndef __Carrier__FFHttpClient__
#define __Carrier__FFHttpClient__

#include "cocos2d.h"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

USING_NS_CC;
USING_NS_CC_EXT;

class FFHttpClientDelegate {
    
public:
    virtual void didSendRequest() = 0;
    virtual void didGetResponse(CCHttpClient* client, CCHttpResponse* response) = 0;
};

class FFHttpClient : public cocos2d::CCObject, public FFHttpClientDelegate {
private:
    CCHttpRequest *mHttpRequest;
    
public:
    FFHttpClient();
    ~FFHttpClient();
    
    virtual bool init();
    CREATE_FUNC(FFHttpClient);
    
    virtual void didSendRequest();
    virtual void didGetResponse(CCHttpClient* client, CCHttpResponse* response);
};

#endif /* defined(__Carrier__FFHttpClient__) */
