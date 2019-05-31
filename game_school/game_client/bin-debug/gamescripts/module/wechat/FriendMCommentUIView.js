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
 * 朋友圈发布消息和留言选择界面
*/
var FriendMCommentUIView = (function (_super) {
    __extends(FriendMCommentUIView, _super);
    function FriendMCommentUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.addEventListener(eui.UIEvent.COMPLETE, _this.uiCompHandler, _this);
        return _this;
    }
    FriendMCommentUIView.prototype.uiCompHandler = function () {
        this.image_back.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClose, this);
    };
    FriendMCommentUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.FriendMCommentUI);
    };
    FriendMCommentUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    FriendMCommentUIView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
        this.gro_all.removeChildren();
    };
    FriendMCommentUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        if (this.isAnnounce == true) {
            this.onSetAnnounceUIInfo();
        }
        else {
            this.onSetCommentUIInfo();
        }
    };
    /**
     * 显示发布朋友圈选项
    */
    FriendMCommentUIView.prototype.onSetAnnounceInfoId = function (id) {
        this.infoId = id;
        this.isAnnounce = true;
    };
    /**
     * 显示朋友圈留言选项
    */
    FriendMCommentUIView.prototype.onSetCommentInfoId = function (id) {
        this.infoId = id;
        this.isAnnounce = false;
    };
    /**
     * 发布朋友圈消息
    */
    FriendMCommentUIView.prototype.onSetAnnounceUIInfo = function () {
        var config = WechatConfig.GetConfig(this.infoId);
        for (var index = 0; index < config.contentId.length; index++) {
            var mess = new FCSelectMessage(config.id, config.contentId[index]);
            mess.onSetAnnounceContent(function () { this.onClose(); }.bind(this));
            this.gro_all.addChild(mess);
        }
    };
    /**
     * 朋友圈留言
    */
    FriendMCommentUIView.prototype.onSetCommentUIInfo = function () {
        var config = WechatConfig.GetConfig(this.infoId);
        for (var index = 0; index < config.talks.length; index++) {
            var mess = new FCSelectMessage(config.id, config.talks[index]);
            mess.onSeCommenttContent(config.friendliness[index], function () { this.onClose(); }.bind(this));
            this.gro_all.addChild(mess);
        }
    };
    return FriendMCommentUIView;
}(BaseEuiView));
__reflect(FriendMCommentUIView.prototype, "FriendMCommentUIView");
/**
 * 选择内容
*/
var FCSelectMessage = (function (_super) {
    __extends(FCSelectMessage, _super);
    function FCSelectMessage(cfid, ctid) {
        var _this = _super.call(this, null, null) || this;
        _this.configid = cfid;
        _this.contentid = ctid;
        _this.skinName = "resource/skins/Wechat_dia_item.exml";
        return _this;
    }
    /**
     * 发布消息
    */
    FCSelectMessage.prototype.onSetAnnounceContent = function (callback) {
        var config = WechatContentConfig.GetConfig(this.contentid);
        this.label_dia.text = config.choiceContent;
        this.button_dia.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            if (callback != null) {
                callback();
            }
            this.onSelectAnnounce();
        }.bind(this), this);
    };
    /**
     * 发布成功，刷新朋友圈消息
    */
    FCSelectMessage.prototype.onSelectAnnounce = function () {
        App.EventMgrHelper.PushEvent(EventDef.updateFriendsInfo, this.configid, this.contentid);
    };
    /**
     * 留言
    */
    FCSelectMessage.prototype.onSeCommenttContent = function (friendliness, callback) {
        var config = WechatContentConfig.GetConfig(this.contentid);
        this.label_dia.text = config.choiceContent;
        this.button_dia.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            if (callback != null) {
                callback();
            }
            this.onSelectRevert(StrConfigManager.getStrById(1001) + friendliness.toString());
        }.bind(this), this);
    };
    /**
     * 留言成功，增加好感度提示，刷新留言
    */
    FCSelectMessage.prototype.onSelectRevert = function (content) {
        App.EventMgrHelper.PushEvent(EventDef.updateCommentInfo, this.configid, this.contentid);
        App.EventMgrHelper.PushEvent(EventDef.Friendliness_tips, -1, -1, content);
    };
    return FCSelectMessage;
}(BaseEuiView));
__reflect(FCSelectMessage.prototype, "FCSelectMessage");
//# sourceMappingURL=FriendMCommentUIView.js.map