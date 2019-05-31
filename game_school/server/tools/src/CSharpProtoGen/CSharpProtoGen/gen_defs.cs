using System;
using System.Collections;
using System.Collections.Generic;
using Google.ProtocolBuffers;
using Google.ProtocolBuffers.Collections;
using Google.ProtocolBuffers.DescriptorProtos;

namespace CSharpProtoGen{
	public static class GenDefs{
		public static void GenerateMsgDef(List<string> defs,FileDescriptorProto fdp)
		{
			string tab1 = MainClass.GenTab(1);
			string tab2 = MainClass.GenTab(2);
            defs.Add("using UnityEngine;");
			defs.Add("using System;");
			defs.Add("using System.Collections;");
			//defs.Add("namespace pwngs.msg{");
			defs.Add("public static class MsgDef{");
			for(int i=0; i<fdp.MessageTypeCount; i++)
			{
				DescriptorProto proto = fdp.GetMessageType(i);
				int msgid = proto.Options.GetExtension(pwngs.Options.Msgid);
                if (msgid == 0)
                {
                    continue;
                }
                else
                {
                    defs.Add(tab1 + "public const int msgid_" + proto.Name + "=" + msgid + ";");
                }
				
			}
			defs.Add("}");
			//defs.Add("}");
		}
	}
}