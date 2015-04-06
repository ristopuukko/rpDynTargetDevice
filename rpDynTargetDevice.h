//
// Copyright (C) 
// 
// File: rpDynTargetDevice.h
//
// Dependency Graph Node: rpDynTargetDevice
//
// Author: Risto Puukko
//
#pragma once



//- Include Maya necessary headers for our class
#include <maya/MPxLocatorNode.h> 
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnStringData.h>
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MDistance.h>
#include <maya/MGlobal.h>
///
#include <maya/MIOStream.h>
#include <maya/MString.h> 
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MVector.h>
#include <maya/MFloatVector.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MColor.h>
#include <maya/M3dView.h>
#include <maya/MDistance.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MMatrix.h>
//
#include <maya/MFn.h>
#include <maya/MPxNode.h>
#include <maya/MPxManipContainer.h> 
#include <maya/MFnDistanceManip.h> 
#include <maya/MFnFreePointTriadManip.h>
#include <maya/MPxContext.h>
#include <maya/MPxSelectionContext.h>
#include <maya/MQuaternion.h>
#include <maya/MEulerRotation.h>
//
#include <maya/MFnNumericData.h>
#include <maya/MManipData.h>
#include <maya/MTime.h>
#include <cmath>
#include <vector>
#include <omp.h>
///

#include "mathUtils.h"


#include "api_macros.h"

#define PI 3.14159265

using namespace std;

//- Derive a new class from the default Maya node proxy class.
class rpDynTargetDevice : public MPxLocatorNode
{
public:
	rpDynTargetDevice() {
		//- Never do anything here which would affect Maya.
		//- Instead implement the virtual postConstructor() method.
	}
	virtual ~rpDynTargetDevice() {}
	
	//- Declare the virtual compute() method.
	virtual MStatus			compute( const MPlug& plug, MDataBlock& data );
	virtual MStatus			connectionMade (const MPlug &plug, const MPlug &otherPlug, bool asSrc);
	virtual MStatus			connectionBroken (const MPlug &plug, const MPlug &otherPlug, bool asSrc);
	virtual void			postConstructor();
	virtual void			draw( M3dView & view, const MDagPath & path, 
								 M3dView::DisplayStyle style,
								 M3dView::DisplayStatus status );
	
	virtual bool            isBounded() const;
	virtual MBoundingBox    boundingBox() const; 

	virtual double			random(double start, double end);
	virtual vec3f			sphrand();//return random vector inside iaRadius
	virtual double			linstep(double start, double end, double arg);
	virtual vec3f			getPosition(MPlug plug);
    virtual float           getLinDamp(MPlug plug);
	virtual vec3f			getPositionFromdArray(MObject node, int index);
	virtual vec3f			calcVelocity(vec3f eDistance, float range, float height);
	virtual	MStatus			getFloat3PlugValue( MPlug plug, MFloatVector & value );
	
	//- Declare/implement the static creator method.
	//- This method exists to give Maya a way to create new objects
	//- of this type. 
	static  void*			creator() {
		return new rpDynTargetDevice();
	}

	//- Declare the static initialize() method.
	static  MStatus			initialize();

public:
	// There needs to be a MObject handle declared for each attribute that
	// the node will have.  These handles are needed for getting and setting
	// the values later.
	//
	static  MObject		iaRadius;		// input attribute
	static	MObject		iaTrajectoryThreshold;
	static	MObject		iaTrajectoryApex;
	static	MObject		iaXray;
	static	MObject		iaInputRigids;
	static  MObject		oaOutput;		// output attribute
	static  MObject		oaOglOutput;	// output attribute for ogl - calls

	static  MObject		iaPoint;
	static	MObject		iaPointX;
	static	MObject		iaPointY;
	static	MObject		iaPointZ;
	static	MObject		iaMaxSpin;
	static	MObject		iaMaxSpinX;
	static	MObject		iaMaxSpinY;
	static	MObject		iaMaxSpinZ;
	static	MObject		iaMinSpin;
	static	MObject		iaMinSpinX;
	static	MObject		iaMinSpinY;
	static	MObject		iaMinSpinZ;
	static	MObject		iaMaxVel;
	static	MObject		iaMaxVelX;
	static	MObject		iaMaxVelY;
	static	MObject		iaMaxVelZ;
	static	MObject		iaMinVel;
	static	MObject		iaMinVelX;
	static	MObject		iaMinVelY;
	static	MObject		iaMinVelZ;
	static	MObject		iaGravity;
	static  MObject		iaDisplayNonActive;
	static  MObject		iaDisplayPercentage;
	static	MObject		iaCurveOpacity;
	static	MObject		iaShuffle;
	static	MObject		iaFlipGravity;
	static	MObject		iaNumCount;
	static	MObject		iaStartTime;
	static	MObject		iaTime;
	

	//- This is a unique node ID for your new node class. It is declared
	//- static because it is common to all instance of that class.
	//-
	//- The typeid is a unique 32bit identifier that describes this node.
	//- It is used to save and retrieve nodes of this type from the binary
	//- file format. If it is not unique, it will cause file IO problems.
public:
	static	MTypeId		id;
	
private:
	
	// global variables for unchanged tool data
	vec3f		inPoint;
	double		radius;
	double		trajectoryApex;
	double		trajectoryThreshold;
	vec3f		maxSpin;
	vec3f		minSpin;
	vec3f		maxVel;
	vec3f		minVel;
	float		gravity;
	int			shuffleValue;
    bool        xRay;
	bool		displayNonActive;
	int			displayPercentage;
	float		curveOpacity;
	bool		dRigidArrayConnected;
    int         rb_motor; // 0=undefined, 1=dynamica, 2=boing
	/// RBD data structure
	///
	struct RBD_DATA {
        vec3f start;
        vec3f mid;
        vec3f end;
        /*
		float start_x;	//  
		float start_y;  // rigid body initial position
		float start_z;  //
		float end_x;	//
		float end_y;	// rigid body calculated ground hit position
		float end_z;	//
		float mid_x;	// 
		float mid_y;	// the height/midpoint of the calculated trajectory arc
		float mid_z;	// 
        */
	} ;
	
	struct RBD_INFO {
		int			numObjs; //number of connected rbd objects;
		RBD_DATA	*objs;	//array of connected rbd objects
	} ;
	
	//RBD_INFO*		rbdInfo;
	vector<RBD_DATA> rbdData;
	bool 			canDraw;

protected:
	
	float floatRand();
	//	These functions draw a circle on the specified plane
	//	\param	r		-	the radius of the circle
	//	\param	divs	-	the number of divisions around the circle
	//
	void DrawCircleXY(const bool x_ray, const float r,const int divs, const float offset);
	void DrawCircleXZ(const bool x_ray,const float r,const int divs, const float offset);
	void DrawCircleYZ(const bool x_ray,const float r,const int divs, const float offset);
	void DrawDottedCircleXZ(const bool x_ray, M3dView::DisplayStatus status, const float r,const int divs, const float offset);
	void DrawSphere(const float r);
	void DrawParabolicCurve(M3dView::DisplayStatus status, M3dView::DisplayStyle style, int index, const int div, const float offset);
	MStatus		drawParabols(M3dView &view,M3dView::DisplayStatus status, M3dView::DisplayStyle style);
	void		printRbdInfo();
	MStatus		checkConnection(MPlug plug);
	
	friend class dynTrajectory;
	friend class randomize;	
	
};
