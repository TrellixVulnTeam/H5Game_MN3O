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
var ItemCommonConfig = (function (_super) {
    __extends(ItemCommonConfig, _super);
    function ItemCommonConfig(id, name, icon, type, subType, levelLimit, color, itemRule, salePrice, overlapNum, description, useScript, isBatchUse, isContiUse, isquickUse, open_ui, acquisition) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.name = name;
        _this.icon = icon;
        _this.type = type;
        _this.subType = subType;
        _this.levelLimit = levelLimit;
        _this.color = color;
        _this.itemRule = itemRule;
        _this.salePrice = salePrice;
        _this.overlapNum = overlapNum;
        _this.description = description;
        _this.useScript = useScript;
        _this.isBatchUse = isBatchUse;
        _this.isContiUse = isContiUse;
        _this.isquickUse = isquickUse;
        _this.open_ui = open_ui;
        _this.acquisition = acquisition;
        return _this;
    }
    ItemCommonConfig.Init = function () {
        this.LoadRes();
    };
    ItemCommonConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "ItemCommonConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 17) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("ItemCommonConfig");
        this.resLoaded = true;
    };
    ItemCommonConfig.Add_Item = function (rs) {
        var arr_item_len_ItemCommonConfig;
        var id = rs.ReadInt();
        var name = rs.ReadString();
        var icon = rs.ReadString();
        var type = rs.ReadInt();
        var subType = rs.ReadInt();
        var levelLimit = rs.ReadInt();
        var color = rs.ReadInt();
        var itemRule = rs.ReadInt();
        var salePrice = rs.ReadInt();
        var overlapNum = rs.ReadInt();
        var description = rs.ReadString();
        arr_item_len_ItemCommonConfig = rs.ReadShort();
        var useScript = [];
        for (var i = 0; i < arr_item_len_ItemCommonConfig; ++i)
            useScript[i] =
                rs.ReadString();
        var isBatchUse = rs.ReadBool();
        var isContiUse = rs.ReadBool();
        var isquickUse = rs.ReadBool();
        arr_item_len_ItemCommonConfig = rs.ReadShort();
        var open_ui = [];
        for (var i = 0; i < arr_item_len_ItemCommonConfig; ++i)
            open_ui[i] =
                rs.ReadInt();
        var acquisition = rs.ReadString();
        var new_obj_ItemCommonConfig = new ItemCommonConfig(id, name, icon, type, subType, levelLimit, color, itemRule, salePrice, overlapNum, description, useScript, isBatchUse, isContiUse, isquickUse, open_ui, acquisition);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_ItemCommonConfig;
        this.array.push(new_obj_ItemCommonConfig);
    };
    ItemCommonConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "ItemCommonConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    ItemCommonConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    ItemCommonConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    ItemCommonConfig.resLoaded = false;
    ItemCommonConfig.dic = {};
    ItemCommonConfig.array = [];
    return ItemCommonConfig;
}(BaseConfig));
__reflect(ItemCommonConfig.prototype, "ItemCommonConfig");
//# sourceMappingURL=ItemCommonConfig.js.map