var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * 技能效果结算
 * @type 掩码
 */
var MagicEffectClearingBits;
(function (MagicEffectClearingBits) {
    /**结算伤害 */
    MagicEffectClearingBits[MagicEffectClearingBits["Bits_SettlementDamage"] = 1] = "Bits_SettlementDamage";
    /**结算治疗 */
    MagicEffectClearingBits[MagicEffectClearingBits["Bits_ClearingTreatment"] = 2] = "Bits_ClearingTreatment";
})(MagicEffectClearingBits || (MagicEffectClearingBits = {}));
/**
 * 技能效果驱散方式
 * @type 掩码
 */
var MagicEffectDisperseCcontent;
(function (MagicEffectDisperseCcontent) {
    /**驱散正面 */
    MagicEffectDisperseCcontent[MagicEffectDisperseCcontent["Disperse_TheFront"] = 1] = "Disperse_TheFront";
    /**驱散负面 */
    MagicEffectDisperseCcontent[MagicEffectDisperseCcontent["Disperse_Negative"] = 2] = "Disperse_Negative";
    /**驱散中立 */
    MagicEffectDisperseCcontent[MagicEffectDisperseCcontent["Disperse_Neutral"] = 3] = "Disperse_Neutral";
})(MagicEffectDisperseCcontent || (MagicEffectDisperseCcontent = {}));
/**结算类型 */
var ClearingType;
(function (ClearingType) {
    /**物理 */
    ClearingType[ClearingType["ClearingType_Physical"] = 1] = "ClearingType_Physical";
    /**魔法 */
    ClearingType[ClearingType["ClearingType_Magic"] = 2] = "ClearingType_Magic";
})(ClearingType || (ClearingType = {}));
var SkillEffect = (function () {
    function SkillEffect(id, target, owner) {
        this.targetS = [];
        this.endCount = 0;
        this.mHurtPercentageModifiers = new LevelModifiers(); //技能伤害百分比 - 等级修正
        this.mHurtValueModifiers = new LevelModifiers(); //技能伤害固定值 - 等级修正
        this.mTreatmentPercentageModifiers = new LevelModifiers(); //技能治疗百分比 - 等级修正
        this.mTreatmentValueModifiers = new LevelModifiers(); //技能治疗固定值 - 等级修正
        this.mSkillEffectid = id;
        this.mConfig = MagicEffectConfig.GetConfig(this.mSkillEffectid);
        this.mTargetObj = target;
        this.mOwnerObj = owner;
        this.mHurtPercentageModifiers.Load(this.mConfig.hurtPercentageMods);
        this.mHurtValueModifiers.Load(this.mConfig.hurtValueMods);
        this.mTreatmentPercentageModifiers.Load(this.mConfig.curePercentageMods);
        this.mTreatmentValueModifiers.Load(this.mConfig.cureValueMods);
    }
    /**
     * 技能效果结算
     * 顺序（驱散->加Buff->伤害/治疗）
     */
    SkillEffect.prototype.Accounting = function (bufflayers, callback) {
        this.targetS = this.GetmTargetObject(this.mTargetObj, this.mOwnerObj);
        this.endCount = 0;
        if (this.targetS) {
            var _loop_1 = function (i) {
                this_1.Disperse(this_1.targetS[i], this_1.mOwnerObj, function () {
                    this.AddBuff(this.targetS[i], this.mOwnerObj, function () {
                        if (TestBits.TestMagicEffectBits(this.mConfig.effectBits, MagicEffectClearingBits.Bits_SettlementDamage)) {
                            this.Damage(this.targetS[i], this.mOwnerObj, 0, callback);
                        }
                        else if (TestBits.TestMagicEffectBits(this.mConfig.effectBits, MagicEffectClearingBits.Bits_ClearingTreatment)) {
                            this.Treatment(this.targetS[i], this.mOwnerObj, 0, callback);
                        }
                        else {
                            this.endCount++;
                            if (this.endCount == this.targetS.length) {
                                if (callback) {
                                    callback();
                                }
                            }
                        }
                    }.bind(this));
                }.bind(this_1));
            };
            var this_1 = this;
            for (var i = 0; i < this.targetS.length; i++) {
                _loop_1(i);
            }
        }
        else {
            if (callback)
                callback();
        }
    };
    /**驱散 */
    SkillEffect.prototype.Disperse = function (target, owner, callback) {
        var buffCom = target.getComponent(ComponentType.Buff);
        if (buffCom) {
            if (TestBits.TestDisperseCcontent(this.mConfig.dispelBit, MagicEffectDisperseCcontent.Disperse_TheFront)) {
                buffCom.DisperseBuff(BuffFriendlyType.BUFFTYPE_POSITIVE, callback);
            }
            else if (TestBits.TestDisperseCcontent(this.mConfig.dispelBit, MagicEffectDisperseCcontent.Disperse_Neutral)) {
                buffCom.DisperseBuff(BuffFriendlyType.BUFFTYPE_NEUTRAL, callback);
            }
            else if (TestBits.TestDisperseCcontent(this.mConfig.dispelBit, MagicEffectDisperseCcontent.Disperse_Negative)) {
                buffCom.DisperseBuff(BuffFriendlyType.BUFFTYPE_NEGATIVE, callback);
            }
            else {
                if (callback) {
                    callback();
                }
            }
        }
    };
    /**
     * 添加Buff
     * @param target 目标
     * @param owner 施法者
     */
    SkillEffect.prototype.AddBuff = function (target, owner, callback) {
        if (!target) {
            if (callback)
                callback();
            return;
        }
        var _loop_2 = function (i) {
            App.TimerManager.doTimer(this_2.mConfig.effectDelay[i], 1, function () {
                var effectCompont = target.getComponent(ComponentType.AvatarEffect);
                if (effectCompont)
                    effectCompont.PlayEffect(this.mConfig.effect[i], this.mConfig.effectPosType[i], AvatarEffectType.Skill);
            }.bind(this_2), this_2, 0, null, this_2);
        };
        var this_2 = this;
        for (var i = 0; i < this.mConfig.effect.length; i++) {
            _loop_2(i);
        }
        var buffCom = target.getComponent(ComponentType.Buff);
        if (buffCom) {
            var isnothitbuff = true;
            if (this.mConfig.hitBuff1 > 0) {
                if (this.mConfig.hitBuffChance1 * 100 >= App.RandomUtils.limitInteger(0, 100)) {
                    buffCom.AddBuff(this.mConfig.hitBuff1, owner.uid, callback);
                    isnothitbuff = false;
                }
            }
            if (this.mConfig.hitBuff2 > 0) {
                if (this.mConfig.hitBuffChance2 * 100 >= App.RandomUtils.limitInteger(0, 100)) {
                    buffCom.AddBuff(this.mConfig.hitBuff2, owner.uid, callback);
                    isnothitbuff = false;
                }
            }
            if (this.mConfig.hitBuff3 > 0) {
                if (this.mConfig.hitBuffChance3 * 100 >= App.RandomUtils.limitInteger(0, 100)) {
                    buffCom.AddBuff(this.mConfig.hitBuff3, owner.uid, callback);
                    isnothitbuff = false;
                }
            }
        }
        if (callback) {
            callback();
        }
    };
    /**
     * 伤害结算
     */
    SkillEffect.prototype.Damage = function (target, owner, bufflayers, callback) {
        if (bufflayers === void 0) { bufflayers = 0; }
        if (target.Alive) {
            var isCRI = false; //是否暴击
            var ownerStatistics = owner.RealTimeProperties;
            var targetStatistics = target.RealTimeProperties;
            //暴击率
            var CritRate = (ownerStatistics[EStatistic.STATISTIC_CRIT_AMOUNT] + 100) / (ownerStatistics[EStatistic.STATISTIC_CRIT_AMOUNT] + targetStatistics[EStatistic.STATISTIC_TOUGHNESS_AMOUNT] + 2000) * 2 * owner.basicattr.StandardCriProb + ownerStatistics[EStatistic.STATISTIC_CRIT_CHANCE] - targetStatistics[EStatistic.STATISTIC_TOUGHNESS_CHANCE];
            //暴击系数
            var CritCoefficient = 0;
            if (owner.basicattr.CheckUltimatelyCriProbIsLegal(CritRate)) {
                CritCoefficient = (ownerStatistics[EStatistic.STATISTIC_CRIT_AMOUNT] + 1000) / (ownerStatistics[EStatistic.STATISTIC_CRIT_AMOUNT] +
                    targetStatistics[EStatistic.STATISTIC_TOUGHNESS_AMOUNT] + 2000) * 2 * (owner.basicattr.StandardCriMul - 1) + 1 +
                    ownerStatistics[EStatistic.STATISTIC_CRIT_DAMAGE] - targetStatistics[EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT];
                if (CritCoefficient < 1.1) {
                    CritCoefficient = 1.1;
                }
                else if (CritCoefficient > 5) {
                    CritCoefficient = 5;
                }
                isCRI = true;
            }
            else {
                CritCoefficient = 1;
            }
            //基础伤害
            var Basedamage = (ownerStatistics[EStatistic.STATISTIC_DAMAGE] *
                ownerStatistics[EStatistic.STATISTIC_DAMAGE] /
                (ownerStatistics[EStatistic.STATISTIC_DAMAGE] +
                    (this.mConfig.additionalHurtType == ClearingType.ClearingType_Physical ?
                        targetStatistics[EStatistic.STATISTIC_PHYSICAL_DEFENCE] * 2 :
                        targetStatistics[EStatistic.STATISTIC_SPELL_DEFENCE] * 2)) *
                (bufflayers ?
                    this.HurtPercentageModifiers.Calc(owner.basicattr.Level, this.mConfig.hurtPercentage) * bufflayers / 100 :
                    this.HurtPercentageModifiers.Calc(owner.basicattr.Level, this.mConfig.hurtPercentage) / 100) +
                this.mHurtValueModifiers.Calc(owner.basicattr.Level, this.mConfig.hurtValue)) *
                CritCoefficient; //暴击系数
            //计算最终伤害值
            //目标受击表现，状态结算 
            this.ActionClearing(target, owner, Basedamage, HurtType.Hurt, isCRI, callback);
        }
        else {
            this.endCount++;
            if (this.endCount == this.targetS.length) {
                if (callback) {
                    callback();
                }
            }
        }
    };
    /**
     * 治疗结算
     */
    SkillEffect.prototype.Treatment = function (target, owner, bufflayers, callback) {
        if (bufflayers === void 0) { bufflayers = 0; }
        if (target.Alive) {
            var ownerStatistics = owner.RealTimeProperties;
            var TreatmentEff = target.basicattr.GetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT); //治疗效果
            var BasicTreatment = (ownerStatistics[EStatistic.STATISTIC_DAMAGE] * ((bufflayers ? this.mTreatmentPercentageModifiers.Calc(owner.basicattr.Level, this.mConfig.curePercentage) * bufflayers : this.mTreatmentPercentageModifiers.Calc(owner.basicattr.Level, this.mConfig.curePercentage)) / 100) *
                0.5 + this.mTreatmentValueModifiers.Calc(owner.basicattr.Level, this.mConfig.cureValue)) * (1 + TreatmentEff);
            //加血
            this.ActionClearing(target, owner, BasicTreatment, HurtType.Gain, false, callback);
        }
        else {
            this.endCount++;
            if (this.endCount == this.targetS.length) {
                if (callback) {
                    callback();
                }
            }
        }
    };
    /*
 *回合结算
 */
    SkillEffect.prototype.ActionClearing = function (target, owner, bloodLoss, type, crit, callback) {
        if (target) {
            var head_1 = target.getComponent(ComponentType.Head);
            var beforeBlood = target.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);
            var currentBlood_1 = 0;
            var total_1;
            if (type == HurtType.Gain) {
                currentBlood_1 = beforeBlood + bloodLoss;
                total_1 = App.FightManager.GetCampTotalBlood(target.camp, bloodLoss);
            }
            else {
                currentBlood_1 = (beforeBlood - bloodLoss) <= 0 ? 0 : (beforeBlood - bloodLoss);
                var realBlood = (beforeBlood - bloodLoss) <= 0 ? beforeBlood : bloodLoss;
                total_1 = App.FightManager.GetCampTotalBlood(target.camp, -realBlood);
                var proportion = target.basicattr.GetCurrentValue(EStatistic.SUNDER_CRITICAL_BLOOD_PROPORTION);
                proportion = proportion + owner.CreatureConf.break_strength - target.CreatureConf.break_resistance;
                if (currentBlood_1 > 0 && currentBlood_1 < (target.basicattr.OriHP * proportion)) {
                    App.ActionManager.AddInjureList(target);
                }
            }
            target.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE, currentBlood_1);
            App.TimerManager.doTimer(this.MConfig.delay, 1, function () {
                App.FightManager.showHpChange(target, bloodLoss, type, crit); //跳血
                head_1.changehpslider(currentBlood_1); //血条
                App.EventMgrHelper.PushEvent(EventDef.UpdateHpBar, target.camp, total_1);
                if (currentBlood_1 <= 0)
                    App.FightManager.removeplayer(target, false); //先从列表删掉，不销毁
                if (type == HurtType.Hurt) {
                    var compont = target.getComponent(ComponentType.Dragon);
                    var action = "";
                    if (currentBlood_1 <= 0) {
                        compont.PlayAct(ActionStr.Die, 1, function () {
                            target.Death();
                            this.endCount++;
                            if (this.endCount == this.targetS.length) {
                                if (callback) {
                                    callback();
                                }
                            }
                        }.bind(this)); //播放死亡动画，销毁
                    }
                    else {
                        var endCallBack = function () {
                            this.endCount++;
                            if (this.endCount == this.targetS.length) {
                                if (callback) {
                                    callback();
                                }
                            }
                        }.bind(this);
                        App.ActionManager.playerObjHurtExpression(target, this.mConfig.effect_colour, this.mConfig.effect_colour_time1, this.mConfig.effect_colour_time2);
                        compont.PlayAct(ActionStr.Hit1, 1, endCallBack);
                    }
                }
                else {
                    this.endCount++;
                    if (this.endCount == this.targetS.length) {
                        if (callback) {
                            callback();
                        }
                    }
                }
            }.bind(this), this);
        }
    };
    Object.defineProperty(SkillEffect.prototype, "ID", {
        get: function () {
            return this.mSkillEffectid;
        },
        enumerable: true,
        configurable: true
    });
    SkillEffect.prototype.GetmTargetObject = function (mTargetObj, owner) {
        var targetArray = [];
        if (this.mConfig.objectType == 1) {
            targetArray.push(mTargetObj);
        }
        else if (this.mConfig.objectType == 2) {
            targetArray.push(mTargetObj);
            for (var i = 0; i < App.FightManager.AllPlayers.length; i++) {
                if (App.FightManager.AllPlayers[i].camp == mTargetObj.camp) {
                    if (App.FightManager.AllPlayers[i].colnum == (mTargetObj.colnum + 1) && App.FightManager.AllPlayers[i].rownum == mTargetObj.rownum) {
                        targetArray.push(App.FightManager.AllPlayers[i]);
                        break;
                    }
                }
            }
        }
        else if (this.mConfig.objectType == 3) {
            for (var i = 0; i < App.FightManager.AllPlayers.length; i++) {
                if (App.FightManager.AllPlayers[i].camp == mTargetObj.camp) {
                    if (App.FightManager.AllPlayers[i].colnum == (mTargetObj.colnum + 1) && App.FightManager.AllPlayers[i].rownum == mTargetObj.rownum) {
                        targetArray.push(App.FightManager.AllPlayers[i]);
                        break;
                    }
                }
            }
        }
        else if (this.mConfig.objectType == 4) {
            var enemy = [];
            for (var i = 0; i < App.FightManager.AllPlayers.length; i++) {
                if (App.FightManager.AllPlayers[i].camp != owner.camp && App.FightManager.AllPlayers[i] != owner) {
                    enemy.push(App.FightManager.AllPlayers[i]);
                }
            }
            if (this.mConfig.objectType2 == 1) {
                targetArray = App.RandomUtils.randomArrayInterval(enemy, this.mConfig.objectNum);
            }
            else if (this.mConfig.objectType2 == 2) {
                var backPlayers = [];
                for (var i = 0; i < enemy.length; i++) {
                    if (enemy[i].colnum == 1) {
                        backPlayers.push(enemy[i]);
                    }
                }
                if (backPlayers.length == 0) {
                    for (var i = 0; i < enemy.length; i++) {
                        if (enemy[i].colnum == 0) {
                            backPlayers.push(enemy[i]);
                        }
                    }
                }
                targetArray = App.RandomUtils.randomArrayInterval(backPlayers, this.mConfig.objectNum);
                backPlayers = null;
            }
            else if (this.mConfig.objectType2 == 3) {
                var frontPlayers = [];
                for (var i = 0; i < enemy.length; i++) {
                    if (enemy[i].colnum == 0) {
                        frontPlayers.push(enemy[i]);
                    }
                }
                if (frontPlayers.length == 0) {
                    for (var i = 0; i < enemy.length; i++) {
                        if (enemy[i].colnum == 1) {
                            frontPlayers.push(enemy[i]);
                        }
                    }
                }
                targetArray = App.RandomUtils.randomArrayInterval(frontPlayers, this.mConfig.objectNum);
                frontPlayers = null;
            }
            else if (this.mConfig.objectType2 == 4) {
                enemy.sort(function (a, b) {
                    if ((a.basicattr.HP / a.basicattr.MaxHP) < (b.basicattr.HP / b.basicattr.MaxHP)) {
                        return 1;
                    }
                    else {
                        return -1;
                    }
                });
                targetArray.push(enemy[0]);
            }
            enemy = null;
        }
        else if (this.mConfig.objectType == 5) {
            var owners = [];
            for (var i = 0; i < App.FightManager.AllPlayers.length; i++) {
                if (App.FightManager.AllPlayers[i].camp == owner.camp) {
                    owners.push(App.FightManager.AllPlayers[i]);
                }
            }
            if (this.mConfig.objectType2 == 1) {
                targetArray = App.RandomUtils.randomArrayInterval(owners, this.mConfig.objectNum);
            }
            else if (this.mConfig.objectType2 == 2) {
                var backPlayers = [];
                for (var i = 0; i < owners.length; i++) {
                    if (owners[i].colnum == 1) {
                        backPlayers.push(owners[i]);
                    }
                }
                if (backPlayers.length == 0) {
                    for (var i = 0; i < owners.length; i++) {
                        if (owners[i].colnum == 0) {
                            backPlayers.push(owners[i]);
                        }
                    }
                }
                targetArray = App.RandomUtils.randomArrayInterval(backPlayers, this.mConfig.objectNum);
                backPlayers = null;
            }
            else if (this.mConfig.objectType2 == 3) {
                var frontPlayers = [];
                for (var i = 0; i < owners.length; i++) {
                    if (owners[i].colnum == 0) {
                        frontPlayers.push(owners[i]);
                    }
                }
                if (frontPlayers.length == 0) {
                    for (var i = 0; i < owners.length; i++) {
                        if (owners[i].colnum == 1) {
                            frontPlayers.push(owners[i]);
                        }
                    }
                }
                targetArray = App.RandomUtils.randomArrayInterval(frontPlayers, this.mConfig.objectNum);
                frontPlayers = null;
            }
            else if (this.mConfig.objectType2 == 4) {
                owners.sort(function (a, b) {
                    if ((a.basicattr.HP / a.basicattr.MaxHP) < (b.basicattr.HP / b.basicattr.MaxHP)) {
                        return 1;
                    }
                    else {
                        return -1;
                    }
                });
                targetArray.push(owners[0]);
            }
            owners = null;
        }
        else if (this.mConfig.objectType == 6) {
            targetArray.push(owner);
        }
        return targetArray;
    };
    Object.defineProperty(SkillEffect.prototype, "HurtPercentageModifiers", {
        /**技能伤害百分比 - 等级修正 */
        get: function () {
            return this.mHurtPercentageModifiers;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(SkillEffect.prototype, "HurtValueModifiers", {
        /**技能伤害固定值 - 等级修正 */
        get: function () {
            return this.mHurtValueModifiers;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(SkillEffect.prototype, "TreatmentPercentageModifiers", {
        /**技能治疗百分比 - 等级修正 */
        get: function () {
            return this.mTreatmentPercentageModifiers;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(SkillEffect.prototype, "TreatmentValueModifiers", {
        /**技能治疗固定值 - 等级修正 */
        get: function () {
            return this.mTreatmentValueModifiers;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(SkillEffect.prototype, "MConfig", {
        /**计算表格 */
        get: function () {
            return this.mConfig;
        },
        enumerable: true,
        configurable: true
    });
    return SkillEffect;
}());
__reflect(SkillEffect.prototype, "SkillEffect");
//# sourceMappingURL=SkillEffect.js.map