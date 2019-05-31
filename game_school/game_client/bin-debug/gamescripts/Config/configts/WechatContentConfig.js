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
var WechatContentConfig = (function (_super) {
    __extends(WechatContentConfig, _super);
    function WechatContentConfig(id, type, name, choiceContent, content, replyContent) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.type = type;
        _this.name = name;
        _this.choiceContent = choiceContent;
        _this.content = content;
        _this.replyContent = replyContent;
        return _this;
    }
    WechatContentConfig.Init = function () {
        this.LoadRes();
    };
    WechatContentConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "WechatContentConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 6) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("WechatContentConfig");
        this.resLoaded = true;
    };
    WechatContentConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var type = rs.ReadInt();
        var name = rs.ReadString();
        var choiceContent = rs.ReadString();
        var content = rs.ReadString();
        var replyContent = rs.ReadString();
        var new_obj_WechatContentConfig = new WechatContentConfig(id, type, name, choiceContent, content, replyContent);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_WechatContentConfig;
        this.array.push(new_obj_WechatContentConfig);
    };
    WechatContentConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "WechatContentConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    WechatContentConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    WechatContentConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    WechatContentConfig.resLoaded = false;
    WechatContentConfig.dic = {};
    WechatContentConfig.array = [];
    return WechatContentConfig;
}(BaseConfig));
__reflect(WechatContentConfig.prototype, "WechatContentConfig");
//# sourceMappingURL=WechatContentConfig.js.map