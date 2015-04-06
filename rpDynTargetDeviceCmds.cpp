/*
 *  randomize.cpp
 *  rpDynTargetDevice
 *
 *  Created by Risto Puukko on 11.11.2012.
 *  Copyright 2012 ristopuukko. All rights reserved.
 *
 */

#include "rpDynTargetDeviceCmds.h"
#include <ctime>

rpShuffleTargets::~rpShuffleTargets(){}

MStatus rpShuffleTargets::doIt( const MArgList& args )
{
	MStatus stat = MS::kUnknownParameter;
	
	MItDependencyNodes nodeIt;
	
	for(; !nodeIt.isDone(); nodeIt.next() ) {
		MObject node = nodeIt.thisNode();
		
		if (node.isNull())
			continue;
		
		MFnDependencyNode fnNode (node);
		if (fnNode.typeName() == "rpDynTargetDevice") {
			struct tm *t;
			time_t tim;
			time(&tim);
			t = localtime(&tim);
			MObject shuffleAttr = fnNode.attribute (MString ("shuffleValue"));
			MPlug messagePlug (node, shuffleAttr);
			tim = time(NULL);
			int timeValue = t->tm_sec + ( 60 * t->tm_min);
			messagePlug.setValue(timeValue);
			//cout << messagePlug.name()<< " value is set to " << timeValue<<endl
			/*
			M3dView view = M3dView::active3dView(&stat);
			if (stat) {
				view.refresh();
			} else {
				cerr<<"problem getting the view!"<<endl;
			}*/
			
			return MS::kSuccess;
		}
		
	}
	
	return stat;
}
