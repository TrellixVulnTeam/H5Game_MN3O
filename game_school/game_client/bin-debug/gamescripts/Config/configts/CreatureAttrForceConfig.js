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
var CreatureAttrForceConfig = (function (_super) {
    __extends(CreatureAttrForceConfig, _super);
    function CreatureAttrForceConfig(id, life, damage, physical_defence, spell_defence, crit_amount, toughness_amout, shot_speed, linking_skills_probability, damage_reduction, deeper_damage, crit_chance, toughness_chance, crit_damage, crit_reduced_amount, treatment_effect, break_strength, break_resistance) {
        var _this = _super.call(this) || this;
        _this.id = id;
        _this.life = life;
        _this.damage = damage;
        _this.physical_defence = physical_defence;
        _this.spell_defence = spell_defence;
        _this.crit_amount = crit_amount;
        _this.toughness_amout = toughness_amout;
        _this.shot_speed = shot_speed;
        _this.linking_skills_probability = linking_skills_probability;
        _this.damage_reduction = damage_reduction;
        _this.deeper_damage = deeper_damage;
        _this.crit_chance = crit_chance;
        _this.toughness_chance = toughness_chance;
        _this.crit_damage = crit_damage;
        _this.crit_reduced_amount = crit_reduced_amount;
        _this.treatment_effect = treatment_effect;
        _this.break_strength = break_strength;
        _this.break_resistance = break_resistance;
        return _this;
    }
    CreatureAttrForceConfig.Init = function () {
        this.LoadRes();
    };
    CreatureAttrForceConfig.OnLoadFile = function (data) {
        var byteData = new egret.ByteArray(data);
        var rs = new ReadStream(byteData);
        /*int file_len = */ rs.ReadInt();
        var flag = rs.ReadString();
        if (flag != "CreatureAttrForceConfig") {
            return;
        }
        var col_cnt = rs.ReadShort();
        if (col_cnt != 18) {
            return;
        }
        var row_cnt = rs.ReadInt();
        for (var i = 0; i < row_cnt; i++) {
            this.Add_Item(rs);
        }
        ConfFact.SetResLoad("CreatureAttrForceConfig");
        this.resLoaded = true;
    };
    CreatureAttrForceConfig.Add_Item = function (rs) {
        var id = rs.ReadInt();
        var life = rs.ReadFloat();
        var damage = rs.ReadFloat();
        var physical_defence = rs.ReadFloat();
        var spell_defence = rs.ReadFloat();
        var crit_amount = rs.ReadFloat();
        var toughness_amout = rs.ReadFloat();
        var shot_speed = rs.ReadFloat();
        var linking_skills_probability = rs.ReadFloat();
        var damage_reduction = rs.ReadFloat();
        var deeper_damage = rs.ReadFloat();
        var crit_chance = rs.ReadFloat();
        var toughness_chance = rs.ReadFloat();
        var crit_damage = rs.ReadFloat();
        var crit_reduced_amount = rs.ReadFloat();
        var treatment_effect = rs.ReadFloat();
        var break_strength = rs.ReadFloat();
        var break_resistance = rs.ReadFloat();
        var new_obj_CreatureAttrForceConfig = new CreatureAttrForceConfig(id, life, damage, physical_defence, spell_defence, crit_amount, toughness_amout, shot_speed, linking_skills_probability, damage_reduction, deeper_damage, crit_chance, toughness_chance, crit_damage, crit_reduced_amount, treatment_effect, break_strength, break_resistance);
        if (this.ContainsKey(id)) {
            return;
        }
        this.dic[id] = new_obj_CreatureAttrForceConfig;
        this.array.push(new_obj_CreatureAttrForceConfig);
    };
    CreatureAttrForceConfig.LoadRes = function () {
        if (this.resLoaded)
            return;
        if (this.isUseLocalTable) {
            var urlName = this.bytespath += "CreatureAttrForceConfig.bytes";
            RES.getResByUrl(urlName, this.OnLoadFile, this, RES.ResourceItem.TYPE_BIN);
        }
    };
    CreatureAttrForceConfig.GetConfig = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return this.dic[key];
            }
        }
        return null;
    };
    CreatureAttrForceConfig.ContainsKey = function (id) {
        for (var key in this.dic) {
            if (key == id) {
                return true;
            }
        }
        return false;
    };
    CreatureAttrForceConfig.resLoaded = false;
    CreatureAttrForceConfig.dic = {};
    CreatureAttrForceConfig.array = [];
    return CreatureAttrForceConfig;
}(BaseConfig));
__reflect(CreatureAttrForceConfig.prototype, "CreatureAttrForceConfig");
//# sourceMappingURL=CreatureAttrForceConfig.js.map