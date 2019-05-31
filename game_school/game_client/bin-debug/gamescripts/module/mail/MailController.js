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
var MailController = (function (_super) {
    __extends(MailController, _super);
    function MailController() {
        var _this = _super.call(this) || this;
        //初始化Model
        _this.mailModel = new MailModel(_this);
        //初始化UI
        _this.mailMainView = new MailMainView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.MailMain, _this.mailMainView);
        _this.mailDetailView = new MailDetailView(_this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.MailDetail, _this.mailDetailView);
        //初始化Proxy
        _this.mailProxy = new MailProxy(_this);
        _this.RegisterEvent(EventDef.UPDATADATA_C2S);
        _this.RegisterEvent(EventDef.SELECTMAIL_C2S);
        return _this;
    }
    MailController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        switch (ev) {
            case EventDef.UPDATADATA_C2S:
                this.onUpdataData(le.IntParam0);
                break;
            case EventDef.SELECTMAIL_C2S:
                this.onSelectMail(le.IntParam0);
                break;
        }
    };
    //选择章节事件
    MailController.prototype.onUpdataData = function (chapterId) {
        this.mailMainView.updataUI();
    };
    MailController.prototype.onSelectMail = function (id) {
        App.ViewManager.open(ViewConst.MailDetail);
        this.mailDetailView.setData(id);
    };
    return MailController;
}(BaseController));
__reflect(MailController.prototype, "MailController");
//# sourceMappingURL=MailController.js.map