var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**技能类型 */
var SkillType;
(function (SkillType) {
    /**主动技能 */
    SkillType[SkillType["ActiveSkills"] = 1] = "ActiveSkills";
    /**被动技能 */
    SkillType[SkillType["PassiveSkill"] = 2] = "PassiveSkill";
    /**连携技 */
    SkillType[SkillType["LinkingSkill"] = 3] = "LinkingSkill";
    /**触发技 */
    SkillType[SkillType["TriggerSkill"] = 4] = "TriggerSkill";
    SkillType[SkillType["MAX"] = 5] = "MAX";
})(SkillType || (SkillType = {}));
var Skill = (function () {
    function Skill(skillid, owner) {
        this.isCanuse = false;
        this.isFinished = false;
        this.actionEnd = false; //动作都执行完毕
        this.effectCount = 0; //特效执行完毕计数
        this.skillId = skillid;
        this.magicConfig = MagicConfig.GetConfig(this.skillId);
        this.skillType = this.magicConfig.type;
        this.entity = owner;
        this.OnFightInitCD();
    }
    /**战斗开始所有技能初始化CD */
    Skill.prototype.OnFightInitCD = function () {
        this.CD = this.magicConfig.cdInit;
    };
    /**技能触发 */
    Skill.prototype.Tigger = function (target, callback) {
        //   console.log("Tigger......................................................................................................"+this.entity.basicattr.Name);
        if (this.entity) {
            this.actionEnd = false;
            var compont = this.entity.getComponent(ComponentType.Dragon);
            var endCallBack = function () {
                this.SkillClearingRecursive(callback);
                // console.log("SkillClearingRecursive");
            }.bind(this);
            if (compont && SkillType.PassiveSkill != this.magicConfig.type) {
                compont.PlayAct(this.magicConfig.active, 1, endCallBack); //播放技能动作
                var _loop_1 = function (i) {
                    App.TimerManager.doTimer(this_1.magicConfig.effectDelay[i], 1, function () {
                        var effectCompont = this.entity.getComponent(ComponentType.AvatarEffect);
                        if (effectCompont) {
                            effectCompont.PlayEffect(this.magicConfig.effect[i], this.magicConfig.effctPosType[i], AvatarEffectType.Skill);
                        }
                    }.bind(this_1), this_1, 0, null, this_1);
                };
                var this_1 = this;
                //播放特效,现在特效是个数组 释放者特效
                for (var i = 0; i < this.magicConfig.effect.length; i++) {
                    _loop_1(i);
                }
                ;
                if (!App.FightManager.IsBackstage) {
                    var _loop_2 = function (i) {
                        App.TimerManager.doTimer(this_2.magicConfig.soundDelay[i], 1, function () {
                            App.SoundManager.playEffect(this.magicConfig.sound[i]); //播放音效
                        }.bind(this_2), this_2, 0, null, this_2);
                    };
                    var this_2 = this;
                    for (var i = 0; i < this.magicConfig.sound.length; i++) {
                        _loop_2(i);
                    }
                }
                App.ActionManager.InitInjuredList();
                /**目标特效，并结算 */
                var effectIds_1 = [];
                this.magicConfig.effectID.forEach(function (element) {
                    effectIds_1.push(element);
                });
                this.SkillClearing(effectIds_1, target, callback);
            }
            else {
                /**目标特效，并结算 */
                var effectIds_2 = [];
                this.magicConfig.effectID.forEach(function (element) {
                    effectIds_2.push(element);
                });
                this.SkillClearing(effectIds_2, target, callback);
            }
        }
    };
    /**技能效果结算 */
    Skill.prototype.SkillClearing = function (effectID, target, callback) {
        var _this = this;
        if (effectID.length > 0) {
            var currentId = effectID[0];
            var magicEff = new SkillEffect(currentId, target, this.entity);
            var index = effectID.indexOf(currentId);
            if (index != -1) {
                effectID.splice(index, 1);
            }
            magicEff.Accounting(0, function () { return _this.SkillClearing(effectID, target, callback); });
        }
        else {
            if (callback)
                this.SkillClearingRecursive(callback);
        }
    };
    /**技能效果结算和技能动作需要 */
    Skill.prototype.SkillClearingRecursive = function (callback) {
        // console.log("SkillClearingRecursive    "+this.actionEnd+"    "+this.SkillId);
        if (this.actionEnd) {
            // console.log("actionEnd");
            this.actionEnd = false;
            this.effectCount = 0;
            this.CD = this.magicConfig.cd;
            App.ActionManager.PlayInjure(function () {
                // console.log("PlayInjure");
                if (callback) {
                    callback();
                }
            }.bind(this));
        }
        else {
            // console.log("this.actionEnd=true;");
            this.actionEnd = true;
        }
    };
    Object.defineProperty(Skill.prototype, "SkillId", {
        get: function () {
            return this.skillId;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Skill.prototype, "SkillType", {
        get: function () {
            return this.skillType;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Skill.prototype, "MagicConfig", {
        get: function () {
            return this.magicConfig;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Skill.prototype, "CD", {
        get: function () { return this.skillCd; },
        set: function (val) {
            this.skillCd = val <= 0 ? 0 : val;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Skill.prototype, "IsCanUse", {
        get: function () {
            return this.isCanuse;
        },
        set: function (val) {
            this.isCanuse = val;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Skill.prototype, "InCD", {
        get: function () {
            if (this.CD > 0) {
                return true;
            }
            return false;
        },
        enumerable: true,
        configurable: true
    });
    return Skill;
}());
__reflect(Skill.prototype, "Skill");
//# sourceMappingURL=Skill.js.map