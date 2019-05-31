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
var BuffTimeType;
(function (BuffTimeType) {
    BuffTimeType[BuffTimeType["BuffTimeType_Begin"] = 1] = "BuffTimeType_Begin";
    BuffTimeType[BuffTimeType["BuffTimeType_End"] = 2] = "BuffTimeType_End";
})(BuffTimeType || (BuffTimeType = {}));
var BuffComponent = (function (_super) {
    __extends(BuffComponent, _super);
    function BuffComponent() {
        return _super.call(this) || this;
    }
    BuffComponent.prototype.start = function () {
        _super.prototype.start.call(this);
        this.mBuffArray = new Array();
        this.avatarEffectComponent = this.entity.getComponent(ComponentType.AvatarEffect);
        this.headComponent = this.entity.getComponent(ComponentType.Head);
        this.headComponent.createhpslider(this.entity.camp);
        var avatarComponent = this.entity.getComponent(ComponentType.Dragon);
        this.mcParent = avatarComponent.Body;
    };
    BuffComponent.prototype.stop = function () {
        _super.prototype.stop.call(this);
    };
    BuffComponent.prototype.update = function (advancetime) {
        _super.prototype.update.call(this, advancetime);
    };
    /**添加Buff
     * @param id BuffID
     * @param casterObj 作俑者
     */
    BuffComponent.prototype.AddBuff = function (id, casterObjId, callback) {
        var buffConf = BuffConfig.GetConfig(id);
        if (this.CheckIsHaveSameIDBuff(id)) {
            this.BuffDealWithSameId(buffConf, casterObjId);
        }
        else if (this.CheckIsHaveSameGroupBuff(buffConf.group)) {
            this.BuffDealWithSameGroup(buffConf, casterObjId);
        }
        else {
            this.AddNewBuff(buffConf, casterObjId);
        }
        if (callback) {
            callback();
        }
    };
    /**
     * 驱散Buff
     */
    BuffComponent.prototype.DisperseBuff = function (type, callback) {
        var num = this.mBuffArray.length;
        for (var i = 0; i < num; i++) {
            if (this.mBuffArray[i].FriendlyType == type && this.mBuffArray[i].DisperseType == BuffDisperseType.BuffDisperseType_CanDis) {
                this.RemoveBuff(this.mBuffArray[i]);
                num = null;
                this.DisperseBuff(type, callback);
                return;
            }
        }
        if (callback) {
            callback();
        }
    };
    /**检测是否存在相同ID的buff */
    BuffComponent.prototype.CheckIsHaveSameIDBuff = function (id) {
        for (var i = 0; i < this.mBuffArray.length; i++) {
            if (this.mBuffArray[i].Config.ID == id) {
                return true;
            }
        }
        return false;
    };
    /**检测是否存在相同Group的buff */
    BuffComponent.prototype.CheckIsHaveSameGroupBuff = function (group) {
        for (var i = 0; i < this.mBuffArray.length; i++) {
            if (this.mBuffArray[i].Config.group == group) {
                return true;
            }
        }
        return false;
    };
    /**
     * Buff相同ID共存逻辑处理
     */
    BuffComponent.prototype.BuffDealWithSameId = function (buffConf, casterObjId) {
        if (buffConf.liveStyle == BuffOverlayProcessing.BuffOverlayProcessing_Offset) {
            this.mBuffArray.forEach(function (data) {
                if (data.Config.ID == buffConf.ID) {
                    this.RemoveBuff(data);
                }
            }.bind(this));
            this.AddNewBuff(buffConf, casterObjId);
        }
        else if (buffConf.liveStyle == BuffOverlayProcessing.BuffOverlayProcessing_coexist) {
            this.AddNewBuff(buffConf, casterObjId);
        }
        else if (buffConf.liveStyle == BuffOverlayProcessing.BuffOverlayProcessing_Overlay) {
            this.mBuffArray.forEach(function (data) {
                if (data.Config.ID == buffConf.ID) {
                    data.CD = buffConf.time;
                    data.AddLayers(1);
                }
            }.bind(this));
        }
        else if (buffConf.liveStyle == BuffOverlayProcessing.BuffOverlayProcessing_Immunity) {
        }
    };
    /**
     * Buff相同Group共存逻辑处理
     */
    BuffComponent.prototype.BuffDealWithSameGroup = function (buffConf, casterObjId) {
        var buffGroup = BuffGroupConfig.GetConfig(buffConf.group);
        if (buffGroup.oper == BuffOverlayProcessing.BuffOverlayProcessing_Offset) {
            this.mBuffArray.forEach(function (data) {
                if (data.Config.group == buffConf.group) {
                    this.RemoveBuff(data);
                }
            }.bind(this));
            this.AddNewBuff(buffConf, casterObjId);
        }
        else if (buffGroup.oper == BuffOverlayProcessing.BuffOverlayProcessing_coexist) {
            this.AddNewBuff(buffConf, casterObjId);
        }
        else if (buffConf.liveStyle == BuffOverlayProcessing.BuffOverlayProcessing_Overlay) {
            this.mBuffArray.forEach(function (data) {
                if (data.Config.ID == buffConf.ID) {
                    data.CD = buffConf.time;
                    data.AddLayers(1);
                }
            }.bind(this));
        }
        else if (buffGroup.oper == BuffOverlayProcessing.BuffOverlayProcessing_Immunity) {
        }
    };
    BuffComponent.prototype.AddNewBuff = function (buffConf, casterObjId) {
        var buff = new Buff(App.MathUtils.uuid(8, 10), casterObjId, this.entity.uid, buffConf);
        buff.Tigger();
        this.mBuffArray.push(buff);
        this.headComponent.addBuffItem(buff.Config.Icon, buff.Config.ID);
        //测试用代码
        //this.AddBuffEffect(buff.Config.ClientEffect, buff);
    };
    /**移除Buff */
    BuffComponent.prototype.RemoveBuff = function (value) {
        var index = this.mBuffArray.indexOf(value);
        if (index != -1) {
            delete this.mBuffArray[index];
            this.mBuffArray.splice(index, 1);
        }
        this.headComponent.removeBuffItem(value.Config.ID);
        this.RemoveBuffEffect(value.Config.effect);
        value.Destory();
        value = null;
    };
    /**播放Buff效果
    * @param id
    * @param buff
    */
    BuffComponent.prototype.PlayBuffEffect = function (id, buff) {
        this.avatarEffectComponent.PlayEffect(id, buff.Config.effectPosType, AvatarEffectType.Buff);
    };
    BuffComponent.prototype.RemoveBuffEffect = function (id) {
        this.avatarEffectComponent.RemoveEffect(id);
    };
    BuffComponent.prototype.UpdateBuffState = function (type, objectId) {
        if (type === void 0) { type = BuffTimeType.BuffTimeType_Begin; }
        if (objectId === void 0) { objectId = ""; }
        this.mBuffArray.sort(function (a, b) {
            if (b.Config.settlePriority > a.Config.settlePriority) {
                return 1;
            }
            else {
                return -1;
            }
        });
        this.UpdateBuffDeath(type, objectId);
        this.UpdateBuffAccount(type, objectId);
        this.UpdateBuffCD(type, objectId);
    };
    /**施法者死亡的 */
    BuffComponent.prototype.UpdateBuffDeath = function (type, objectId) {
        for (var i = 0; i < this.mBuffArray.length; i++) {
            var tempObj = App.FightManager.GetPlayerByUId(this.mBuffArray[i].CasterId);
            if (!tempObj) {
                if (this.mBuffArray[i].Config.settleType == 3 && type == BuffTimeType.BuffTimeType_Begin) {
                    if (this.mBuffArray[i].OwnerId == objectId) {
                        this.mBuffArray[i].Accounting();
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                        }
                    }
                }
                else if (this.mBuffArray[i].Config.settleType == 4 && type == BuffTimeType.BuffTimeType_End) {
                    if (this.mBuffArray[i].OwnerId == objectId) {
                        this.mBuffArray[i].Accounting();
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                        }
                    }
                }
            }
        }
    };
    /** 更新Buff结算*/
    BuffComponent.prototype.UpdateBuffAccount = function (type, objectId) {
        var num = this.mBuffArray.length;
        for (var i = 0; i < num; i++) {
            if (this.mBuffArray[i].Config.settleType == 1 && type == BuffTimeType.BuffTimeType_Begin) {
                if (this.mBuffArray[i].OwnerId == objectId) {
                    this.mBuffArray[i].Accounting();
                }
            }
            else if (this.mBuffArray[i].Config.settleType == 2 && type == BuffTimeType.BuffTimeType_End) {
                if (this.mBuffArray[i].OwnerId == objectId) {
                    this.mBuffArray[i].Accounting();
                }
            }
            else if (this.mBuffArray[i].Config.settleType == 3 && type == BuffTimeType.BuffTimeType_Begin) {
                if (this.mBuffArray[i].CasterId == objectId) {
                    this.mBuffArray[i].Accounting();
                }
            }
            else if (this.mBuffArray[i].Config.settleType == 4 && type == BuffTimeType.BuffTimeType_End) {
                if (this.mBuffArray[i].CasterId == objectId) {
                    this.mBuffArray[i].Accounting();
                }
            }
        }
        num = 0;
    };
    /**更新BuffCD */
    BuffComponent.prototype.UpdateBuffCD = function (type, objectId) {
        var num = this.mBuffArray.length;
        for (var i = 0; i < num; i++) {
            if (this.mBuffArray[i].CD != -1) {
                if (this.mBuffArray[i].Config.timeType == 1 && type == BuffTimeType.BuffTimeType_Begin) {
                    if (this.mBuffArray[i].OwnerId == objectId) {
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                            this.UpdateBuffCD(type, objectId);
                            num = null;
                            return;
                        }
                    }
                }
                else if (this.mBuffArray[i].Config.timeType == 2 && type == BuffTimeType.BuffTimeType_End) {
                    if (this.mBuffArray[i].OwnerId == objectId) {
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                            this.UpdateBuffCD(type, objectId);
                            num = null;
                            return;
                        }
                    }
                }
                else if (this.mBuffArray[i].Config.timeType == 3 && type == BuffTimeType.BuffTimeType_Begin) {
                    if (this.mBuffArray[i].CasterId == objectId) {
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                            this.UpdateBuffCD(type, objectId);
                            num = null;
                            return;
                        }
                    }
                }
                else if (this.mBuffArray[i].Config.timeType == 4 && type == BuffTimeType.BuffTimeType_End) {
                    if (this.mBuffArray[i].CasterId == objectId) {
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                            this.UpdateBuffCD(type, objectId);
                            num = null;
                            return;
                        }
                    }
                }
            }
        }
    };
    /**
     * 身上是否有眩晕buff
     */
    BuffComponent.prototype.IsDizziness = function () {
        for (var _i = 0, _a = this.BuffArray; _i < _a.length; _i++) {
            var buf = _a[_i];
            if (buf.ControlType == BuffControlType.BuffControlType_Dizziness) {
                return true;
            }
        }
        return false;
    };
    /**
     * 身上是否沉默buf
     */
    BuffComponent.prototype.IsSilence = function () {
        for (var _i = 0, _a = this.BuffArray; _i < _a.length; _i++) {
            var buf = _a[_i];
            if (buf.ControlType == BuffControlType.BuffControlType_Silence) {
                return true;
            }
        }
        return false;
    };
    Object.defineProperty(BuffComponent.prototype, "BuffArray", {
        get: function () {
            return this.mBuffArray;
        },
        enumerable: true,
        configurable: true
    });
    return BuffComponent;
}(Component));
__reflect(BuffComponent.prototype, "BuffComponent");
var AvatarBuffMovieClip = (function (_super) {
    __extends(AvatarBuffMovieClip, _super);
    function AvatarBuffMovieClip() {
        return _super.call(this) || this;
    }
    AvatarBuffMovieClip.prototype.Init = function (gameResGroupName, mcpath, mcname, entity) {
        _super.prototype.Init.call(this, gameResGroupName, mcpath, mcname, entity);
    };
    AvatarBuffMovieClip.prototype.start = function () {
        _super.prototype.start.call(this);
    };
    AvatarBuffMovieClip.prototype.stop = function () {
        _super.prototype.stop.call(this);
    };
    AvatarBuffMovieClip.prototype.update = function (advancetime) {
        _super.prototype.update.call(this, advancetime);
        this.MovieClip.runAction(advancetime);
    };
    AvatarBuffMovieClip.prototype.complateAction = function () {
        _super.prototype.complateAction.call(this);
    };
    return AvatarBuffMovieClip;
}(MovieClipComponentBase));
__reflect(AvatarBuffMovieClip.prototype, "AvatarBuffMovieClip");
//# sourceMappingURL=BuffComponent.js.map