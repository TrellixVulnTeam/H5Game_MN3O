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
var ChatOptionConfig = (function (_super) {
    __extends(ChatOptionConfig, _super);
    function ChatOptionConfig(optionID, optionNum, optionContent1, optionContent2, optionContent3, optionContent4, nextChat1, nextChat2, nextChat3, nextChat4, firendAwardGirl, friendliness, reward_num) {
        var _this = _super.call(this) || this;
        _this.optionID = optionID;
        _this.optionNum = optionNum;
        _this.optionContent1 = optionContent1;
        _this.optionContent2 = optionContent2;
        _this.optionContent3 = optionContent3;
        _this.optionContent4 = optionContent4;
        _this.nextChat1 = nextChat1;
        _this.nextChat2 = nextChat2;
        _this.nextChat3 = nextChat3;
        _this.nextChat4 = nextChat4;
        _this.firendAwardGirl = firendAwardGirl;
        _this.friendliness = friendliness;
        _this.reward_num = reward_num;
        return _this;
    }
    ChatOptionConfig.Init = function () {
        this.LoadRes();
    };
    ChatOptionConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "ChatOptionConfig") {
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
        ConfFact.SetResLoad("ChatOptionConfig");
        this.resLoaded = true;
    };
    ChatOptionConfig.Add_Item = function (rs) {
        var arr_item_len_ChatOptionConfig;
        var optionID = rs.ReadInt();
        var optionNum = rs.ReadInt();
        var optionContent1 = rs.ReadString();
        var optionContent2 = rs.ReadString();
        var optionContent3 = rs.ReadString();
        var optionContent4 = rs.ReadString();
        var nextChat1 = rs.ReadInt();
        var nextChat2 = rs.ReadInt();
        var nextChat3 = rs.ReadInt();
        var nextChat4 = rs.ReadInt();
        arr_item_len_ChatOptionConfig = rs.ReadShort();
        var firendAwardGirl = [];
        for (var i = 0; i < arr_item_len_ChatOptionConfig; ++i)
            firendAwardGirl[i] =
                rs.ReadInt();
        arr_item_len_ChatOptionConfig = rs.ReadShort();
        var friendliness = [];
        for (var i = 0; i < arr_item_len_ChatOptionConfig; ++i)
            friendliness[i] =
                rs.ReadInt();
        arr_item_len_ChatOptionConfig = rs.ReadShort();
        var reward_num = [];
        for (var i = 0; i < arr_item_len_ChatOptionConfig; ++i)
            reward_num[i] =
                rs.ReadInt();
        var new_obj_ChatOptionConfig = new ChatOptionConfig(optionID, optionNum, optionContent1, optionContent2, optionContent3, optionContent4, nextChat1, nextChat2, nextChat3, nextChat4, firendAwardGirl, friendliness, reward_num);
        if (this.ContainsKey(optionID)) {
            return;
        }
        this.dic[optionID] = new_obj_ChatOptionConfig;
        this.array.push(new_obj_ChatOptionConfig);
    };
    ChatOptionConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "ChatOptionConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    ChatOptionConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    ChatOptionConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    ChatOptionConfig.resLoaded = false;
    ChatOptionConfig.dic = {};
    ChatOptionConfig.array = [];
    return ChatOptionConfig;
}(BaseConfig));
__reflect(ChatOptionConfig.prototype, "ChatOptionConfig");
//# sourceMappingURL=ChatOptionConfig.js.map