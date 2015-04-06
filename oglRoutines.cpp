/*
 *  oglRoutines.cpp
 *  rpDynTargetDevice
 *
 *  Created by Risto Puukko on 13.6.2012.
 *  Copyright 2012 ristopuukko. All rights reserved.
 *
 */

#include "oglRoutines.h"
#ifndef rpDynTargetDevice_H
#include "rpDynTargetDevice.h"
#endif


void rpDynTargetDevice::DrawSphere(const float r) {
	DrawCircleXY(false, r,30,0.0f);
	DrawCircleXZ(false, r,30,0.0f);
	DrawCircleYZ(false, r,30,0.0f);
}


//	These functions draw a 2 crossed lines in the specified plane.
//	\brief	w	-	the width
//	\brief	h	-	the height
//
/*
void rpDynTargetDevice::DrawCrossXY(const float w,const float h) {
	glBegin(GL_LINES);
	glVertex3f( -0.5f*w, 0, 0 );
	glVertex3f(  0.5f*w, 0, 0 );
	glVertex3f( 0,  0.5f*h, 0 );
	glVertex3f( 0, -0.5f*h, 0 );
	glEnd();
}
void rpDynTargetDevice::DrawCrossXZ(const float w,const float h) {
	glBegin(GL_LINES);
	glVertex3f( -0.5f*w, 0, 0 );
	glVertex3f(  0.5f*w, 0, 0 );
	glVertex3f( 0,0,  0.5f*h );
	glVertex3f( 0,0, -0.5f*h );
	glEnd();
}
void rpDynTargetDevice::DrawCrossYZ(const float w,const float h) {
	glBegin(GL_LINES);
	glVertex3f( 0, -0.5f*w, 0 );
	glVertex3f( 0,  0.5f*w, 0 );
	glVertex3f( 0, 0,  0.5f*h );
	glVertex3f( 0, 0, -0.5f*h );
	glEnd();
}

//	These functions draw a quad in the specified plane.
//	\brief	w	-	the width
//	\brief	h	-	the height
//
void rpDynTargetDevice::DrawQuadXY(const float w,const float h) {
	glBegin(GL_LINE_LOOP);
	glVertex3f( -0.5f*w, -0.5f*h, 0 );
	glVertex3f(  0.5f*w, -0.5f*h, 0 );
	glVertex3f(  0.5f*w,  0.5f*h, 0 );
	glVertex3f( -0.5f*w,  0.5f*h, 0 );
	glEnd();
}
void rpDynTargetDevice::DrawQuadXZ(const float w,const float h) {
	glBegin(GL_LINE_LOOP);
	glVertex3f( -0.5f*w, 0, -0.5f*h );
	glVertex3f(  0.5f*w, 0, -0.5f*h );
	glVertex3f(  0.5f*w, 0,  0.5f*h );
	glVertex3f( -0.5f*w, 0,  0.5f*h );
	glEnd();
}
void rpDynTargetDevice::DrawQuadYZ(const float w,const float h) {
	glBegin(GL_LINE_LOOP);
	glVertex3f( 0, -0.5f*w, -0.5f*h );
	glVertex3f( 0,  0.5f*w, -0.5f*h );
	glVertex3f( 0,  0.5f*w,  0.5f*h );
	glVertex3f( 0, -0.5f*w,  0.5f*h );
	glEnd();
}

void rpDynTargetDevice::DrawFilledQuadXY(const float w,const float h) {
	glBegin(GL_QUADS);
	glVertex3f( -0.5f*w, -0.5f*h, 0 );
	glVertex3f(  0.5f*w, -0.5f*h, 0 );
	glVertex3f(  0.5f*w,  0.5f*h, 0 );
	glVertex3f( -0.5f*w,  0.5f*h, 0 );
	glEnd();
}
void rpDynTargetDevice::DrawFilledQuadXZ(const float w,const float h) {
	glBegin(GL_QUADS);
	glVertex3f( -0.5f*w, 0, -0.5f*h );
	glVertex3f(  0.5f*w, 0, -0.5f*h );
	glVertex3f(  0.5f*w, 0,  0.5f*h );
	glVertex3f( -0.5f*w, 0,  0.5f*h );
	glEnd();
}
void rpDynTargetDevice::DrawFilledQuadYZ(const float w,const float h) {
	glBegin(GL_QUADS);
	glVertex3f( 0, -0.5f*w, -0.5f*h );
	glVertex3f( 0,  0.5f*w, -0.5f*h );
	glVertex3f( 0,  0.5f*w,  0.5f*h );
	glVertex3f( 0, -0.5f*w,  0.5f*h );
	glEnd();
}

void rpDynTargetDevice::DrawCube(const float w,const float h,const float d) {
	glPushMatrix();
	glTranslatef(0,0,d/2);
	DrawQuadXY(w,h);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,-d/2);
	DrawQuadXY(w,h);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,h/2,0);
	DrawQuadXZ(w,d);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-h/2,0);
	DrawQuadXZ(w,d);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(w/2,0,0);
	DrawQuadYZ(h,d);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-w/2,0,0);
	DrawQuadYZ(h,d);
	glPopMatrix();
}

void rpDynTargetDevice::DrawFilledCube(const float w,const float h,const float d) {
	glPushMatrix();
	glTranslatef(0,0,d/2);
	DrawFilledQuadXY(w,h);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,-d/2);
	DrawFilledQuadXY(w,h);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0,h/2,0);
	DrawFilledQuadXZ(w,d);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-h/2,0);
	DrawFilledQuadXZ(w,d);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(w/2,0,0);
	DrawFilledQuadYZ(h,d);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-w/2,0,0);
	DrawFilledQuadYZ(h,d);
	glPopMatrix();
}

//	These functions draw a 2 crossed lines in the specified plane.
//	\brief	r	-	the radius
//	\brief	h	-	the height
//
void rpDynTargetDevice::DrawCylinderXY(const float r,const float h)
{
	glPushMatrix();
	glTranslatef(0,0,h/2);
	DrawCircleXY(r,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,-h/2);
	DrawCircleXY(r,30);
	glPopMatrix();
	
	glBegin(GL_LINES);
	glVertex3f(r,0,-h/2);
	glVertex3f(r,0,h/2);
	
	glVertex3f(-r,0,-h/2);
	glVertex3f(-r,0,h/2);
	
	glVertex3f(0,r,-h/2);
	glVertex3f(0,r,h/2);
	
	glVertex3f(0,-r,-h/2);
	glVertex3f(0,-r,h/2);
	glEnd();
}
void rpDynTargetDevice::DrawCone(const float r,const float h)
{
	glPushMatrix();
	glTranslatef(0,-h/2,0);
	DrawCircleXZ(r,30);
	glPopMatrix();
	
	glBegin(GL_LINES);
	glVertex3f(r,-h/2,0);
	glVertex3f(0,h/2,0);
	
	glVertex3f(-r,-h/2,0);
	glVertex3f(0,h/2,0);
	
	glVertex3f(0,-h/2,r);
	glVertex3f(0,h/2,0);
	
	glVertex3f(0,-h/2,-r);
	glVertex3f(0,h/2,0);
	glEnd();
}
void rpDynTargetDevice::DrawCylinderXZ(const float r,const float h)
{
	glPushMatrix();
	glTranslatef(0,h/2,0);
	DrawCircleXZ(r,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,-h/2,0);
	DrawCircleXZ(r,30);
	glPopMatrix();
	
	glBegin(GL_LINES);
	glVertex3f(r,-h/2,0);
	glVertex3f(r,h/2,0);
	
	glVertex3f(-r,-h/2,0);
	glVertex3f(-r,h/2,0);
	
	glVertex3f(0,-h/2,r);
	glVertex3f(0,h/2,r);
	
	glVertex3f(0,-h/2,-r);
	glVertex3f(0,h/2,-r);
	glEnd();
}
void rpDynTargetDevice::DrawCylinderYZ(const float r,const float h)
{
	glPushMatrix();
	glTranslatef(h/2,0,0);
	DrawCircleYZ(r,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-h/2,0,0);
	DrawCircleYZ(r,30);
	glPopMatrix();
	
	glBegin(GL_LINES);
	glVertex3f(-h/2,r,0);
	glVertex3f(h/2,r,0);
	
	glVertex3f(-h/2,-r,0);
	glVertex3f(h/2,-r,0);
	
	glVertex3f(-h/2,0,r);
	glVertex3f(h/2,0,r);
	
	glVertex3f(-h/2,0,-r);
	glVertex3f(h/2,0,-r);
	glEnd();
}
*/
//	These functions draw a circle on the specified plane
//	\param	r		-	the radius of the circle
//	\param	divs	-	the number of divisions around the circle
//
void rpDynTargetDevice::DrawCircleXY(const bool x_ray, const float r,const int divs, const float offset) {
	glBegin(GL_LINE_LOOP);
	for(int i=0;i!=divs;++i)
	{
		float angle = (i*360.0f/divs) * 3.1415926535898f/180.0f;
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(ca*r,sa*r,(0.0f + offset));
	}
	glEnd();
}
void rpDynTargetDevice::DrawCircleXZ(const bool x_ray, const float r,const int divs, const float offset) {

	if (x_ray) {
		glPushAttrib(MGL_ALL_ATTRIB_BITS);
		glClearDepth(0.0);
		glDepthFunc(MGL_ALWAYS);	
	}
	glBegin(GL_LINE_LOOP);
	for(int i=0;i!=divs;++i)
	{
		float angle = (i*360.0f/divs) * 3.1415926535898f/180.0f;
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(ca*r,(0.0f + offset),sa*r);
	}
	glEnd();
	if (x_ray)
		glPopAttrib();
}
void rpDynTargetDevice::DrawCircleYZ(const bool x_ray, const float r,const int divs, const float offset) {
	glBegin(GL_LINE_LOOP);
	for(int i=0;i!=divs;++i)
	{
		float angle = (i*360.0f/divs) * (3.1415926535898f/180.0f);
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(( 0.0f + offset),ca*r,sa*r);
	}
	glEnd();
}
/*
void rpDynTargetDevice::DrawFilledCircleXY(const float r,const int divs) {
	glBegin(GL_POLYGON);
	for(int i=0;i!=divs;++i)
	{
		float angle = (i*360.0f/divs) * 3.1415926535898f/180.0f;
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(ca*r,sa*r,0.0f);
	}
	glEnd();
}
void rpDynTargetDevice::DrawFilledCircleXZ(const float r,const int divs) {
	glBegin(GL_POLYGON);
	for(int i=0;i!=divs;++i)
	{
		float angle = (i*360.0f/divs) * 3.1415926535898f/180.0f;
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(ca*r,0.0f,sa*r);
	}
	glEnd();
}
void rpDynTargetDevice::DrawFilledCircleYZ(const float r,const int divs) {
	glBegin(GL_POLYGON);
	for(int i=0;i!=divs;++i)
	{
		float angle = (i*360.0f/divs) * (3.1415926535898f/180.0f);
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(0.0f,ca*r,sa*r);
	}
	glEnd();
}
*/
//	These functions draw an arc on the specified plane
//	\param	r		-	the radius of the circle
//	\param	sa		-	the start angle in degrees
// 	\param	ea		-	the end angle in degrees
//	\param	divs	-	the number of divisions around the circle
//
//void rpDynTargetDevice::DrawArcXY(const float r,const float sa,const float ea,const int divs){
	
//}
//void rpDynTargetDevice::DrawArcXZ(const float r,const float sa,const float ea,const int divs, const float offset){

void rpDynTargetDevice::DrawDottedCircleXZ(const bool x_ray, M3dView::DisplayStatus status, const float r,const int divs, const float offset) {

	glPushAttrib(MGL_ALL_ATTRIB_BITS);	
	MColor outlineCol = colorRGB(status);
	bool drawpoly = false;
	if(status == M3dView::kLead ) {
		glColor4f(0.0f,1.0f,0.0f,0.3f);
		drawpoly = true;
	} else {
		// Otherwise i use a slightly varied intensity of the colour
		glColor4f(outlineCol.r,outlineCol.g,outlineCol.b,0.5f);
		drawpoly = false;
	}
	
	if (x_ray) {
		glClearDepth(0.0);
		glDepthFunc(MGL_ALWAYS);	
	}
	
	glBegin(MGL_LINES);
	for(int i=0;i!=divs;i++)
	{
		int n = i % 2;
		if (n != 0) {
			float angle = (i*360.0f/divs) * 3.1415926535898f/180.0f;
			float ca = cos(angle);
			float sa = sin(angle);
			glVertex3f(ca*r,(0.0f + offset),sa*r);
			angle += .1;
			ca = cos(angle);
			sa = sin(angle);
			glVertex3f(ca*r,(0.0f + offset),sa*r);
		}
	}
	glEnd();

	if(drawpoly) {

	
		glEnable(MGL_BLEND);
		glBlendFunc(MGL_SRC_ALPHA, MGL_ONE_MINUS_SRC_ALPHA);
		glBegin(MGL_POLYGON);
		
		for(int i=0;i!=divs;++i)
		{
			float angle = (i*360.0f/divs) * (3.1415926535898f/180.0f);
			float ca = cos(angle);
			float sa = sin(angle);
			glVertex3f(ca*r,(0.0f + offset),sa*r);
		}
		
		glEnd();
		
		glDisable(MGL_BLEND);
	}
	
	glPopAttrib();

}
//********************************
//quadric (parabolic) curve points 
/*
#define f0(t) (1.-(t))*(1.-(t))
#define f1(t) 2.*(t)*(1.-(t))
#define f2(t) (t)*(t)
*/
// *******************************

void rpDynTargetDevice::DrawParabolicCurve( M3dView::DisplayStatus status, M3dView::DisplayStyle style, int index, const int div, const float offset)
{

	//cout << rbdData.empty() << endl;
	if (!rbdData.empty()) {

        glPushAttrib(MGL_ALL_ATTRIB_BITS);
		
		if (xRay) {
			glClearDepth(0.0);
			glDepthFunc(MGL_ALWAYS);	
		}

		
		glEnable(MGL_BLEND);
		glBlendFunc(MGL_SRC_ALPHA, MGL_ONE_MINUS_SRC_ALPHA);
		
        glBegin(MGL_LINE_STRIP);
		
        //cout << "curveOpacity = "<<curveOpacity<<endl;
        //cout << " ( status == M3dView::kActive ) = " << ( status == M3dView::kActive ) << endl;
        if ( status == M3dView::kActive ) {
            glColor4f(0.0f,1.0f,0.0f, curveOpacity);
        } else {
            glColor4f(0.0f,0.0f,1.0f, curveOpacity);
        }
		
		
		//MVector start(rbdData[index].start_x,rbdData[index].start_y,rbdData[index].start_z);
		//MVector mid(rbdData[index].mid_x, rbdData[index].mid_y,rbdData[index].mid_z);
		//MVector end(rbdData[index].end_x, rbdData[index].end_y,rbdData[index].end_z);
		//MVector dir = end-start;
		vec3f dir = rbdData[index].end - rbdData[index].start;
        
        
        double range = norm2(dir);
        
		//float dum = MVector(MVector(mid.x,0,mid.z) - start).length() ;
        vec3f midInGround(rbdData[index].mid[0], 0, rbdData[index].mid[2]);
		float dum = norm2(midInGround - rbdData[index].start) ;
        
		//float a =-1 * rbdData[index].mid_y / pow(dum,2);
        float a =-1 * rbdData[index].mid[1] / pow(dum,2);
        
		//double alphaRad = atan((4 * rbdData[index].mid_y) / range);
        double alphaRad = atan((4 * rbdData[index].mid[1]) / range);
		
		//direction vector
		MVector direction(0,1,0);
		MQuaternion mqhorz = direction.rotateTo(MVector(dir[0], dir[1], dir[2] ) );
		//cout<<"mqhorz : "<<mqhorz<<endl;
		MVector dirHorz = direction.rotateBy(mqhorz);
		//cout<<"dirHorz : "<<dirHorz<<endl;
        MVector cross;
        if ( dirHorz != (MVector::yAxis) ) {
            cross = dirHorz^MVector::yAxis;
        } else {
            cross = dirHorz^(MVector::xAxis);
        }
		//cout<<"cross : "<<cross<<endl;
		MQuaternion mqup(alphaRad, (cross));
		//cout<<"mqup : "<<mqup<<endl;
		MVector result = dirHorz.rotateBy(mqup);
		result.y=0;
		result.normalize();
		result *= range;
		MVector middle = result / 2 + MVector(rbdData[index].start[0], rbdData[index].start[1], rbdData[index].start[2] );
		// rotate the parabola 
		MVector res(5, 0, 0);
		MQuaternion rotQ(res, result);
		
		float t;
		
		for(int i=0;i!=div+1;++i)
		{
			t = (float)i/(float)div;
			t *= (2 * dum);
			t -= dum;
			
			//calculate the parabola
			float y = a*pow((float)t,2) + rbdData[index].mid[1];
			
			MVector parabola(t , y , 0);
			
			//cout << "rotQ = " << rotQ <<endl;
			//cout << "res = " << res <<endl;
			MVector curve = parabola.rotateBy(rotQ); 
			//cout << "curve = res.rotateBy(rotQ) : " << curve <<endl;
			curve += middle;		
			curve.rotateBy(MVector::kYaxis, (45.0 * 180 / PI) );
			glVertex3f(curve.x , curve.y , curve.z);
			
		}
		glEnd();
		glPopAttrib();
	}
}

//void rpDynTargetDevice::DrawArcYZ(const float r,const float sa,const float ea,const int divs){
	
//}

/*

//	These functions draw an arc on the specified plane
//	\param	r		-	the radius of the circle
//	\param	sa		-	the start angle in degrees
// 	\param	ea		-	the end angle in degrees
//	\param	h		-	the height of the spiral to draw
//	\param	divs	-	the number of divisions around the circle
//
void rpDynTargetDevice::DrawSpiralXY(const float sr,const float er,const float sa,const float ea,const float h,const int divs){
	
	glPushMatrix();
	glTranslatef(0,0,-h/2);
	DrawCircleXY(sr,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,h/2);
	DrawCircleXY(er,30);
	glPopMatrix();
	
	glBegin(GL_LINE_STRIP);
	for(int i=0;i!=divs;++i)
	{
		float t = (float) i / (divs-1);
		float r = (1-t)*sr + t*er;
		float angle = (i*(ea-sa)/divs) * 3.1415926535898f/180.0f;
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(ca*r,sa*r,t*h -h/2);
	}
	glEnd();
}
void rpDynTargetDevice::DrawSpiralXZ(const float sr,const float er,const float sa,const float ea,const float h,const int divs){
	
	glPushMatrix();
	glTranslatef(0,-h/2,0);
	DrawCircleXZ(sr,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,h/2,0);
	DrawCircleXZ(er,30);
	glPopMatrix();
	
	glBegin(GL_LINE_STRIP);
	for(int i=0;i!=divs;++i)
	{
		float t = (float) i / (divs-1);
		float r = (1-t)*sr + t*er;
		float angle = (i*(ea-sa)/divs) * 3.1415926535898f/180.0f;
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(ca*r,t*h -h/2,sa*r);
	}
	glEnd();
}
void rpDynTargetDevice::DrawSpiralYZ(const float sr,const float er,const float sa,const float ea,const float h,const int divs){
	
	glPushMatrix();
	glTranslatef(-h/2,0,0);
	DrawCircleXZ(sr,30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(h/2,0,0);
	DrawCircleXZ(er,30);
	glPopMatrix();
	
	glBegin(GL_LINE_STRIP);
	for(int i=0;i!=divs;++i)
	{
		float t = (float) i / (divs-1);
		float r = (1-t)*sr + t*er;
		float angle = (i*(ea-sa)/divs) * 3.1415926535898f/180.0f;
		float ca = cos(angle);
		float sa = sin(angle);
		glVertex3f(t*h -h/2,ca*r,sa*r);
	}
	glEnd();
}
*/