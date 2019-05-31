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
var CreatureAbilityConfig = (function (_super) {
    __extends(CreatureAbilityConfig, _super);
    function CreatureAbilityConfig(id, magic1, magic2, magic3, magic4) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.magic1 = magic1;
        _this.magic2 = magic2;
        _this.magic3 = magic3;
        _this.magic4 = magic4;
        return _this;
    }
    CreatureAbilityConfig.Init = function () {
        this.LoadRes();
    };
    CreatureAbilityConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "CreatureAbilityConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 5) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("CreatureAbilityConfig");
        this.resLoaded = true;
    };
    CreatureAbilityConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var magic1 = rs.ReadInt();
        var magic2 = rs.ReadInt();
        var magic3 = rs.ReadInt();
        var magic4 = rs.ReadInt();
        var new_obj_CreatureAbilityConfig = new CreatureAbilityConfig(id, magic1, magic2, magic3, magic4);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_CreatureAbilityConfig;
        this.array.push(new_obj_CreatureAbilityConfig);
    };
    CreatureAbilityConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "CreatureAbilityConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    CreatureAbilityConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    CreatureAbilityConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    CreatureAbilityConfig.resLoaded = false;
    CreatureAbilityConfig.dic = {};
    CreatureAbilityConfig.array = [];
    return CreatureAbilityConfig;
}(BaseConfig));
__reflect(CreatureAbilityConfig.prototype, "CreatureAbilityConfig");
//# sourceMappingURL=CreatureAbilityConfig.js.map