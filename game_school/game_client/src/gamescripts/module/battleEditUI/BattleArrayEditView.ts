/**
 * 布阵界面
 */
class BattleArrayEditView extends BaseEuiView {

	private btn_back: eui.Button;//返回
	private listGroup: eui.Group;//列表容器
	private playermove: eui.Group;//移动层
	private btn_teamchoose: eui.Button;//选择当前队伍

	private gro_btn: eui.Button;
	private btn_team1: eui.RadioButton;
	private btn_team2: eui.RadioButton;
	private btn_team3: eui.RadioButton;

	/**
	 * 临时指引标记
	*/
	private isFirstGuide = false;
	private isSecondGuide = false;
	private isThirdGuide = false;
	private isFourthGuide = false;

	public constructor($controller: BaseController, $parent: eui.Group) {
		super($controller, $parent);
	}

	public initUI(): void {
		super.initUI();
		this.skinName = App.ViewManager.getSkin(ViewConst.BattleArray);

		this.isFirstGuide = App.GuideManager.getIsGuide;
		this.isSecondGuide = App.GuideManager.getIsGuide;
		this.isThirdGuide = App.GuideManager.getIsGuide;
		this.isFourthGuide = App.GuideManager.getIsGuide;

		this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
			App.ViewManager.open(ViewConst.Chapter);
			App.ViewManager.close(ViewConst.BattleArray);
		}, this);

		this.CreateItem();

		this.playermove.touchEnabled = false;
		var radioGroup: eui.RadioButtonGroup = new eui.RadioButtonGroup();
		radioGroup.addEventListener(eui.UIEvent.CHANGE, this.radioChangeHandler, this);
		this.btn_team1.value = BelongArray.Array1;
		this.btn_team2.value = BelongArray.Array2;
		this.btn_team3.value = BelongArray.Array3;
		this.btn_team1.group = radioGroup;
		this.btn_team2.group = radioGroup;
		this.btn_team3.group = radioGroup;
		this.btn_team1.selected = true;


		this.btn_teamchoose.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
			App.ViewManager.close(ViewConst.BattleArray);
			App.ViewManager.open(ViewConst.Chapter);
		}, this);

		App.EventMgrHelper.PushEvent(EventDef.ChangeTeam,BelongArray.Array1);
	}

	/**选项卡监听 */
	private radioChangeHandler(evt: eui.UIEvent): void {
		var radioGroup: eui.RadioButtonGroup = evt.target;
		App.EventMgrHelper.PushEvent(EventDef.ChangeTeam,radioGroup.selectedValue);
	}

	/**
	 * 切换队伍
	 */
	public ChangeTeam(teamInfo: HeroInfo[]) {
		for (let i = 0; i < this.listGroup.numElements; i++) {
			let tempItem: HeroArrayItem = this.listGroup.getChildAt(i) as HeroArrayItem;
			if (tempItem) {
				if (tempItem.indexPos <= parseInt(PublicConstConfig.GetConfig(1).value)) {
					let tempInfo: HeroInfo = this.GetInfoByIndex(tempItem.indexPos, teamInfo);
					if (tempInfo && tempInfo.id != 0) {
						tempItem.UpdateInfo(tempInfo);
					} else {
						tempItem.SetNoIncrease();
					}
				} else {
					tempItem.SetAction(false);
				}
			}
		}

		if (this.isFirstGuide == false && this.isSecondGuide == false && this.isThirdGuide) {
			this.isThirdGuide = false;
			this.addThirdGuide();
		}
	}

	/**
	 * 根据位置获取信息
	 */
	public GetInfoByIndex(index: number, infos: HeroInfo[]): HeroInfo {
		for (let i = 0; i < infos.length; i++) {
			if (infos[i].index == index) {
				return infos[i];
			}
		}
		return null;
	}

	/**
	 * 获取指定下标item
	 */
	public GetItemByIndex(index: number): HeroArrayItem {
		for (let i = 0; i < this.listGroup.numElements; i++) {
			let tempItem: HeroArrayItem = this.listGroup.getChildAt(i) as HeroArrayItem;
			if (tempItem.indexPos == index) {
				return tempItem;
			}
		}
		return null;
	}

	public initData(): void {
		super.initData();
	}

	public open(...param: any[]): void {
		super.open(param);
		//开启ComponentSystem
		ComponentSystem.start();

		if (this.isFirstGuide) {
			this.isFirstGuide = false;
			this.addFirstGuide();
		}
	}

    /**
     * 临时指引1（第一次进入布阵界面, 点击阵型1按钮）
    */
	public addFirstGuide() {
		this.validateNow();
		let mask = new GuideMask(this.btn_team1, () => {
			App.EventMgrHelper.PushEvent(EventDef.ChangeTeam,BelongArray.Array1);
			if (this.isFirstGuide == false && this.isSecondGuide) {
				
				this.addSecondGuide();
			}
		});
		this.addChild(mask);
	}

	/**
     * 临时指引2（点击阵型1按钮后，点击阵型上的第二个位置）
    */
	public addSecondGuide() {
		let item = this.listGroup.getChildAt(0) as HeroArrayItem;
		if (item != null) {
			this.validateNow();
			let mask = new GuideMask(item.image_plus, () => {
				this.isSecondGuide = false;
				App.EventMgrHelper.PushEvent(EventDef.ShowHeroList,item.indexPos);
			});
			this.addChild(mask);
		}
	}

	/**
     * 临时指引3（第二次进入布阵界面，点击退出按钮）
    */
	public addThirdGuide() {
		this.validateNow();
		let mask = new GuideMask(this.btn_back, () => {
			this.onClose();
			this.addFourthGuide();
		}, "", true, 0, -(this.btn_back.height / 2));
		this.addChild(mask);
	}


    /**
     * 临时指引4（点击退出按钮后，播放剧情，播放剧情后打开主界面）
    */
	public addFourthGuide() {
		//临时播剧情
		App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 105, function () {
			App.ViewManager.close(ViewConst.Dialog);
			App.ViewManager.open(ViewConst.MainUI);
		}.bind(this), 0, 0, "", "");
		// App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 105, function () {
		// 	App.ViewManager.close(ViewConst.Dialog);
		// 	App.ViewManager.open(ViewConst.MainUI);
		// });
	}


	/**
	 * 生成item
	 */
	public CreateItem() {
		if (this.listGroup.numElements == 6)
			return;

		for (let i = 0; i < 6; i++) {
			let item: HeroArrayItem = new HeroArrayItem(i, this.playermove, this.width / 3);
			this.listGroup.addChild(item);

			if (item.indexPos <= parseInt(PublicConstConfig.GetConfig(1).value)) {//限制数量，暂时在常量表取
				App.EventMgrHelper.PushEventEx(EventDef.InitArray,true,null,item.indexPos,0,"","");

				item.SetNoIncrease();
			} else {
				App.EventMgrHelper.PushEventEx(EventDef.InitArray,false,null,item.indexPos,0,"","");
				item.SetAction(false);
			}
		}
	}

	/**设置所有添加按钮状态 */
	public SetAddBtnVisible(visible: boolean) {
		for (let i = 0; i < this.listGroup.numElements; i++) {
			let item: HeroArrayItem = this.listGroup.getChildAt(i) as HeroArrayItem;

			if (item && item.action) {
				item.SetAddState(visible);
			}
		}
	}


	/**检测所有站位 */
	public HitCheckAllPoint(target: egret.DisplayObject): HeroArrayItem {
		for (let i = 0; i < this.listGroup.numElements; i++) {
			let item: HeroArrayItem = this.listGroup.getChildAt(i) as HeroArrayItem;
			let tempDis: HeroArrayItem = <HeroArrayItem>this.hitTestP(target, item);
			if (tempDis != null) {
				return tempDis;
			}
		}
		return null;
	}


	/**碰撞检测 */
	public hitTestP(obj1: egret.DisplayObject, obj2: egret.DisplayObject): egret.DisplayObject {
		var rect1: egret.Rectangle = obj1.getBounds();//获取显示对象的测量边界
		let tempItem: HeroArrayItem = obj2 as HeroArrayItem;
		var rect2: egret.Rectangle = tempItem.Base_back.getBounds(); 4

		let point1: egret.Point = this.listGroup.localToGlobal(obj1.x + 400, obj1.y + 200);
		let point2: egret.Point = this.listGroup.localToGlobal(tempItem.x, tempItem.y);

		rect1.x = point1.x;
		rect1.y = point1.y;
		rect2.x = point2.x;
		rect2.y = point2.y;
		if (rect1.intersects(rect2)) {
			return obj2;
		} else {
			return null;
		}
	}
}

/**
 * 英雄item
 */
class HeroArrayItem extends eui.Component {

	public indexPos: number;//位置
	public currentObj: DemonstrationObject;//人物
	public action: boolean;//是否激活
	public posInfo: BattlePosition;//位置
	public id: number;//id

	private rootgroup: eui.Group;//根节点
	private label_position: eui.Label;//位置
	private label_lock: eui.Label;//解锁条件
	private image_lock: eui.Image;//锁图片
	private group_player: eui.Group;//人物容器
	public image_plus: eui.Button;//加号图片
	public btn_add: eui.Button;//添加按钮
	private rootView: egret.DisplayObjectContainer;//列表
	private base_back: eui.Image;
	private point_back: eui.Image;
	private player_image: eui.Image;//玩家

	private isMove: boolean = false;
	private offsetX: number;
	private offsetY: number;

	private oriPoint: egret.Point = new egret.Point();//玩家原始位置

	public constructor(index: number, rootView: egret.DisplayObjectContainer, width: number) {
		super();

		this.skinName = App.ViewManager.getSkin(ViewConst.ArrayItem);

		this.oriPoint.x = this.player_image.x;
		this.oriPoint.y = this.player_image.y;
		this.width = width;
		this.player_image.width = width;
		this.rootView = rootView;
		this.rootgroup.touchEnabled = false
		this.group_player.touchEnabled = false;
		this.base_back.touchEnabled = false;
		this.point_back.touchEnabled = false;

		//this.ConvertIndex(index)
		this.indexPos = index + 1;
		let backImgName: string = this.base_back.source.toString();
		let pndIndex: number = backImgName.indexOf("_png");
		backImgName = backImgName.substring(0, pndIndex - 1) + this.indexPos + "_png";
		this.base_back.source = backImgName;

		this.label_position.text = this.indexPos.toString();
		this.btn_add.removeEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickAddBtn, this);
		this.btn_add.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickAddBtn, this);

		this.player_image.removeEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickAddBtn, this);
		this.player_image.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickAddBtn, this);

		this.player_image.removeEventListener(egret.TouchEvent.TOUCH_BEGIN, this.StartMove, this);
		this.player_image.addEventListener(egret.TouchEvent.TOUCH_BEGIN, this.StartMove, this);

		this.player_image.removeEventListener(egret.TouchEvent.TOUCH_END, this.StopMove, this);
		this.player_image.addEventListener(egret.TouchEvent.TOUCH_END, this.StopMove, this);

		this.player_image.removeEventListener(egret.TouchEvent.TOUCH_RELEASE_OUTSIDE, this.StopMove, this);
		this.player_image.addEventListener(egret.TouchEvent.TOUCH_RELEASE_OUTSIDE, this.StopMove, this);
	}

	public StartMove(e: egret.TouchEvent) {

		let pos: egret.Point = this.player_image.localToGlobal(this.player_image.x, this.player_image.y);//转成世界坐标

		this.rootView.addChild(this.player_image);
		//this.rootgroup.removeChild(this.player_image);
		let localPos: egret.Point = this.player_image.globalToLocal(pos.x, pos.y);//世界坐标转本地坐标
		this.player_image.x = localPos.x;
		this.player_image.y = localPos.y;

		this.offsetX = e.stageX - this.player_image.x;
		this.offsetY = e.stageY - this.player_image.y;

		this.player_image.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.OnMove, this);

	}

	public StopMove(e: egret.TouchEvent) {
	
		App.EventMgrHelper.PushEventEx(EventDef.CheckCollision,this,this.player_image,0,0,"","");

		this.rootgroup.addChild(this.player_image);
		this.BackInPlace();
		this.player_image.removeEventListener(egret.TouchEvent.TOUCH_MOVE, this.OnMove, this);
	}

	public OnMove(e: egret.TouchEvent) {
		if (!this.isMove) this.isMove = true;
		this.player_image.x = e.stageX - this.offsetX;
		this.player_image.y = e.stageY - this.offsetY;
	}

	//返回
	public BackInPlace() {
		this.player_image.x = this.oriPoint.x;
		this.player_image.y = this.oriPoint.y;
	}

	/**
	 * 设置出站
	 */
	public UpdateInfo(info: HeroInfo) {
		//this.group_player.visible=true;
		this.image_plus.visible = false;
		this.player_image.visible = true;
		this.SetAction(true);
		if (this.id != info.id) {
			this.id = info.id;
			// this.posInfo=new BattlePosition();
			// let Pos:egret.Point=new egret.Point(0,this.group_player.y*0.5);
			// this.posInfo.InitDisPos(this.indexPos,Pos);
			// if(this.currentObj){
			// 	this.currentObj.Death();
			// 	ObjectPool.push(this.currentObj);
			// 	this.currentObj=null;
			// }
			// this.currentObj = ObjectPool.pop("DemonstrationObject");
			// this.currentObj.init(info.id,this.posInfo,Camp.Friendly,this.group_player,this.rootView);
			let modelConfig = ModelConfig.GetConfig(CreatureTempletConfig.GetConfig(info.id).model);
			if (modelConfig) {
				this.player_image.source = modelConfig.animation;
				this.player_image.x = this.oriPoint.x;
				this.player_image.y = this.oriPoint.y;
			}
		}
	}

	/**
	 * 设置未出战
	 */
	public SetNoIncrease() {
		this.SetAction(true);
		this.group_player.visible = false;
		this.image_plus.visible = true;
		this.player_image.visible = false;
		this.id = 0;
	}

	/**
	 * 设置按钮状态
	 */
	public SetAddState(state: boolean) {
		if (this.btn_add && this.btn_add.visible != state) {
			this.btn_add.touchEnabled = state;
			this.btn_add.visible = state;
		}
	}

	/**
	 * 添加按钮点击事件
	 */
	private OnClickAddBtn() {
		if (!this.isMove) {
			App.EventMgrHelper.PushEvent(EventDef.ShowHeroList,this.indexPos);
		} else {
			this.isMove = false;
		}
	}

	/**
	 * 是否激活
	 */
	public SetAction(action: boolean, level: number = 0) {
		if (action) {
			this.label_lock.visible = false;
			this.image_lock.visible = false;
			this.btn_add.visible = true;
		} else {
			this.image_lock.visible = false;
			this.group_player.visible = false;
			this.label_lock.visible = false;
			this.image_plus.visible = false;
			this.btn_add.visible = false;
			this.player_image.visible = false;
		}
	}

	/**
	 * 转换为与战斗位置相同的下标
	 */
	public ConvertIndex(index: number) {
		switch (index) {
			case 0:
				this.indexPos = 4;
				break;
			case 1:
				this.indexPos = 1;
				break;
			case 2:
				this.indexPos = 5;
				break;
			case 3:
				this.indexPos = 2;
				break;
			case 4:
				this.indexPos = 6;
				break;
			case 5:
				this.indexPos = 3;
				break;
		}
	}

	public get Base_back(): eui.Image { return this.base_back; }


}