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
var ChatGroupNumConfig = (function (_super) {
    __extends(ChatGroupNumConfig, _super);
    function ChatGroupNumConfig(chatGroupID, groupHead, name) {
        var _this = _super.call(this) || this;
        _this.chatGroupID = chatGroupID;
        _this.groupHead = groupHead;
        _this.name = name;
        return _this;
    }
    ChatGroupNumConfig.Init = function () {
        this.LoadRes();
    };
    ChatGroupNumConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "ChatGroupNumConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 3) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("ChatGroupNumConfig");
        this.resLoaded = true;
    };
    ChatGroupNumConfig.Add_Item = function (rs) {
        var chatGroupID = rs.ReadInt();
        var groupHead = rs.ReadString();
        var name = rs.ReadString();
        var new_obj_ChatGroupNumConfig = new ChatGroupNumConfig(chatGroupID, groupHead, name);
        if (this.ContainsKey(chatGroupID)) {
            return;
        }
        this.dic[chatGroupID] = new_obj_ChatGroupNumConfig;
        this.array.push(new_obj_ChatGroupNumConfig);
    };
    ChatGroupNumConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "ChatGroupNumConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    ChatGroupNumConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    ChatGroupNumConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    ChatGroupNumConfig.resLoaded = false;
    ChatGroupNumConfig.dic = {};
    ChatGroupNumConfig.array = [];
    return ChatGroupNumConfig;
}(BaseConfig));
__reflect(ChatGroupNumConfig.prototype, "ChatGroupNumConfig");
//# sourceMappingURL=ChatGroupNumConfig.js.map