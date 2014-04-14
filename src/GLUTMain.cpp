
#include "Globals.h"
#include "Game.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

Game game;

void AppRender()
{
	game.render();
}
void AppKeyboard(unsigned char key, int x, int y)
{
	game.readKeyboard(key,x,y,true);
}
void AppKeyboardUp(unsigned char key, int x, int y)
{
	game.readKeyboard(key,x,y,false);
}
void AppSpecialKeys(int key, int x, int y)
{
	game.readKeyboard(key,x,y,true);
}
void AppSpecialKeysUp(int key, int x, int y)
{
	game.readKeyboard(key,x,y,false);
}
void AppMouse(int button, int state, int x, int y)
{
	game.readMouse(button,state,x,y);
}
void AppIdle()
{
	if(!game.Loop()) exit(0);
}
void AppMouseMotion(int x, int y) {
	game.readMousePosition(x, y);
}
void main(int argc, char** argv)
{
	int res_x,res_y,pos_x,pos_y;

	//GLUT initialization
	glutInit(&argc, argv);

	//RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x>>1)-(SCREEN_WIDTH>>1);
	pos_y = (res_y>>1)-(SCREEN_HEIGHT>>1);
	
	glutInitWindowPosition(pos_x,pos_y);
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutCreateWindow("My Awesome 3D Game!");

	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	//Make the default cursor disappear
	glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutDisplayFunc(AppRender);			
	glutKeyboardFunc(AppKeyboard);		
	glutKeyboardUpFunc(AppKeyboardUp);	
	glutSpecialFunc(AppSpecialKeys);	
	glutSpecialUpFunc(AppSpecialKeysUp);
	glutMouseFunc(AppMouse);
	glutIdleFunc(AppIdle);
	glutPassiveMotionFunc(AppMouseMotion);

	//Game initializations
	game.init();

	//Application loop
	glutMainLoop();	
}
