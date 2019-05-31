/**
 * 战斗编辑控制
 */
class BattleEditController extends BaseController {

	private editView : BattleEditMainView;
	private arrayView: BattleArrayEditView;
	private editModel: BattleEditModel;

	public constructor() {
		super();

		//View战斗编辑
		this.editView= new BattleEditMainView(this,LayerManager.UI_Main);
		App.ViewManager.register(ViewConst.BattleEdit,this.editView);

		//布阵
		this.arrayView=new BattleArrayEditView(this,LayerManager.UI_Main);
		App.ViewManager.register(ViewConst.BattleArray,this.arrayView);

		//Model
		this.editModel=new BattleEditModel(this);
		this.setModel(this.editModel);

		//注册模块消息
		this.RegisterEvent(EventDef.UpdateArrayList);
		this.RegisterEvent(EventDef.ChangeTeam);
		this.RegisterEvent(EventDef.ShowHeroList);
		this.RegisterEvent(EventDef.AddHero);
		this.RegisterEvent(EventDef.SetAddState);	
		this.RegisterEvent(EventDef.CheckCollision);
		this.RegisterEvent(EventDef.InitArray);
		this.RegisterEvent(EventDef.StartFightByArray);
	}

	public HandleEvent(ev:EventDef,le:LogicEvent){
		super.HandleEvent(ev,le);
		switch(ev){
			case EventDef.UpdateArrayList:
			this.UpdateArrayList();
			break;
			case EventDef.ChangeTeam:
			this.ChangeTeam(le.IntParam0);
			break;
			case EventDef.ShowHeroList:
			this.ShowHeroList(le.IntParam0);
			break;
			case EventDef.AddHero:
			this.AddHero(le.IntParam0);
			break;
			case EventDef.SetAddState:
			this.SetAddBtnState(le.Object0);
			break;
			case EventDef.CheckCollision:
			this.CheckCollisionImage(le.Object0,le.Object1);
			break;
			case EventDef.InitArray:
			this.InitArray(le.Object0,le.IntParam0);
			break;
			case EventDef.StartFightByArray:
			this.StartFightByArray(le.IntParam0);
			break;
		}
	}

	/**更新列表 */
	public UpdateArrayList(){
		this.editView.UpdateUI(this.editModel.GetAllHero());
	}

	/**更改队伍 */
	public ChangeTeam(index:number){
	this.arrayView.ChangeTeam (this.editModel.GetTeamByIndex(index));
	}

	/**显示列表 */
	public ShowHeroList(index:number){
		this.editModel.currentIndex=index;
		App.ViewManager.open(ViewConst.BattleEdit);
	}

	/**添加英雄到队伍 */
	public AddHero(id:number){
		if(this.editModel.AddToCurrentArray(id))//当前队伍不能重复
		this.arrayView.ChangeTeam(this.editModel.GetTeamByIndex(this.editModel.currentTeam));
	}

	/**设置所有添加按钮状态 */
	public SetAddBtnState(state:boolean){
		this.arrayView.SetAddBtnVisible(state);
	}

/**检测人物是否与站位碰撞 */
	public CheckCollisionImage(demObj:HeroArrayItem,disObj:egret.DisplayObjectContainer){ 
		 let tempDis :HeroArrayItem= this.arrayView.HitCheckAllPoint(disObj)

		 if(tempDis!=null&&this.editModel.ExchangePoint(demObj.indexPos,tempDis.indexPos)){
			 this.arrayView.ChangeTeam(this.editModel.GetTeamByIndex(this.editModel.currentTeam));
		 }	else{
			 demObj.BackInPlace();
		 }
	}


	/**检测人物是否与站位碰撞 */
	public CheckCollision(demObj:DemonstrationObject,disObj:egret.DisplayObjectContainer){ 
		 let tempDis :HeroArrayItem= this.arrayView.HitCheckAllPoint(disObj)

		 if(tempDis!=null&&this.editModel.ExchangePoint(demObj.posInfo.Index,tempDis.indexPos)){
			 this.arrayView.ChangeTeam(this.editModel.GetTeamByIndex(this.editModel.currentTeam));
		 }	else{
			 demObj.BackInPlace();
		 }
	}

	/**初始化站位信息 */
	public InitArray(action:boolean,index:number){
		this.editModel.InitArrayInfo(action,index);
	}
	
	/**开始战斗 */
	public StartFightByArray(mapId:number){
		 App.ViewManager.open(ViewConst.CCG_GameFight,mapId);
		 App.EventMgrHelper.PushEventEx(EventDef.GameInit,this.editModel.GetTeamByIndex(this.editModel.currentTeam),null,mapId,0,"","");
	}


}