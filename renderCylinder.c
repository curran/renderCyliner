/**
 * Rendering a Cylinder Between Two Points in OpenGL
 * -------------------------------------------------
 * This problem is more of a pain than one would think!
 * Here is some code that does it, based on the implementation
 * which used to be posted at the following URL by Joel J. Parris:
 * http://home.neo.rr.com/jparris/OpenGL%20-%20draw%20cylinder%20between%202%20pts.htm
 *
 * Unfortunately Joel's link is down, and I'm not totally sure what
 * kind of license he put on it if any. I hope he doesn't mind that I declare:
 *
 * This code is in the public domain.
 *
 * I would welcome any improvements as code contributions.
 *
 * -- Curran Kelleher 12/22/2010
 */
 
 /*
  * Edited using the suggestions found in the replies to the blog post (mostly Edward's version)
  * And some tinkering of my own in the edge cases where it still messed up
  * Any further bugfixes are welcome.
  * -- Joost 08/10/2012
*/
void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric)
{
  float vx = x2-x1;
  float vy = y2-y1;
  float vz = z2-z1;
  float v = sqrt( vx*vx + vy*vy + vz*vz );
  float ax;

  if (fabs(vz) < 1.0e-3) {
    ax = 57.2957795*acos( vx/v ); // rotation angle in x-y plane
    if ( vy <= 0.0 )
      ax = -ax;
  }
  else {
    ax = 57.2957795*acos( vz/v ); // rotation angle
    if ( vz <= 0.0 )
      ax = -ax;
  }
  
  float rx = -vy*vz;
  float ry = vx*vz;
  
  glPushMatrix();
  //draw the cylinder body
  glTranslatef( x1,y1,z1 );
  if (fabs(vz) < 1.0e-3) {
    glRotated(90.0, 0, 1, 0.0); // Rotate & align with x axis
    glRotated(ax, -1.0, 0.0, 0.0); // Rotate to point 2 in x-y plane
  }
  else {
    glRotated(ax, rx, ry, 0.0); // Rotate about rotation vector
  }
  gluQuadricOrientation(quadric,GLU_OUTSIDE);
  gluCylinder(quadric, radius, radius, v, subdivisions, 1);

  //draw the first cap
  gluQuadricOrientation(quadric,GLU_INSIDE);
  gluDisk( quadric, 0.0, radius, subdivisions, 1);
  glTranslatef( 0,0,v );

  //draw the second cap
  gluQuadricOrientation(quadric,GLU_OUTSIDE);
  gluDisk( quadric, 0.0, radius, subdivisions, 1);
  glPopMatrix();
}

void renderCylinder_convenient(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions)
{
  //the same quadric can be re-used for drawing many cylinders
  GLUquadricObj *quadric=gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  renderCylinder(x1,y1,z1,x2,y2,z2,radius,subdivisions,quadric);
  gluDeleteQuadric(quadric);
}
