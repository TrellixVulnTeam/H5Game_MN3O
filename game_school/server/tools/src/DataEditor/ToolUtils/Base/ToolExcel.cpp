#include "stdafx.h"
#include "ToolExcel.h"
#include "ToolApp.h"
#include "ToolTree.h"
#include "ACString.h"
#include "ACLog.h"
#include <algorithm>

BEGIN_NS_AC

const int cst_carry_num = 'Z' - 'A' + 1;

void MakeColumnName(int nCol,CString& strColName)
{
	ACCHECK(nCol > 0);

	if(nCol >= 1 && nCol <= cst_carry_num)
	{
		strColName.Insert(0,_T('A' + nCol - 1));
		return;
	}

	if(nCol % cst_carry_num == 0)
	{
		nCol = nCol - cst_carry_num;
		strColName.Insert(0,_T('Z'));
		nCol = nCol / cst_carry_num;
	}
	else
	{
		int nLow = nCol % cst_carry_num;
		strColName.Insert(0,_T('A' + nLow - 1));
		nCol = nCol / cst_carry_num;
	}

	MakeColumnName(nCol,strColName);
}

CString MakeCellName(int nRow,int nCol)
{
	ACCHECK(nRow > 0 && nRow <= EXCEL_ROW_MAX);
	ACCHECK(nCol > 0 && nCol <= EXCEL_COL_MAX);

	CString strColName;
	MakeColumnName(nCol,strColName);
	CString strRowName;
	strRowName.Format(_T("%d"), nRow);
	return strColName + strRowName;
}

int TestMakeCellName()
{
	ACCHECK(MakeCellName(1000,1) == _T("A1000"));	// A1000
	ACCHECK(MakeCellName(1000,26) == _T("Z1000"));		// Z1000
	ACCHECK(MakeCellName(1000,27) == _T("AA1000"));		// AA1000
	ACCHECK(MakeCellName(1000,52) == _T("AZ1000"));		// AZ1000
	ACCHECK(MakeCellName(1000,53) == _T("BA1000"));		// BA1000
	ACCHECK(MakeCellName(1000,2 * 26 + 26) == _T("BZ1000")); // BZ1000
	ACCHECK(MakeCellName(1000,2 * 26 * 26 + 26 * 26 + 26) == _T("BZZ1000")); // BZZ1000
	return 0;
}

void FillSafeArray(OLECHAR FAR* sz, int nRow, int nCol, COleSafeArray* sa)
{
	VARIANT v;
	long index[2];

	index[0] = nRow;
	index[1] = nCol;

	VariantInit(&v);
	v.vt = VT_BSTR;
	v.bstrVal = SysAllocString(sz);
	sa->PutElement(index,v.bstrVal);
	SysFreeString(v.bstrVal);
	VariantClear(&v);
}

void SetRowSafeArray(COleSafeArray& rSa, int nColTotal, std::vector<CString>& vtValues, CString strDefaultValue)
{
	DWORD numElements[] = {1,nColTotal};
	rSa.Create(VT_BSTR,2,numElements);
	for(int nCol = 0; nCol < nColTotal; ++nCol)
	{
		if(nCol < vtValues.size())
			FillSafeArray(vtValues[nCol].GetBuffer(),0,nCol,&rSa);
		else
			FillSafeArray(strDefaultValue.GetBuffer(),0,nCol,&rSa);
	}
}

void GetRowSafeArray(COleSafeArray& rSa, int nColTotal, std::vector<CString>& vtValues, CString strDefaultValue)
{
	long index[2];
	VARIANT val;
	CString strVal;
	long nCol,nColNum;
	rSa.GetLBound(2,&nCol);
	rSa.GetUBound(2,&nColNum);
	ACCHECK(nCol == 1);

	for(nCol = 1; nCol <= nColTotal; ++nCol)
	{
		index[0] = 1;
		index[1] = nCol;

		if(nCol <= nColNum)
		{
			rSa.GetElement(index,&val);
			if(val.vt == VT_BOOL)
			{
				/* 0 == FALSE, -1 == TRUE */
				strVal = val.boolVal == -1 ? _T("true") : _T("false");
			}
			else
			{
				strVal = val;
			}
		}
		else
		{
			strVal = strDefaultValue;
		}

		vtValues.push_back(strVal);
	}
}

//-----------------------------------------------------------------

ExcelWorkbook::ExcelWorkbook(LPDISPATCH workbook)
{
	m_objWorkbook.AttachDispatch(workbook);
	m_objWorkSheets.AttachDispatch(m_objWorkbook.get_Worksheets());
}

ExcelWorkbook::~ExcelWorkbook()
{
	m_objWorkSheets.ReleaseDispatch();
	m_objWorkbook.ReleaseDispatch();
}

int ExcelWorkbook::GetSheetCount()
{
	return m_objWorkSheets.get_Count();
}

int ExcelWorkbook::GetUsedRowCount(int sheetidx)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CRange range;
	range.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(range.get_Rows());
	return range.get_Count();
}

int ExcelWorkbook::GetUsedColumnCount(int sheetidx)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CRange range;
	range.AttachDispatch(sheet.get_UsedRange());
	range.AttachDispatch(range.get_Columns());
	return range.get_Count();
}

CString ExcelWorkbook::GetCellText(int sheetidx,int row,int col)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);
	ACCHECK(col >= 0 && col < EXCEL_COL_MAX);
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CRange range;
	range.AttachDispatch(sheet.get_Cells());
	CString strCell = MakeCellName(row+1,col+1);
	range.AttachDispatch(range.get_Range(COleVariant(strCell),covOptional));
	COleVariant result = range.get_Value2();
	if(result.vt == VT_BOOL)
	{
		/* 0 == FALSE, -1 == TRUE */
		return result.boolVal == -1 ? _T("true") : _T("false");
	}
	else
		return result;
}

void ExcelWorkbook::SetCellText(int sheetidx,int row,int col,CString val)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);
	ACCHECK(col >= 0 && col < EXCEL_COL_MAX);
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CRange range;
	range.AttachDispatch(sheet.get_Cells());
	range.put_Item(COleVariant((short)(row+1)),COleVariant((short)(col+1)),COleVariant(val));
}

void ExcelWorkbook::SetCellText(int sheetidx,int row,int col,int val)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);
	ACCHECK(col >= 0 && col < EXCEL_COL_MAX);
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CRange range;
	range.AttachDispatch(sheet.get_Cells());
	range.put_Item(COleVariant((short)(row+1)),COleVariant((short)(col+1)),COleVariant((long)val));
}

void ExcelWorkbook::SortAllSheetByColumn(int sortByCol,int startRow)
{
	int nSheetTotal = GetSheetCount();
	for(int nSheet = 0; nSheet < nSheetTotal; ++nSheet)
	{
		int nRowTotal = GetUsedRowCount(nSheet);
		int nColTotal = GetUsedColumnCount(nSheet);

		if(nRowTotal <= startRow)
			continue;

		ACCHECK(startRow >= 0 && startRow < EXCEL_ROW_MAX);
		ACCHECK(sortByCol >= 0 && sortByCol < EXCEL_COL_MAX);
		CWorksheet sheet;
		sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(nSheet+1))));
		CString strCell1 = MakeCellName(startRow,1);
		CString strCell2 = MakeCellName(nRowTotal,nColTotal);
		CRange range;
		range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));
		VARIANT key;
		V_VT(&key) = VT_DISPATCH;
		CString strCell3 = MakeCellName(1,sortByCol+1);
		V_DISPATCH(&key) = range.get_Range(COleVariant(strCell3),COleVariant(strCell3));
		range.Sort(key,xlAscending,covOptional,covOptional,xlAscending,covOptional,
			xlAscending,xlYes,covOptional,COleVariant((long)0),xlSortColumns,xlPinYin,0,0,0);
	}
}

void ExcelWorkbook::DeleteRow(int sheetidx,int row)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CString strCell = MakeCellName(row+1,1);
	CRange range;
	range.AttachDispatch(sheet.get_Range(COleVariant(strCell),COleVariant(strCell)));
	range.AttachDispatch(range.get_EntireRow());
	range.Delete(COleVariant((long)xlShiftUp));
}

void ExcelWorkbook::GetRowText(int sheetidx,int row,std::vector<CString>& vtStr)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);
	int nColTotal = GetUsedColumnCount(sheetidx);
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CString strCell1 = MakeCellName(row+1,1);
	CString strCell2 = MakeCellName(row+1,nColTotal);
	CRange range;
	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));
	COleSafeArray saRet = range.get_Value2();
	GetRowSafeArray(saRet,nColTotal,vtStr,_T(""));
}

void ExcelWorkbook::SetRowText(int sheetidx,int row,std::vector<CString>& vtStr)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);
	int nColTotal = GetUsedColumnCount(sheetidx);
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CString strCell1 = MakeCellName(row+1,1);
	CString strCell2 = MakeCellName(row+1,nColTotal);
	CRange range;
	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));

	COleSafeArray saRet;
	SetRowSafeArray(saRet,nColTotal,vtStr,_T(""));
	range.put_Value2(COleVariant(saRet));
}

void ExcelWorkbook::SetRowText(int sheetidx,int row,COleSafeArray& rSA)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);
	int nColTotal = GetUsedColumnCount(sheetidx);
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CString strCell1 = MakeCellName(row+1,1);
	CString strCell2 = MakeCellName(row+1,nColTotal);
	CRange range;
	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));

	long nColBound;
	rSA.GetUBound(2,&nColBound);
	//ACCHECK(nColBound == (nColTotal - 1));

	range.put_Value2(COleVariant(rSA));
}

void ExcelWorkbook::InsertRow(int sheetidx,int row,std::vector<CString>& vtStr)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);

	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));

	int nColTotal = GetUsedColumnCount(sheetidx);
	CString strCell1 = MakeCellName(row+1,1);
	CString strCell2 = MakeCellName(row+1,nColTotal);

	CRange range;
	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));
	range.Insert(COleVariant((short)xlShiftDown),covOptional);

	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));
	COleSafeArray saRet;
	SetRowSafeArray(saRet,nColTotal,vtStr,_T(" "));
	range.put_Value2(COleVariant(saRet));
}

void ExcelWorkbook::InsertRow(int sheetidx,int row,COleSafeArray& rSA)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);

	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));

	int nColTotal = GetUsedColumnCount(sheetidx);
	CString strCell1 = MakeCellName(row+1,1);
	CString strCell2 = MakeCellName(row+1,nColTotal);

	CRange range;
	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));
	range.Insert(COleVariant((short)xlShiftDown),covOptional);

	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));

	long nColBound;
	rSA.GetUBound(2,&nColBound);
	//ACCHECK(nColBound == (nColTotal - 1));

	range.put_Value2(COleVariant(rSA));
}

void ExcelWorkbook::InsertEmptyRow(int sheetidx,int row)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	ACCHECK(row >= 0 && row < EXCEL_ROW_MAX);

	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));

	int nColTotal = GetUsedColumnCount(sheetidx);
	CString strCell1 = MakeCellName(row+1,1);
	CString strCell2 = MakeCellName(row+1,nColTotal);
	
	CRange range;
	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));
	range.Insert(COleVariant((short)xlShiftDown),covOptional);

	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));
	COleSafeArray saRet;
	std::vector<CString> vtEmpty;
	SetRowSafeArray(saRet,nColTotal,vtEmpty,_T(" "));
	range.put_Value2(COleVariant(saRet));
}

void ExcelWorkbook::AppendEmptyRow(int sheetidx)
{
	ACCHECK(sheetidx >= 0 && sheetidx < GetSheetCount());
	int nRowTotal = GetUsedRowCount(sheetidx);
	int nColTotal = GetUsedColumnCount(sheetidx);
	CWorksheet sheet;
	sheet.AttachDispatch(m_objWorkSheets.get_Item(COleVariant((short)(sheetidx+1))));
	CString strCell1 = MakeCellName(nRowTotal+1,1);
	CString strCell2 = MakeCellName(nRowTotal+1,nColTotal);
	CRange range;
	range.AttachDispatch(sheet.get_Range(COleVariant(strCell1),COleVariant(strCell2)));
	COleSafeArray saRet;
	std::vector<CString> vtEmpty;
	SetRowSafeArray(saRet,nColTotal,vtEmpty,_T(" "));
	range.put_Value2(COleVariant(saRet));
}

void ExcelWorkbook::SaveWorkbook()
{
	m_objWorkbook.Save();
	m_objWorkbook.put_Saved(TRUE);
}

void ExcelWorkbook::CloseWorkbook()
{
	m_objWorkbook.put_Saved(TRUE);
	m_objWorkbook.Close(covOptional,covOptional,covOptional);
}

//--------------------------------------------------------

ExcelDB::ExcelDB(LPDISPATCH pWorkbook, SExcelConfig& rExcelConfig)
: ExcelWorkbook(pWorkbook)
{
	m_strFilePath = rExcelConfig.m_strExcelPath;
	m_strExcelCName = rExcelConfig.m_strExcelCName;
	m_strKeyCName = rExcelConfig.m_strKeyCName;
	m_strDesCName = rExcelConfig.m_strDesCName;
	m_vtLayers = rExcelConfig.m_vtLayers;
	m_nHeadRow = rExcelConfig.m_nHeadRow-1;
	m_nTypeRow = rExcelConfig.m_nTypeRow-1;
	m_nDataRow = rExcelConfig.m_nDataRow-1;

	m_mapCNameToColumn.clear();
	InitMapNameToColumn();

	SetLayersColInfo();

	m_vtDataTypes.clear();
	InitVectorDataType();

	SortDB();

	m_vtTreeItemInfos.clear();
	InitTreeItemInfos();

	CreateTree();

	if(rExcelConfig.m_bExpand)
	{
		m_pTree->ExpandAllItems();
	}
}

ExcelDB::~ExcelDB()
{
	DestroyTree();
	m_mapCNameToColumn.clear();
}

int ExcelDB::InitMapNameToColumn()
{
	ACCHECK(GetSheetCount() > 0);

	int nFirstSheet = 0;
	if(GetUsedRowCount(nFirstSheet) < m_nHeadRow)
	{
		ERROR_MSG("Require head,excel:%s",CStringToStlString(m_strFilePath).c_str());
		return -1;
	}

	std::vector<CString> vtStr;
	GetRowText(nFirstSheet,m_nHeadRow,vtStr);

	for(size_t nCol = 0; nCol < vtStr.size(); ++nCol)
	{
		CString& str = vtStr[nCol];
		if(str.IsEmpty())
			continue;

		m_mapCNameToColumn.insert(std::make_pair(str,nCol));
	}

	return 0;
}

int ExcelDB::InitTreeItemInfos()
{
	int nSheet = 0;
	int nRowTotal = GetUsedRowCount(nSheet);
	for(int nRow = m_nDataRow; nRow < nRowTotal; ++nRow)
	{
		STreeItemInfo info;
		int ret = GetTreeItemInfo(nSheet,nRow,info);
		if(ret != 0)
			break;

		m_vtTreeItemInfos.push_back(info);
	}
	return 0;
}

size_t ExcelDB::GetTreeItemInfoCount()
{
	return m_vtTreeItemInfos.size();
}

struct CompareTreeInfo
{
	bool operator()(const STreeItemInfo& lh,const STreeItemInfo& rh)
	{
		return lh.m_nKey < rh.m_nKey;
	}
};

PairTreeInfoFoundT ExcelDB::FindTreeInfoByKey(int key)
{
	PairTreeInfoFoundT result;
	STreeItemInfo info;
	info.m_nKey = key;
	result.second = std::lower_bound(m_vtTreeItemInfos.begin(),m_vtTreeItemInfos.end(),info,CompareTreeInfo());

	if(result.second == m_vtTreeItemInfos.end() || result.second->m_nKey != key)
		result.first = false;
	else
		result.first = true;

	return result;
}

int ExcelDB::WriteDBRecord(int key, MapCNameToValueT& mapValues)
{
	PairTreeInfoFoundT findResult = FindTreeInfoByKey(key);
	if(!findResult.first)
	{
		ERROR_MSG("WriteDBRecord,can't find key:%d",key);
		return -1;
	}

	STreeItemInfo& rTreeItemInfo = *(findResult.second);
	int nSheet = rTreeItemInfo.m_nSheet;
	int nRow = findResult.second - m_vtTreeItemInfos.begin() + m_nDataRow;
	std::vector<CString> vtStr;
	GetRowText(nSheet,nRow,vtStr);

	for(MapCNameToValueT::iterator iter = mapValues.begin(); iter != mapValues.end(); ++iter)
	{
		int nCtrlCol = m_mapCNameToColumn[iter->first];
		vtStr[nCtrlCol] = iter->second;
	}

	COleSafeArray sa;
	ConvertDataTypeToActual(vtStr,sa);
	SetRowText(nSheet,nRow,sa);

	SaveWorkbook();

	// 更新tree
	STreeItemInfo infoNew;
	GetTreeItemInfo(nSheet,nRow,infoNew);
	ACCHECK(infoNew.m_nKey == rTreeItemInfo.m_nKey);

	if(infoNew.m_vtLayers != rTreeItemInfo.m_vtLayers)
	{
		m_pTree->DeleteItemByKey(infoNew.m_nKey);
		m_pTree->UpdateOrInsertItemByKey(infoNew.m_nKey,infoNew.m_strDes,infoNew.m_vtLayers);
		m_pTree->SelectKey(key);
		m_pTree->UpdatedItems();
	}
	else if(infoNew.m_strDes != rTreeItemInfo.m_strDes)
	{
		m_pTree->UpdateOrInsertItemByKey(infoNew.m_nKey,infoNew.m_strDes,infoNew.m_vtLayers);
		m_pTree->UpdatedItems();
	}

	rTreeItemInfo = infoNew;
	return 0;
}

void ExcelDB::SetDBDefaultValue(MapCNameToValueT& mapDefault)
{
	m_mapDefaultValue = mapDefault;
}

void ExcelDB::GetDBDefaultValue(MapCNameToValueT& mapDefault)
{
	mapDefault = m_mapDefaultValue;
}

int ExcelDB::UpdateTreeItemInfo(STreeItemInfo& rTreeItemInfo,MapCNameToValueT& mapValues,bool bForcedUpdateTree /* = false */)
{
	bool bChanged = false;
	for(MapCNameToValueT::iterator iter = mapValues.begin(); iter != mapValues.end(); ++iter)
	{
		// 更新描述信息
		if(iter->first == m_strDesCName)
		{
			if(rTreeItemInfo.m_strDes == iter->second)
				bChanged = true;

			rTreeItemInfo.m_strDes = iter->second;
		}

		// 更新层级信息
	}

	m_pTree->UpdateOrInsertItemByKey(rTreeItemInfo.m_nKey,rTreeItemInfo.m_strDes,rTreeItemInfo.m_vtLayers);
	m_pTree->UpdatedItems();
	return 0;
}

int ExcelDB::ReadDBRecord(int key, MapCNameToValueT& mapValues)
{
	PairTreeInfoFoundT findResult = FindTreeInfoByKey(key);
	if(!findResult.first)
	{
		ERROR_MSG("ReadDBRecord,can't find key:%d",key);
		return -1;
	}

	STreeItemInfo& rTreeItemInfo = *(findResult.second);
	int nSheet = rTreeItemInfo.m_nSheet;
	int nRow = findResult.second - m_vtTreeItemInfos.begin() + m_nDataRow;

	std::vector<CString> vtStr;
	GetRowText(nSheet,nRow,vtStr);

	for(MapCNameToColumnT::iterator iter = m_mapCNameToColumn.begin(); iter != m_mapCNameToColumn.end(); ++iter)
	{
		CString& strDBVal = vtStr[iter->second];
		mapValues.insert(std::make_pair(iter->first,strDBVal));
	}

	return 0;
}

int ExcelDB::DBToTree(ToolTree* pTree)
{
	pTree->DeleteAllItems();
	pTree->InsertUndefinedRoot();

	VectorTreeItemInfoT::iterator it,ed;
	for(it = m_vtTreeItemInfos.begin(),ed = m_vtTreeItemInfos.end(); it != ed; ++it)
	{
		STreeItemInfo& rTreeItemInfo = *it;
		pTree->UpdateOrInsertItemByKey(rTreeItemInfo.m_nKey,rTreeItemInfo.m_strDes,rTreeItemInfo.m_vtLayers);
	}

	pTree->UpdatedItems();
	return 0;
}

int ExcelDB::SortDB()
{
	int nKeyCol = m_mapCNameToColumn[m_strKeyCName];
	SortAllSheetByColumn(nKeyCol,m_nDataRow);
	return 0;
}

int ExcelDB::GetKeyInExcel(int sheet,int row)
{
	int nKeyCol = m_mapCNameToColumn[m_strKeyCName];
	CString strKey = GetCellText(sheet,row,nKeyCol);
	return ACAtoi(CStringToStlString(strKey).c_str());
}

CString ExcelDB::GetDBRecordField(int nKey,const CString& strFieldName)
{
	PairTreeInfoFoundT findResult = FindTreeInfoByKey(nKey);
	if(!findResult.first)
		return _T("");
	
	if(strFieldName == m_strDesCName)
	{
		return findResult.second->m_strDes;
	}
	else
	{
		MapCNameToColumnT::iterator iter = m_mapCNameToColumn.find(strFieldName);
		if(iter == m_mapCNameToColumn.end())
			return _T("");

		int nSheet = 0;
		int nRow = findResult.second - m_vtTreeItemInfos.begin() + m_nDataRow;
		int nCol = iter->second;

		return GetCellText(nSheet,nRow,nCol);
	}

	return _T("");
}

int ExcelDB::InsertByKey(int key, MapCNameToValueT& mapValues)
{
	if(key < 0)
		return -1;

	PairTreeInfoFoundT findResult = FindTreeInfoByKey(key);
	if(findResult.first)
		return -1;

	int nSheet = 0;
	int nRow = findResult.second - m_vtTreeItemInfos.begin() + m_nDataRow;
	int nColTotal = GetUsedColumnCount(nSheet);

	std::vector<CString> vtStr;
	for(int nCol = 0; nCol < nColTotal; ++nCol)
	{
		vtStr.push_back(_T(""));
	}

	for(MapCNameToValueT::iterator iter = mapValues.begin(); iter != mapValues.end(); ++iter)
	{
		MapCNameToColumnT::iterator iterCNToCol = m_mapCNameToColumn.find(iter->first);
		if(iterCNToCol == m_mapCNameToColumn.end())
			continue;

		int nCtrlCol = m_mapCNameToColumn[iter->first];
		vtStr[nCtrlCol] = iter->second;
	}

	COleSafeArray sa;
	ConvertDataTypeToActual(vtStr,sa);
	InsertRow(nSheet,nRow,sa);

	SaveWorkbook();

	STreeItemInfo infoNew;
	GetTreeItemInfo(nSheet,nRow,infoNew);
	m_vtTreeItemInfos.insert(findResult.second,infoNew);

	// 更新tree
	m_pTree->UpdateOrInsertItemByKey(infoNew.m_nKey,infoNew.m_strDes,infoNew.m_vtLayers);
	m_pTree->SelectKey(key);
	m_pTree->UpdatedItems();

	return key;
}

int ExcelDB::GetTreeItemInfo(int nSheet,int nRow,STreeItemInfo& info)
{
	int nKeyCol = m_mapCNameToColumn[m_strKeyCName];
	int nDesCol = m_mapCNameToColumn[m_strDesCName];

	CString strKey = GetCellText(nSheet,nRow,nKeyCol);
	strKey.Trim();
	if(strKey.IsEmpty())
		return -1;

	info.m_nKey = ACAtoi(CStringToStlString(strKey).c_str());
	if(info.m_nKey < 0)
		return -1;

	info.m_strDes = GetCellText(nSheet,nRow,nDesCol);
	info.m_nSheet = nSheet;

	for(size_t i = 0; i < m_vtLayers.size(); ++i)
	{
		SLayerInfo& rLayerInfo = m_vtLayers[i];

		CString strLayerDB = GetCellText(nSheet,nRow,rLayerInfo.nCol);
		
		CString strType = rLayerInfo.strType;
		strType.MakeLower();

		CString strLayerCtrl = strLayerDB;
		if(strType == _T("comboboxint"))
		{
			strLayerCtrl = Combobox_ConvertDBToCtrl(m_strExcelCName,rLayerInfo.strCName,DATA_INT,strLayerDB);
		}

		if(strLayerCtrl.IsEmpty())
			continue;

		info.m_vtLayers.push_back(strLayerCtrl);
	}

	return 0;
}

int ExcelDB::DeleteByKey(int key)
{
	if(key < 0)
		return -1;

	PairTreeInfoFoundT findResult = FindTreeInfoByKey(key);
	if(!findResult.first)
		return -1;

	STreeItemInfo& rTreeItemInfo = *(findResult.second);
	int nRow = findResult.second - m_vtTreeItemInfos.begin() + m_nDataRow;
	DeleteRow(rTreeItemInfo.m_nSheet,nRow);

	SaveWorkbook();

	int nNextKey = -1;
	VectorTreeItemInfoT::iterator iterNext = m_vtTreeItemInfos.erase(findResult.second);
	if(iterNext != m_vtTreeItemInfos.end())
		nNextKey = iterNext->m_nKey;

	// 更新tree
	m_pTree->DeleteItemByKey(key);
	m_pTree->SelectKey(nNextKey);
	m_pTree->UpdatedItems();

	return nNextKey;
}

int ExcelDB::GetUnusedKey()
{
	if(m_vtTreeItemInfos.empty())
		return 1;

	return m_vtTreeItemInfos.back().m_nKey + 1;
}

int ExcelDB::CreateTree()
{
	m_pTree = new ToolTree(this);
	m_pTree->Create();
	DBToTree(m_pTree);
	return 0;
}

int ExcelDB::DestroyTree()
{
	_safe_delete(m_pTree);
	return 0;
}

BOOL ExcelDB::ShowTree(int nCmdShow)
{
	return m_pTree->ShowWindow(nCmdShow);
}

BOOL ExcelDB::EnableTree(BOOL bEnable)
{
	return m_pTree->EnableWindow(bEnable);
}

int ExcelDB::GetTreeLastSelected()
{
	return m_pTree->GetLastSelectKey();
}

int ExcelDB::InitVectorDataType()
{
	ACCHECK(GetSheetCount() > 0);

	int nFirstSheet = 0;
	if(GetUsedRowCount(nFirstSheet) < m_nTypeRow)
	{
		ERROR_MSG("Require type,excel:%s",CStringToStlString(m_strFilePath).c_str());
		return -1;
	}

	std::vector<CString> vtStr;
	GetRowText(nFirstSheet,m_nTypeRow,vtStr);

	for(size_t nCol = 0; nCol < vtStr.size(); ++nCol)
	{
		m_vtDataTypes.push_back(GetDataTypeFromName(vtStr[nCol]));
	}

	return 0;
}

void ExcelDB::ConvertDataTypeToActual(std::vector<CString>& vtStrValues,COleSafeArray& rSA)
{
	DWORD numElements[] = {1,vtStrValues.size()};
	rSA.Create(VT_VARIANT,2,numElements);

	long index[2];
	index[0] = 0;

	for(size_t nCol = 0; nCol < vtStrValues.size(); ++nCol)
	{
		index[1] = nCol;
		VARIANT var;
		VariantInit(&var);
		switch(m_vtDataTypes[nCol])
		{
		case DATA_INT:
			var.vt = VT_I4;
			var.lVal = ACAtoi(CStringToStlString(vtStrValues[nCol]).c_str());
			rSA.PutElement(index,&var);
			break;
		case DATA_FLOAT:
			var.vt = VT_R8;
			var.dblVal = ACAtof(CStringToStlString(vtStrValues[nCol]).c_str());
			rSA.PutElement(index,&var);
			break;
		case DATA_BOOL:
			{
				VARIANT_BOOL bValue = VARIANT_FALSE;
				CString strValue = vtStrValues[nCol];
				strValue.Trim();
				strValue.MakeLower();
				if(strValue == _T("true"))
					bValue = VARIANT_TRUE;
				else if(strValue == _T("false"))
					bValue = VARIANT_FALSE;
				else
				{
					bool bb = ACAtoi(CStringToStlString(strValue).c_str());
					bValue = bb ? VARIANT_TRUE : VARIANT_FALSE;
				}
				var.vt = VT_BOOL;
				var.boolVal = bValue;
				rSA.PutElement(index,&var);
			}
			break;
		case DATA_STRING:
			var.vt = VT_BSTR;
			var.bstrVal = SysAllocString(vtStrValues[nCol].GetBuffer());
			rSA.PutElement(index,&var);
			SysFreeString(var.bstrVal);
			break;
		}
		VariantClear(&var);
	}
}

void ExcelDB::SetLayersColInfo()
{
	for(size_t i = 0; i < m_vtLayers.size(); ++i)
	{
		CString& strCName = m_vtLayers[i].strCName;
		MapCNameToColumnT::iterator iter = m_mapCNameToColumn.find(strCName);
		if(iter == m_mapCNameToColumn.end())
		{
			CString strErr;
			strErr.Format(_T("SetLayersColInfo failed,layer name:%s"),strCName);
			ErrorMessageBox(strErr);
			ExitProcess(-1);
		}

		m_vtLayers[i].nCol = iter->second;
	}
}

//--------------------------------------------------------

ToolExcel::ToolExcel(ToolApp* app)
: Module<ToolApp>(app)
{
	CreateExcelServer();
}

ToolExcel::~ToolExcel()
{
	DestroyExcelServer();
}

int ToolExcel::CreateExcelServer()
{
	if(!AfxOleInit())
	{
		ErrorMessageBox(_T("Error! Ole initial failed!"));
		ExitProcess(-1);
	}

	if(!m_objApplication.CreateDispatch(_T("Excel.Application")))
	{
		ErrorMessageBox(_T("Error! Creat excel application server failed!"));
		ExitProcess(-1);
	}

	/*m_objApplication.put_AlertBeforeOverwriting(FALSE);
	m_objApplication.put_DisplayAlerts(FALSE);*/
	m_objApplication.put_Visible(TRUE);
	m_objApplication.put_UserControl(TRUE);

	m_objWorkbooks.AttachDispatch(m_objApplication.get_Workbooks());
	return 0;
}

int ToolExcel::DestroyExcelServer()
{
	for(MapNameToWorkbookT::iterator iter = m_mapWorkbooks.begin(); iter != m_mapWorkbooks.end(); ++iter)
	{
		ExcelDB* pBook = iter->second;
		pBook->CloseWorkbook();
		_safe_delete(pBook);
	}

	m_mapWorkbooks.clear();
	m_objWorkbooks.Close();
	m_objWorkbooks.ReleaseDispatch();
	m_objApplication.Quit();
	m_objApplication.ReleaseDispatch();
	return 0;
}

ExcelDB* ToolExcel::OpenWorkbook(SExcelConfig& rExcelConfig)
{
	MapNameToWorkbookT::iterator iter = m_mapWorkbooks.find(rExcelConfig.m_strExcelCName);
	if(iter != m_mapWorkbooks.end())
		return iter->second;

	LPDISPATCH workbook = m_objWorkbooks.Open(rExcelConfig.m_strExcelPath,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,
		covOptional,covOptional,covOptional,covOptional,covOptional,covOptional);

	ExcelDB* pExcelDB = new ExcelDB(workbook,rExcelConfig);
	m_mapWorkbooks.insert(std::make_pair(rExcelConfig.m_strExcelCName,pExcelDB));
	return pExcelDB;
}

ExcelDB* ToolExcel::GetWorkbook(CString strExcelCName)
{
	MapNameToWorkbookT::iterator iter = m_mapWorkbooks.find(strExcelCName);
	if(iter != m_mapWorkbooks.end())
		return iter->second;

	return NULL;
}

END_NS_AC