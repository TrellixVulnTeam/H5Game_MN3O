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
var DialogOptionView = (function (_super) {
    __extends(DialogOptionView, _super);
    function DialogOptionView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.optionItemArray = [];
        return _this;
    }
    Object.defineProperty(DialogOptionView.prototype, "Model", {
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
    DialogOptionView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.DialogOption);
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    DialogOptionView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    DialogOptionView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        //TweenManager.scaleTween(this.Group_choose, this, 1, 249, () => { });
        this.updataUI();
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    DialogOptionView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    //刷新页面UI
    DialogOptionView.prototype.updataUI = function () {
        var con = this.Model.GetDialogOptionConfigByOptionID(this.Model.curDialogConf.optionID);
        this.createOrUpdateItem(con);
        for (var i = 0; i < this.optionItemArray.length; i++) {
            this.optionItemArray[i].setVisible(false);
        }
        if (con.optionContent1 != "") {
            this.optionItemArray[0].setData(0, con.optionContent1, con.nextDialog1);
            this.optionItemArray[0].setVisible(true);
        }
        if (con.optionContent2 != "") {
            this.optionItemArray[1].setData(0, con.optionContent2, con.nextDialog2);
            this.optionItemArray[1].setVisible(true);
        }
        if (con.optionContent3 != "") {
            this.optionItemArray[2].setData(0, con.optionContent3, con.nextDialog3);
            this.optionItemArray[2].setVisible(true);
        }
        if (con.optionContent4 != "") {
            this.optionItemArray[3].setData(0, con.optionContent4, con.nextDialog4);
            this.optionItemArray[3].setVisible(true);
        }
    };
    DialogOptionView.prototype.createOrUpdateItem = function (con) {
        //创建UI chapterItem
        for (var i = this.optionItemArray.length; i < con.option1; i++) {
            var optionItem = new OptionItem();
            optionItem.init(this);
            this.Group_choose.addChild(optionItem);
            this.optionItemArray.push(optionItem);
        }
    };
    DialogOptionView.prototype.onClickOptionItem = function (optionIndex, nextDialogID) {
        App.EventMgrHelper.PushEvent(EventDef.SelectDialogOption, optionIndex, nextDialogID);
        //App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.SELECTOPTION_C2C, optionIndex, nextDialogID);
        this.onClose();
    };
    return DialogOptionView;
}(BaseEuiView));
__reflect(DialogOptionView.prototype, "DialogOptionView");
var OptionItem = (function (_super) {
    __extends(OptionItem, _super);
    function OptionItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/skins/Dialogue_choose_item.exml";
        return _this;
    }
    OptionItem.prototype.init = function (view) {
        if (view == null)
            return;
        this.mHandView = view;
        this.button_dia.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    };
    OptionItem.prototype.setData = function (index, str, nextDialogID) {
        this.index = index;
        this.label_dia.text = str;
        this.nextDialogID = nextDialogID;
    };
    OptionItem.prototype.setVisible = function (v) {
        this.visible = v;
    };
    OptionItem.prototype.onClick = function () {
        this.mHandView.onClickOptionItem(this.index, this.nextDialogID);
    };
    return OptionItem;
}(eui.Component));
__reflect(OptionItem.prototype, "OptionItem");
//# sourceMappingURL=DialogOptionView.js.map