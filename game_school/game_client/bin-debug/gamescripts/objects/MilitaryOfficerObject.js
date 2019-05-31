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
/**
 * Player
 * created by sjz on 2018-5-9.
 */
var MilitaryOfficerObject = (function (_super) {
    __extends(MilitaryOfficerObject, _super);
    function MilitaryOfficerObject() {
        return _super.call(this) || this;
    }
    MilitaryOfficerObject.prototype.init = function (id, posinfo, camp, gameView, data) {
        var _this = this;
        _super.prototype.init.call(this, id, posinfo, camp, gameView, data);
        // this.addComponent(ComponentType.Avatar);
        this.addComponent(ComponentType.Dragon); //骨骼组件必须放在最前
        this.addComponent(ComponentType.AvatarEffect);
        this.addComponent(ComponentType.Head);
        this.addComponent(ComponentType.Move);
        this.addComponent(ComponentType.Skill);
        this.addComponent(ComponentType.Buff);
        this.ClientBit.SetBitSet(ClientBits.CLIENT_BIT_DEAD, false);
        this.RegisEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ActionManager.CurrentTarget = _this;
        });
    };
    MilitaryOfficerObject.prototype.Death = function () {
        _super.prototype.Death.call(this);
        this.ClientBit.SetBitSet(ClientBits.CLIENT_BIT_DEAD, true);
        this.DelClientBitState(ClientBits.CLIENT_BIT_SKILL_ACTIVATE);
    };
    /**
     * 掉血
     * @param 伤害值（掉血值）
     * @param 是否暴击
     * @param 回调函数
     */
    MilitaryOfficerObject.prototype.DamageSettlemen = function (hurt, isCri, callback) {
        if (callback) {
            callback();
        }
    };
    return MilitaryOfficerObject;
}(GameObject));
__reflect(MilitaryOfficerObject.prototype, "MilitaryOfficerObject");
//# sourceMappingURL=MilitaryOfficerObject.js.map