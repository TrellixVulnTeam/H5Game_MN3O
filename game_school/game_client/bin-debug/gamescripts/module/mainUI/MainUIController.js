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
 */
var MainUIController = (function (_super) {
    __extends(MainUIController, _super);
    function MainUIController() {
        var _this = _super.call(this) || this;
        //初始化Model
        _this.mainUIModel = new MainUIModel(_this);
        //初始化UI
        _this.mainUIView = new MainUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.MainUI, _this.mainUIView);
        //初始化Proxy
        _this.mainUIProxy = new MainUIProxy(_this);
        return _this;
        //注册模块间、模块内部事件监听
        //注册C2S消息
        //this.registerFunc(LoginConst.LOGIN_C2S, this.onLogin, this);
        //注册S2C消息
        //this.registerFunc(LoginConst.LOGIN_S2C, this.loginSuccess, this);
    }
    return MainUIController;
}(BaseController));
__reflect(MainUIController.prototype, "MainUIController");
//# sourceMappingURL=MainUIController.js.map