
#include "MD2Model.h"

int animlist[21][3] = 
{
    // first, last, fps
    {   0,  39,  9 },   // STAND
    {  40,  45, 10 },   // RUN
    {  46,  53, 10 },   // ATTACK
    {  54,  57,  7 },   // PAIN_A
    {  58,  61,  7 },   // PAIN_B
    {  62,  65,  7 },   // PAIN_C
    {  66,  71,  7 },   // JUMP
    {  72,  83,  7 },   // FLIP
    {  84,  94,  7 },   // SALUTE
    {  95, 111, 10 },   // FALLBACK
    { 112, 122,  7 },   // WAVE
    { 123, 134,  6 },   // POINT
    { 135, 153, 10 },   // CROUCH_STAND
    { 154, 159,  7 },   // CROUCH_WALK
    { 160, 168, 10 },   // CROUCH_ATTACK
    { 196, 172,  7 },   // CROUCH_PAIN
    { 173, 177,  5 },   // CROUCH_DEATH
    { 178, 183,  7 },   // DEATH_FALLBACK
    { 184, 189,  7 },   // DEATH_FALLFORWARD
    { 190, 197,  7 },   // DEATH_FALLBACKSLOW
    { 198, 198,  5 },   // BOOM
};

MD2Model::MD2Model()
{
	model = NULL;
	color.x = 1.0f;
	color.y = 1.0f;
	color.z = 1.0f;
	anim = -1;			//Static, Dynamic when >= 0
}
MD2Model::~MD2Model()
{
	if(model) delete model;
}
bool MD2Model::Load(char *filename)
{
	char tris[128],skin[128];

	sprintf(tris,"assets/models/%s/tris.md2",filename);
	sprintf(skin,"assets/models/%s/skin.jpg",filename);
	
	if(!tex.Load(skin,GL_RGB,GL_REPEAT,GL_REPEAT,GL_LINEAR,GL_LINEAR_MIPMAP_LINEAR,true))
		return false;

	model = new md2();
	if(!model) return false;

	return model->load(tris);
}
void MD2Model::SetAnimation(int anim_state)
{
	anim = anim_state;
	frame = animlist[anim][0];
}
void MD2Model::SetColor(float r,float g,float b)
{
	color.x = r;
	color.y = g;
	color.z = b;
}
void MD2Model::Render(float x,float y,float z)
{
	Render(x,y,z,0,0);
}
void MD2Model::Render(float x,float y,float z,float yaw,float pitch)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex.GetID());

	//md2::render(vec &light, int frame, int range, float x, float y, float z, float yaw, float pitch, float sc, float speed, int snap, int lastmillis,int basetime)
	if(anim >= 0)
	{
		model->render(color,frame,1, x,y,z, yaw,pitch,1, 10,0,0,0);
		frame++;
		if(frame > animlist[anim][1])
			frame = animlist[anim][0];
	}
	else
	{
		model->render(color,0,1, x,y,z, yaw,pitch,1, 10,0,0,0);
	}

	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f,1.0f,1.0f);
}
void MD2Model::Render(	float x,float y,float z,float yaw,float pitch,
						float frame,float range,float scale,float speed,float snap,float time_last,float time_base)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex.GetID());
	model->render(color,frame,range, x,y,z, yaw,pitch,scale, speed,snap,time_last,time_base);
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f,1.0f,1.0f);
}