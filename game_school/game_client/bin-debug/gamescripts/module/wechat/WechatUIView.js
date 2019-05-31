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
var WechatUIType;
(function (WechatUIType) {
    WechatUIType[WechatUIType["Wechat_fm"] = 0] = "Wechat_fm";
    WechatUIType[WechatUIType["Wechat_chat"] = 1] = "Wechat_chat";
    WechatUIType[WechatUIType["Wechat_record"] = 2] = "Wechat_record";
    WechatUIType[WechatUIType["Wechat_vipcn_com"] = 3] = "Wechat_vipcn_com";
})(WechatUIType || (WechatUIType = {}));
var WechatUIView = (function (_super) {
    __extends(WechatUIView, _super);
    function WechatUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.btnGroup = new eui.RadioButtonGroup(); //按钮//
        _this.bulbs = new Array(); //红点//
        _this.groupArray = Array();
        _this.childViewArray = Array();
        _this.addEventListener(eui.UIEvent.COMPLETE, function () {
            _this.uiCompHandler($controller);
        }, _this);
        return _this;
    }
    WechatUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.WechatUI);
    };
    WechatUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    WechatUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.openDefaultUI(); //暂时默认打开
        this.updateBtnBulb();
    };
    WechatUIView.prototype.close = function () {
        _super.prototype.close.call(this);
        for (var index = 0; index < this.childViewArray.length; index++) {
            this.childViewArray[index].onChildGroupHide();
        }
    };
    WechatUIView.prototype.openDefaultUI = function () {
        this.btn_1.selected = true;
        this.openGroupUI(WechatUIType.Wechat_fm);
    };
    WechatUIView.prototype.uiCompHandler = function ($controller) {
        this.addChildUIView($controller);
        this.addChildGroupUI();
        this.onSetBtnGroup();
        this.onSetBtnBulb();
    };
    WechatUIView.prototype.addChildUIView = function ($controller) {
        this.friendMomentUI = new FriendMomentUIView($controller, this.gro_pyq, this._key);
        this.childViewArray.push(this.friendMomentUI);
        this.chatListInfoUi = new ChatListsInfoUIView($controller, this.gro_talk, this._key);
        this.childViewArray.push(this.chatListInfoUi);
        this.addressBookView = new AddressbookListUIView($controller, this.gro_other, this._key);
        this.childViewArray.push(this.addressBookView);
    };
    WechatUIView.prototype.addChildGroupUI = function () {
        this.groupArray.push(this.gro_pyq);
        this.groupArray.push(this.gro_talk);
        this.groupArray.push(this.gro_other);
        this.groupArray.push(this.gro_mor);
    };
    WechatUIView.prototype.onSetBtnGroup = function () {
        this.btnGroup.addEventListener(eui.UIEvent.CHANGE, this.selectUIHandler, this);
        this.btn_1.value = WechatUIType.Wechat_fm;
        this.btn_2.value = WechatUIType.Wechat_chat;
        this.btn_3.value = WechatUIType.Wechat_record;
        this.btn_4.value = WechatUIType.Wechat_vipcn_com;
        this.btn_1.group = this.btnGroup;
        this.btn_2.group = this.btnGroup;
        this.btn_3.group = this.btnGroup;
        this.btn_4.group = this.btnGroup;
    };
    WechatUIView.prototype.onSetBtnBulb = function () {
        this.bulbs.push(this.image_tishi_pyq1);
        this.bulbs.push(this.image_tishi_pyq2);
        this.bulbs.push(this.image_tishi_pyq3);
        this.bulbs.push(this.image_tishi_pyq4);
    };
    WechatUIView.prototype.SelectUIByType = function (type) {
        this.btn_1.selected = type == this.btn_1.value;
        this.btn_2.selected = type == this.btn_2.value;
        this.btn_3.selected = type == this.btn_3.value;
        this.btn_4.selected = type == this.btn_4.value;
        this.openGroupUI(type);
    };
    WechatUIView.prototype.selectUIHandler = function (evt) {
        this.btnGroup = evt.target;
        this.openGroupUI(this.btnGroup.selectedValue);
    };
    WechatUIView.prototype.openGroupUI = function (type) {
        for (var index = 0; index < this.groupArray.length; index++) {
            if (type == index) {
                this.groupArray[index].visible = true;
                if (index < this.childViewArray.length) {
                    this.childViewArray[index].onChildGroupShow();
                }
            }
            else {
                this.groupArray[index].visible = false;
                if (index < this.childViewArray.length) {
                    this.childViewArray[index].onChildGroupHide();
                }
            }
        }
    };
    WechatUIView.prototype.updateBtnBulb = function () {
        for (var index = 0; index < this.bulbs.length; index++) {
            if (0 == index) {
                this.bulbs[index].visible = true;
            }
            else {
                this.bulbs[index].visible = false;
            }
        }
    };
    return WechatUIView;
}(BaseEuiView));
__reflect(WechatUIView.prototype, "WechatUIView");
//# sourceMappingURL=WechatUIView.js.map