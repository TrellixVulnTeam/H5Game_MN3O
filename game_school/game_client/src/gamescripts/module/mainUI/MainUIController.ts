/**
 * 
 */
class MainUIController extends BaseController{
    //本模块的数据存储
    private mainUIModel:MainUIModel;
    //本模块的所有UI
    private mainUIView:MainUIView;
    //本模块的Proxy
    private mainUIProxy:MainUIProxy;

    public constructor(){
        super();

        //初始化Model
        this.mainUIModel = new MainUIModel(this);

        //初始化UI
        this.mainUIView = new MainUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.MainUI, this.mainUIView);

        //初始化Proxy
        this.mainUIProxy = new MainUIProxy(this);

        //注册模块间、模块内部事件监听

        //注册C2S消息
        //this.registerFunc(LoginConst.LOGIN_C2S, this.onLogin, this);

        //注册S2C消息
        //this.registerFunc(LoginConst.LOGIN_S2C, this.loginSuccess, this);
    }
}