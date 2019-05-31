/**
 * 
 */
class LoginController extends BaseController{
    //本模块的数据存储
    private loginModel:LoginModel;
    //本模块的所有UI
    private loginView:LoginView;
    //本模块的Proxy
    private loginProxy:LoginProxy;

    public constructor(){
        super();

        //初始化Model
        this.loginModel = new LoginModel(this);

        //初始化UI
        this.loginView = new LoginView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Login, this.loginView);

        //初始化Proxy
        this.loginProxy = new LoginProxy(this);
    }

    /**
     * 请求登陆处理
     * @param userName
     * @param pwd
     */
    private onLogin(userName:string, pwd:string):void{
        this.loginProxy.login(userName, pwd);
    }

    /**
     * 登陆成功处理
     */
    private loginSuccess(userInfo:any):void{
        //保存数据
        this.loginModel.userInfo = userInfo;
        //本模块UI处理
        this.loginView.loginSuccess();
        //UI跳转
        App.ViewManager.close(ViewConst.Login);

        var model:BaseModel = this.getControllerModel(ControllerConst.Login);
    }
}