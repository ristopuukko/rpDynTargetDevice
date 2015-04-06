/*
 *  rpDynTargetDeviceManip.cpp
 *  rpDynTargetDevice
 *
 *  Created by Risto Puukko on 13.6.2012.
 *  Copyright 2012 ristopuukko. All rights reserved.
 *
 */
//#include "rpDynTargetDevice.h"
#ifndef RPDYNTARGETDEVICEMANIP_H
#include "rpDynTargetDeviceManip.h"
#endif


/*static*/ MTypeId rpDynTargetDeviceManip::id( 0x8431e );
///*static*/ MVector rpDynTargetDeviceManip::loc = MVector(0,0,0);

MManipData rpDynTargetDeviceManip::startPointCallback(unsigned index) const
{
	float offset = 0;
	MManipData manipData;
	MFnNumericData numData;
	MObject numDataObj = numData.create(MFnNumericData::k3Double);
	MVector vec = nodeTranslation();


	numData.setData(vec.x + offset, vec.y, vec.z);
	manipData = numDataObj;
	//cout<<"startPointCallback index = "<<index<<endl;
	/*
	if  (index && radiusManipIndex) {
		cout<<"radiusManipIndex = "<<index<<endl;
		return manipData;
	}
	if (index && thresholdManipIndex) {
		cout<<"thresholdManipIndex = "<<index<<endl;
		return manipData;
	}
	if (index && apexManipIndex) {
		cout<<"apexManipIndex = "<<index<<endl;
		return manipData;
	}
	*/
	return manipData;
}


MVector rpDynTargetDeviceManip::nodeTranslation() const
{
	MStatus stat;
	MFnDagNode dagFn(fNodePath);
	MDagPath path; 
	dagFn.getPath(path);
	
	path.pop();  // pop from the shape to the transform

	MFnTransform transformFn(path);
	return transformFn.translation(MSpace::kWorld);
}



rpDynTargetDeviceManip::rpDynTargetDeviceManip() 
{ 
    // Do not call createChildren from here 
}


rpDynTargetDeviceManip::~rpDynTargetDeviceManip() 
{
}


void* rpDynTargetDeviceManip::creator()
{
	return new rpDynTargetDeviceManip();
}

MStatus rpDynTargetDeviceManip::initialize()
{ 
    MStatus stat;
    stat = MPxManipContainer::initialize();
    return stat;
}


MStatus rpDynTargetDeviceManip::createChildren()
{
    MStatus stat = MStatus::kSuccess;

    MPoint startPoint(0.0, 0.0, 0.0);
    MVector direction(1.0, 0.0, 0.0);
	
    fRadiusManip = addDistanceManip("radiusManip",
									  "Target Radius");
	MFnDistanceManip radiusManipFn(fRadiusManip);
	radiusManipFn.setStartPoint(startPoint);
	radiusManipFn.setDirection(direction);

	direction = MVector(0.0, 1.0, 0.0);
	
	fThresholdManip = addDistanceManip("thresholdManip",
									  "Trajectory threshold");
	MFnDistanceManip thresholdManipFn(fThresholdManip);
	thresholdManipFn.setStartPoint(startPoint);
	thresholdManipFn.setDirection(direction);
	//thresholdManipFn.setDrawStart(true);
	
	direction = MVector(0.0, 1.0, 0.0);
	startPoint = MPoint(1.0, 0.0, 0.0);
	
	fApexManip = addDistanceManip("apexManip",
									 "Trajectory apex");
	MFnDistanceManip apexManipFn(fApexManip);
	apexManipFn.setStartPoint(startPoint);
	apexManipFn.setDirection(direction); 
	//apexManipFn.setDrawStart(true);

    return stat;
}

MStatus rpDynTargetDeviceManip::connectToDependNode(const MObject &node)
{
    MStatus stat;
	
	// Get the DAG path
	//
	MFnDagNode dagNodeFn(node);
	dagNodeFn.getPath(fNodePath);
	
	
	// Connect the plugs
    //    
	
	MFnDistanceManip radiusManipFn(fRadiusManip);
    MFnDependencyNode nodeFn(node);    
	
	MPlug radiusPlug = nodeFn.findPlug("radius", &stat);
    if (MStatus::kFailure != stat) {
		radiusManipFn.connectToDistancePlug(radiusPlug);
		radiusManipIndex = radiusManipFn.startPointIndex();
		addPlugToManipConversionCallback(radiusManipIndex, 
										 (plugToManipConversionCallback) 
										 &rpDynTargetDeviceManip::startPointCallback);
		//cout << "radius index "<<startPointIndex<<endl;
	}

	MFnDistanceManip thresholdManipFn(fThresholdManip);
	
	MPlug thresholdPlug = nodeFn.findPlug("trajectoryThreshold", &stat);
    if (MStatus::kFailure != stat) {
		thresholdManipFn.connectToDistancePlug(thresholdPlug);
		thresholdManipIndex = thresholdManipFn.startPointIndex();
		addPlugToManipConversionCallback(thresholdManipIndex, 
										 (plugToManipConversionCallback) 
										 &rpDynTargetDeviceManip::startPointCallback);
		//cout << "trajectory threshold index "<<startPointIndex<<endl;
	}

	MFnDistanceManip apexManipFn(fApexManip);
	
	MPlug apexPlug = nodeFn.findPlug("trajectoryApex", &stat);
    if (MStatus::kFailure != stat) {
		apexManipFn.connectToDistancePlug(apexPlug);
		apexManipIndex = apexManipFn.startPointIndex();
		addPlugToManipConversionCallback(apexManipIndex, 
										 (plugToManipConversionCallback) 
										 &rpDynTargetDeviceManip::startPointCallback);
		//cout << "trajectory apex index "<<startPointIndex<<endl;
	}
	
	
	finishAddingManips();
	MPxManipContainer::connectToDependNode(node);	
    return stat;
}


void rpDynTargetDeviceManip::draw(M3dView & view, 
								 const MDagPath &path, 
								 M3dView::DisplayStyle style,
								 M3dView::DisplayStatus status)
{ 
	MStatus stat;
	// Create a MPoint object to hold the coordinates of the CurrentPoint
		
    
	view.beginGL(); 
	
    //MPoint textPos = nodeTranslation();

	MFnDagNode dagFn(fNodePath);
	
    //MFnDependencyNode nodeFn(dagFn);    
	MFnDependencyNode nodeFn( thisMObject() );
	
	MDistance::Unit ui_unit = MDistance::uiUnit();
	
	MFnDistanceManip radiusmanipFn(fRadiusManip);
	unsigned currentPointIndex = radiusmanipFn.currentPointIndex( &stat );
	MPoint currentPoint;
	getConverterManipValue( currentPointIndex, currentPoint );
	
	MPlug rPlug = nodeFn.findPlug("radius", &stat);	
	MDistance radiusVal;
	rPlug.getValue(radiusVal);
	float r = (float) radiusVal.as(ui_unit) ;
    char str[100];
    sprintf(str, "  radius %4.3f", r); 
    MString viewTxt(str);
    view.drawText(viewTxt, currentPoint, M3dView::kLeft);

	MFnDistanceManip thresholdmanipFn(fThresholdManip);
	currentPointIndex = thresholdmanipFn.currentPointIndex( &stat );
	MPoint thresholdPoint;
	getConverterManipValue( currentPointIndex, thresholdPoint );
	
	MFnDistanceManip apexmanipFn(fApexManip);
	currentPointIndex = apexmanipFn.currentPointIndex( &stat );
	MPoint apexPoint;
	getConverterManipValue( currentPointIndex, apexPoint );
	
	
	if (apexPoint.y < (thresholdPoint.y - .001) )
		apexPoint = thresholdPoint;

	if (thresholdPoint.y > (apexPoint.y + .001) )
		thresholdPoint = apexPoint;
	
	
	MPlug hPlug = nodeFn.findPlug("trajectoryThreshold", &stat);	
	MDistance thresholdVal;
	hPlug.getValue(thresholdVal);
	float t = (float) thresholdVal.as(ui_unit) ;
	
	MPlug aPlug = nodeFn.findPlug("trajectoryApex", &stat);	
	MDistance apexVal;
	aPlug.getValue(apexVal);
	float a = (float) apexVal.as(ui_unit) ;
	
	
    sprintf(str, "trajectory\nthreshold %4.3f  ", t); 
    viewTxt = str;
    view.drawText(viewTxt, thresholdPoint, M3dView::kRight);
	



    sprintf(str, "trajectory\napex %4.3f  ", a); 
    viewTxt = str;
    view.drawText(viewTxt, apexPoint, M3dView::kCenter);
	
    view.endGL();
	/*
	MStatus stat;
	MFnDistanceManip thresholdManipFn(fThresholdManip);
	unsigned currentPointIndex = thresholdManipFn.currentPointIndex( &stat );
	
	// Create a MPoint object to hold the coordinates of the CurrentPoint
	MPoint currentPoint;
	getConverterManipValue( currentPointIndex, currentPoint );
	//cout<<"currentPoint = "<<currentPoint<<endl;
	MFnDistanceManip apexManipFn(fApexManip);
	
	apexManipFn.setStartPoint( currentPoint );
	*/
	MPxManipContainer::draw(view, path, style, status);
}