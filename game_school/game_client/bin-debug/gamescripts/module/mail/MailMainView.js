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
var MailMainView = (function (_super) {
    __extends(MailMainView, _super);
    function MailMainView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.mailItemArray = [];
        return _this;
    }
    Object.defineProperty(MailMainView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.Mail);
        },
        enumerable: true,
        configurable: true
    });
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    MailMainView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.MailMain);
        //this.Model.setMailDataArray();  //临时初始化的数据
        this.btn_close.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.onClose();
        }, this);
        this.btn_onedel.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onDel, this);
        this.btn_onekey.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onKey, this);
    };
    /**
    *对面板数据的初始化，用于子类继承
    *
    */
    MailMainView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    MailMainView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        if (this.Model.mailDataArray == null || this.Model.mailDataArray.length <= 0)
            this.Model.setMailDataArray(); //临时初始化的数据
        this.updataUI();
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    MailMainView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    //选择关卡页面
    MailMainView.prototype.onArrow = function () {
        // 如果已经打开了,就不在重复打开了,或者出战UI是否已经打开了
        if (App.ViewManager.isShow(ViewConst.ChapterMseeag)
            || App.ViewManager.isShow(ViewConst.ChapterChoose)) {
            return;
        }
        App.ViewManager.open(ViewConst.ChapterChoose);
    };
    //刷新页面UI
    MailMainView.prototype.updataUI = function () {
        this.createOrUpdateItem(this.Model.mailDataArray);
        for (var i = 0; i < this.mailItemArray.length; i++) {
            this.mailItemArray[i].setVisible(false);
        }
        for (var i = 0; i < this.Model.mailDataArray.length; i++) {
            this.mailItemArray[i].setData(this.Model.mailDataArray[i]);
            this.mailItemArray[i].setVisible(true);
        }
    };
    MailMainView.prototype.createOrUpdateItem = function (listCount) {
        //创建UI chapterItem
        for (var i = this.mailItemArray.length; i < listCount.length; i++) {
            var mailItem = new MailItem();
            mailItem.init(this);
            this.scrollerCon.addChild(mailItem);
            this.mailItemArray.push(mailItem);
        }
    };
    MailMainView.prototype.selectMail = function (id) {
        App.EventMgrHelper.PushEvent(EventDef.SELECTMAIL_C2S, id);
    };
    MailMainView.prototype.onDel = function () {
        var array = [];
        for (var i = 0; i < this.Model.mailDataArray.length; i++) {
            if (this.Model.mailDataArray[i].isNew == false && this.Model.mailDataArray[i].isGet()) {
                array.push(this.Model.mailDataArray[i].mailID);
                // this.Model.mailDataArray.splice(i, 1);
            }
        }
        for (var i = 0; i < array.length; i++) {
            this.Model.delMailDataByID(array[i]);
        }
        App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S);
    };
    //一键领取
    MailMainView.prototype.onKey = function () {
        for (var i = 0; i < this.Model.mailDataArray.length; i++) {
            if (this.Model.mailDataArray[i].isNew == true)
                this.Model.mailDataArray[i].isNew = false;
            this.Model.mailDataArray[i].clearItems();
        }
        App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S);
    };
    return MailMainView;
}(BaseEuiView));
__reflect(MailMainView.prototype, "MailMainView");
var MailItem = (function (_super) {
    __extends(MailItem, _super);
    function MailItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/skins/Mail_item.exml";
        return _this;
    }
    MailItem.prototype.setVisible = function (v) {
        this.visible = v;
    };
    //刷新数据
    MailItem.prototype.init = function (view) {
        if (view == null)
            return;
        this.mHandView = view;
        this.button_open.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    };
    //设置数据
    MailItem.prototype.setData = function (data) {
        if (data == null)
            return;
        this.mailID = data.mailID;
        this.label_title.text = data.mailName;
        this.label_mess.text = data.mailMes;
        this.image_news.visible = data.IsNew;
    };
    //设置位置
    MailItem.prototype.setPos = function (posX, posY) {
        this.x = posX;
        this.y = posY;
    };
    MailItem.prototype.onClick = function () {
        this.mHandView.selectMail(this.mailID);
    };
    return MailItem;
}(eui.Component));
__reflect(MailItem.prototype, "MailItem");
//# sourceMappingURL=MailMainView.js.map