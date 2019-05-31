// MagicTypeHuman.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "MagicTypeHuman.h"


// MagicTypeHuman dialog

IMPLEMENT_DYNAMIC(MagicTypeHuman, CDialog)

MagicTypeHuman::MagicTypeHuman(CWnd* pParent /*=NULL*/)
	: CDialog(MagicTypeHuman::IDD, pParent)
{

}

MagicTypeHuman::~MagicTypeHuman()
{
}

void MagicTypeHuman::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MagicTypeHuman, CDialog)
END_MESSAGE_MAP()


// MagicTypeHuman message handlers

BOOL MagicTypeHuman::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCombobox(this,IDC_MAGIC_lockTargetDie,_T("MagicType"),_T("lockTargetDie"));
	CreateCombobox(this,IDC_MAGIC_autoSkillType,_T("MagicType"),_T("autoSkillType"));
	CreateCombobox(this,IDC_MAGIC_default_loc,_T("MagicType"),_T("default_loc"));
	CreateCheckCombo(this,IDC_MAGIC_enable_loc,_T("MagicType"),_T("enable_loc"));
	return TRUE;
}

void MagicTypeHuman::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareEditStr(false,IDC_MAGIC_imageSet,_T("imageSet"));
	DeclareEditStr(false,IDC_MAGIC_magicIconID,_T("magicIconID"));

	DeclareCheckbox(false,IDC_MAGIC_keyHold,_T("keyHold"));
	DeclareCheckbox(false,IDC_MAGIC_isContinusMagic,_T("isContinusMagic"));
	DeclareEditInt(false,IDC_MAGIC_ContinusMagic,_T("ContinusMagic"));
	DeclareEditFloat(false,IDC_MAGIC_consumeValue,_T("consumeValue"));
	DeclareCheckbox(false,IDC_MAGIC_attackLimit,_T("attackLimit"));
	DeclareCheckbox(false,IDC_MAGIC_moveLimit,_T("moveLimit"));
	DeclareCheckbox(false,IDC_MAGIC_lockTarget,_T("lockTarget"));

	DeclareComboboxInt(false,IDC_MAGIC_lockTargetDie,_T("lockTargetDie"));

	DeclareEditInt(false,IDC_MAGIC_SkillLevel,_T("SkillLevel"));
	DeclareEditFloat(false,IDC_MAGIC_add_mp_use_magic,_T("add_mp_use_magic"));
	DeclareEditFloat(false,IDC_MAGIC_add_mp_hit_first,_T("add_mp_hit_first"));
	DeclareEditFloat(false,IDC_MAGIC_add_mp_hit_other,_T("add_mp_hit_other"));
	DeclareCheckbox(false,IDC_MAGIC_is_add_mp_dodge,_T("is_add_mp_dodge"));

	DeclareComboboxInt(false,IDC_MAGIC_autoSkillType,_T("autoSkillType"));

	DeclareEditInt(false,IDC_MAGIC_autoSkillPriority,_T("autoSkillPriority"));
	DeclareEditInt(false,IDC_MAGIC_upgradeField,_T("upgradeField"));
	DeclareEditStr(false,IDC_MAGIC_levelRange,_T("levelRange"));
	DeclareEditInt(false,IDC_MAGIC_nextID,_T("nextID"));

	DeclareComboboxInt(false,IDC_MAGIC_default_loc,_T("default_loc"));
	DeclareCheckComboBit(false,IDC_MAGIC_enable_loc,_T("enable_loc"));
}

void MagicTypeHuman::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareEditStr(true,IDC_MAGIC_imageSet,_T("imageSet"));
	DeclareEditStr(true,IDC_MAGIC_magicIconID,_T("magicIconID"));

	DeclareCheckbox(true,IDC_MAGIC_keyHold,_T("keyHold"));
	DeclareCheckbox(true,IDC_MAGIC_isContinusMagic,_T("isContinusMagic"));
	DeclareEditInt(true,IDC_MAGIC_ContinusMagic,_T("ContinusMagic"));
	DeclareEditFloat(true,IDC_MAGIC_consumeValue,_T("consumeValue"));
	DeclareCheckbox(true,IDC_MAGIC_attackLimit,_T("attackLimit"));
	DeclareCheckbox(true,IDC_MAGIC_moveLimit,_T("moveLimit"));
	DeclareCheckbox(true,IDC_MAGIC_lockTarget,_T("lockTarget"));

	DeclareComboboxInt(true,IDC_MAGIC_lockTargetDie,_T("lockTargetDie"));

	DeclareEditInt(true,IDC_MAGIC_SkillLevel,_T("SkillLevel"));
	DeclareEditFloat(true,IDC_MAGIC_add_mp_use_magic,_T("add_mp_use_magic"));
	DeclareEditFloat(true,IDC_MAGIC_add_mp_hit_first,_T("add_mp_hit_first"));
	DeclareEditFloat(true,IDC_MAGIC_add_mp_hit_other,_T("add_mp_hit_other"));
	DeclareCheckbox(true,IDC_MAGIC_is_add_mp_dodge,_T("is_add_mp_dodge"));

	DeclareComboboxInt(true,IDC_MAGIC_autoSkillType,_T("autoSkillType"));

	DeclareEditInt(true,IDC_MAGIC_autoSkillPriority,_T("autoSkillPriority"));
	DeclareEditInt(true,IDC_MAGIC_upgradeField,_T("upgradeField"));
	DeclareEditStr(true,IDC_MAGIC_levelRange,_T("levelRange"));
	DeclareEditInt(true,IDC_MAGIC_nextID,_T("nextID"));

	DeclareComboboxInt(true,IDC_MAGIC_default_loc,_T("default_loc"));
	DeclareCheckComboBit(true,IDC_MAGIC_enable_loc,_T("enable_loc"));
}
