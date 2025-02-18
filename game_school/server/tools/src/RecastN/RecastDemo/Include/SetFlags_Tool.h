//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef _SET_FLAGS_TOOL
#define _SET_FLAGS_TOOL

#include "Sample.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshQuery.h"

// Tool to create off-mesh connection for InputGeom

class SetFlagsTool : public SampleTool
{
	Sample* m_sample;
	float m_hitPos[3];
	bool m_hitPosSet;


	bool m_bflags[5];
	bool m_bDisable;
	unsigned char m_oldFlags;
	dtNavMesh* m_navMesh;
	dtNavMeshQuery* m_navQuery;
	dtQueryFilter m_filter;
public:
	SetFlagsTool();
	~SetFlagsTool();

	virtual int type() { return TOOL_SET_FLAGS; }
	virtual void init(Sample* sample);
	virtual void reset();
	virtual void handleMenu();
	virtual void handleClick(const float* s, const float* p, bool shift);
	virtual void handleToggle();
	virtual void handleStep();
	virtual void handleUpdate(const float dt);
	virtual void handleRender();
	virtual void handleRenderOverlay(double* proj, double* model, int* view);
};

#endif // _SET_FLAGS_TOOL
