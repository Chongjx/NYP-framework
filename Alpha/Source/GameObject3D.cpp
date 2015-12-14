#include "GameObject3D.h"

GameObject3D::GameObject3D()
{
}

GameObject3D::~GameObject3D()
{
}

void GameObject3D::setHitbox(OBB3D hitbox)
{
	this->obbHitbox = hitbox;
}

void GameObject3D::setHitbox(Vector3 midPoint, float length, float height, float depth, const string name)
{
	this->obbHitbox.create3Dhitbox(midPoint, length, height, depth, name);
}

OBB3D GameObject3D::getHitbox(void)
{
	return this->obbHitbox;
}

void GameObject3D::updateHitbox(Vector3 finalPos)
{
	obbHitbox.setMidPoint(finalPos);
	Mtx44 vertex = this->getProperties().modelProperties;

	obbHitbox.create3Dhitbox
		(vertex * Vector3(obbHitbox.getHalfLength(), -obbHitbox.getHalfHeight(), obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(obbHitbox.getHalfLength(), obbHitbox.getHalfHeight(), obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(-obbHitbox.getHalfLength(), obbHitbox.getHalfHeight(), obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(-obbHitbox.getHalfLength(), -obbHitbox.getHalfHeight(), obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(obbHitbox.getHalfLength(), -obbHitbox.getHalfHeight(), -obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(obbHitbox.getHalfLength(), obbHitbox.getHalfHeight(), -obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(-obbHitbox.getHalfLength(), obbHitbox.getHalfHeight(), -obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(-obbHitbox.getHalfLength(), -obbHitbox.getHalfHeight(), -obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(), obbHitbox.getName()
		);
}

void GameObject3D::updateHitbox(void)
{
	obbHitbox.setMidPoint(this->position);
	Mtx44 vertex = this->getProperties().modelProperties;

	obbHitbox.create3Dhitbox
		(vertex * Vector3(obbHitbox.getHalfLength(), -obbHitbox.getHalfHeight(), obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(obbHitbox.getHalfLength(), obbHitbox.getHalfHeight(), obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(-obbHitbox.getHalfLength(), obbHitbox.getHalfHeight(), obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(-obbHitbox.getHalfLength(), -obbHitbox.getHalfHeight(), obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(obbHitbox.getHalfLength(), -obbHitbox.getHalfHeight(), -obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(obbHitbox.getHalfLength(), obbHitbox.getHalfHeight(), -obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(-obbHitbox.getHalfLength(), obbHitbox.getHalfHeight(), -obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(),
		vertex * Vector3(-obbHitbox.getHalfLength(), -obbHitbox.getHalfHeight(), -obbHitbox.getHalfDepth()) + obbHitbox.getMidPoint(), obbHitbox.getName()
		);
}