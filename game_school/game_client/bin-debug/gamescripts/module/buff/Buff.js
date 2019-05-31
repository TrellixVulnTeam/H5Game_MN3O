var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**Buff类型 */
var BuffFriendlyType;
(function (BuffFriendlyType) {
    /**良性效果 */
    BuffFriendlyType[BuffFriendlyType["BUFFTYPE_POSITIVE"] = 0] = "BUFFTYPE_POSITIVE";
    /**负面效果 */
    BuffFriendlyType[BuffFriendlyType["BUFFTYPE_NEGATIVE"] = 1] = "BUFFTYPE_NEGATIVE";
    /**中立效果 */
    BuffFriendlyType[BuffFriendlyType["BUFFTYPE_NEUTRAL"] = 2] = "BUFFTYPE_NEUTRAL";
})(BuffFriendlyType || (BuffFriendlyType = {}));
/**Buff共存逻辑类型 */
var BuffOverlayProcessing;
(function (BuffOverlayProcessing) {
    /**冲抵 */
    BuffOverlayProcessing[BuffOverlayProcessing["BuffOverlayProcessing_Offset"] = 1] = "BuffOverlayProcessing_Offset";
    /**免疫 */
    BuffOverlayProcessing[BuffOverlayProcessing["BuffOverlayProcessing_Immunity"] = 2] = "BuffOverlayProcessing_Immunity";
    /**共存 */
    BuffOverlayProcessing[BuffOverlayProcessing["BuffOverlayProcessing_coexist"] = 3] = "BuffOverlayProcessing_coexist";
    /**叠加 */
    BuffOverlayProcessing[BuffOverlayProcessing["BuffOverlayProcessing_Overlay"] = 4] = "BuffOverlayProcessing_Overlay";
})(BuffOverlayProcessing || (BuffOverlayProcessing = {}));
/**Buff驱散类型 */
var BuffDisperseType;
(function (BuffDisperseType) {
    /**不可驱散 */
    BuffDisperseType[BuffDisperseType["BuffDisperseType_NotDis"] = 0] = "BuffDisperseType_NotDis";
    /**可驱散 */
    BuffDisperseType[BuffDisperseType["BuffDisperseType_CanDis"] = 1] = "BuffDisperseType_CanDis";
})(BuffDisperseType || (BuffDisperseType = {}));
/**Buff控制类型 */
var BuffControlType;
(function (BuffControlType) {
    /**眩晕 */
    BuffControlType[BuffControlType["BuffControlType_Dizziness"] = 1] = "BuffControlType_Dizziness";
    /**沉默 */
    BuffControlType[BuffControlType["BuffControlType_Silence"] = 1] = "BuffControlType_Silence";
})(BuffControlType || (BuffControlType = {}));
/**
 * created by sjz on 2018-5-10.
 * Buff
 */
var Buff = (function () {
    function Buff(uid, casterid, ownerid, buffconf) {
        this.mUid = uid;
        this.mCasterId = casterid;
        this.mOwnerId = ownerid;
        this.mBuffeffectArray = new Array();
        this.mConfig = buffconf;
        this.mFriendlyType = buffconf.friendlyLevel;
        this.mDispleType = buffconf.dispelType;
        if (TestBits.TestBuffControlTypeBits(buffconf.controlBit, BuffControlType.BuffControlType_Dizziness)) {
            this.mControlType = BuffControlType.BuffControlType_Dizziness;
        }
        else if (TestBits.TestBuffControlTypeBits(buffconf.controlBit, BuffControlType.BuffControlType_Silence)) {
            this.mControlType = BuffControlType.BuffControlType_Silence;
        }
        this.mMaxLayers = this.mConfig.maxLayers;
        this.mLayers = this.mConfig.defaultLayers;
        this.mCd = this.mConfig.time;
    }
    Object.defineProperty(Buff.prototype, "CasterId", {
        get: function () {
            return this.mCasterId;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Buff.prototype, "OwnerId", {
        get: function () {
            return this.mOwnerId;
        },
        enumerable: true,
        configurable: true
    });
    Buff.prototype.Destory = function () {
        this.DestoryBuffEffect();
    };
    Object.defineProperty(Buff.prototype, "UID", {
        get: function () {
            return this.mUid;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Buff.prototype, "BuffEffectArray", {
        get: function () {
            return this.mBuffeffectArray;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Buff.prototype, "Config", {
        get: function () {
            return this.mConfig;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Buff.prototype, "CD", {
        /**-1代表永久 */
        get: function () {
            return this.mCd;
        },
        set: function (value) {
            this.mCd = value <= 0 ? 0 : value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Buff.prototype, "FriendlyType", {
        /**友好度类型 */
        get: function () {
            return this.mFriendlyType;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Buff.prototype, "ControlType", {
        /**控制类型 */
        get: function () {
            return this.mControlType;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Buff.prototype, "DisperseType", {
        /**驱散性质 */
        get: function () {
            return this.mDispleType;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(Buff.prototype, "Layers", {
        /**叠加层数 */
        get: function () {
            return this.mLayers;
        },
        enumerable: true,
        configurable: true
    });
    /**增加叠加层数 */
    Buff.prototype.AddLayers = function (value) {
        var layers = value + this.mLayers;
        if (layers > this.mMaxLayers) {
            layers = this.mMaxLayers;
        }
        this.mLayers = layers;
    };
    Buff.prototype.Tigger = function (callback) {
        this.AddBuffEffect();
    };
    Buff.prototype.AddBuffEffect = function (callback) {
        if (this.mConfig.effectID1 != -1) {
            var buffEffect1 = new BuffEffect(this.mConfig.effectID1, this, App.FightManager.GetPlayerByUId(this.mOwnerId), App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect1);
        }
        if (this.mConfig.effectID2 != -1) {
            var buffEffect2 = new BuffEffect(this.mConfig.effectID2, this, App.FightManager.GetPlayerByUId(this.mOwnerId), App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect2);
        }
        if (this.mConfig.effectID3 != -1) {
            var buffEffect3 = new BuffEffect(this.mConfig.effectID3, this, App.FightManager.GetPlayerByUId(this.mOwnerId), App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect3);
        }
        if (this.mConfig.effectID4 != -1) {
            var buffEffect4 = new BuffEffect(this.mConfig.effectID4, this, App.FightManager.GetPlayerByUId(this.mOwnerId), App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect4);
        }
        if (this.mConfig.effectID5 != -1) {
            var buffEffect5 = new BuffEffect(this.mConfig.effectID5, this, App.FightManager.GetPlayerByUId(this.mOwnerId), App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect5);
        }
        if (this.mConfig.effect != null) {
            //预留 客户端表现
            var entity = App.FightManager.GetPlayerByUId(this.mOwnerId);
            if (entity) {
                var compont = entity.getComponent(ComponentType.Buff);
                compont.PlayBuffEffect(this.mConfig.effect, this); //播放特效            
            }
        }
    };
    /**
     * 移除当前buff所有表现
     */
    Buff.prototype.DestoryBuffEffect = function () {
        for (var i = 0; i < this.mBuffeffectArray.length; i++) {
            this.mBuffeffectArray[i].Destory();
            delete this.mBuffeffectArray[i];
        }
        this.mBuffeffectArray.slice(0, this.mBuffeffectArray.length);
    };
    Buff.prototype.Accounting = function () {
        for (var i = 0; i < this.mBuffeffectArray.length; i++) {
            this.mBuffeffectArray[i].Update();
        }
    };
    return Buff;
}());
__reflect(Buff.prototype, "Buff");
//# sourceMappingURL=Buff.js.map