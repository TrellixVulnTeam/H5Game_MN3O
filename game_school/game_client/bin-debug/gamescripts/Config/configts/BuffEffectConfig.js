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
var BuffEffectConfig = (function (_super) {
    __extends(BuffEffectConfig, _super);
    function BuffEffectConfig(id, desc, type, para1, para2, para3, para4, para5, para6, para1_lvmod, para2_lvmod, para3_lvmod, para4_lvmod, para5_lvmod, para6_lvmod) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.desc = desc;
        _this.type = type;
        _this.para1 = para1;
        _this.para2 = para2;
        _this.para3 = para3;
        _this.para4 = para4;
        _this.para5 = para5;
        _this.para6 = para6;
        _this.para1_lvmod = para1_lvmod;
        _this.para2_lvmod = para2_lvmod;
        _this.para3_lvmod = para3_lvmod;
        _this.para4_lvmod = para4_lvmod;
        _this.para5_lvmod = para5_lvmod;
        _this.para6_lvmod = para6_lvmod;
        return _this;
    }
    BuffEffectConfig.Init = function () {
        this.LoadRes();
    };
    BuffEffectConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "BuffEffectConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 15) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("BuffEffectConfig");
        this.resLoaded = true;
    };
    BuffEffectConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var desc = rs.ReadString();
        var type = rs.ReadInt();
        var para1 = rs.ReadInt();
        var para2 = rs.ReadInt();
        var para3 = rs.ReadInt();
        var para4 = rs.ReadFloat();
        var para5 = rs.ReadFloat();
        var para6 = rs.ReadFloat();
        var para1_lvmod = rs.ReadString();
        var para2_lvmod = rs.ReadString();
        var para3_lvmod = rs.ReadString();
        var para4_lvmod = rs.ReadString();
        var para5_lvmod = rs.ReadString();
        var para6_lvmod = rs.ReadString();
        var new_obj_BuffEffectConfig = new BuffEffectConfig(id, desc, type, para1, para2, para3, para4, para5, para6, para1_lvmod, para2_lvmod, para3_lvmod, para4_lvmod, para5_lvmod, para6_lvmod);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_BuffEffectConfig;
        this.array.push(new_obj_BuffEffectConfig);
    };
    BuffEffectConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "BuffEffectConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    BuffEffectConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    BuffEffectConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    BuffEffectConfig.resLoaded = false;
    BuffEffectConfig.dic = {};
    BuffEffectConfig.array = [];
    return BuffEffectConfig;
}(BaseConfig));
__reflect(BuffEffectConfig.prototype, "BuffEffectConfig");
//# sourceMappingURL=BuffEffectConfig.js.map