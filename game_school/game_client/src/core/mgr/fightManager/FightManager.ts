/**
 * created by sjz on 2018-5-11.
 * 战斗管理
 */
class FightManager extends BaseClass {
    private checkPointID: number;//当前章节id
    private gameView: CCG_FightGameView;//战斗场景

    private battlePoints: BattlePosition[] = [];//站位
    private roundNum: number = 0;//回合数

    private isAutomatic: boolean = true;//是否自动战斗
    private isFighting: boolean = false;  //是否战斗中

    private currentIndex: number = 0;//当前行动人物
    private victor: Camp;//胜利者

    private passCount: number = 0;//使用被动技能的人数
    private passUseCount: number = 0;//使用完毕计数

    private createOwner: boolean = false;//己方完成
    private createEnemy: boolean = false;//敌方完成

    private ownPlayers: MilitaryOfficerObject[];  //己方上阵人员
    private enemyPlayers: MilitaryOfficerObject[];//敌方上阵人员
    private allPlayers: MilitaryOfficerObject[];  //场上所有人

    private enemyHpTotal: number = 0;//敌人总血量
    private playHpTotal: number = 0;//己方总血量

    private currentbattleCon: BattleConfig;//当前战斗表格
    private currentCheckCon: CheckPointConfig;//当前章节表
    private currentFightIndex: number = 0;//当前战斗下标

    private isBackstage: boolean = false;//战斗页面是否切换到后台
    private waitSettlement: boolean = false;//等待结算
    private waitActAni: boolean = false;//等待开场动画结束

    private index: number = 0;
    private index1: number = 6;

    public constructor() {
        super();
    }

    /**
     * 添加站位
     */
    public AddPoint(point: egret.Point) {
        if (this.battlePoints.length <= BattleInfoConst.Admission_MAX) {
            var index = this.battlePoints.length;
            var posInfo: BattlePosition = new BattlePosition();
            posInfo.InitPos(index, point);
            this.battlePoints.push(posInfo);
        }
    }

    /**
     * 初始化战斗信息
     */
    public InitData(fightId: number, ownerObjects: any[], enemyObjects: any[] = null, gameview: CCG_FightGameView) {
        this.isFighting = true;
        this.gameView = gameview;
        this.checkPointID = fightId;
        this.ResetFight();
        App.EventMgrHelper.PushEventEx(EventDef.SwitchingFight,this.isAutomatic,null,0,0,"","");
        this.currentCheckCon = CheckPointConfig.GetConfig(fightId);
        this.createplayer(ownerObjects, true, () => this.CreateOwner());
        this.InitEnemyInfo();
        App.EventMgrHelper.PushEventEx(EventDef.FightAni,function () {
            this.waitActAni = true;
            if (this.createOwner && this.createEnemy) {
                this.FightintStart();
            }
        }.bind(this),null,0,0,"","");

    }

    /**
     * 重置
     */
    public ResetFight() {
        if (this.allPlayers) {
            this.allPlayers.forEach(element => {
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
    }

    /**
     * 初始化敌人
     */
    public InitEnemyInfo() {
        this.enemyPlayers = [];
        if (this.currentFightIndex < this.currentCheckCon.battle.length) {
            this.currentbattleCon = BattleConfig.GetConfig(this.currentCheckCon.battle[this.currentFightIndex]);
            let enemyids: number[] = [
                this.currentbattleCon.monster1,
                this.currentbattleCon.monster2,
                this.currentbattleCon.monster3,
                this.currentbattleCon.monster4,
                this.currentbattleCon.monster5,
                this.currentbattleCon.monster6];
            this.createplayer(enemyids, false, () => this.CreateEnemy());
            this.currentFightIndex++;
        }
        App.SoundManager.playBg(this.currentbattleCon.battle_music);
    }

    /**
     * 生成人物
     */
    public createplayer(data: any, isowner: boolean, callback?: Function): void {
        let executor: FrameExecutor = new FrameExecutor(1);
        if (isowner) {
            this.index = 0;
            let awardAttr = 1;  //默认值是1
            if (this.IsCheckPointConfigRequest(data))
                awardAttr = this.currentCheckCon.awardAttr;
            data.forEach(function (id) {
                executor.regist(() => this.CreateObj(id, Camp.Friendly, awardAttr), this);
            }.bind(this));
        }
        else {
            this.index1 = 6;
            data.forEach(function (id) {
                executor.regist(() => this.CreateObj(id, Camp.Hostility), this);
            }.bind(this));
        }
        executor.execute(callback);
    }

    /**
     * 生成
     */
    public CreateObj(id: number, camp: Camp, data?: any) {
        let player: MilitaryOfficerObject = ObjectPool.pop("MilitaryOfficerObject");
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
    }

    /**
     * 重新排序
     */
    public SortAllPlayer() {
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
    }

    /**
     * 创建己方完成
     */
    public CreateOwner() {
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
    }

    /**
     * 创建敌方完成
     */
    public CreateEnemy() {
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
    }

    /**
     * 破甲临界血量比例
     */
    public GetArmorValue(arrs: MilitaryOfficerObject[]) {
        let basicArmor: number = parseFloat(ClientConstConfig.GetConfig(3).value);
        let armorRange: number = parseFloat(ClientConstConfig.GetConfig(4).value);
        arrs.forEach(element => {
            let armorProportion = basicArmor + (App.RandomUtils.limit(0, 1) + App.RandomUtils.limit(0, 1)) * 0.5 * armorRange;
            element.basicattr.SetCurrentValue(EStatistic.SUNDER_CRITICAL_BLOOD_PROPORTION, armorProportion);
        });
    }

    /**
     * 战斗开始
     */
    public FightintStart(): void {
        let fightInfo = this.GetFightInfo();
        App.EventMgrHelper.PushEventEx(EventDef.InitUI,fightInfo,null,0,0,"","");
        this.AllPlayPassiveSkill();
    }

    /**
    * 获取战斗信息
    */
    public GetFightInfo(): any[] {
        this.ownPlayers.forEach(element => {
            this.playHpTotal += element.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);
        });
        this.enemyPlayers.forEach(element => {
            this.enemyHpTotal += element.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);
        });

        let fightInfo: any[] = [
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
    }

    /**
     * 所有人执行被动技能
     */
    public AllPlayPassiveSkill() {
        if (this.allPlayers.length > 0) {
            this.allPlayers.forEach(element => {
                let killCom: SkillComponent = <SkillComponent>element.getComponent(ComponentType.Skill);
                let kill: Skill = killCom.GetPassiveSkill();
                if (kill != null) {
                    this.passCount++;
                    killCom.UseSkill(kill, element, () => this.PassiveSkillCallBack());
                }
            });

            if (this.passCount < 1) {
                this.RoundStart();
            }
        }
    }

    /**
     * 所有被动执行结束
     */
    public PassiveSkillCallBack() {
        this.passUseCount++;
        if (this.passUseCount == this.passCount) {
            this.RoundStart();
        }
    }

    /**
     * 战斗结束
     */
    public FightFinish() {
        this.roundNum = 0;
        App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, this.currentbattleCon.dialogue_tail, function () {
            App.ViewManager.close(ViewConst.Dialog);
            if (this.victor == Camp.Friendly) {
                if (this.currentFightIndex < this.currentCheckCon.battle.length) {
                    this.enemyHpTotal = 0;
                    this.playHpTotal = 0;
                    App.EventMgrHelper.PushEventEx(EventDef.FightConvert, () => this.InitEnemyInfo(),null,0,0,"","");
                } else {
                    App.EventMgrHelper.PushEvent(EventDef.NextCheckPoint, this.checkPointID);
                   
                    this.FightClearing();
                }
            } else {
                this.FightClearing();
            }
        }.bind(this), 0, 0, "", "");
       
    }

    /**
     * 战斗结算
     */
    public FightClearing() {
        if (!this.isBackstage) {
            App.ViewManager.open(ViewConst.BattleResult);
            this.isFighting = false;
            this.waitSettlement = false;
            this.currentFightIndex = 0;
        } else {
            this.waitSettlement = true;
        }
    }

    /**
     * 切换战斗动画
     */
    public SwitchCombat() {
        this.InitEnemyInfo();
    }

    /** 
     * 开启新的回合
    */
    public RoundStart(): void {

        App.TimerManager.doTimer(500, 1, function () {
            if (this.currentbattleCon.round == -1 || this.roundNum < this.currentbattleCon.round) {//是否限制回合数 
                this.roundNum++;
                App.EventMgrHelper.PushEvent(EventDef.UpdateRound,this.roundNum);
                this.RefreshSkill();//刷新技能cd

                if (!this.IsFightFin()) {//刷新完buff有可能会有死亡

                    this.SortAllPlayer(); //刷新完buff可能速度可能会有变化

                    // App.ActionManager.StartAction(this.allPlayers[this.currentIndex], () => this.ActionFinish());//开始行动
                    this.ActionStart();
                } else {
                    this.FightFinish();
                }
            } else {
                this.victor = Camp.Hostility;//到达限定回合数算玩家输
                this.FightFinish();
            }
        }.bind(this), this);
    }

    /**
     * 回合结束
     */
    public RoundFinish() {
        this.currentIndex = 0;
        this.RoundStart();
    }

    /**
     * 行动回调
     */
    public ActionStart() {
        App.ActionManager.StartAction(this.allPlayers[this.currentIndex], () => this.ActionFinish());
        this.RefreshAllBuff(this.allPlayers[this.currentIndex], BuffTimeType.BuffTimeType_Begin);
    }

    /**
     * 行动结束
     */
    public ActionFinish() {
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
        } else {
            this.FightFinish();
        }
    }

    /**
     * 根据双方还存在的人数判断战斗是否结束
     */
    public IsFightFin(): boolean {
        if (this.ownPlayers.length < 1) {
            this.victor = Camp.Hostility;
            return true;
        }
        if (this.enemyPlayers.length < 1) {
            this.victor = Camp.Friendly;
            return true;
        }
        return false;
    }

    /**
     * 刷新buff
     */
    public RefreshAllBuff(obj: MilitaryOfficerObject, type: BuffTimeType) {
        if (!obj)
            return;
        this.allPlayers.forEach(element => {
            let buffCom: BuffComponent = <BuffComponent>element.getComponent(ComponentType.Buff);
            if (buffCom) {
                buffCom.UpdateBuffState(type, obj.uid);
            }
        });
    }

    /**
     * 每回合之前技能cd
     */
    public RefreshSkill() {
        this.allPlayers.forEach(element => {
            let killCom: SkillComponent = <SkillComponent>element.getComponent(ComponentType.Skill);
            killCom.UpdateSkillState();
        });
    }

    /**
     * 死亡移除
     */
    public removeplayer(obj: MilitaryOfficerObject, isDestory: boolean = true): void {
        let index: number;
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
    }

    /**
     * 判断角色是否还存在列表中，因为角色死亡会先从列表删除，并不会立即死亡
     * 所以判断是否死亡无效
     */
    public IsExistInAllObj(obj: MilitaryOfficerObject): boolean {
        if (obj.camp == Camp.Friendly) {
            let index: number = this.ownPlayers.indexOf(obj);
            if (index != -1) {
                return true;
            } else {
                return false;
            }
        }
        else {
            let index: number = this.enemyPlayers.indexOf(obj);
            if (index != -1) {
                return true;
            } else {
                return false;
            }
        }
    }

    /**
    * 每个回合开始 初始化所有人技能CD
    * 第一个回合不调用此函数，之后每个回合开始前都会调用一次，更改技能状态
    * 目前需要更改的为技能CD,以后或许还有更多状态都通过此函数去更新
    */
    public ChangeSkillCDState(): void {
        this.allPlayers.forEach(function (data: MilitaryOfficerObject) {
            let compon: SkillComponent = <SkillComponent>data.getComponent(ComponentType.Skill);
            if (compon) {
                compon.UpdateSkillState();
            }
        })
    }

    /**
     * 可以使用连携技的Players
     */
    public CanUseLinkingSkillPlayer(obj: MilitaryOfficerObject): MilitaryOfficerObject[] {
        this.SortAllPlayer();
        let players: MilitaryOfficerObject[] = [];
        if (obj) {
            for (let i = 0; i < this.allPlayers.length; i++) {
                if (this.allPlayers[i].camp == obj.camp && this.allPlayers[i] != obj) {
                    players.push(this.allPlayers[i]);
                }
            }

            let players_havelinking: MilitaryOfficerObject[] = [];
            for (let i = 0; i < players.length; i++) {
                let buffCom: BuffComponent = <BuffComponent>players[i].getComponent(ComponentType.Buff);
                if (buffCom && !buffCom.IsDizziness() && !buffCom.IsSilence()) {
                    let skill: Skill = (<SkillComponent>players[i].getComponent(ComponentType.Skill)).GetSkill(SkillType.LinkingSkill);
                    if (skill && !skill.InCD) {
                        let linkingPro: number = players[i].basicattr.GetCurrentValue(EStatistic.STATISTIC_LINKING_SKILLS_PROBABILITY) * 100;
                        if (this.CanTiggerLinkingSkill(0, 100, linkingPro)) {
                            players_havelinking.push(players[i]);
                        }
                    }
                }
            }

            players_havelinking.sort(function (a, b) {
                let a_skill: Skill = (<SkillComponent>a.getComponent(ComponentType.Skill)).GetSkill(SkillType.LinkingSkill);
                let b_skill: Skill = (<SkillComponent>b.getComponent(ComponentType.Skill)).GetSkill(SkillType.LinkingSkill);
                if (a_skill.MagicConfig.comboSkillPriority > b_skill.MagicConfig.comboSkillPriority) {
                    return 1;
                } else {
                    return -1;
                }
            });
            return players_havelinking;

        } else {
            return players;
        }

    }

    /**
     * 是否可以使用连携技
     */
    public CanTiggerLinkingSkill(min, max, probability): boolean {
        if (probability <= 0) return false;
        let random: number = App.RandomUtils.limitInteger(min, max);
        if (random <= probability) {
            return true;
        }
        return false;
    }

    /**
     * 根据id获取英雄
     */
    public GetPlayerByUId(uid: string) {
        for (let i = 0; i < this.allPlayers.length; i++) {
            if (this.allPlayers[i].uid == uid) {
                return this.allPlayers[i];
            }
        }
        return null;
    }

    /**
     * 根据阵营返回总血量
     */
    public GetCampTotalBlood(camp: Camp, offset: number = 0): number {
        if (camp == Camp.Friendly) {
            this.PlayHpTotal += offset;
            return this.PlayHpTotal;
        } else {
            this.EnemyHpTotal += offset;
            return this.EnemyHpTotal;
        }
    }

    public get RoundNum() {
        return this.roundNum;
    }

    public get AllPlayers() {
        return this.allPlayers;
    }

    public get OwnerPlayers() {
        return this.ownPlayers;
    }
    public get EnemyPlayers() {
        return this.enemyPlayers;
    }
    public get IsFightFinish() {
        return this.isFighting;
    }
    public get IsAutomatic() {
        return this.isAutomatic;
    }
    public get EnemyHpTotal() {
        return this.enemyHpTotal;
    }
    public set EnemyHpTotal(value: number) {
        this.enemyHpTotal = value;
    }
    public get PlayHpTotal() {
        return this.playHpTotal;
    }
    public set PlayHpTotal(value: number) {
        this.playHpTotal = value;
    }
    public get CheckPointID() {
        return this.checkPointID;
    }
    public get IsBackstage() {
        return this.isBackstage;
    }
    public set IsBackstage(value: boolean) {
        this.isBackstage = value;
    }
    public get WaitSettlement() {
        return this.waitSettlement;
    }

    public set IsAutomatic(value: boolean) {
        this.isAutomatic = value;
        if (App.ActionManager.WaitAuto) {
            App.ActionManager.DiversionAction();
        }
    }

    public GetBattlePoints(index: number): egret.Point {
        return this.battlePoints[index].Pos;
    }

    /**
    * 所有人物移动
    */
    public AllPlayMove(objs: MilitaryOfficerObject[], callback: Function): void {
        if (objs.length > 0) {
            let moveCount: number = 0;
            objs.forEach(element => {
                let moveCom: MoveComponent = <MoveComponent>element.getComponent(ComponentType.Move);
                moveCom.DoMove(element.posInfo.Pos, function () {
                    moveCount++;
                    (<DragonComponent>element.getComponent(ComponentType.Dragon)).PlayAct(Action.Stand);
                    if (moveCount == objs.length) {
                        callback();
                    }
                }.bind(this), 2000);
            });
        }
    }

    public IsCheckPointConfigRequest(data: any): boolean {
        let result: boolean = true; //默认满足条件
        let requestArray: number[] = this.currentCheckCon.request; //目前的条件,条件是且的关系,需要全部满足才会有属性加成

        for (let i = 0; i < requestArray.length; i++) {
            let con: CheckPointRequestConfig = CheckPointRequestConfig.GetConfig(requestArray[i]);
            if (con == null) //数据出错了,直接返回false          
                return false;
            let isBool: boolean = this.IsRequest(data, con); //本次是不是满足条件
            if (!isBool) //有一个不满足条件,就直接false了,都满足会返回默认的resule
                return false;
        }
        return result;
    }

    public IsRequest(data: any, con: CheckPointRequestConfig): boolean {
        let index: number = con.number; //要求数量
        let value: number = con.para2;  //只有属性达标有这个参数需求
        let ix = 0; //下面计数用          
        switch (con.type) {
            case 1: //玩家主属性达标
                data.forEach(function (id) {
                    let creatureTempletConf = CreatureTempletConfig.GetConfig(id);
                    if (this.IsAttr(creatureTempletConf, con.para1, value))
                        ix++;
                }.bind(this));
                if (ix >= index) {
                    return true;
                }
                break;
            case 2://角色主属性
                data.forEach(function (id) {
                    let creatureTempletConf = CreatureTempletConfig.GetConfig(id);
                    if (creatureTempletConf.mainAttr == con.para1)
                        ix++;
                }.bind(this));
                if (ix >= index) {
                    return true;
                }
                break;
            case 3://角色社团                             
                data.forEach(function (id) {
                    let creatureTempletConf = CreatureTempletConfig.GetConfig(id);
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
                    let creatureTempletConf = CreatureTempletConfig.GetConfig(id);
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
    }

    /**
    * 是否满足属性要求,这函数写的太蛋疼,只能单独抽出来写
    */
    private IsAttr(con: CreatureTempletConfig, para1: number, value: number): boolean {
        if (!con) return;
        let result: boolean = false;
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
    }

    /**
   * 血量变化
   * @param gameObj 
   * @param changeHp
   * @param txtColor
  */
    public showHpChange(gameObj: MilitaryOfficerObject, changeHp: number, type: HurtType, crit?: boolean, txtColor: number = 0xFF0000): void {

        let hpTxt: egret.TextField = ObjectPool.pop("egret.TextField");
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
        })
    }



}

