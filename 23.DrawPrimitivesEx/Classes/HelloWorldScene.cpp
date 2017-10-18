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

	auto wlayer = LayerColor::create(Color4B(255, 255, 255, 255));
	this->addChild(wlayer);
    
	/////////////////////////////////

	newDraw();

    return true;
}

void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	//draw
	CHECK_GL_ERROR_DEBUG();

	// draw a simple line
	// The default state is:
	// Line Width: 1
	// color: 255,255,255,255 (white, non-transparent)
	// Anti-Aliased
	//  glEnable(GL_LINE_SMOOTH);
	DrawPrimitives::drawLine(Vec2(0, 0), Vec2(480, 320));

	CHECK_GL_ERROR_DEBUG();

	// line: color, width, aliased
	// glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
	// GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
	//  glDisable(GL_LINE_SMOOTH);
	glLineWidth(5.0f);
	DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
	DrawPrimitives::drawLine(Vec2(0, 320), Vec2(480, 0));

	CHECK_GL_ERROR_DEBUG();

	// TIP:
	// If you are going to use always the same color or width, you don't
	// need to call it before every draw
	//
	// Remember: OpenGL is a state-machine.

	// draw big point in the center
	DrawPrimitives::setPointSize(64);
	DrawPrimitives::setDrawColor4B(0, 0, 255, 128);
	DrawPrimitives::drawPoint(Vec2(240, 160));

	CHECK_GL_ERROR_DEBUG();

	// draw 4 small points
	Vec2 points[] = { Vec2(60,60), Vec2(70,70), Vec2(60,70), Vec2(70,60) };
	DrawPrimitives::setPointSize(4);
	DrawPrimitives::setDrawColor4B(0, 255, 255, 255);
	DrawPrimitives::drawPoints(points, 4);

	CHECK_GL_ERROR_DEBUG();

	// draw a green circle with 10 segments
	glLineWidth(16);
	DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
	DrawPrimitives::drawCircle(Vec2(240, 160), 100, 0, 10, false);

	CHECK_GL_ERROR_DEBUG();

	// draw a green circle with 50 segments with line to center
	glLineWidth(2);
	DrawPrimitives::setDrawColor4B(0, 255, 255, 255);
	DrawPrimitives::drawCircle(Vec2(240, 160), 50, CC_DEGREES_TO_RADIANS(90), 50, true);

	CHECK_GL_ERROR_DEBUG();

	// draw a pink solid circle with 50 segments
	glLineWidth(2);
	DrawPrimitives::setDrawColor4B(255, 0, 255, 255);
	DrawPrimitives::drawSolidCircle(Vec2(240, 160) + Vec2(140, 0), 40, CC_DEGREES_TO_RADIANS(90), 50, 1.0f, 1.0f);

	CHECK_GL_ERROR_DEBUG();

	// open yellow poly
	DrawPrimitives::setDrawColor4B(255, 255, 0, 255);
	glLineWidth(10);
	Vec2 vertices[] = { Vec2(0,0), Vec2(50,50), Vec2(100,50), Vec2(100,100), Vec2(50,100) };
	DrawPrimitives::drawPoly(vertices, 5, false);

	CHECK_GL_ERROR_DEBUG();

	// filled poly
	glLineWidth(1);
	Vec2 filledVertices[] = { Vec2(0,120), Vec2(50,120), Vec2(50,170), Vec2(25,200), Vec2(0,170) };
	DrawPrimitives::drawSolidPoly(filledVertices, 5, Color4F(0.5f, 0.5f, 1, 1));


	// closed purble poly
	DrawPrimitives::setDrawColor4B(255, 0, 255, 255);
	glLineWidth(2);
	Vec2 vertices2[] = { Vec2(30,130), Vec2(30,230), Vec2(50,200) };
	DrawPrimitives::drawPoly(vertices2, 3, true);

	CHECK_GL_ERROR_DEBUG();

	// draw quad bezier path
	DrawPrimitives::drawQuadBezier(Vec2(0, 320), Vec2(240, 160), Vec2(480, 320), 50);

	CHECK_GL_ERROR_DEBUG();

	// draw cubic bezier path
	DrawPrimitives::drawCubicBezier(Vec2(240, 160), Vec2(Vec2(240, 160).x + 30, Vec2(240, 160).y + 50), Vec2(Vec2(240, 160).x + 60, Vec2(240, 160).y - 50), Vec2(0, 160), 100);

	CHECK_GL_ERROR_DEBUG();

	//draw a solid polygon
	Vec2 vertices3[] = { Vec2(60,160), Vec2(70,190), Vec2(100,190), Vec2(90,160) };
	DrawPrimitives::drawSolidPoly(vertices3, 4, Color4F(1, 1, 0, 1));

	// restore original values
	glLineWidth(1);
	DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
	DrawPrimitives::setPointSize(1);

	CHECK_GL_ERROR_DEBUG();

	//end draw
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void HelloWorld::newDraw() {
	auto s = Director::getInstance()->getWinSize();

	auto draw = DrawNode::create();
	addChild(draw, 10);

	draw->drawPoint(Vec2(s.width / 2 - 120, s.height / 2 - 120), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

	draw->drawPoint(Vec2(s.width / 2 + 120, s.height / 2 + 120), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

	// draw 4 small points
	Vec2 position[] = { Vec2(60,60), Vec2(70,70), Vec2(60,70), Vec2(70,60) };
	draw->drawPoints(position, 4, 5, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

	// draw a line
	draw->drawLine(Vec2(0, 0), Vec2(s.width, s.height), Color4F(1.0, 0.0, 0.0, 0.5));

	// draw a rectangle
	draw->drawRect(Vec2(23, 23), Vec2(7, 7), Color4F(1, 1, 0, 1));

	draw->drawRect(Vec2(15, 30), Vec2(30, 15), Vec2(15, 0), Vec2(0, 15), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

	// draw a circle
	draw->drawCircle(Vec2(240, 160) + Vec2(140, 0), 100, CC_DEGREES_TO_RADIANS(90), 50, true, 1.0f, 2.0f, Color4F(1.0, 0.0, 0.0, 0.5));

	draw->drawCircle(Vec2(240, 160) - Vec2(140, 0), 50, CC_DEGREES_TO_RADIANS(90), 30, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

	// Draw some beziers
	draw->drawQuadBezier(Vec2(s.width - 150, s.height - 150), Vec2(s.width - 70, s.height - 10), Vec2(s.width - 10, s.height - 10), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

	draw->drawQuadBezier(Vec2(0, s.height), Vec2(s.width / 2, s.height / 2), Vec2(s.width, s.height), 50, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

	draw->drawCubicBezier(Vec2(240, 160), Vec2(Vec2(240, 160).x + 30, Vec2(240, 160).y + 50), Vec2(Vec2(240, 160).x + 60, Vec2(240, 160).y - 50), Vec2(0, 160), 100, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

	draw->drawCubicBezier(Vec2(s.width - 250, 40), Vec2(s.width - 70, 100), Vec2(s.width - 30, 250), Vec2(s.width - 10, s.height - 50), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

	auto array = PointArray::create(20);
	array->addControlPoint(Vec2(0, 0));
	array->addControlPoint(Vec2(80, 80));
	array->addControlPoint(Vec2(s.width - 80, 80));
	array->addControlPoint(Vec2(s.width - 80, s.height - 80));
	array->addControlPoint(Vec2(80, s.height - 80));
	array->addControlPoint(Vec2(80, 80));
	array->addControlPoint(Vec2(s.width / 2, s.height / 2));
	draw->drawCardinalSpline(array, 0.5, 50, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

	auto array2 = PointArray::create(20);
	array2->addControlPoint(Vec2(s.width / 2, 30));
	array2->addControlPoint(Vec2(s.width - 80, 30));
	array2->addControlPoint(Vec2(s.width - 80, s.height - 80));
	array2->addControlPoint(Vec2(s.width / 2, s.height - 80));
	array2->addControlPoint(Vec2(s.width / 2, 30));
	draw->drawCatmullRom(array2, 50, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

	// open random color poly
	Vec2 vertices[] = { Vec2(0,0), Vec2(50,50), Vec2(100,50), Vec2(100,100), Vec2(50,100) };
	draw->drawPoly(vertices, 5, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

	// closed random color poly
	Vec2 vertices2[] = { Vec2(30,130), Vec2(30,230), Vec2(50,200) };
	draw->drawPoly(vertices2, 3, true, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

	// Draw 10 circles
	for (int i = 0; i < 10; i++)
	{
		draw->drawDot(Vec2(s.width / 2, s.height / 2), 10 * (10 - i), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
	}

	// Draw polygons
	Vec2 points[] = { Vec2(s.height / 4,0), Vec2(s.width,s.height / 5), Vec2(s.width / 3 * 2,s.height) };
	draw->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(1, 0, 0, 0.5), 4, Color4F(0, 0, 1, 0.5));

	// star poly (triggers buggs)
	{
		const float o = 80;
		const float w = 20;
		const float h = 50;
		Vec2 star[] = {
			Vec2(o + w,o - h), Vec2(o + w * 2, o),                        // lower spike
			Vec2(o + w * 2 + h, o + w), Vec2(o + w * 2, o + w * 2),        // right spike
																		   //              {o +w, o+w*2+h}, {o,o+w*2},                 // top spike
																		   //              {o -h, o+w}, {o,o},                         // left spike
		};

		draw->drawPolygon(star, sizeof(star) / sizeof(star[0]), Color4F(1, 0, 0, 0.5), 1, Color4F(0, 0, 1, 1));
	}

	// star poly (doesn't trigger bug... order is important un tesselation is supported.
	{
		const float o = 180;
		const float w = 20;
		const float h = 50;
		Vec2 star[] = {
			Vec2(o,o), Vec2(o + w,o - h), Vec2(o + w * 2, o),        // lower spike
			Vec2(o + w * 2 + h, o + w), Vec2(o + w * 2, o + w * 2),    // right spike
			Vec2(o + w, o + w * 2 + h), Vec2(o,o + w * 2),               // top spike
			Vec2(o - h, o + w),                                     // left spike
		};

		draw->drawPolygon(star, sizeof(star) / sizeof(star[0]), Color4F(1, 0, 0, 0.5), 1, Color4F(0, 0, 1, 1));
	}

	//draw a solid polygon
	Vec2 vertices3[] = { Vec2(60,160), Vec2(70,190), Vec2(100,190), Vec2(90,160) };
	draw->drawSolidPoly(vertices3, 4, Color4F(1, 1, 0, 1));

	//draw a solid rectangle
	draw->drawSolidRect(Vec2(10, 10), Vec2(20, 20), Color4F(1, 1, 0, 1));

	//draw a solid circle
	draw->drawSolidCircle(Vec2(240, 160) + Vec2(140, 0), 40, CC_DEGREES_TO_RADIANS(90), 50, 2.0f, 2.0f, Color4F(0.0, 1.0, 0.0, 1.0));

	// Draw segment
	draw->drawSegment(Vec2(20, s.height), Vec2(20, s.height / 2), 10, Color4F(0, 1, 0, 1));

	draw->drawSegment(Vec2(10, s.height / 2), Vec2(s.width / 2, s.height / 2), 40, Color4F(1, 0, 1, 0.5));

	// Draw triangle
	draw->drawTriangle(Vec2(10, 10), Vec2(70, 30), Vec2(100, 140), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

	for (int i = 0; i < 100; i++) {
		draw->drawPoint(Vec2(i * 7, 5), (float)i / 5 + 1, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
	}

	auto draw1 = DrawNode::create();
	this->addChild(draw1, 10);
	draw1->setLineWidth(4);
	draw1->drawLine(Vec2(0, s.height), Vec2(s.width, s.height - 20), Color4F::YELLOW);
	draw1->drawLine(Vec2(0, 0), Vec2(s.width, s.height - 20), Color4F::YELLOW);

	draw->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.2), FadeOut::create(1.2), NULL)));
	draw1->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.2), FadeOut::create(1.2), NULL)));
}