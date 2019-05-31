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
var WechatConfig = (function (_super) {
    __extends(WechatConfig, _super);
    function WechatConfig(id, personID, days, head, name, contentId, pic, talks, friendliness, otherReply, type, param1, param2, param3, param4, param5) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.personID = personID;
        _this.days = days;
        _this.head = head;
        _this.name = name;
        _this.contentId = contentId;
        _this.pic = pic;
        _this.talks = talks;
        _this.friendliness = friendliness;
        _this.otherReply = otherReply;
        _this.type = type;
        _this.param1 = param1;
        _this.param2 = param2;
        _this.param3 = param3;
        _this.param4 = param4;
        _this.param5 = param5;
        return _this;
    }
    WechatConfig.Init = function () {
        this.LoadRes();
    };
    WechatConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "WechatConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 16) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("WechatConfig");
        this.resLoaded = true;
    };
    WechatConfig.Add_Item = function (rs) {
        var arr_item_len_WechatConfig;
        var id = rs.ReadInt();
        var personID = rs.ReadInt();
        var days = rs.ReadInt();
        var head = rs.ReadString();
        var name = rs.ReadString();
        arr_item_len_WechatConfig = rs.ReadShort();
        var contentId = [];
        for (var i = 0; i < arr_item_len_WechatConfig; ++i)
            contentId[i] =
                rs.ReadInt();
        var pic = rs.ReadString();
        arr_item_len_WechatConfig = rs.ReadShort();
        var talks = [];
        for (var i = 0; i < arr_item_len_WechatConfig; ++i)
            talks[i] =
                rs.ReadInt();
        arr_item_len_WechatConfig = rs.ReadShort();
        var friendliness = [];
        for (var i = 0; i < arr_item_len_WechatConfig; ++i)
            friendliness[i] =
                rs.ReadInt();
        arr_item_len_WechatConfig = rs.ReadShort();
        var otherReply = [];
        for (var i = 0; i < arr_item_len_WechatConfig; ++i)
            otherReply[i] =
                rs.ReadInt();
        var type = rs.ReadInt();
        var param1 = rs.ReadInt();
        var param2 = rs.ReadInt();
        var param3 = rs.ReadInt();
        var param4 = rs.ReadFloat();
        var param5 = rs.ReadFloat();
        var new_obj_WechatConfig = new WechatConfig(id, personID, days, head, name, contentId, pic, talks, friendliness, otherReply, type, param1, param2, param3, param4, param5);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_WechatConfig;
        this.array.push(new_obj_WechatConfig);
    };
    WechatConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "WechatConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    WechatConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    WechatConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    WechatConfig.resLoaded = false;
    WechatConfig.dic = {};
    WechatConfig.array = [];
    return WechatConfig;
}(BaseConfig));
__reflect(WechatConfig.prototype, "WechatConfig");
//# sourceMappingURL=WechatConfig.js.map