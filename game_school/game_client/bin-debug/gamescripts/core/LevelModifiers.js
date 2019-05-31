var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var LevelModifier = (function () {
    function LevelModifier() {
        this.lv_start = 0;
        this.lv_ended = 0;
        this.factor = 0;
    }
    return LevelModifier;
}());
__reflect(LevelModifier.prototype, "LevelModifier");
/**
 * 等级修正
 */
var LevelModifiers = (function () {
    function LevelModifiers() {
        this.modifiers = [];
        this.count = 0;
    }
    LevelModifiers.prototype.Load = function (json) {
        var ar = JSON.parse(json);
        if (ar == null)
            return;
        this.count = ar.length;
        this.modifiers = [ar.length];
        for (var i = 0; i < ar.length; ++i) {
            var aa = ar[i];
            this.modifiers[i] = new LevelModifier();
            this.modifiers[i].lv_start = aa[0];
            this.modifiers[i].lv_ended = aa[1];
            this.modifiers[i].factor = aa[2];
        }
    };
    LevelModifiers.prototype.GetIndex = function (level) {
        for (var i = 0; i < this.count; ++i) {
            if (this.modifiers[i].lv_start <= level && this.modifiers[i].lv_ended >= level)
                return i;
        }
        return -1;
    };
    LevelModifiers.prototype.Calc = function (level, oldvalue) {
        var index = this.GetIndex(level);
        if (index < 0)
            return oldvalue;
        var result = 0.0;
        for (var i = 0; i < index; ++i) {
            result += (this.modifiers[i].lv_ended - this.modifiers[i].lv_start + 1) * this.modifiers[i].factor;
        }
        result += (level - this.modifiers[index].lv_start + 1) * this.modifiers[index].factor;
        return oldvalue + result;
    };
    return LevelModifiers;
}());
__reflect(LevelModifiers.prototype, "LevelModifiers");
//# sourceMappingURL=LevelModifiers.js.map