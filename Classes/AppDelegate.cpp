#include "pch.h"
#include "AppDelegate.h"
#include "TitleScene.h"
#include "GameManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(960, 540, ResolutionPolicy::SHOW_ALL);
    //director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
	GET_GAME_MANAGER()->changeScene(SceneType::TITLE_SCENE);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

}
