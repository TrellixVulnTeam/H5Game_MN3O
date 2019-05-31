using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.Odbc;
using System.IO;
using Excel = Microsoft.Office.Interop.Excel;


namespace CtrlExcel
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args[0] == null)
            {
                Console.WriteLine("Error : No param for file path...");

                return;
            }

            if (args[1] == null)
            {
                Console.WriteLine("Error : No param for map name...");

                return;
            }
                
            //string path = System.IO.Directory.GetCurrentDirectory() + args[0];

            string path = args[0];

            string mapname = args[1];
            
            //Console.WriteLine(path);

            if (File.Exists(path))
            {
                DataTable dt = Load.ParseExcel(path,mapname);

                //File.Delete(path);

                Save.SaveDataTableToExcel(dt, path, mapname);
            }
            else
            {
                Console.WriteLine("Error : File Not Found : {0}",path);
            }
           
            //Console.Read();
        }
    }

    class Save
    {
        public static bool SaveDataTableToExcel(System.Data.DataTable excelTable, string filePath, string mapname)
        {
            Excel.Application app = new Excel.ApplicationClass();
            try
            {
                app.Visible = false;

                //Excel.Workbook wBook = app.Workbooks.Add(true);
                //Excel.Worksheet wSheet = wBook.Worksheets[1] as Excel.Worksheet;

                Object oMissing = System.Reflection.Missing.Value;

                Excel.Workbook wBook = app.Workbooks.Open(filePath, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing, oMissing);
            
                Excel.Worksheet wSheet = null;

                for (int i = 1; i <= wBook.Sheets.Count; i++)
                {
                    Excel.Worksheet wSheetTemp = wBook.Worksheets[i] as Excel.Worksheet;

                    if (wSheetTemp.Name == mapname)
                    {
                        wSheet = wSheetTemp;
                        
                        wSheet.ClearArrows();
                        
                        break;
                    }
                }

                if (wSheet == null)
                    return false;
                
                
                if (excelTable.Rows.Count > 0)
                {
                    int row = 0;
                    row = excelTable.Rows.Count;
                    int col = excelTable.Columns.Count;

                    wSheet.Cells[2, 1] = "map";
                    wSheet.Cells[2, 2] = "point_name";
                    wSheet.Cells[2, 3] = "pos_x";
                    wSheet.Cells[2, 4] = "pos_y";
                    wSheet.Cells[2, 5] = "pos_z";
                    wSheet.Cells[2, 6] = "orientation";

                    wSheet.Cells[3, 1] = "int";
                    wSheet.Cells[3, 2] = "string";
                    wSheet.Cells[3, 3] = "float";
                    wSheet.Cells[3, 4] = "float";
                    wSheet.Cells[3, 5] = "float";
                    wSheet.Cells[3, 6] = "float";

                    wSheet.Cells[4, 1] = "cs";
                    wSheet.Cells[4, 2] = "cs";
                    wSheet.Cells[4, 3] = "cs";
                    wSheet.Cells[4, 4] = "cs";
                    wSheet.Cells[4, 5] = "cs";
                    wSheet.Cells[4, 6] = "cs";

                    for (int i = 3; i < row; i++)
                    {
                        for (int j = 0; j < col; j++)
                        {
                            string str = excelTable.Rows[i][j].ToString();
                            wSheet.Cells[i + 2, j + 1] = str;
                        }
                    }
                }

                int size = excelTable.Columns.Count;
                for (int i = 0; i < size; i++)
                {
                    wSheet.Cells[1, 1 + i] = excelTable.Columns[i].ColumnName;
                }
                //设置禁止弹出保存和覆盖的询问提示框 C# 写入excel及读取Excel实例
                app.DisplayAlerts = false;
                app.AlertBeforeOverwriting = false;
                //保存工作簿 < type="text/JavaScript"> alimama_pid="mm_10249644_1605763_5027492"; alimama_type="f"; alimama_sizecode ="tl_1x5_8"; alimama_fontsize=12; alimama_bordercolor="FFFFFF"; alimama_bgcolor="FFFFFF"; alimama_titlecolor="0000FF"; alimama_underline=0; alimama_height=22; alimama_width=0; < src="http://a.alimama.cn/inf.js" type=text/javascript> 
                //wBook.Save();
               
                wBook.Save();
            
                //wBook.SaveAs(filePath, Excel.XlFileFormat.xlWorkbookNormal, null, null, false, false, Excel.XlSaveAsAccessMode.xlShared, false, false, null, null, null);
                //wBook.SaveAs(filePath, 56, null, null, false, false, Excel.XlSaveAsAccessMode.xlShared, false, false, null, null, null);


                //保存excel文件 
                //app.Save(filePath);
                //app.SaveWorkspace(filePath);
               
                app.Quit();
                app = null;
                return true;
            }
            catch (Exception err)
            {

                Console.WriteLine("导出Excel出错！错误原因：" + err.Message);
                return false;
            }
            finally
            {

            }
        }
    }
    class Load
    {
        public static DataTable ParseExcel(string path,string mapname)
        {
            try
            {
                string con = "Driver={Microsoft Excel Driver (*.xls)}; DriverId=790; Dbq=" + path + ";";

                string yourQuery = "SELECT * FROM [" + mapname + "$]";

                OdbcConnection oCon = new OdbcConnection(con);

                OdbcCommand oCmd = new OdbcCommand(yourQuery, oCon);

                DataTable dtYourData = new DataTable("YourData");

                oCon.Open();

                OdbcDataReader rData = oCmd.ExecuteReader();

                dtYourData.Load(rData);

                rData.Close();

                oCon.Close();

                return dtYourData;
            }
            catch (System.Exception ex)
            {
                Console.WriteLine("数据绑定Excel失败 ：" + ex.Message);

                return null;
            }

        }
    }
}
