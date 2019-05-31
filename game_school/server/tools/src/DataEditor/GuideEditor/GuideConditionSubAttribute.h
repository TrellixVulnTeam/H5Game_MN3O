#pragma once

#include "ToolDef.h"
#include "GuideConditionSubAttributeSub1.h"
#include "GuideConditionSubAttributeSub2.h"

USE_NS_AC;

// 触发属性改变时，具体的属性类型
enum EGuideAttributeType
{
	GUIDE_ATTRIBUTE_TYPE_LEVEL				= 1,	// 等级
	GUIDE_ATTRIBUTE_TYPE_PROFESSION			= 2,	// 职业
	GUIDE_ATTRIBUTE_TYPE_MANA				= 3,	// 魔法值
	GUIDE_ATTRIBUTE_TYPE_BLOODLINE			= 4,	// 血脉等级
};

// GuideConditionSubAttribute dialog

class GuideConditionSubAttribute : public CDialog
{
	PRE_TRANSLATE_MESSAGE_SUB
	DECLARE_DYNAMIC(GuideConditionSubAttribute)

public:
	GuideConditionSubAttribute(CWnd* pParent = NULL);   // standard constructor
	virtual ~GuideConditionSubAttribute();

// Dialog Data
	enum { IDD = IDD_DIALOG_SUBATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
protected:
	GuideConditionSubAttributeSub1 m_objSub1;
	GuideConditionSubAttributeSub2 m_objSub2;
public:
	void OnLoadFromDB(MapCNameToValueT& mapValues);
	void OnSaveToDB(MapCNameToValueT& mapValues);
	afx_msg void OnCbnSelchangeGuideconditionparam1();
};
