/**
 * Created by sjz on 2018-5-10.
 */
class Game_FightController extends BaseController {

    private gameView: CCG_FightGameView;
    private gameModel: CCG_GameModel; //当前model

    public constructor() {
        super();

        //View初始化
        this.gameView = new CCG_FightGameView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.CCG_GameFight, this.gameView);

         //Model初始化
        this.gameModel=new CCG_GameModel(this);
        this.setModel(this.gameModel);
    
        this.RegisterEvent(EventDef.GameInit);
        this.RegisterEvent(EventDef.GameResize);
        this.RegisterEvent(EventDef.GameStart);
        this.RegisterEvent(EventDef.UpdateRound);
        this.RegisterEvent(EventDef.InitUI);
        this.RegisterEvent(EventDef.UpdateTimer);
        this.RegisterEvent(EventDef.UpdateHpBar);
        this.RegisterEvent(EventDef.OpenSkill);
        this.RegisterEvent(EventDef.SwitchingFight);
        this.RegisterEvent(EventDef.FightAni);
        this.RegisterEvent(EventDef.FightConvert);
        this.RegisterEvent(EventDef.FightMaskViableTrue);
        this.RegisterEvent(EventDef.FightMaskViableFalse);
        this.RegisterEvent(EventDef.SetBackMainBtnVis);
    }

    public HandleEvent(ev:EventDef,le:LogicEvent){
        super.HandleEvent(ev,le);
        switch(ev){
            case EventDef.GameInit:
               this.gameInit(le.IntParam0,le.Object0);
            break;
            case EventDef.GameResize:
                this.gameResize();
            break;
            case EventDef.GameStart:
             this.gameStart();
            break;
            case EventDef.UpdateRound:
             this.UpdateRound(le.IntParam0);
            break;
            case EventDef.InitUI:
             this.InitGameUI(le.Object0);
            break;
            case EventDef.UpdateTimer:
            this.UpdateTimer(le.IntParam0);
            break;
            case EventDef.UpdateHpBar:
            this.UpdateHpBar(le.IntParam0,le.IntParam1);
            break;
            case EventDef.OpenSkill:
            this.UpdateSkill(le.Object0,le.Object1);
            break;
            case EventDef.SwitchingFight:
            this.SwitchingFightStyle(le.Object0);
            break;
            case EventDef.FightAni:
            this.PlayFightAni(le.Object0);
            break;
            case EventDef.FightConvert:
            this. FightConvert(le.Object0);
            break;
            case EventDef.FightMaskViableTrue:
            this.FightMaskViableTrue(le.StrParam0);
            break;
            case EventDef.FightMaskViableFalse:
            this.FightMaskViableFalse(le.StrParam0);
            break;
            case EventDef.SetBackMainBtnVis:
            this.SetBackMainBtnVis(le.Object0);
            break;
        }
    }

    /**
     * 战斗表现
     */
    private FightMaskViableTrue(objUID:string){
        this.gameView.setObjMaskViewIndex(objUID,true);
    }

    /**
     * 战斗表现
     */
    private FightMaskViableFalse(objUID:string){
        this.gameView.setObjMaskViewIndex(objUID,false);
    }

    /**
     * 战斗转换
     */
    private FightConvert(callback:Function){
        this.gameView. FightConvert(callback);
    }

    /**
     * 播放战斗动画
     */
    private PlayFightAni(callback:Function){
        this.gameView.PlayFightAni(callback);
    }


    /**
     * 战斗数据
     */
    private gameInit(mapId: number,arrayInfos:HeroInfo[]) {
        this.gameModel.InitGameData(mapId,arrayInfos);
        this.gameStart();
    }

    /**
     * 显隐返回主界面按钮
     */
    private SetBackMainBtnVis(vis:boolean){
         if(this.gameModel.mapId!=1001){
             this.gameView.SetBackMainBtnVis(vis);
         }
    }

    /**
     * 战斗开始
     */
    private gameStart():void
    {
    if(this.gameModel.mapId==1001){
        this.gameView.SetBackMainBtnVis(false);
    }else{
        this.gameView.SetBackMainBtnVis(true);
    }
    App.FightManager.InitData(this.gameModel.mapId,this.gameModel.onwerplayerData,this.gameModel.enemyplayerData,this.gameView);//初始化战斗人员数据
    }

    /**
     * 更新回合数
     */
    private UpdateRound(roundCount:number){
        this.gameView.UpdateRound(roundCount);
    }

    /**
     * 更新时间
     */
    private UpdateTimer(timer:number){
        this.gameView.UpdateTimer(timer);
    }

    /**
     * 初始化ui
     */
    private InitGameUI(fightInfo:any[]){
        this.gameView.InitGameUI(fightInfo);
    }

    /**
     * 更新血条
     */
    private UpdateHpBar(camp:Camp,value:number){
        this.gameView.UpdateHpBar(camp,value);
    }

    /**
     * 更新技能
     */
    private UpdateSkill(own:MilitaryOfficerObject, skills:Skill[]){
        this.gameView.OpenSkillGroup(own,skills);
    }

    /**
     * 切换战斗
     */
    public SwitchingFightStyle(auto:boolean){
        this.gameView.SwitchingFightStyle(auto);
    }

    private gameResize(): void {
        //this.gameView.resize();
    }
}