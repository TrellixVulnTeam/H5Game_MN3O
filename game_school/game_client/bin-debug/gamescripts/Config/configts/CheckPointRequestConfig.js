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
var CheckPointRequestConfig = (function (_super) {
    __extends(CheckPointRequestConfig, _super);
    function CheckPointRequestConfig(id, type, para1, para2, para3, number, describe) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.type = type;
        _this.para1 = para1;
        _this.para2 = para2;
        _this.para3 = para3;
        _this.number = number;
        _this.describe = describe;
        return _this;
    }
    CheckPointRequestConfig.Init = function () {
        this.LoadRes();
    };
    CheckPointRequestConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "CheckPointRequestConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 7) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("CheckPointRequestConfig");
        this.resLoaded = true;
    };
    CheckPointRequestConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var type = rs.ReadInt();
        var para1 = rs.ReadInt();
        var para2 = rs.ReadFloat();
        var para3 = rs.ReadFloat();
        var number = rs.ReadInt();
        var describe = rs.ReadString();
        var new_obj_CheckPointRequestConfig = new CheckPointRequestConfig(id, type, para1, para2, para3, number, describe);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_CheckPointRequestConfig;
        this.array.push(new_obj_CheckPointRequestConfig);
    };
    CheckPointRequestConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "CheckPointRequestConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    CheckPointRequestConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    CheckPointRequestConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    CheckPointRequestConfig.resLoaded = false;
    CheckPointRequestConfig.dic = {};
    CheckPointRequestConfig.array = [];
    return CheckPointRequestConfig;
}(BaseConfig));
__reflect(CheckPointRequestConfig.prototype, "CheckPointRequestConfig");
//# sourceMappingURL=CheckPointRequestConfig.js.map