class SettingUIController extends BaseController
{
    //本模块的数据存储
    private settingModel:SettingUIModel;
    
    //本模块的所有UI
    private settingView:SettingUIView;

    //本模块的Proxy
    private settingProxy:SettingUIProxy;

    public constructor(){
        super();

        this.settingModel = new SettingUIModel(this);
        this.settingProxy = new SettingUIProxy(this);

        this.settingView = new SettingUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.SettingUI, this.settingView);
    }
}