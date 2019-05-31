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
var ActivityRewardUIController = (function (_super) {
    __extends(ActivityRewardUIController, _super);
    function ActivityRewardUIController() {
        var _this = _super.call(this) || this;
        _this.activityRewardModel = new ActivityRewardUIModel(_this);
        _this.activityRewardProxy = new ActivityRewardUIProxy(_this);
        _this.activityRewardView = new ActivityRewardUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.ActivityRewardUI, _this.activityRewardView);
        _this.RegisterEvent(EventDef.ActivityReward_dailySign);
        return _this;
    }
    ActivityRewardUIController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        if (EventDef.ActivityReward_dailySign == ev) {
            this.UpdateCurAccRewardItem();
        }
    };
    /**
     * 成功领取累签奖励
    */
    ActivityRewardUIController.prototype.UpdateCurAccRewardItem = function () {
        this.activityRewardView.dailySignUI.updateCurAccRewardItem();
    };
    return ActivityRewardUIController;
}(BaseController));
__reflect(ActivityRewardUIController.prototype, "ActivityRewardUIController");
//# sourceMappingURL=ActivityRewardUIController.js.map