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
 */
var LoadingController = (function (_super) {
    __extends(LoadingController, _super);
    function LoadingController() {
        var _this = _super.call(this) || this;
        //初始化UI
        _this.loadingView = new LoadingView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Loading, _this.loadingView);
        _this.RegisterEvent(EventDef.LoadingRes_progress);
        _this.RegisterEvent(EventDef.LoadingConfig_progress);
        return _this;
    }
    LoadingController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        if (EventDef.LoadingRes_progress == ev) {
            this.setProgress(le.IntParam0, le.IntParam1);
        }
        else if (EventDef.LoadingConfig_progress == ev) {
            this.configLoadingProgress(le.IntParam0, le.IntParam1);
        }
    };
    LoadingController.prototype.setProgress = function (current, total) {
        this.loadingView.setProgress(current, total);
    };
    LoadingController.prototype.configLoadingProgress = function (current, total) {
        this.loadingView.configLoadingProgress(current, total);
    };
    return LoadingController;
}(BaseController));
__reflect(LoadingController.prototype, "LoadingController");
//# sourceMappingURL=LoadingController.js.map