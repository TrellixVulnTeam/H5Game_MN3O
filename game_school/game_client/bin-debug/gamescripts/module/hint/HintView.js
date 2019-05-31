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
var HintView = (function (_super) {
    __extends(HintView, _super);
    function HintView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.ensureClick = null;
        _this.cancelClick = null;
        return _this;
    }
    Object.defineProperty(HintView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.Dialog);
        },
        enumerable: true,
        configurable: true
    });
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    HintView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.Hint);
        this.btn_ensure.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnEnsure, this);
        this.btn_cancel.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnCancel, this);
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    HintView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    HintView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    HintView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    HintView.prototype.setData = function (tishi, text, ensureClick, cancelClick) {
        this.label_tishi.text = tishi;
        this.label_str.text = text;
        // this.btn_ensure.label = ensureLabel;
        // this.btn_cancel.label = cancelLabel;
        this.ensureClick = ensureClick;
        this.cancelClick = cancelClick;
    };
    HintView.prototype.onBtnEnsure = function () {
        this.onClose();
        if (this.ensureClick != null)
            this.ensureClick();
    };
    HintView.prototype.onBtnCancel = function () {
        if (this.cancelClick != null)
            this.cancelClick();
        else {
            this.onClose();
        }
    };
    return HintView;
}(BaseEuiView));
__reflect(HintView.prototype, "HintView");
//# sourceMappingURL=HintView.js.map