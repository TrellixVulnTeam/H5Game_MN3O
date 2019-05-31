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
var EffectConfig = (function (_super) {
    __extends(EffectConfig, _super);
    function EffectConfig(ID, resourcesGroup, effectResources, position, repeat, layer, scale) {
        var _this = _super.call(this) || this;
        _this.ID = ID;
        _this.resourcesGroup = resourcesGroup;
        _this.effectResources = effectResources;
        _this.position = position;
        _this.repeat = repeat;
        _this.layer = layer;
        _this.scale = scale;
        return _this;
    }
    EffectConfig.Init = function () {
        this.LoadRes();
    };
    EffectConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "EffectConfig") {
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
        ConfFact.SetResLoad("EffectConfig");
        this.resLoaded = true;
    };
    EffectConfig.Add_Item = function (rs) {
        var arr_item_len_EffectConfig;
        var ID = rs.ReadInt();
        var resourcesGroup = rs.ReadString();
        var effectResources = rs.ReadString();
        arr_item_len_EffectConfig = rs.ReadShort();
        var position = [];
        for (var i = 0; i < arr_item_len_EffectConfig; ++i)
            position[i] =
                rs.ReadFloat();
        var repeat = rs.ReadInt();
        var layer = rs.ReadInt();
        var scale = rs.ReadFloat();
        var new_obj_EffectConfig = new EffectConfig(ID, resourcesGroup, effectResources, position, repeat, layer, scale);
        if (this.ContainsKey(ID)) {
            return;
        }
        this.dic[ID] = new_obj_EffectConfig;
        this.array.push(new_obj_EffectConfig);
    };
    EffectConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "EffectConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    EffectConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    EffectConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    EffectConfig.resLoaded = false;
    EffectConfig.dic = {};
    EffectConfig.array = [];
    return EffectConfig;
}(BaseConfig));
__reflect(EffectConfig.prototype, "EffectConfig");
//# sourceMappingURL=EffectConfig.js.map