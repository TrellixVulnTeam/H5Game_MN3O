class GrilDetailedInfoUiView extends BaseEuiView{
 
	private btn_chatback:eui.Button;

	private image_player:eui.Image;//头像
	private image_bian:eui.Image;//边框
	private label_name:eui.Label;//名称
	private label_blood_type:eui.Label;//血型
	private label_star:eui.Label;//星座
	private btn_huanyuan:eui.Button;//名称还原
	private btn_xiugai:eui.Button;//名称修改
	private change_name:eui.Group;//名称修改区
	private change_inputtext:eui.EditableText;//修改输入框
	private btn_ok:eui.Button;//输入确认按钮
	private xuanzhuan:egret.tween.TweenGroup;//放大动画
	private back:egret.tween.TweenGroup;//缩小动画

	private label_rank:eui.Label;//友好度
	private progre:eui.ProgressBar;//进度条

	private scr_talk:eui.Scroller;//朋友圈历史滚动条
	private scr_playertalk:eui.Group;//历史容器

	private btn_chat:eui.Button;//聊天记录
	private btn_history:eui.Button;//聊天 

	private enlarge_Image:eui.Image;//放大图片
	private enlarge_group:eui.Group;//放大容器

	private imagelist_group:eui.Group;//大图列表
	private left_image:eui.Image;
	private middle_image:eui.Image;
	private right_image:eui.Image;

	private currentGirl:GirlInfo;

	private oriImageX:number;//原始位置
	private offsetX:number;
	private isMove:boolean;
	private disExtent:number=150;//
	private images:string[];
	private currentIndex:number=0;

 	public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);
    }

	public initUI():void{
		super.initUI();
	this.skinName=App.ViewManager.getSkin(ViewConst.GrilInfo);
	this.oriImageX=this.imagelist_group.x;
	this.enlarge_group.visible=false;
	this.imagelist_group.visible=false;

	// for(let i=0;i<this.imagelist_group.numElements;i++){
	// 	this.imagelist_group.getChildAt(i).width=this.height;
	// 	this.imagelist_group.getChildAt(i).height=this.width;
	// }

	this.btn_chatback.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>{
		App.EventMgrHelper.PushEvent(EventDef.CloseGirlInfoView);
	},this);

	this.btn_ok.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickEnterBtnEventHandler,this);
	this.btn_huanyuan.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickReductionBtnEventHandler,this);
	this.btn_xiugai.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickChangeBtnEventHandler,this);
	this.btn_chat.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickChatBtnEventHandler,this);
	this.btn_history.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickhistoryBtnEventHandler,this);
	this.change_inputtext.addEventListener(egret.TouchEvent.TOUCH_TAP,function(){
		this.change_inputtext.text="";
	}.bind(this),this);

	this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_TAP,this.ZoomoutImage,this);

	this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_BEGIN,this.StartMove,this);
	this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_END,this.StopMove,this);
	this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_RELEASE_OUTSIDE,this.StopMove,this);
}

private StartMove(e:egret.TouchEvent){
	this.offsetX=e.stageX;
	this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_MOVE,this.OnMove,this);
}

private StopMove(e:egret.TouchEvent){
	 let tempDis=e.stageX-this.offsetX;
	
	 let absDis=(tempDis>0)?tempDis:-tempDis;

	if(absDis>this.disExtent){
		if(tempDis>0){//→
			let imagename:string =this.GetBeforeImage();
			if(imagename!=""){
				  egret.Tween.get(this.imagelist_group, {loop: false, onChangeObj: this})
                    .to({ x: 0}, 300)
                    .call(() => {
						this.enlarge_Image.source=imagename;
						this.UpdateImage();
						this.imagelist_group.x=this.oriImageX;
                    });	
			}
		
		}else{//←
			let imagename:string =this.GetNextImage();
			if(imagename!=""){
				  egret.Tween.get(this.imagelist_group, {loop: false, onChangeObj: this})
                    .to({ x: -(this.middle_image.height*2)}, 300)
                    .call(() => {
						this.enlarge_Image.source=imagename;
						this.UpdateImage();
						this.imagelist_group.x=this.oriImageX;
                    });	
			}
		}
	}else{
		this.imagelist_group.x=this.oriImageX;
	}
}

private OnMove(e:egret.TouchEvent){
	if(!this.isMove)
	this.isMove=true;

	let tempOffset:number=	e.stageX-this.offsetX;

	if(tempOffset>0){//→
			if(this.currentIndex>0){
				this.imagelist_group.x=this.oriImageX+tempOffset;
			}
	}else{//←
			if(this.currentIndex<this.images.length-1){
				this.imagelist_group.x=this.oriImageX+tempOffset;
			}
	}
}

public GetNextImage():string{
	if(this.currentIndex<(this.images.length-1)){
		this.currentIndex++;
		return this.images[this.currentIndex];
	}
	return "";
}

public GetBeforeImage():string{
	if(this.currentIndex>0){
		this.currentIndex--;
		return this.images[this.currentIndex];
	}
	return "";
}

/**
 * 缩小图片
 */
public ZoomoutImage(){
	if(!this.isMove){
		this.imagelist_group.visible=false;
		this.enlarge_Image.visible=true;
		this.back.play(0);
			App.TimerManager.doTimer(250,1,function(){
					this.enlarge_group.visible=false;
			}.bind(this),this);
	}else{
		this.isMove=false;
	}
}

/**
 * 放大
 */
public EnlargeImage(imagename:string){
	this.isMove=false;
	if(imagename!=""){
		let index=this.images.indexOf(imagename);
		if(index==-1){
			return ;
		}
		this.currentIndex=index;
		this.enlarge_Image.source=imagename;
		this.enlarge_group.visible=true;
		this.xuanzhuan.play(0);
		
		App.TimerManager.doTimer(250,1,function(){
			
			this.UpdateImage();
			this.enlarge_Image.visible=false;
			this.imagelist_group.visible=true;
			this.imagelist_group.height=this.height;
			this.imagelist_group.width=this.width*3;
			 
		}.bind(this),this);
	}
}

private UpdateImage(){
			this.middle_image.source=this.images[this.currentIndex];

			if(this.currentIndex>0)
			this.left_image.source=this.images[this.currentIndex-1];

			if(this.currentIndex<this.images.length-1)
			this.right_image.source=this.images[this.currentIndex+1];
}



/**
 *  聊天记录
 */
private OnClickhistoryBtnEventHandler(){
		App.EventMgrHelper.PushEvent(EventDef.OpenHistoryView,this.currentGirl.GirlId);
}

/**
 * 前往聊天
 */
private OnClickChatBtnEventHandler(){
	App.EventMgrHelper.PushEvent(EventDef.OpendialogView,this.currentGirl.GirlId,WechatUIType.Wechat_record);
}

/**
 * 改名确认
 */
private OnClickEnterBtnEventHandler(){
	if(this.change_inputtext){
		let text:string =this.change_inputtext.text;
		let tips:string =StrConfig.GetConfig(11033).str;
		if(text.length>0&&text!=tips){
			this.change_name.visible=false;
			this.label_name.visible=true;
			this.label_name.text=text;
			this.currentGirl.GirlName=text;
		}else{
			this.change_inputtext.text=tips;
		}
	}
}

/**
 * 名称还原
 */
private OnClickReductionBtnEventHandler(){
	this.label_name.visible=true;
	this.label_name.text=this.currentGirl.Config.name;
	this.currentGirl.GirlName=this.currentGirl.Config.name;
}

/**
 * 名称修改
 */
private OnClickChangeBtnEventHandler(){
	if(!this.change_name.visible){
      this.change_name.visible=true;
	  this.change_inputtext.text="";
	  this.label_name.visible=false;
	}else{
	   this.change_name.visible=false;
	   this.label_name.visible=true;
	}
}

/**
 * 初始化
 */
public InitViewInfo(gridId:number){

	if(gridId)
	{
		this.change_name.visible=false;
		this.currentGirl=App.PlayerManager.GetGirl(gridId);
		this.image_player.source=this.currentGirl.Config.icon;
		this.label_name.text=this.currentGirl.GirlName;
		this.label_blood_type.text=this.currentGirl.Config.bloodType;
		this.label_star.text=this.currentGirl.Config.constellation;
		let upperLimit:number=	parseInt(PublicConstConfig.GetConfig(5).value);
		this.label_rank.text=this.currentGirl.FriendlyNum.toString();
		this.progre.value=(this.currentGirl.FriendlyNum/upperLimit)*100;
	
		this.images=[];
		for(let i =0;i<App.WechatManager.AlreadyAnnIds.length;i++){
			let config:WechatConfig=	WechatConfig.GetConfig(App.WechatManager.AlreadyAnnIds[i]);
			if(config){
				if(config.personID==this.currentGirl.GirlId){
					this.images.push(config.pic);
				}
			}
		}	

		
		let num:number=this.scr_playertalk.numElements;
		for(let j=0;j<num;j++){
			let item:FriendcircleImageItem;
			if(j<this.images.length){
				item=this.scr_playertalk.getChildAt(j) as FriendcircleImageItem;
				item.visible=true;
				item.UpdateItem(this.images[j],(imageName)=>this.EnlargeImage(imageName));
			}else{
				item=this.scr_playertalk.getChildAt(this.scr_playertalk.numElements-1) as FriendcircleImageItem;
				item.visible=false;
				ObjectPool.push(item);
				this.scr_playertalk.removeChild(item);
			}
		}
		
		let index:number=this.scr_playertalk.numElements;
		for(let y=index;y<this.images.length;y++){
			let item:FriendcircleImageItem=ObjectPool.pop("FriendcircleImageItem");
			item.UpdateItem(this.images[y],(imageName)=>this.EnlargeImage(imageName));
			item.visible=true;
			this.scr_playertalk.addChild(item);
		}
	}
}

}

/**朋友圈图片 */
 class FriendcircleImageItem extends eui.Component{
	 	private back_Image:eui.Image;
		private root_btn:eui.Button;
		private root_Group:eui.Group;

		private imageName:string="";
		private OnClickRootBtnEvent:Function;

	 	public constructor(){
		super();
		this.skinName="resource/skins/Friendcircle_Image.exml";
		this.root_btn.addEventListener(egret.TouchEvent.TOUCH_TAP,this.rootBtnClick,this);
		}

		public rootBtnClick(){
			this.OnClickRootBtnEvent(this.imageName);
		}

		public UpdateItem(imageName:string,itemClickCallback:Function){
			this.imageName=imageName;
			this.back_Image.source=this.imageName;
			this.OnClickRootBtnEvent=itemClickCallback;
		}

}

