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
var WechatUIController = (function (_super) {
    __extends(WechatUIController, _super);
    function WechatUIController() {
        var _this = _super.call(this) || this;
        _this.wechatModel = new WechatUIModel(_this);
        _this.wechatProxy = new WechatUIProxy(_this);
        _this.historyView = new WeChatHistoryUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.historyView, _this.historyView);
        _this.wechatView = new WechatUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.WechatUI, _this.wechatView);
        _this.fmcView = new FriendMCommentUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.FriendMCommentUI, _this.fmcView);
        _this.girlInfoView = new GrilDetailedInfoUiView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.GrilInfo, _this.girlInfoView);
        _this.dialoguiView = new DialogueCommentUIView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Dialogue, _this.dialoguiView);
        /**
        * 朋友圈
        */
        _this.RegisterEvent(EventDef.announceInfo);
        _this.RegisterEvent(EventDef.commentInfo);
        _this.RegisterEvent(EventDef.updateFriendsInfo);
        _this.RegisterEvent(EventDef.updateCommentInfo);
        /**聊天 */
        _this.RegisterEvent(EventDef.InquireChatInfo);
        _this.RegisterEvent(EventDef.OpenListByType);
        _this.RegisterEvent(EventDef.OpendialogView);
        _this.RegisterEvent(EventDef.BackDialogListView);
        _this.RegisterEvent(EventDef.ActivationChatGroup);
        _this.RegisterEvent(EventDef.OpendialogViewByChatId);
        /**通讯录 */
        _this.RegisterEvent(EventDef.OpenAddressBookList);
        _this.RegisterEvent(EventDef.OpenGirlInfoView);
        _this.RegisterEvent(EventDef.CloseGirlInfoView);
        _this.RegisterEvent(EventDef.OpenHistoryView);
        return _this;
    }
    WechatUIController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        switch (ev) {
            case EventDef.announceInfo:
                this.announceInfo(le.IntParam0);
                break;
            case EventDef.commentInfo:
                this.commentInfo(le.IntParam0);
                break;
            case EventDef.updateFriendsInfo:
                this.updateFriendsInfo(le.IntParam0, le.IntParam1);
                break;
            case EventDef.updateCommentInfo:
                this.updateCommentInfo(le.IntParam0, le.IntParam1);
                break;
            case EventDef.InquireChatInfo:
                this.InquireChatInfo();
                break;
            case EventDef.OpenListByType:
                this.OpenListByType(le.IntParam0);
                break;
            case EventDef.OpendialogView:
                this.OpendialogView(le.IntParam0, le.IntParam1);
                break;
            case EventDef.BackDialogListView:
                this.BackDialogListView(le.IntParam0);
                break;
            case EventDef.ActivationChatGroup:
                this.ActivationChatGroup(le.IntParam0);
                break;
            case EventDef.OpendialogViewByChatId:
                this.OpendialogViewByID(le.IntParam0, le.IntParam1);
                break;
            case EventDef.OpenAddressBookList:
                this.OpenAddressBookList();
                break;
            case EventDef.OpenGirlInfoView:
                this.OpenGirlInfoView(le.IntParam0);
                break;
            case EventDef.CloseGirlInfoView:
                this.CloseGirlInfoView();
                break;
            case EventDef.OpenHistoryView:
                this.OpenHistoryView(le.IntParam0);
                break;
        }
    };
    /**
     * 朋友圈发布消息
    */
    WechatUIController.prototype.announceInfo = function (id) {
        this.fmcView.onSetAnnounceInfoId(id);
        App.ViewManager.open(ViewConst.FriendMCommentUI);
    };
    /**
     * 朋友圈留言
    */
    WechatUIController.prototype.commentInfo = function (id) {
        this.fmcView.onSetCommentInfoId(id);
        App.ViewManager.open(ViewConst.FriendMCommentUI);
    };
    /**
     * 刷新朋友圈消息
    */
    WechatUIController.prototype.updateFriendsInfo = function (cfid, ctid) {
        this.wechatView.friendMomentUI.onUpdateAnnounceInfo(cfid, ctid);
    };
    /**
    * 刷新留言
   */
    WechatUIController.prototype.updateCommentInfo = function (cfid, ctid) {
        this.wechatView.friendMomentUI.onUpdateCommentInfo(cfid, ctid);
    };
    /**
     *  查询聊天信息
     */
    WechatUIController.prototype.InquireChatInfo = function () {
        this.wechatModel.InquireChatInfo();
    };
    /**
     * 通过类型打开列表
     */
    WechatUIController.prototype.OpenListByType = function (type) {
        if (type == WeChatGroupType.Flock) {
            this.wechatView.chatListInfoUi.UpdateList(true, type, App.WechatManager.FlockList);
        }
        else {
            this.wechatView.chatListInfoUi.UpdateList(true, type, App.WechatManager.FiendList);
        }
    };
    /**
     * 打开通讯录
     */
    WechatUIController.prototype.OpenAddressBookList = function () {
        this.wechatView.addressBookView.UpdateList();
    };
    /**
     * 打开聊天
     */
    WechatUIController.prototype.OpendialogView = function (girlId, type) {
        if (girlId === void 0) { girlId = 0; }
        if (type === void 0) { type = WechatUIType.Wechat_chat; }
        var info = App.WechatManager.GetChatListByownId(girlId);
        if (info) {
            this.wechatView.chatListInfoUi.CleraItem();
            App.ViewManager.open(ViewConst.Dialogue);
            App.WechatManager.SetLaseTimerList(info);
            this.dialoguiView.OpenByOwner(info.ownId);
        }
        //   this.dialoguiView.openType=type;
        //   if(type==WechatUIType.Wechat_record)
        //    App.ViewManager.close(ViewConst.GrilInfo);
        //    App.ViewManager.close(ViewConst.WechatUI);
    };
    /**
     * 返回聊天列表
     */
    WechatUIController.prototype.BackDialogListView = function (type) {
        if (type === void 0) { type = WechatUIType.Wechat_chat; }
        App.ViewManager.close(ViewConst.Dialogue);
        App.ViewManager.open(ViewConst.WechatUI);
        this.wechatView.SelectUIByType(type);
    };
    /**
     * 激活聊天组
     */
    WechatUIController.prototype.ActivationChatGroup = function (id) {
        App.WechatManager.AddActionChatToList(id, WeChatGroupStatus.ActivationNotTrigger, egret.getTimer());
    };
    /**
     * 打开聊天
     */
    WechatUIController.prototype.OpendialogViewByID = function (ownId, chatId) {
        this.wechatView.chatListInfoUi.CleraItem();
        App.ViewManager.open(ViewConst.Dialogue);
        this.dialoguiView.OpenByChatID(ownId, chatId);
    };
    /**
     * 打开信息页面
     */
    WechatUIController.prototype.OpenGirlInfoView = function (girlid) {
        App.ViewManager.open(ViewConst.GrilInfo);
        this.girlInfoView.InitViewInfo(girlid);
    };
    /**
    * 关闭
    */
    WechatUIController.prototype.CloseGirlInfoView = function () {
        App.ViewManager.close(ViewConst.GrilInfo);
        this.wechatView.addressBookView.UpdateList();
    };
    /**
     * 打开聊天记录
     */
    WechatUIController.prototype.OpenHistoryView = function (girlId) {
        App.ViewManager.open(ViewConst.historyView);
        this.historyView.InitView(App.WechatManager.GetChatListByownId(girlId).GetAllTriggered());
    };
    return WechatUIController;
}(BaseController));
__reflect(WechatUIController.prototype, "WechatUIController");
//# sourceMappingURL=WechatUIController.js.map