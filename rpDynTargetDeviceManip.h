/*
 *  rpDynTargetDeviceManip.h
 *  rpDynTargetDevice
 *
 *  Created by Risto Puukko on 13.6.2012.
 *  Copyright 2012 ristopuukko. All rights reserved.
 *
 */
#pragma once
#ifndef RPDYNTARGETDEVICE_H
#include "rpDynTargetDevice.h"
#endif

#include <maya/MDistance.h>
//#include <maya/MIOStream.h>

//#include <maya/MPxNode.h>   

//#include <maya/MPxLocatorNode.h> 
/*
#include <maya/MString.h> 
#include <maya/MTypeId.h> 
#include <maya/MPlug.h>
#include <maya/MVector.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MColor.h>
#include <maya/M3dView.h>
#include <maya/MFnPlugin.h>

#include <maya/MFnUnitAttribute.h>

#include <maya/MFn.h>
#include <maya/MPxNode.h>
#include <maya/MPxManipContainer.h> 
#include <maya/MFnDistanceManip.h> 
#include <maya/MPxContext.h>
#include <maya/MPxSelectionContext.h>

#include <maya/MFnNumericData.h>
#include <maya/MManipData.h>
*/

class rpDynTargetDeviceManip : public MPxManipContainer
{
public:
    rpDynTargetDeviceManip();
    virtual ~rpDynTargetDeviceManip();
    
    static void * creator();
    static MStatus initialize();
    virtual MStatus createChildren();
    virtual MStatus connectToDependNode(const MObject & node);
	
    virtual void draw(M3dView & view, 
					  const MDagPath & path, 
					  M3dView::DisplayStyle style,
					  M3dView::DisplayStatus status);
	MManipData startPointCallback(unsigned index) const;
	MVector nodeTranslation() const;
	
    MDagPath fRadiusManip;
	unsigned radiusManipIndex;
    MDagPath fThresholdManip;
	unsigned thresholdManipIndex;
    MDagPath fApexManip;
	unsigned apexManipIndex;
	MDagPath fNodePath;
	
public:
    static MTypeId id;
	//static MVector loc;
};
