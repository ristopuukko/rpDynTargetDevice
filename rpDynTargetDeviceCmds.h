/*
 *  randomize.h
 *  rpDynTargetDevice
 *
 *  Created by Risto Puukko on 11.11.2012.
 *  Copyright 2012 ristopuukko. All rights reserved.
 *
 */

#pragma once
#ifndef RPDYNTARGETDEVICE_H
#include "rpDynTargetDevice.h"
#endif

#include <maya/MPxCommand.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MFnDependencyNode.h>

class rpShuffleTargets : public MPxCommand
{
public:
	rpShuffleTargets(){};
	virtual                 ~rpShuffleTargets(); 
	
	MStatus                 doIt( const MArgList& args );
	
	
	static void*			creator(){return new rpShuffleTargets();};
	
	//friend class rpDynTargetDevice;
};
