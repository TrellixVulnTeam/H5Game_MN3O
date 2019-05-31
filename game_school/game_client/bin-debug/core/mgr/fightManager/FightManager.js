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
 * created by sjz on 2018-5-11.
 * 战斗管理
 */
var FightManager = (function (_super) {
    __extends(FightManager, _super);
    function FightManager() {
        var _this = _super.call(this) || this;
        _this.battlePoints = []; //站位
        _this.roundNum = 0; //回合数
        _this.isAutomatic = true; //是否自动战斗
        _this.isFighting = false; //是否战斗中
        _this.currentIndex = 0; //当前行动人物
        _this.passCount = 0; //使用被动技能的人数
        _this.passUseCount = 0; //使用完毕计数
        _this.createOwner = false; //己方完成
        _this.createEnemy = false; //敌方完成
        _this.enemyHpTotal = 0; //敌人总血量
        _this.playHpTotal = 0; //己方总血量
        _this.currentFightIndex = 0; //当前战斗下标
        _this.isBackstage = false; //战斗页面是否切换到后台
        _this.waitSettlement = false; //等待结算
        _this.waitActAni = false; //等待开场动画结束
        _this.index = 0;
        _this.index1 = 6;
        return _this;
    }
    /**
     * 添加站位
     */
    FightManager.prototype.AddPoint = function (point) {
        if (this.battlePoints.length <= BattleInfoConst.Admission_MAX) {
            var index = this.battlePoints.length;
            var posInfo = new BattlePosition();
            posInfo.InitPos(index, point);
            this.battlePoints.push(posInfo);
        }
    };
    /**
     * 初始化战斗信息
     */
    FightManager.prototype.InitData = function (fightId, ownerObjects, enemyObjects, gameview) {
        var _this = this;
        if (enemyObjects === void 0) { enemyObjects = null; }
        this.isFighting = true;
        this.gameView = gameview;
        this.checkPointID = fightId;
        this.ResetFight();
        App.EventMgrHelper.PushEventEx(EventDef.SwitchingFight, this.isAutomatic, null, 0, 0, "", "");
        this.currentCheckCon = CheckPointConfig.GetConfig(fightId);
        this.createplayer(ownerObjects, true, function () { return _this.CreateOwner(); });
        this.InitEnemyInfo();
        App.EventMgrHelper.PushEventEx(EventDef.FightAni, function () {
            this.waitActAni = true;
            if (this.createOwner && this.createEnemy) {
                this.FightintStart();
            }
        }.bind(this), null, 0, 0, "", "");
    };
    /**
     * 重置
     */
    FightManager.prototype.ResetFight = function () {
        if (this.allPlayers) {
            this.allPlayers.forEach(function (element) {
                element.Death();
            });
        }
        this.gameView.getGameObjcetLayer().removeChildren();
        this.ownPlayers = [];
        this.enemyPlayers = [];
        this.allPlayers = [];
        this.currentFightIndex = 0;
        this.currentIndex = 0;
        this.roundNum = 0;
        this.enemyHpTotal = 0;
        this.playHpTotal = 0;
        this.createOwner = false;
        this.createEnemy = false;
    };
    /**
     * 初始化敌人
     */
    FightManager.prototype.InitEnemyInfo = function () {
        var _this = this;
        this.enemyPlayers = [];
        if (this.currentFightIndex < this.currentCheckCon.battle.length) {
            this.currentbattleCon = BattleConfig.GetConfig(this.currentCheckCon.battle[this.currentFightIndex]);
            var enemyids = [
                this.currentbattleCon.monster1,
                this.currentbattleCon.monster2,
                this.currentbattleCon.monster3,
                this.currentbattleCon.monster4,
                this.currentbattleCon.monster5,
                this.currentbattleCon.monster6
            ];
            this.createplayer(enemyids, false, function () { return _this.CreateEnemy(); });
            this.currentFightIndex++;
        }
        App.SoundManager.playBg(this.currentbattleCon.battle_music);
    };
    /**
     * 生成人物
     */
    FightManager.prototype.createplayer = function (data, isowner, callback) {
        var executor = new FrameExecutor(1);
        if (isowner) {
            this.index = 0;
            var awardAttr_1 = 1; //默认值是1
            if (this.IsCheckPointConfigRequest(data))
                awardAttr_1 = this.currentCheckCon.awardAttr;
            data.forEach(function (id) {
                var _this = this;
                executor.regist(function () { return _this.CreateObj(id, Camp.Friendly, awardAttr_1); }, this);
            }.bind(this));
        }
        else {
            this.index1 = 6;
            data.forEach(function (id) {
                var _this = this;
                executor.regist(function () { return _this.CreateObj(id, Camp.Hostility); }, this);
            }.bind(this));
        }
        executor.execute(callback);
    };
    /**
     * 生成
     */
    FightManager.prototype.CreateObj = function (id, camp, data) {
        var player = ObjectPool.pop("MilitaryOfficerObject");
        if (camp == Camp.Friendly) {
            if (id != 0 && this.battlePoints[this.index] != null) {
                player.init(id, this.battlePoints[this.index], camp, this.gameView.getGameObjcetLayer(), data);
                this.ownPlayers.push(player);
            }
            this.index++;
        }
        else {
            if (id != 0 && this.battlePoints[this.index1] != null) {
                player.init(id, this.battlePoints[this.index1], camp, this.gameView.getGameObjcetLayer(), data);
                this.enemyPlayers.push(player);
            }
            this.index1++;
        }
    };
    /**
     * 重新排序
     */
    FightManager.prototype.SortAllPlayer = function () {
        this.allPlayers = this.ownPlayers.concat(this.enemyPlayers);
        /**行动顺序 */
        this.allPlayers.sort(function (a, b) {
            if (a.basicattr.GetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED) < b.basicattr.GetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED)) {
                return 1;
            }
            else {
                return -1;
            }
        });
    };
    /**
     * 创建己方完成
     */
    FightManager.prototype.CreateOwner = function () {
        this.createOwner = true;
        if (this.createEnemy) {
            App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, this.currentbattleCon.dialogue_front, function () {
                App.ViewManager.close(ViewConst.Dialog);
                this.GetArmorValue(this.ownPlayers);
                this.SortAllPlayer();
                if (this.waitActAni)
                    this.FightintStart();
            }.bind(this), 0, 0, "", "");
        }
    };
    /**
     * 创建敌方完成
     */
    FightManager.prototype.CreateEnemy = function () {
        this.createEnemy = true;
        if (this.createOwner) {
            App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, this.currentbattleCon.dialogue_front, function () {
                App.ViewManager.close(ViewConst.Dialog);
                this.GetArmorValue(this.enemyPlayers);
                this.SortAllPlayer();
                if (this.waitActAni)
                    this.FightintStart();
            }.bind(this), 0, 0, "", "");
        }
    };
    /**
     * 破甲临界血量比例
     */
    FightManager.prototype.GetArmorValue = function (arrs) {
        var basicArmor = parseFloat(ClientConstConfig.GetConfig(3).value);
        var armorRange = parseFloat(ClientConstConfig.GetConfig(4).value);
        arrs.forEach(function (element) {
            var armorProportion = basicArmor + (App.RandomUtils.limit(0, 1) + App.RandomUtils.limit(0, 1)) * 0.5 * armorRange;
            element.basicattr.SetCurrentValue(EStatistic.SUNDER_CRITICAL_BLOOD_PROPORTION, armorProportion);
        });
    };
    /**
     * 战斗开始
     */
    FightManager.prototype.FightintStart = function () {
        var fightInfo = this.GetFightInfo();
        App.EventMgrHelper.PushEventEx(EventDef.InitUI, fightInfo, null, 0, 0, "", "");
        this.AllPlayPassiveSkill();
    };
    /**
    * 获取战斗信息
    */
    FightManager.prototype.GetFightInfo = function () {
        var _this = this;
        this.ownPlayers.forEach(function (element) {
            _this.playHpTotal += element.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);
        });
        this.enemyPlayers.forEach(function (element) {
            _this.enemyHpTotal += element.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);
        });
        var fightInfo = [
            {
                name: "测试玩家",
                icon: "",
                blood: this.playHpTotal,
                backImage: this.currentbattleCon.battle_bg
            },
            {
                name: "初级敌人",
                icon: this.currentbattleCon.icon,
                blood: this.enemyHpTotal,
            }
        ];
        return fightInfo;
    };
    /**
     * 所有人执行被动技能
     */
    FightManager.prototype.AllPlayPassiveSkill = function () {
        var _this = this;
        if (this.allPlayers.length > 0) {
            this.allPlayers.forEach(function (element) {
                var killCom = element.getComponent(ComponentType.Skill);
                var kill = killCom.GetPassiveSkill();
                if (kill != null) {
                    _this.passCount++;
                    killCom.UseSkill(kill, element, function () { return _this.PassiveSkillCallBack(); });
                }
            });
            if (this.passCount < 1) {
                this.RoundStart();
            }
        }
    };
    /**
     * 所有被动执行结束
     */
    FightManager.prototype.PassiveSkillCallBack = function () {
        this.passUseCount++;
        if (this.passUseCount == this.passCount) {
            this.RoundStart();
        }
    };
    /**
     * 战斗结束
     */
    FightManager.prototype.FightFinish = function () {
        this.roundNum = 0;
        App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, this.currentbattleCon.dialogue_tail, function () {
            var _this = this;
            App.ViewManager.close(ViewConst.Dialog);
            if (this.victor == Camp.Friendly) {
                if (this.currentFightIndex < this.currentCheckCon.battle.length) {
                    this.enemyHpTotal = 0;
                    this.playHpTotal = 0;
                    App.EventMgrHelper.PushEventEx(EventDef.FightConvert, function () { return _this.InitEnemyInfo(); }, null, 0, 0, "", "");
                }
                else {
                    App.EventMgrHelper.PushEvent(EventDef.NextCheckPoint, this.checkPointID);
                    this.FightClearing();
                }
            }
            else {
                this.FightClearing();
            }
        }.bind(this), 0, 0, "", "");
    };
    /**
     * 战斗结算
     */
    FightManager.prototype.FightClearing = function () {
        if (!this.isBackstage) {
            App.ViewManager.open(ViewConst.BattleResult);
            this.isFighting = false;
            this.waitSettlement = false;
            this.currentFightIndex = 0;
        }
        else {
            this.waitSettlement = true;
        }
    };
    /**
     * 切换战斗动画
     */
    FightManager.prototype.SwitchCombat = function () {
        this.InitEnemyInfo();
    };
    /**
     * 开启新的回合
    */
    FightManager.prototype.RoundStart = function () {
        App.TimerManager.doTimer(500, 1, function () {
            if (this.currentbattleCon.round == -1 || this.roundNum < this.currentbattleCon.round) {
                this.roundNum++;
                App.EventMgrHelper.PushEvent(EventDef.UpdateRound, this.roundNum);
                this.RefreshSkill(); //刷新技能cd
                if (!this.IsFightFin()) {
                    this.SortAllPlayer(); //刷新完buff可能速度可能会有变化
                    // App.ActionManager.StartAction(this.allPlayers[this.currentIndex], () => this.ActionFinish());//开始行动
                    this.ActionStart();
                }
                else {
                    this.FightFinish();
                }
            }
            else {
                this.victor = Camp.Hostility; //到达限定回合数算玩家输
                this.FightFinish();
            }
        }.bind(this), this);
    };
    /**
     * 回合结束
     */
    FightManager.prototype.RoundFinish = function () {
        this.currentIndex = 0;
        this.RoundStart();
    };
    /**
     * 行动回调
     */
    FightManager.prototype.ActionStart = function () {
        var _this = this;
        App.ActionManager.StartAction(this.allPlayers[this.currentIndex], function () { return _this.ActionFinish(); });
        this.RefreshAllBuff(this.allPlayers[this.currentIndex], BuffTimeType.BuffTimeType_Begin);
    };
    /**
     * 行动结束
     */
    FightManager.prototype.ActionFinish = function () {
        if (!this.IsFightFin()) {
            this.RefreshAllBuff(this.allPlayers[this.currentIndex], BuffTimeType.BuffTimeType_End);
            this.currentIndex++;
            this.SortAllPlayer();
            if (this.currentIndex < this.allPlayers.length) {
                this.ActionStart();
            }
            else {
                this.RoundFinish();
            }
        }
        else {
            this.FightFinish();
        }
    };
    /**
     * 根据双方还存在的人数判断战斗是否结束
     */
    FightManager.prototype.IsFightFin = function () {
        if (this.ownPlayers.length < 1) {
            this.victor = Camp.Hostility;
            return true;
        }
        if (this.enemyPlayers.length < 1) {
            this.victor = Camp.Friendly;
            return true;
        }
        return false;
    };
    /**
     * 刷新buff
     */
    FightManager.prototype.RefreshAllBuff = function (obj, type) {
        if (!obj)
            return;
        this.allPlayers.forEach(function (element) {
            var buffCom = element.getComponent(ComponentType.Buff);
            if (buffCom) {
                buffCom.UpdateBuffState(type, obj.uid);
            }
        });
    };
    /**
     * 每回合之前技能cd
     */
    FightManager.prototype.RefreshSkill = function () {
        this.allPlayers.forEach(function (element) {
            var killCom = element.getComponent(ComponentType.Skill);
            killCom.UpdateSkillState();
        });
    };
    /**
     * 死亡移除
     */
    FightManager.prototype.removeplayer = function (obj, isDestory) {
        if (isDestory === void 0) { isDestory = true; }
        var index;
        if (this.allPlayers) {
            index = this.allPlayers.indexOf(obj);
            if (index != -1) {
                this.allPlayers.splice(index, 1);
            }
        }
        if (obj.camp == Camp.Friendly) {
            index = this.ownPlayers.indexOf(obj);
            if (index != -1) {
                this.ownPlayers.splice(index, 1);
            }
        }
        else {
            index = this.enemyPlayers.indexOf(obj);
            if (index != -1) {
                this.enemyPlayers.splice(index, 1);
            }
        }
        if (isDestory) {
            obj.Death();
            obj = null;
        }
    };
    /**
     * 判断角色是否还存在列表中，因为角色死亡会先从列表删除，并不会立即死亡
     * 所以判断是否死亡无效
     */
    FightManager.prototype.IsExistInAllObj = function (obj) {
        if (obj.camp == Camp.Friendly) {
            var index = this.ownPlayers.indexOf(obj);
            if (index != -1) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            var index = this.enemyPlayers.indexOf(obj);
            if (index != -1) {
                return true;
            }
            else {
                return false;
            }
        }
    };
    /**
    * 每个回合开始 初始化所有人技能CD
    * 第一个回合不调用此函数，之后每个回合开始前都会调用一次，更改技能状态
    * 目前需要更改的为技能CD,以后或许还有更多状态都通过此函数去更新
    */
    FightManager.prototype.ChangeSkillCDState = function () {
        this.allPlayers.forEach(function (data) {
            var compon = data.getComponent(ComponentType.Skill);
            if (compon) {
                compon.UpdateSkillState();
            }
        });
    };
    /**
     * 可以使用连携技的Players
     */
    FightManager.prototype.CanUseLinkingSkillPlayer = function (obj) {
        this.SortAllPlayer();
        var players = [];
        if (obj) {
            for (var i = 0; i < this.allPlayers.length; i++) {
                if (this.allPlayers[i].camp == obj.camp && this.allPlayers[i] != obj) {
                    players.push(this.allPlayers[i]);
                }
            }
            var players_havelinking = [];
            for (var i = 0; i < players.length; i++) {
                var buffCom = players[i].getComponent(ComponentType.Buff);
                if (buffCom && !buffCom.IsDizziness() && !buffCom.IsSilence()) {
                    var skill = players[i].getComponent(ComponentType.Skill).GetSkill(SkillType.LinkingSkill);
                    if (skill && !skill.InCD) {
                        var linkingPro = players[i].basicattr.GetCurrentValue(EStatistic.STATISTIC_LINKING_SKILLS_PROBABILITY) * 100;
                        if (this.CanTiggerLinkingSkill(0, 100, linkingPro)) {
                            players_havelinking.push(players[i]);
                        }
                    }
                }
            }
            players_havelinking.sort(function (a, b) {
                var a_skill = a.getComponent(ComponentType.Skill).GetSkill(SkillType.LinkingSkill);
                var b_skill = b.getComponent(ComponentType.Skill).GetSkill(SkillType.LinkingSkill);
                if (a_skill.MagicConfig.comboSkillPriority > b_skill.MagicConfig.comboSkillPriority) {
                    return 1;
                }
                else {
                    return -1;
                }
            });
            return players_havelinking;
        }
        else {
            return players;
        }
    };
    /**
     * 是否可以使用连携技
     */
    FightManager.prototype.CanTiggerLinkingSkill = function (min, max, probability) {
        if (probability <= 0)
            return false;
        var random = App.RandomUtils.limitInteger(min, max);
        if (random <= probability) {
            return true;
        }
        return false;
    };
    /**
     * 根据id获取英雄
     */
    FightManager.prototype.GetPlayerByUId = function (uid) {
        for (var i = 0; i < this.allPlayers.length; i++) {
            if (this.allPlayers[i].uid == uid) {
                return this.allPlayers[i];
            }
        }
        return null;
    };
    /**
     * 根据阵营返回总血量
     */
    FightManager.prototype.GetCampTotalBlood = function (camp, offset) {
        if (offset === void 0) { offset = 0; }
        if (camp == Camp.Friendly) {
            this.PlayHpTotal += offset;
            return this.PlayHpTotal;
        }
        else {
            this.EnemyHpTotal += offset;
            return this.EnemyHpTotal;
        }
    };
    Object.defineProperty(FightManager.prototype, "RoundNum", {
        get: function () {
            return this.roundNum;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "AllPlayers", {
        get: function () {
            return this.allPlayers;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "OwnerPlayers", {
        get: function () {
            return this.ownPlayers;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "EnemyPlayers", {
        get: function () {
            return this.enemyPlayers;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "IsFightFinish", {
        get: function () {
            return this.isFighting;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "IsAutomatic", {
        get: function () {
            return this.isAutomatic;
        },
        set: function (value) {
            this.isAutomatic = value;
            if (App.ActionManager.WaitAuto) {
                App.ActionManager.DiversionAction();
            }
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "EnemyHpTotal", {
        get: function () {
            return this.enemyHpTotal;
        },
        set: function (value) {
            this.enemyHpTotal = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "PlayHpTotal", {
        get: function () {
            return this.playHpTotal;
        },
        set: function (value) {
            this.playHpTotal = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "CheckPointID", {
        get: function () {
            return this.checkPointID;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "IsBackstage", {
        get: function () {
            return this.isBackstage;
        },
        set: function (value) {
            this.isBackstage = value;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FightManager.prototype, "WaitSettlement", {
        get: function () {
            return this.waitSettlement;
        },
        enumerable: true,
        configurable: true
    });
    FightManager.prototype.GetBattlePoints = function (index) {
        return this.battlePoints[index].Pos;
    };
    /**
    * 所有人物移动
    */
    FightManager.prototype.AllPlayMove = function (objs, callback) {
        var _this = this;
        if (objs.length > 0) {
            var moveCount_1 = 0;
            objs.forEach(function (element) {
                var moveCom = element.getComponent(ComponentType.Move);
                moveCom.DoMove(element.posInfo.Pos, function () {
                    moveCount_1++;
                    element.getComponent(ComponentType.Dragon).PlayAct(Action.Stand);
                    if (moveCount_1 == objs.length) {
                        callback();
                    }
                }.bind(_this), 2000);
            });
        }
    };
    FightManager.prototype.IsCheckPointConfigRequest = function (data) {
        var result = true; //默认满足条件
        var requestArray = this.currentCheckCon.request; //目前的条件,条件是且的关系,需要全部满足才会有属性加成
        for (var i = 0; i < requestArray.length; i++) {
            var con = CheckPointRequestConfig.GetConfig(requestArray[i]);
            if (con == null)
                return false;
            var isBool = this.IsRequest(data, con); //本次是不是满足条件
            if (!isBool)
                return false;
        }
        return result;
    };
    FightManager.prototype.IsRequest = function (data, con) {
        var index = con.number; //要求数量
        var value = con.para2; //只有属性达标有这个参数需求
        var ix = 0; //下面计数用          
        switch (con.type) {
            case 1://玩家主属性达标
                data.forEach(function (id) {
                    var creatureTempletConf = CreatureTempletConfig.GetConfig(id);
                    if (this.IsAttr(creatureTempletConf, con.para1, value))
                        ix++;
                }.bind(this));
                if (ix >= index) {
                    return true;
                }
                break;
            case 2://角色主属性
                data.forEach(function (id) {
                    var creatureTempletConf = CreatureTempletConfig.GetConfig(id);
                    if (creatureTempletConf.mainAttr == con.para1)
                        ix++;
                }.bind(this));
                if (ix >= index) {
                    return true;
                }
                break;
            case 3://角色社团                             
                data.forEach(function (id) {
                    var creatureTempletConf = CreatureTempletConfig.GetConfig(id);
                    if (creatureTempletConf.association == con.para1)
                        ix++;
                }.bind(this));
                if (ix >= index) {
                    return true;
                }
                break;
            case 4://指定角色                  
                data.forEach(function (id) {
                    if (id == con.para1)
                        ix++;
                }.bind(this));
                if (ix >= index) {
                    return true;
                }
                break;
            case 5://角色性格
                data.forEach(function (id) {
                    var creatureTempletConf = CreatureTempletConfig.GetConfig(id);
                    var index = creatureTempletConf.label.indexOf(con.para1); //判断是不是包含这个性格需求
                    if (index >= 0) {
                        ix++;
                    }
                }.bind(this));
                if (ix >= index) {
                    return true;
                }
                break;
        }
        return false;
    };
    /**
    * 是否满足属性要求,这函数写的太蛋疼,只能单独抽出来写
    */
    FightManager.prototype.IsAttr = function (con, para1, value) {
        if (!con)
            return;
        var result = false;
        switch (para1) {
            case EStatistic.STATISTIC_VITALITY:
                break;
            case EStatistic.STATISTIC_INTELLECT:
                break;
            case EStatistic.STATISTIC_STRENGTH:
                break;
            case EStatistic.STATISTIC_AGILITY:
                break;
            case EStatistic.STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER4:
                break;
            case EStatistic.STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER5:
                break;
            case EStatistic.STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER6:
                break;
            case EStatistic.STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER7:
                break;
            case EStatistic.STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER8:
                break;
            case EStatistic.STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER9:
                break;
            case EStatistic.STATISTIC_LIFE:
                if (con.life >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_MANA:
                break;
            case EStatistic.STATISTIC_DAMAGE:
                if (con.damage >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_PHYSICAL_DEFENCE:
                if (con.physical_defence >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_SPELL_DEFENCE:
                if (con.spell_defence >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_DAMAGE_REDUCTION:
                if (con.damage_reduction >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_DEEPER_DAMAGE:
                if (con.deeper_damage >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_DAMAGE_FORMULA_6:
                break;
            case EStatistic.STATISTIC_DAMAGE_FORMULA_7:
                break;
            case EStatistic.STATISTIC_DAMAGE_FORMULA_8:
                break;
            case EStatistic.STATISTIC_DAMAGE_FORMULA_9:
                break;
            case EStatistic.STATISTIC_SHOT_SPEED:
                if (con.shot_speed >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_CRIT_AMOUNT:
                if (con.crit_amount >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_TOUGHNESS_AMOUNT:
                if (con.toughness_amout >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_CRIT_CHANCE:
                if (con.crit_chance >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_TOUGHNESS_CHANCE:
                if (con.toughness_chance >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_CRIT_DAMAGE:
                if (con.crit_damage >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT:
                if (con.crit_reduced_amount >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_TREATMENT_EFFECT:
                if (con.treatment_effect >= value)
                    result = true;
                break;
            case EStatistic.STATISTIC_LINKING_SKILLS_PROBABILITY:
                if (con.linking_skills_probability >= value)
                    result = true;
                break;
            case EStatistic.SUNDER_CRITICAL_BLOOD_PROPORTION:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_30:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_31:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_32:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_33:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_34:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_35:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_36:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_37:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_38:
                break;
            case EStatistic.STATISTIC_FIGHT_FORMULA_39:
                break;
            case EStatistic.STATISTIC_MAX:
                break;
            default:
                return result;
        }
        return result;
    };
    /**
   * 血量变化
   * @param gameObj
   * @param changeHp
   * @param txtColor
  */
    FightManager.prototype.showHpChange = function (gameObj, changeHp, type, crit, txtColor) {
        if (txtColor === void 0) { txtColor = 0xFF0000; }
        var hpTxt = ObjectPool.pop("egret.TextField");
        changeHp = Math.floor(changeHp);
        hpTxt.size = crit ? 50 : 35;
        hpTxt.textColor = crit ? ColorConst.Yellow_Light : HurtType.Gain == type ? ColorConst.Green_Light : ColorConst.Red_Light;
        hpTxt.width = crit ? 150 : 100;
        hpTxt.height = crit ? 30 : 20;
        hpTxt.textAlign = egret.HorizontalAlign.CENTER;
        hpTxt.strokeColor = 0xF8F8FF;
        hpTxt.stroke = 2;
        hpTxt.text = changeHp.toString();
        hpTxt.x = gameObj.position.x;
        hpTxt.y = gameObj.position.y - 150;
        hpTxt.alpha = 1;
        AnchorUtil.setAnchorX(hpTxt, 0.5);
        this.gameView.getGameEffectLayer().addChild(hpTxt);
        egret.Tween.get(hpTxt).to({ "y": gameObj.position.y - 250, "alpha": 0 }, 1000).call(function () {
            App.DisplayUtils.removeFromParent(hpTxt);
            ObjectPool.push(hpTxt);
        });
    };
    return FightManager;
}(BaseClass));
__reflect(FightManager.prototype, "FightManager");
//# sourceMappingURL=FightManager.js.map