/**
 * 通讯录界面
 */
class AddressbookListUIView extends BaseEuiChildView{

	private tongxun_back:eui.Button;//返回
	private py_tongxun:eui.Scroller;//滚动条
	private tongxun_Group:eui.Group;//

	public constructor($controller: BaseController, $parent: eui.Group, key:number) {
		super($controller, $parent, key);
		this.onInitUI();
	}

	private onInitUI():void
 	{
		 this.tongxun_back=this.myParent.getChildByName("tongxun_back") as eui.Button;
		 this.py_tongxun=this.myParent.getChildByName("py_tongxun") as eui.Scroller;
		 this.tongxun_Group=this.py_tongxun.getChildByName("tongxun_Group") as eui.Group; 
		 
		 this.tongxun_back.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>{
		  App.ViewManager.close(this._key);
		 },this)
    }
 
  /**
  * 打开页面
  */
  public onChildGroupShow():void 
  {
        super.onChildGroupShow();
		this.UpdateList();
  }
  
/**
 * 刷新页面
 */
public UpdateList(){
		let itemCount:number=this.tongxun_Group.numElements;
		let tempItem:AddressBookItem;
		for(let i=0;i<App.PlayerManager.OwnGirl.length;i++){
		if(i<itemCount){
			tempItem=this.tongxun_Group.getChildAt(i) as AddressBookItem;
		}else{
			tempItem=ObjectPool.pop("AddressBookItem") as AddressBookItem;
			this.tongxun_Group.addChild(tempItem);
		}
		tempItem.UpdateItem(App.PlayerManager.GetFriendlySortList()[i]);
		tempItem.visible=true;
	   }
}
}

/**
 * 聊天组item
 */ 
class AddressBookItem extends eui.Component{

	private info:GirlInfo;
	private name_label:eui.Label;
	private btn_item:eui.Button;//按钮
	private player:eui.Image;//头像
	private image_wcz:eui.Image;//选择
	private image_quality:eui.Image;//边
	
	public constructor(){
		super();
	     this.skinName = "resource/skins/Wechat_tongxun_item.exml";
		 this.percentWidth=100;
		 this.btn_item.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>this.ClickItemBen(),this);
	}
	
	public UpdateItem(info:GirlInfo){
		this.info=info;
		this.name_label.text=this.info.GirlName;
		this.player.source =this.info.HeadIcon;
	}

	public ClickItemBen(){
		App.EventMgrHelper.PushEvent(EventDef.OpenGirlInfoView,this.info.GirlId);
	}
}