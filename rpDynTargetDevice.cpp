//
// Copyright (C) 
// 
// File:  rpDynTargetDevice.cpp
//
// Dependency Graph Node: rpDynTargetDevice
//
// Author: Risto Puukko
//

#ifndef RPDYNTARGETDEVICE_H
#include "RPDYNTARGETDEVICE.h"
#endif

#ifndef RPDYNTARGETDEVICEMANIP_H
#include "RPDYNTARGETDEVICEManip.h"
#endif

//#include <maya/MGlobal.h>

#define _DEBUG 0

//- Assigning a unique node ID to your new node class.
//- Ask ADN or Autodesk product support to reserve IDs for your company. You can
//- reserve ID by block of 64, 128, 256, or 512 consecutive ID.
//-
//- 0x00001 is a temporary ID for reserved for development. Never use that ID in a
//- production environment.
/*static*/ MTypeId rpDynTargetDevice::id( 0x8431f );

//- Instantiate the static attributes of your node class.
/*static*/ MObject rpDynTargetDevice::iaRadius;
/*static*/ MObject rpDynTargetDevice::iaTrajectoryThreshold;
/*static*/ MObject rpDynTargetDevice::iaTrajectoryApex;

/*static*/ MObject rpDynTargetDevice::iaXray;
/*static*/ MObject rpDynTargetDevice::iaInputRigids;

/*static*/ MObject rpDynTargetDevice::iaPoint;
/*static*/ MObject rpDynTargetDevice::iaPointX;
/*static*/ MObject rpDynTargetDevice::iaPointY;
/*static*/ MObject rpDynTargetDevice::iaPointZ;

/*static*/ MObject rpDynTargetDevice::iaMaxSpin;
/*static*/ MObject rpDynTargetDevice::iaMaxSpinX;
/*static*/ MObject rpDynTargetDevice::iaMaxSpinY;
/*static*/ MObject rpDynTargetDevice::iaMaxSpinZ;

/*static*/ MObject rpDynTargetDevice::iaMinSpin;
/*static*/ MObject rpDynTargetDevice::iaMinSpinX;
/*static*/ MObject rpDynTargetDevice::iaMinSpinY;
/*static*/ MObject rpDynTargetDevice::iaMinSpinZ;

/*static*/ MObject	rpDynTargetDevice::iaMaxVel;
/*static*/ MObject	rpDynTargetDevice::iaMaxVelX;
/*static*/ MObject	rpDynTargetDevice::iaMaxVelY;
/*static*/ MObject	rpDynTargetDevice::iaMaxVelZ;

/*static*/ MObject	rpDynTargetDevice::iaMinVel;
/*static*/ MObject	rpDynTargetDevice::iaMinVelX;
/*static*/ MObject	rpDynTargetDevice::iaMinVelY;
/*static*/ MObject	rpDynTargetDevice::iaMinVelZ;

/*static*/ MObject rpDynTargetDevice::iaTime;
/*static*/ MObject rpDynTargetDevice::iaStartTime;
/*static*/ MObject rpDynTargetDevice::iaGravity;
/*static*/ MObject rpDynTargetDevice::iaDisplayNonActive;
/*static*/ MObject rpDynTargetDevice::iaDisplayPercentage;
/*static*/ MObject rpDynTargetDevice::iaCurveOpacity;
/*static*/ MObject rpDynTargetDevice::iaShuffle;
/*static*/ MObject rpDynTargetDevice::iaFlipGravity;
/*static*/ MObject rpDynTargetDevice::iaNumCount;
/*static*/ MObject rpDynTargetDevice::oaOutput;
/*static*/ MObject rpDynTargetDevice::oaOglOutput;

float rpDynTargetDevice::floatRand(){
	return (float)rand() / (float)RAND_MAX;
}

double rpDynTargetDevice::random(double start, double end) 
{
	if (start == end) return start;
	
	double r = ((double) rand() / RAND_MAX) ;
	//fprintf(stderr, "r = %f\n", r);
	//if (start < 0) start *= -1;
	//if (end < 0) end *= -1;
	double val = (r * ( end - start)) + start;
	//fprintf(stderr, "start %f end %f val %f\n", start, end ,val);
	
	return val;
}

vec3f rpDynTargetDevice::sphrand()
{
	float x,z;
	do {
		x = 2.0*floatRand()-1.0;
		z = 2.0*floatRand()-1.0;
	} while ( x*x+z*z > 1.0 );
	
	vec3f result( x * radius, 0 , z * radius) ;
	
	return result;
}

double rpDynTargetDevice::linstep(double start, double end, double arg) 
{
	double stp = (arg-start) / (start-end) ; 
	if (stp < 0) stp *= -1;
	
	return stp;
}

void rpDynTargetDevice::printRbdInfo(){
	cout<<"rbdData.size() : "<<rbdData.size()<<endl;
	for(vector<RBD_DATA>::iterator it = rbdData.begin(); it != rbdData.end() ;it++ ) {
        cout<<"vector<RBD_DATA>::iterator it.start = "<<(*it).start<<endl;
        cout<<"vector<RBD_DATA>::iterator it.mid = "<<(*it).mid<<endl;
        cout<<"vector<RBD_DATA>::iterator it.end = "<<(*it).end<<endl;
        
		/*
        cout<<"vector<RBD_DATA>::iterator it.start_x = "<< (*it).start_x <<endl;
		cout<<"vector<RBD_DATA>::iterator it.start_y = "<< (*it).start_y <<endl;
		cout<<"vector<RBD_DATA>::iterator it.start_z = "<< (*it).start_z <<endl;
		cout<<"vector<RBD_DATA>::iterator it.end_x = "<< (*it).end_x <<endl;
		cout<<"vector<RBD_DATA>::iterator it.end_y = "<< (*it).end_y <<endl;
		cout<<"vector<RBD_DATA>::iterator it.end_z = "<< (*it).end_z <<endl;
		cout<<"vector<RBD_DATA>::iterator it.mid_x = "<< (*it).mid_x <<endl;
		cout<<"vector<RBD_DATA>::iterator it.mid_y = "<< (*it).mid_y <<endl;
		cout<<"vector<RBD_DATA>::iterator it.mid_z = "<< (*it).mid_z <<endl;
         */
	}
	
}


//- The initialize method is called to create and initialize all of the 
//- attributes and attribute dependencies for this node type. This is 
//- only called once when the node type is registered with Maya.
//- Return Values: MS::kSuccess / MS::kFailure
//-
MStatus rpDynTargetDevice::initialize()
{
	//- Initialize a float input attribute using the MFnNumericAttribute
	//- class. Make that attribute definition saved into Maya file (setStorable),
	//- and selectable in the channel box (setKeyable).
	// init rdb_data struct
	//canDraw = 0;
	
	MStatus stat;
	
	//- Create a generic attribute using MFnNumericAttribute
	MFnNumericAttribute nAttr;
	MFnUnitAttribute unitFn;
	MFnMessageAttribute mAttr;

	iaFlipGravity = nAttr.create("flipGravity", "fg", MFnNumericData::kBoolean, 1);
	nAttr.setStorable(true);
	nAttr.setChannelBox(true);
	
	iaStartTime = nAttr.create("startTime", "st", MFnNumericData::kFloat, 1.0f);
	nAttr.setStorable(true);
	nAttr.setChannelBox(true);
	nAttr.setWritable(true);

	iaTime = unitFn.create("time", "ti", MFnUnitAttribute::kTime);
	nAttr.setStorable(false);
	//nAttr.setChannelBox(true);
	//nAttr.setWritable(true);
	
	iaCurveOpacity = nAttr.create("curveOpacity", "cuop", MFnNumericData::kFloat, 1.0f);
	nAttr.setStorable(true);
	nAttr.setChannelBox(true);
	nAttr.setMin(0.0f);
	nAttr.setMax(1.0f);
	nAttr.setWritable(true);
	
	
	iaDisplayNonActive = nAttr.create("displayNonActive", "dpna", MFnNumericData::kBoolean, false);
	nAttr.setStorable(true);
	nAttr.setChannelBox(true);
	nAttr.setMin(0);
	nAttr.setMax(100);
	nAttr.setWritable(true);
    
    
	iaDisplayPercentage = nAttr.create("displayPercentage", "dpre", MFnNumericData::kInt, 100);
	nAttr.setStorable(true);
	nAttr.setChannelBox(true);
	nAttr.setMin(0);
	nAttr.setMax(100);
	nAttr.setWritable(true);
	
	
	iaShuffle = nAttr.create("shuffleValue", "sfh", MFnNumericData::kInt);
	nAttr.setStorable(true);
	nAttr.setWritable(false);
	nAttr.setHidden(true);
	nAttr.setKeyable(false);
	
	// count: connect if dRigidBodyArray
	iaNumCount = nAttr.create("numCount", "nc", MFnNumericData::kInt);
	
	nAttr.setConnectable(true);
	nAttr.setWritable(true);
	//nAttr.setHidden(false);
	//nAttr.setKeyable(false);
	
	//iaTime = unitFn.create("time", "t", MFnUnitAttribute::kTime);
	
	iaRadius = unitFn.create("radius", "ra", MFnUnitAttribute::kDistance);
	unitFn.setDefault(1.0);
	unitFn.setStorable(true);
	unitFn.setWritable(true);
	unitFn.setMin(0.0001);
	unitFn.setChannelBox(true);

	iaTrajectoryThreshold = unitFn.create("trajectoryThreshold", "th", MFnUnitAttribute::kDistance);
	unitFn.setDefault(1.0);
	unitFn.setStorable(true);
	unitFn.setWritable(true);
	unitFn.setMin(0.0001);
	unitFn.setChannelBox(true);

	iaTrajectoryApex = unitFn.create("trajectoryApex", "ap", MFnUnitAttribute::kDistance);
	unitFn.setDefault(2.0);
	unitFn.setStorable(true);
	unitFn.setWritable(true);
	unitFn.setMin(0.0002);
	unitFn.setChannelBox(true);
	
	iaXray = nAttr.create("xray", "xr", MFnNumericData::kBoolean, 0.0 );
	nAttr.setStorable(true);
	nAttr.setKeyable(false);
	nAttr.setChannelBox(true);
	
	iaInputRigids = mAttr.create("inputRigids", "ipr");
	mAttr.setArray(true);
	mAttr.setIndexMatters(true);
	mAttr.setConnectable(true);
	mAttr.setStorable(true);
	mAttr.setWritable(true);
	mAttr.setDisconnectBehavior(MFnAttribute::kDelete);
		
	iaPointX = nAttr.create( "pointX", "px", MFnNumericData::kFloat, 0.0 );
	iaPointY = nAttr.create( "pointY", "py", MFnNumericData::kFloat, 0.0 );
	iaPointZ = nAttr.create( "pointZ", "pz", MFnNumericData::kFloat, 0.0 );
	iaPoint = nAttr.create("point", "p", iaPointX, iaPointY, iaPointZ);
	//- Attribute will be written to files when this type of node is stored
 	nAttr.setStorable(true);
	//- Attribute is keyable and will show up in the channel box
 	nAttr.setKeyable(true);
	
	iaGravity = nAttr.create( "gravity", "gr", MFnNumericData::kFloat, 9.81 );
	nAttr.setChannelBox(true);
	nAttr.setStorable(false);
 	nAttr.setKeyable(false);
	
    cerr << "creating iaMaxSpin!";
	iaMaxSpinX = nAttr.create( "maxSpinX", "mxsx", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMaxSpinY = nAttr.create( "maxSpinY", "mxsy", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMaxSpinZ = nAttr.create( "maxSpinZ", "mxsz", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMaxSpin = nAttr.create("maxSpin", "mxs", iaMaxSpinX, iaMaxSpinY, iaMaxSpinZ);
 	nAttr.setStorable(true);
 	nAttr.setKeyable(true);
    cerr << "created!" << endl;

    cerr << "creating iaMinSpin!";
	iaMinSpinX = nAttr.create( "minSpinX", "mnsx", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMinSpinY = nAttr.create( "minSpinY", "mnsy", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMinSpinZ = nAttr.create( "minSpinZ", "mnsz", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMinSpin = nAttr.create("minSpin", "mns", iaMinSpinX, iaMinSpinY, iaMinSpinZ);
 	nAttr.setStorable(true);
 	nAttr.setKeyable(true);
    cerr << "created!" << endl;
	
    cerr << "creating iaMaxVel!";
	iaMaxVelX = nAttr.create( "maxVelX", "mxvx", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMaxVelY = nAttr.create( "maxVelY", "mxvy", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMaxVelZ = nAttr.create( "maxVelZ", "mxvz", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMaxVel = nAttr.create("maxVel", "mxv", iaMaxVelX, iaMaxVelY, iaMaxVelZ);
 	nAttr.setStorable(true);
 	nAttr.setKeyable(true);
    cerr << "created!" << endl;

    cerr << "creating iaMinVel!";
	iaMinVelX = nAttr.create( "minVelX", "mnvx", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMinVelY = nAttr.create( "minVelY", "mnvy", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMinVelZ = nAttr.create( "minVelZ", "mnvz", MFnNumericData::kDouble, 0.0 );
    cerr << "..";
	iaMinVel = nAttr.create("minVel", "mnv", iaMinVelX, iaMinVelY, iaMinVelZ);
 	nAttr.setStorable(true);
 	nAttr.setKeyable(true);
    cerr << "created!" << endl;
	
	//- Initialize a float output attribute using the MFnNumericAttribute
	//- class. Make that attribute definition not saved into Maya file.
	oaOutput = nAttr.create( "output", "out", MFnNumericData::kFloat, 0.0 );
	//- Attribute will not be written to files when this type of node is stored
	nAttr.setStorable(false);
	
    oaOglOutput = nAttr.create( "oglOutput", "oglOut", MFnNumericData::kFloat, 0.0 );
	nAttr.setStorable(false);
    
	//- Now add the attribute to your node definition using the addAttribute()
	//- method.

	//- Add the attributes we have created to the node
	addAttribute( iaTrajectoryThreshold );
	addAttribute( iaRadius );	
	addAttribute( iaTrajectoryApex );	
	addAttribute( iaXray );
	addAttribute( iaInputRigids );
	addAttribute( iaPoint );
	addAttribute( iaGravity );
	
	addAttribute( iaMaxVel );
	addAttribute( iaMinVel );

	addAttribute( iaMaxSpin );
	addAttribute( iaMinSpin );

	addAttribute( iaDisplayNonActive );
	addAttribute( iaDisplayPercentage );
	addAttribute( iaCurveOpacity );
	addAttribute( iaShuffle );
	addAttribute( iaFlipGravity );
	addAttribute( iaNumCount );
	addAttribute( iaStartTime );
	addAttribute( iaTime );
	

	
	//- Add the aOutput attribute to the node type definition
	addAttribute( oaOutput );
	//- Add the aOglOutput attribute to the node type definition
	addAttribute( oaOglOutput );
    
	
	//- Finally tell Maya how the information should flow through your node.
	//- This will also tell Maya how the dirty flag is propagated in your node
	//- and ultimately in the Maya DG. To do this, use the attributeAffects()
	//- method to link your node' attributes together.

	//- Set up a dependency between the input and the output. This will cause
	//- the output to be marked dirty when the input changes. The output will
	//- then be recomputed the next time the value of the output is requested.
	attributeAffects( iaTrajectoryThreshold, oaOutput );
	attributeAffects( iaRadius, oaOutput );
	attributeAffects( iaTrajectoryApex, oaOutput );
	attributeAffects( iaInputRigids, oaOutput );
	attributeAffects( iaPoint, oaOutput );

	attributeAffects( iaMaxVel, oaOutput );
	attributeAffects( iaMinVel, oaOutput );

	attributeAffects( iaMaxSpin, oaOutput );
	attributeAffects( iaMinSpin, oaOutput );
	
	attributeAffects( iaGravity, oaOutput );
	attributeAffects( iaFlipGravity, oaOutput );
	attributeAffects( iaShuffle, oaOutput );
	attributeAffects( iaNumCount, oaOutput ); 
	attributeAffects( iaStartTime, oaOutput ); 
	attributeAffects( iaTime, oaOutput ); 

	MPxManipContainer::addToManipConnectTable(id);

	//- Return success to Maya
	return MS::kSuccess;
}

MStatus rpDynTargetDevice::connectionMade (const MPlug &plug, const MPlug &otherPlug, bool asSrc)
{
	MStatus stat;
	/*
    std::cout << "Connection made!"<<std::endl;
	std::cout << "plug : "<<std::endl;
	std::cout << plug.info() <<std::endl;
    std::cout << "other plug : "<<std::endl;
    std::cout << otherPlug.info() <<std::endl;
	*/
	MFnDependencyNode otherNodeFn( otherPlug.node() );
    MString connected = plug.partialName(false, false, false, false, false, true);
    //std::cout << "otherNodeFn.typeName() : " << otherNodeFn.typeName() << std::endl;
    
    //rb_motor
    
	if ( checkConnection(otherPlug) ) {
        if ( otherNodeFn.typeName() == "bSolver" && connected == "gravityY" ) {
            rb_motor = RB_ENGINE_DYNAMICA;
        } else if (otherNodeFn.typeName() == "dSolver" && connected == "gravityY" ) {
            rb_motor = RB_ENGINE_BOING;
        }
        stat = MS::kUnknownParameter;
	} else {
        rb_motor = RB_ENGINE_UNDEFINED;
 		stat =  MS::kFailure;
	}
	
	
	return stat;
}

MStatus rpDynTargetDevice::connectionBroken (const MPlug &plug, const MPlug &otherPlug, bool asSrc)
{
	//cout<<"connection broken !"<<endl;
	//cout<<plug.name()<<endl;
	//cout<<plug.info()<<endl;
	MString connected = plug.partialName(false, false, false, false, false, true);
	
	MFnDependencyNode otherNodeFn( otherPlug.node() );

	MFnDependencyNode nodeFn( plug.node() );
	
	
	//cout << nodeFn.typeName()<<endl;
    //cout << connected << endl;
	
    if ( otherNodeFn.typeName() == "dRigidBodyArray" && connected =="numCount")
		dRigidArrayConnected = false;

	if ( otherNodeFn.typeName() == "dRigidBody" )
        dRigidArrayConnected = false;
	
    
	return MS::kUnknownParameter;	
	
}

MStatus rpDynTargetDevice::getFloat3PlugValue( MPlug plug, MFloatVector & value )
{
	// Retrieve the value as an MObject
	//
	MObject object;
	plug.getValue( object );
	
	// Convert the MObject to a float3
	//
	MFnNumericData numDataFn( object );
	numDataFn.getData( value[0], value[1], value[2] );
	return MS::kSuccess;
}

//calculate position based on iaInputRigids dArray index
vec3f rpDynTargetDevice::getPositionFromdArray(MObject node, int index) {
	
	MStatus status;
	MFnDagNode nodeFn(node);
    
#ifdef _DEBUG
    //cout<<"nodeFn.name() in getPositionFromdArray = "<<nodeFn.name()<<endl;
#endif
	MPlug posArrayPlug = nodeFn.findPlug("initialPosition");
	MFnDagNode transFn(nodeFn.parent(0));
	//cout << transFn.name() << endl;
	float *xyz = (float *)malloc(sizeof(float) * 3);
	
	MPlug trPosPlug = transFn.findPlug("translate");
	MPlug plug_xyz;
	if (trPosPlug.isCompound()) {
		for(unsigned i=0; i<3;i++) {
            plug_xyz = trPosPlug.child(i);
            plug_xyz.getValue(xyz[i]);
            cout<<" translate["<<i<<"] = "<<xyz[i]<<endl;
		}
	}
	
	if(!posArrayPlug.isArray()) {
		MGlobal::displayError("Something wrong with the connections between bRigidBody.msg -> rpDynTargetDeviceShape.inputRigids[]");
		return vec3f(-1);
	}
	
	MFloatVector posData;
	MPlug posPlug;

	
	posPlug = posArrayPlug.elementByPhysicalIndex( index, &status );
	if( status == MS::kSuccess && !posPlug.isNull() )
	{
		getFloat3PlugValue( posPlug, posData );
        //cout << "before xyz - posData["<<index<<"] : " << posData << endl;
		posData += MFloatVector( xyz[0], xyz[1], xyz[2]);
        //cout << "after xyz  - posData["<<index<<"] : " << posData << endl;
	}

    free(xyz);
    
	return vec3f(posData.x,posData.y,posData.z);
	
	
}
//calculate position based on iaInputRigids element plug
vec3f rpDynTargetDevice::getPosition(MPlug &plug) {
	
#ifdef _DEBUG
	//cout << "plug.info() in calcPosition : "<<plug.info()<<endl;
	//cout << "plug.name() in calcPosition : "<<plug.name()<<endl;
#endif
	MPlugArray plugs;
	plug.connectedTo(plugs,true,false);
	//cout<<"plugs.length() : "<<plugs.length()<<endl;
	MFnDagNode dShapeFn(plugs[0].node());
#ifdef _DEBUG
	//cout<<dShapeFn.name()<<endl;
#endif
	//MObject dShape = dagFn.child(0);
	//MFnDagNode dShapeFn(dShape);
#ifdef _DEBUG
	//cout<<dShapeFn.name()<<endl;
#endif
	MPlug posPlug = dShapeFn.findPlug("initialPosition");
#ifdef _DEBUG
	//cout<<"calcPosition posPlug.info() : "<<posPlug.info()<<endl;
#endif
	if(!posPlug.isCompound()) {
		MGlobal::displayError("Something wrong with the connections between dRigidBody.msg -> rpDynTargetDeviceShape.inputRigids[]");
		return vec3f(-1);
	}
	
	vec3f position;
	MPlug posx = posPlug.child(0);
	MPlug posy = posPlug.child(1);
	MPlug posz = posPlug.child(2);
	
	posx.getValue(position[0]);
	posy.getValue(position[1]);
	posz.getValue(position[2]);

	return position;
}

float rpDynTargetDevice::getTimeStep(MPlug &plug) {

    MFnDagNode rbFn(plug.node());
    MPlug rbSolverPlug = rbFn.findPlug(MString("solver"));
    MPlugArray plugs;
    rbSolverPlug.connectedTo(plugs, false, true);
    MFnDagNode dShapeFn(plugs[0].node());
    //MPlug timeStepPlug = dShapeFn.findPlug("timeStep");
    cout << "solver in getTimeStep : "<<dShapeFn.name()<<endl;

    //MPlug stepPlug = dShapeFn.findPlug("timeStep");
    
    return .1f;
    
}

float rpDynTargetDevice::getLinDamp(MPlug &plug)
{
	
#ifdef _DEBUG
	//cout << "plug.info() in getLinDamp : "<<plug.info()<<endl;
    //cout << "plug.info() in getLinDamp : "<<plug.info()<<endl;
#endif
	MPlugArray plugs;
	plug.connectedTo(plugs,true,false);
	//cout<<"plugs.length() : "<<plugs.length()<<endl;
	MFnDagNode dShapeFn(plugs[0].node());
#ifdef _DEBUG
	//cout<<dShapeFn.name()<<endl;
#endif
	//MObject dShape = dagFn.child(0);
	//MFnDagNode dShapeFn(dShape);
#ifdef _DEBUG
	//cout<<dShapeFn.name()<<endl;
#endif
	MPlug dampPlug = dShapeFn.findPlug("linearDamping");
#ifdef _DEBUG
	//cout<<"getLinDamp dampPlug.info() : "<<dampPlug.info()<<endl;
#endif
	if(dampPlug.isCompound()) {
		MGlobal::displayError("Something wrong with the connections between dRigidBody.msg -> rpDynTargetDeviceShape.inputRigids[]");
		return (-1.0f);
	}
	
	float linearDamp;
    
	dampPlug.getValue(linearDamp);

    
	return linearDamp;
}


vec3f rpDynTargetDevice::calcVelocity(vec3f eDistance, float range, float height)
{
	
	// alpha : up angle
	double alphaRad = atan((4 * height) / range);
	
	//lasketaan velocity
	double dum1 =  range * gravity ;
	double dum2 = 2 * sin(alphaRad) * cos(alphaRad);
	double vel = sqrt( dum1 / dum2 );
	
	//direction vector
	MVector direction(0,1,0);
	MQuaternion mqhorz = direction.rotateTo(MVector(eDistance[0],eDistance[1],eDistance[2]));
	//cout<<"mqhorz : "<<mqhorz<<endl;
	MVector dirHorz = direction.rotateBy(mqhorz);
	//cout<<"dirHorz : "<<dirHorz<<endl;
	MVector cross = dirHorz^MVector(0,1,0);
	//cout<<"cross : "<<cross<<endl;
	MQuaternion mqup(alphaRad, (cross));
	//cout<<"mqup : "<<mqup<<endl;
	
	vec3f velocity = vec3f(dirHorz.rotateBy(mqup).x,
                           dirHorz.rotateBy(mqup).y,
                           dirHorz.rotateBy(mqup).z);
	
	velocity = velocity * vel;
	
	return velocity;
	
}



//- This method computes the value of the given output plug based
//- on the values of the input attributes.
//- Arguments:
//- 	plug - the plug to compute
//- 	data - object that provides access to the attributes for this node
MStatus rpDynTargetDevice::compute( const MPlug& plug, MDataBlock& data )
{
	MStatus status;
 
	//- Check which output attribute we have been asked to compute. If this 
	//- node doesn't know how to compute it, you must return MS::kUnknownParameter.
	//cout<<"plug.partialName : "<<plug.partialName(true, true, true, false, true, true)<<endl;
	
    /*
	if( plug == oaOglOutput ) {
		curveOpacity =  data.inputValue(iaCurveOpacity, &status).asFloat();
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaCurveOpacity!\n");
			return MS::kFailure;
		}
        
        displayNonActive  =  data.inputValue(iaDisplayNonActive, &status).asBool();
#ifdef _DEBUG
        //cout << "displayNonActive = " << displayNonActive << endl;
#endif
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaDisplayNonActive!\n");
			return MS::kFailure;
		}
        
        MDataHandle hDisplayPercentage = data.inputValue(iaDisplayPercentage, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaDisplayPercentage!\n");
			return MS::kFailure;
		}
        
		displayPercentage = hDisplayPercentage.asInt();

        //- Get a handle on the aOutput attribute
        MDataHandle outputHandle = data.outputValue( oaOglOutput );
        
        //- Set the new output value to the handle.
        outputHandle.setFloat( curveOpacity );
        
        //- Mark the destination plug as being clean. This will prevent the
        //- dependency graph from repeating this calculation until an input
        //- attribute of this node which affects this output attribute changes.
        
        //- Tell Maya the plug is now clean
        data.setClean(plug);
        
        return MS::kSuccess;
    
    }
    */
    
	if( plug == oaOutput )
	{
		//- Get a handle to the input attribute that we will need for the
		//- computation. If the value is being supplied via a connection 
		//- in the dependency graph, then this call will cause all upstream  
		//- connections to be evaluated so that the correct value is supplied.
		
		
		//MDataHandle hTime = data.inputValue(iaTime);
		//double time = hTime.asTime().as(MTime::kMilliseconds);

		int newShuffleValue = data.inputValue(iaShuffle).asInt();
		
		MDataHandle hInputPoint = data.inputValue( iaPoint, &status );
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaPoint!\n");
			return MS::kFailure;
		}
		vec3f newInPoint(hInputPoint.asFloatVector().x, hInputPoint.asFloatVector().y, hInputPoint.asFloatVector().z);
		
        //cout<<inPoint<<endl;
		
		MDataHandle hTrajectoryApex = data.inputValue(iaTrajectoryApex, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaTrajectoryApex!\n");
			return MS::kFailure;
		}
		double newTrajectoryApex = hTrajectoryApex.asDistance().value();
		//cout<<"trajectoryApex = "<<trajectoryApex<<endl;
		
		MDataHandle hTrajectoryThreshold = data.inputValue(iaTrajectoryThreshold, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaTrajectoryThreshold!\n");
			return MS::kFailure;
		}
		double newTrajectoryThreshold = hTrajectoryThreshold.asDistance().value();
		
		MDataHandle hRadius = data.inputValue(iaRadius, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaRadius!\n");
			return MS::kFailure;
		}
		double newRadius = hRadius.asDistance().value();		
		
		
		//velocity max/min values  
		
		vec3f	newMaxVelocity, newMinVelocity;
		
		MDataHandle hMaxVel = data.inputValue(iaMaxVel, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read hMaxVel!\n");
			return MS::kFailure;
		}
		newMaxVelocity = vec3f(hMaxVel.asVector().x, hMaxVel.asVector().y, hMaxVel.asVector().z);
		
		
		MDataHandle hMinVel = data.inputValue(iaMinVel, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaMinVel!\n");
			return MS::kFailure;
		}
		newMinVelocity = vec3f(hMinVel.asVector().x, hMinVel.asVector().y, hMinVel.asVector().z);
		
		if ((newMaxVelocity[0] = 0) && (newMinVelocity[0] = 0)) {
			newMaxVelocity[0] = 1;
			newMinVelocity[0] = 1;
		}
		if ((newMaxVelocity[1] = 0) && (newMinVelocity[1] = 0)) {
			newMaxVelocity[1] = 1;
			newMinVelocity[1] = 1;
		}
		if ((newMaxVelocity[2] = 0) && (newMinVelocity[2] = 0)) {
			newMaxVelocity[2] = 1;
			newMinVelocity[2] = 1;
		}
		
		
		
		//spin max/min values  
		
		vec3f newMaxSpin, newMinSpin;
		
		MDataHandle hMaxSpin = data.inputValue(iaMaxSpin, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaMaxSpin!\n");
			return MS::kFailure;
		}
		newMaxSpin = vec3f(hMaxSpin.asVector().x,hMaxSpin.asVector().y,hMaxSpin.asVector().z);

		MDataHandle hMinSpin = data.inputValue(iaMinSpin, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaMinSpin!\n");
			return MS::kFailure;
		}
		newMinSpin = vec3f(hMinSpin.asVector().x,hMinSpin.asVector().y,hMinSpin.asVector().z);
		// end spin values
		
		MDataHandle hGravity = data.inputValue(iaGravity, &status);
		if (status != MS::kSuccess) {
			MGlobal::displayError("Cannot read iaGravity!\n");
			return MS::kFailure;
		}
		float newGravity = hGravity.asFloat();
		
		bool flipY = data.inputValue(iaFlipGravity).asBool();
		
		if (flipY) {
			newGravity *= -1;
		}
		
		int nCount = data.inputValue(iaNumCount).asInt();
		
		//MTime mtime = data.inputValue(iaTime).asTime();
		
		//float tim = (int) mtime.as( MTime::uiUnit() );
		
		//float startTime = data.inputValue(iaStartTime).asFloat();

		int nObjs;
		MPlug iRigidsPlug(thisMObject(), iaInputRigids);
		
		if (!dRigidArrayConnected) {
			// single dRigidShapes connected 
			nObjs = iRigidsPlug.numConnectedElements();
		} else {
			// dRigidArrayShape connected
			nObjs = nCount;
		}
		
		//cout << "dRigidArrayConnected : " << dRigidArrayConnected << endl;
		
		if ( 0 < nObjs ) {

			bool changeFlag = false;

			if (
                (newInPoint[0] != inPoint[0]) ||
                (newInPoint[1] != inPoint[1]) ||
                (newInPoint[2] != inPoint[2])
                ) {
				inPoint = newInPoint;
				changeFlag = true;
			}
			
			if (
                (newMaxSpin[0] != maxSpin[0]) ||
                (newMaxSpin[1] != maxSpin[1]) ||
                (newMaxSpin[2] != maxSpin[2])
                ) {
				maxSpin = newMaxSpin;
				changeFlag = true;
			}
			if (
                (newMinSpin[0] != minSpin[0]) ||
                (newMinSpin[1] != minSpin[1]) ||
                (newMinSpin[2] != minSpin[2])
                ) {
				minSpin = newMinSpin;
				changeFlag = true;
			}
			
			if (
                (newMaxVelocity[0] != maxVel[0]) ||
                (newMaxVelocity[1] != maxVel[1]) ||
                (newMaxVelocity[2] != maxVel[2])
                ) {
				maxVel = newMaxVelocity;
				changeFlag = true;
			}
			if (
                (newMinVelocity[0] != minVel[0]) ||
                (newMinVelocity[1] != minVel[1]) ||
                (newMinVelocity[2] != minVel[2])
                ) {
				minVel = newMinVelocity;
				changeFlag = true;
			}
			
			
			if (newTrajectoryApex != trajectoryApex) {
				trajectoryApex = newTrajectoryApex;
				changeFlag = true;
			}
			if (newTrajectoryThreshold != trajectoryThreshold) {
				trajectoryThreshold = newTrajectoryThreshold;
				changeFlag = true;
			}
			if (newGravity != gravity) {
				gravity = newGravity;
				changeFlag = true;
			}
			
			if (newShuffleValue != shuffleValue) {
				shuffleValue = newShuffleValue;
				changeFlag = true;
			}

			if (newRadius != radius) {
				radius = newRadius;
				changeFlag = true;
			}
			
			//if (changeFlag) {
			 
				 RBD_DATA * privateData = new RBD_DATA;
				 rbdData.clear();
				 canDraw = false;
				 				 
                //#pragma omp parallel for
				 for (unsigned i=0; i<nObjs; i++) {
					 
					 //cout<<"going for loop no "<<i<<endl;
					 MPlug elementPlug;
					 MPlug calcPlug;
					 MPlugArray plugs;
					 MFnDagNode dShapeFn;
					 
					 if (!dRigidArrayConnected) {
						 elementPlug = iRigidsPlug.elementByPhysicalIndex(i);
					 } else {
						 elementPlug = iRigidsPlug.elementByPhysicalIndex(0);
					 }
					 if (elementPlug.isNull()) return MS::kFailure;
					 calcPlug = elementPlug;
#ifdef _DEBUG
					 //cout<<"elementPlug : "<<elementPlug.partialName(true,true,true)<<endl;
#endif
					 elementPlug.connectedTo(plugs,true,false);
					 dShapeFn.setObject(plugs[0].node());
#ifdef _DEBUG
					 //cout << "dShapeFn.name() : "<< dShapeFn.name() << endl;
#endif
				     srand(shuffleValue + i);

					 vec3f distance = sphrand() + inPoint;
					 distance[1] = 0;
#ifdef _DEBUG
					 //cout<<"distance["<<i<<"] : "<<distance<<endl;
#endif
					 //if (gatherRbdData) {
					 privateData->end = distance;
					 //privateData->end = distance[1];
					 //privateData->end = distance[2];
#ifdef _DEBUG
					 //cout<<"privateInfo["<<i<<"].end is collected!"<<endl;
#endif
					 //}
					 vec3f position;
                     float linearDamp = 0.f;
                     float timeStep =0.f;
#ifdef _DEBUG
					 //cout << "dRigidArrayConnected : "<<dRigidArrayConnected<<endl;
#endif
					 if (!dRigidArrayConnected) {
						 position = getPosition(calcPlug);
                         linearDamp = getLinDamp(calcPlug);
                         timeStep = getTimeStep(calcPlug);
#ifdef _DEBUG
                         //cout<< "position["<<i<<" = "<<position<<endl;
                         //cout<< "linearDamp["<<i<<" = "<<linearDamp<<endl;
#endif
					 } else {
						 position = getPositionFromdArray(dShapeFn.object(), i);
					 }
#ifdef _DEBUG
					 //cout << " in Compute : getPositionFromdArray(MFnDagNode "<< dShapeFn.name() <<", int "<<i<<") = "<<position<<endl;
#endif
					 //if (gatherRbdData) {
					 privateData->start = position;
					 //privateData->start_y = position.y;
					 //privateData->start_z = position.z;
#ifdef _DEBUG
					 //cout<<"privateInfo["<<i<<"].start is collected!"<<endl;
#endif
					 //}
					 
					 vec3f mid = ( distance - position )/2 + position;
					 vec3f trajApex(mid[0], random(trajectoryThreshold, trajectoryApex), mid[2]);
					 privateData->mid = trajApex;
					 //privateData->mid_y = trajApex.y;
					 //privateData->mid_z = trajApex.z;
					 //cout<<"privateInfo["<<i<<"].mid is collected!"<<endl;
					 vec3f eDistance = distance - position;
#ifdef _DEBUG
					 //cout<<"going to calcVelocity"<<endl;
#endif
					 vec3f vel = calcVelocity(eDistance, norm2(eDistance), trajApex[1]);
                     
                     //figure out how to get rid of bullet damping
                     //m_linearVelocity *= btPow(btScalar(1)-m_linearDamping, timeStep);
                     // timeStep = 1 / subSteps ie. 1/10
					 
                     
                     vel = vel / pow((1 + linearDamp), timeStep);
#ifdef _DEBUG
					 //cout <<"vel["<<i<<"] = "<<vel<<endl;
#endif
					 	 
					 MPlug vPlug = dShapeFn.findPlug("initialVelocity", &status);
					 MPlug velPlug;
					 if (dRigidArrayConnected) {
						 if(!vPlug.isArray()) {
							 MGlobal::displayError("vPlug is not an Array() ");
							 return MS::kFailure;
						 }
						 //cout << "vPlug.name()"<<vPlug.name()<<endl;
						 velPlug = vPlug.elementByPhysicalIndex( i, &status );
						 //cout << "velPlug.name()"<<velPlug.name()<<endl;
						 //cout << velPlug.isNull()<<endl;
						 if( status == MS::kFailure || velPlug.isNull() ) {
							 if (status == MS::kFailure) cout <<"velPlug assign returned error"<<endl;
							 return MS::kFailure;
						 }
					 } else {
						 velPlug = vPlug;
					 }
					 
                     //bool t =  ((int)startTime == (int)tim);
					 //cout << "time = " << tim << endl;
					 //cout << " ((startTime - 1 > tim) && (startTime + 1 < tim) ) = "<<t<<endl;
					 /*
                     MPlug xfPlug = dShapeFn.findPlug("externalForce", &status);
					 if ( t ) {
						 cout << "setting value " << vel << endl;
						 xfPlug.child(0).setValue(vel.x * random(minVel.x, maxVel.x));
						 xfPlug.child(1).setValue(vel.y * random(minVel.y, maxVel.y));
						 xfPlug.child(2).setValue(vel.z * random(minVel.z, maxVel.z));
					 } else {
						 xfPlug.child(0).setValue(0);
						 xfPlug.child(1).setValue(0);
						 xfPlug.child(2).setValue(0);
						 
					 }
					 */
					  // get the plugs to the child attributes
                     //MPlug velPlug = dShapeFn.findPlug("externalForce", &status);
#ifdef _DEBUG
                     //cout<<"setting initialVelocity values"<<endl;
#endif
					 if(velPlug.isCompound()) {
                         MPlug velPlug_x = velPlug.child(0);
                         MPlug velPlug_y = velPlug.child(1);
                         MPlug velPlug_z = velPlug.child(2);
                         // get the values from the child plugs
                         velPlug_x.setValue( vel[0] );//* random(minVel.x, maxVel.x) );
                         velPlug_y.setValue( vel[1] );//* random(minVel.y, maxVel.y) );
                         velPlug_z.setValue( vel[2] );//* random(minVel.z, maxVel.z) );
#ifdef _DEBUG
                         //cout << "initialVelocity = "<<vel[0]<<" "<<vel[1]<<" "<<vel[2]<<endl;
#endif
                     }
                     
					 MPlug sPlug = dShapeFn.findPlug("initialSpin", &status);
					 MPlug spinPlug;
					 if (dRigidArrayConnected) {
						 if(!sPlug.isArray()) {
							 MGlobal::displayError("sPlug is not an array");
							 return MS::kFailure;
						 }
						 //cout << "sPlug.name()"<<sPlug.name()<<endl;
						 spinPlug = sPlug.elementByPhysicalIndex( i, &status );
						 //cout << "sPlug.name()"<<spinPlug.name()<<endl;
						 
						 if( status == MS::kFailure || spinPlug.isNull() ) {
							 MString msg= "spinPlug.isNull() = ";
							 msg += MString( (char*)spinPlug.isNull() );
							 MGlobal::displayError(msg);
							 return MS::kFailure;
						 }
					 } else {
						 spinPlug = sPlug;
					 }
					 
#ifdef _DEBUG
                     //cout<<"setting initialSpin values"<<endl;
#endif
					 if(spinPlug.isCompound()) {
						 // get the plugs to the child attributes
						 MPlug spinPlug_x = spinPlug.child(0);
						 MPlug spinPlug_y = spinPlug.child(1);
						 MPlug spinPlug_z = spinPlug.child(2);
						 // get the values from the child plugs
                         vec3f spin = sphrand() * norm2(maxSpin - minSpin ) + minSpin  ;
                         spinPlug_x.setValue( spin[0] );
						 spinPlug_y.setValue( spin[1] );
						 spinPlug_z.setValue( spin[2] );
#ifdef _DEBUG
						 //cout << "initialSpin = "<<spin[0]<<" "<<spin[1]<<" "<<spin[2]<<endl;
#endif
					 }
					 
					 
					 //cout << "pushing privateData to rbdData"<<endl;
					 rbdData.push_back(*privateData);
					 
				 }
				//cout << "deleting privateData!"<<endl;
				delete privateData;
				if (!canDraw) canDraw = true;
			//} <-- (changeFlag) 
                
            //printRbdInfo();
			//- Get a handle to the output attribute. This is similar to the
			//- "inputValue" call above except that no dependency graph 
			//- computation will be done as a result of this call.
			
			//- Get a handle on the aOutput attribute
			MDataHandle outputHandle = data.outputValue( oaOutput );
			
			//- Set the new output value to the handle.
			outputHandle.setFloat( inPoint[0] );
			
			//- Mark the destination plug as being clean. This will prevent the
			//- dependency graph from repeating this calculation until an input 
			//- attribute of this node which affects this output attribute changes.
			
			//- Tell Maya the plug is now clean
			data.setClean(plug);
			
			//- Return success to Maya
			return MS::kSuccess;
		}


	}

	//- Tell Maya that we do not know how to handle this plug, but let give a chance
	//- to our parent class to evaluate it.
	return MS::kUnknownParameter;
}

void rpDynTargetDevice::postConstructor()
{
	MFnDependencyNode nodeFn(thisMObject());
	nodeFn.setName("rpDynTargetDeviceShape#");
    MPlugArray plugs;
    
    //cout<<nodeFn.parentNamespace()<<endl;
   
    nodeFn.getConnections(plugs);
    //MObject transform = plugs[0].node();
    //MFnDagNode transformFn(transform);
    //cout<<transformFn.partialPathName()<<endl;
    //MString cmd = "connectAttr -f "
	
}

MStatus rpDynTargetDevice::checkConnection(MPlug plug) 
{

	MFnDependencyNode nodeFn( plug.node() );
	
	//cout << "checkConnection node : " << nodeFn.name() << endl;
	//cout << "checkConnection typeName : " << nodeFn.typeName() << endl;
	
	if ( nodeFn.typeName() == "dRigidBodyArray" ) {
		dRigidArrayConnected = true;
	} else if (nodeFn.typeName() == "dRigidBody" ||  nodeFn.typeName() == "bulletRigidBodyShape") {
		dRigidArrayConnected = false;
	}
 	
	return MS::kSuccess;
	
}

void rpDynTargetDevice::draw(M3dView &view, const MDagPath &path, 
							M3dView::DisplayStyle style,
							M3dView::DisplayStatus status)
{ 
	//cout<<"rbdData.empty() : "<<rbdData.empty()<<endl;

	view.beginGL(); 
	
	if ( ( style == M3dView::kFlatShaded ) || 
		( style == M3dView::kGouraudShaded ) ) 
	{  
		// Push the color settings
		// 
		glPushAttrib( GL_CURRENT_BIT );
		
		if ( status == M3dView::kActive ) {
			view.setDrawColor( 13, M3dView::kActiveColors );
		} else {
			view.setDrawColor( 13, M3dView::kDormantColors );
		}  
		
		glPopAttrib();
	}

	MFnDistanceManip dManip(path);
	//cout<<"rpDynTargetDevice::draw node "<<path.fullPathName()<<endl;
	
	MObject thisNode = thisMObject();
	MPlug plug(thisNode, iaXray);

	plug.getValue(xRay);
	
	plug = MPlug(thisNode, iaRadius);
	MDistance val;
	plug.getValue(val);
	
	radius = (float) val.asCentimeters();
	
    plug = MPlug(thisNode, iaDisplayPercentage);

    plug.getValue(displayPercentage);
    
    plug = MPlug(thisNode, iaDisplayNonActive);
    plug.getValue(displayNonActive);
    
	DrawCircleXZ(xRay, radius, 60, 0);

	plug = MPlug(thisNode, iaTrajectoryThreshold);
	plug.getValue(val);
	
	float he = (float) val.asCentimeters();
	DrawDottedCircleXZ(xRay, status, radius, 60, he);

	plug = MPlug(thisNode, iaTrajectoryApex);
	plug.getValue(val);
	
	float ap = (float) val.asCentimeters();
	DrawDottedCircleXZ(xRay, status, radius, 60, ap);

	plug = MPlug(thisNode, iaCurveOpacity);
    plug.getValue(curveOpacity);
	
	//glEnd();
	
	view.endGL();
	//printRbdInfo();
    /*
    cout<<"( status == M3dView::kLead ) : "<< ( status == M3dView::kLead ) <<" ";
    cout<<"displayPercentage : "<< displayPercentage <<" ";
    cout<<"displayNonActive : "<< displayNonActive <<endl;
    */
    
	if ( (( status == M3dView::kLead ) && (displayPercentage > 0)) || ( ( displayNonActive == true ) && (displayPercentage > 0) ) && ( curveOpacity > .001) )  {
		if (canDraw && (!rbdData.empty()) ) {
            //cout<<"drawParabols YES!"<<endl;
        
            drawParabols(view,status, style);
        }
	}

}

MStatus rpDynTargetDevice::drawParabols(M3dView &view, M3dView::DisplayStatus status, M3dView::DisplayStyle style) {
	
	//M3dView view = M3dView::active3dView();
	MDagPath cam;
	MStatus stat = view.getCamera(cam);
	MString path = cam.partialPathName();
	MDagPath                    thisCameraView;       // the dagPath for this modelPanel's Camera
	MMatrix                     cameraInverseMatrix;  // inverse matrix for the modelPanel's Camera
	double                      dMatrix[4][4];        // the 4×4 array for the OpenGL matrix
	
	// Get the Maya Camera associated with this view
	view.getCamera( thisCameraView );
	
	// Load inverse of the Camera's Matrix
	cameraInverseMatrix = (thisCameraView.inclusiveMatrix()).inverse();
	
	// Get 4×4 array to represent matrix (required for glLoadMatrix)
	cameraInverseMatrix.get( dMatrix );
	
	// Initialize Maya's GL
	view.beginGL();
	
	//view.beginOverlayDrawing();
	
	glMatrixMode( MGL_MODELVIEW );
	glPushMatrix();
	
	// Load the inverse of the Camera's matrix into the Model View.
	// This places the render origin at Maya's world center.
	glLoadMatrixd( (GLdouble *)dMatrix );

    //view.beginGL();
	//glLineWidth(0.2f);
	MVector position, height, range;
	
	MPlug arrayPlug(thisMObject(), iaInputRigids);
	int nObjs ;
	if (dRigidArrayConnected) {
		MPlug numPlug(thisMObject(), iaNumCount);
		numPlug.getValue(nObjs);
		//nObjs = arrayPlug.numElements();
	} else {
		nObjs= arrayPlug.numConnectedElements();
	}
	//cout << "displayPercentage : "<<displayPercentage<<endl;
	//cout << "(100/displayPercentage) : "<<(100/displayPercentage)<<endl;
	//bool x_ray = true;
	//cout<<"status == M3dView::kLead : " << (status == M3dView::kLead) << endl;
	for (unsigned i=0; i<nObjs; i += ((int)(100/displayPercentage)) ) {
		//cout<<"DrawParabolicCurve Yep"<<endl;
		DrawParabolicCurve(status, style,  i, 20, 0);
	}
	
	
	
#ifdef _WINDOWS
	glXSwapBuffers(view.display(), view.window());
#elseif _macOS
	SwapBuffers(view.deviceContext());
#endif
	
	glPopMatrix();
	
	//view.endOverlayDrawing();
	view.endGL();
	
	return MS::kSuccess;
	
	
}

bool rpDynTargetDevice::isBounded() const
{ 
	return true;
}

MBoundingBox rpDynTargetDevice::boundingBox() const
{   
	// Get the size
	//
	
	//MDistance::Unit ui_Unit = MDistance::uiUnit();
	
	MObject thisNode = thisMObject();
	MPlug plug(thisNode, iaRadius);
	MDistance rVal;
	plug.getValue(rVal);
	
	plug = MPlug(thisNode, iaTrajectoryThreshold);
	MDistance hVal;
	plug.getValue(hVal);
	
	double hei = hVal.asCentimeters();
	double rad = rVal.asCentimeters();
	
	MPoint corner1(-1.0 * rad, 0.0, -1.0 * rad);
	MPoint corner2(1.0 * rad, 1.0 * hei, 1.0 * rad);
	
	return MBoundingBox(corner1, corner2); 
}


