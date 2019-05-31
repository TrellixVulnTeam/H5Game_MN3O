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
 * 技能管理
 */
var SkillComponent = (function (_super) {
    __extends(SkillComponent, _super);
    function SkillComponent() {
        var _this = _super.call(this) || this;
        _this.SkillAyyary = new Array();
        return _this;
    }
    SkillComponent.prototype.start = function () {
        _super.prototype.start.call(this);
        this.InitData();
    };
    SkillComponent.prototype.stop = function () {
        _super.prototype.stop.call(this);
        for (var skill in this.SkillAyyary) {
            ObjectPool.push(skill);
        }
        this.SkillAyyary = [];
    };
    SkillComponent.prototype.update = function (advancedTime) {
        _super.prototype.update.call(this, advancedTime);
    };
    SkillComponent.prototype.InitData = function () {
        this.abilityConf = CreatureAbilityConfig.GetConfig(this.entity.CreatureConf.ability);
        if (this.abilityConf && this.abilityConf.magic1 != 0) {
            var skill1 = ObjectPool.pop("Skill", this.abilityConf.magic1, this.entity);
            this.SkillAyyary.push(skill1);
        }
        if (this.abilityConf && this.abilityConf.magic2 != 0) {
            var skill2 = ObjectPool.pop("Skill", this.abilityConf.magic2, this.entity);
            this.SkillAyyary.push(skill2);
        }
        if (this.abilityConf && this.abilityConf.magic3 != 0) {
            var skill3 = ObjectPool.pop("Skill", this.abilityConf.magic3, this.entity);
            this.SkillAyyary.push(skill3);
        }
        if (this.abilityConf && this.abilityConf.magic4 != 0) {
            var skill4 = ObjectPool.pop("Skill", this.abilityConf.magic4, this.entity);
            this.SkillAyyary.push(skill4);
        }
    };
    SkillComponent.prototype.UseSkill = function (value, targertObj, callback, previousCallback) {
        if (typeof value == "number") {
            var skill = this.GetSkill(value);
            if (skill) {
                if (!skill.InCD) {
                    if (skill.MagicConfig) {
                        if (App.TimerManager.TimeScale == 1) {
                            this.PlayerScaleAndDrawing(skill, skill.MagicConfig.ID, targertObj, callback, previousCallback);
                        }
                        else {
                            if (targertObj) {
                                this.IsNeedMove(skill, targertObj, callback);
                            }
                            else {
                                this.IsNeedMove(skill, targertObj, callback);
                            }
                        }
                    }
                }
            }
        }
        else {
            if (value) {
                if (!value.InCD) {
                    if (value.MagicConfig) {
                        if (App.TimerManager.TimeScale == 1) {
                            this.PlayerScaleAndDrawing(value, value.MagicConfig.ID, targertObj, callback, previousCallback);
                        }
                        else {
                            if (targertObj) {
                                this.IsNeedMove(value, targertObj, callback);
                            }
                            else {
                                this.IsNeedMove(value, targertObj, callback);
                            }
                        }
                    }
                }
            }
        }
    };
    /**
     * 播放放大高亮及立绘
     */
    SkillComponent.prototype.PlayerScaleAndDrawing = function (skill, id, targertObj, callback, previousCallback) {
        if (skill.MagicConfig.ifEnlarge) {
            App.ActionManager.PlayerScale(this.entity, true, function () {
                if (skill.MagicConfig.ifAnimation) {
                    this.PlayThreeDimensionalDrawing(skill.MagicConfig.ID, function () {
                        if (previousCallback)
                            previousCallback(); //连携技播放完立绘再让上一个玩家回去
                        App.ActionManager.playerMaskViableFalse(this.entity.uid);
                        this.IsNeedMove(skill, targertObj, function () {
                            App.ActionManager.PlayerScale(this.entity, false, callback);
                        }.bind(this));
                    }.bind(this));
                }
                else {
                    App.ActionManager.playerMaskViableFalse(this.entity.uid);
                    if (targertObj) {
                        this.IsNeedMove(skill, targertObj, function () {
                            App.ActionManager.PlayerScale(this.entity, false, callback);
                        }.bind(this));
                    }
                    else {
                        this.IsNeedMove(skill, targertObj, function () {
                            App.ActionManager.PlayerScale(this.entity, false, callback);
                        }.bind(this));
                    }
                }
            }.bind(this));
        }
        else {
            if (skill.MagicConfig.ifAnimation) {
                this.PlayThreeDimensionalDrawing(skill.MagicConfig.ID, function () {
                    if (previousCallback)
                        previousCallback(); //连携技播放完立绘再让上一个玩家回去
                    this.IsNeedMove(skill, targertObj, callback);
                }.bind(this));
            }
            else {
                if (targertObj) {
                    this.IsNeedMove(skill, targertObj, callback);
                }
                else {
                    this.IsNeedMove(skill, targertObj, callback);
                }
            }
        }
    };
    /**
     * 使用技能播放立绘
     * callback 回调函数
     */
    SkillComponent.prototype.PlayThreeDimensionalDrawing = function (id, callback) {
        if (!App.FightManager.IsBackstage) {
            App.EventMgrHelper.PushEventEx(EventDef.SetBackMainBtnVis, false, null, 0, 0, "", "");
            var effectCompont = this.entity.getComponent(ComponentType.AvatarEffect);
            effectCompont.PlayEffect(1000010, 5, AvatarEffectType.Buff, function () {
                App.EventMgrHelper.PushEventEx(EventDef.SKILLPICTURE_C2C, function () {
                    App.EventMgrHelper.PushEventEx(EventDef.SetBackMainBtnVis, true, null, 0, 0, "", "");
                    var effectCompont = this.entity.getComponent(ComponentType.AvatarEffect);
                    effectCompont.PlayEffect(1000020, 5, AvatarEffectType.Buff, function () {
                        if (callback)
                            callback();
                    }.bind(this));
                }.bind(this), null, id, 0, "", "");
            }.bind(this));
        }
        else {
            if (callback)
                callback();
        }
    };
    /**
     * 是否需要移动
     * @param skill
     * @param isNeedMove 是否需要移动
     * @param target 目标
     * @param callback 回调函数
     */
    SkillComponent.prototype.IsNeedMove = function (skill, target, callback) {
        if (skill.MagicConfig.rolePosType == 1) {
            var moveCom = this.entity.getComponent(ComponentType.Move);
            //坐标      
            var point = new egret.Point();
            if (target.dir == Dir.Left) {
                point.x = target.position.x + skill.MagicConfig.rolePosition[0];
                point.y = target.position.y + skill.MagicConfig.rolePosition[1];
            }
            else {
                point.x = target.position.x - skill.MagicConfig.rolePosition[0];
                point.y = target.position.y - skill.MagicConfig.rolePosition[1];
            }
            //let point: egret.Point = new egret.Point(target.position.x + skill.MagicConfig.rolePosition[0], target.position.y + skill.MagicConfig.rolePosition[1]);
            moveCom.DoMove(point, function () {
                if (target) {
                    this.DoSKill(skill, target, callback);
                }
                else {
                    this.DoSKill(skill, this.GetTarget(), callback);
                }
            }.bind(this));
        }
        else {
            if (target) {
                this.DoSKill(skill, target, callback);
            }
            else {
                this.DoSKill(skill, this.GetTarget(), callback);
            }
        }
    };
    /**
     * 执行技能
     * @param skill
     * @param target 目标
     * @param isNeedReturnPos 技能执行完毕是否需要返回原位置
     * @param callback 回调函数
     */
    SkillComponent.prototype.DoSKill = function (skill, target, callback) {
        if (skill) {
            this.entity.AddClientBitState(ClientBits.CLIENT_BIT_CASTING);
            skill.Tigger(target, function () {
                if (skill.SkillType == SkillType.ActiveSkills) {
                    if (skill.MagicConfig.ifCombo && target.Alive) {
                        this.TriggerConnectionTechnology(target, callback, function (callback) {
                            this.SkillEnd(skill, callback, this.entity);
                        }.bind(this));
                    }
                    else {
                        this.SkillEnd(skill, callback);
                    }
                }
                else if (skill.SkillType == SkillType.LinkingSkill) {
                    callback();
                }
                else {
                    this.SkillEnd(skill, callback);
                }
            }.bind(this));
        }
    };
    /**
     * 触发连携技
     */
    SkillComponent.prototype.TriggerConnectionTechnology = function (target, callback, skillCallback) {
        var linkObjs = App.FightManager.CanUseLinkingSkillPlayer(this.entity);
        if (linkObjs.length < 1) {
            skillCallback(callback);
        }
        else {
            this.UserConnectionTechnology(linkObjs, target, callback, skillCallback);
        }
    };
    /**
     * 递归执行连携技
     */
    SkillComponent.prototype.UserConnectionTechnology = function (linkObjs, target, callback, skillCallback) {
        var _this = this;
        if (linkObjs.length > 0 && target && App.FightManager.IsExistInAllObj(target)) {
            var currentObj_1 = linkObjs[0];
            var skillCom = currentObj_1.getComponent(ComponentType.Skill);
            if (skillCom) {
                var skill_1 = skillCom.GetSkill(SkillType.LinkingSkill);
                skillCom.UseSkill(skill_1, target, function () {
                    var index = linkObjs.indexOf(currentObj_1);
                    if (index != -1) {
                        linkObjs.splice(index, 1);
                        if (linkObjs.length == 0) {
                            _this.SkillEnd(skill_1, null, currentObj_1);
                        }
                        _this.UserConnectionTechnology(linkObjs, target, callback, function () { return _this.SkillEnd(skill_1, null, currentObj_1); });
                    }
                }, skillCallback);
            }
        }
        else {
            if (callback) {
                callback();
            }
        }
    };
    SkillComponent.prototype.GetTarget = function () {
        return this.target;
    };
    SkillComponent.prototype.SetTarget = function (object) {
        this.target = object;
    };
    SkillComponent.prototype.GetSkill = function (val) {
        if (typeof val == "number" && val > SkillType.MAX) {
            for (var i = 0; i < this.SkillAyyary.length; i++) {
                if (this.SkillAyyary[i].SkillId == val) {
                    return this.SkillAyyary[i];
                }
            }
        }
        else {
            for (var i = 0; i < this.SkillAyyary.length; i++) {
                if (this.SkillAyyary[i].SkillType == val) {
                    return this.SkillAyyary[i];
                }
            }
        }
    };
    SkillComponent.prototype.SkillEnd = function (skill, callback, obj) {
        if (obj == null) {
            if (callback)
                callback();
            return;
        }
        var currentEntity;
        if (obj != null) {
            currentEntity = obj;
        }
        else {
            currentEntity = this.entity;
        }
        if (skill.MagicConfig.rolePosType == 1) {
            var moveCom = currentEntity.getComponent(ComponentType.Move);
            var point = currentEntity.StartPosition;
            moveCom.DoMove(point, function () {
                currentEntity.getComponent(ComponentType.Dragon).PlayAct(ActionStr.Stand);
                if (callback) {
                    callback();
                }
            }.bind(this), 249);
        }
        else {
            currentEntity.getComponent(ComponentType.Dragon).PlayAct(ActionStr.Stand);
            if (callback) {
                callback();
            }
        }
        currentEntity.DelClientBitState(ClientBits.CLIENT_BIT_CASTING);
    };
    /**
     * 更新技能状态
     */
    SkillComponent.prototype.UpdateSkillState = function () {
        //CD 
        this.SkillAyyary.forEach(function (data) {
            data.CD = (data.CD - 1);
        });
    };
    /**
      * 获得被动技能
      */
    SkillComponent.prototype.GetPassiveSkill = function () {
        for (var _i = 0, _a = this.SkillAyyary; _i < _a.length; _i++) {
            var element = _a[_i];
            if (element.MagicConfig.type == SkillType.PassiveSkill) {
                return element;
            }
        }
        return null;
    };
    /**
     * 获取可用主动技能
     */
    SkillComponent.prototype.GetAvailable = function () {
        var tempArr = this.SkillAyyary;
        //按主动技能优先级排序
        tempArr.sort(function (a, b) {
            if (a.MagicConfig.autoSkillPriority < b.MagicConfig.autoSkillPriority) {
                return 1;
            }
            else {
                return -1;
            }
        });
        for (var _i = 0, tempArr_1 = tempArr; _i < tempArr_1.length; _i++) {
            var element = tempArr_1[_i];
            if (element.MagicConfig.type == SkillType.ActiveSkills) {
                if (element.CD == 0) {
                    return element;
                }
            }
        }
        return null;
    };
    /**
     * 获取所有主动技能
     */
    SkillComponent.prototype.GetAvailableSkill = function () {
        var avaSkill = [];
        this.SkillAyyary.forEach(function (element) {
            if (element.SkillType == SkillType.ActiveSkills)
                avaSkill.push(element);
        });
        return avaSkill;
    };
    return SkillComponent;
}(Component));
__reflect(SkillComponent.prototype, "SkillComponent");
//# sourceMappingURL=SkillComponent.js.map