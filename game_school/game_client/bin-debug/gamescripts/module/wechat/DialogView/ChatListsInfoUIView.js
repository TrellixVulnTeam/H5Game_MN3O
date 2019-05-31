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
 * 聊天组列表子签
 */
var ChatListsInfoUIView = (function (_super) {
    __extends(ChatListsInfoUIView, _super);
    function ChatListsInfoUIView($controller, $parent, key) {
        var _this = _super.call(this, $controller, $parent, key) || this;
        _this.frientIsOpen = false; //好友列表是否打开
        _this.flockIsOpen = false; //群聊列表是否打开
        _this.friendItemList = []; //私聊列表
        _this.flockItemList = []; //群聊列表
        _this.onInitUI();
        return _this;
    }
    ChatListsInfoUIView.prototype.onInitUI = function () {
        var _this = this;
        this.chat_back = this.myParent.getChildByName("chat_back");
        this.py_talk = this.myParent.getChildByName("py_talk");
        this.talk_Group = this.py_talk.getChildByName("talk_Group");
        this.frinde_TreeNode_Title = this.talk_Group.getChildByName("frinde_TreeNode_Title");
        this.flock_TreeNode_Title = this.talk_Group.getChildByName("flock_TreeNode_Title");
        // this.btn_friend=this.frinde_TreeNode_Title.getChildByName("btn_friend")as eui.Button;
        // this.btn_flock=this.flock_TreeNode_Title.getChildByName("btn_flock")as eui.Button;
        this.chat_back.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.close(_this._key);
        }, this);
        //	 this.btn_flock.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickBtnEventListener,this);
        //	 this.btn_friend.addEventListener(egret.TouchEvent.TOUCH_TAP,this.OnClickBtnEventListener,this);
    };
    /**
     * 打开页面
     */
    ChatListsInfoUIView.prototype.onChildGroupShow = function () {
        _super.prototype.onChildGroupShow.call(this);
        this.CleraItem();
        //this.applyFunc(WechatUIConst.InquireChatInfo);
        //this.UpdateList(false,WeChatGroupType.Friend);
        //this.UpdateList(false,WeChatGroupType.Flock);
        App.EventMgrHelper.PushEvent(EventDef.OpenListByType, WeChatGroupType.Friend);
    };
    /**
     * 展开或关闭列表
     */
    ChatListsInfoUIView.prototype.OnClickBtnEventListener = function (event) {
        if (event.target == this.btn_flock) {
            this.flockIsOpen = !this.flockIsOpen;
            if (this.flockIsOpen) {
                App.EventMgrHelper.PushEvent(EventDef.OpenListByType, WeChatGroupType.Flock);
            }
            else {
                this.UpdateList(false, WeChatGroupType.Flock);
            }
        }
        else {
            this.frientIsOpen = !this.frientIsOpen;
            if (this.frientIsOpen) {
                App.EventMgrHelper.PushEvent(EventDef.OpenListByType, WeChatGroupType.Friend);
            }
            else {
                this.UpdateList(false, WeChatGroupType.Friend);
            }
        }
    };
    /**
     * 更新列表
     */
    ChatListsInfoUIView.prototype.UpdateList = function (open, type, infos) {
        var _this = this;
        if (open) {
            if (infos && infos.length > 0) {
                var currentList = (type == WeChatGroupType.Friend) ? this.friendItemList : this.flockItemList;
                for (var i = 0; i < infos.length; i++) {
                    if (i < length) {
                        currentList[i].UpdateItem(infos[i]);
                    }
                    else {
                        var item = ObjectPool.pop("ChatListItem");
                        currentList.push(item);
                        item.UpdateItem(infos[i]);
                    }
                    currentList[i].visible = true;
                }
            }
            else {
                //没有激活的聊天组，待处理
            }
        }
        else {
            if (type == WeChatGroupType.Flock) {
                this.flockItemList.forEach(function (element) {
                    element.visible = false;
                    _this.talk_Group.removeChild(element);
                    ObjectPool.push(element);
                });
                this.flockItemList.splice(0, this.flockItemList.length);
            }
            else {
                this.friendItemList.forEach(function (element) {
                    element.visible = false;
                    _this.talk_Group.removeChild(element);
                    ObjectPool.push(element);
                });
                this.friendItemList.splice(0, this.friendItemList.length);
            }
        }
        this.UpdateItemViewIndex();
    };
    /**
     * 清空
     */
    ChatListsInfoUIView.prototype.CleraItem = function () {
        var _this = this;
        this.flockItemList.forEach(function (element) {
            _this.talk_Group.removeChild(element);
            ObjectPool.push(element);
            element.visible = false;
        });
        this.flockItemList.splice(0, this.flockItemList.length);
        this.friendItemList.forEach(function (element) {
            _this.talk_Group.removeChild(element);
            ObjectPool.push(element);
            element.visible = false;
        });
        this.friendItemList.splice(0, this.friendItemList.length);
    };
    /**
     * 更新列表的位置
     */
    ChatListsInfoUIView.prototype.UpdateItemViewIndex = function () {
        // this.talk_Group.setChildIndex(this.frinde_TreeNode_Title,0);//私聊标题永远在最上
        for (var i = 0; i < this.friendItemList.length; i++) {
            this.talk_Group.addChildAt(this.friendItemList[i], i);
        }
        //  this.talk_Group.setChildIndex(this.flock_TreeNode_Title,this.friendItemList.length+1);
        //  let indexFlockTitle=this.talk_Group.getChildIndex(this.flock_TreeNode_Title)+1;
        //  for(let i=0;i<this.flockItemList.length;i++){
        // 	 this.talk_Group.addChildAt(this.flockItemList[i],indexFlockTitle+i);
        //  }
    };
    return ChatListsInfoUIView;
}(BaseEuiChildView));
__reflect(ChatListsInfoUIView.prototype, "ChatListsInfoUIView");
/**
 * 聊天组item
 */
var ChatListItem = (function (_super) {
    __extends(ChatListItem, _super);
    function ChatListItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/skins/Wechat_List_Item.exml";
        _this.percentWidth = 100;
        _this.item_btn.addEventListener(egret.TouchEvent.TOUCH_TAP, function () { return _this.ClickItemBen(); }, _this);
        return _this;
    }
    ChatListItem.prototype.UpdateItem = function (info) {
        this.info = info;
        if (this.info.currentType == WeChatGroupType.Flock) {
            this.flockConf = ChatGroupNumConfig.GetConfig(this.info.ownId);
            this.laebl_name.text = this.flockConf.name;
            this.image_playericon.source = this.flockConf.groupHead;
        }
        else {
            this.laebl_name.text = info.Owner.GirlName;
            this.image_playericon.source = info.Owner.HeadIcon;
        }
        this.image_newfriend0.visible = this.info.IsExistNoTrigger();
        var text = this.info.GetLastSentence();
        if (text.length > 18) {
            text = text.substr(0, 16) + "...";
        }
        this.laebl_mess.text = text;
    };
    ChatListItem.prototype.ClickItemBen = function () {
        App.EventMgrHelper.PushEvent(EventDef.OpendialogView, this.info.ownId);
    };
    return ChatListItem;
}(eui.Component));
__reflect(ChatListItem.prototype, "ChatListItem");
//# sourceMappingURL=ChatListsInfoUIView.js.map