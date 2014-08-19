#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size winSize = Director::getInstance()->getWinSize();
    
  
	_ball = Sprite::create("ball.png");
	_ball->setPosition(Vec2(100.f, 300.f));
	this->addChild(_ball);

	BOX2D_H::b2Vec2 gravity = BOX2D_H::b2Vec2(0.f, -8.f);
	_world = new BOX2D_H::b2World(gravity);

	BOX2D_H::b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set(100/PTM, 300/PTM);
	ballBodyDef.userData = _ball;
	_body = _world->CreateBody(&ballBodyDef);

	BOX2D_H::b2CircleShape circle;
	circle.m_radius = 26.0/PTM;

	BOX2D_H::b2FixtureDef ballShapeDef;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 0.8f;
	_body->CreateFixture(&ballShapeDef);

	this->schedule(schedule_selector(HelloWorld::update));

    return true;
}


void HelloWorld::update(float dt) {
	_world->Step(dt, 10, 10);
	for(b2Body *b = _world->GetBodyList(); b; b= b->GetNext()) {
		if(b->GetUserData() != NULL) {
			Sprite *ballData = (Sprite *) b->GetUserData();
			ballData->setPosition(Point(b->GetPosition().x * PTM, b->GetPosition().y * PTM));
			ballData->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

HelloWorld::~HelloWorld() {
	delete _world;
	_body = NULL;
	_world = NULL;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
