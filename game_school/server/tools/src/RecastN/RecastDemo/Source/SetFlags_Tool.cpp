#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include "imgui.h"
#include "InputGeom.h"
#include "Sample.h"
#include "Recast.h"
#include "RecastDebugDraw.h"
#include "DetourDebugDraw.h"
#include "SetFlags_Tool.h"

#ifdef WIN32
#	define snprintf _snprintf
#endif

SetFlagsTool::SetFlagsTool() :
	m_sample(0),
	m_hitPosSet(0),
	m_oldFlags(0),
	m_navMesh(0),
	m_navQuery(0)
{
	m_bDisable = false;
	memset(m_bflags,0,sizeof(m_bflags));
	m_bflags[0] = true;

	m_filter.setIncludeFlags(SAMPLE_POLYFLAGS_ALL);
	m_filter.setExcludeFlags(0);
}

SetFlagsTool::~SetFlagsTool()
{
	if (m_sample)
	{
		m_sample->setNavMeshDrawFlags(m_oldFlags);
	}
}

void SetFlagsTool::init(Sample* sample)
{
	if (m_sample != sample)
	{
		m_sample = sample;
		m_oldFlags = m_sample->getNavMeshDrawFlags();
		m_sample->setNavMeshDrawFlags(m_oldFlags & ~DU_DRAWNAVMESH_OFFMESHCONS);

		m_navMesh = sample->getNavMesh();
		m_navQuery = sample->getNavMeshQuery();
	}
}

void SetFlagsTool::reset()
{
	m_hitPosSet = false;
}

void SetFlagsTool::handleMenu()
{
	for(size_t i = 0; i < _countof(m_bflags); ++i)
	{
		char name[100] = "";
		sprintf(name,"Block %d",i+1);
		if (imguiCheck(name, m_bflags[i]))
		{
			memset(m_bflags,0,sizeof(m_bflags));
			m_bflags[i] = true;
			m_bDisable = false;
		}
	}
	if (imguiCheck("Disable", m_bDisable))
	{
		memset(m_bflags,0,sizeof(m_bflags));
		m_bDisable = true;
	}
}

void SetFlagsTool::handleClick(const float* /*s*/, const float* p, bool shift)
{
	if (!m_sample) return;
	InputGeom* geom = m_sample->getInputGeom();
	if (!geom) return;

	// geom->raycastMesh()

	float extents[3] = { 1,1,1 };
	dtPolyRef pref = 0;
	if(dtStatusFailed(m_navQuery->findNearestPoly(p,extents,&m_filter,&pref,NULL)))
		return ;

	dtMeshTile* tile = 0;
	dtPoly* poly = 0;
	m_navMesh->getTileAndPolyByRefUnsafe(pref,(const dtMeshTile**)&tile,(const dtPoly**)&poly);

	int flags = 0;
	if(m_bflags[0])
		flags = SAMPLE_POLYFLAGS_PWNGS_BLOCK1;
	else if(m_bflags[1])
		flags = SAMPLE_POLYFLAGS_PWNGS_BLOCK2;
	else if(m_bflags[2])
		flags = SAMPLE_POLYFLAGS_PWNGS_BLOCK3;
	else if(m_bflags[3])
		flags = SAMPLE_POLYFLAGS_PWNGS_BLOCK4;
	else if(m_bflags[4])
		flags = SAMPLE_POLYFLAGS_PWNGS_BLOCK5;
	else if(m_bDisable)
		flags = SAMPLE_POLYFLAGS_DISABLED;

	if(shift)
		poly->flags &= ~flags;
	else
		poly->flags |= flags;

}

void SetFlagsTool::handleToggle()
{
}

void SetFlagsTool::handleStep()
{
}

void SetFlagsTool::handleUpdate(const float /*dt*/)
{
}

void SetFlagsTool::handleRender()
{
	DebugDrawGL dd;
	const float s = m_sample->getAgentRadius();

	if (m_hitPosSet)
		duDebugDrawCross(&dd, m_hitPos[0],m_hitPos[1]+0.1f,m_hitPos[2], s, duRGBA(0,0,0,128), 2.0f);

	InputGeom* geom = m_sample->getInputGeom();
	if (geom)
		geom->drawOffMeshConnections(&dd, true);
}

void SetFlagsTool::handleRenderOverlay(double* proj, double* model, int* view)
{
	GLdouble x, y, z;

	// Draw start and end point labels
	if (m_hitPosSet && gluProject((GLdouble)m_hitPos[0], (GLdouble)m_hitPos[1], (GLdouble)m_hitPos[2],
		model, proj, view, &x, &y, &z))
	{
		imguiDrawText((int)x, (int)(y-25), IMGUI_ALIGN_CENTER, "Start", imguiRGBA(0,0,0,220));
	}

	// Tool help
	const int h = view[3];
	if (!m_hitPosSet)
	{
		imguiDrawText(280, h-40, IMGUI_ALIGN_LEFT, "LMB: Create new connection.  SHIFT+LMB: Delete existing connection, click close to start or end point.", imguiRGBA(255,255,255,192));	
	}
	else
	{
		imguiDrawText(280, h-40, IMGUI_ALIGN_LEFT, "LMB: Set connection end point and finish.", imguiRGBA(255,255,255,192));	
	}
}