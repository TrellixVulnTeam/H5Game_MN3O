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

// ������ɼ��������
enum EGuideOpenCondition
{
	GUIDE_OPEN_CONDITION_ATTRIBUTE_CHECK	= 1,	// ָ������ֵ�Ƿ���������

	GUIDE_OPEN_CONDITION_TASK_CAN_ACCEPT	= 21,	// ָ�������Ƿ�ɽ�
	GUIDE_OPEN_CONDITION_TASK_ACCEPTED		= 22,	// ָ�������Ƿ��ѽ�
	GUIDE_OPEN_CONDITION_TASK_CANFINISH		= 23,	// ָ�������Ƿ�ɽ�
	GUIDE_OPEN_CONDITION_TASK_FINISHED		= 24,	// ָ�������Ƿ��ѽ�
	GUIDE_OPEN_CONDITION_TASK_COUNT_CHECK	= 25,	// ָ����������Ƿ���������

	GUIDE_OPEN_CONDITION_CREATURE_CONTROLLED= 46,	// �Ƿ��ѿ���ָ��npc

	GUIDE_OPEN_CONDITION_STAGE_CHECK		= 61,	// �Ƿ���ָ��������

	GUIDE_OPEN_CONDITION_ENCHANT_MAX_LEVEL	= 71,	// ��ǰװ�������ǿ���ȼ��Ƿ���������
	GUIDE_OPEN_CONDITION_ENCHANT_TOTAL_LEVEL= 72,	// ��ǰװ����ǿ���ȼ��ܺ��Ƿ���������

	GUIDE_OPEN_CONDITION_BLOOD_ACTIVE_COUNT	= 75,	// Ѫ������ײ������Ƿ���������
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
