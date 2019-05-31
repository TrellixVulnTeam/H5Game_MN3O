using System;
using System.Collections;
using System.Collections.Generic;
using Google.ProtocolBuffers;
using Google.ProtocolBuffers.Collections;
using Google.ProtocolBuffers.DescriptorProtos;

namespace CSharpProtoGen{
	public static class GenMsgHandler{
		public static void GenerateMsgProcess(List<MsgHandler> list, FileDescriptorProto fdp)
		{
			string tab1 = MainClass.GenTab(1);
			string tab2 = MainClass.GenTab(2);
			string tab3 = MainClass.GenTab(3);
			string tab4 = MainClass.GenTab(4);
			
			for(int i=0; i<fdp.MessageTypeCount; i++)
			{
				DescriptorProto proto = fdp.GetMessageType(i);
				int msgid = proto.Options.GetExtension(pwngs.Options.Msgid);
                if (msgid == 0)
                {
                    MsgHandler msgHandler = new MsgHandler();
                    msgHandler.name = proto.Name;
                    msgHandler.lines = new List<string>();
                    msgHandler.lines.Add("using UnityEngine;");
                    msgHandler.lines.Add("using System;");
                    msgHandler.lines.Add("using System.Collections;");
                    msgHandler.lines.Add("using System.IO;");
                    msgHandler.lines.Add("using Google.ProtocolBuffers;");
                    msgHandler.lines.Add("using Google.ProtocolBuffers.Collections;");
                    msgHandler.lines.Add("using Google.ProtocolBuffers.DescriptorProtos;");
                    //msgHandler.lines.Add("using pwngs.protobuf;");
                    //msgHandler.lines.Add("namespace pwngs.msg{");
                    msgHandler.lines.Add("public static class " + proto.Name + "Handler{");
                    
                    msgHandler.lines.Add(tab1 + "public static " + proto.Name + " Create(){");
                    msgHandler.lines.Add(tab2 + proto.Name + " actMsg = new " + proto.Name + "();");
                    msgHandler.lines.Add(tab2 + "return actMsg;");
                    msgHandler.lines.Add(tab1 + "}");
                    
                    msgHandler.lines.Add("}");
                    //msgHandler.lines.Add("}");

                    list.Add(msgHandler);
                }
                else
                {
                    MsgHandler msgHandler = new MsgHandler();
                    msgHandler.name = proto.Name;
                    msgHandler.lines = new List<string>();
                    msgHandler.lines.Add("using UnityEngine;");
                    msgHandler.lines.Add("using System;");
                    msgHandler.lines.Add("using System.Collections;");
                    msgHandler.lines.Add("using System.IO;");
                    msgHandler.lines.Add("using Google.ProtocolBuffers;");
                    msgHandler.lines.Add("using Google.ProtocolBuffers.Collections;");
                    msgHandler.lines.Add("using Google.ProtocolBuffers.DescriptorProtos;");
                    //msgHandler.lines.Add("using pwngs.protobuf;");
                    //msgHandler.lines.Add("namespace pwngs.msg{");
                    msgHandler.lines.Add("public static class " + proto.Name + "Handler{");
                    if (string.Equals(proto.Name.Substring(0,2),"SC"))
                    {
                        msgHandler.lines.Add(tab1 + "public static int Process(" + proto.Name + " actMsg){");
                        msgHandler.lines.Add(tab2 + "return 0;");
                        msgHandler.lines.Add(tab1 + "}");
                    }
                    else if (string.Equals(proto.Name.Substring(0, 2), "CS"))
                    {
                        msgHandler.lines.Add(tab1 + "public static " + proto.Name + " Create(){");
                        msgHandler.lines.Add(tab2 + proto.Name + " actMsg = new " + proto.Name +"();");
                        msgHandler.lines.Add(tab2 + "return actMsg;");
                        msgHandler.lines.Add(tab1 + "}");
                    }
                    msgHandler.lines.Add("}");
                    //msgHandler.lines.Add("}");

                    list.Add(msgHandler);
                }
			}
		}
	}
}
