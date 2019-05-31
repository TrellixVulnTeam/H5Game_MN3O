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
 * Created by egret on 15-1-7.
 */
var LoadingView = (function (_super) {
    __extends(LoadingView, _super);
    function LoadingView($controller, $parent) {
        return _super.call(this, $controller, $parent) || this;
    }
    LoadingView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = "resource/skins/LoadingUISkin.exml"; //登陆界面Config数据还没加载不使用App.ViewManager.getSkin
    };
    LoadingView.prototype.setProgress = function (current, total) {
        this.txtMsg.text = "资源加载中..." + ((current / total) * 100).toFixed() + "%";
        this.pro.value = current / total * 100;
    };
    LoadingView.prototype.configLoadingProgress = function (current, total) {
        this.txtMsg.text = "configloading " + ((current / total) * 100).toFixed() + "%";
        this.pro.value = current / total * 100;
    };
    return LoadingView;
}(BaseEuiView));
__reflect(LoadingView.prototype, "LoadingView");
//# sourceMappingURL=LoadingView.js.map