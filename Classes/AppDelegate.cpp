#include "AppDelegate.h"
#include "HelloWorldScene.h"

//
#include "LevelScene.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //set design resolution size
//    pEGLView->setDesignResolutionSize(480, 320, kResolutionNoBorder);
    CCSize frameSize = pEGLView->getFrameSize();
//    CCSize lsSize = CCSizeMake(960, 640);
    CCSize lsSize = CCSizeMake(1200, 900);
    
    float scaleX = frameSize.width / lsSize.width;
    float scaleY = frameSize.height / lsSize.height;
    
    float scale = MAX(scaleX, scaleY);
    
//    if (scaleX > scaleY) {
//        scale = scaleX / (frameSize.height / lsSize.height);
//    } else {
//        scale = scaleY / (frameSize.width / lsSize.width);
//    }
    
    //固定高度
//    if (scaleX > scaleY) {
//        scale = scaleX / (frameSize.height / lsSize.height);
//    } else {
//        scale = scaleX / (frameSize.width / lsSize.width);
//    }
    
    //固定宽度
    if (scaleX > scaleY) {
        scale = scaleY / (frameSize.height / lsSize.height);
    } else {
        scale = scaleY / (frameSize.width / lsSize.width);
    }
    
    CCLog("x: %f, y: %f, scale: %f", scaleX, scaleY, scale);
    pEGLView->setDesignResolutionSize(lsSize.width * scale, lsSize.height * scale, kResolutionNoBorder);
    
    // create a scene. it's an autorelease object
//    CCScene *pScene = HelloWorld::scene();
//    CCScene *pScene = LevelScene::scene();
    CCScene *pScene = GameScene::scene();

    // run
    pDirector->runWithScene(pScene);
    
    //show size
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLog("FrameSize: width[%f], height[%f]", frameSize.width, frameSize.height);
    CCLog("WinSize: width[%f], height[%f]", winSize.width, winSize.height);
    CCLog("VisibleSize: width[%f], height[%f]", visibleSize.width, visibleSize.height);
    CCLog("VisibleOrigin: x[%f], y[%f]", visibleOrigin.x, visibleOrigin.y);
    
    CCLog("XScale: %f, YScale: %f", CCEGLView::sharedOpenGLView()->getScaleX(), CCEGLView::sharedOpenGLView()->getScaleY());
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
