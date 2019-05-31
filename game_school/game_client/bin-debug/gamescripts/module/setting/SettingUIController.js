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
var SettingUIController = (function (_super) {
    __extends(SettingUIController, _super);
    function SettingUIController() {
        var _this = _super.call(this) || this;
        _this.settingModel = new SettingUIModel(_this);
        _this.settingProxy = new SettingUIProxy(_this);
        _this.settingView = new SettingUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.SettingUI, _this.settingView);
        return _this;
    }
    return SettingUIController;
}(BaseController));
__reflect(SettingUIController.prototype, "SettingUIController");
//# sourceMappingURL=SettingUIController.js.map