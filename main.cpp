#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

    //The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	// Cube

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	cTexture ballTxt;
	ballTxt.createTexture("Images\\Ball.png");
	cSprite ballSprite;
	ballSprite.setBall(true);
	ballSprite.setSpritePos(glm::vec2(512.0f, 384.0f));
	ballSprite.setTexture(ballTxt.getTexture());
	ballSprite.setTextureDimensions(ballTxt.getTWidth(), ballTxt.getTHeight());
	ballSprite.setWindowManager(pgmWNDMgr);

	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\starscape1024x768.png");
	cSprite spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());
	spriteBkgd.setWindowManager(pgmWNDMgr);

	cTexture rocketTxt;
	rocketTxt.createTexture("Images\\rocketSprite.png");
	cSprite topRocket;
	topRocket.setTopRocket(true);
	topRocket.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	topRocket.setSpritePos(glm::vec2(512.0f, 0.0f));
	topRocket.setSpriteTranslation(glm::vec2(5.0f, 0.0f));
	topRocket.setTexture(rocketTxt.getTexture());
	topRocket.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	topRocket.setWindowManager(pgmWNDMgr);
	
	cSprite bottomRocket;
	bottomRocket.setBottomRocket(true);
	bottomRocket.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	bottomRocket.setSpritePos(glm::vec2(512.0f, 640.0f));
	bottomRocket.setSpriteTranslation(glm::vec2(5.0f, 0.0f));
	bottomRocket.setTexture(rocketTxt.getTexture());
	bottomRocket.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	bottomRocket.setWindowManager(pgmWNDMgr);
    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		spriteBkgd.render();
		topRocket.update();
		topRocket.render();
		bottomRocket.update();
		bottomRocket.render();
		ballSprite.render();
		ballSprite.update();

		pgmWNDMgr->swapBuffers();
		//theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
		/*if (ballSprite.getRect().left < topRocket.getRect().right && 
			ballSprite.getRect().right>topRocket.getRect().left && 
			ballSprite.getRect().bottom<topRocket.getRect().top && 
			ballSprite.getRect().top>topRocket.getRect().bottom)
		{
			ballSprite.setColliding(true);
		}
		else
		{
			ballSprite.setColliding(false);
		}*/
		if (ballSprite.getSpritePos().y > bottomRocket.getSpritePos().y && ballSprite.getSpritePos().x == bottomRocket.getSpritePos().x ||
			ballSprite.getSpritePos().y < topRocket.getSpritePos().y && ballSprite.getSpritePos().x == topRocket.getSpritePos().x)
		{
			ballSprite.setColliding(true);
		}
		else
		{
			ballSprite.setColliding(false);
		}
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
