/**
 * 
 * Controller管理类
 */
class ControllerManager extends BaseClass {
    public RegisterLoadingController(callback: Function):void
    { 
        this.register(ControllerConst.Loading, new LoadingController());//加载模块
        this.loadingPreloadUI(callback);
    }

    public RegisterAllController():void
    { 
        this.register(ControllerConst.Login, new LoginController());//登录模块
        this.register(ControllerConst.Home, new HomeController()); //主UI
        this.register(ControllerConst.SettingUI, new SettingUIController());//设置
        //this.register(ControllerConst.Friend, new FriendController());//好友
        this.register(ControllerConst.MainUI, new MainUIController());//主界面UI
        this.register(ControllerConst.WechatUI, new WechatUIController());//通信
        this.register(ControllerConst.ActivityRewardUI, new ActivityRewardUIController());//奖励活动
        this.register(ControllerConst.WorldDriftTipsUI, new WorldDriftTipsUIController());//飄字提示
        this.register(ControllerConst.HintCommonItemUI, new HintCommonItemUIController());//item提示框
        this.register(ControllerConst.FriendlinessTipsUI, new FriendlinessTipsUIController());//友好度提示
        this.register(ControllerConst.CreatureRoleUI, new CreatureRoleUIController());//创建角色
        this.register(ControllerConst.Chapter, new ChapterController());//章节
        this.register(ControllerConst.Battle, new BattleController());//战斗UI
        this.register(ControllerConst.CCG_GameFight, new Game_FightController());//战斗模块
        this.register(ControllerConst.BattleEdit,new BattleEditController());//编队
        this.register(ControllerConst.Mail,new MailController());//邮箱
        this.register(ControllerConst.MainActivity,new ActivityController());//活动

        this.register(ControllerConst.Dialog, new DialogController());//剧情模块
        this.register(ControllerConst.Hint, new HintController());//提示框模块
        this.register(ControllerConst.VideoPlayContro,new VideoPlayUIController());//视频播放UI
        
        this.register(ControllerConst.TestSpine,new TestSpineController());//测试Spine动画专用
        //this.loadNeedPreloadUI(); 不用预加载ui了，前期加载资源太多
    }
    
    private _modules:any;

    /**
     * 构造函数
     */
    public constructor() {
        super();
        this._modules = {};
    }

    /**
     * 清空处理
     */
    public clear():void {
        this._modules = {};
    }

    /**
     * 动态添加的Controller
     * @param key 唯一标识
     * @param manager Manager
     *
     */
    public register(key:number, control:BaseController):void {
        if (this.isExists(key))
            return;

        this._modules[key] = control;
    }

    /**
     * 动态移除Controller
     * @param key 唯一标识
     *
     */
    public unregister(key:number):void {
        if (!this.isExists(key))
            return;

        this._modules[key] = null;
        delete this._modules[key];
    }

    /**
     * 是否已经存在Controller
     * @param key 唯一标识
     * @return Boolean
     *
     */
    public isExists(key:number):boolean {
        return this._modules[key] != null;
    }

    /**
     * 跨模块消息传递
     * @param controllerD Controller唯一标识
     * @param key 消息唯一标识
     *
     */
    public applyFunc(controllerD:number, key:number, ...param:any[]):any {
        var manager:BaseController = this._modules[controllerD];
        if (manager) {
            var params = [];
            for (var i = 1; i < arguments.length; i++) {
                params[i - 1] = arguments[i];
            }
            return manager.applyFunc.apply(manager, params);
        } else {
            Log.Error("模块" + controllerD + "不存在");
            return null;
        }
    }

    /**
     * 获取指定Controller的Model对象
     * @param controllerD Controller唯一标识
     * @returns {BaseModel}
     */
    public getControllerModel(controllerD:number):BaseModel {
        var manager:BaseController = this._modules[controllerD];
        if (manager) {
            return manager.getModel();
        }
        return null;
    }

    /**
     * 获取指定Controller对象
     * @param controllerD Controller唯一标识
     * @returns {BaseModel}
     */
    public getController(controllerD:number):BaseController {
        var manager:BaseController = this._modules[controllerD];
        if (manager) 
        {
            return manager;
        }
        return null;
    }

    /**
     * 加载预加载界面
    */
    private loadingPreloadUI(callback: Function):void
    {
        App.ViewManager.onLoadingPreloadUI(callback);
    }

    /**
     * 加载预加载界面
     *此函数摒弃了
    private loadNeedPreloadUI():void
    {
        App.ViewManager.onLoadNeedPreloadUI();
    }
    */
}
