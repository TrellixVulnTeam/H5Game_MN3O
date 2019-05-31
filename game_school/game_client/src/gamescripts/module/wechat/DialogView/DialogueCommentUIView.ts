/**
 * 对话界面
 */
class DialogueCommentUIView extends BaseEuiView{

	private btn_chatback:eui.Button;//返回
	private talk_name:eui.Label;//标题
	private scr_playertalk:eui.Group;//聊天内容

	private Group_player:eui.Group;//玩家操作区域
	private btn_open:eui.Button;//输入按钮
	private btn_sent:eui.Button;//发送按钮
	private tab_group:eui.Group;//选项卡容器
	private tab_backImage:eui.Image;//选项卡背景
	private tips_label:eui.Label;//提示文本
	private label_choose:eui.Label;//输入框文本

	private toggle1:eui.RadioButton;//选项1
	private toggle2:eui.RadioButton;//选项2
	private toggle3:eui.RadioButton;//选项3
	private toggle4:eui.RadioButton;//选项4
	private toggleArr:eui.RadioButton[]=[];//选项卡
	private radioGroup: eui.RadioButtonGroup ;//选项卡

	private scr_talk:eui.Scroller;//滚动条
	private tab_filling:eui.Image;//填充图

	private currentInfoList:ChatOwnList;//当前聊天列表
	
	private isOpenPlayer:boolean=true;//是否展开
	private isPlayerTalk:boolean=false;//是否到玩家发言
	private tab_height:number;//选项卡高度
	private oriHeight:number;//选项卡原始高度
	
	private currentSelectIndex:number;//玩家选择id
	private currentInfo:WechatGroupInfo;//当前聊天组
	private currentOptionId:number;//玩家选项id
	private currentChatId:number;//当前聊天id

	private upPull:boolean=false;//上拉
	private dounPull:boolean=false;//下拉
	private laseIndex:number=0;

	public openType:WechatUIType=WechatUIType.Wechat_chat;

	public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);
	}

	/**
	 * 打开与某角色的对话
	*/
	public OpenByOwner(ownId:number){
		this.ReSetUI();
		this.currentInfoList=App.WechatManager.GetChatListByownId(ownId);
		let info:WechatGroupInfo;
		if(this.currentInfoList.IsExistNoTrigger()){//如果有未触发
			info=this.currentInfoList.GetCurrentChat();
		}else{
			info=this.currentInfoList.GetLastChatByStatu();
		}

		if(info){
				this.currentInfo=info;
				if(info.mChatConfig.type==WeChatGroupType.Flock){
					let config=ChatGroupNumConfig.GetConfig(info.mChatConfig.belong);
					this.talk_name.text=config.name;
				}else{
					let config=GirlConfig .GetConfig(info.mChatConfig.belong);
					this.talk_name.text=config.name;
				}
				
				this.CreateTalk(info.mChatConfig.startChatID,info,false);
		}else{
			//未发现聊天信息
		}
	}

	/**
	 * 打开某条对话
	 */
	public OpenByChatID(ownId:number,chatId:number){
		this.ReSetUI();
		let info:WechatGroupInfo=App.WechatManager.GetChatById(ownId,chatId);
		if(info)
		this.CreateTalk(info.mChatConfig.startChatID,info,false);
	}


	public initUI(){
		super.initUI();
		this.skinName=App.ViewManager.getSkin(ViewConst.Dialogue);
		this.tab_height=this.tab_backImage.height;
		this.oriHeight=this.Group_player.y;//默认选项卡的ui是展开的，记录下位置
		this.scr_talk.viewport = this.scr_playertalk;
		this.btn_open.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OpenBtnClickEvent,this);
		this.btn_sent.addEventListener(egret.TouchEvent.TOUCH_TAP,this.SendBtnClickEvent,this);
		this. radioGroup= new eui.RadioButtonGroup();
		this. radioGroup.addEventListener(eui.UIEvent.CHANGE, this.radioChangeHandler, this);
		this.btn_chatback.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>{
			App.EventMgrHelper.PushEvent(EventDef.BackDialogListView,this.openType);
		},this);
		this.scr_talk.addEventListener(eui.UIEvent.CHANGE,this.MoveHandler,this);
		this.scr_talk.addEventListener(eui.UIEvent.CHANGE_END,this.MoveEndHandler,this);
	}

	/**
	 * 拖动滚动条
	 */
	private MoveHandler(){
		//上拉
		if(this.scr_talk.viewport.scrollV > (this.scr_talk.viewport.contentHeight - this.scr_talk.viewport.height)+100){
				this.upPull=true;
		}
		//下拉
		if(this.scr_talk.viewport.scrollV <-100){
			this.dounPull=true;
		}
	}

	/**
	 * 拖动结束
	 */
	private MoveEndHandler(){
		if(this.upPull&&this.currentInfo.CurrentStatus==WeChatGroupStatus.Triggered){
				this.upPull=false;
				let info:WechatGroupInfo=this.currentInfoList.GetNextChat();
				if(info){
				this.currentInfo=info;
				this.CreateTalk(info.mChatConfig.startChatID,info,false);
				}
		}
				
		if(this.dounPull&&this.currentInfo.CurrentStatus==WeChatGroupStatus.Triggered){
				this.dounPull=false;
				let info:WechatGroupInfo=this.currentInfoList.GetLastChat();
				if(info){
				this.currentInfo=info;
				this.laseIndex=0;
				this.CreateLastTalk(info.mChatConfig.startChatID,info,false);
				}
		}
	}

	/**
	 * 生成上一个
	 */
	public CreateLastTalk(id:number,info:WechatGroupInfo,isDelay:boolean){
		if(id!=-1){
			let config:ChatConfig=ChatConfig.GetConfig(id);
			
			if(config){
				
				if(info.CurrentStatus==WeChatGroupStatus.ActivationNotTrigger){//未触发
				
				}else{
					if(config.type==DialogType.Player){
						 let item: DialogueItemView=ObjectPool.pop("DialogueItemView");
			 			 let optionConfig=ChatOptionConfig.GetConfig(config.optionID);
						 item.CreatePlayDialog(optionConfig,info,info.mSelectMap[optionConfig.optionID]);
						 this.scr_playertalk.addChildAt(item,this.laseIndex);
						 this.laseIndex++;
						 item.visible=true;
						 info.lastchatId=config.chatId;
						 let id;
						 if(info.mSelectMap[optionConfig.optionID]==1){
							 id=optionConfig.nextChat1;
							 info.LastSentence=optionConfig.optionContent1;
						 }
						 if(info.mSelectMap[optionConfig.optionID]==2){
							 id=optionConfig.nextChat2;
							  info.LastSentence=optionConfig.optionContent2;
						 }
			 			 if(info.mSelectMap[optionConfig.optionID]==3){
							 id=optionConfig.nextChat3;
							  info.LastSentence=optionConfig.optionContent3;
						 }
			 			 if(info.mSelectMap[optionConfig.optionID]==4){
							 id=optionConfig.nextChat4;
							  info.LastSentence=optionConfig.optionContent4;
						 }
						 this.CreateLastTalk(id,info,false);
					}else{
						 let item: DialogueItemView=	ObjectPool.pop("DialogueItemView");
						 item.UpdateInfo(config,info);
						 info.lastchatId=config.chatId;
						 info.LastSentence=config.content;
						 item.visible=true;
						if(this.isOpenPlayer){
						this.scr_playertalk.removeChild(this.tab_filling);
						this.tab_filling.visible=false;
						}
						 this.scr_playertalk.addChildAt(item,this.laseIndex);
						 this.laseIndex++;
						if(this.isOpenPlayer){
						this.scr_playertalk.addChild(this.tab_filling);
						this.tab_filling.visible=true;
						}
						item.SetChatText();
						if(config.nextId!=0)
							this.CreateLastTalk(config.nextId,info,isDelay);
						}
					}
			   
			}else{
				console.log("dont find ChatConfig!");
			}
		}else{
			//聊天结束
			info.CurrentStatus=WeChatGroupStatus.Triggered;
			this.btn_sent.visible=false;
			let dividingLine:eui.Image=new eui.Image();
			dividingLine.source="image_wuchatline_png";
			dividingLine.width=this.width*0.6;
			dividingLine.explicitWidth=100;
			this.laseIndex++;
			this.scr_playertalk.addChildAt(dividingLine,this.laseIndex);
		}
	}

	/**
	 * 输入框点击
	 */
	public OpenBtnClickEvent(){
		if(this.isPlayerTalk){
			this.PlayerGroupOperating(!this.isOpenPlayer);
		}
	}

	/**
	 * 发送按钮
	 */
	public SendBtnClickEvent(){
			
		if(this.isPlayerTalk){
			 this.isPlayerTalk=false;
			 let item: DialogueItemView=ObjectPool.pop("DialogueItemView");
			 let config=ChatOptionConfig.GetConfig(this.currentOptionId);
			 item.CreatePlayDialog(config,this.currentInfo,this.currentSelectIndex);
			 this.currentInfo.mSelectMap[this.currentOptionId]=this.currentSelectIndex;
			 this.scr_playertalk.addChild(item);
			 item.visible=true;
			 let id;
			 if(this.currentSelectIndex==1){
				 id=config.nextChat1;
				 this.currentInfo.LastSentence=config.optionContent1;
			 }
			  if(this.currentSelectIndex==2){
				 id=config.nextChat2;
				  this.currentInfo.LastSentence=config.optionContent2;
			 }
			  if(this.currentSelectIndex==3){
				 id=config.nextChat3;
				  this.currentInfo.LastSentence=config.optionContent3;
			 }
			  if(this.currentSelectIndex==4){
				 id=config.nextChat4;
				this.currentInfo.LastSentence=config.optionContent4;
			 }
			 this.SetScrend();
			 this.currentInfo.AddToPast(this.currentChatId);
			 this.CreateTalk(id,this.currentInfo,true);
			 this.PlayerGroupOperating(false);
			 this.btn_sent.visible=false;
			 this.label_choose.visible=false;
			 if(this.toggle1)
			 this.toggle1.selected=false;
			  if(this.toggle2)
			 this.toggle2.selected=false;
			  if(this.toggle3)
			 this.toggle3.selected=false;
			  if(this.toggle4)
			 this.toggle4.selected=false;
		}
	}

	/**
	 * 重置ui
	 */
	public ReSetUI(){
		this.isPlayerTalk=false;
		this.btn_sent.visible=false;
		this.Group_player.y=this.oriHeight+this.tab_height;
		this.isOpenPlayer=false;
		this.label_choose.visible =false;
		
		let childs:egret.DisplayObject[]=[];
		for(let i=0;i<this.scr_playertalk.numElements;i++){
			let child=	this.scr_playertalk.getChildAt(i) ;
			if(child){
			ObjectPool.push(child as DialogueItemView);
			childs.push(child);
			}
		}
		childs.forEach(element => {
			this.scr_playertalk.removeChild(element);
		});
		 App.TimerManager.removeAll(this);
		 this.scr_talk.validateNow();
		 this.scr_talk.viewport.scrollV =0;
	}
	
	/**
	 * 打开或关闭选项卡
	 */
	public PlayerGroupOperating(open:boolean,timer:number=100){
		if(open==this.isOpenPlayer){
			return;
		}else{
		this.isOpenPlayer=open;
		let targetY;
		let scrollY;
		if(open){
			targetY=this.oriHeight;
			this.scr_playertalk.addChild(this.tab_filling);
			this.tab_filling.visible=true
		}else{
			targetY=this.oriHeight+this.tab_height;
			this.scr_playertalk.removeChild(this.tab_filling);
			this.tab_filling.visible=false;
		}
		
		egret.Tween.get(this.Group_player, {loop: false, onChangeObj: this})
		.to({y:targetY},timer);

		this.SetScrend();
		}
	}

	/**
	 * 生成聊天
	 */
	public CreateTalk(id:number,info:WechatGroupInfo,isDelay:boolean){
		if(!this.isShow()) return ;
		if(id!=-1){
			let config:ChatConfig=ChatConfig.GetConfig(id);
			
			if(config){
			
				if(info.CurrentStatus==WeChatGroupStatus.ActivationNotTrigger&&!info.FindPastChat(id)){//未触发
				if(config.type==DialogType.Player){
					//未触发己方发言
					if(config.optionID!=0){
								this.currentOptionId=config.optionID;
								this.currentChatId=id;
								this.CreateTabItem(config.optionID);
								this.isPlayerTalk=true;	
								this.PlayerGroupOperating(true);
								this.SetScrend();
						}else{
							console.log("ChatConfig optionID null!");
						}

				}else{

					//未触发对方发言
					if(isDelay){
						this. DelayAction(config,info,true);
					}else{
						this.DirectAction(config,info,true);
					}	
				}
				}else{
					if(config.type==DialogType.Player){
						 let item: DialogueItemView=ObjectPool.pop("DialogueItemView");
			 			 let optionConfig=ChatOptionConfig.GetConfig(config.optionID);
						 item.CreatePlayDialog(optionConfig,info,info.mSelectMap[optionConfig.optionID]);
						 this.scr_playertalk.addChild(item);
						 item.visible=true;
						 info.lastchatId=config.chatId;

						 let id;
						 if(info.mSelectMap[optionConfig.optionID]==1){
							 id=optionConfig.nextChat1;
							 info.LastSentence=optionConfig.optionContent1;
						 }
						 if(info.mSelectMap[optionConfig.optionID]==2){
							  id=optionConfig.nextChat2;
							  info.LastSentence=optionConfig.optionContent2;
						 }
			 			 if(info.mSelectMap[optionConfig.optionID]==3){
							  id=optionConfig.nextChat3;
							  info.LastSentence=optionConfig.optionContent3;
						 }
			 			 if(info.mSelectMap[optionConfig.optionID]==4){
							  id=optionConfig.nextChat4;
							  info.LastSentence=optionConfig.optionContent4;
						 }
						 info.AddToPast(config.chatId);
						 this.SetScrend();
						 this.CreateTalk(id,info,false);
					}else{
						this.DirectAction(config,info,false);
					}
			   }
			   
			}else{
				console.log("dont find ChatConfig!");
			}
		}else{
			//聊天结束
			info.CurrentStatus=WeChatGroupStatus.Triggered;
			this.btn_sent.visible=false;
			let dividingLine:eui.Image=new eui.Image();
			dividingLine.source="image_wuchatline_png";
			dividingLine.width=this.width*0.6;
			dividingLine.explicitWidth=100;
			this.scr_playertalk.addChild(dividingLine);
		}
	}

	/**
	 * 直接执行
	 */
	public DirectAction(config:ChatConfig,info:WechatGroupInfo,isDelay:boolean){
				 let item: DialogueItemView=	ObjectPool.pop("DialogueItemView");
				 item.UpdateInfo(config,info);
				 info.lastchatId=config.chatId;
				 info.AddToPast(config.chatId);
				 info.LastSentence=config.content;
				 item.visible=true;
				if(this.isOpenPlayer){
				this.scr_playertalk.removeChild(this.tab_filling);
				this.tab_filling.visible=false;
				}
				this.scr_playertalk.addChild(item);
				if(this.isOpenPlayer){
				this.scr_playertalk.addChild(this.tab_filling);
				this.tab_filling.visible=true;
				}
				item.SetChatText();
 				this.SetScrend();
				 if(config.nextId!=0)
					this.CreateTalk(config.nextId,info,isDelay);
	}

	/**
	 * 延时
	 */
	public DelayAction(config:ChatConfig,info:WechatGroupInfo,isDelay:boolean){
			 App.TimerManager.doTimer(500, 1,function(){
				
				 let item: DialogueItemView=	ObjectPool.pop("DialogueItemView");
				 item.UpdateInfo(config,info);
				 item.visible=true;

				  let delay:number=parseFloat( ClientConstConfig.GetConfig(6).value)*1000;
				  let multiple:number=((item.mconfig.content.length/10)-1) *( parseFloat( ClientConstConfig.GetConfig(7).value))*1000;
				  delay+=multiple;
				  let count :number=delay/500;

				if(this.isOpenPlayer){
				this.scr_playertalk.removeChild(this.tab_filling);
				this.tab_filling.visible=false;
				}
				this.scr_playertalk.addChild(item);
				if(this.isOpenPlayer){
				this.scr_playertalk.addChild(this.tab_filling);
				this.tab_filling.visible=true;
				}
				this.SetScrend();

				App.TimerManager.doTimer(delay/count,count,
				 function(){//设置等待输入
					 item.SetWaitInput();
				 }.bind(this) , this,0,
				 function(){//设置文字
					 item.SetChatText();
 					 this.SetScrend();
					 info.AddToPast(config.chatId);
					 info.LastSentence=config.content;
					 this.CreateTalk(config.nextId,info,isDelay);
				 }.bind(this),this);
				 }.bind(this), this);		 
	}
	
	/**
	 * 滚动条置底
	 */
	public SetScrend(){
 		 this.scr_talk.validateNow();
		 if(this.scr_talk.viewport.contentHeight>this.scr_talk.viewport.height)
		 this.scr_talk.viewport.scrollV = this.scr_talk.viewport.contentHeight - this.scr_talk.viewport.height;
	}


	/**
	 * 生成选项卡
	 */
	public CreateTabItem(option:number){
		let optionConfig:ChatOptionConfig=ChatOptionConfig.GetConfig(option);
		if(optionConfig){
			if(optionConfig.optionContent1){
				if(!this.toggle1){
				this.toggle1=new eui.RadioButton();
				this.toggle1.skinName="resource/eui_skins/DialogViewRadioButtonSkin.exml";
				}
				this.toggle1.visible=true;
				let str:string = optionConfig.optionContent1;
				if(str.length>18){
					str=str.substring(0,18)+"...";
				}
				this.toggle1.label=str;
				this.toggle1.value=1;
				this.toggle1.group=this.radioGroup;
				this.tab_group.addChild(this.toggle1);
			}else{
				if(this.toggle1){
				let index=	this.tab_group.getChildIndex(this.toggle1);
					if(index!=-1)	
					this.tab_group.removeChildAt(index);
				}
			}

			if(optionConfig.optionContent2){
				if(!this.toggle2){
					this.toggle2=new eui.RadioButton();
					this.toggle2.skinName="resource/eui_skins/DialogViewRadioButtonSkin.exml";
				}
				let str:string = optionConfig.optionContent2;
				if(str.length>18){
					str=str.substring(0,18)+"...";
				}
				this.toggle2.label=str;
				this.toggle2.value=2;
				this.toggle2.group=this.radioGroup;
				this.tab_group.addChild(this.toggle2);
			}else{
				if(this.toggle2){
				let index=	this.tab_group.getChildIndex(this.toggle2);
					if(index!=-1)	
					this.tab_group.removeChildAt(index);
				}
			}

			if(optionConfig.optionContent3){
				if(!this.toggle3){
					this.toggle3=new eui.RadioButton();
					this.toggle3.skinName="resource/eui_skins/DialogViewRadioButtonSkin.exml";
				}
				let str:string = optionConfig.optionContent3;
				if(str.length>18){
					str=str.substring(0,18)+"...";
				}
				this.toggle3.label=str;
				this.toggle3.value=3;
				this.toggle3.group=this.radioGroup;
				this.tab_group.addChild(this.toggle3);
			}else{
				if(this.toggle3){
				let index=	this.tab_group.getChildIndex(this.toggle3);
					if(index!=-1)	
					this.tab_group.removeChildAt(index);
				}
			}

			if(optionConfig.optionContent4){
				if(!this.toggle4){
					this.toggle4=new eui.RadioButton();
					this.toggle4.skinName="resource/eui_skins/DialogViewRadioButtonSkin.exml";
				}
				let str:string = optionConfig.optionContent4;
				if(str.length>18){
					str=str.substring(0,18)+"...";
				}
				this.toggle4.label=str;
				this.toggle4.value=4;
				this.toggle4.group=this.radioGroup;
				this.tab_group.addChild(this.toggle4);
			}else{
				if(this.toggle4){
				let index=	this.tab_group.getChildIndex(this.toggle4);
					if(index!=-1)	
					this.tab_group.removeChildAt(index);
				}
			}
		}else{
			console.log("dont find ChatOptionConfig || toggle1 null");
		}
	}
	
	/**
	 * 选项切换
	 */
 	 private radioChangeHandler(evt:eui.UIEvent):void {
		  let btnGroup:eui.RadioButtonGroup=evt.target;
		  this.btn_sent.visible=true;
	      this.label_choose.visible=true;
		  this.currentSelectIndex=btnGroup.selectedValue; 
		  let text:string = btnGroup.selection.label;
		if(text.length>10){
		text=text.substr(0,9)+"...";
		}
		this.label_choose.text=text;
	}

}

/**
 * 玩家或ai发言
 */
enum DialogType{
	Player,
	Ai
}

/**
 * 对话条
 */
class DialogueItemView extends eui.Component{

	private root_Group:eui.Group;
	private root_oriHeight:number;

	private left_group:eui.Group;
	private left_playericon:eui.Image;//头像
	private left_frame:eui.Image;//头像边框
	private left_talkdi:eui.Image;//聊天背景
	private left_talkdi1:eui.Image;//小三角
	private left_label:eui.Label;//聊天文本
	private left_audio_play:eui.Button;//音效播放
	private left_dialoggroup:eui.Group;
	private left_name:eui.Label;//对方名称
	private	left_audioImage:eui.Image;

	private right_group:eui.Group;
	private right_playericon:eui.Image;//头像
	private right_dialoggroup:eui.Group;
	private right_frame:eui.Image;//头像边框
	private right_talkdi:eui.Image;//聊天背景
	private right_label:eui.Label;//聊天文本
	private right_audio_play:eui.Button;//音效播放
	public mconfig:ChatConfig;//聊天表
	private pointList:string =".";
	private count:number=0;
	private audioNames:string[]=["image_voice1_png","image_voice2_png","image_voice3_png"];
	private imageIndex=0;
	private isPlay:boolean=false;//
	private currentSound:egret.Sound;

	public constructor(){
		super();
		this.skinName="resource/skins/Wechat_talk_dialogue_item.exml";
		this.root_oriHeight=this.root_Group.height;
			this.left_audio_play.addEventListener(egret.TouchEvent.TOUCH_TAP,function(){
					
					if(!this.isPlay){
						  App.SoundManager.stopChat();
						  App.SoundManager.playChat(this.mconfig.voice,(sound:egret.Sound)=>this.UpdateAudioBtn(sound),()=>this.StopSound());
						  this. SetImageAuto();
					}else{
						if(this.currentSound){
							 this.StopSound();
						}
					}
				 
			}.bind(this),this);
	}

	/**
	 * 播放或暂停
	 */
	private  UpdateAudioBtn(sound:egret.Sound){
		if(sound){
			this.currentSound=sound;
			this.isPlay=true;
			let lasting:number =sound.length;
		App.TimerManager.doTimer(lasting*1000,1,function(){
					App.SoundManager.stopChat();
		}.bind(this),this);

		App.TimerManager.doTimer(500,0,function(){
				this.SetImageAuto();
		}.bind(this),this);
		}
	} 

	/**
	 * 设置图片
	 */
	private SetImageAuto(){
		this.left_audioImage.source=this.audioNames[this.imageIndex];
		this.imageIndex++;
		this.imageIndex = this.imageIndex % 3;
	}

	/**
	 * 停止播放
	 */
	private StopSound(){
			
				this.isPlay=false;
				this.left_audioImage.source=this.audioNames[2];
				App.TimerManager.removeAll(this);
	}

	/**
	 *  更新非玩家
	 */
	public UpdateInfo(config:ChatConfig,info:WechatGroupInfo){
			this.mconfig=config;
			this.left_group .visible=true;
			this.right_group.visible=false;
			this.left_audio_play.visible=false;
			this.left_label.visible=true;
			this.left_talkdi.visible=true;
			this.left_talkdi1.visible=true;
			this.left_audioImage.visible=false;

			if(this.mconfig.chatType==WeChatGroupType.Flock){
					this.left_name.text=this.mconfig.name;
					this.left_name.visible=true;
			}
			else{
				this.left_name.visible=false;
			}
			
			this.height=this.root_oriHeight;
			this.left_playericon.source=config.head;
			this.SetWaitInput();
			this.UpdateScale();
	}

	/**
	 * 设置等待输入
	 */
	public SetWaitInput(){
		this.count++;
		this.count = this.count % 3;
		let pointStr="";
		for(let i=0;i<=this.count;i++){
			pointStr+=this.pointList;
		}
		this.left_label.text=StrConfig.GetConfig(1007).str+pointStr; 
	}

	/**
	 * 设置ai聊天内容
	 */
	public SetChatText(){
		if(this.mconfig.npcDialogType==1){
				this.left_label.visible=true;
				this.left_talkdi.visible=true;
				this.left_talkdi1.visible=true;
				this.left_audio_play.visible=false;
				this.left_label.text=this.mconfig.content;
				this.UpdateScale();
		}else if(this.mconfig.npcDialogType==2){
				this.left_label.visible=false;
				this.left_talkdi.visible=false;
				this.left_talkdi1.visible=false;
				this.left_audio_play.visible=true;
				this.left_audioImage.visible=true;
				this.left_audioImage.source=this.audioNames[2];
		}
	}

	/**
	 * 更新组件大小
	 */
	public UpdateScale(){
		if(this.left_label.width>this.left_dialoggroup.width){
				this.left_label.width=this.left_dialoggroup.width;
		}
		
		if(this.left_label.height>this.root_Group.height-60){
				this.height=this.left_label.height+80;
		}
		this.left_talkdi.height=this.left_label.height +20;
		this.left_talkdi.width=this.left_label.width+40;
	}


	/**
	 * 生成玩家聊天
	 */
	public CreatePlayDialog(config:ChatOptionConfig,info:WechatGroupInfo,selectId:number=0){
			this.left_group .visible=false;
			this.right_group.visible=true;
			this.right_playericon.source="boy_icon_png";//玩家头像暂时写死
			this.height=this.root_oriHeight;
			this.right_audio_play.visible=false;
			if(selectId==0){

			}else{
				let text:string;
			  if(selectId==1){
				 text=config.optionContent1;
			  }
			 if(selectId==2){
				 text=config.optionContent2;
			  }
			   if(selectId==3){
				 text=config.optionContent3;
			  }
			   if(selectId==4){
				 text=config.optionContent4;
			  }
				this.right_label.text=text;

				if(this.right_label.width>this.right_dialoggroup.width){
				this.right_label.width=this.right_dialoggroup.width;
				}
			
				if(this.right_label.height>this.root_Group.height-60){
					this.height=this.right_label.height+80;
				}
				this.right_talkdi.height=this.right_label.height+20;
				this.right_talkdi.width=this.right_label.width+20;
			}
	}



}