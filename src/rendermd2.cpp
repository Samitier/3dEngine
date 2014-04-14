
// Source code from Cube Engine Project
// version 2005_08_29
//
//--DELETED means deleted from original version
	//xtraverts: global variable, vertices counter
	//COMMAND macro
	//isoccluded query in rendermodel function
	//rendermodel OUTBORD, simplified
	//delayedload method
	//hash table
//
//--MODIFIED means modified from original version
	//md2::render function do not use lastmillis global variable, it is included as a parameterç
	//md2::render function do not use an user range for displaylist, glGenLists instead of [10..)

#include "rendermd2.h"

bool md2::load(char* filename)
{
    FILE* file;
    md2_header header;

    if((file= fopen(filename, "rb"))==NULL) return false;

    fread(&header, sizeof(md2_header), 1, file);
    endianswap(&header, sizeof(int), sizeof(md2_header)/sizeof(int));

    if(header.magic!= 844121161 || header.version!=8) return false;

    frames = new char[header.frameSize*header.numFrames];
    if(frames==NULL) return false;

    fseek(file, header.offsetFrames, SEEK_SET);
    fread(frames, header.frameSize*header.numFrames, 1, file);

    for(int i = 0; i < header.numFrames; ++i)
    {
        endianswap(frames + i * header.frameSize, sizeof(float), 6);
    }

    glCommands = new int[header.numGlCommands];
    if(glCommands==NULL) return false;

    fseek(file,       header.offsetGlCommands, SEEK_SET);
    fread(glCommands, header.numGlCommands*sizeof(int), 1, file);

    endianswap(glCommands, sizeof(int), header.numGlCommands);

    numFrames    = header.numFrames;
    numGlCommands= header.numGlCommands;
    frameSize    = header.frameSize;
    numTriangles = header.numTriangles;
    numVerts     = header.numVertices;

    fclose(file);
    
    mverts = new vec*[numFrames];
    loopj(numFrames) mverts[j] = NULL;

    return true;
};

float snap(int sn, float f) { return sn ? (float)(((int)(f+sn*0.5f))&(~(sn-1))) : f; };

void md2::scale(int frame, float scale, int sn)
{
    mverts[frame] = new vec[numVerts];
    md2_frame *cf = (md2_frame *) ((char*)frames+frameSize*frame);
    float sc = 16.0f/scale;
    loop(vi, numVerts)
    {
        uchar *cv = (uchar *)&cf->vertices[vi].vertex;
        vec *v = &(mverts[frame])[vi];
        v->x =  (snap(sn, cv[0]*cf->scale[0])+cf->translate[0])/sc;
        v->y = -(snap(sn, cv[1]*cf->scale[1])+cf->translate[1])/sc;
        v->z =  (snap(sn, cv[2]*cf->scale[2])+cf->translate[2])/sc;
    };
};

//--MODIFIED void md2::render(vec &light, int frame, int range, float x, float y, float z, float yaw, float pitch, float sc, float speed, int snap, int basetime)
void md2::render(vec &light, int frame, int range, float x, float y, float z, float yaw, float pitch, float sc, float speed, int snap, int lastmillis,int basetime)
{
    loopi(range) if(!mverts[frame+i]) scale(frame+i, sc, snap);
    
    glPushMatrix ();
    glTranslatef(x, y, z);
    glRotatef(yaw+180, 0, -1, 0);
    glRotatef(pitch, 0, 0, 1);
    
	glColor3fv((float *)&light);

    if(displaylist && frame==0 && range==1)
    {
		glCallList(displaylist);
		//--DELETED xtraverts += displaylistverts;
    }
    else
    {
		if(frame==0 && range==1)
		{
			//--MODIFIED static int displaylistn = 10;
			//--MODIFIED glNewList(displaylist = displaylistn++, GL_COMPILE);
			displaylist = glGenLists(1);
			glNewList(displaylist, GL_COMPILE);
			//--DELETED displaylistverts = xtraverts;
		};
		
		int time = lastmillis-basetime;
		int fr1 = (int)(time/speed);
		float frac1 = (time-fr1*speed)/speed;
		float frac2 = 1-frac1;
		fr1 = fr1%range+frame;
		int fr2 = fr1+1;
		if(fr2>=frame+range) fr2 = frame;
		vec *verts1 = mverts[fr1];
		vec *verts2 = mverts[fr2];

		for(int *command = glCommands; (*command)!=0;)
		{
			int numVertex = *command++;
			if(numVertex>0) { glBegin(GL_TRIANGLE_STRIP); }
			else            { glBegin(GL_TRIANGLE_FAN); numVertex = -numVertex; };

			loopi(numVertex)
			{
				float tu = *((float*)command++);
				float tv = *((float*)command++);
				glTexCoord2f(tu, tv);
				int vn = *command++;
				vec &v1 = verts1[vn];
				vec &v2 = verts2[vn];
				#define ip(c) v1.c*frac2+v2.c*frac1
				glVertex3f(ip(x), ip(z), ip(y));
			};

			//--DELETED xtraverts += numVertex;

			glEnd();
		};
		
		if(displaylist)
		{
			glEndList();
			//--DELETED displaylistverts = xtraverts-displaylistverts;
		};
	};

    glPopMatrix();
}