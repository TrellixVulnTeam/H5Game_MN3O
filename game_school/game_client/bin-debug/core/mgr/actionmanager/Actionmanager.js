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
var HurtType;
(function (HurtType) {
    HurtType[HurtType["Hurt"] = 0] = "Hurt";
    HurtType[HurtType["Gain"] = 1] = "Gain";
    HurtType[HurtType["Max"] = 2] = "Max";
})(HurtType || (HurtType = {}));
var ActionManager = (function (_super) {
    __extends(ActionManager, _super);
    function ActionManager() {
        var _this = _super.call(this) || this;
        _this.currentObj = null; //当前行动对象
        _this.currentSkill = null; //当前技能
        _this.currentTarget = null; //当前目标
        _this.actioning = false; //行动中
        _this.waitAuto = false; //等待操作
        return _this;
    }
    /**
     * 开启行动
     */
    ActionManager.prototype.StartAction = function (obj, actionEnd) {
        var _this = this;
        this.actioning = true;
        this.timer = 10;
        this.ResetAction();
        this.currentEnd = actionEnd;
        this.currentObj = obj;
        this.currentCamp = obj.camp;
        this.currentBuffCom = this.currentObj.getComponent(ComponentType.Buff);
        this.currentKillCom = this.currentObj.getComponent(ComponentType.Skill);
        this.SetSideList();
        this.SelectedEffectShow(this.currentObj, true);
        if (!App.FightManager.IsAutomatic)
            this.timeHandler = App.TimerManager.doTimer(1000, this.timer, function () { return _this.OnTimeUpdate(); }, this, 0, function () { return _this.OnTimeFinity(); }, this); //一秒一次
        this.DiversionAction();
    };
    ActionManager.prototype.SetSideList = function () {
        if (this.currentCamp == Camp.Friendly) {
            this.currentotherSide = App.FightManager.EnemyPlayers;
            this.currentSelfSide = App.FightManager.OwnerPlayers;
        }
        else {
            this.currentotherSide = App.FightManager.OwnerPlayers;
            this.currentSelfSide = App.FightManager.EnemyPlayers;
        }
    };
    /**
     * 选中
     */
    ActionManager.prototype.SelectedEffectShow = function (target, self) {
        var avatarCom = target.getComponent(ComponentType.Dragon);
        if (avatarCom)
            selectCharacter.onSelectImg(avatarCom.Body, target.camp);
        if (self) {
            this.currentSelfSide.forEach(function (element) {
                if (element.uid != target.uid) {
                    var enemyCom = element.getComponent(ComponentType.Dragon);
                    selectCharacter.unSelectImg(enemyCom.Body);
                }
            });
        }
        else {
            this.currentotherSide.forEach(function (element) {
                if (element.uid != target.uid) {
                    var enemyCom = element.getComponent(ComponentType.Dragon);
                    selectCharacter.unSelectImg(enemyCom.Body);
                }
            });
        }
    };
    /**
     * 分类执行
     */
    ActionManager.prototype.DiversionAction = function () {
        if (!this.currentBuffCom.IsDizziness()) {
            if (this.currentObj.camp == Camp.Friendly)
                this.FriendlyAction();
            else
                this.HostilityAction();
        }
        else {
            this.currentEnd(); //如果眩晕直接结束行为
        }
    };
    /**
     * 计时器更新
     */
    ActionManager.prototype.OnTimeUpdate = function () {
        this.timer--;
        if (this.timer <= 2 && !App.FightManager.IsAutomatic) {
            App.EventMgrHelper.PushEvent(EventDef.UpdateTimer, this.timer);
        }
    };
    /**
     * 计时结束
     */
    ActionManager.prototype.OnTimeFinity = function () {
        if (this.timer <= 0) {
            if (this.timeHandler)
                App.TimerManager.remove(this.timeHandler.id, this);
            App.FightManager.IsAutomatic = true;
        }
    };
    /**
     * 友好
     */
    ActionManager.prototype.FriendlyAction = function () {
        var skillCom = this.currentObj.getComponent(ComponentType.Skill);
        var skills = skillCom.GetAvailableSkill();
        App.EventMgrHelper.PushEventEx(EventDef.OpenSkill, this.currentObj, skills, 0, 0, "", "");
        if (!App.FightManager.IsAutomatic) {
            this.waitAuto = true;
        }
        else {
            this.AutoAction();
        }
    };
    /**
     * 敌人的话直接执行ai
     */
    ActionManager.prototype.HostilityAction = function () {
        App.EventMgrHelper.PushEventEx(EventDef.OpenSkill, this.currentObj, null, 0, 0, "", "");
        this.AutoAction();
    };
    /**
     * 自动执行
     */
    ActionManager.prototype.AutoAction = function () {
        this.currentSkill = this.currentKillCom.GetAvailable(); //获取主动技能
        this.currentTarget = this.GetTarget();
        //	console.log("AutoAction:"+this.currentTarget.basicattr.Name);
        this.UseSkillAction();
    };
    /**
     * 执行战斗
     */
    ActionManager.prototype.UseSkillAction = function () {
        this.actioning = false;
        this.waitAuto = false;
        if (this.currentTarget != null) {
            this.SelectedEffectShow(this.currentTarget, false);
            if (this.currentSkill != null) {
                this.currentKillCom.SetTarget(this.currentTarget);
                this.currentKillCom.UseSkill(this.currentSkill.SkillId, this.currentTarget, function () {
                    this.SkillCallback(this.currentTarget);
                }.bind(this));
            }
            else {
            }
        }
        else {
            //没有找到目标
        }
    };
    /**
     * 玩家缩放高亮
     */
    ActionManager.prototype.PlayerScale = function (obj, enlarge, callback) {
        if (obj) {
            var multiple = obj.oriScale * 1.2;
            if (enlarge) {
                this.playerMaskViableTrue(obj.uid);
                this.playerObjExpression(obj, [1, 1], [obj.oriScale, multiple], [0, 30], [0, 200], 200, function () {
                    if (callback)
                        callback();
                }.bind(this));
            }
            else {
                this.playerObjExpression(obj, [1, 1], [obj.oriScale, obj.oriScale], [30, 0], [0, 200], 200, function () {
                    if (callback)
                        callback();
                }.bind(this));
            }
        }
        else {
            if (callback)
                callback();
        }
    };
    /**
     * 技能释放完毕回调
     */
    ActionManager.prototype.SkillCallback = function (target) {
        //console.log("SkillCallback");
        this.ActionFinity();
    };
    /**
     * 选择目标
     */
    ActionManager.prototype.GetTarget = function () {
        this.SetSideList();
        //顺序  血量百分比少的， 血量数值少的， 按站位 1 2 3
        //console.log(this.currentotherSide.length);
        if (this.currentotherSide.length > 0) {
            return this.Sortpercentage()[0];
        }
        return null;
    };
    /**
     * 行动结束
     */
    ActionManager.prototype.ActionFinity = function () {
        if (this.timeHandler)
            App.TimerManager.remove(this.timeHandler.id, this);
        this.currentEnd();
    };
    /**
     * 重置行动
     */
    ActionManager.prototype.ResetAction = function () {
        this.currentObj = null;
        this.currentSkill = null;
        this.currentTarget = null;
    };
    /**
     * 按百分比排序
     */
    ActionManager.prototype.Sortpercentage = function () {
        var tempObjs = this.currentotherSide;
        tempObjs.sort(function (a, b) {
            if ((a.basicattr.OriHp / a.basicattr.MaxHP) < (a.basicattr.OriHp / a.basicattr.MaxHP))
                return 1;
            else
                return -1;
        });
        var sameObjs;
        var comObj = tempObjs[0];
        tempObjs.forEach(function (element) {
            if ((comObj.basicattr.OriHp / comObj.basicattr.MaxHP) == (element.basicattr.OriHp / element.basicattr.MaxHP)) {
                sameObjs.push(element);
            }
        });
        if (sameObjs != null && sameObjs.length > 1) {
            return this.SortHPValue(sameObjs);
        }
        else {
            return tempObjs;
        }
    };
    /**
     * 按血量排序
     */
    ActionManager.prototype.SortHPValue = function (objlist) {
        objlist.sort(function (a, b) {
            if (a.basicattr.OriHp < a.basicattr.OriHp)
                return 1;
            else
                return -1;
        });
        var sameObjs;
        var comObj = objlist[0];
        objlist.forEach(function (element) {
            if (comObj.basicattr.OriHp == element.basicattr.OriHp) {
                sameObjs.push(element);
            }
        });
        if (sameObjs != null && sameObjs.length > 1) {
            return this.SortPoint(sameObjs);
        }
        else {
            return objlist;
        }
    };
    /**
     * 按站位从上往下排序
     */
    ActionManager.prototype.SortPoint = function (objlist) {
        objlist.sort(function (a, b) {
            if (a.posInfo.LineNum < a.posInfo.LineNum) {
                return 1;
            }
            else {
                return -1;
            }
        });
        return objlist;
    };
    Object.defineProperty(ActionManager.prototype, "WaitAuto", {
        get: function () { return this.waitAuto; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionManager.prototype, "CurrentObj", {
        set: function (value) { this.currentObj = value; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionManager.prototype, "CurrentTarget", {
        /**
         * 设置目标
         */
        set: function (value) {
            if (this.actioning && value.camp != this.currentCamp) {
                this.currentTarget = value;
                this.SelectedEffectShow(this.currentTarget, false);
                if (this.currentSkill != null) {
                    this.UseSkillAction();
                }
                else {
                }
            }
            else {
            }
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(ActionManager.prototype, "CurrentSkill", {
        /**
         * 设置技能
         */
        set: function (value) {
            if (this.actioning) {
                this.currentSkill = value;
                if (this.currentTarget != null) {
                    this.UseSkillAction();
                }
                else {
                    this.currentTarget = this.GetTarget();
                    this.UseSkillAction();
                }
            }
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 初始化受伤列表
     */
    ActionManager.prototype.InitInjuredList = function () {
        this.currentInjuredList = [];
    };
    /**
     * 添加受伤
     */
    ActionManager.prototype.AddInjureList = function (obj) {
        for (var i = 0; i < this.currentInjuredList.length; i++) {
            if (this.currentInjuredList[i].uid == obj.uid) {
                return;
            }
        }
        if (obj) {
            var buffCom = obj.getComponent(ComponentType.Buff);
            if (!buffCom.CheckIsHaveSameIDBuff(parseInt(ClientConstConfig.GetConfig(5).value))) {
                this.currentInjuredList.push(obj);
            }
        }
    };
    /**
     * 受伤立绘
     */
    ActionManager.prototype.PlayInjure = function (callback) {
        if (App.FightManager.IsBackstage) {
            if (callback)
                callback();
            return;
        }
        if (this.currentInjuredList.length <= 0) {
            if (callback)
                callback();
        }
        else {
            var currentObj_1 = this.currentInjuredList[0];
            var index = this.currentInjuredList.indexOf(currentObj_1);
            if (index != -1) {
                this.currentInjuredList.splice(index, 1);
            }
            if (currentObj_1) {
                App.EventMgrHelper.PushEventEx(EventDef.SetBackMainBtnVis, false, null, 0, 0, "", "");
                App.EventMgrHelper.PushEventEx(EventDef.HPPICTURE_C2C, function () {
                    var buffCom = currentObj_1.getComponent(ComponentType.Buff);
                    if (buffCom) {
                        App.EventMgrHelper.PushEventEx(EventDef.SetBackMainBtnVis, true, null, 0, 0, "", "");
                        buffCom.AddBuff(parseInt(ClientConstConfig.GetConfig(5).value), currentObj_1.uid);
                        this.PlayInjure(callback);
                    }
                    else {
                        if (callback)
                            callback();
                    }
                }.bind(this), null, 0, 0, "", "");
            }
            else {
                if (callback)
                    callback();
            }
        }
    };
    /**
     * 开启半透明遮罩
    */
    ActionManager.prototype.playerMaskViableTrue = function (objUID) {
        App.EventMgrHelper.PushEvent(EventDef.FightMaskViableTrue, 0, 0, objUID);
    };
    /**
     * 关闭半透明遮罩
    */
    ActionManager.prototype.playerMaskViableFalse = function (objUID) {
        App.EventMgrHelper.PushEvent(EventDef.FightMaskViableFalse, 0, 0, objUID);
    };
    /**
     * 角色透明度，放缩和滤镜
     *
     * alpha[]初始透明度, 变化透明度
     * scale[]初始缩放比例, 变化缩放比例
     * filter[]初始滤镜值, 滤镜变化值
     * time[]等待时长，变化时长
     * functionTime回掉函数等待时长
     * callBack回掉函数
    */
    ActionManager.prototype.playerObjExpression = function (obj, alpha, scale, filter, time, functionTime, callBack) {
        if (functionTime === void 0) { functionTime = 0; }
        if (obj != null) {
            var compon = obj.getComponent(ComponentType.Dragon);
            if (compon != null) {
                if (compon instanceof DragonComponent) {
                    if (compon.Body != null) {
                        var body = compon.Body;
                        this.playerBodyExpression(body, alpha, scale, filter, time, functionTime, callBack);
                    }
                }
            }
        }
    };
    /**
     * alpha[]初始透明度, 变化透明度
     * scale[]初始缩放比例, 变化缩放比例
     * filter[]初始滤镜值, 滤镜变化值
     * time[]等待时长，变化时长
     * functionTime回掉函数等待时长
     * callBack回掉函数
    */
    ActionManager.prototype.playerBodyExpression = function (target, alpha, scale, filter, time, functionTime, callBack) {
        var _this = this;
        if (functionTime === void 0) { functionTime = 0; }
        if (target == null || alpha.length < 2 || scale.length < 2 || time.length < 2 || filter.length < 2) {
            return;
        }
        target.alpha = alpha[0];
        target.scaleX = scale[0];
        target.scaleY = scale[0];
        egret.Tween.get(target)
            .wait(time[0])
            .call(function () {
            _this.setObjFilters(target, filter[0], filter[1]);
            egret.Tween.get(target)
                .to({ alpha: alpha[1], scaleX: scale[1], scaleY: scale[1] }, time[1])
                .wait(functionTime)
                .call(function () {
                if (callBack != null) {
                    callBack();
                }
            });
        });
    };
    /**
     * 设置高亮滤镜
    */
    ActionManager.prototype.setObjFilters = function (target, oTime, tTime) {
        if (target == null || oTime < 0 || tTime < 0) {
            return;
        }
        var intervalID = setInterval(function onTick() {
            if (oTime < tTime) {
                oTime++;
            }
            else if (oTime > tTime) {
                oTime--;
            }
            var colorMatrix = [
                1, 0, 0, 0, oTime,
                0, 1, 0, 0, oTime,
                0, 0, 1, 0, oTime,
                0, 0, 0, 1, 0
            ];
            target.filters = [new egret.ColorMatrixFilter(colorMatrix)];
            if (oTime == tTime) {
                clearInterval(intervalID);
            }
        }.bind(this), 1);
    };
    /**
     * 受伤表现
    */
    ActionManager.prototype.playerObjHurtExpression = function (obj, color, chaTime, showTime, functionTime, callBack) {
        if (functionTime === void 0) { functionTime = 0; }
        if (obj != null) {
            var compon = obj.getComponent(ComponentType.Avatar);
            if (compon != null) {
                if (compon instanceof DragonComponent) {
                    if (compon.Body != null) {
                        var body = compon.Body;
                        this.playerBodyHurtExpression(body, color, chaTime, showTime, functionTime, callBack);
                    }
                }
            }
        }
    };
    /**
     * body受伤表现
    */
    ActionManager.prototype.playerBodyHurtExpression = function (target, color, chaTime, showTime, funcTime, callBack) {
        var _this = this;
        if (funcTime === void 0) { funcTime = 0; }
        if (target == null || color == null || color == "" || chaTime <= 0) {
            return;
        }
        var array = this.getRgbByColor(color);
        if (array.length = 3) {
            this.setObjHurtFilters(target, array[0], array[1], array[2], chaTime, true);
            egret.Tween.get(target)
                .wait(chaTime + showTime)
                .call(function () {
                _this.setObjHurtFilters(target, array[0], array[1], array[2], chaTime, false);
                egret.Tween.get(target)
                    .wait(chaTime + funcTime)
                    .call(function () {
                    if (callBack != null) {
                        callBack();
                    }
                });
            });
        }
    };
    ActionManager.prototype.getRgbByColor = function (color) {
        var array = new Array();
        var num = Number(color);
        var b = num % 256;
        var g = (num / 256) % 256;
        var r = (num / 256 / 256) % 256;
        array.push(r);
        array.push(g);
        array.push(b);
        return array;
    };
    /**
     * 设置受伤滤镜
    */
    ActionManager.prototype.setObjHurtFilters = function (target, rTime, gTime, bTime, ctime, increase) {
        if (increase === void 0) { increase = false; }
        if (target == null || rTime < 0 || gTime < 0 || bTime < 0 || ctime <= 0) {
            return;
        }
        var or = 0;
        var ocr = rTime / ctime;
        var og = 0;
        var ocg = gTime / ctime;
        var ob = 0;
        var ocb = bTime / ctime;
        if (increase) {
            var intervalID = setInterval(function onTick() {
                ctime--;
                or += ocr;
                og += ocg;
                ob += ocb;
                var colorMatrix = [
                    1, 0, 0, 0, or,
                    0, 1, 0, 0, og,
                    0, 0, 1, 0, ob,
                    0, 0, 0, 1, 0
                ];
                target.filters = [new egret.ColorMatrixFilter(colorMatrix)];
                if (ctime <= 0) {
                    clearInterval(intervalID);
                }
            }.bind(this), 1);
        }
        else {
            var intervalID = setInterval(function onTick() {
                ctime--;
                rTime -= ocr;
                gTime -= ocg;
                bTime -= ocb;
                var colorMatrix = [
                    1, 0, 0, 0, rTime,
                    0, 1, 0, 0, gTime,
                    0, 0, 1, 0, bTime,
                    0, 0, 0, 1, 0
                ];
                target.filters = [new egret.ColorMatrixFilter(colorMatrix)];
                if (ctime <= 0) {
                    clearInterval(intervalID);
                }
            }.bind(this), 1);
        }
    };
    return ActionManager;
}(BaseClass));
__reflect(ActionManager.prototype, "ActionManager");
//# sourceMappingURL=Actionmanager.js.map