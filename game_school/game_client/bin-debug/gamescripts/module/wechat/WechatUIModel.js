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
var WechatUIModel = (function (_super) {
    __extends(WechatUIModel, _super);
    function WechatUIModel($controller) {
        var _this = _super.call(this, $controller) || this;
        _this.InquireChatInfo();
        return _this;
    }
    //测试数据
    WechatUIModel.prototype.InquireChatInfo = function () {
        for (var i = 0; i < ChatGroupConfig.array.length; i++) {
            App.WechatManager.AddActionChatToList(ChatGroupConfig.array[i].chatID, WeChatGroupStatus.ActivationNotTrigger, egret.getTimer());
        }
    };
    return WechatUIModel;
}(BaseModel));
__reflect(WechatUIModel.prototype, "WechatUIModel");
//# sourceMappingURL=WechatUIModel.js.map