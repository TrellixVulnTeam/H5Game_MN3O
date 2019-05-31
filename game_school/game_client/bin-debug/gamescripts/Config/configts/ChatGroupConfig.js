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
var ChatGroupConfig = (function (_super) {
    __extends(ChatGroupConfig, _super);
    function ChatGroupConfig(chatID, type, belong, chatName, startChatID, triggerType, param1, param2, param3, param4, param5, reward, reward_num) {
        var _this = _super.call(this) || this;
        _this.chatID = chatID;
        _this.type = type;
        _this.belong = belong;
        _this.chatName = chatName;
        _this.startChatID = startChatID;
        _this.triggerType = triggerType;
        _this.param1 = param1;
        _this.param2 = param2;
        _this.param3 = param3;
        _this.param4 = param4;
        _this.param5 = param5;
        _this.reward = reward;
        _this.reward_num = reward_num;
        return _this;
    }
    ChatGroupConfig.Init = function () {
        this.LoadRes();
    };
    ChatGroupConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "ChatGroupConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 13) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("ChatGroupConfig");
        this.resLoaded = true;
    };
    ChatGroupConfig.Add_Item = function (rs) {
        var arr_item_len_ChatGroupConfig;
        var chatID = rs.ReadInt();
        var type = rs.ReadInt();
        var belong = rs.ReadInt();
        var chatName = rs.ReadString();
        var startChatID = rs.ReadInt();
        var triggerType = rs.ReadInt();
        var param1 = rs.ReadInt();
        var param2 = rs.ReadInt();
        var param3 = rs.ReadInt();
        var param4 = rs.ReadFloat();
        var param5 = rs.ReadFloat();
        arr_item_len_ChatGroupConfig = rs.ReadShort();
        var reward = [];
        for (var i = 0; i < arr_item_len_ChatGroupConfig; ++i)
            reward[i] =
                rs.ReadInt();
        arr_item_len_ChatGroupConfig = rs.ReadShort();
        var reward_num = [];
        for (var i = 0; i < arr_item_len_ChatGroupConfig; ++i)
            reward_num[i] =
                rs.ReadInt();
        var new_obj_ChatGroupConfig = new ChatGroupConfig(chatID, type, belong, chatName, startChatID, triggerType, param1, param2, param3, param4, param5, reward, reward_num);
        if (this.ContainsKey(chatID)) {
            return;
        }
        this.dic[chatID] = new_obj_ChatGroupConfig;
        this.array.push(new_obj_ChatGroupConfig);
    };
    ChatGroupConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "ChatGroupConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    ChatGroupConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    ChatGroupConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    ChatGroupConfig.resLoaded = false;
    ChatGroupConfig.dic = {};
    ChatGroupConfig.array = [];
    return ChatGroupConfig;
}(BaseConfig));
__reflect(ChatGroupConfig.prototype, "ChatGroupConfig");
//# sourceMappingURL=ChatGroupConfig.js.map