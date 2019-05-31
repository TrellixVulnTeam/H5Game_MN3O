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
var HintController = (function (_super) {
    __extends(HintController, _super);
    function HintController() {
        var _this = _super.call(this) || this;
        //初始化Model
        _this.hintModel = new HintModel(_this);
        //初始化UI
        _this.hintView = new HintView(_this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.Hint, _this.hintView);
        //初始化Proxy
        _this.hintProxy = new HintProxy(_this);
        //注册模块间、模块内部事件监听
        _this.RegisterEvent(EventDef.DialogSkip);
        return _this;
    }
    HintController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        if (EventDef.DialogSkip == ev) {
            this.onDialogSkip(le.StrParam0, le.StrParam1, le.Object0, le.Object1);
        }
    };
    /**
    *
    * @param tishi 标题文字
    * @param text 文本内容
    * @param ensureLabel 确认按钮文本
    * @param cancelLabel 取消按钮文本
    * @param ensureClick 确认事件
    * @param cancelClick 取消事件 这个是空的话,就默认关闭自己
    */
    HintController.prototype.onDialogSkip = function (tishi, text, ensureClick, cancelClick) {
        App.ViewManager.open(ViewConst.Hint);
        this.hintView.setData(tishi, text, ensureClick, cancelClick);
    };
    return HintController;
}(BaseController));
__reflect(HintController.prototype, "HintController");
//# sourceMappingURL=HintController.js.map