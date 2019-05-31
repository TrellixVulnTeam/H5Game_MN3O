using System;
using System.Xml;
using System.Windows.Forms;
using System.Text;
using System.Collections.Generic;
using System.IO;

namespace TreeViewSerialization
{

	/// <summary>
	/// Summary description for TreeViewSerializer.
	/// </summary>
	public class TreeViewSerializer
	{

        // Xml tag for node, e.g. 'node' in case of <node></node>
        public const string XmlRootTag = "root";
        public const string XmlDungeonTag = "dungeon";
        public const string XmlNodeTag = "node";

        // Xml attributes for node e.g. <node text="Asia" tag="" imageindex="1"></node>
        public const string XmlNodeTextAtt = "text";
        public const string XmlNodeNameAtt = "name";
        public const string XmlNodeIdAtt = "id";
        public const string XmlNodeTypeAtt = "type";
        public const string XmlNodeTypeidAtt = "typeid";
        public const string XmlNodeChilds = "childs";
        public const string XmlNodeParam1 = "param1";
        public const string XmlNodeParam2 = "param2";
        public const string XmlNodeParam3 = "param3";
        public const string XmlNodeParam4 = "param4";
        public const string XmlNodeParam5 = "param5";
        public const string XmlNodeParam6 = "param6";
        public const string XmlNodeParam7 = "param7";
        public const string XmlNodeParam8 = "param8";


        public const string ConfigNodeTextAtt = "text";
        public const string ConfigNodeNameAtt = "name";
        public const string ConfigNodeTypeAtt = "type";
        public const string ConfigNodeTypeidAtt = "typeid";
        public const string ConfigNodeParam1 = "tbParam1";
        public const string ConfigNodeParam2 = "tbParam2";
        public const string ConfigNodeParam3 = "tbParam3";
        public const string ConfigNodeParam4 = "tbParam4";
        public const string ConfigNodeParam5 = "tbParam5";
        public const string ConfigNodeParam6 = "tbParam6";
        public const string ConfigNodeParam7 = "tbParam7";
        public const string ConfigNodeParam8 = "tbParam8";
        public const string ConfigNodeContent = "content";
        public const string ConfigNodeCount = "count";


		public TreeViewSerializer()
		{
			//
			// TODO: Add constructor logic here
			//
		}

		//System.IO.StringWriter s;
		public void SerializeXml(TreeView treeView, string fileName) 
		{
			XmlTextWriter textWriter = new XmlTextWriter(fileName, System.Text.Encoding.UTF8);
			// writing the xml declaration tag
			textWriter.WriteStartDocument();
			//textWriter.WriteRaw("\r\n");
			// writing the main tag that encloses all node tags
            textWriter.WriteStartElement("root");
			
			// save the nodes, recursive method
			SaveNodes(treeView.Nodes, textWriter);
			
			textWriter.WriteEndElement();
					
			textWriter.Close();
		}

        public void SerializeLua(TreeView treeView, string fileName, Dictionary<Int32, Dictionary<Int32, ControlConfig>> dicControlConfig)
        {
            FileStream fs = new FileStream(fileName, FileMode.Create);
            StreamWriter sw = new StreamWriter(fs);

            sw.WriteLine("CurrentDungeonScript = {}");
            sw.WriteLine("CurrentDungeonScript.Vars = {}");
            sw.WriteLine("CurrentDungeonScript.Humans = {} -- k = id,v = Human*");
            sw.WriteLine("CurrentDungeonScript.MainHuman = nil -- nil or Human*");
            sw.WriteLine("CurrentDungeonScript.Stage = nil -- nil or Stage* .");
            sw.WriteLine("\n");
            sw.WriteLine("----------------------------------------------------------------------");
            sw.WriteLine("\n");

            SaveLua(treeView.Nodes, sw, dicControlConfig);

            sw.WriteLine("function CurrentDungeonScript:Cleanup()");
            sw.WriteLine("end");

            sw.Flush();
            sw.Close();
            fs.Close();
        }

        private void SaveLua(TreeNodeCollection nodesCollection, StreamWriter sw, Dictionary<Int32, Dictionary<Int32, ControlConfig>> dicControlConfig)
        {
            for (int i = 0; i < nodesCollection.Count; i++)
            {
                TreeNode node = nodesCollection[i];
                NodeInfo info = (NodeInfo)node.Tag;
                if (info.type == (Int32)NodeType.TypeEvent)
                {
                    GenerateCode(info, sw, dicControlConfig);

                    if (info.childs.Count > 0)
                    {
                        foreach (Int32 index in info.childs)
                        {
                            TreeNode child = FindChild(node, index);
                            if (child != null && child.Tag != null)
                            {
                                GenerateCode((NodeInfo)child.Tag, sw, dicControlConfig);
                            }
                        }
                    }
                    sw.WriteLine("end");
                    sw.WriteLine("\n");
                }

                SaveLua(node.Nodes, sw, dicControlConfig);
            }
            
        }

        private void GenerateCode(NodeInfo info, StreamWriter sw, Dictionary<Int32, Dictionary<Int32, ControlConfig>> dicControlConfig)
        {
            StringBuilder builder = new StringBuilder();

            ControlConfig dic;
            bool ret = dicControlConfig[info.type].TryGetValue(info.typeid, out dic);

            switch (dic.count)
            {
                case 0:
                    sw.WriteLine(dic.content, dic.name);
                    break;
                case 1:
                    sw.WriteLine(dic.content, dic.name, info.param1);
                    break;
                case 2:
                    sw.WriteLine(dic.content, dic.name, info.param1, info.param2);
                    break;
                case 3:
                    sw.WriteLine(dic.content, dic.name, info.param1, info.param2, info.param3);
                    break;
                case 4:
                    sw.WriteLine(dic.content, dic.name, info.param1, info.param2, info.param3, info.param4);
                    break;
                case 5:
                    sw.WriteLine(dic.content, dic.name, info.param1, info.param2, info.param3, info.param4, info.param5);
                    break;
                case 6:
                    sw.WriteLine(dic.content, dic.name, info.param1, info.param2, info.param3, info.param4, info.param5, info.param6);
                    break;
                case 7:
                    sw.WriteLine(dic.content, dic.name, info.param1, info.param2, info.param3, info.param4, info.param5, info.param6, info.param7);
                    break;
                
            }
            
            
            /*
            if ((NodeType)info.type == NodeType.TypeEvent)
                        {
                            switch ((EventType)info.typeid)
                            {
                                case EventType.Startup:
                                    {
                                        sw.WriteLine("function CurrentDungeonScript:Startup()");
                                    }
                                    break;
                                case EventType.EventCreateProcess:
                                    {
                                        sw.WriteLine("function CurrentDungeonScript:EventCreateProcess()");
                                    }
                                    break;
                                case EventType.TimeEvent:
                                    {
                                        builder.AppendFormat("function CurrentDungeonScript:{0}()", info.name);
                                        sw.WriteLine(builder.ToString());
                                    }
                                    break;
                            }
            
                        }
                        else if ((NodeType)info.type == NodeType.TypeAction)
                        {
                            switch ((ActionType)info.typeid)
                            {
                                case ActionType.SetEventHandler:
                                    {
                                        builder.AppendFormat("  {0}({1},\"{2}\")", info.name, info.param1, info.param2);
                                        sw.WriteLine(builder.ToString());
                                    }
                                    break;
                                case ActionType.CreateTimer:
                                    {
                                        builder.AppendFormat("  self.SModDungeonScript:CreateTimer({0}, {1})", info.param1, info.param2);
                                        sw.WriteLine(builder.ToString());
                                    }
                                    break;
                            }
                        }
                        else if ((NodeType)info.type == NodeType.TypeCondtion)
                        {
            
                        }*/
            

            if (info.param8 != null)
            {

                string[] strs = info.param8.Split('\r', '\n');
                foreach (string str in strs)
                {
                    sw.WriteLine(str);
                }
            }
        }

        private TreeNode FindChild(TreeNode nodes, Int32 id)
        {


            for (int i = 0; i < nodes.Nodes.Count; i++)
            {
                TreeNode node = nodes.Nodes[i];
                if (node.Tag != null)
                {
                    NodeInfo info = (NodeInfo)node.Tag;
                    if (info.id == id)
                    {
                        return node;
                    }
                }
            }

            return null;
        }

		private void SaveNodes(TreeNodeCollection nodesCollection, 
			XmlTextWriter textWriter)
		{
			
			for(int i = 0; i < nodesCollection.Count; i++)
			{
				TreeNode node = nodesCollection[i];
				textWriter.WriteStartElement(XmlNodeTag);
				textWriter.WriteAttributeString(XmlNodeTextAtt, node.Text);
                if (node.Tag != null)
                {
                    NodeInfo info = (NodeInfo)node.Tag;
                    if (info.name != null)
                        textWriter.WriteAttributeString(XmlNodeNameAtt, info.name.ToString());
                    
                    textWriter.WriteAttributeString(XmlNodeIdAtt, info.id.ToString());
                    textWriter.WriteAttributeString(XmlNodeTypeAtt, info.type.ToString());
                    textWriter.WriteAttributeString(XmlNodeTypeidAtt, info.typeid.ToString());
                    
                    if (info.childs != null)
                    {
                        StringBuilder builder = new StringBuilder();
                        foreach (Int32 index in info.childs)
                        {
                            builder.AppendFormat("{0},", index);
                        }

                        textWriter.WriteAttributeString(XmlNodeChilds, builder.ToString());
                    }
                  
                    if (info.param1 != null)
                        textWriter.WriteAttributeString(XmlNodeParam1, info.param1.ToString());
                    if (info.param2 != null)
                        textWriter.WriteAttributeString(XmlNodeParam2, info.param2.ToString());
                    if (info.param3 != null)
                        textWriter.WriteAttributeString(XmlNodeParam3, info.param3.ToString());
                    if (info.param4 != null)
                        textWriter.WriteAttributeString(XmlNodeParam4, info.param4.ToString());
                    if (info.param5 != null)
                        textWriter.WriteAttributeString(XmlNodeParam5, info.param5.ToString());
                    if (info.param6 != null)
                        textWriter.WriteAttributeString(XmlNodeParam6, info.param6.ToString());
                    if (info.param7 != null)
                        textWriter.WriteAttributeString(XmlNodeParam7, info.param7.ToString());
                    if (info.param8 != null)
                        textWriter.WriteAttributeString(XmlNodeParam8, info.param8.ToString());
                    
                }   
				
				// add other node properties to serialize here
				
				if (node.Nodes.Count > 0)
				{
					
					SaveNodes(node.Nodes, textWriter);
					    
				} 				
				textWriter.WriteEndElement();
			}
			
		}


        public void LoadXmlConfig(Dictionary<Int32, Dictionary<Int32, ControlConfig>> dicControlConfig, string fileName)
        {
            XmlTextReader reader = null;
            Dictionary<Int32, ControlConfig> dicActionConfig = new Dictionary<int, ControlConfig>();
            Dictionary<Int32, ControlConfig> dicEventConfig = new Dictionary<int, ControlConfig>();
            Dictionary<Int32, ControlConfig> dicConditionConfig = new Dictionary<int, ControlConfig>();
            try
            {
                reader =
                    new XmlTextReader(fileName);
                while (reader.Read())
                {
                    if (reader.NodeType == XmlNodeType.Element && reader.Name == XmlNodeTag)
                    {
                        int attributeCount = reader.AttributeCount;
                        if (attributeCount > 0)
                        {
                            ControlConfig info = new ControlConfig();
                            for (int i = 0; i < attributeCount; i++)
                            {
                                reader.MoveToAttribute(i);
                               
                                SetControlConfig(reader.Name, reader.Value, info);

                            }

                            if (info.type == (Int32)NodeType.TypeEvent)
                            {
                                dicEventConfig.Add(info.typeid, info);
                            }
                            else if (info.type == (Int32)NodeType.TypeAction)
                            {
                                dicActionConfig.Add(info.typeid, info);
                            }
                            else if (info.type == (Int32)NodeType.TypeCondtion)
                            {
                                dicConditionConfig.Add(info.typeid, info);
                            }
                        }
                    }

                }

                dicControlConfig.Add((Int32)NodeType.TypeEvent, dicEventConfig);
                dicControlConfig.Add((Int32)NodeType.TypeAction, dicActionConfig);
                dicControlConfig.Add((Int32)NodeType.TypeCondtion, dicConditionConfig);
            }
            finally
            {
                reader.Close();
            }
        }

		public void LoadXmlTreeView(TreeView treeView, string fileName)
		{
			XmlTextReader reader = null;
			try
			{
                // disabling re-drawing of treeview till all nodes are added
				treeView.BeginUpdate();				
				reader =
					new XmlTextReader(fileName);

				TreeNode parentNode = null;

/*
                MLTree<NodeInfo> tr = new MLTree<NodeInfo>();
                MLNode<NodeInfo> mNode1 = new MLNode<NodeInfo>(20);
                MLNode<NodeInfo> mNode2 = new MLNode<NodeInfo>(20);

                //构建根节点
                TreeNode rootNode = new TreeNode();
                NodeInfo rootInfo = new NodeInfo();
                rootInfo.name = "root";

                if (parentNode != null)
                    parentNode.Nodes.Add(rootNode);
                else
                    treeView.Nodes.Add(rootNode);

                mNode1.Data = rootInfo;
                tr.Head = mNode1;
                MLNode<NodeInfo>[] mArray = null;*/

/*
                //构建根节点
                NodeInfo rootInfo = new NodeInfo();
                rootInfo.name = "root";
                rootInfo.id = 0;
                STreeNode node = new STreeNode(rootInfo);
                STree tree = new STree();
                tree.Nodes.Add(node);*/

				while (reader.Read())
				{
					if (reader.NodeType == XmlNodeType.Element)
					{
	                    
						if (reader.Name == XmlNodeTag || reader.Name == XmlDungeonTag)
						{
							TreeNode newNode = new TreeNode();
                            
							bool isEmptyElement = reader.IsEmptyElement;

                            // loading node attributes
							int attributeCount = reader.AttributeCount;
							if (attributeCount > 0)
							{
                                NodeInfo info = new NodeInfo();
								for (int i = 0; i < attributeCount; i++)
								{
									reader.MoveToAttribute(i);
									
									SetAttributeValue(newNode, reader.Name, reader.Value, info);
                                    
                                    
								}
                                newNode.Tag = info;

							}


                            // add new node to Parent Node or TreeView
                            if(parentNode != null)
                                parentNode.Nodes.Add(newNode);
                            else
                                treeView.Nodes.Add(newNode);

                            // making current node 'ParentNode' if its not empty
							if (!isEmptyElement)
							{
                                parentNode = newNode;
							}
														
						}						                    
					}
                    // moving up to in TreeView if end tag is encountered
					else if (reader.NodeType == XmlNodeType.EndElement)
					{
						if (reader.Name == XmlNodeTag)
						{
							parentNode = parentNode.Parent;
						}
					}
					else if (reader.NodeType == XmlNodeType.XmlDeclaration)
					{ //Ignore Xml Declaration                    
					}
					else if (reader.NodeType == XmlNodeType.None)
					{
						return;
					}
					else if (reader.NodeType == XmlNodeType.Text)
					{
						parentNode.Nodes.Add(reader.Value);
					}

				}
			}
			finally
			{
                // enabling redrawing of treeview after all nodes are added
				treeView.EndUpdate();      
                reader.Close();	
			}
		}

        private void SetControlConfig(string propertyName, string value, ControlConfig info)
        {
            if (propertyName == ConfigNodeTextAtt)
            {
                info.text = value;
            }
            else if (propertyName == ConfigNodeNameAtt)
            {
                info.name = value.ToString();
            }
            else if (propertyName == ConfigNodeTypeAtt)
            {
                info.type = Convert.ToInt32(value);
            }
            else if (propertyName == ConfigNodeTypeidAtt)
            {
                info.typeid = Convert.ToInt32(value);
            }
            else if (propertyName == ConfigNodeParam1)
            {
                info.param1 = value.ToString();
            }
            else if (propertyName == ConfigNodeParam2)
            {
                info.param2 = value.ToString();
            }
            else if (propertyName == ConfigNodeParam3)
            {
                info.param3 = value.ToString();
            }
            else if (propertyName == ConfigNodeParam4)
            {
                info.param4 = value.ToString();
            }
            else if (propertyName == ConfigNodeParam5)
            {
                info.param5 = value.ToString();
            }
            else if (propertyName == ConfigNodeParam6)
            {
                info.param6 = value.ToString();
            }
            else if (propertyName == ConfigNodeParam7)
            {
                info.param7 = value.ToString();
            }
            else if (propertyName == ConfigNodeParam8)
            {
                info.param8 = value.ToString();
            }
            else if (propertyName == ConfigNodeContent)
            {
                info.content = value.ToString();
            }
            else if (propertyName == ConfigNodeCount)
            {
                info.count = Convert.ToInt32(value);
            }
        }

		/// <summary>
		/// Used by Deserialize method for setting properties of TreeNode from xml node attributes
		/// </summary>
		/// <param name="node"></param>
		/// <param name="propertyName"></param>
		/// <param name="value"></param>
		private void SetAttributeValue(TreeNode node, string propertyName, string value, NodeInfo info)
		{
			if (propertyName == XmlNodeTextAtt)
			{                
				node.Text = value;				
			}
            else if (propertyName == XmlNodeNameAtt)
            {
                info.name = value.ToString();
            }
            else if (propertyName == XmlNodeIdAtt)
            {
                info.id = Convert.ToInt32(value);
            }
            else if (propertyName == XmlNodeTypeAtt)
            {
                info.type = Convert.ToInt32(value);
            }
            else if (propertyName == XmlNodeTypeidAtt)
            {
                info.typeid = Convert.ToInt32(value);
            }
            else if (propertyName == XmlNodeChilds)
            {
                foreach (string str in value.Split(','))
                {
                    if(str != "")
                    {
                        Int32 i = Convert.ToInt32(str);
                        info.childs.Add(i);
                    }
                }
                
            }
            else if (propertyName == XmlNodeParam1)
            {
                info.param1 = value.ToString();
            }
            else if (propertyName == XmlNodeParam2)
            {
                info.param2 = value.ToString();
            }
            else if (propertyName == XmlNodeParam3)
            {
                info.param3 = value.ToString();
            }
            else if (propertyName == XmlNodeParam4)
            {
                info.param4 = value.ToString();
            }
            else if (propertyName == XmlNodeParam5)
            {
                info.param5 = value.ToString();
            }
            else if (propertyName == XmlNodeParam6)
            {
                info.param6 = value.ToString();
            }
            else if (propertyName == XmlNodeParam7)
            {
                info.param7 = value.ToString();
            }
            else if (propertyName == XmlNodeParam8)
            {
                info.param8 = value.ToString();
            }
			
		}

        public void LoadXmlFileInTreeView(TreeView treeView, string fileName)
        {
            XmlTextReader reader = null;
            try
            {
                treeView.BeginUpdate();
                reader = new XmlTextReader(fileName);

                TreeNode n = new TreeNode(fileName);
                treeView.Nodes.Add(n);
                while(reader.Read())
                {
                    if(reader.NodeType == XmlNodeType.Element)
                    {
                        bool isEmptyElement = reader.IsEmptyElement;
                        StringBuilder text = new StringBuilder();
                        text.Append(reader.Name);
                        int attributeCount = reader.AttributeCount;
                        if(attributeCount > 0)
                        {
                            text.Append(" ( ");
                            for(int i = 0; i < attributeCount; i++)
                            {
                                if(i!=0) text.Append(", ");
                                reader.MoveToAttribute(i);
                                text.Append(reader.Name);
                                text.Append(" = ");
                                text.Append(reader.Value);
                            }
                            text.Append(" ) ");
                        }
            
                        if(isEmptyElement)
                        {
                            n.Nodes.Add(text.ToString());
                        }
                        else
                        {
                            n = n.Nodes.Add(text.ToString());
                        }
                    }
                    else if(reader.NodeType == XmlNodeType.EndElement)
                    {
                        n = n.Parent;                    
                    }
                    else if(reader.NodeType == XmlNodeType.XmlDeclaration)
                    {
                    
                    }
                    else if(reader.NodeType == XmlNodeType.None) 
                    {
                        return;
                    }
                    else if(reader.NodeType == XmlNodeType.Text)
                    {
                        n.Nodes.Add(reader.Value);
                    }

                }        
            }
            finally
            {
                treeView.EndUpdate();
                reader.Close();
            }
        }
	}
}
