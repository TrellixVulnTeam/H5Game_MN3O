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
var GirlConfig = (function (_super) {
    __extends(GirlConfig, _super);
    function GirlConfig(id, name, associationName, icon, plot, live2D, bloodType, constellation) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.name = name;
        _this.associationName = associationName;
        _this.icon = icon;
        _this.plot = plot;
        _this.live2D = live2D;
        _this.bloodType = bloodType;
        _this.constellation = constellation;
        return _this;
    }
    GirlConfig.Init = function () {
        this.LoadRes();
    };
    GirlConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "GirlConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 8) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("GirlConfig");
        this.resLoaded = true;
    };
    GirlConfig.Add_Item = function (rs) {
        var arr_item_len_GirlConfig;
        var id = rs.ReadInt();
        var name = rs.ReadString();
        var associationName = rs.ReadString();
        var icon = rs.ReadString();
        arr_item_len_GirlConfig = rs.ReadShort();
        var plot = [];
        for (var i = 0; i < arr_item_len_GirlConfig; ++i)
            plot[i] =
                rs.ReadInt();
        var live2D = rs.ReadInt();
        var bloodType = rs.ReadString();
        var constellation = rs.ReadString();
        var new_obj_GirlConfig = new GirlConfig(id, name, associationName, icon, plot, live2D, bloodType, constellation);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_GirlConfig;
        this.array.push(new_obj_GirlConfig);
    };
    GirlConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "GirlConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    GirlConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    GirlConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    GirlConfig.resLoaded = false;
    GirlConfig.dic = {};
    GirlConfig.array = [];
    return GirlConfig;
}(BaseConfig));
__reflect(GirlConfig.prototype, "GirlConfig");
//# sourceMappingURL=GirlConfig.js.map