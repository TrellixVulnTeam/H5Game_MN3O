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
 * 登陆界面
 */
var LoginView = (function (_super) {
    __extends(LoginView, _super);
    function LoginView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.play = false;
        _this.addEventListener(eui.UIEvent.COMPLETE, _this.uiCompHandler, _this);
        return _this;
    }
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    LoginView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.Login);
        this.createPlayerArmature();
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    LoginView.prototype.initData = function () {
        _super.prototype.initData.call(this);
        App.KeyboardUtils.addKeyDown(this.onKeyDown, this);
    };
    LoginView.prototype.onKeyDown = function (keyCode) {
        switch (keyCode) {
            case Keyboard.SPACE:
                App.GuideManager.setIsGuide(true);
                break;
            case Keyboard.A:
                App.GuideManager.setIsGuide(false);
                break;
            default:
                break;
        }
    };
    LoginView.prototype.uiCompHandler = function () {
        this.username.addEventListener(egret.TouchEvent.CHANGE, this.onChangeUsername, this);
        this.username.addEventListener(egret.TouchEvent.FOCUS_IN, this.onSetUsername, this);
        this.username.addEventListener(egret.TouchEvent.FOCUS_OUT, this.offSetUsername, this);
        this.password.addEventListener(egret.TouchEvent.CHANGE, this.onChangePassword, this);
        this.password.addEventListener(egret.TouchEvent.FOCUS_IN, this.onSetPassword, this);
        this.password.addEventListener(egret.TouchEvent.FOCUS_OUT, this.offSetPassword, this);
        this.loginbtn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onLogin, this);
    };
    LoginView.prototype.onSetUsername = function () {
        this.username.text = "";
    };
    LoginView.prototype.offSetUsername = function () {
        if (this.username.text == "") {
            this.username.text = "用户名";
        }
    };
    LoginView.prototype.onChangeUsername = function (ev) {
        this.username.text = ev.target.text;
    };
    LoginView.prototype.onSetPassword = function () {
        this.password.text = "";
    };
    LoginView.prototype.offSetPassword = function () {
        if (this.password.text == "") {
            this.password.displayAsPassword = false;
            this.password.text = "密码";
        }
    };
    LoginView.prototype.onChangePassword = function (ev) {
        this.password.displayAsPassword = true;
        this.password.text = ev.target.text;
    };
    /**
     * 请求登陆处理
     * @param userName
     * @param pwd
     */
    LoginView.prototype.onLogin = function () {
        var userName = this.username.text;
        var pwd = this.password.text;
        if (userName == null || userName.length == 0) {
            return;
        }
        if (pwd == null || pwd.length == 0) {
            return;
        }
        this.onClose();
        App.ViewManager.open(ViewConst.CreatureRoleUI);
        //this.applyFunc(LoginConst.LOGIN_C2S, userName, pwd);
    };
    /**
     * 登陆成功处理
     */
    LoginView.prototype.loginSuccess = function () {
        //TODO 登陆成功处理
        this.onClose();
        App.ViewManager.open(ViewConst.CreatureRoleUI);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    LoginView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.taiyang.play(0);
        var time = 200; //动画播放时间//
        var intervalID = setInterval(function onTick() {
            time--;
            if (time < 0) {
                time = 200;
                this.taiyang.play(0);
            }
            if (this.play) {
                clearInterval(intervalID);
            }
        }.bind(this), 10);
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    LoginView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
        this.play = true;
    };
    /**
     * 人物
     */
    LoginView.prototype.createPlayerArmature = function () {
        this.actionArray = ["stand", "standby"];
        var dbName = "相川小春_部活_制服";
        this.mDrag = ObjectPool.pop("DragonObjectTest");
        this.mDrag.init(dbName, "buhuo_zhifu", this.actionArray);
        this.mDrag.armature.x = (this.Group_Dragon.width + 100) / 2;
        this.mDrag.armature.y = this.Group_Dragon.height;
        this.mDrag.armature.touchEnabled = true;
        this.mDrag.armature.$addListener(egret.TouchEvent.TOUCH_BEGIN, this.changeArmature, this);
        this.Group_Dragon.scaleX = 1.28;
        this.Group_Dragon.scaleY = 1.28;
        this.Group_Dragon.addChild(this.mDrag);
    };
    /**
     * 点击动作
     */
    LoginView.prototype.changeArmature = function () {
        var act = App.RandomUtils.randomArray(this.actionArray);
        this.mDrag.armature.play(act, 0);
    };
    return LoginView;
}(BaseEuiView));
__reflect(LoginView.prototype, "LoginView");
//# sourceMappingURL=LoginView.js.map