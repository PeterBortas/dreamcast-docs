/* KallistiOS 1.1.8

   vfzclip.c
   (c)2001, 2002 Trilinear@hotmail.com, Paul Boese

   mods by Heinrich Tillack, 2002
*/

/*
    A demonstration of the NEAR-Z-Clipper that has been
    incorporated into KGL-X. Use the joystick to rotate the view, the D-Pad
    to move forward and back, and the A button to toggle the Z-Clipper
    on or off. Please note that the code works with GL_TRIANGLES and GL_TRIANGLE_STRIPS only.
    
*/

#include <kos.h>


#include <GL/gl.h>
#include <GL/glu.h>


#include <pcx/pcx.h>

//#define SDIFF 0.001f

#define SDIFF 0.0f

CVSID("$Id");



inline void quad() {
	float x=-1.0f;
	float y=-1.0f;

	float incr=2.0f;


#if 0
	glBegin(GL_QUADS);
		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glColor3f(1.0f,0.5f,0.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);
		glVertex3f(-1.0f,-1.0f, 1.0f);
		glColor3f(1.0f,0.0f,1.0f);
		glVertex3f( 1.0f, 1.0f,-1.0f);
		glVertex3f( 1.0f, 1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f, 1.0f);
		glVertex3f( 1.0f,-1.0f,-1.0f);
	glEnd();
#else
	glBegin(GL_TRIANGLES);


	while (x<=1.0f-incr) {
		while (y<=1.0f-incr) {
			/* Front face */
			glTexCoord2f(1.0f-SDIFF,0.0f+SDIFF);
			glVertex3f(x,  y+incr,     0.0f);
			glTexCoord2f(0.0f+SDIFF,0.0f+SDIFF);
			glVertex3f(x+incr, y+incr, 0.0f);
			glTexCoord2f(0.0f+SDIFF,1.0f-SDIFF);
			glVertex3f(x+incr, y, 0.0f);

			glTexCoord2f(1.0f-SDIFF,0.0f+SDIFF);
			glVertex3f(x, y+incr,      0.0f);
			glTexCoord2f(0.0f+SDIFF,1.0f-SDIFF);
			glVertex3f(x+incr, y, 0.0f);
			glTexCoord2f(1.0f-SDIFF,1.0f-SDIFF);
			glVertex3f(x, y,      0.0f);
			y+=incr;
		}
		y=-1.0f;
		x+=incr;
	}
	glEnd();
#endif
}

void cube() {

		glPushMatrix();
		glTranslatef(0.0f, 0.0f, 1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0f, 0.0f, -1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f,1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);
		quad();
		glPopMatrix();
		glPushMatrix();
		glRotatef(-90, 0.0f, 1.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 1.0f);
		quad();
		glPopMatrix();
}


/* Load a texture using pcx_load_texture and glKosTex2D */
void loadtxr(const char *fn, GLuint *txr) {
	kos_img_t img;
	pvr_ptr_t txaddr;

	if (pcx_to_img(fn, &img) < 0) {
		printf("can't load %s\n", fn);
		return;
	}

	txaddr = pvr_mem_malloc(img.w * img.h * 2);
	pvr_txr_load_kimg(&img, txaddr, PVR_TXRLOAD_INVERT_Y);
	kos_img_free(&img, 0);

	glGenTextures(1, txr);

	glBindTexture(GL_TEXTURE_2D, *txr);

	glKosTex2D(GL_RGB565_TWID, img.w, img.h, txaddr);
}

extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT);
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
	uint8		addr;
	cont_cond_t	cond;
	GLuint	texture;
	float	z = -1.0f;
	float	rx = 0.0f;
	float	ry = 0.0f;
	int	zclip = true;
	int	a_pressed = false;

	/* Normal init */
	pvr_init_defaults();

	/* Get KGL stuff initialized */
	glKosInit();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);

	//gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 10000.0f);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);


	/* Expect CW verts */
	glFrontFace(GL_CW);

	/* Load a texture and make to look nice */
	loadtxr("/rd/crate.pcx", &texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);


	glClearColor(0.3f, 0.4f, 0.5f, 1.0f);

	while(1) {
		
		addr = maple_first_controller();
		if (addr == 0)
			continue;
		if (cont_get_cond(addr, &cond) < 0)
		continue;
	
		if (!(cond.buttons & CONT_START)) {
			break;
		}
	

		if (!(cond.buttons & CONT_DPAD_UP))
			z -= 1.2f;
		if (!(cond.buttons & CONT_DPAD_DOWN))
			z += 1.2f;
		if (!(cond.buttons & CONT_A)) 
		 {
			// if (a_pressed) continue;
			a_pressed = true;
			zclip = !zclip;
		}
		else {
			a_pressed  = false;
		}

		rx+=((float)cond.joyy)/100.0f;
		ry+=((float)cond.joyx)/100.0f;

		/* Begin frame */
		glKosBeginFrame();

		glLoadIdentity();

		glTranslatef(0.0f, 0.0f, -50.0f-z);

		glRotatef(-90, 1.0f, 0.0f, 0.0f);
		glRotatef(rx, 1.0f, 0.0f, 0.0f);
		glRotatef(ry, 0.0f, 0.0f, 1.0f);

		glPushMatrix();
		glBindTexture( GL_TEXTURE_2D, texture);
		glScalef(50.0f, 50.0f, 50.0f);
		glTranslatef(0.0f, 0.0f, 0.75f);

		if (zclip) glEnable(GL_KOS_NEARZ_CLIPPING);
		cube();
		glDisable(GL_KOS_NEARZ_CLIPPING);

		glPopMatrix();

		/* Finish the frame */
		glKosFinishFrame();
	}
	return 0;
}

