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
var ChatConfig = (function (_super) {
    __extends(ChatConfig, _super);
    function ChatConfig(chatId, nextId, chatType, type, head, name, npcDialogType, content, voice, playerDialogType, optionID) {
        var _this = _super.call(this) || this;
        _this.chatId = chatId;
        _this.nextId = nextId;
        _this.chatType = chatType;
        _this.type = type;
        _this.head = head;
        _this.name = name;
        _this.npcDialogType = npcDialogType;
        _this.content = content;
        _this.voice = voice;
        _this.playerDialogType = playerDialogType;
        _this.optionID = optionID;
        return _this;
    }
    ChatConfig.Init = function () {
        this.LoadRes();
    };
    ChatConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "ChatConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 11) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("ChatConfig");
        this.resLoaded = true;
    };
    ChatConfig.Add_Item = function (rs) {
        var chatId = rs.ReadInt();
        var nextId = rs.ReadInt();
        var chatType = rs.ReadInt();
        var type = rs.ReadInt();
        var head = rs.ReadString();
        var name = rs.ReadString();
        var npcDialogType = rs.ReadInt();
        var content = rs.ReadString();
        var voice = rs.ReadString();
        var playerDialogType = rs.ReadInt();
        var optionID = rs.ReadInt();
        var new_obj_ChatConfig = new ChatConfig(chatId, nextId, chatType, type, head, name, npcDialogType, content, voice, playerDialogType, optionID);
        if (this.ContainsKey(chatId)) {
            return;
        }
        this.dic[chatId] = new_obj_ChatConfig;
        this.array.push(new_obj_ChatConfig);
    };
    ChatConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "ChatConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    ChatConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    ChatConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    ChatConfig.resLoaded = false;
    ChatConfig.dic = {};
    ChatConfig.array = [];
    return ChatConfig;
}(BaseConfig));
__reflect(ChatConfig.prototype, "ChatConfig");
//# sourceMappingURL=ChatConfig.js.map