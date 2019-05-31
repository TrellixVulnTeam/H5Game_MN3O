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
var AttributeFormatConfig = (function (_super) {
    __extends(AttributeFormatConfig, _super);
    function AttributeFormatConfig(id, attr, format, canBeNegative, tips, weight, num_color1, num_color2) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.attr = attr;
        _this.format = format;
        _this.canBeNegative = canBeNegative;
        _this.tips = tips;
        _this.weight = weight;
        _this.num_color1 = num_color1;
        _this.num_color2 = num_color2;
        return _this;
    }
    AttributeFormatConfig.Init = function () {
        this.LoadRes();
    };
    AttributeFormatConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "AttributeFormatConfig") {
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
        ConfFact.SetResLoad("AttributeFormatConfig");
        this.resLoaded = true;
    };
    AttributeFormatConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var attr = rs.ReadString();
        var format = rs.ReadInt();
        var canBeNegative = rs.ReadInt();
        var tips = rs.ReadString();
        var weight = rs.ReadFloat();
        var num_color1 = rs.ReadString();
        var num_color2 = rs.ReadString();
        var new_obj_AttributeFormatConfig = new AttributeFormatConfig(id, attr, format, canBeNegative, tips, weight, num_color1, num_color2);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_AttributeFormatConfig;
        this.array.push(new_obj_AttributeFormatConfig);
    };
    AttributeFormatConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "AttributeFormatConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    AttributeFormatConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    AttributeFormatConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    AttributeFormatConfig.resLoaded = false;
    AttributeFormatConfig.dic = {};
    AttributeFormatConfig.array = [];
    return AttributeFormatConfig;
}(BaseConfig));
__reflect(AttributeFormatConfig.prototype, "AttributeFormatConfig");
//# sourceMappingURL=AttributeFormatConfig.js.map