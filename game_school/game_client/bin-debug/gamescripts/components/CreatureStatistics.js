var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var EStatistic;
(function (EStatistic) {
    /**活力 */
    EStatistic[EStatistic["STATISTIC_VITALITY"] = 0] = "STATISTIC_VITALITY";
    /**智力 */
    EStatistic[EStatistic["STATISTIC_INTELLECT"] = 1] = "STATISTIC_INTELLECT";
    /**力量 */
    EStatistic[EStatistic["STATISTIC_STRENGTH"] = 2] = "STATISTIC_STRENGTH";
    /**敏捷 */
    EStatistic[EStatistic["STATISTIC_AGILITY"] = 3] = "STATISTIC_AGILITY";
    /**一级属性占位4 */
    EStatistic[EStatistic["STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER4"] = 4] = "STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER4";
    /**一级属性占位5 */
    EStatistic[EStatistic["STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER5"] = 5] = "STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER5";
    /**一级属性占位6 */
    EStatistic[EStatistic["STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER6"] = 6] = "STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER6";
    /**一级属性占位7 */
    EStatistic[EStatistic["STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER7"] = 7] = "STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER7";
    /**一级属性占位8 */
    EStatistic[EStatistic["STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER8"] = 8] = "STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER8";
    /**一级属性占位9 */
    EStatistic[EStatistic["STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER9"] = 9] = "STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER9";
    /**生命值 */
    EStatistic[EStatistic["STATISTIC_LIFE"] = 10] = "STATISTIC_LIFE";
    /**预留魔法值 */
    EStatistic[EStatistic["STATISTIC_MANA"] = 11] = "STATISTIC_MANA";
    /**攻击力 */
    EStatistic[EStatistic["STATISTIC_DAMAGE"] = 11] = "STATISTIC_DAMAGE";
    /**物理防御 */
    EStatistic[EStatistic["STATISTIC_PHYSICAL_DEFENCE"] = 12] = "STATISTIC_PHYSICAL_DEFENCE";
    /**魔法防御 */
    EStatistic[EStatistic["STATISTIC_SPELL_DEFENCE"] = 13] = "STATISTIC_SPELL_DEFENCE";
    /**伤害减免 */
    EStatistic[EStatistic["STATISTIC_DAMAGE_REDUCTION"] = 14] = "STATISTIC_DAMAGE_REDUCTION";
    /**伤害加深 */
    EStatistic[EStatistic["STATISTIC_DEEPER_DAMAGE"] = 15] = "STATISTIC_DEEPER_DAMAGE";
    /**伤害公式预留6 */
    EStatistic[EStatistic["STATISTIC_DAMAGE_FORMULA_6"] = 16] = "STATISTIC_DAMAGE_FORMULA_6";
    /**伤害公式预留7 */
    EStatistic[EStatistic["STATISTIC_DAMAGE_FORMULA_7"] = 17] = "STATISTIC_DAMAGE_FORMULA_7";
    /**伤害公式预留8 */
    EStatistic[EStatistic["STATISTIC_DAMAGE_FORMULA_8"] = 18] = "STATISTIC_DAMAGE_FORMULA_8";
    /**伤害公式预留9 */
    EStatistic[EStatistic["STATISTIC_DAMAGE_FORMULA_9"] = 19] = "STATISTIC_DAMAGE_FORMULA_9";
    /**出手速度 */
    EStatistic[EStatistic["STATISTIC_SHOT_SPEED"] = 20] = "STATISTIC_SHOT_SPEED";
    /**暴击值 */
    EStatistic[EStatistic["STATISTIC_CRIT_AMOUNT"] = 21] = "STATISTIC_CRIT_AMOUNT";
    /**韧性值 */
    EStatistic[EStatistic["STATISTIC_TOUGHNESS_AMOUNT"] = 22] = "STATISTIC_TOUGHNESS_AMOUNT";
    /**暴击率 */
    EStatistic[EStatistic["STATISTIC_CRIT_CHANCE"] = 23] = "STATISTIC_CRIT_CHANCE";
    /**韧性率 */
    EStatistic[EStatistic["STATISTIC_TOUGHNESS_CHANCE"] = 24] = "STATISTIC_TOUGHNESS_CHANCE";
    /**暴击伤害 */
    EStatistic[EStatistic["STATISTIC_CRIT_DAMAGE"] = 25] = "STATISTIC_CRIT_DAMAGE";
    /**暴击伤害减免 */
    EStatistic[EStatistic["STATISTIC_CRIT_REDUCED_AMOUNT"] = 26] = "STATISTIC_CRIT_REDUCED_AMOUNT";
    /**治疗效果 */
    EStatistic[EStatistic["STATISTIC_TREATMENT_EFFECT"] = 27] = "STATISTIC_TREATMENT_EFFECT";
    /**连携技概率 */
    EStatistic[EStatistic["STATISTIC_LINKING_SKILLS_PROBABILITY"] = 28] = "STATISTIC_LINKING_SKILLS_PROBABILITY";
    /**破甲临界血量比例 */
    EStatistic[EStatistic["SUNDER_CRITICAL_BLOOD_PROPORTION"] = 29] = "SUNDER_CRITICAL_BLOOD_PROPORTION";
    /**战斗公式预留30 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_30"] = 30] = "STATISTIC_FIGHT_FORMULA_30";
    /**战斗公式预留31 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_31"] = 31] = "STATISTIC_FIGHT_FORMULA_31";
    /**战斗公式预留32 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_32"] = 32] = "STATISTIC_FIGHT_FORMULA_32";
    /**战斗公式预留33 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_33"] = 33] = "STATISTIC_FIGHT_FORMULA_33";
    /**战斗公式预留34 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_34"] = 34] = "STATISTIC_FIGHT_FORMULA_34";
    /**战斗公式预留35 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_35"] = 35] = "STATISTIC_FIGHT_FORMULA_35";
    /**战斗公式预留36 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_36"] = 36] = "STATISTIC_FIGHT_FORMULA_36";
    /**战斗公式预留37 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_37"] = 37] = "STATISTIC_FIGHT_FORMULA_37";
    /**战斗公式预留38 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_38"] = 38] = "STATISTIC_FIGHT_FORMULA_38";
    /**战斗公式预留39 */
    EStatistic[EStatistic["STATISTIC_FIGHT_FORMULA_39"] = 39] = "STATISTIC_FIGHT_FORMULA_39";
    EStatistic[EStatistic["STATISTIC_MAX"] = 40] = "STATISTIC_MAX";
})(EStatistic || (EStatistic = {}));
var CreatureStatistics = (function () {
    function CreatureStatistics() {
        this.CONVERT_SILVER_NUMBER = 100000; //银币转换
        this.MONEY_UNIT_NUMBER = 10000; //货币单位数量
        this.MONEY_INFO_ID = 2314; //万
        this.MAX_PLAYER_LEVEL = 99; //人物最大等级
        this.CONVERT_EXP_NUMBER = 100000; //转换经验值
        this.EXP_UNIT_NUMBER = 10000;
        this.mIsAutoFighting = false; //是否为自动战斗
        this.mCurrentStaticValues = [EStatistic.STATISTIC_MAX];
        this.mStandardCriProb = 0.2; //标准暴击率
        this.mStandardCriMul = 2; //标准暴击倍数
        this.mLevel = 0; //当前等级
        this.mGoldNum = 0; //金币数量
        this.mDiamondNum = 0; //钻石数量
        this.mPhysicalStrength = 0; //体力数量
        this.name = "";
        for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
            this.SetCurrentValue(i, 0);
        }
        this.mStandardCriProb = parseFloat(ClientConstConfig.GetConfig(1).value);
        this.mStandardCriMul = parseFloat(ClientConstConfig.GetConfig(2).value);
    }
    Object.defineProperty(CreatureStatistics.prototype, "Name", {
        get: function () {
            return this.name;
        },
        set: function (value) {
            this.name = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "Title", {
        get: function () {
            return this.titile;
        },
        set: function (value) {
            this.titile = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "IsAutoFighting", {
        /**是否自动战斗 */
        get: function () {
            return this.mIsAutoFighting;
        },
        set: function (value) {
            this.mIsAutoFighting = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "StandardCriProb", {
        /**标准暴击率 */
        get: function () {
            return this.mStandardCriProb;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "StandardCriMul", {
        /**标准暴击倍数 */
        get: function () {
            return this.mStandardCriMul;
        },
        enumerable: true,
        configurable: true
    });
    /**检测最终暴击率合法性 */
    CreatureStatistics.prototype.CheckUltimatelyCriProbIsLegal = function (value) {
        if (value <= 0.05) {
            value = 0.05;
        }
        if (value >= 0.6) {
            value = 0.6;
        }
        if (App.RandomUtils.limitInteger(0, 100) <= value * 100) {
            return true;
        }
        return false;
    };
    /**检测最终暴击系数合法性 */
    CreatureStatistics.prototype.CheckUltimatelyCriMulIsLegal = function (value) {
        if (1.1 <= value && value >= 5) {
            return true;
        }
        else {
            return false;
        }
    };
    CreatureStatistics.prototype.SetCurrentValue = function (index, value) {
        if (typeof index == "number") {
            this.mCurrentStaticValues[index] = value;
        }
        else {
            this.mCurrentStaticValues[index] = value;
        }
    };
    CreatureStatistics.prototype.GetCurrentValue = function (index) {
        if (typeof index == "number") {
            return this.mCurrentStaticValues[index];
        }
        else {
            return this.mCurrentStaticValues[index];
        }
    };
    Object.defineProperty(CreatureStatistics.prototype, "OriHP", {
        get: function () {
            return this.GetCurrentValue(EStatistic.STATISTIC_VITALITY);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "OriHp", {
        set: function (value) {
            this.SetCurrentValue(EStatistic.STATISTIC_VITALITY, value);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "HP", {
        get: function () {
            return Math.ceil(this.OriHP);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "MaxHP", {
        get: function () {
            if (this.OriMaxHP < 1) {
                return 1;
            }
            else {
                return Math.ceil(this.OriMaxHP);
            }
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "OriMaxHP", {
        get: function () {
            return Math.max(this.mCurrentStaticValues[EStatistic.STATISTIC_VITALITY], 1);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "OriMaxMP", {
        get: function () {
            return Math.max(this.mCurrentStaticValues[EStatistic.STATISTIC_INTELLECT], 1);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "MaxMP", {
        get: function () {
            return Math.ceil(this.OriMaxMP);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "OriMP", {
        get: function () {
            return this.GetCurrentValue(EStatistic.STATISTIC_INTELLECT);
        },
        set: function (value) {
            this.SetCurrentValue(EStatistic.STATISTIC_INTELLECT, value);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "MP", {
        get: function () {
            return Math.ceil(this.OriMP);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "Level", {
        /**等级 */
        get: function () {
            return this.mLevel;
        },
        set: function (value) {
            this.mLevel = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "GoldNum", {
        /**金币数量 */
        get: function () {
            return this.mGoldNum;
        },
        set: function (value) {
            this.mGoldNum = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "DiamondNum", {
        /**钻石数量 */
        get: function () {
            return this.mDiamondNum;
        },
        set: function (value) {
            this.mDiamondNum = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(CreatureStatistics.prototype, "PhysicalStrength", {
        /**体力 */
        get: function () {
            return this.mPhysicalStrength;
        },
        set: function (value) {
            this.mPhysicalStrength = value;
        },
        enumerable: true,
        configurable: true
    });
    return CreatureStatistics;
}());
__reflect(CreatureStatistics.prototype, "CreatureStatistics");
//# sourceMappingURL=CreatureStatistics.js.map