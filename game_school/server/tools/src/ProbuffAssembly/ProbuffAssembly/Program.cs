using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace ProbuffAssembly
{
            
    class Program
    {
        static void Main(string[] args)
        {
            string[] strFiles;
            string outFile;
/*
            if (args.Length == 1)
            {
                strPath = args[0];
                strFiles = Directory.GetFiles(strPath, "*.proto");
                outFile = "worldsrv.proto";
            }

            else
            {*/
            if (args.Length != 1)
                return;

            if(args[0].Length < 8)
            {
                string strPath = args[0];
                strFiles = Directory.GetFiles(strPath, "*.proto");
                outFile = "worldsrv.proto";

                FileStream stream = new FileStream(outFile, FileMode.Create);
                StreamWriter writer = new StreamWriter(stream, Encoding.Default);

                writer.WriteLine("import \"options.proto\";");
                // writer.WriteLine("package com.pwrd.game.accsrv;");
                // writer.WriteLine("package pwngs.protocol.worldsrv;");
               // writer.WriteLine("package " + "pwngs.protocol.worldsrv" + ";");
                


                for (int i = 0; i < strFiles.Length; i++)
                {
                    string file = strFiles[i];

                    StreamReader strReadFile = new StreamReader(file, Encoding.Default);
                    
                    while (!strReadFile.EndOfStream)
                    {
                        string strReadLine = strReadFile.ReadLine();

                        writer.WriteLine(strReadLine);
                    }
                    strReadFile.Close();

                }

                writer.Close();
                stream.Close();


            }
            else
            {
                strFiles = args;
                outFile = "process_proto/" + strFiles[0].Substring(8);

                Array.Sort(strFiles);

                File.Delete(outFile);

                FileStream stream = new FileStream(outFile, FileMode.CreateNew);
                StreamWriter writer = new StreamWriter(stream, Encoding.Default);

                writer.WriteLine("import \"pwngs/options.proto\";");
                writer.WriteLine("import \"pwngs/protocol/worldsrv/00000_00000_def.proto\";");
                writer.WriteLine("package pwngs.protocol.worldsrv;");
                //writer.WriteLine("import \"..\\proto\\00000_00000_def.proto\";");
                // writer.WriteLine("package com.pwrd.game.accsrv;");
                // writer.WriteLine("package pwngs.protocol.worldsrv;");
                //writer.WriteLine("package " + args[1] + ";");

                writer.WriteLine("");

                for (int i = 0; i < strFiles.Length; i++)
                {
                    string file = strFiles[i];

                    StreamReader strReadFile = new StreamReader(file, Encoding.Default);

                    writer.WriteLine("// -------------------------------------------------------");
                    writer.WriteLine("// auto generate by ProbufAssembly");
                    writer.WriteLine("// " + file);
                    writer.WriteLine("// -------------------------------------------------------");

                    while (!strReadFile.EndOfStream)
                    {
                        string strReadLine = strReadFile.ReadLine();

                        writer.WriteLine(strReadLine);
                    }
                    strReadFile.Close();

                }

                writer.Close();
                stream.Close();

            }
           }
            
        }
}

