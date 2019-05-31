var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * 效果类型
 */
var BuffEffecttype;
(function (BuffEffecttype) {
    /**
     * 属性修改
     */
    BuffEffecttype[BuffEffecttype["BuffEffecttype_ChangeAttr"] = 1] = "BuffEffecttype_ChangeAttr";
    /**
     * 持续伤害
     */
    BuffEffecttype[BuffEffecttype["BuffEffecttype_Dot"] = 2] = "BuffEffecttype_Dot";
    /**
     * 持续治疗
     */
    BuffEffecttype[BuffEffecttype["BuffEffecttype_AC"] = 3] = "BuffEffecttype_AC";
})(BuffEffecttype || (BuffEffecttype = {}));
/**
 * Buff属性修改方式
 */
var BuffEffectChangeAttrType;
(function (BuffEffectChangeAttrType) {
    /**
     * 定值
     */
    BuffEffectChangeAttrType[BuffEffectChangeAttrType["BuffEffectChangeAttrType_TheSpec"] = 0] = "BuffEffectChangeAttrType_TheSpec";
    /**
     * 百分比
     */
    BuffEffectChangeAttrType[BuffEffectChangeAttrType["BuffEffectChangeAttrType_Percentage"] = 1] = "BuffEffectChangeAttrType_Percentage";
    /**
     * 定值加索引属性
     */
    BuffEffectChangeAttrType[BuffEffectChangeAttrType["BuffEffectChangeAttrType_TheSpecAndPercentage"] = 2] = "BuffEffectChangeAttrType_TheSpecAndPercentage";
})(BuffEffectChangeAttrType || (BuffEffectChangeAttrType = {}));
/**
 * created by sjz on 2018-5-11.
 * @class BuffEffect
 */
var BuffEffect = (function () {
    function BuffEffect(id, parent, entity, caster) {
        this.mBuffStatistics = [];
        for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
            this.mBuffStatistics[i] = 0;
        }
        this.mId = id;
        this.mEntity = entity;
        this.mCaster = caster;
        this.mParent = parent;
        this.mConfig = BuffEffectConfig.GetConfig(id);
        this.mAdditionAuraEffect = new AdditionAuraEffect(id);
        this.mType = this.mConfig.type;
        this.Tigger();
    }
    Object.defineProperty(BuffEffect.prototype, "Type", {
        get: function () {
            return this.mType;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BuffEffect.prototype, "BuffStatistics", {
        get: function () {
            return this.mBuffStatistics;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BuffEffect.prototype, "Config", {
        get: function () {
            return this.mConfig;
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 更新Buff效果
     * 只更新buff效果附带的技能结算效果，属性修改的只在初次修改，之后不再修改
     */
    BuffEffect.prototype.Update = function () {
        if (this.mSkillMaicEffect != null) {
            this.mSkillMaicEffect.Accounting();
        }
    };
    /**
     * 效果移除逻辑
     */
    BuffEffect.prototype.Destory = function () {
        this.mId = 0;
        this.mConfig = null;
        this.mEntity = null;
        this.mBuffStatistics = null;
        this.mSkillMaicEffect = null;
        this.mAdditionAuraEffect = null;
    };
    /**
     * 效果触发
     */
    BuffEffect.prototype.Tigger = function () {
        if (!this.mEntity)
            return;
        if (this.mConfig.type == BuffEffecttype.BuffEffecttype_ChangeAttr) {
            var changenum = Number(this.mAdditionAuraEffect.GetField(this.mEntity.basicattr.Level, "para4"));
            if (this.mConfig.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_TheSpec) {
                this.mBuffStatistics[this.mConfig.para1] = changenum;
            }
            else if (this.mConfig.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_Percentage) {
                changenum = changenum / 100;
                this.mBuffStatistics[this.mConfig.para1] = changenum;
            }
            else if (this.mConfig.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_Percentage) {
                var indexproperty = this.mCaster.basicattr.GetCurrentValue(this.mConfig.para3) * this.mConfig.para5; //索引者为施法者，即Buff添加者
                changenum = changenum + this.mEntity.basicattr.GetCurrentValue(this.mConfig.para1) + indexproperty;
                this.mBuffStatistics[this.mConfig.para1] = changenum;
                indexproperty = null;
            }
        }
        else if (this.mConfig.type == BuffEffecttype.BuffEffecttype_Dot) {
            this.mSkillMaicEffect = new SkillEffect(this.mConfig.para1, this.mEntity, this.mCaster);
            this.mSkillMaicEffect.Accounting(this.mParent.Layers);
        }
        else if (this.mConfig.type == BuffEffecttype.BuffEffecttype_AC) {
            this.mSkillMaicEffect = new SkillEffect(this.mConfig.para1, this.mEntity, this.mCaster);
            this.mSkillMaicEffect.Accounting(this.mParent.Layers);
        }
    };
    return BuffEffect;
}());
__reflect(BuffEffect.prototype, "BuffEffect");
//# sourceMappingURL=BuffEffect.js.map