//
//  FFHttpClient.cpp
//  Carrier
//
//  Created by pig on 14-10-13.
//
//

#include "FFHttpClient.h"

FFHttpClient::FFHttpClient()
{
    mHttpRequest = NULL;
}

FFHttpClient::~FFHttpClient()
{
    if (mHttpRequest) {
        CC_SAFE_RELEASE_NULL(mHttpRequest);
    }
}

bool FFHttpClient::init()
{
    mHttpRequest = new CCHttpRequest();
    mHttpRequest->setRequestType(CCHttpRequest::kHttpGet);
    mHttpRequest->setUrl("http://www.baidu.com");
    mHttpRequest->setResponseCallback(this, httpresponse_selector(FFHttpClient::didGetResponse));
    mHttpRequest->setTag("FFHttpClient");
    
    return true;
}

//FFHttpClientDelegate
void FFHttpClient::didSendRequest()
{
    CCHttpClient *httpClient = CCHttpClient::getInstance();
    httpClient->setTimeoutForConnect(30);
    httpClient->send(mHttpRequest);
}

void FFHttpClient::didGetResponse(cocos2d::extension::CCHttpClient *client, cocos2d::extension::CCHttpResponse *response)
{
    if (!response->isSucceed()) {
        CCLog("Receive Error: %s", response->getErrorBuffer());
        return;
    }
    const char *tag = response->getHttpRequest()->getTag();
    if (0 == strcmp("FFHttpClient", tag)) {
        std::vector<char> *data = response->getResponseData();
        int dataLen = data->size();
        std::string res;
        for (int i=0; i<dataLen; i++) {
            res += (*data)[i];
        }
        res += '\0';
        CCLog("response: %s", res.c_str());
    }
}
