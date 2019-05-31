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
var FilterNameConfig = (function (_super) {
    __extends(FilterNameConfig, _super);
    function FilterNameConfig(id, str) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.str = str;
        return _this;
    }
    FilterNameConfig.Init = function () {
        this.LoadRes();
    };
    FilterNameConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "FilterNameConfig") {
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
        ConfFact.SetResLoad("FilterNameConfig");
        this.resLoaded = true;
    };
    FilterNameConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var str = rs.ReadString();
        var new_obj_FilterNameConfig = new FilterNameConfig(id, str);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_FilterNameConfig;
        this.array.push(new_obj_FilterNameConfig);
    };
    FilterNameConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "FilterNameConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    FilterNameConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    FilterNameConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    FilterNameConfig.resLoaded = false;
    FilterNameConfig.dic = {};
    FilterNameConfig.array = [];
    return FilterNameConfig;
}(BaseConfig));
__reflect(FilterNameConfig.prototype, "FilterNameConfig");
//# sourceMappingURL=FilterNameConfig.js.map