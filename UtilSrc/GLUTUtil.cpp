#include "Utils.h"
void GLUTUtil::
Begin2D(const R3Viewer* viewer)
{
    glMatrixMode (GL_PROJECTION);
    glPushMatrix(); // projection
    glLoadIdentity ();
    glOrtho (0, viewer->Viewport().Width(), 0,
			 viewer->Viewport().Height(), 0, 1);
    glMatrixMode (GL_MODELVIEW);
    glPushMatrix(); // modelview
    glLoadIdentity();
    glTranslatef(0.375, 0.375, 0);
    glPushAttrib(GL_CURRENT_BIT|GL_ENABLE_BIT);
    glDisable(GL_LIGHTING);
}

void GLUTUtil::
End2D(void)
{
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix(); // modelview
    glMatrixMode (GL_MODELVIEW);
    glPopMatrix(); // projection
}

void GLUTUtil::
DrawText(const R3Point& p, const char *s)
{
	glDisable(GL_LIGHTING);
	glColor3f(0, 0, 0);
    // Draw text string s and position p
    glRasterPos3d(p[0], p[1], p[2]);
    while (*s) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *(s++));
}

void GLUTUtil::
DrawText(const R2Point& p, const char *s, const R3Viewer* viewer)
{
	glDisable(GL_LIGHTING);
	glColor3f(0, 0, 0);
    // Draw text string s and position p
    R3Ray ray = viewer->WorldRay((int) p[0], (int) p[1]);
    R3Point position = ray.Point(2 * viewer->Camera().Near());
    glRasterPos3d(position[0], position[1], position[2]);
	//    while (*s) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *(s++));
    while (*s) glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *(s++));
}
