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
var MailDetailView = (function (_super) {
    __extends(MailDetailView, _super);
    function MailDetailView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.itemArray = [];
        return _this;
    }
    Object.defineProperty(MailDetailView.prototype, "Model", {
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
    MailDetailView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.MailDetail);
        this.btn_close.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.onClose();
        }, this);
        this.btn_get.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onGet, this);
        this.btn_del.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onDel, this);
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    MailDetailView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    MailDetailView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.star.play(0);
        //TweenManager.scaleTween(this.chapterChooseGroup, this, 1, 249, () => { });
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    MailDetailView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    MailDetailView.prototype.setData = function (id) {
        this.mMailID = id;
        this.mMailData = this.Model.getMailDataByID(id);
        this.label_name.text = this.mMailData.mailName;
        this.label_mail.text = this.mMailData.mailMes;
        this.Model.setMailDataIsNewByID(id);
        this.updataRewardItem();
        App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S, id);
    };
    //一键删除所以已读
    MailDetailView.prototype.onDel = function () {
        if (this.mMailData.isGet())
            this.Model.delMailDataByID(this.mMailID);
        App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S, this.mMailID);
        this.onClose();
    };
    //一键领取
    MailDetailView.prototype.onGet = function () {
        //TODO,临时
        this.mMailData.clearItems();
        App.EventMgrHelper.PushEvent(EventDef.UPDATADATA_C2S, this.mMailID);
        this.onClose();
    };
    //刷新页面UI
    MailDetailView.prototype.updataRewardItem = function () {
        this.createOrUpdateItem(this.mMailData.items);
        for (var i = 0; i < this.itemArray.length; i++) {
            this.itemArray[i].setVisible(false);
        }
        for (var i = 0; i < this.mMailData.items.length; i++) {
            this.itemArray[i].setItem(this.mMailData.items[i]);
            this.itemArray[i].UnLock();
            this.itemArray[i].setVisible(true);
        }
    };
    MailDetailView.prototype.createOrUpdateItem = function (listCount) {
        //创建UI chapterItem
        for (var i = this.itemArray.length; i < listCount.length; i++) {
            var item = new UIItem();
            this.group_reward.addChild(item);
            this.itemArray.push(item);
        }
    };
    return MailDetailView;
}(BaseEuiView));
__reflect(MailDetailView.prototype, "MailDetailView");
//# sourceMappingURL=MailDetailView.js.map