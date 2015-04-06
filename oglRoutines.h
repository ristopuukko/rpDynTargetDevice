/*
 *  oglRoutines.h
 *  rpDynTargetDevice
 *
 *  Created by Risto Puukko on 13.6.2012.
 *  Copyright 2012 ristopuukko. All rights reserved.
 *
 */

#pragma once

#ifdef _WINDOWS
	#define _WINSOCKAPI_ 
	#include <windows.h>
	#include <gl/gl.h>
	#include <gl/glu.h>
	#include <gl/glut.h>
#elseif _macOS
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif
