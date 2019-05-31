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
var StrConfig = (function (_super) {
    __extends(StrConfig, _super);
    function StrConfig(id, str) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.str = str;
        return _this;
    }
    StrConfig.Init = function () {
        this.LoadRes();
    };
    StrConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "StrConfig") {
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
        ConfFact.SetResLoad("StrConfig");
        this.resLoaded = true;
    };
    StrConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var str = rs.ReadString();
        var new_obj_StrConfig = new StrConfig(id, str);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_StrConfig;
        this.array.push(new_obj_StrConfig);
    };
    StrConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "StrConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    StrConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    StrConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    StrConfig.resLoaded = false;
    StrConfig.dic = {};
    StrConfig.array = [];
    return StrConfig;
}(BaseConfig));
__reflect(StrConfig.prototype, "StrConfig");
//# sourceMappingURL=StrConfig.js.map