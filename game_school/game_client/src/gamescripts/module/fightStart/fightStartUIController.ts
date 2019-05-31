class fightStartUIController extends BaseController
{
    //本模块的数据存储
    private fightStartModel:fightStartUIModel;
    
    //本模块的所有UI
    private fightStartView:fightStartUIView;

    //本模块的Proxy
    private fightStartProxy:fightStartUIProxy;

    public constructor(){
        super();

        this.fightStartModel = new fightStartUIModel(this);
        this.fightStartProxy = new fightStartUIProxy(this);

        this.fightStartView = new fightStartUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.FightStartUI, this.fightStartView);
    }
}