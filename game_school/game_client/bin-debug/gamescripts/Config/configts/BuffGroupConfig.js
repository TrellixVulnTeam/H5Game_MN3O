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
var BuffGroupConfig = (function (_super) {
    __extends(BuffGroupConfig, _super);
    function BuffGroupConfig(id, oper) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.oper = oper;
        return _this;
    }
    BuffGroupConfig.Init = function () {
        this.LoadRes();
    };
    BuffGroupConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "BuffGroupConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 2) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("BuffGroupConfig");
        this.resLoaded = true;
    };
    BuffGroupConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var oper = rs.ReadInt();
        var new_obj_BuffGroupConfig = new BuffGroupConfig(id, oper);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_BuffGroupConfig;
        this.array.push(new_obj_BuffGroupConfig);
    };
    BuffGroupConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "BuffGroupConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    BuffGroupConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    BuffGroupConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    BuffGroupConfig.resLoaded = false;
    BuffGroupConfig.dic = {};
    BuffGroupConfig.array = [];
    return BuffGroupConfig;
}(BaseConfig));
__reflect(BuffGroupConfig.prototype, "BuffGroupConfig");
//# sourceMappingURL=BuffGroupConfig.js.map