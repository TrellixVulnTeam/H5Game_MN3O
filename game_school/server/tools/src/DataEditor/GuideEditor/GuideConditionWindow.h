#pragma once

#include "ToolDef.h"
#include "afxcmn.h"

#include "GuideConditionSubAttribute.h"
#include "GuideConditionSubControl.h"
#include "GuideConditionSubEnchant.h"
#include "GuideConditionSubStage.h"
#include "GuideConditionSubTask.h"
#include "GuideConditionSubTaskCount.h"
#include "GuideConditionSubBlood.h"

USE_NS_AC;

// 触发后可激活的条件
enum EGuideOpenCondition
{
	GUIDE_OPEN_CONDITION_ATTRIBUTE_CHECK	= 1,	// 指定属性值是否满足条件

	GUIDE_OPEN_CONDITION_TASK_CAN_ACCEPT	= 21,	// 指定任务是否可接
	GUIDE_OPEN_CONDITION_TASK_ACCEPTED		= 22,	// 指定任务是否已接
	GUIDE_OPEN_CONDITION_TASK_CANFINISH		= 23,	// 指定任务是否可交
	GUIDE_OPEN_CONDITION_TASK_FINISHED		= 24,	// 指定任务是否已交
	GUIDE_OPEN_CONDITION_TASK_COUNT_CHECK	= 25,	// 指定任务计数是否满足条件

	GUIDE_OPEN_CONDITION_CREATURE_CONTROLLED= 46,	// 是否已控制指定npc

	GUIDE_OPEN_CONDITION_STAGE_CHECK		= 61,	// 是否在指定场景中

	GUIDE_OPEN_CONDITION_ENCHANT_MAX_LEVEL	= 71,	// 当前装备的最高强化等级是否满足条件
	GUIDE_OPEN_CONDITION_ENCHANT_TOTAL_LEVEL= 72,	// 当前装备的强化等级总和是否满足条件

	GUIDE_OPEN_CONDITION_BLOOD_ACTIVE_COUNT	= 75,	// 血脉激活孔槽数量是否满足条件
};

// GuideConditionWindow dialog

class GuideConditionWindow : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionWindow)

public:
	GuideConditionWindow(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionWindow();

// Dialog Data
	enum { IDD = IDD_DIALOG_GUIDECONDITION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
protected:
	GuideConditionSubAttribute m_objSubAttribute;
	GuideConditionSubControl m_objSubControl;
	GuideConditionSubEnchant m_objSubEnchant;
	GuideConditionSubStage m_objSubStage;
	GuideConditionSubTask m_objSubTask;
	GuideConditionSubTaskCount m_objSubTaskCount;
	GuideConditionSubBlood m_objSubBlood;
public:
	void RegisterWnds();
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
	afx_msg void OnCbnSelchangeGuideconditionaction();
};
