﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using CSharpJExcel.Jxl;
using CSharpJExcel.Interop;

namespace gen_csv
{
    public partial class gen_csv : Form
    {
        [System.Runtime.InteropServices.DllImport("kernel32")]

        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);

        [System.Runtime.InteropServices.DllImport("kernel32")]

        private static extern int GetPrivateProfileString(string section, string key, string def, System.Text.StringBuilder retVal, int size, string filePath);


        private string m_strServerPath;
        private int m_nSelectIdx;

        const int cst_RowForChineseName = 0;
        const int cst_RowForName = 1;
        const int cst_RowForType = 2;
        const int cst_RowForSide = 3;
        const int cst_RowForData = cst_RowForSide + 1;

        public gen_csv()
        {
            InitializeComponent();
            
            StringBuilder temp = new StringBuilder(255);
            GetPrivateProfileString("ServerPathInfo", "Path", "E:\\workspace\\pwngs\\server", temp, 255, ".\\gen_csv.ini");
            
            m_strServerPath = temp.ToString();
            
            textBox.Text = m_strServerPath;

            // 多语言版本下拉框
            versionbox.Items.Add("中文");
            versionbox.Items.Add("韩文");
            versionbox.Items.Add("日文");
            versionbox.Items.Add("腾讯");
            versionbox.SelectedIndex = 0;

            m_nSelectIdx = versionbox.SelectedIndex;
        }

        void ShowMessage(string table,string sheet,int row,int col,string error)
        {
            string str = "Table:" + table + "Config" + " Sheet:" + sheet + " Row:" + row + " Col:" + col;
            MessageBox.Show(str,error);
        }

        string GetStringFromCell(Sheet sheet, int row, int col,string name)
        {
            string str = "";

            Cell cell = sheet.getCell(col, row);
            CellType cellType = cell.getType();

            if (cellType.Equals(CellType.LABEL))
            {
                str = cell.getContents();

                // 数据层才生效
                if (row >= cst_RowForData)
                {
                    string type = GetStringFromCell(sheet, cst_RowForType, col, name);
                    if (type.Equals("bool"))
                    {
                        if (str.Equals("TRUE", StringComparison.OrdinalIgnoreCase))
                        {
                            str = 1.ToString();
                        }
                        else if (str.Equals("FALSE", StringComparison.OrdinalIgnoreCase))
                        {
                            str = 0.ToString();
                        }
                        else
                        {
                            ShowMessage(name, sheet.getName(), row, col, "type error");
                        }
                    }
                }
            }
            else if (cellType.Equals(CellType.NUMBER))
            {
                string type = GetStringFromCell(sheet, cst_RowForType, col,name);

                NumberCell numCell = (NumberCell)cell;
                double value = numCell.getValue();

                try 
                {
                    if (type.Equals("int"))
                    {
                        str = ((int)value).ToString();
                    }
                    else if (type.Equals("long"))
                    {
                        str = ((long)value).ToString();
                    }
                    else if (type.Equals("float"))
                    {
                        str = ((float)value).ToString("F6");
                    }
                    else if (type.Equals("double"))
                    {
                        str = ((double)value).ToString("F6");
                    }
                    else if (type.Equals("string") || type.Contains("int[") || type.Contains("float[") || type.Contains("string[") || type.Contains("long["))
                    {
                        str = value.ToString();
                    }
                    else
                    {
                        ShowMessage(name, sheet.getName(), row, col, "type error");
                    }
                }
                catch (Exception ex)
                {
                    //MessageBox.Show(ex.ToString());
                    ShowMessage(name, sheet.getName(), row, col, "data error");
                }
            }
            else if (cellType.Equals(CellType.BOOLEAN))
            {
                string type = GetStringFromCell(sheet, cst_RowForType, col, name);

                BooleanCell boolCell = (BooleanCell)cell;
                //bool value = boolCell.getValue();

                string value = boolCell.getContents();

                if(type.Equals("bool"))
                {
                    if(value.Equals("TRUE",StringComparison.OrdinalIgnoreCase))
                    {
                        str = 1.ToString();
                    }
                    else if (value.Equals("FALSE", StringComparison.OrdinalIgnoreCase))
                    {
                        str = 0.ToString();
                    }
                    //str = value.ToString();
                }
                else
                {
                    ShowMessage(name, sheet.getName(), row, col, "type error");
                }
            }
            else if (cellType.Equals(CellType.EMPTY))
            {
                str = cell.getContents();
            }
            else if (cellType.Equals(CellType.DATE))
            {
                str = cell.getContents();
            }
            else
            {
                ShowMessage(name, sheet.getName(), row, col, "invalid data type");
            }

            str = str.Replace("\r", "");
            str = str.Replace("\n", "");
            str = str.Replace("\t", "");
            str = str.Replace(" ", "");

            return str;
        }

        private void button_Click(object sender, EventArgs e)
        {
            string strSearchDir;
            string strCppsDir;
            string strCsvsDir;

            m_strServerPath = textBox.Text;

            if(m_strServerPath.Length <= 0)
            {
                MessageBox.Show("Invalid Input");
                return;
            }

            // 选择多国版本
            int result = SelectVersion();
            if (result != 0)
                return;

            if(m_strServerPath.Substring(m_strServerPath.Length-1,1) != "\\")
            {
                m_strServerPath += "\\";
            }

            strSearchDir = m_strServerPath + "..\\shared\\config\\";
            strCppsDir = m_strServerPath + "pwworldsrv\\conf\\";
            strCsvsDir = m_strServerPath + "bin\\data\\csv\\";

            if (!Directory.Exists(strSearchDir))
            {
                MessageBox.Show("Invalid Directory");
                return;
            }

            if (!Directory.Exists(strCppsDir))
            {
                Directory.CreateDirectory(strCppsDir);
            }

            if (!Directory.Exists(strCsvsDir))
            {
                Directory.CreateDirectory(strCsvsDir);
            }

            string[] files = Directory.GetFiles(strSearchDir, "*.xls");
            
            //TODO:: log
             if (listBox.Items.Count > 0)
            {
                listBox.Items.Clear();
            }

            for (int i = 0; i < files.Length; i++)
            {
                string file = files[i];

                if(Path.GetExtension(file).ToLower() != ".xls")
                    continue;
                
                string name = Path.GetFileNameWithoutExtension(file);

                string str = "Config";

                if (name.IndexOf(str) > -1)
                {
                    name = name.Substring(0, name.Length - str.Length);
                }

                string hppfile = strCppsDir + "pwconf_" + name + ".h";
                string cppfile = strCppsDir + "pwconf_" + name + ".cpp";
                string csvfile = strCsvsDir + "pwconf_" + name + ".csv";

                Generate(name, file, hppfile, cppfile, csvfile);

//                 if(name.ToLower() == "magictype" || 
//                     name.ToLower() == "effectcommon" ||
//                     name.ToLower() == "effectcollision" ||
//                     name.ToLower() == "effectmotion" ||
//                     name.ToLower() == "effectflexible" ||
//                     name.ToLower() == "aura" ||
//                     name.ToLower() == "auraeffect")
//                 {
//                     string dir = m_strServerPath + "pwworldsrv\\magic\\";
//                     string cpp = dir + "pw_modifier_" + name.ToLower() + ".cpp";
//                     GenerateModifier(name, file, cpp);
//                 }

                string filepath = Path.GetFullPath(file);
                string log = "Generated : " + filepath;
                listBox.Items.Add(log.ToString());
            }

            textBox.Text = m_strServerPath;
            WritePrivateProfileString("ServerPathInfo", "Path", m_strServerPath, ".\\gen_csv.ini");
            listBox.Items.Add("Generate Completed.");
        }

        long bkdr_hash_and_sum(string s)
        {
            long sum = 0;
            int seed = 131; // 31 131 1313 13131 131313 etc..
            int hash = 0;

            for (int i = 0; i < s.Length; ++i)
            {
                sum += s[i];
                hash = hash * seed + s[i];
            }

            return (sum << 32) + (hash & 0x7FFFFFFF);
        }

        void GenerateModifier(string name, string file, string cppfile)
        {
            Workbook w = Workbook.getWorkbook(new FileInfo(file));
            if (w == null)
            {
                listBox.Items.Add("modifier Error Open File:" + file);
                return;
            }

            File.Delete(cppfile);

            FileStream stream = new FileStream(cppfile, FileMode.CreateNew);
            StreamWriter writer = new StreamWriter(stream, Encoding.UTF8);

            Sheet s = w.getSheet(0);

            string tname = "";
            string ename = "";

            switch (name.ToLower())
            {
                case "magictype":
                    tname = "SMagicType";
                    ename = "MAGIC_MODIFIER_TYPE_MAGIC";
                    break;
                case "effectcommon":
                    tname = "SEffectCommon";
                    ename = "MAGIC_MODIFIER_TYPE_EFFECT_COMMON";
                    break;
                case "effectcollision":
                    tname = "SEffectCollision";
                    ename = "MAGIC_MODIFIER_TYPE_EFFECT_COLLISION";
                    break;
                case "effectmotion":
                    tname = "SEffectMotion";
                    ename = "MAGIC_MODIFIER_TYPE_EFFECT_MOTION";
                    break;
                case "effectflexible":
                    tname = "SEffectFlexible";
                    ename = "MAGIC_MODIFIER_TYPE_EFFECT_FLEXIBLES";
                    break;
                case "aura":
                    tname = "SAuraType";
                    ename = "MAGIC_MODIFIER_TYPE_AURA";
                    break;
                case "auraeffect":
                    tname = "SAuraEffect";
                    ename = "MAGIC_MODIFIER_TYPE_AURA_EFFECT";
                    break;
            }
            // extern int ExecuteMagicModifier(SMagicType* target,SMagicModifier* modifier);
            writer.WriteLine("#include \"pw_magic_modifier.h\"");
            writer.WriteLine("");
            writer.WriteLine("namespace pwngs");
            writer.WriteLine("{");

            writer.WriteLine("\t" + "int ExecuteMagicModifier(" + tname + "* target,SMagicModifier* modifier)");
            writer.WriteLine("\t" + "{");
            writer.WriteLine("\t\t" + "if(modifier->type != " + ename + ")");
            writer.WriteLine("\t\t\t" + "return 0;");
            writer.WriteLine("\t\t" + "switch(modifier->field_hash)");
            writer.WriteLine("\t\t" + "{");


            int cols = s.getColumns();
            int rows = s.getRows();

            for (int j = 0; j < cols; j++)
            {
                string colm_name = GetStringFromCell(s, 1, j, name);
                string type_name = GetStringFromCell(s, 2, j, name);
                string cs = GetStringFromCell(s, 3, j, name);

                if (cs.Trim() == "c")
                    continue;
                long hash = bkdr_hash_and_sum(colm_name);

                if (type_name != "int" && type_name != "float" && type_name != "long" && type_name != "bool")
                    continue;

                writer.WriteLine("\t\t" + "case " + hash.ToString() + ":" + "// field " + colm_name + " type=" + type_name);
                writer.WriteLine("\t\t\t" + "{");
                writer.WriteLine("\t\t\t\t" + "ExecuteMagicModifier(" + "target->" + colm_name + ",modifier->operation,modifier->value);");
                writer.WriteLine("\t\t\t" + "}");
                writer.WriteLine("\t\t\t" + "break;");
            }

            writer.WriteLine("\t\t" + "default:");
            writer.WriteLine("\t\t\t" + "return -2;");
            writer.WriteLine("\t\t}");
            writer.WriteLine("\t\treturn 0;");
            writer.WriteLine("\t}");
            writer.WriteLine("}");
            writer.Flush();

            writer.Close();
            stream.Close();
            w.close();
        }        

        void Generate(string name, string file, string hpp_file, string cpp_file, string csv_file)
        {
            Encoding e = new UTF8Encoding(false);

            File.Delete(csv_file);

            FileStream stream = new FileStream(csv_file, FileMode.CreateNew);

            StreamWriter writer = new StreamWriter(stream,e);

            Workbook w = Workbook.getWorkbook(new FileInfo(file));
            if (w == null)
            {
                //TODO::log
                listBox.Items.Add("Error Open File:");
                return;
            }

            for (int i = 0; i < w.getNumberOfSheets(); ++i)
            {
                Sheet s = w.getSheet(i);

                if (i == 0)
                {
                    GenerateCsvHeader(s, writer,name);

                    if (File.Exists(hpp_file) && File.Exists(cpp_file))
                    {
                        //TODO::log
                        string log = "Ignore generate(Hpp,Cpp): " + name;
                        listBox.Items.Add(log.ToString());
                    }
                    else
                    {
                        GenerateHpp(s, hpp_file, name);
                        GenerateCpp(s, cpp_file, name);
                    }
                }
                GenerateCsv(s,writer,name);
            }

            writer.Close();
            stream.Close();
        }

        void W2F(int tabcount, StreamWriter writer,string value)
        {
            for (int i = 0; i < tabcount; ++i)
            {
                value = "\t" + value;
            }

            writer.WriteLine(value);
        }

        void GenerateHpp(Sheet sheet,string hpp_file,string name)
        {
            if (File.Exists(hpp_file))
                File.Delete(hpp_file);

            FileStream stream = new FileStream(hpp_file, FileMode.CreateNew);
            StreamWriter writer = new StreamWriter(stream, Encoding.Default);

            string structname = "S" + name;
            string filename = Path.GetFileName(hpp_file);

            W2F(0, writer, "#ifndef _config_" + name + "_included_");
            W2F(0, writer, "#define _config_" + name + "_included_");
            W2F(0, writer, "");
	        W2F(0, writer, "#include \"pw_def.h\"");
            W2F(0, writer, "");

            W2F(0, writer, "namespace pwconf");
            W2F(0, writer, "{");
            W2F(0, writer, "");
                W2F(1, writer, "struct " + structname);
                W2F(1, writer, "{");
                for (int i = 0; i < sheet.getColumns(); ++i)
                {
                    string colname = GetStringFromCell(sheet,cst_RowForName,i,name);
                    string typname = GetStringFromCell(sheet,cst_RowForType,i,name);
                    string cnname = GetStringFromCell(sheet, cst_RowForChineseName, i, name);

                    if(typname.Equals("int"))
					    W2F(2,writer,"int32 " + colname + ";\t// " + cnname);
				    else if(typname.Equals("long"))
                        W2F(2,writer,"int64 " + colname + ";\t// " + cnname);
				    else if(typname.Equals("float"))
                        W2F(2,writer,"float " + colname + ";\t// " + cnname);
				    else if(typname.Equals("double"))
                        W2F(2,writer,"double " + colname + ";\t// " + cnname);
				    else if(typname.Equals("string"))
                        W2F(2,writer,"std::string " + colname + ";\t// " + cnname);
				    else if(typname.Equals("bool"))
                        W2F(2,writer,"bool " + colname + ";\t// " + cnname);
				    /*else if(typname.Equals("string[]"))
                        W2F(2,writer,"std::vector<std::string> " + colname + ";\t// " + cnname);
				    else if(typname.Equals("float[]"))
                        W2F(2,writer,"std::vector<float> " + colname + ";\t// " + cnname);
				    else if(typname.Equals("int[]"))
                        W2F(2,writer,"std::vector<int32> " + colname + ";\t// " + cnname);*/
                    else if (typname.Contains("string["))
                    {
                        if (typname.Equals("string[]"))
                        {
                            W2F(2, writer, "std::vector<std::string> " + colname + ";\t// " + cnname);
                        }
                        else if (typname.Substring(typname.Length-1, 1).Equals("]"))
                        {
                            int val = int.Parse(typname.Substring(7, typname.Length - 8));

                            W2F(2, writer, "std::string "+ colname + "[" + val + "]" + ";\t// " + cnname);
                        }
                    }
                    else if (typname.Contains("float["))
                    {
                        if (typname.Equals("float[]"))
                        {
                            W2F(2, writer, "std::vector<float> " + colname + ";\t// " + cnname);
                        }
                        else if (typname.Substring(typname.Length - 1, 1).Equals("]"))
                        {
                            int val = int.Parse(typname.Substring(6, typname.Length - 7));

                            W2F(2, writer, "float " + colname + "[" + val + "]" + ";\t// " + cnname);
                        }
                    }
                    else if (typname.Contains("int["))
                    {
                        if (typname.Equals("int[]"))
                        {
                            W2F(2,writer,"std::vector<int32> " + colname + ";\t// " + cnname);
                        }
                        else if (typname.Substring(typname.Length - 1, 1).Equals("]"))
                        {
                            int val = int.Parse(typname.Substring(4, typname.Length - 5));

                            W2F(2, writer, "int " + colname + "[" + val + "]" + ";\t// " + cnname);
                        }
                    }
                    else if (typname.Contains("long["))
                    {
                        if (typname.Equals("long[]"))
                        {
                            W2F(2, writer, "std::vector<int64> " + colname + ";\t// " + cnname);
                        }
                        else if (typname.Substring(typname.Length - 1, 1).Equals("]"))
                        {
                            int val = int.Parse(typname.Substring(5, typname.Length - 6));

                            W2F(2, writer, "int64 " + colname + "[" + val + "]" + ";\t// " + cnname);
                        }
                    } 
                    else if (typname.Equals(""))
                        continue;
                    else
                        ShowMessage(name, sheet.getName(), cst_RowForType, i, "invalid_configure");
                }
                W2F(1, writer, "};");
		        W2F(1, writer, "");

                W2F(1, writer, "/* ");
                W2F(1, writer,"@class " + name + " ");
                W2F(1, writer,"@author tool GenCSV");
                W2F(1, writer,"@date " + DateTime.Now.ToString());
                W2F(1, writer,"@file " + filename);
                W2F(1, writer,"@brief 从" + name + "文件中自动生成的配置类");
                W2F(1, writer, "*/ ");

                W2F(1, writer, "class " + name);
                W2F(1, writer, "{");
                    W2F(1,writer,"public:");
                        W2F(2, writer, "bool LoadFrom(const char* filename);");
                        W2F(2, writer,"bool LoadFrom(const std::string& filename)");
                        W2F(2, writer, "{");
                            W2F(3, writer,"return LoadFrom(filename.c_str());");
				        W2F(2, writer, "}");

                    W2F(1, writer,"public:");
                        W2F(2, writer, structname + "& Get(size_t);");
                    W2F(1, writer, "public:");
				        W2F(2, writer, "inline size_t Count()");
                        W2F(2, writer, "{");
                            W2F(3, writer, "return m_vtConfigures.size();");
                        W2F(2, writer, "}");
                    W2F(1, writer, "private:");
				        W2F(2, writer, "typedef std::vector<" + structname + "> CollectionConfiguresT;");
                    W2F(1, writer, "private:");
				        W2F(2, writer, "CollectionConfiguresT m_vtConfigures;");
                W2F(1, writer, "};");
	        W2F(0, writer, "}");

            W2F(0, writer, "#endif // _config_" + name + "_included_\r\n");

            writer.Close();
            stream.Close();
        }

        void GenerateCpp(Sheet sheet, string cpp_file, string name)
        {
            if (File.Exists(cpp_file))
                File.Delete(cpp_file);

            FileStream stream = new FileStream(cpp_file, FileMode.CreateNew);
            StreamWriter writer = new StreamWriter(stream, Encoding.Default);

            string structname = "S" + name;
            string filename = Path.GetFileName(cpp_file);
            string classname = name;

            W2F(0, writer, "#include \"pwconf_" + name + ".h\"");
	        W2F(0, writer, "#include \"pw_csv.h\"");
	        W2F(0, writer, "#include \"tokenizer.h\"");
	        W2F(0, writer, "#include \"pw_utils.h\"");
	        W2F(0, writer, "#include \"pw_logger.h\"");
	        W2F(0, writer, "");

	        W2F(0, writer, "namespace pwconf");

            W2F(0, writer, "{");

                // LoadFrom
		        W2F(1, writer, "bool " + classname + "::LoadFrom(const char* filename)");
                W2F(1, writer, "{");
                    W2F(2, writer, "pwutils::CSVReader csv;");
			        W2F(2, writer, "if(csv.load(filename) != 0)");
                        W2F(3, writer, "return false;");
                    for (int col = 0; col < sheet.getColumns(); ++col)
                    {
                        string colname = GetStringFromCell(sheet, cst_RowForName, col, name);
                        string cnname = GetStringFromCell(sheet, cst_RowForChineseName, col, name);

                        if (colname.Equals("") || cnname.Equals(""))
                            continue;

                        W2F(2, writer, "size_t index_" + colname + " = csv.index(\"" + colname + "\"," + cst_RowForName.ToString() + ");");
				        W2F(2, writer, "pwassertn(index_" + colname + " != (size_t)-1);");
				        W2F(2, writer, "");
                    }
                    W2F(2, writer, "");
			        W2F(2, writer, "for(size_t row = " + (cst_RowForData-1).ToString() + "; row < csv.count(); ++row)");
			        W2F(2, writer, "{");
                        W2F(3, writer, structname + " conf;");
                        for (int col = 0; col < sheet.getColumns(); ++col)
                        {
                            string colname = GetStringFromCell(sheet, cst_RowForName, col, name);
                            string typname = GetStringFromCell(sheet, cst_RowForType, col, name);

                            if (colname.Equals("") || typname.Equals(""))
                                continue;

                            if(typname.Equals("int"))
						        W2F(3, writer, "conf." + colname + " = csv.get_i32(row,index_" + colname + ");");
					        else if(typname.Equals("long"))
                                W2F(3, writer, "conf." + colname + " = csv.get_i64(row,index_" + colname + ");");
					        else if(typname.Equals("float"))
                                W2F(3, writer, "conf." + colname + " = (float)csv.get_dec(row,index_" + colname + ");");
					        else if(typname.Equals("double"))
                                W2F(3, writer, "conf." + colname + " = csv.get_dec(row,index_" + colname + ");");
					        else if(typname.Equals("string"))
                                W2F(3, writer, "conf." + colname + " = csv.get_str(row,index_" + colname + ");");
					        else if(typname.Equals("bool"))
                                W2F(3, writer, "conf." + colname + " = csv.get_bool(row,index_" + colname + ");");
                            /*else if(typname.Equals("string[]"))
					        {
						        W2F(3, writer, "{");
							        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
							        W2F(4, writer, "tokenize(__tmp,conf." + colname + ",\",\",\"\",\"\\\"\");;");
						        W2F(3, writer, "}");
					        }
                            else if(typname.Equals("float[]"))
					        {
						        W2F(3, writer, "{");
							        W2F(4, writer, "std::vector<std::string> vals;");
							        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
							        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
							        W2F(4, writer, "for(size_t i = 0; i < vals.size(); ++i)");
								        W2F(5, writer, "conf." + colname + ".push_back(pwutils::atof(vals[i].c_str()));");
						        W2F(3, writer, "}");
					        }
                            else if(typname.Equals("int[]"))
					        {
						        W2F(3, writer, "{");
						            W2F(4, writer, "std::vector<std::string> vals;");
                                    W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
							        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
							        W2F(4, writer, "for(size_t i = 0; i < vals.size(); ++i)");
							            W2F(5, writer, "conf." + colname + ".push_back(pwutils::atoi(vals[i].c_str()));");
							    W2F(3, writer, "}");
					        }*/
                            else if(typname.Contains("string["))
                            {
                                if (typname.Equals("string[]"))
                                {
                                    W2F(3, writer, "{");
                                        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
                                        W2F(4, writer, "tokenize(__tmp,conf." + colname + ",\",\",\"\",\"\\\"\");;");
                                    W2F(3, writer, "}");
                                }
                                else if (typname.Substring(typname.Length - 1, 1).Equals("]"))
                                {
                                    int val = int.Parse(typname.Substring(7, typname.Length - 8));

                                    W2F(3, writer, "{");
                                        W2F(4, writer, "std::vector<std::string> vals;");
                                        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
                                        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
                                        W2F(4, writer, "pwassertn(vals.size() == " + val + "|| vals.empty()" + ");");
                                        W2F(4, writer, "for(size_t i = 0; i < " + val + "; ++i)");
                                            W2F(5, writer, "conf." + colname + "[i] = vals.empty() ? \"\" : vals[i];");
                                    W2F(3, writer, "}");
                                }
                            }
                            else if (typname.Contains("float["))
                            {
                                if (typname.Equals("float[]"))
                                {
                                    W2F(3, writer, "{");
                                        W2F(4, writer, "std::vector<std::string> vals;");
                                        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
                                        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
                                        W2F(4, writer, "for(size_t i = 0; i < vals.size(); ++i)");
                                            W2F(5, writer, "conf." + colname + ".push_back(pwutils::atof(vals[i].c_str()));");
                                    W2F(3, writer, "}");
                                }
                                else if (typname.Substring(typname.Length - 1, 1).Equals("]"))
                                {
                                    int val = int.Parse(typname.Substring(6, typname.Length - 7));

                                    W2F(3, writer, "{");
                                        W2F(4, writer, "std::vector<std::string> vals;");
                                        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
                                        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
                                        W2F(4, writer, "pwassertn(vals.size() == " + val + "|| vals.empty()" + ");");
                                        W2F(4, writer, "for(size_t i = 0; i < " + val + "; ++i)");
                                            W2F(5, writer, "conf." + colname + "[i] = vals.empty() ? 0.0 : pwutils::atof(vals[i].c_str());");
                                    W2F(3, writer, "}");
                                }   
                            }
                            else if (typname.Contains("int["))
                            {
                                if (typname.Equals("int[]"))
                                {
                                    W2F(3, writer, "{");
                                        W2F(4, writer, "std::vector<std::string> vals;");
                                        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
                                        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
                                        W2F(4, writer, "for(size_t i = 0; i < vals.size(); ++i)");
                                            W2F(5, writer, "conf." + colname + ".push_back(pwutils::atoi(vals[i].c_str()));");
                                    W2F(3, writer, "}");
                                }
                                else if (typname.Substring(typname.Length - 1, 1).Equals("]"))
                                {
                                    int val = int.Parse(typname.Substring(4, typname.Length - 5));
                                    
                                    W2F(3, writer, "{");
                                        W2F(4, writer, "std::vector<std::string> vals;");
                                        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
                                        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
                                        W2F(4, writer, "pwassertn(vals.size() == " + val + "|| vals.empty()" + ");");
                                        W2F(4, writer, "for(size_t i = 0; i < " + val + "; ++i)");
                                            W2F(5, writer, "conf." + colname + "[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());");
                                    W2F(3, writer, "}");
                                }
                            }
                            else if (typname.Contains("long["))
                            {
                                if (typname.Equals("long[]"))
                                {
                                    W2F(3, writer, "{");
                                        W2F(4, writer, "std::vector<std::string> vals;");
                                        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
                                        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
                                        W2F(4, writer, "for(size_t i = 0; i < vals.size(); ++i)");
                                            W2F(5, writer, "conf." + colname + ".push_back(pwutils::atoi(vals[i].c_str()));");
                                    W2F(3, writer, "}");
                                }
                                else if (typname.Substring(typname.Length - 1, 1).Equals("]"))
                                {
                                    int val = int.Parse(typname.Substring(5, typname.Length - 6));

                                    W2F(3, writer, "{");
                                        W2F(4, writer, "std::vector<std::string> vals;");
                                        W2F(4, writer, "const char* __tmp = csv.get_str(row,index_" + colname + ");");
                                        W2F(4, writer, "tokenize(__tmp,vals,\",\",\"\",\"\\\"\");;");
                                        W2F(4, writer, "pwassertn(vals.size() == " + val + "|| vals.empty()" + ");");
                                        W2F(4, writer, "for(size_t i = 0; i < " + val + "; ++i)");
                                            W2F(5, writer, "conf." + colname + "[i] = vals.empty() ? 0 : pwutils::atoi(vals[i].c_str());");
                                    W2F(3, writer, "}");
                                }
                            }
                        }
                        W2F(3, writer, "m_vtConfigures.push_back(conf);");
                    W2F(2, writer, "}");
			        W2F(2, writer, "return true;");
                W2F(1, writer, "}");

		        W2F(1, writer, "");
		        // Get
		        W2F(1, writer, structname + "& " + classname + "::Get(size_t row)");
		        W2F(1, writer, "{");
			        W2F(2, writer, "return m_vtConfigures.at(row);");
		        W2F(1, writer, "}");
            W2F(0, writer, "}");
            
            writer.Close();
            stream.Close();

        }

        void GenerateCsvHeader(Sheet sheet, StreamWriter writer, string name)
        {
            int cols = sheet.getColumns();
            int rows = sheet.getRows();

            for (int i = 0; i < cst_RowForData; ++i)
            {
                string line = "";

                for (int j = 0; j < cols; j++)
                {
                    line = line + "\"" + GetStringFromCell(sheet,i,j,name) + "\"\t";
                }

                line = line + "\n";
                writer.Write(line);
            }
        }

        void GenerateCsv(Sheet sheet, StreamWriter writer, string name)
        {
            int cols = sheet.getColumns();
            int rows = sheet.getRows();

            for (int i = cst_RowForData; i < rows; ++i)
            {
                string line = "";
                bool allempty = true;
                string firstcell = "";

                for (int j = 0; j < cols; ++j)
                {
                    string str = GetStringFromCell(sheet, i, j, name);

                    if(j == 0)
                    {
                        firstcell = str;

                        // 每行第一个元素以#开头，忽略本行
                        if (firstcell.StartsWith("#"))
                        {
                            allempty = true;
                            break;
                        }
                    }

                    if (str != "")
                        allempty = false;

                    line = line + "\"" + str + "\"\t";
                }

                if (!allempty)
                {
                    if (firstcell.Equals(""))
                    {
                        ShowMessage(name, sheet.getName(), i, 0, "first col can't be empty");
                    }
                    else
                    {
                        line = line + "\n";
                        writer.Write(line);
                    }
                }
                   
            }
        }

        private void versionbox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_nSelectIdx = versionbox.SelectedIndex;
        }

        int SelectVersion()
        {
            string srcPath = System.IO.Directory.GetCurrentDirectory();
            string dstPath = srcPath + "\\";

            switch (m_nSelectIdx)
            {
                case 0:
                    {
                        // 中文目录
                        srcPath = srcPath + "\\CN\\";
                    }
                    break;
                case 1:
                    {
                        // 韩文目录
                        srcPath = srcPath + "\\KOR\\";
                    }
                    break;
                case 2:
                    {
                        // 日文目录
                        srcPath = srcPath + "\\JP\\";
                    }
                    break;
                case 3:
                    {
                        // QQ目录
                        srcPath = srcPath + "\\QQ\\";
                    }
                    break;
                default:
                    {
                        return -1;
                    }
            }

            int result = CopyVersionFiles(srcPath, dstPath);
            if (result != 0)
                return -1;

            return 0;
        }

        int CopyVersionFiles(string srcPath,string dstPaht)
        {
            if (!Directory.Exists(srcPath))
            {
                MessageBox.Show("Invalid Directory : " + srcPath);
                return -1;
            }

             if (!Directory.Exists(dstPaht))
            {
                MessageBox.Show("Invalid Directory : " + dstPaht);
                return -1;
            }

            foreach (string file in Directory.GetFiles(srcPath))
            {
                if (Path.GetExtension(file).ToLower() != ".xls")
                    continue;

                File.Copy(file, dstPaht + Path.GetFileName(file), true);
            }

            return 0;
        }

        private void gen_csv_Load(object sender, EventArgs e)
        {

        }
    }
}
