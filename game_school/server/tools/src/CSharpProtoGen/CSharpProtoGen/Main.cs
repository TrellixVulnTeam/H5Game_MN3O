using System;
using System.IO;
using System.Text;
using System.Collections;
using System.Collections.Generic;
using Google.ProtocolBuffers;
using Google.ProtocolBuffers.DescriptorProtos;
using Google.ProtocolBuffers.Collections;

namespace CSharpProtoGen
{
	class MainClass
	{
		public static int WriteToFile(List<string> list,string filename)
		{
			Stream outStream = File.OpenWrite(filename);
			if ( outStream == null)
			{
				Console.WriteLine("Open file:{1} failed!",filename);
				return 1;
			}
			for(int i=0; i<list.Count;i++)
			{
				byte[] bytebuf = Encoding.ASCII.GetBytes(list[i]);
				byte[] enter = Encoding.ASCII.GetBytes("\n");
				outStream.Write(bytebuf,0,bytebuf.Length);
				outStream.Write(enter,0,enter.Length);
			}
			outStream.Close();
			return 0;
		}
		public static string GenTab(int n)
		{
			string result = "";
			for(int i=0; i<n; i++)
			{
				result += "\t";
			}
			return result;
		}
	
		public static void Main (string[] args)
		{
			
			ExtensionRegistry extensionRegistry = ExtensionRegistry.CreateInstance();
			extensionRegistry.Add(CSharpOptions.CSharpFieldOptions);
			extensionRegistry.Add(CSharpOptions.CSharpFileOptions);
			extensionRegistry.Add(pwngs.Options.Msgid);
			//Stream inputStream = File.OpenRead("../../msg.protobin");
			Stream inputStream = File.OpenRead(args[0]);
			string path = args[1];
			
			FileDescriptorSet fds = FileDescriptorSet.ParseFrom(inputStream,extensionRegistry);
			FileDescriptorProto fdp = fds.GetFile(2);
			
			//generate msg.def.cs
			List<string> def = new List<string>();
			GenDefs.GenerateMsgDef(def,fdp);
			WriteToFile(def,path + "msg.def.cs");
			
			//generate msg.handler.cs
			List<string> handler = new List<string>();
			GenHandler.GenerateMsgHandlerCpp(handler,fdp);
			WriteToFile(handler,path + "msg.handler.cs");
			
			//generate msg.handler.MSG.cs
			List<MsgHandler> msghandler = new List<MsgHandler>();
			GenMsgHandler.GenerateMsgProcess(msghandler,fdp);
			for (int i=0; i<msghandler.Count; i++)
			{
				string filename = path + "msg.handler." + msghandler[i].name + ".cs";
				if(!File.Exists(filename))
				{
					WriteToFile(msghandler[i].lines,filename);
				}
			}
			inputStream.Close();
		}
	}
	public class MsgHandler{
		public string name;
		public List<string> lines;
	}

}

