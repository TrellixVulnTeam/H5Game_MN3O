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
 * 通讯录界面
 */
var AddressbookListUIView = (function (_super) {
    __extends(AddressbookListUIView, _super);
    function AddressbookListUIView($controller, $parent, key) {
        var _this = _super.call(this, $controller, $parent, key) || this;
        _this.onInitUI();
        return _this;
    }
    AddressbookListUIView.prototype.onInitUI = function () {
        var _this = this;
        this.tongxun_back = this.myParent.getChildByName("tongxun_back");
        this.py_tongxun = this.myParent.getChildByName("py_tongxun");
        this.tongxun_Group = this.py_tongxun.getChildByName("tongxun_Group");
        this.tongxun_back.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.close(_this._key);
        }, this);
    };
    /**
    * 打开页面
    */
    AddressbookListUIView.prototype.onChildGroupShow = function () {
        _super.prototype.onChildGroupShow.call(this);
        this.UpdateList();
    };
    /**
     * 刷新页面
     */
    AddressbookListUIView.prototype.UpdateList = function () {
        var itemCount = this.tongxun_Group.numElements;
        var tempItem;
        for (var i = 0; i < App.PlayerManager.OwnGirl.length; i++) {
            if (i < itemCount) {
                tempItem = this.tongxun_Group.getChildAt(i);
            }
            else {
                tempItem = ObjectPool.pop("AddressBookItem");
                this.tongxun_Group.addChild(tempItem);
            }
            tempItem.UpdateItem(App.PlayerManager.GetFriendlySortList()[i]);
            tempItem.visible = true;
        }
    };
    return AddressbookListUIView;
}(BaseEuiChildView));
__reflect(AddressbookListUIView.prototype, "AddressbookListUIView");
/**
 * 聊天组item
 */
var AddressBookItem = (function (_super) {
    __extends(AddressBookItem, _super);
    function AddressBookItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/skins/Wechat_tongxun_item.exml";
        _this.percentWidth = 100;
        _this.btn_item.addEventListener(egret.TouchEvent.TOUCH_TAP, function () { return _this.ClickItemBen(); }, _this);
        return _this;
    }
    AddressBookItem.prototype.UpdateItem = function (info) {
        this.info = info;
        this.name_label.text = this.info.GirlName;
        this.player.source = this.info.HeadIcon;
    };
    AddressBookItem.prototype.ClickItemBen = function () {
        App.EventMgrHelper.PushEvent(EventDef.OpenGirlInfoView, this.info.GirlId);
    };
    return AddressBookItem;
}(eui.Component));
__reflect(AddressBookItem.prototype, "AddressBookItem");
//# sourceMappingURL=AddressbookListUIView.js.map