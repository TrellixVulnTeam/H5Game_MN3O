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
var PublicConstConfig = (function (_super) {
    __extends(PublicConstConfig, _super);
    function PublicConstConfig(id, value) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.value = value;
        return _this;
    }
    PublicConstConfig.Init = function () {
        this.LoadRes();
    };
    PublicConstConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "PublicConstConfig") {
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
        ConfFact.SetResLoad("PublicConstConfig");
        this.resLoaded = true;
    };
    PublicConstConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var value = rs.ReadString();
        var new_obj_PublicConstConfig = new PublicConstConfig(id, value);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_PublicConstConfig;
        this.array.push(new_obj_PublicConstConfig);
    };
    PublicConstConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "PublicConstConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    PublicConstConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    PublicConstConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    PublicConstConfig.resLoaded = false;
    PublicConstConfig.dic = {};
    PublicConstConfig.array = [];
    return PublicConstConfig;
}(BaseConfig));
__reflect(PublicConstConfig.prototype, "PublicConstConfig");
//# sourceMappingURL=PublicConstConfig.js.map