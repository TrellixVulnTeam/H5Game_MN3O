/**
 * 通信(wechat)管理类
*/
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
 * 聊天组状态
 */
var WeChatGroupStatus;
(function (WeChatGroupStatus) {
    WeChatGroupStatus[WeChatGroupStatus["Inactivated"] = 0] = "Inactivated";
    WeChatGroupStatus[WeChatGroupStatus["ActivationNotTrigger"] = 1] = "ActivationNotTrigger";
    WeChatGroupStatus[WeChatGroupStatus["Triggered"] = 2] = "Triggered"; //已触发
})(WeChatGroupStatus || (WeChatGroupStatus = {}));
/**
  * 聊天类型
  */
var WeChatGroupType;
(function (WeChatGroupType) {
    WeChatGroupType[WeChatGroupType["Friend"] = 0] = "Friend";
    WeChatGroupType[WeChatGroupType["Flock"] = 1] = "Flock"; //群组聊天
})(WeChatGroupType || (WeChatGroupType = {}));
var WechatManager = (function (_super) {
    __extends(WechatManager, _super);
    function WechatManager() {
        var _this = _super.call(this) || this;
        /**朋友圈 */
        _this.alreadyAnnId = new Array(); //发布的朋友圈id(WechatConfig)
        /**聊天 */
        _this.ownChatList = []; //当前激活的聊天
        _this.ownChatIdList = []; //与聊天集合对应的归属id集合
        _this.fiendList = []; //私聊集合
        _this.flockList = []; //群聊集合
        return _this;
    }
    Object.defineProperty(WechatManager.prototype, "OwnChatIdList", {
        get: function () { return this.ownChatIdList; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(WechatManager.prototype, "OwnChatList", {
        get: function () { return this.ownChatList; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(WechatManager.prototype, "FlockList", {
        get: function () { return this.flockList; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(WechatManager.prototype, "FiendList", {
        get: function () { return this.fiendList; },
        enumerable: true,
        configurable: true
    });
    /**聊天 */
    /**
    * 通过归属id获取聊天集合
    */
    WechatManager.prototype.GetChatListByownId = function (ownId) {
        var index = this.ownChatIdList.indexOf(ownId);
        if (index != -1) {
            return this.ownChatList[index];
        }
        else {
            return null;
        }
    };
    /**
     * 通过id获取聊天组
     */
    WechatManager.prototype.GetChatById = function (ownID, id) {
        return this.GetChatListByownId(ownID).GetChatByID(id);
        ;
    };
    /**
    * 有激活的聊天组添加到列表
    */
    WechatManager.prototype.AddActionChatToList = function (id, statu, timer) {
        var _this = this;
        if (statu === void 0) { statu = WeChatGroupStatus.ActivationNotTrigger; }
        if (timer === void 0) { timer = egret.getTimer(); }
        if (statu != WeChatGroupStatus.Inactivated) {
            var config = ChatGroupConfig.GetConfig(id);
            if (config) {
                var index = this.ownChatIdList.indexOf(config.belong);
                var list = void 0;
                App.PlayerManager.GetGirl(config.belong);
                if (index != -1) {
                    list = this.ownChatList[index];
                    this.ownChatIdList[index] = config.belong;
                    list.AddInfo(id, statu, timer);
                }
                else {
                    list = new ChatOwnList(config.belong);
                    this.ownChatIdList.push(config.belong);
                    this.ownChatList.push(list);
                    list.AddInfo(id, statu, timer);
                }
                if (list.currentType == WeChatGroupType.Flock) {
                    this.AddChatToFlockList(list);
                }
                else {
                    this.AddChatToFiendList(list);
                }
                this.ownChatList.sort(function (a, b) { return _this.ChatListSort(a, b); });
                this.ownChatIdList.splice(0, this.ownChatIdList.length);
                this.ownChatList.forEach(function (element) {
                    _this.ownChatIdList.push(element.ownId);
                });
            }
        }
        else {
            //未激活的待处理
        }
    };
    /**
    * 添加到私聊列表
    */
    WechatManager.prototype.AddChatToFiendList = function (list) {
        var _this = this;
        for (var i = 0; i < this.fiendList.length; i++) {
            if (this.fiendList[i].ownId == list.ownId) {
                this.fiendList[i] = list;
                this.fiendList.sort(function (a, b) { return _this.ChatListSort(a, b); });
                return;
            }
        }
        this.fiendList.push(list);
        this.fiendList.sort(function (a, b) { return _this.ChatListSort(a, b); });
    };
    /**
    * 添加到群聊列表
    */
    WechatManager.prototype.AddChatToFlockList = function (list) {
        var _this = this;
        for (var i = 0; i < this.flockList.length; i++) {
            if (this.flockList[i].ownId == list.ownId) {
                this.flockList[i] = list;
                this.flockList.sort(function (a, b) { return _this.ChatListSort(a, b); });
                return;
            }
        }
        this.flockList.push(list);
        this.flockList.sort(function (a, b) { return _this.ChatListSort(a, b); });
    };
    /**
     * 设置最后打开时间修改时间
     */
    WechatManager.prototype.SetLaseTimerList = function (info) {
        var _this = this;
        info.Timer = egret.getTimer();
        this.flockList.sort(function (a, b) { return _this.ChatListSort(a, b); });
        this.fiendList.sort(function (a, b) { return _this.ChatListSort(a, b); });
        this.ownChatList.sort(function (a, b) { return _this.ChatListSort(a, b); });
        this.ownChatIdList.splice(0, this.ownChatIdList.length);
        this.ownChatList.forEach(function (element) {
            _this.ownChatIdList.push(element.ownId);
        });
    };
    /**
     * 同状态  按最后一次读取时间 倒叙
     */
    WechatManager.prototype.ChatListSort = function (a, b) {
        if (a.ishaveNt == b.ishaveNt) {
            if (a.Timer == b.Timer)
                return b.ownId - a.ownId;
            return b.Timer - a.Timer;
        }
        else if (a.ishaveNt) {
            return 1;
        }
        else {
            return -1;
        }
    };
    /**朋友圈 */
    /**
     * 添加正在显示的朋友圈动态id（需要读服务器数据）
    */
    WechatManager.prototype.addAlreadyAnnId = function (confid) {
        this.alreadyAnnId.push(confid);
    };
    Object.defineProperty(WechatManager.prototype, "AlreadyAnnIds", {
        /**
         * 获取朋友圈动态id
        */
        get: function () {
            return this.alreadyAnnId;
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 朋友圈是否有动态可以发布
    */
    WechatManager.prototype.isFriendMomentAnnounce = function () {
        if (this.prepareAnnId.length > 0) {
            return true;
        }
        else {
            return false;
        }
    };
    return WechatManager;
}(BaseManager));
__reflect(WechatManager.prototype, "WechatManager");
/**
 * 聊天归属集合
 */
var ChatOwnList = (function () {
    function ChatOwnList(ownId) {
        this.ishaveNt = false; //是否拥有未触发的聊天
        this.ownInfos = []; //拥有的聊天
        this.ownIds = []; //拥有聊天的id
        this.currentId = 0; //当前对话id
        this.ownId = ownId;
        this.owner = App.PlayerManager.GetGirl(ownId);
    }
    Object.defineProperty(ChatOwnList.prototype, "Timer", {
        get: function () { return this.timer; },
        set: function (value) { this.timer = value; } //以后可能要保存
        ,
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ChatOwnList.prototype, "Owner", {
        get: function () { return this.owner; },
        enumerable: true,
        configurable: true
    });
    /**
     * 新增聊天组
     */
    ChatOwnList.prototype.AddInfo = function (id, statu, timer) {
        var _this = this;
        var info = new WechatGroupInfo(id, statu, timer);
        this.currentType = info.CurrentType;
        this.timer = timer;
        var index = this.ownIds.indexOf(id);
        if (index != -1) {
            this.ownId[index] = id;
            this.ownInfos[index] = info;
        }
        else {
            this.ownIds.push(id);
            this.ownInfos.push(info);
        }
        if (info.CurrentStatus == WeChatGroupStatus.ActivationNotTrigger)
            this.ishaveNt = true;
        this.ownInfos.sort(function (a, b) { return b.ActivTimer - a.ActivTimer; });
        this.ownIds.splice(0, this.ownIds.length);
        this.ownInfos.forEach(function (element) {
            _this.ownIds.push(element.ID);
        });
    };
    /**
     * 获取当前聊天
     * 按激活顺序的第一个未触发的信息
     * 如果没有返回最后一个
     */
    ChatOwnList.prototype.GetCurrentChat = function () {
        if (this.ownInfos) {
            if (this.currentId != 0) {
                return this.GetChatByID(this.currentId);
            }
            else {
                for (var i = 0; i < this.ownInfos.length; i++) {
                    if (this.ownInfos[i].CurrentStatus == WeChatGroupStatus.ActivationNotTrigger) {
                        this.currentId = this.ownInfos[i].ID;
                        return this.ownInfos[i];
                    }
                }
                if (this.ownInfos.length > 0) {
                    this.currentId = this.ownInfos[this.ownInfos.length - 1].ID;
                    return this.ownInfos[this.ownInfos.length - 1];
                }
                else {
                    return null;
                }
            }
        }
        else {
            return null;
        }
    };
    /**
     * 获取下一个聊天
     */
    ChatOwnList.prototype.GetNextChat = function () {
        if (this.currentId != 0) {
            var index = this.ownIds.indexOf(this.currentId);
            if (index != -1) {
                if (index < this.ownInfos.length - 1) {
                    this.currentId = this.ownInfos[index + 1].ID;
                    return this.ownInfos[index + 1];
                }
                else {
                    return null;
                }
            }
            else {
                return this.GetCurrentChat();
            }
        }
        else {
            return this.GetCurrentChat();
        }
    };
    /**
     * 获取上一个聊天
     */
    ChatOwnList.prototype.GetLastChat = function () {
        if (this.currentId != 0) {
            var index = this.ownIds.indexOf(this.currentId);
            if (index != -1) {
                if (index > 0) {
                    this.currentId = this.ownInfos[index - 1].ID;
                    return this.ownInfos[index - 1];
                }
                else {
                    return null;
                }
            }
            else {
                return this.GetCurrentChat();
            }
        }
        else {
            return this.GetCurrentChat();
        }
    };
    /**
     * 获取最后一个已经触发的聊天
     */
    ChatOwnList.prototype.GetLastChatByStatu = function () {
        for (var i = this.ownInfos.length - 1; i >= 0; i--) {
            if (this.ownInfos[i].CurrentStatus == WeChatGroupStatus.Triggered) {
                return this.ownInfos[i];
            }
        }
        return null;
    };
    /**
    * 获取所有已经触发的聊天
    */
    ChatOwnList.prototype.GetAllTriggered = function () {
        var tempList = [];
        for (var i = 0; i < this.ownInfos.length; i++) {
            if (this.ownInfos[i].CurrentStatus == WeChatGroupStatus.Triggered) {
                tempList.push(this.ownInfos[i]);
            }
        }
        return tempList;
    };
    /**
     * 获取最后一句话
     */
    ChatOwnList.prototype.GetLastSentence = function () {
        if (this.currentId != 0 && (this.ownIds.indexOf(this.currentId) != -1)) {
            return this.GetChatByID(this.currentId).LastSentence;
        }
        else {
            var info = this.GetLastChatByStatu();
            if (info) {
                return info.LastSentence;
            }
            else {
                info = this.GetCurrentChat();
                if (info) {
                    return info.LastSentence;
                }
                else {
                    return "";
                }
            }
        }
    };
    /**
     * 通过id获取聊天组
     */
    ChatOwnList.prototype.GetChatByID = function (id) {
        var index = this.ownIds.indexOf(id);
        if (index != -1) {
            return this.ownInfos[index];
        }
        else {
            return null;
        }
    };
    /**
     * 是否存在激活未出发的聊天
     */
    ChatOwnList.prototype.IsExistNoTrigger = function () {
        for (var i = 0; i < this.ownInfos.length; i++) {
            if (this.ownInfos[i].CurrentStatus == WeChatGroupStatus.ActivationNotTrigger) {
                return true;
            }
        }
        return false;
    };
    return ChatOwnList;
}());
__reflect(ChatOwnList.prototype, "ChatOwnList");
/**
 * 聊天组信息
 */
var WechatGroupInfo = (function () {
    function WechatGroupInfo(id, statu, timer) {
        if (statu === void 0) { statu = WeChatGroupStatus.ActivationNotTrigger; }
        this.pastChatList = []; //已经聊过
        this.lastchatId = 0; //聊天进度
        this.mSelectMap = {};
        this.id = id;
        this.currentStatus = statu;
        this.mChatConfig = ChatGroupConfig.GetConfig(id);
        this.currentType = this.mChatConfig.type;
        this.activTimer = timer;
        this.ownObjId = this.mChatConfig.belong;
        this.lastchatId = this.mChatConfig.startChatID;
        this.owner = App.PlayerManager.GetGirl(this.ownObjId);
        var chatCon = ChatConfig.GetConfig(this.mChatConfig.startChatID);
        if (chatCon) {
            if (chatCon.type == 0) {
                this.lastSentence = "";
            }
            else {
                if (chatCon.npcDialogType == 1) {
                    this.lastSentence = chatCon.content;
                }
                else {
                    this.lastSentence = "[语音通话]";
                }
            }
        }
        else {
            this.lastSentence = "";
        }
    }
    Object.defineProperty(WechatGroupInfo.prototype, "ActivTimer", {
        get: function () { return this.activTimer; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(WechatGroupInfo.prototype, "LastSentence", {
        get: function () { return this.lastSentence; },
        set: function (value) { this.lastSentence = value; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(WechatGroupInfo.prototype, "ID", {
        get: function () { return this.id; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(WechatGroupInfo.prototype, "CurrentType", {
        get: function () { return this.currentType; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(WechatGroupInfo.prototype, "OwnObjId", {
        get: function () { return this.ownObjId; },
        enumerable: true,
        configurable: true
    });
    /**
     * 添加到已聊天
     */
    WechatGroupInfo.prototype.AddToPast = function (id) {
        var index = this.pastChatList.indexOf(id);
        if (index != -1) {
            this.pastChatList[index] = id;
        }
        else {
            this.pastChatList.push(id);
        }
    };
    /**
     * 检测是否是已经聊过
     */
    WechatGroupInfo.prototype.FindPastChat = function (id) {
        var index = this.pastChatList.indexOf(id);
        if (index != -1) {
            return true;
        }
        else {
            return false;
        }
    };
    Object.defineProperty(WechatGroupInfo.prototype, "CurrentStatus", {
        get: function () { return this.currentStatus; },
        set: function (statu) {
            if (this.currentStatus != WeChatGroupStatus.Triggered && statu == WeChatGroupStatus.Triggered) {
                this.owner.SetFriendlyNum(this.mChatConfig.param2);
            }
            this.currentStatus = statu;
        },
        enumerable: true,
        configurable: true
    });
    return WechatGroupInfo;
}());
__reflect(WechatGroupInfo.prototype, "WechatGroupInfo");
//# sourceMappingURL=WechatManager.js.map