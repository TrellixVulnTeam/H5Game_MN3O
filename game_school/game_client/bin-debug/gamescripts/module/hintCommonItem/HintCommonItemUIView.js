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
 * item提示框界面
 */
var HintCommonItemUIView = (function (_super) {
    __extends(HintCommonItemUIView, _super);
    function HintCommonItemUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.ensureClick = null;
        _this.cancelClick = null;
        _this.itemArray = new Array();
        _this.addEventListener(eui.UIEvent.COMPLETE, function () {
            _this.uiCompHandler($controller);
        }, _this);
        return _this;
    }
    HintCommonItemUIView.prototype.uiCompHandler = function ($controller) {
        this.btn_ensure.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnEnsure, this);
        this.btn_cancel.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnCancel, this);
    };
    HintCommonItemUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.HintCommonItemUI);
    };
    HintCommonItemUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    HintCommonItemUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
    };
    HintCommonItemUIView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    HintCommonItemUIView.prototype.onSetContent = function (tishi, text, items, ensureClick, cancelClick) {
        this.label_tishi.text = tishi;
        this.label_str.text = text;
        this.ensureClick = ensureClick;
        this.cancelClick = cancelClick;
        this.createItems(items);
    };
    HintCommonItemUIView.prototype.createItems = function (items) {
        if (this.itemArray.length <= 0) {
            for (var index = 0; index < items.length; index++) {
                var item = new UIItem();
                this.group_item.addChild(item);
                this.itemArray.push(item);
            }
        }
        else {
            if (this.itemArray.length <= items.length) {
                for (var index = 0; index < items.length - this.itemArray.length; index++) {
                    var item = new UIItem();
                    this.group_item.addChild(item);
                    this.itemArray.push(item);
                }
            }
            else {
                for (var index = 0; index < this.itemArray.length; index++) {
                    if (index > items.length) {
                        this.itemArray[index].visible = false;
                    }
                    else {
                        this.itemArray[index].visible = true;
                    }
                }
            }
        }
        for (var index = 0; index < items.length; index++) {
            this.itemArray[index].setItem(items[index]);
            this.itemArray[index].UnLock();
        }
    };
    HintCommonItemUIView.prototype.onBtnEnsure = function () {
        this.onClose();
        if (this.ensureClick != null) {
            this.ensureClick();
        }
    };
    HintCommonItemUIView.prototype.onBtnCancel = function () {
        if (this.cancelClick != null) {
            this.cancelClick();
        }
        else {
            this.onClose();
        }
    };
    return HintCommonItemUIView;
}(BaseEuiView));
__reflect(HintCommonItemUIView.prototype, "HintCommonItemUIView");
//# sourceMappingURL=HintCommonItemUIView.js.map