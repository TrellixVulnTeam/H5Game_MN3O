using   System; 
using   System.Collections;
using System.Collections.Generic; 

namespace   TreeViewSerialization 
{ 
    public   class   STreeNode 
    { 
        #region   The   STreeNodeCollection   class. 
        public   class   STreeNodeCollection:ICollection 
        { 
            private   STreeNode   _owner=null; 
            private   ArrayList   _innerList=new   ArrayList(); 

            public   STreeNodeCollection(STreeNode   owner) 
            { 
                this._owner=owner; 
            } 

            public   STreeNode   this[int   index] 
            { 
                get
                {
                    return   (STreeNode)this._innerList[index];
                } 

                set 
                { 
                    if(value   ==null) 
                        throw   new   ArgumentNullException(); 

                    (this._innerList[index]   as   STreeNode)._parent=null; 
                    value._parent=this._owner; 
                    this._innerList[index]=value; 
                } 
            } 

            public   bool   IsSynchronized 
            { 
                get
                {   
                    return   this._innerList.IsSynchronized;
                } 
            } 

            public   int   Count 
            { 
                get
                {   
                    return   this._innerList.Count;
                } 
            } 

            public   void   CopyTo(Array   array,   int   index) 
            { 
                this._innerList.CopyTo(array,index); 
            } 

            public   object   SyncRoot 
            { 
                get 
                { 
                    return   this._innerList.SyncRoot; 
                } 
            } 

            public   IEnumerator   GetEnumerator() 
            { 
                return   this._innerList.GetEnumerator(); 
            } 

            public   int   Add(STreeNode   value) 
            { 
                if(value   ==null) 
                    throw   new   ArgumentNullException();	

                value._parent=this._owner; 
                return   this._innerList.Add(value); 
            } 

            public   void   Insert(int   index,   STreeNode   value) 
            { 
                if(value   ==null) 
                    throw   new   ArgumentNullException(); 

                value._parent=this._owner; 
                this._innerList.IndexOf(value,index); 
            } 

            public   void   RemoveAt(int   index) 
            { 
                try 
                { 
                    this[index]._parent=null; 
                    this._innerList.RemoveAt(index); 
                } 
                catch 
                { 
                } 
            } 

            public   int   IndexOf(STreeNode   value) 
            { 
                return   this._innerList.IndexOf(value); 
            } 

            public   void   Clear() 
            { 
                for(int   i=0;i <this.Count;i++) 
                { 
                    this[i]._parent=null; 
                } 

                this._innerList.Clear(); 
            } 

            public   bool   Contains(STreeNode   value) 
            { 
                return   this._innerList.Contains(value); 
            } 
        } 
        #endregion 

        private   STreeNode   _parent               =   null;
        private   NodeInfo    _value; 
        private   STreeNodeCollection   _childNodes  =   null;

        public STreeNode(NodeInfo value) 
        { 
            this._value = value; 
        } 

        public   STreeNode   ParentNode 
        { 
            get
            {
                return   this._parent;
            } 
        }

        public NodeInfo Value 
        { 
            get
            {
                return   this._value;
            } 
            set
            {
                this._value = value; 
            }
        } 

        public   STreeNodeCollection   ChildNodes 
        { 
            get 
            { 
                if(this._childNodes   !=null)   
                    return   this._childNodes; 

                this._childNodes = new   STreeNodeCollection(this); 
                return   this._childNodes; 
            } 
        } 

        public   bool   IsRoot 
        { 
            get
            {
                return   this.ParentNode==null;
            } 
        } 

        public   bool   IsLeaf 
        { 
            get 
            { 
                return   this._childNodes==null   ||   this._childNodes.Count==0; 
            } 
        } 

        public   Int32   Id 
        { 
            get 
            {
                return this.Value.id;
            } 
        }
    } 

    public   class   STree 
    { 
        private   STreeNode.STreeNodeCollection     _nodes=new   STreeNode.STreeNodeCollection(null); 

        public   STreeNode.STreeNodeCollection   Nodes 
        { 
            get
            {
                return   this._nodes;
            } 
        } 

        public   STreeNode   SearchNode(Int32   id) 
        { 

            STreeNode   treeNode=null; 
            for(int   i=0;i <this.Nodes.Count;i++) 
            { 
                if(this.Nodes[i].Value.id == id) 
                { 
                    treeNode=this.Nodes[i];   
                    break; 
                } 
            }
 
            /*
             int   c=1; 
                         while(treeNode!=null   &&   c <loc.Length) 
                         { 
                             for(int   i=0;i <treeNode.ChildNodes.Count;i++) 
                             { 
                                 if(treeNode.ChildNodes[i].Value==loc[c]) 
                                 { 
                                     treeNode=treeNode.ChildNodes[i]; 
                                     c++; 
                                 } 
                             } 
                             treeNode=null; 
                          }*/
              
             return   treeNode; 
        } 
    }

    public class NodeInfo
    {
        public string name;
        public Int32 id;
        public Int32 type;
        public Int32 typeid;
        public string param1;
        public string param2;
        public string param3;
        public string param4;
        public string param5;
        public string param6;
        public string param7;
        public string param8;
        public List<Int32> childs;
        public NodeInfo()
        {
            childs = new List<Int32>();
        }
        public NodeInfo(NodeInfo value)
        {
            name = value.name;
            id = value.id;
            type = value.type;
            typeid = value.typeid;
            param1 = value.param1;
            param2 = value.param2;
            param3 = value.param3;
            param4 = value.param4;
            param5 = value.param5;
            param6 = value.param6;
            param7 = value.param7;
            param8 = value.param8;
            childs = new List<Int32>(value.childs);
        }

    }

    public class ControlConfig
    {
        public string name;
        public string text;
        public Int32 type;
        public Int32 typeid;
        public string param1;
        public string param2;
        public string param3;
        public string param4;
        public string param5;
        public string param6;
        public string param7;
        public string param8;
        public string content;
        public Int32 count;
    }

    enum NodeType
    {
        TypeUnknown,
        TypeEvent,
        TypeAction,
        TypeCondtion,
    }

    enum EventType
    {
        TypeUnknown,
        Startup, 
        EventCreateProcess,    
        TimeEvent,
    }

    enum ActionType
    {
        TypeUnknown,
        SetEventHandler,
        CreateTimer,

    }

    enum ConditionType
    {
        TypeUnknown,
    }


/*
    struct Node{
        string strName;
        Int32 nID;
        List<Node> vtChilds;
        Node parent;
    }

    class Tree{
        private:
            Node root;

    }*/


} 