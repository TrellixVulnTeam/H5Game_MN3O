/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "BasicDemo.h"
#include "GlutStuff.h"
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btHashMap.h"




	
BasicDemo ccdDemo;

void myexit()
{
	ccdDemo.exitPhysics();
}

int main(int argc,char** argv)
{

	ccdDemo.initPhysics();
 

#ifdef CHECK_MEMORY_LEAKS
	ccdDemo.exitPhysics();
#else
	glutmain(argc, argv,1024,600,"Bullet Physics Demo. http://bulletphysics.org",&ccdDemo);
#endif

	atexit(&myexit);
	
	
	//default glut doesn't return from mainloop
	return 0;
}

