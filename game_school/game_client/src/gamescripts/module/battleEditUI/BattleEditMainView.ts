/**
 * 战斗编辑页面
 */
class BattleEditMainView extends BaseEuiView{

	private btn_back:eui.Button;//返回
	private scrollerCon :eui.Group;//列表容器

	/**
	 * 临时指引标记
	*/
	private isFirstGuide = false;

	public constructor($controller: BaseController, $parent: eui.Group) {
		super($controller, $parent);
	}

	public initUI():void{
		super.initUI();
		this.skinName = App.ViewManager.getSkin(ViewConst.BattleEdit);

		this.isFirstGuide = App.GuideManager.getIsGuide;

		this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP,()=>{
	         App.ViewManager.close(ViewConst.BattleEdit);
	 		 App.ViewManager.open(ViewConst.BattleArray);
		},this);
	}

	public initData(): void {
        super.initData();
    }

    public open(...param: any[]): void {
        super.open(param);
		App.EventMgrHelper.PushEvent(EventDef.UpdateArrayList);
    }

	/**
	 * 刷新UI
	 */
	public UpdateUI(allHero:HeroInfo[]){
		for(let i=0;i<allHero.length;i++){
			if(i<this.scrollerCon.numElements){
				let tempItem=this.scrollerCon.getChildAt(i) as HeroInfoItem;
				tempItem.UpdateUI(allHero[i]);
			}else{
				let tempItem=new HeroInfoItem(this.width);
				tempItem.UpdateUI(allHero[i]);
				this.scrollerCon.addChild(tempItem);
			}
		}

		if(this.isFirstGuide)
		{
			this.isFirstGuide = false;
			this.addFirstGuide();
		}
	}

	/**
     * 临时指引1（第一次进入英雄选择界面，选择第二个英雄上阵）
    */
    public addFirstGuide()
    {
		let item = this.scrollerCon.getChildAt(1) as HeroInfoItem;
		if(item != null)
		{
			this.validateNow();
			
			let itemtemp = new HeroInfoItem(item.width);
			itemtemp.width = item.width;
			itemtemp.height = item.height;
			itemtemp.x = item.localToGlobal().x;
			itemtemp.y = item.localToGlobal().y;
			itemtemp.UpdateUI(item.heroInfo);

			let mask = new GuideMask(itemtemp, () => {
				App.ViewManager.close(ViewConst.BattleEdit);
				App.EventMgrHelper.PushEvent(EventDef.AddHero,item.heroInfoId);
			}, "", false);
			this.addChild(mask);
		}
    }
}

/**
 * 英雄信息条
 */
class HeroInfoItem extends eui.Component{

	private player:eui.Image;//头像
	private label_name:eui.Label;//名称
	private label_battle:eui.Label;//战斗力
	private label_type:eui.Label;//标签
	private image_wcz:eui.Image;//为出战
	private image_ycz:eui.Image;//已出站

	public heroInfoId = 0;
	public heroInfo = null;
	private mConfig:CreatureTempletConfig;//角色表

	public constructor(wid:number) {
		super();
		this.percentWidth=100;
		this.width=wid;
		
		this.skinName = App.ViewManager.getSkin(ViewConst.HeroInfoItem);
	}

	public UpdateUI(heroinfo:HeroInfo){
		this.heroInfoId = heroinfo.id;
		this.heroInfo = heroinfo;
		this.mConfig=CreatureTempletConfig.GetConfig(heroinfo.id);
		this.player.source=this.mConfig.icon;
		this.label_name.text=this.mConfig.name;
		this.image_wcz.visible=!heroinfo.belong;
		this.image_ycz.visible=heroinfo.belong;
		this.addEventListener(egret.TouchEvent.TOUCH_TAP,function(){
				App.ViewManager.close(ViewConst.BattleEdit);
				App.EventMgrHelper.PushEvent(EventDef.AddHero,heroinfo.id);
		}.bind(this),this);
	}
}