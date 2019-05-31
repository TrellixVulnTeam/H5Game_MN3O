var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var AdditionAuraEffect = (function () {
    function AdditionAuraEffect(id) {
        this.config = null;
        this.param1_modifiers = new LevelModifiers();
        this.param2_modifiers = new LevelModifiers();
        this.param3_modifiers = new LevelModifiers();
        this.param4_modifiers = new LevelModifiers();
        this.param5_modifiers = new LevelModifiers();
        this.param6_modifiers = new LevelModifiers();
        this.config = BuffEffectConfig.GetConfig(id);
        this.param1_modifiers.Load(this.config.para1_lvmod);
        this.param2_modifiers.Load(this.config.para2_lvmod);
        this.param3_modifiers.Load(this.config.para3_lvmod);
        this.param4_modifiers.Load(this.config.para4_lvmod);
        this.param5_modifiers.Load(this.config.para5_lvmod);
        this.param6_modifiers.Load(this.config.para6_lvmod);
    }
    AdditionAuraEffect.prototype.GetField = function (level, field) {
        var value;
        switch (field) {
            case "para1":
                value = parseInt((this.param1_modifiers.Calc(level, this.config.para1)).toString()).toString();
                break;
            case "para2":
                value = parseInt((this.param2_modifiers.Calc(level, this.config.para2)).toString()).toString();
                break;
            case "para3":
                value = parseInt((this.param3_modifiers.Calc(level, this.config.para3)).toString()).toString();
                break;
            case "para4":
                value = this.param4_modifiers.Calc(level, this.config.para4).toString();
                break;
            case "para5":
                value = this.param5_modifiers.Calc(level, this.config.para5).toString();
                break;
            case "para6":
                value = this.param6_modifiers.Calc(level, this.config.para6).toString();
                break;
        }
        return value;
    };
    return AdditionAuraEffect;
}());
__reflect(AdditionAuraEffect.prototype, "AdditionAuraEffect");
//# sourceMappingURL=AdditionAuraEffect.js.map