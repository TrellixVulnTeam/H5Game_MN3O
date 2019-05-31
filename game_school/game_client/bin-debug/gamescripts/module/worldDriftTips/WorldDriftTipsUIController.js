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
 * 飘字提示controller
 */
var WorldDriftTipsUIController = (function (_super) {
    __extends(WorldDriftTipsUIController, _super);
    function WorldDriftTipsUIController() {
        var _this = _super.call(this) || this;
        _this.worldDriftView = new WorldDriftTipsUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.WorldDriftTipsUI, _this.worldDriftView);
        _this.RegisterEvent(EventDef.Setdrift_world);
        return _this;
    }
    WorldDriftTipsUIController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        if (EventDef.Setdrift_world == ev) {
            this.onSetContent(le.StrParam0);
        }
    };
    WorldDriftTipsUIController.prototype.onSetContent = function (content) {
        if (content == null)
            return;
        this.worldDriftView.setContent(content);
        App.ViewManager.open(ViewConst.WorldDriftTipsUI);
    };
    return WorldDriftTipsUIController;
}(BaseController));
__reflect(WorldDriftTipsUIController.prototype, "WorldDriftTipsUIController");
//# sourceMappingURL=WorldDriftTipsUIController.js.map