/**
 * 聊天记录
 */
class WeChatHistoryUIView extends BaseEuiView {
	
	public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);
    }

	private btn_chatback:eui.Button;
	private scr_playertalk:eui.Group;

	public initUI():void{
		super.initUI();
		this.skinName=App.ViewManager.getSkin(ViewConst.historyView);
		this.btn_chatback.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>{
			App.ViewManager.close(this._key);
		},this);
	}


	public open(...param: any[]): void 
    {
        super.open(param);
    }

	public InitView(girlChat:WechatGroupInfo[]){
		if(!girlChat) return;
		let num:number=this.scr_playertalk.numElements;
		for(let j=0;j<num;j++){
			let item:HistoryItem;
			if(j<girlChat.length){
				item=this.scr_playertalk.getChildAt(j) as HistoryItem;
				item.visible=true;
				item.UpdateItem(girlChat[j]);
			}else{
				item=this.scr_playertalk.getChildAt(this.scr_playertalk.numElements-1) as HistoryItem;
				item.visible=false;
				ObjectPool.push(item);
				this.scr_playertalk.removeChild(item);
			}
		}
		
		let index:number=this.scr_playertalk.numElements;
		for(let y=index;y<girlChat.length;y++){
			let item:HistoryItem=ObjectPool.pop("HistoryItem");
			item.UpdateItem(girlChat[y]);
			item.visible=true;
			this.scr_playertalk.addChild(item);
		}
	}



}

/**
 * 聊天记录item
 */
class HistoryItem extends BaseEuiView{

	public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);
		this.skinName="resource/skins/Wechat_history_item.exml";
		this.btn_choose.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickChooseBtn,this);
    }

	private label_name :eui.Label;
	private btn_choose:eui.Button;
	private info:WechatGroupInfo;

	public UpdateItem(info:WechatGroupInfo){
			this.info=info;
			this.label_name.text=info.mChatConfig.chatName;
	}

	private OnClickChooseBtn(){
			App.ViewManager.close(ViewConst.historyView);
			App.EventMgrHelper.PushEvent(EventDef.OpendialogViewByChatId,this.info.OwnObjId,this.info.ID);
	}

}