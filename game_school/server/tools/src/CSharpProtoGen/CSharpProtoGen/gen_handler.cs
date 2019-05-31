using System;
using System.Collections;
using System.Collections.Generic;
using Google.ProtocolBuffers;
using Google.ProtocolBuffers.Collections;
using Google.ProtocolBuffers.DescriptorProtos;

namespace CSharpProtoGen{
	public static class GenHandler{
		public static void GenerateMsgHandlerCpp(List<string> list, FileDescriptorProto fdp)
		{
			string tab1 = MainClass.GenTab(1);
			string tab2 = MainClass.GenTab(2);
			string tab3 = MainClass.GenTab(3);
			string tab4 = MainClass.GenTab(4);
            list.Add("using UnityEngine;");
			list.Add("using System;");
			list.Add("using System.Collections;");
			list.Add("using System.IO;");
			list.Add("using Google.ProtocolBuffers;");
			list.Add("using Google.ProtocolBuffers.Collections;");
			list.Add("using Google.ProtocolBuffers.DescriptorProtos;");
			//list.Add("namespace pwngs.msg{");
			list.Add("public static class MsgHandler{");

			//function process
			list.Add(tab1 + "public static int Process(int msgid,byte[] buf){");
			list.Add(tab2 + "switch(msgid)");
			list.Add(tab2 + "{");
			for(int i=0; i<fdp.MessageTypeCount; i++)
			{
				DescriptorProto proto = fdp.GetMessageType(i);
				int msgid = proto.Options.GetExtension(pwngs.Options.Msgid);
                if (msgid == 0)
                {
                    continue;
                }
                else if (string.Equals(proto.Name.Substring(0, 2), "CS"))
                {
                    continue;
                }
                else
                {
                    list.Add(tab2 + "case MsgDef.msgid_" + proto.Name + ":");
                    list.Add(tab3 + "CodedInputStream stream" + proto.Name + " = Parse(buf,buf.Length);");
                    list.Add(tab3 + proto.Name + " act" + proto.Name + " = " + proto.Name + ".ParseFrom(stream" + proto.Name + ");");
                    list.Add(tab3 + "return " + proto.Name + "Handler.Process(act" + proto.Name + ");");
                }
			}
			list.Add(tab2 + "default:");
			list.Add(tab3 + "break;");
			list.Add(tab2 + "}");
			list.Add(tab1 + "return 0;");
			list.Add(tab1 + "}");

			//function parse
			list.Add(tab1 + "public static CodedInputStream Parse(byte[] buf, int length){");
			list.Add(tab2 + "System.IO.MemoryStream stream = new System.IO.MemoryStream(length);");
			list.Add(tab2 + "stream.Write(buf,0,length);");
			list.Add(tab2 + "stream.Seek(0,SeekOrigin.Begin);");
			list.Add(tab2 + "CodedInputStream stream1 = CodedInputStream.CreateInstance(stream);");
			list.Add(tab2 + "return stream1;");
			list.Add(tab1 + "}");
			
            //function SendMessage
            list.Add(tab1 + "public static void Send(byte[] msgArray, Int32 msgLength, Int32 msgID){");
            list.Add(tab2 + "byte[] newMsgArray = new byte[msgLength];");
            list.Add(tab2 + "Int32 newMsgLength = System.Net.IPAddress.HostToNetworkOrder(msgLength);");
            list.Add(tab2 + "Int32 newMsgID = System.Net.IPAddress.HostToNetworkOrder(msgID);");
            list.Add(tab2 + "BitConverter.GetBytes(newMsgLength).CopyTo(newMsgArray,0);");
            list.Add(tab2 + "BitConverter.GetBytes(newMsgID).CopyTo(newMsgArray,4);");
            list.Add(tab2 + "msgArray.CopyTo(newMsgArray,8);");
            list.Add(tab2 + "OutputMsgQueue.WriteMsg(newMsgArray);");
            list.Add(tab2 + "Debug.Log(\"Put Message InputQueue ID:\" + msgID);");
            list.Add(tab1 + "}");
           
			//list.Add(tab1 + "}");
			list.Add("}");
			
			
		}
	}
}
