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
var ActionStr = (function () {
    function ActionStr() {
    }
    ActionStr.Die = "dead";
    ActionStr.Move = "run";
    ActionStr.Stand = "idle";
    ActionStr.Hit1 = "hit01";
    ActionStr.Hit2 = "hit02";
    ActionStr.Hit3 = "hit03";
    ActionStr.Hit4 = "hit04";
    ActionStr.Win = "win";
    ActionStr.Attack = "attack";
    ActionStr.Chant = "chant";
    ActionStr.Skill = "skill";
    return ActionStr;
}());
__reflect(ActionStr.prototype, "ActionStr");
var DragonCombatantObject = (function (_super) {
    __extends(DragonCombatantObject, _super);
    function DragonCombatantObject() {
        return _super.call(this) || this;
    }
    DragonCombatantObject.prototype.init = function (res_ske_json, armatureName, actionName, oriAction, playSpeed) {
        if (playSpeed === void 0) { playSpeed = 1; }
        _super.prototype.init.call(this, res_ske_json, armatureName, actionName, oriAction, playSpeed);
    };
    DragonCombatantObject.prototype.destory = function () {
        _super.prototype.destory.call(this);
    };
    DragonCombatantObject.prototype.update = function (timer) {
        _super.prototype.update.call(this, timer);
    };
    return DragonCombatantObject;
}(DragonObjectBase));
__reflect(DragonCombatantObject.prototype, "DragonCombatantObject");
//# sourceMappingURL=DragonCombatantObject.js.map