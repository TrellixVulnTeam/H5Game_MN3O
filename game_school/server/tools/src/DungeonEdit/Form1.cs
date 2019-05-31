using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Xml;
using System.Text;
using System.Collections.Generic; 

namespace TreeViewSerialization
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.TreeView treeView1;
		private System.Windows.Forms.Button btnLoad;
		private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.Button btnViewXml;
        private Button btnSaveLua;
        private Button btnAddNode;
        private Button btnDeleteNode;
        private Label label1;
        private ComboBox cbbNodeType;
        private Label label2;
        private ComboBox cbbEvent;
        private Label label3;
        private ComboBox cbbAction;
        private Label label4;
        private ComboBox cbbCondition;
        private Label label5;
        private TextBox tbParam1;
        private Label label6;
        private Label label7;
        private TextBox tbParam2;
        private TextBox tbParam3;
        private TextBox tbParam6;
        private TextBox tbParam5;
        private Label label8;
        private Label label9;
        private TextBox tbParam4;
        private Label label10;
        private Label label11;
        private TextBox tbText;
        private Label label12;
        private TextBox tbName;
        private Label label13;
        private TextBox tbId;
        private Label label14;
        private TextBox tbChilds;
        private Button tbEditNewNode;
        private System.ComponentModel.IContainer components;
        private TextBox tbParam8;
        private Label label15;
        private TextBox tbParam7;
        private Label label16;
        private Button btSaveNode;
        private Button bnNew;

        private Dictionary<Int32, Dictionary<Int32, ControlConfig>> dicControlConfig = null;


		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
            InitConfig();
            InitControl();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.btnLoad = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.btnViewXml = new System.Windows.Forms.Button();
            this.btnSaveLua = new System.Windows.Forms.Button();
            this.btnAddNode = new System.Windows.Forms.Button();
            this.btnDeleteNode = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.cbbNodeType = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cbbEvent = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cbbAction = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cbbCondition = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tbParam1 = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.tbParam2 = new System.Windows.Forms.TextBox();
            this.tbParam3 = new System.Windows.Forms.TextBox();
            this.tbParam6 = new System.Windows.Forms.TextBox();
            this.tbParam5 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.tbParam4 = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.tbText = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.tbName = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.tbId = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.tbChilds = new System.Windows.Forms.TextBox();
            this.tbEditNewNode = new System.Windows.Forms.Button();
            this.tbParam8 = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.tbParam7 = new System.Windows.Forms.TextBox();
            this.label16 = new System.Windows.Forms.Label();
            this.btSaveNode = new System.Windows.Forms.Button();
            this.bnNew = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // treeView1
            // 
            this.treeView1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.treeView1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.treeView1.ImageIndex = 0;
            this.treeView1.ImageList = this.imageList1;
            this.treeView1.Location = new System.Drawing.Point(7, 33);
            this.treeView1.Name = "treeView1";
            this.treeView1.SelectedImageIndex = 7;
            this.treeView1.Size = new System.Drawing.Size(300, 700);
            this.treeView1.TabIndex = 0;
            this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.treeView1_AfterSelect);
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "");
            this.imageList1.Images.SetKeyName(1, "");
            this.imageList1.Images.SetKeyName(2, "");
            this.imageList1.Images.SetKeyName(3, "");
            this.imageList1.Images.SetKeyName(4, "");
            this.imageList1.Images.SetKeyName(5, "");
            this.imageList1.Images.SetKeyName(6, "");
            this.imageList1.Images.SetKeyName(7, "");
            // 
            // btnLoad
            // 
            this.btnLoad.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnLoad.Location = new System.Drawing.Point(139, 2);
            this.btnLoad.Name = "btnLoad";
            this.btnLoad.Size = new System.Drawing.Size(90, 24);
            this.btnLoad.TabIndex = 1;
            this.btnLoad.Text = "加载Xml";
            this.btnLoad.Click += new System.EventHandler(this.btnLoad_Click);
            // 
            // btnSave
            // 
            this.btnSave.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSave.Location = new System.Drawing.Point(465, 2);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(90, 24);
            this.btnSave.TabIndex = 2;
            this.btnSave.Text = "保存Xml";
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // btnViewXml
            // 
            this.btnViewXml.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnViewXml.Location = new System.Drawing.Point(12, 3);
            this.btnViewXml.Name = "btnViewXml";
            this.btnViewXml.Size = new System.Drawing.Size(112, 22);
            this.btnViewXml.TabIndex = 3;
            this.btnViewXml.Text = "查看Xml";
            this.btnViewXml.Click += new System.EventHandler(this.btnViewXml_Click);
            // 
            // btnSaveLua
            // 
            this.btnSaveLua.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSaveLua.Location = new System.Drawing.Point(356, 2);
            this.btnSaveLua.Name = "btnSaveLua";
            this.btnSaveLua.Size = new System.Drawing.Size(90, 24);
            this.btnSaveLua.TabIndex = 4;
            this.btnSaveLua.Text = "保存Lua";
            this.btnSaveLua.Click += new System.EventHandler(this.btnSaveLua_Click);
            // 
            // btnAddNode
            // 
            this.btnAddNode.Location = new System.Drawing.Point(676, 3);
            this.btnAddNode.Name = "btnAddNode";
            this.btnAddNode.Size = new System.Drawing.Size(75, 23);
            this.btnAddNode.TabIndex = 5;
            this.btnAddNode.Text = "添加节点";
            this.btnAddNode.UseVisualStyleBackColor = true;
            this.btnAddNode.Click += new System.EventHandler(this.btnAddNode_Click);
            // 
            // btnDeleteNode
            // 
            this.btnDeleteNode.Location = new System.Drawing.Point(575, 3);
            this.btnDeleteNode.Name = "btnDeleteNode";
            this.btnDeleteNode.Size = new System.Drawing.Size(75, 23);
            this.btnDeleteNode.TabIndex = 6;
            this.btnDeleteNode.Text = "删除节点";
            this.btnDeleteNode.UseVisualStyleBackColor = true;
            this.btnDeleteNode.Click += new System.EventHandler(this.btnDeleteNode_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(342, 58);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "节点类型：";
            // 
            // cbbNodeType
            // 
            this.cbbNodeType.FormattingEnabled = true;
            this.cbbNodeType.Items.AddRange(new object[] {
            "---",
            "事件",
            "动作",
            "条件"});
            this.cbbNodeType.Location = new System.Drawing.Point(417, 56);
            this.cbbNodeType.Name = "cbbNodeType";
            this.cbbNodeType.Size = new System.Drawing.Size(121, 20);
            this.cbbNodeType.TabIndex = 8;
            this.cbbNodeType.SelectedIndexChanged += new System.EventHandler(this.cbbNodeType_SelectedIndexChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(573, 59);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 9;
            this.label2.Text = "触发器：";
            // 
            // cbbEvent
            // 
            this.cbbEvent.Enabled = false;
            this.cbbEvent.FormattingEnabled = true;
/*
            this.cbbEvent.Items.AddRange(new object[] {
            "---",
            "Startup",
            "创建副本事件",
            "创建time事件"});*/

            this.cbbEvent.Location = new System.Drawing.Point(632, 55);
            this.cbbEvent.Name = "cbbEvent";
            this.cbbEvent.Size = new System.Drawing.Size(121, 20);
            this.cbbEvent.TabIndex = 10;
            this.cbbEvent.SelectedIndexChanged += new System.EventHandler(this.cbbEvent_SelectedIndexChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(778, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 12);
            this.label3.TabIndex = 11;
            this.label3.Text = "动作：";
            // 
            // cbbAction
            // 
            this.cbbAction.Enabled = false;
            this.cbbAction.FormattingEnabled = true;
/*
            this.cbbAction.Items.AddRange(new object[] {
            "----",
            "创建事件动作",
            "创建time动作"});*/

            this.cbbAction.Location = new System.Drawing.Point(825, 56);
            this.cbbAction.Name = "cbbAction";
            this.cbbAction.Size = new System.Drawing.Size(121, 20);
            this.cbbAction.TabIndex = 12;
            this.cbbAction.SelectedIndexChanged += new System.EventHandler(this.cbbAction_SelectedIndexChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(977, 58);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 12);
            this.label4.TabIndex = 13;
            this.label4.Text = "条件：";
            // 
            // cbbCondition
            // 
            this.cbbCondition.Enabled = false;
            this.cbbCondition.FormattingEnabled = true;
/*
            this.cbbCondition.Items.AddRange(new object[] {
            "----"});*/

            this.cbbCondition.Location = new System.Drawing.Point(1033, 55);
            this.cbbCondition.Name = "cbbCondition";
            this.cbbCondition.Size = new System.Drawing.Size(121, 20);
            this.cbbCondition.TabIndex = 14;
            this.cbbCondition.SelectedIndexChanged += new System.EventHandler(this.cbbCondition_SelectedIndexChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(342, 148);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 12);
            this.label5.TabIndex = 15;
            this.label5.Text = "param1：";
            // 
            // tbParam1
            // 
            this.tbParam1.Location = new System.Drawing.Point(417, 148);
            this.tbParam1.Name = "tbParam1";
            this.tbParam1.Size = new System.Drawing.Size(100, 21);
            this.tbParam1.TabIndex = 16;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(573, 148);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 17;
            this.label6.Text = "param2：";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(778, 148);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(53, 12);
            this.label7.TabIndex = 18;
            this.label7.Text = "param3：";
            // 
            // tbParam2
            // 
            this.tbParam2.Location = new System.Drawing.Point(632, 148);
            this.tbParam2.Name = "tbParam2";
            this.tbParam2.Size = new System.Drawing.Size(100, 21);
            this.tbParam2.TabIndex = 19;
            // 
            // tbParam3
            // 
            this.tbParam3.Location = new System.Drawing.Point(825, 148);
            this.tbParam3.Name = "tbParam3";
            this.tbParam3.Size = new System.Drawing.Size(100, 21);
            this.tbParam3.TabIndex = 20;
            // 
            // tbParam6
            // 
            this.tbParam6.Location = new System.Drawing.Point(632, 204);
            this.tbParam6.Name = "tbParam6";
            this.tbParam6.Size = new System.Drawing.Size(100, 21);
            this.tbParam6.TabIndex = 26;
            // 
            // tbParam5
            // 
            this.tbParam5.Location = new System.Drawing.Point(417, 204);
            this.tbParam5.Name = "tbParam5";
            this.tbParam5.Size = new System.Drawing.Size(100, 21);
            this.tbParam5.TabIndex = 25;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(573, 204);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 24;
            this.label8.Text = "param6：";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(342, 204);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(53, 12);
            this.label9.TabIndex = 23;
            this.label9.Text = "param5：";
            // 
            // tbParam4
            // 
            this.tbParam4.Location = new System.Drawing.Point(1036, 148);
            this.tbParam4.Name = "tbParam4";
            this.tbParam4.Size = new System.Drawing.Size(100, 21);
            this.tbParam4.TabIndex = 22;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(977, 148);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(53, 12);
            this.label10.TabIndex = 21;
            this.label10.Text = "param4：";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(342, 109);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(41, 12);
            this.label11.TabIndex = 27;
            this.label11.Text = "text：";
            // 
            // tbText
            // 
            this.tbText.Location = new System.Drawing.Point(417, 100);
            this.tbText.Name = "tbText";
            this.tbText.Size = new System.Drawing.Size(100, 21);
            this.tbText.TabIndex = 28;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(573, 109);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(41, 12);
            this.label12.TabIndex = 29;
            this.label12.Text = "name：";
            // 
            // tbName
            // 
            this.tbName.Location = new System.Drawing.Point(632, 100);
            this.tbName.Name = "tbName";
            this.tbName.Size = new System.Drawing.Size(100, 21);
            this.tbName.TabIndex = 30;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(778, 109);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(29, 12);
            this.label13.TabIndex = 31;
            this.label13.Text = "id：";
            // 
            // tbId
            // 
            this.tbId.Enabled = false;
            this.tbId.Location = new System.Drawing.Point(825, 100);
            this.tbId.Name = "tbId";
            this.tbId.Size = new System.Drawing.Size(100, 21);
            this.tbId.TabIndex = 32;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(977, 109);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(53, 12);
            this.label14.TabIndex = 33;
            this.label14.Text = "childs：";
            // 
            // tbChilds
            // 
            this.tbChilds.Enabled = false;
            this.tbChilds.Location = new System.Drawing.Point(1036, 100);
            this.tbChilds.Name = "tbChilds";
            this.tbChilds.Size = new System.Drawing.Size(100, 21);
            this.tbChilds.TabIndex = 34;
            // 
            // tbEditNewNode
            // 
            this.tbEditNewNode.Location = new System.Drawing.Point(757, 3);
            this.tbEditNewNode.Name = "tbEditNewNode";
            this.tbEditNewNode.Size = new System.Drawing.Size(75, 23);
            this.tbEditNewNode.TabIndex = 35;
            this.tbEditNewNode.Text = "编辑新节点";
            this.tbEditNewNode.UseVisualStyleBackColor = true;
            this.tbEditNewNode.Click += new System.EventHandler(this.tbEditNewNode_Click);
            // 
            // tbParam8
            // 
            this.tbParam8.Location = new System.Drawing.Point(344, 287);
            this.tbParam8.Multiline = true;
            this.tbParam8.Name = "tbParam8";
            this.tbParam8.Size = new System.Drawing.Size(783, 325);
            this.tbParam8.TabIndex = 36;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(778, 213);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(53, 12);
            this.label15.TabIndex = 37;
            this.label15.Text = "param7：";
            // 
            // tbParam7
            // 
            this.tbParam7.Location = new System.Drawing.Point(825, 204);
            this.tbParam7.Name = "tbParam7";
            this.tbParam7.Size = new System.Drawing.Size(100, 21);
            this.tbParam7.TabIndex = 38;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(342, 257);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(191, 12);
            this.label16.TabIndex = 39;
            this.label16.Text = "param8：在节点下任意编辑lua脚本";
            // 
            // btSaveNode
            // 
            this.btSaveNode.Location = new System.Drawing.Point(838, 3);
            this.btSaveNode.Name = "btSaveNode";
            this.btSaveNode.Size = new System.Drawing.Size(87, 23);
            this.btSaveNode.TabIndex = 40;
            this.btSaveNode.Text = "保存当前节点";
            this.btSaveNode.UseVisualStyleBackColor = true;
            this.btSaveNode.Click += new System.EventHandler(this.btSaveNode_Click);
            // 
            // bnNew
            // 
            this.bnNew.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.bnNew.Location = new System.Drawing.Point(251, 2);
            this.bnNew.Name = "bnNew";
            this.bnNew.Size = new System.Drawing.Size(90, 24);
            this.bnNew.TabIndex = 41;
            this.bnNew.Text = "新建Xml";
            this.bnNew.Click += new System.EventHandler(this.bnNew_Click);
            // 
            // Form1
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(6, 14);
            this.ClientSize = new System.Drawing.Size(1192, 738);
            this.Controls.Add(this.bnNew);
            this.Controls.Add(this.btSaveNode);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.tbParam7);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.tbParam8);
            this.Controls.Add(this.tbEditNewNode);
            this.Controls.Add(this.tbChilds);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.tbId);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.tbName);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.tbText);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.tbParam6);
            this.Controls.Add(this.tbParam5);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.tbParam4);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.tbParam3);
            this.Controls.Add(this.tbParam2);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.tbParam1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.cbbCondition);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.cbbAction);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.cbbEvent);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.cbbNodeType);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnDeleteNode);
            this.Controls.Add(this.btnAddNode);
            this.Controls.Add(this.btnSaveLua);
            this.Controls.Add(this.btnViewXml);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnLoad);
            this.Controls.Add(this.treeView1);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "TreeView Serialization";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void Form1_Load(object sender, System.EventArgs e)
		{

		}

        private void btnSave_Click(object sender, System.EventArgs e)
		{
            SaveFileDialog saveFile = new SaveFileDialog();
            saveFile.FileName = Application.StartupPath;
            if(saveFile.ShowDialog() != DialogResult.OK) return;

			TreeViewSerializer serializer = new TreeViewSerializer();
            serializer.SerializeXml(this.treeView1, saveFile.FileName);
		}

		private void btnLoad_Click(object sender, System.EventArgs e)
		{
			OpenFileDialog openFile = new OpenFileDialog();
            openFile.FileName = Application.StartupPath;
			if (openFile.ShowDialog() != DialogResult.OK) return;
            this.treeView1.Nodes.Clear();
			TreeViewSerializer serializer = new TreeViewSerializer();
            serializer.LoadXmlTreeView(this.treeView1, openFile.FileName);
			
		}

        private void bnNew_Click(object sender, EventArgs e)
        {
            this.treeView1.Nodes.Clear();
            InitControl();
            TreeNode node = new TreeNode();


            NodeInfo info = new NodeInfo();
            info.name = "Startup";
            info.id = 1;
            info.type = 1;
            info.typeid = 1;
            tbId.Text = info.id.ToString();
            tbName.Text = info.name;
            node.Text = "开始副本事件";
            node.Tag = info;

            treeView1.Nodes.Add(node);

            
        }


        private void btnViewXml_Click(object sender, System.EventArgs e)
        {
            OpenFileDialog openFile = new OpenFileDialog();
            openFile.FileName = Application.StartupPath;
            if(openFile.ShowDialog() != DialogResult.OK) return;

            this.treeView1.Nodes.Clear();
            TreeViewSerializer serializer = new TreeViewSerializer();
            serializer.LoadXmlFileInTreeView(this.treeView1, openFile.FileName);        
        }

        private void btnSaveLua_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFile = new SaveFileDialog();
            saveFile.FileName = Application.StartupPath ;
            if (saveFile.ShowDialog() != DialogResult.OK) return;

            TreeViewSerializer serializer = new TreeViewSerializer();
            serializer.SerializeLua(this.treeView1, saveFile.FileName, dicControlConfig);
        }

        private void btnAddNode_Click(object sender, EventArgs e)
        {
            string message;
            if(this.treeView1.SelectedNode != null)
            {
                AddChildNode();
            }
            else
            {
                message = "请选择节点";
                MessageBox.Show(this, message);
            }
        }

        private void AddChildNode()
        {

            TreeNode vTreeNode = new TreeNode();
            vTreeNode.Text = tbText.Text;

            NodeInfo info = new NodeInfo();
            info.id = Convert.ToInt32(tbId.Text);
            info.name = tbName.Text.ToString();
            info.type = cbbNodeType.SelectedIndex;
            if ((NodeType)cbbNodeType.SelectedIndex == NodeType.TypeEvent)
            {
                info.typeid = cbbEvent.SelectedIndex;
            }
            else if ((NodeType)cbbNodeType.SelectedIndex == NodeType.TypeAction)
            {
                info.typeid = cbbAction.SelectedIndex;
            }
            else if ((NodeType)cbbNodeType.SelectedIndex == NodeType.TypeCondtion)
            {
                info.typeid = cbbCondition.SelectedIndex;
            }

            info.param1 = tbParam1.Text.ToString();
            info.param2 = tbParam2.Text.ToString();
            info.param3 = tbParam3.Text.ToString();
            info.param4 = tbParam4.Text.ToString();
            info.param5 = tbParam5.Text.ToString();
            info.param6 = tbParam6.Text.ToString();
            info.param7 = tbParam7.Text.ToString();
            if (tbParam8.Text.Length != 0)
            {
                info.param8 = tbParam8.Text.ToString();
            }

            vTreeNode.Tag = info;

            this.treeView1.SelectedNode.Nodes.Add(vTreeNode);
            this.treeView1.SelectedNode.Expand();
            this.treeView1.SelectedNode = vTreeNode;
            TreeNode node = this.treeView1.SelectedNode.Parent;
            if (node != null)
            {
                ((NodeInfo)node.Tag).childs.Add(info.id);
            }
        }

        private void tbEditNewNode_Click(object sender, EventArgs e)
        {
            InitControl();
            TreeViewSerializer serializer = new TreeViewSerializer();
            tbId.Text = (treeView1.GetNodeCount(true) + 1).ToString();//serializer.GetNodeCount(this.treeView1).ToString();
        }

        private void btnDeleteNode_Click(object sender, EventArgs e)
        {
            string vMessage;

            if (this.treeView1.SelectedNode.Nodes.Count > 0)
                vMessage = "This Node has child nodes, if you delete it, the child nodes will be also be deleted \n Sure you want to delete it ?";
            else
                vMessage = "Sure you want to delete it ?";

            if (MessageBox.Show(this, vMessage, "treeView1", System.Windows.Forms.MessageBoxButtons.OKCancel, System.Windows.Forms.MessageBoxIcon.Warning) == System.Windows.Forms.DialogResult.OK)
            {
                TreeNode parent = this.treeView1.SelectedNode.Parent;
                if (parent != null)
                {
                    ((NodeInfo)parent.Tag).childs.Clear();
                }
                this.treeView1.SelectedNode.Remove();
            }
        }

        private void cbbNodeType_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch ((NodeType)cbbNodeType.SelectedIndex)
           {
               case NodeType.TypeEvent:
                   cbbEvent.Enabled = true;
                   cbbAction.Enabled = false;
                   cbbCondition.Enabled = false;
                   cbbEvent.SelectedIndex = 0;
                   cbbAction.SelectedIndex = 0;
                   cbbCondition.SelectedIndex = 0;
                   break;
                case NodeType.TypeAction:
                   cbbEvent.Enabled = false;
                   cbbAction.Enabled = true;
                   cbbCondition.Enabled = false;
                   cbbEvent.SelectedIndex = 0;
                   cbbAction.SelectedIndex = 0;
                   cbbCondition.SelectedIndex = 0;
                   break;
                case NodeType.TypeCondtion:
                   cbbEvent.Enabled = false;
                   cbbAction.Enabled = false;
                   cbbCondition.Enabled = true;
                   cbbEvent.SelectedIndex = 0;
                   cbbAction.SelectedIndex = 0;
                   cbbCondition.SelectedIndex = 0;
                   break;
           }
        }

        private void cbbEvent_SelectedIndexChanged(object sender, EventArgs e)
        {
            //cbbEvent.SelectedIndex
            ControlConfig info;
            bool ret = dicControlConfig[(Int32)NodeType.TypeEvent].TryGetValue(cbbEvent.SelectedIndex, out info);
            if (ret)
            {
                changeControl(info);
            }

            
        }

        private void cbbAction_SelectedIndexChanged(object sender, EventArgs e)
        {
            ControlConfig info;
            bool ret = dicControlConfig[(Int32)NodeType.TypeAction].TryGetValue(cbbAction.SelectedIndex, out info);
            if (ret)
            {
                changeControl(info);
            }

            
        }

        private void cbbCondition_SelectedIndexChanged(object sender, EventArgs e)
        {
            ControlConfig info;
            bool ret = dicControlConfig[(Int32)NodeType.TypeCondtion].TryGetValue(cbbCondition.SelectedIndex, out info);
            if (ret)
            {
                changeControl(info);
            }
            
        }

        private void changeControl(ControlConfig info)
        {
                tbName.Text = info.name;
                tbText.Text = info.text;
                if (info.param1 != "0")
                {
                    tbParam1.Text = info.param1;
                    tbParam1.Enabled = true;
                }
                else
                {
                    tbParam1.Text = "";
                    tbParam1.Enabled = false;

                }

                if (info.param2 != "0")
                {
                    tbParam2.Text = info.param2;
                    tbParam2.Enabled = true;
                }
                else
                {
                    tbParam2.Text = "";
                    tbParam2.Enabled = false;
                }

                if (info.param3 != "0")
                {
                    tbParam3.Text = info.param3;
                    tbParam3.Enabled = true;
                }
                else
                {
                    tbParam3.Text = "";
                    tbParam3.Enabled = false;
                }

                if (info.param4 != "0")
                {
                    tbParam4.Text = info.param4;
                    tbParam4.Enabled = true;
                }
                else
                {
                    tbParam4.Text = "";
                    tbParam4.Enabled = false;
                }

                if (info.param5 != "0")
                {
                    tbParam5.Text = info.param5;
                    tbParam5.Enabled = true;
                }
                else
                {
                    tbParam5.Text = "";
                    tbParam5.Enabled = false;
                }

                if (info.param6 != "0")
                {
                    tbParam6.Text = info.param6;
                    tbParam6.Enabled = true;
                }
                else
                {
                    tbParam6.Text = "";
                    tbParam6.Enabled = false;
                }

                if (info.param7 != "0")
                {
                    tbParam7.Text = info.param7;
                    tbParam7.Enabled = true;
                }
                else
                {
                    tbParam7.Text = "";
                    tbParam7.Enabled = false;
                }
        }

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (this.treeView1.SelectedNode != null && this.treeView1.SelectedNode.Tag != null)
            {
                NodeInfo info = (NodeInfo)this.treeView1.SelectedNode.Tag;
                this.cbbNodeType.SelectedIndex = info.type;
                if ((NodeType)(this.cbbNodeType.SelectedIndex) == NodeType.TypeEvent)
                {
                    cbbEvent.Enabled = true;
                    cbbAction.Enabled = false;
                    cbbCondition.Enabled = false;

                    cbbEvent.SelectedIndex = info.typeid;
                    cbbAction.SelectedIndex = 0;
                    cbbCondition.SelectedIndex = 0;
                }
                else if ((NodeType)(this.cbbNodeType.SelectedIndex) == NodeType.TypeAction)
                {
                    cbbEvent.Enabled = false;
                    cbbAction.Enabled = true;
                    cbbCondition.Enabled = false;

                    cbbEvent.SelectedIndex = 0;
                    cbbAction.SelectedIndex = info.typeid;
                    cbbCondition.SelectedIndex = 0;
                }
                else if ((NodeType)(this.cbbNodeType.SelectedIndex) == NodeType.TypeCondtion)
                {
                    cbbEvent.Enabled = false;
                    cbbAction.Enabled = false;
                    cbbCondition.Enabled = true;

                    cbbEvent.SelectedIndex = 0;
                    cbbAction.SelectedIndex = 0;
                    cbbCondition.SelectedIndex = info.typeid;
                }

                this.tbText.Text = this.treeView1.SelectedNode.Text;
                this.tbName.Text = info.name;
                this.tbId.Text = info.id.ToString();
                 if (info.childs != null)
                  {
                        StringBuilder builder = new StringBuilder();
                        foreach (Int32 index in info.childs)
                        {
                            builder.AppendFormat("{0},", index);
                        }
                        this.tbChilds.Text = builder.ToString();
                 }
                 this.tbParam1.Text = info.param1;
                 this.tbParam2.Text = info.param2;
                 this.tbParam3.Text = info.param3;
                 this.tbParam4.Text = info.param4;
                 this.tbParam5.Text = info.param5;
                 this.tbParam6.Text = info.param6;
                 this.tbParam7.Text = info.param7;
                 this.tbParam8.Text = info.param8;

                 ControlConfig config;
                 bool ret = dicControlConfig[info.type].TryGetValue(info.typeid, out config);
                 if (ret)
                 {
                     changeControl(config);
                 }

                
            }
        }

        private void InitControl()
        {
            cbbEvent.Enabled = false;
            cbbAction.Enabled = false;
            cbbCondition.Enabled = false;

            cbbNodeType.SelectedIndex = 0;
            cbbEvent.SelectedIndex = 0;
            cbbAction.SelectedIndex = 0;
            cbbCondition.SelectedIndex = 0;
            this.tbText.Text = "";
            this.tbName.Text = "";
            this.tbId.Text = "";
            this.tbChilds.Text = "";
            this.tbParam1.Text = "";
            this.tbParam2.Text = "";
            this.tbParam3.Text = "";
            this.tbParam4.Text = "";
            this.tbParam5.Text = "";
            this.tbParam6.Text = "";
            this.tbParam7.Text = "";
            this.tbParam8.Text = "";
        }

        private void InitConfig()
        {
            dicControlConfig = new Dictionary<Int32, Dictionary<Int32, ControlConfig>>();

            OpenFileDialog openFile = new OpenFileDialog();
            openFile.FileName = Application.StartupPath;
            if (openFile.ShowDialog() != DialogResult.OK) return;
            this.treeView1.Nodes.Clear();
            TreeViewSerializer serializer = new TreeViewSerializer();
            serializer.LoadXmlConfig(dicControlConfig, openFile.FileName);

            cbbEvent.Items.Insert(0, "----");
            cbbAction.Items.Insert(0, "----");
            cbbCondition.Items.Insert(0, "----");
            foreach (KeyValuePair<Int32, Dictionary<Int32, ControlConfig>> kvp in dicControlConfig)
            {
                if (kvp.Key == (Int32)NodeType.TypeEvent)
                {
                    foreach (KeyValuePair<Int32, ControlConfig> dic in kvp.Value)
                    {
                        cbbEvent.Items.Insert(dic.Key, dic.Value.text);
                    }
                    
                }
                else if (kvp.Key == (Int32)NodeType.TypeAction)
                {
                    foreach (KeyValuePair<Int32, ControlConfig> dic in kvp.Value)
                    {
                        cbbAction.Items.Insert(dic.Key, dic.Value.text);
                    }
                }
                else if (kvp.Key == (Int32)NodeType.TypeCondtion)
                {
                    foreach (KeyValuePair<Int32, ControlConfig> dic in kvp.Value)
                    {
                        cbbCondition.Items.Insert(dic.Key, dic.Value.text);
                    }
                }
                
            }

        }

        private void btSaveNode_Click(object sender, EventArgs e)
        {
            if (this.treeView1.SelectedNode != null)
            {
                NodeInfo info = (NodeInfo)(this.treeView1.SelectedNode.Tag);
                info.id = Convert.ToInt32(tbId.Text);
                info.name = tbName.Text.ToString();
                info.type = cbbNodeType.SelectedIndex;
                if ((NodeType)cbbNodeType.SelectedIndex == NodeType.TypeEvent)
                {
                    info.typeid = cbbEvent.SelectedIndex;
                }
                else if ((NodeType)cbbNodeType.SelectedIndex == NodeType.TypeAction)
                {
                    info.typeid = cbbAction.SelectedIndex;
                }
                else if ((NodeType)cbbNodeType.SelectedIndex == NodeType.TypeCondtion)
                {
                    info.typeid = cbbCondition.SelectedIndex;
                }

                info.param1 = tbParam1.Text.ToString();
                info.param2 = tbParam2.Text.ToString();
                info.param3 = tbParam3.Text.ToString();
                info.param4 = tbParam4.Text.ToString();
                info.param5 = tbParam5.Text.ToString();
                info.param6 = tbParam6.Text.ToString();
                info.param7 = tbParam7.Text.ToString();
                if (tbParam8.Text.Length != 0)
                {
                    info.param8 = tbParam8.Text.ToString();
                }
            }
        }


	}
}
