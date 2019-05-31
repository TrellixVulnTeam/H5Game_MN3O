/**
 * 
 */
class BattleController extends BaseController {
    //本模块的数据存储
    private battleModel: BattleModel;
    //本模块的所有UI
    private battleView: BattleResultView;
    //战斗主界面
    private battleMainView: BattleMainView;
    //战斗立绘页面
    private battlePictureView: BattlePictureView;

    //本模块的Proxy
    private battleProxy: BattleProxy;

    public constructor() {
        super();
        //初始化Proxy
        this.battleProxy = new BattleProxy(this);

        //初始化Model
        this.battleModel = new BattleModel(this);
        this.setModel(this.battleModel);

        //初始化战斗主界面
        this.battleMainView = new BattleMainView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.BattleMain, this.battleMainView);

        //初始化战斗结算
        this.battleView = new BattleResultView(this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.BattleResult, this.battleView);

        //初始化战斗立绘
        this.battlePictureView = new BattlePictureView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.BattlePicture, this.battlePictureView);

        this.RegisterEvent(EventDef.SKILLPICTURE_C2C);
        this.RegisterEvent(EventDef.HPPICTURE_C2C);
        
    }

    public HandleEvent(ev:EventDef,le:LogicEvent){
        super.HandleEvent(ev,le);

        switch(ev){
            case EventDef.SKILLPICTURE_C2C:
                this.onSkillPictre(le.IntParam0,le.Object0);
            break;
            case EventDef.HPPICTURE_C2C:
                this.onHPPictre(le.IntParam0,le.Object0);
            break;
        }
    }


    private onSkillPictre(id: number, callBack?: Function): void {
        if (id < 0)
            return;

        var mconfig = MagicConfig.GetConfig(id);
        if(mconfig != null)
        {
            App.ViewManager.open(ViewConst.BattlePicture);
            this.battlePictureView.playPicturnAnimation(mconfig.animationDraw, callBack);
        }
    }

    private onHPPictre(uid: number, callBack?: Function): void {
        if (uid < 0){
            if(callBack)
                callBack();
             return;
        }
        var cconfig = CreatureTempletConfig.GetConfig(uid);
        if(cconfig != null)
        {
            App.ViewManager.open(ViewConst.BattlePicture);
            this.battlePictureView.playPicturnAnimation(cconfig.hurtDraw, callBack);
        }else{
             if(callBack)
                callBack();
        }
    }

}