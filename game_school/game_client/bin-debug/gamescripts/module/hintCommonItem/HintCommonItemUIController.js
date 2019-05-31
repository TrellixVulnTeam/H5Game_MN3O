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
 * item提示框controller
 */
var HintCommonItemUIController = (function (_super) {
    __extends(HintCommonItemUIController, _super);
    function HintCommonItemUIController() {
        var _this = _super.call(this) || this;
        _this.hintCommonview = new HintCommonItemUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.HintCommonItemUI, _this.hintCommonview);
        _this.RegisterEvent(EventDef.SHOWHINTITEMUI);
        return _this;
    }
    HintCommonItemUIController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        switch (ev) {
            case EventDef.SHOWHINTITEMUI:
                this.onSetContent(le.StrParam0, le.StrParam0, le.Object0, le.Object1, le.Object2);
                break;
        }
    };
    HintCommonItemUIController.prototype.onSetContent = function (tishi, text, items, ensureClick, cancelClick) {
        if (items != null && items.length > 0) {
            App.ViewManager.open(ViewConst.HintCommonItemUI);
            this.hintCommonview.onSetContent(tishi, text, items, ensureClick, cancelClick);
        }
    };
    return HintCommonItemUIController;
}(BaseController));
__reflect(HintCommonItemUIController.prototype, "HintCommonItemUIController");
//# sourceMappingURL=HintCommonItemUIController.js.map