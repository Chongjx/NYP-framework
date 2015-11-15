#include "GameObject2D.h"

GameObject2D::GameObject2D()
{
}

GameObject2D::~GameObject2D()
{
}

void GameObject2D::setHitbox(OBB2D hitbox)
{
	this->obbHitbox = hitbox;
}

OBB2D GameObject2D::getHitbox(void)
{
	return this->obbHitbox;
}

void GameObject2D::updateHitbox(void)
{
	obbHitbox.setMidPoint(Vector2(this->position.x, this->position.y));
	Mtx44 vertex = this->getProperties().modelProperties;

	obbHitbox.create2Dhitbox
		(vertex * Vector2(obbHitbox.getHalfLength(), -obbHitbox.getHeight()) + obbHitbox.getMidPoint(),
		vertex * Vector2(obbHitbox.getHalfLength(), obbHitbox.getHeight()) + obbHitbox.getMidPoint(),
		vertex * Vector2(-obbHitbox.getHalfLength(), obbHitbox.getHeight()) + obbHitbox.getMidPoint(),
		vertex * Vector2(obbHitbox.getHalfLength(), -obbHitbox.getHeight()) + obbHitbox.getMidPoint(),
		obbHitbox.getName()
		);
}