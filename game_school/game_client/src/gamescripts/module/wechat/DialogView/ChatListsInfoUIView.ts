/**
 * 聊天组列表子签
 */
class ChatListsInfoUIView extends BaseEuiChildView
 {
	private talk_Group:eui.Group;//聊天容器
	private frinde_TreeNode_Title:eui.Group;
	private flock_TreeNode_Title:eui.Group;
	private py_talk:eui.Scroller;//滚动条
	private chat_back:eui.Button;//返回
	private btn_friend:eui.Button;//好友列表按钮
	private btn_flock:eui.Button;//群聊列表按钮

	private frientIsOpen:boolean=false;//好友列表是否打开
	private flockIsOpen:boolean=false;//群聊列表是否打开

	private friendItemList:ChatListItem[]=[];//私聊列表
	private flockItemList:ChatListItem[]=[];//群聊列表

	public constructor($controller: BaseController, $parent: eui.Group, key:number) {
		super($controller, $parent, key);
		this.onInitUI();
	}

 private onInitUI():void
 {
	 this.chat_back=this.myParent.getChildByName("chat_back")as eui.Button;
	 this.py_talk=this.myParent.getChildByName("py_talk") as eui.Scroller;
	 this.talk_Group=this.py_talk.getChildByName("talk_Group") as eui.Group;
	 this.frinde_TreeNode_Title=this.talk_Group.getChildByName("frinde_TreeNode_Title") as eui.Group;
 	 this.flock_TreeNode_Title=this.talk_Group.getChildByName("flock_TreeNode_Title") as eui.Group;
	// this.btn_friend=this.frinde_TreeNode_Title.getChildByName("btn_friend")as eui.Button;
	// this.btn_flock=this.flock_TreeNode_Title.getChildByName("btn_flock")as eui.Button;
	 this.chat_back.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>{
		  App.ViewManager.close(this._key);
	 },this)
//	 this.btn_flock.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickBtnEventListener,this);
//	 this.btn_friend.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickBtnEventListener,this);
 }

 /**
  * 打开页面
  */
  public onChildGroupShow():void 
  {
        super.onChildGroupShow();
		this.CleraItem();
		//this.applyFunc(WechatUIConst.InquireChatInfo);
		//this.UpdateList(false,WeChatGroupType.Friend);
		//this.UpdateList(false,WeChatGroupType.Flock);
		App.EventMgrHelper.PushEvent(EventDef.OpenListByType,WeChatGroupType.Friend);
   }

/**
 * 展开或关闭列表
 */
 private OnClickBtnEventListener(event:egret.Event){
	if( event.target ==this.btn_flock){
		this.flockIsOpen=!this.flockIsOpen;
		if(this.flockIsOpen){
			App.EventMgrHelper.PushEvent(EventDef.OpenListByType,WeChatGroupType.Flock);
		}else{
			this.UpdateList(false,WeChatGroupType.Flock);
		}
	}else{
		this.frientIsOpen=!this.frientIsOpen;
		if(this.frientIsOpen){
			App.EventMgrHelper.PushEvent(EventDef.OpenListByType,WeChatGroupType.Friend);
		}else{
			this.UpdateList(false,WeChatGroupType.Friend);
		}
	}
 }


/**
 * 更新列表
 */
 public  UpdateList(open:boolean,type:WeChatGroupType,infos?:ChatOwnList[]){
	if(open){
			if(infos&&infos.length>0){
				let currentList:ChatListItem[]=(type==WeChatGroupType.Friend)?this.friendItemList:this.flockItemList;
				for(let i=0;i<infos.length;i++){
					if(i<length){
						currentList[i].UpdateItem(infos[i]);
					}else{
					let item =	ObjectPool.pop("ChatListItem") as ChatListItem;
					currentList.push(item);
					item.UpdateItem(infos[i]);
					}
					currentList[i].visible=true;
				}
			}else{
				//没有激活的聊天组，待处理
			}
	}else{
		if(type==WeChatGroupType.Flock){
			this.flockItemList.forEach(element => {
				element.visible=false;
				this.talk_Group.removeChild(element);
				ObjectPool.push(element);
			});
			this.flockItemList.splice(0,this.flockItemList.length);
		}else{
			this.friendItemList.forEach(element => {
				element.visible=false;
				this.talk_Group.removeChild(element);
				ObjectPool.push(element);
			});
			this.friendItemList.splice(0,this.friendItemList.length);
		}
	}
	this.UpdateItemViewIndex();
 }

 /**
  * 清空
  */
 public CleraItem(){
		this.flockItemList.forEach(element => {
				this.talk_Group.removeChild(element);
				ObjectPool.push(element);
				element.visible=false;
			});
			this.flockItemList.splice(0,this.flockItemList.length);

			this.friendItemList.forEach(element => {
				this.talk_Group.removeChild(element);
				ObjectPool.push(element);
				element.visible=false;
			});
			this.friendItemList.splice(0,this.friendItemList.length);
 }

 
 /**
  * 更新列表的位置
  */
 public UpdateItemViewIndex(){
	// this.talk_Group.setChildIndex(this.frinde_TreeNode_Title,0);//私聊标题永远在最上
	 for(let i=0;i<this.friendItemList.length;i++){
		 this.talk_Group.addChildAt(this.friendItemList[i],i);
	 }
	//  this.talk_Group.setChildIndex(this.flock_TreeNode_Title,this.friendItemList.length+1);
	//  let indexFlockTitle=this.talk_Group.getChildIndex(this.flock_TreeNode_Title)+1;
	//  for(let i=0;i<this.flockItemList.length;i++){
	// 	 this.talk_Group.addChildAt(this.flockItemList[i],indexFlockTitle+i);
	//  }
 }

}

/**
 * 聊天组item
 */ 
class ChatListItem extends eui.Component{

	private info:ChatOwnList;
	private flockConf:ChatGroupNumConfig;
	private laebl_name:eui.Label;
	private laebl_mess:eui.Label;//最后一句
	private image_newfriend0:eui.Image;//红点
	private image_playericon0:eui.Image;//边框
	private image_playericon:eui.Image;//头像
	private item_btn:eui.Button;//按钮

	public constructor(){
		super();
	     this.skinName = "resource/skins/Wechat_List_Item.exml";
		 this.percentWidth=100;
		 	this.item_btn.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>this.ClickItemBen(),this);
	}

	public UpdateItem(info:ChatOwnList){
		this.info=info;
		if(this.info.currentType==WeChatGroupType.Flock){
			this.flockConf=ChatGroupNumConfig.GetConfig(this.info.ownId);
			this.laebl_name.text=this.flockConf.name;
			this.image_playericon.source=this.flockConf.groupHead;
		}else{
			this.laebl_name.text=info.Owner.GirlName;
			this.image_playericon.source =info.Owner.HeadIcon;
		}
		this.image_newfriend0.visible=this.info.IsExistNoTrigger();
	
		let text:string = this.info.GetLastSentence();
		if(text.length>18){
		text=text.substr(0,16)+"...";
		}
		this.laebl_mess.text=text;
	}

	public ClickItemBen(){
		App.EventMgrHelper.PushEvent(EventDef.OpendialogView,this.info.ownId);
	}



}