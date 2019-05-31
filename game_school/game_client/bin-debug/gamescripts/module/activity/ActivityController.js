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
var ActivityController = (function (_super) {
    __extends(ActivityController, _super);
    function ActivityController() {
        var _this = _super.call(this) || this;
        //初始化Model
        _this.activityModel = new ActivityModel(_this);
        //初始化UI
        _this.activityView = new ActivityView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.MainActivity, _this.activityView);
        //初始化Proxy
        _this.activityProxy = new ActivityProxy(_this);
        return _this;
        // //注册模块间、模块内部事件监听
        // this.registerFunc(MailConst.UPDATADATA_C2S, this.onUpdataData, this);
        // this.registerFunc(MailConst.SELECTMAIL_C2S, this.onSelectMail, this);
    }
    //选择章节事件
    ActivityController.prototype.onUpdataData = function (chapterId) {
    };
    ActivityController.prototype.onSelectMail = function (id) {
    };
    return ActivityController;
}(BaseController));
__reflect(ActivityController.prototype, "ActivityController");
//# sourceMappingURL=ActivityController.js.map