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
var MagicConfig = (function (_super) {
    __extends(MagicConfig, _super);
    function MagicConfig(ID, name, describe, imageSet, Icon, type, cd, cdInit, magicAura, magicBuff, autoSkillPriority, ifCombo, comboSkillPriority, triggerTime, triggerChance, triggerSkillPriority, ifEnlarge, ifAnimation, AnimationType, animationDraw, rolePosType, rolePosition, active, effect, effectDelay, effctPosType, effectID, sound, soundDelay) {
        var _this = _super.call(this) || this;
        _this.ID = ID;
        _this.name = name;
        _this.describe = describe;
        _this.imageSet = imageSet;
        _this.Icon = Icon;
        _this.type = type;
        _this.cd = cd;
        _this.cdInit = cdInit;
        _this.magicAura = magicAura;
        _this.magicBuff = magicBuff;
        _this.autoSkillPriority = autoSkillPriority;
        _this.ifCombo = ifCombo;
        _this.comboSkillPriority = comboSkillPriority;
        _this.triggerTime = triggerTime;
        _this.triggerChance = triggerChance;
        _this.triggerSkillPriority = triggerSkillPriority;
        _this.ifEnlarge = ifEnlarge;
        _this.ifAnimation = ifAnimation;
        _this.AnimationType = AnimationType;
        _this.animationDraw = animationDraw;
        _this.rolePosType = rolePosType;
        _this.rolePosition = rolePosition;
        _this.active = active;
        _this.effect = effect;
        _this.effectDelay = effectDelay;
        _this.effctPosType = effctPosType;
        _this.effectID = effectID;
        _this.sound = sound;
        _this.soundDelay = soundDelay;
        return _this;
    }
    MagicConfig.Init = function () {
        this.LoadRes();
    };
    MagicConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "MagicConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 29) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("MagicConfig");
        this.resLoaded = true;
    };
    MagicConfig.Add_Item = function (rs) {
        var arr_item_len_MagicConfig;
        var ID = rs.ReadInt();
        var name = rs.ReadString();
        var describe = rs.ReadString();
        var imageSet = rs.ReadString();
        var Icon = rs.ReadString();
        var type = rs.ReadInt();
        var cd = rs.ReadInt();
        var cdInit = rs.ReadInt();
        var magicAura = rs.ReadInt();
        var magicBuff = rs.ReadInt();
        var autoSkillPriority = rs.ReadInt();
        var ifCombo = rs.ReadBool();
        var comboSkillPriority = rs.ReadInt();
        var triggerTime = rs.ReadInt();
        var triggerChance = rs.ReadFloat();
        var triggerSkillPriority = rs.ReadInt();
        var ifEnlarge = rs.ReadBool();
        var ifAnimation = rs.ReadBool();
        var AnimationType = rs.ReadInt();
        var animationDraw = rs.ReadInt();
        var rolePosType = rs.ReadInt();
        arr_item_len_MagicConfig = rs.ReadShort();
        var rolePosition = [];
        for (var i = 0; i < arr_item_len_MagicConfig; ++i)
            rolePosition[i] =
                rs.ReadFloat();
        var active = rs.ReadString();
        arr_item_len_MagicConfig = rs.ReadShort();
        var effect = [];
        for (var i = 0; i < arr_item_len_MagicConfig; ++i)
            effect[i] =
                rs.ReadInt();
        arr_item_len_MagicConfig = rs.ReadShort();
        var effectDelay = [];
        for (var i = 0; i < arr_item_len_MagicConfig; ++i)
            effectDelay[i] =
                rs.ReadInt();
        arr_item_len_MagicConfig = rs.ReadShort();
        var effctPosType = [];
        for (var i = 0; i < arr_item_len_MagicConfig; ++i)
            effctPosType[i] =
                rs.ReadInt();
        arr_item_len_MagicConfig = rs.ReadShort();
        var effectID = [];
        for (var i = 0; i < arr_item_len_MagicConfig; ++i)
            effectID[i] =
                rs.ReadInt();
        arr_item_len_MagicConfig = rs.ReadShort();
        var sound = [];
        for (var i = 0; i < arr_item_len_MagicConfig; ++i)
            sound[i] =
                rs.ReadString();
        arr_item_len_MagicConfig = rs.ReadShort();
        var soundDelay = [];
        for (var i = 0; i < arr_item_len_MagicConfig; ++i)
            soundDelay[i] =
                rs.ReadInt();
        var new_obj_MagicConfig = new MagicConfig(ID, name, describe, imageSet, Icon, type, cd, cdInit, magicAura, magicBuff, autoSkillPriority, ifCombo, comboSkillPriority, triggerTime, triggerChance, triggerSkillPriority, ifEnlarge, ifAnimation, AnimationType, animationDraw, rolePosType, rolePosition, active, effect, effectDelay, effctPosType, effectID, sound, soundDelay);
        if (this.ContainsKey(ID)) {
            return;
        }
        this.dic[ID] = new_obj_MagicConfig;
        this.array.push(new_obj_MagicConfig);
    };
    MagicConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "MagicConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    MagicConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    MagicConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    MagicConfig.resLoaded = false;
    MagicConfig.dic = {};
    MagicConfig.array = [];
    return MagicConfig;
}(BaseConfig));
__reflect(MagicConfig.prototype, "MagicConfig");
//# sourceMappingURL=MagicConfig.js.map