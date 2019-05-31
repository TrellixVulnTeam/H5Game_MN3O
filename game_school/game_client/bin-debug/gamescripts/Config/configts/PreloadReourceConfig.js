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
var PreloadReourceConfig = (function (_super) {
    __extends(PreloadReourceConfig, _super);
    function PreloadReourceConfig(id, name, proxy) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.name = name;
        _this.proxy = proxy;
        return _this;
    }
    PreloadReourceConfig.Init = function () {
        this.LoadRes();
    };
    PreloadReourceConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "PreloadReourceConfig") {
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
        ConfFact.SetResLoad("PreloadReourceConfig");
        this.resLoaded = true;
    };
    PreloadReourceConfig.Add_Item = function (rs) {
        var arr_item_len_PreloadReourceConfig;
        var id = rs.ReadInt();
        arr_item_len_PreloadReourceConfig = rs.ReadShort();
        var name = [];
        for (var i = 0; i < arr_item_len_PreloadReourceConfig; ++i)
            name[i] =
                rs.ReadString();
        var proxy = rs.ReadInt();
        var new_obj_PreloadReourceConfig = new PreloadReourceConfig(id, name, proxy);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_PreloadReourceConfig;
        this.array.push(new_obj_PreloadReourceConfig);
    };
    PreloadReourceConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "PreloadReourceConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    PreloadReourceConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    PreloadReourceConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    PreloadReourceConfig.resLoaded = false;
    PreloadReourceConfig.dic = {};
    PreloadReourceConfig.array = [];
    return PreloadReourceConfig;
}(BaseConfig));
__reflect(PreloadReourceConfig.prototype, "PreloadReourceConfig");
//# sourceMappingURL=PreloadReourceConfig.js.map