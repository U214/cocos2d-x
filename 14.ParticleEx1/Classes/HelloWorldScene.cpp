#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
	/////////////////////////////////

	this->doParticles();

    return true;
}

void HelloWorld::doParticles() {
	ParticleSystem* particleTest = ParticleFire::create();
	//ParticleSystem* particleTest = ParticleSun::create();
	//ParticleSystem* particleTest = ParticleGalaxy::create();
	//ParticleSystem* particleTest = ParticleSmoke::create();
	//ParticleSystem* particleTest = ParticleMeteor::create();

	//ParticleSystem* particleTest = ParticleFlower::create();
	//ParticleSystem* particleTest = ParticleFireworks::create();
	//ParticleSystem* particleTest = ParticleExplosion::create();

	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/fire.png");
	//auto texture = Director::getInstance()->getTextureCache()->addImage("Images/stars.png");
	particleTest->setTexture(texture);

	if (particleTest != NULL) {
		// 파티클의 크기 조정
		particleTest->setScale(1.0);
		// 파티클의 지속 시간 조정 : -1 means 'forever'
		// particleTest->setDuration(1.0);
		// 파티클의 위치 조정
		particleTest->setPosition(Vec2(240, 160));

		this->addChild(particleTest);
	}

}
