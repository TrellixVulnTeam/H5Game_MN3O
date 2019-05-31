var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var __extends = this && this.__extends || function __extends(t, e) { 
 function r() { 
 this.constructor = t;
}
for (var i in e) e.hasOwnProperty(i) && (t[i] = e[i]);
r.prototype = e.prototype, t.prototype = new r();
};
/**
 *
 * Controller管理类
 */
var ControllerManager = (function (_super) {
    __extends(ControllerManager, _super);
    /**
     * 构造函数
     */
    function ControllerManager() {
        var _this = _super.call(this) || this;
        _this._modules = {};
        return _this;
    }
    ControllerManager.prototype.RegisterLoadingController = function (callback) {
        this.register(ControllerConst.Loading, new LoadingController()); //加载模块
        this.loadingPreloadUI(callback);
    };
    ControllerManager.prototype.RegisterAllController = function () {
        this.register(ControllerConst.Login, new LoginController()); //登录模块
        this.register(ControllerConst.Home, new HomeController()); //主UI
        this.register(ControllerConst.SettingUI, new SettingUIController()); //设置
        //this.register(ControllerConst.Friend, new FriendController());//好友
        this.register(ControllerConst.MainUI, new MainUIController()); //主界面UI
        this.register(ControllerConst.WechatUI, new WechatUIController()); //通信
        this.register(ControllerConst.ActivityRewardUI, new ActivityRewardUIController()); //奖励活动
        this.register(ControllerConst.WorldDriftTipsUI, new WorldDriftTipsUIController()); //飄字提示
        this.register(ControllerConst.HintCommonItemUI, new HintCommonItemUIController()); //item提示框
        this.register(ControllerConst.FriendlinessTipsUI, new FriendlinessTipsUIController()); //友好度提示
        this.register(ControllerConst.CreatureRoleUI, new CreatureRoleUIController()); //创建角色
        this.register(ControllerConst.Chapter, new ChapterController()); //章节
        this.register(ControllerConst.Battle, new BattleController()); //战斗UI
        this.register(ControllerConst.CCG_GameFight, new Game_FightController()); //战斗模块
        this.register(ControllerConst.BattleEdit, new BattleEditController()); //编队
        this.register(ControllerConst.Mail, new MailController()); //邮箱
        this.register(ControllerConst.MainActivity, new ActivityController()); //活动
        this.register(ControllerConst.Dialog, new DialogController()); //剧情模块
        this.register(ControllerConst.Hint, new HintController()); //提示框模块
        this.register(ControllerConst.VideoPlayContro, new VideoPlayUIController()); //视频播放UI
        this.register(ControllerConst.TestSpine, new TestSpineController()); //测试Spine动画专用
        //this.loadNeedPreloadUI(); 不用预加载ui了，前期加载资源太多
    };
    /**
     * 清空处理
     */
    ControllerManager.prototype.clear = function () {
        this._modules = {};
    };
    /**
     * 动态添加的Controller
     * @param key 唯一标识
     * @param manager Manager
     *
     */
    ControllerManager.prototype.register = function (key, control) {
        if (this.isExists(key))
            return;
        this._modules[key] = control;
    };
    /**
     * 动态移除Controller
     * @param key 唯一标识
     *
     */
    ControllerManager.prototype.unregister = function (key) {
        if (!this.isExists(key))
            return;
        this._modules[key] = null;
        delete this._modules[key];
    };
    /**
     * 是否已经存在Controller
     * @param key 唯一标识
     * @return Boolean
     *
     */
    ControllerManager.prototype.isExists = function (key) {
        return this._modules[key] != null;
    };
    /**
     * 跨模块消息传递
     * @param controllerD Controller唯一标识
     * @param key 消息唯一标识
     *
     */
    ControllerManager.prototype.applyFunc = function (controllerD, key) {
        var param = [];
        for (var _i = 2; _i < arguments.length; _i++) {
            param[_i - 2] = arguments[_i];
        }
        var manager = this._modules[controllerD];
        if (manager) {
            var params = [];
            for (var i = 1; i < arguments.length; i++) {
                params[i - 1] = arguments[i];
            }
            return manager.applyFunc.apply(manager, params);
        }
        else {
            Log.Error("模块" + controllerD + "不存在");
            return null;
        }
    };
    /**
     * 获取指定Controller的Model对象
     * @param controllerD Controller唯一标识
     * @returns {BaseModel}
     */
    ControllerManager.prototype.getControllerModel = function (controllerD) {
        var manager = this._modules[controllerD];
        if (manager) {
            return manager.getModel();
        }
        return null;
    };
    /**
     * 获取指定Controller对象
     * @param controllerD Controller唯一标识
     * @returns {BaseModel}
     */
    ControllerManager.prototype.getController = function (controllerD) {
        var manager = this._modules[controllerD];
        if (manager) {
            return manager;
        }
        return null;
    };
    /**
     * 加载预加载界面
    */
    ControllerManager.prototype.loadingPreloadUI = function (callback) {
        App.ViewManager.onLoadingPreloadUI(callback);
    };
    return ControllerManager;
}(BaseClass));
__reflect(ControllerManager.prototype, "ControllerManager");
//# sourceMappingURL=ControllerManager.js.map