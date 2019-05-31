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
var MagicEffectConfig = (function (_super) {
    __extends(MagicEffectConfig, _super);
    function MagicEffectConfig(ID, objectType, objectType2, objectNum, effect, effectDelay, effectPosType, effect_colour, effect_colour_time1, effect_colour_time2, delay, effectBits, hitBuff1, hitBuff2, hitBuff3, hitBuffChance1, hitBuffChance2, hitBuffChance3, dispelBit, hurtPercentage, hurtValue, additionalHurtType, hurtPercentageMods, hurtValueMods, curePercentage, cureValue, curePercentageMods, cureValueMods) {
        var _this = _super.call(this) || this;
        _this.ID = ID;
        _this.objectType = objectType;
        _this.objectType2 = objectType2;
        _this.objectNum = objectNum;
        _this.effect = effect;
        _this.effectDelay = effectDelay;
        _this.effectPosType = effectPosType;
        _this.effect_colour = effect_colour;
        _this.effect_colour_time1 = effect_colour_time1;
        _this.effect_colour_time2 = effect_colour_time2;
        _this.delay = delay;
        _this.effectBits = effectBits;
        _this.hitBuff1 = hitBuff1;
        _this.hitBuff2 = hitBuff2;
        _this.hitBuff3 = hitBuff3;
        _this.hitBuffChance1 = hitBuffChance1;
        _this.hitBuffChance2 = hitBuffChance2;
        _this.hitBuffChance3 = hitBuffChance3;
        _this.dispelBit = dispelBit;
        _this.hurtPercentage = hurtPercentage;
        _this.hurtValue = hurtValue;
        _this.additionalHurtType = additionalHurtType;
        _this.hurtPercentageMods = hurtPercentageMods;
        _this.hurtValueMods = hurtValueMods;
        _this.curePercentage = curePercentage;
        _this.cureValue = cureValue;
        _this.curePercentageMods = curePercentageMods;
        _this.cureValueMods = cureValueMods;
        return _this;
    }
    MagicEffectConfig.Init = function () {
        this.LoadRes();
    };
    MagicEffectConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "MagicEffectConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 28) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("MagicEffectConfig");
        this.resLoaded = true;
    };
    MagicEffectConfig.Add_Item = function (rs) {
        var arr_item_len_MagicEffectConfig;
        var ID = rs.ReadInt();
        var objectType = rs.ReadInt();
        var objectType2 = rs.ReadInt();
        var objectNum = rs.ReadInt();
        arr_item_len_MagicEffectConfig = rs.ReadShort();
        var effect = [];
        for (var i = 0; i < arr_item_len_MagicEffectConfig; ++i)
            effect[i] =
                rs.ReadInt();
        arr_item_len_MagicEffectConfig = rs.ReadShort();
        var effectDelay = [];
        for (var i = 0; i < arr_item_len_MagicEffectConfig; ++i)
            effectDelay[i] =
                rs.ReadInt();
        arr_item_len_MagicEffectConfig = rs.ReadShort();
        var effectPosType = [];
        for (var i = 0; i < arr_item_len_MagicEffectConfig; ++i)
            effectPosType[i] =
                rs.ReadInt();
        var effect_colour = rs.ReadString();
        var effect_colour_time1 = rs.ReadInt();
        var effect_colour_time2 = rs.ReadInt();
        var delay = rs.ReadInt();
        var effectBits = rs.ReadInt();
        var hitBuff1 = rs.ReadInt();
        var hitBuff2 = rs.ReadInt();
        var hitBuff3 = rs.ReadInt();
        var hitBuffChance1 = rs.ReadFloat();
        var hitBuffChance2 = rs.ReadFloat();
        var hitBuffChance3 = rs.ReadFloat();
        var dispelBit = rs.ReadInt();
        var hurtPercentage = rs.ReadInt();
        var hurtValue = rs.ReadInt();
        var additionalHurtType = rs.ReadInt();
        var hurtPercentageMods = rs.ReadString();
        var hurtValueMods = rs.ReadString();
        var curePercentage = rs.ReadInt();
        var cureValue = rs.ReadInt();
        var curePercentageMods = rs.ReadString();
        var cureValueMods = rs.ReadString();
        var new_obj_MagicEffectConfig = new MagicEffectConfig(ID, objectType, objectType2, objectNum, effect, effectDelay, effectPosType, effect_colour, effect_colour_time1, effect_colour_time2, delay, effectBits, hitBuff1, hitBuff2, hitBuff3, hitBuffChance1, hitBuffChance2, hitBuffChance3, dispelBit, hurtPercentage, hurtValue, additionalHurtType, hurtPercentageMods, hurtValueMods, curePercentage, cureValue, curePercentageMods, cureValueMods);
        if (this.ContainsKey(ID)) {
            return;
        }
        this.dic[ID] = new_obj_MagicEffectConfig;
        this.array.push(new_obj_MagicEffectConfig);
    };
    MagicEffectConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "MagicEffectConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    MagicEffectConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    MagicEffectConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    MagicEffectConfig.resLoaded = false;
    MagicEffectConfig.dic = {};
    MagicEffectConfig.array = [];
    return MagicEffectConfig;
}(BaseConfig));
__reflect(MagicEffectConfig.prototype, "MagicEffectConfig");
//# sourceMappingURL=MagicEffectConfig.js.map