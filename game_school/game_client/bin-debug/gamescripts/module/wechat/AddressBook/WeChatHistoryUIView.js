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
 * 聊天记录
 */
var WeChatHistoryUIView = (function (_super) {
    __extends(WeChatHistoryUIView, _super);
    function WeChatHistoryUIView($controller, $parent) {
        return _super.call(this, $controller, $parent) || this;
    }
    WeChatHistoryUIView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.historyView);
        this.btn_chatback.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.close(_this._key);
        }, this);
    };
    WeChatHistoryUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
    };
    WeChatHistoryUIView.prototype.InitView = function (girlChat) {
        if (!girlChat)
            return;
        var num = this.scr_playertalk.numElements;
        for (var j = 0; j < num; j++) {
            var item = void 0;
            if (j < girlChat.length) {
                item = this.scr_playertalk.getChildAt(j);
                item.visible = true;
                item.UpdateItem(girlChat[j]);
            }
            else {
                item = this.scr_playertalk.getChildAt(this.scr_playertalk.numElements - 1);
                item.visible = false;
                ObjectPool.push(item);
                this.scr_playertalk.removeChild(item);
            }
        }
        var index = this.scr_playertalk.numElements;
        for (var y = index; y < girlChat.length; y++) {
            var item = ObjectPool.pop("HistoryItem");
            item.UpdateItem(girlChat[y]);
            item.visible = true;
            this.scr_playertalk.addChild(item);
        }
    };
    return WeChatHistoryUIView;
}(BaseEuiView));
__reflect(WeChatHistoryUIView.prototype, "WeChatHistoryUIView");
/**
 * 聊天记录item
 */
var HistoryItem = (function (_super) {
    __extends(HistoryItem, _super);
    function HistoryItem($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.skinName = "resource/skins/Wechat_history_item.exml";
        _this.btn_choose.addEventListener(egret.TouchEvent.TOUCH_TAP, _this.OnClickChooseBtn, _this);
        return _this;
    }
    HistoryItem.prototype.UpdateItem = function (info) {
        this.info = info;
        this.label_name.text = info.mChatConfig.chatName;
    };
    HistoryItem.prototype.OnClickChooseBtn = function () {
        App.ViewManager.close(ViewConst.historyView);
        App.EventMgrHelper.PushEvent(EventDef.OpendialogViewByChatId, this.info.OwnObjId, this.info.ID);
    };
    return HistoryItem;
}(BaseEuiView));
__reflect(HistoryItem.prototype, "HistoryItem");
//# sourceMappingURL=WeChatHistoryUIView.js.map