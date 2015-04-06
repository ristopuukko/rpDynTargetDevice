//
// Copyright (C)  
// 
// File: pluginMain.cpp
//
// Dependency Graph Node: rpDynTargetDevice
//
// Author: Risto Puukko
//

#include <maya/MFnPlugin.h>
#ifndef RPDYNTARGETDEVICE_H
#include "rpDynTargetDevice.h"
#endif

#ifndef RPDYNTARGETDEVICEMANIP_H
#include "rpDynTargetDeviceManip.h"
#endif


#ifndef RANDOMIZE_H
#include "rpDynTargetDeviceCmds.h"
#endif

#define _macOS
//#define _WINDOWS


MStatus initializePlugin( MObject obj )
//
//	Description:
//		this method is called when the plug-in is loaded into Maya.  It 
//		registers all of the services that this plug-in provides with 
//		Maya.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{ 
	MStatus   status;
	MFnPlugin plugin( obj, "ristopuukko", "0.1", "Any");
	
	// Add plug-in feature registration here
	//
	
	//- Register your node here, so Maya can use it and recognize it
	//- while reading/saving a file which has instance of this node type.
	status = plugin.registerNode( "rpDynTargetDevice", rpDynTargetDevice::id, rpDynTargetDevice::creator, rpDynTargetDevice::initialize, MPxNode::kLocatorNode );
	
	if (!status) {
		status.perror("registerNode \"rpDynTargetDevice\" ");
		return status;
	}
	// <debug>
	
	//MString txt = MString( "RPDYNTARGETDEVICE-main node created ! " ) ;
	//MGlobal::displayInfo( txt );
    
	// </debug>
	
	
	status = plugin.registerNode( "rpDynTargetDeviceManip", rpDynTargetDeviceManip::id, rpDynTargetDeviceManip::creator, rpDynTargetDeviceManip::initialize, MPxNode::kManipContainer );
	
	if (!status) {
		status.perror("registerNode \"rpDynTargetDeviceManip\" ");
		return status;
	}
	// <debug>
	
	//txt = MString( "RPDYNTARGETDEVICEManip - manipulator created ! " ) ;
	//MGlobal::displayInfo( txt );
    
	// </debug>

	status = plugin.registerCommand( "rpShuffleTargets", rpShuffleTargets::creator );
	if (!status) {
		status.perror("registerCommand \"rpShuffleTargets\"");
		return status;
	}
	// <debug>
	
	//txt = MString( "randomize - command created ! " ) ;
	//MGlobal::displayInfo( txt );
	// </debug>
	
	return status;
}

MStatus uninitializePlugin( MObject obj )
//s
//	Description:
//		this method is called when the plug-in is unloaded from Maya. It 
//		deregisters all of the services that it was providing.
//
//	Arguments:
//		obj - a handle to the plug-in object (use MFnPlugin to access it)
//
{
	MStatus   status;
	MFnPlugin plugin( obj );
	
	// Add plug-in feature deregistration here
	//
	
	
	//- Unregister your node here, so Maya stops using it.
	status = plugin.deregisterNode( rpDynTargetDevice::id );
	
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}
	
	status = plugin.deregisterNode( rpDynTargetDeviceManip::id );
	
	if (!status) {
		status.perror("deregisterNode");
		return status;
	}

	status = plugin.deregisterCommand( "rpShuffleTargets" );
	if (!status) {
		status.perror("deregisterCommand \"rpShuffleTargets\"");
		return status;
	}	
	
	return status;
}


