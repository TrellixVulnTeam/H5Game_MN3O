// MagicTypeNpc.cpp : implementation file
//

#include "stdafx.h"
#include "MagicEditor.h"
#include "MagicTypeNpc.h"


// MagicTypeNpc dialog

IMPLEMENT_DYNAMIC(MagicTypeNpc, CDialog)

MagicTypeNpc::MagicTypeNpc(CWnd* pParent /*=NULL*/)
	: CDialog(MagicTypeNpc::IDD, pParent)
{

}

MagicTypeNpc::~MagicTypeNpc()
{
}

void MagicTypeNpc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MagicTypeNpc, CDialog)
END_MESSAGE_MAP()


// MagicTypeNpc message handlers

BOOL MagicTypeNpc::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateCombobox(this,IDC_MAGIC_dodgeType,_T("MagicType"),_T("dodgeType"));
	return TRUE;
}

void MagicTypeNpc::OnLoadFromDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(false,IDC_MAGIC_dodgeType,_T("dodgeType"));

	DeclareEditFloat(false,IDC_MAGIC_dodgeDis,_T("dodgeDis"));
	DeclareEditInt(false,IDC_MAGIC_dodgeTime,_T("dodgeTime"));
}

void MagicTypeNpc::OnSaveToDB(MapCNameToValueT& mapValues)
{
	InitDeclare(this,mapValues);

	DeclareComboboxInt(true,IDC_MAGIC_dodgeType,_T("dodgeType"));

	DeclareEditFloat(true,IDC_MAGIC_dodgeDis,_T("dodgeDis"));
	DeclareEditInt(true,IDC_MAGIC_dodgeTime,_T("dodgeTime"));
}
