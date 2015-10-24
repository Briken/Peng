/*
=================
cSprite.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CSPRITE_H
#define _CSPRITE_H
#include "cInputMgr.h"
#include "GameConstants.h"
#include "cWNDManager.h"

class cSprite
{
private:
	// position, rotation, scalling
	glm::vec2 spritePos2D;
	glm::vec2 spriteTranslation;
	glm::vec2 spriteCentre;
	glm::vec2 spriteScaling;
	float spriteScalingRotation;
	float spriteRotation;
	glm::mat4x4 spriteTransformMatrix;
	RECT boundingRect;

	//texturing
	glm::vec2 spriteVertexData[4];
	glm::vec2 spriteTexCoordData[4];

	// Texture width & Height
	int textureWidth;
	int textureHeight;
	GLuint GLTextureID;
	cInputMgr* m_InputMgr;

	//collisions
	cWNDManager* m_Window;
	bool isColliding;
	bool isBall = false;
	bool isTopPaddle = false;
	bool isBottomPaddle = false;
	float hSpeed = 0;
	float vSpeed = 3;
	int hDirection = 1;
	int vDirection = 1;

public:
	cSprite();			// Default constructor
	//cSprite(glm::vec3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	~cSprite();			// Destructor
	void render();
	void setSpriteTexCoordData();
	glm::vec2 getSpritePos();  // Return the sprites current position
	void setSpritePos(glm::vec2 sPosition); // set the position of the sprite
	GLuint getTexture();  // Return the sprites current image
	void setTexture(GLuint GLtexID);  // set the image of the sprite
	void setTextureDimensions(int texWidth, int textHeight);
	void setSpriteTranslation(glm::vec2 translation); // Set the amount of movement on the x & y axis
	glm::vec2 getSpriteTranslation();  // return the amount of movement on the x & y axis
	void attachInputMgr(cInputMgr* inputMgr);  // Attach the Input Manager
	void update();
	RECT getRect()
	{
		return boundingRect;
	}
	void setColliding(bool newColliding)
	{
		isColliding = newColliding;
	}
	void setWindowManager(cWNDManager* window)
	{
		m_Window = window;
	}

	void setBall(bool newBall)
	{
		isBall = newBall;
	}
	void setTopRocket(bool isTopRocket)
	{
		isTopPaddle = isTopRocket;
	}
	void setBottomRocket(bool isBottomRocket)
	{
		isBottomPaddle = isBottomRocket;
	}
};
#endif