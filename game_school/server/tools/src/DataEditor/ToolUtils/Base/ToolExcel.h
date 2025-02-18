#ifndef _TOOL_EXCEL_H_
#define _TOOL_EXCEL_H_

#include "ToolDef.h"
#include "ToolApp.h"

#include "ToolExcelDef.h"

#include "stdafx.h"
#include "CApplication.h"
#include "CWorkbooks.h"
#include "CWorkbook.h"
#include "CWorksheets.h"
#include "CWorksheet.h"
#include "CRange.h"

BEGIN_NS_AC

class ToolTree;

// 将行号列好转成Cell的名字，如(1000,52) = "AZ1000"
CString MakeCellName(int nRow,int nCol);

class ExcelWorkbook
{
public:
	ExcelWorkbook(LPDISPATCH workbook);
	virtual ~ExcelWorkbook();
public:
	int GetSheetCount();
	int GetUsedRowCount(int sheetidx);
	int GetUsedColumnCount(int sheetidx);
public:
	CString GetCellText(int sheetidx,int row,int col);
	void SetCellText(int sheetidx,int row,int col,CString val);
	void SetCellText(int sheetidx,int row,int col,int val);
public:
	void SortAllSheetByColumn(int sortByCol,int startRow);
public:
	void DeleteRow(int sheetidx,int row);
	void GetRowText(int sheetidx,int row,std::vector<CString>& vtStr);
	void SetRowText(int sheetidx,int row,std::vector<CString>& vtStr);
	void SetRowText(int sheetidx,int row,COleSafeArray& rSA);
	void InsertRow(int sheetidx,int row,std::vector<CString>& vtStr);
	void InsertRow(int sheetidx,int row,COleSafeArray& rSA);
	void InsertEmptyRow(int sheetidx,int row);
	void AppendEmptyRow(int sheetidx);
public:
	void SaveWorkbook();
	void CloseWorkbook();
private:
	CWorkbook m_objWorkbook;
	CWorksheets m_objWorkSheets;
};

//--------------------------------------------------------------

typedef std::map<CString,size_t> MapCNameToColumnT;

struct STreeItemInfo
{
	int m_nKey;
	CString m_strDes;
	std::vector<CString> m_vtLayers;
	int m_nSheet;
};

typedef std::vector<STreeItemInfo> VectorTreeItemInfoT;

typedef std::pair<bool,VectorTreeItemInfoT::iterator> PairTreeInfoFoundT;

class ExcelDB : public ExcelWorkbook
{
public:
	ExcelDB(LPDISPATCH pWorkbook, SExcelConfig& rExcelConfig);
	virtual ~ExcelDB();
public:
	virtual int ReadDBRecord(int key, MapCNameToValueT& mapValues);
	virtual int WriteDBRecord(int key, MapCNameToValueT& mapValues);

	virtual void SetDBDefaultValue(MapCNameToValueT& mapDefault);
	virtual void GetDBDefaultValue(MapCNameToValueT& mapDefault);

	virtual int DBToTree(ToolTree* pTree);
	virtual int SortDB();

	virtual int InsertByKey(int key, MapCNameToValueT& mapValues);
	virtual int DeleteByKey(int key);
	virtual int GetUnusedKey();

	int InitMapNameToColumn();

	int InitTreeItemInfos();
	int GetTreeItemInfo(int nSheet,int nRow,STreeItemInfo& info);
	int UpdateTreeItemInfo(STreeItemInfo& rTreeItemInfo,MapCNameToValueT& mapValues,bool bForcedUpdateTree = false);
	PairTreeInfoFoundT FindTreeInfoByKey(int key);
	size_t GetTreeItemInfoCount();

	int GetKeyInExcel(int sheet,int row);

	CString GetDBRecordField(int nKey,const CString& strFieldName);
public:
	int CreateTree();
	int DestroyTree();
	BOOL ShowTree(int nCmdShow);
	BOOL EnableTree(BOOL bEnable);
	int GetTreeLastSelected();
public:
	int InitVectorDataType();
	void ConvertDataTypeToActual(std::vector<CString>& vtStrValues,COleSafeArray& rSA);
private:
	void SetLayersColInfo();
private:
	CString m_strFilePath;
	CString m_strExcelCName;
	CString m_strKeyCName;
	CString m_strDesCName;

	std::vector<SLayerInfo> m_vtLayers;// 控制主树控件层级的控件

	int m_nHeadRow;
	int m_nTypeRow;
	int m_nDataRow;
	MapCNameToColumnT m_mapCNameToColumn;
	VectorTreeItemInfoT m_vtTreeItemInfos;
	MapCNameToValueT m_mapDefaultValue;

	std::vector<int> m_vtDataTypes;
public:
	inline ToolTree* GetTree()
	{
		return m_pTree;
	}
private:
	ToolTree* m_pTree;
};

//--------------------------------------------------------------

class ToolExcel : public Module<ToolApp>
{
public:
	ToolExcel(ToolApp* app);
	virtual ~ToolExcel();
public:
	int CreateExcelServer();
	int DestroyExcelServer();
public:
	ExcelDB* OpenWorkbook(SExcelConfig& rExcelConfig);
	ExcelDB* GetWorkbook(CString strExcelCName);
protected:
	typedef std::map<CString,ExcelDB*> MapNameToWorkbookT;
private:
	CApplication m_objApplication;
	CWorkbooks m_objWorkbooks;
	MapNameToWorkbookT m_mapWorkbooks;
};

END_NS_AC

#endif//_TOOL_EXCEL_H_