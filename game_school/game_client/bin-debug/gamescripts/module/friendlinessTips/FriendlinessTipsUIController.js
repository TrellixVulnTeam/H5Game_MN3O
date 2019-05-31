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
var FriendlinessTipsUIController = (function (_super) {
    __extends(FriendlinessTipsUIController, _super);
    function FriendlinessTipsUIController() {
        var _this = _super.call(this) || this;
        _this.FriendlinessTipsView = new FriendlinessTipsUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.FriendlinessTipsUI, _this.FriendlinessTipsView);
        _this.RegisterEvent(EventDef.Friendliness_tips);
        return _this;
    }
    FriendlinessTipsUIController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        if (EventDef.Friendliness_tips == ev) {
            this.onSetContent(le.StrParam0);
        }
    };
    FriendlinessTipsUIController.prototype.onSetContent = function (content) {
        if (content == null)
            return;
        this.FriendlinessTipsView.setContent(content);
        App.ViewManager.open(ViewConst.FriendlinessTipsUI);
    };
    return FriendlinessTipsUIController;
}(BaseController));
__reflect(FriendlinessTipsUIController.prototype, "FriendlinessTipsUIController");
//# sourceMappingURL=FriendlinessTipsUIController.js.map