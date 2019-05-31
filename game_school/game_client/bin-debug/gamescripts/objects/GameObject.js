var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * 阵营
 */
var Camp;
(function (Camp) {
    /**友好 */
    Camp[Camp["Friendly"] = 0] = "Friendly";
    /**中立 */
    Camp[Camp["Neutral"] = 1] = "Neutral";
    /**敌对 */
    Camp[Camp["Hostility"] = 2] = "Hostility";
})(Camp || (Camp = {}));
var ClientBits;
(function (ClientBits) {
    ClientBits[ClientBits["CLIENT_BIT_DEAD"] = 0] = "CLIENT_BIT_DEAD";
    ClientBits[ClientBits["CLIENT_BIT_MOVING"] = 1] = "CLIENT_BIT_MOVING";
    ClientBits[ClientBits["CLIENT_BIT_CASTING"] = 2] = "CLIENT_BIT_CASTING";
    ClientBits[ClientBits["CLIENT_BIT_SKILL_ACTIVATE"] = 3] = "CLIENT_BIT_SKILL_ACTIVATE";
    ClientBits[ClientBits["CLIENT_BIT_CANNOT_MOVE"] = 4] = "CLIENT_BIT_CANNOT_MOVE";
    ClientBits[ClientBits["CLIENT_BIT_SLIENT"] = 5] = "CLIENT_BIT_SLIENT";
    ClientBits[ClientBits["CLIENT_BIT_TALKING"] = 6] = "CLIENT_BIT_TALKING";
    ClientBits[ClientBits["CLIENT_BIT_COMBAT"] = 7] = "CLIENT_BIT_COMBAT";
    ClientBits[ClientBits["CLIENT_BIT_PLOT_CANNOTMOVE"] = 8] = "CLIENT_BIT_PLOT_CANNOTMOVE";
})(ClientBits || (ClientBits = {}));
/**
 * created by sjz 2018-5-9.
 * 模型基类
 */
var GameObject = (function () {
    function GameObject() {
        /**世界坐标 */
        this.position = new egret.Point();
        /** 初始化世界坐标 用于移动之后走回来 这个坐标初始化之后就不在改变 初始化请用下面的 initPosition*/
        this.startPosition = new egret.Point();
        this.mClientBit = new MyBitset(32);
        this._components = {};
    }
    Object.defineProperty(GameObject.prototype, "StartPosition", {
        get: function () {
            return this.startPosition;
        },
        enumerable: true,
        configurable: true
    });
    GameObject.prototype.init = function (id, posinfo, camp, gameView, data) {
        this.uid = App.MathUtils.uuid(10, 16);
        this.basicattr = new CreatureStatistics();
        /*
          CreatureSpawnConfig表通过这个ID来获取,CreatureTempletConfig 表要用CreatureSpawnConfig 里面的templet字段来获取
          CreatureTempletConfig 表里的数据现在已经是属于一种模板数据了,实际的最终数据,要通过CreatureSpawnConfig表来计算一次
          实际的数据处理,在下面初始化数据的时候真正处理,需要依赖的两张表是  CreatureAttrForceConfig(强制数据表) 和 CreatureAttrTypeConfig
        */
        if (camp == Camp.Friendly) {
            this.modelId = id;
            this.creatureConf = CreatureTempletConfig.GetConfig(id);
        }
        else if (camp == Camp.Hostility) {
            this.creatureSpawnConf = CreatureSpawnConfig.GetConfig(id);
            this.modelId = this.creatureSpawnConf.templet;
            this.creatureConf = CreatureTempletConfig.GetConfig(this.creatureSpawnConf.templet);
        }
        this.modelConf = ModelConfig.GetConfig(this.creatureConf.model);
        this.avatarPath = GameobjConst.McPath;
        this.avatarName = this.modelConf.filename;
        this.oriScale = this.modelConf.size;
        this.skilleffpath = GameobjConst.SkillEffectFilePath;
        this.skillName = GameobjConst.SkillName;
        this.buffeffpath = GameobjConst.Buffeffpath;
        this.buffName = GameobjConst.BuffName;
        this.gameView = gameView;
        this.action = Action.Stand;
        this.camp = camp;
        if (camp == Camp.Friendly)
            this.dir = Dir.Left;
        else
            this.dir = Dir.Right;
        this.posInfo = posinfo;
        this.initPosition();
        if (camp == Camp.Friendly) {
            //目前data是己方数据的增幅比例
            this.InitOwnBasicattr(data); //己方的数据独立处理
        }
        else if (camp == Camp.Hostility) {
            this.InitEnemyBasicattr();
        }
    };
    /**事件监听 */
    GameObject.prototype.RegisEventListener = function (eventType, event) {
        var avater = this.getComponent(ComponentType.Avatar);
        if (avater) {
            avater.AvatarMovieClip.RegisEventListener(eventType, event);
        }
    };
    /**删除事件监听 */
    GameObject.prototype.RemoveEventListener = function (eventType, event) {
        var avater = this.getComponent(ComponentType.Avatar);
        if (avater) {
            avater.AvatarMovieClip.RemoveEventListener(eventType, event);
        }
    };
    /**修改父物体 */
    GameObject.prototype.ChangeParent = function (view) {
        var avater = this.getComponent(ComponentType.Avatar);
        if (avater) {
            avater.AvatarMovieClip.ChangeParent(view);
        }
    };
    /**删除所有事件监听 */
    GameObject.prototype.RemoveAllEventListener = function () {
        var avater = this.getComponent(ComponentType.Avatar);
        if (avater) {
            avater.AvatarMovieClip.RemoveAllEventListener();
        }
    };
    GameObject.prototype.initPosition = function () {
        this.position.x = this.posInfo.Pos.x;
        this.position.y = this.posInfo.Pos.y;
        this.startPosition.x = this.posInfo.Pos.x;
        this.startPosition.y = this.posInfo.Pos.y;
        this.colnum = this.posInfo.SelfArrAnger;
        this.rownum = this.posInfo.LineNum;
    };
    GameObject.prototype.InitOwnBasicattr = function (awardAttr) {
        if (awardAttr === void 0) { awardAttr = 1; }
        this.basicattr.Name = this.creatureConf.name;
        this.basicattr.Title = "[111]";
        //有六个属性可能有加成,其中,速度不享受加成,目前是这样的  
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE, this.GetValue(this.creatureConf.life, awardAttr));
        this.basicattr.OriHp = this.creatureConf.life;
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_DAMAGE, this.GetValue(this.creatureConf.damage, awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_PHYSICAL_DEFENCE, this.GetValue(this.creatureConf.physical_defence, awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SPELL_DEFENCE, this.GetValue(this.creatureConf.spell_defence, awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_AMOUNT, this.GetValue(this.creatureConf.crit_amount, awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_AMOUNT, this.GetValue(this.creatureConf.toughness_amout, awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED, this.creatureConf.shot_speed);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_CHANCE, this.creatureConf.crit_chance);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_CHANCE, this.creatureConf.toughness_chance);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_DAMAGE, this.creatureConf.crit_damage);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT, this.creatureConf.crit_reduced_amount);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT, this.creatureConf.treatment_effect);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LINKING_SKILLS_PROBABILITY, this.creatureConf.linking_skills_probability);
    };
    GameObject.prototype.InitEnemyBasicattr = function () {
        this.basicattr.Name = this.creatureConf.name;
        this.basicattr.Title = "[111]";
        /*
        attrMethod =1 使用CreatureAttrTypeConfig表
        attrMethod =/ CreatureAttrForceConfig(强制数据表)
        */
        if (this.creatureSpawnConf.attrMethod == 1) {
            // CreatureAttrTypeConfig 表ID = attrID*1000 * level ,最后结果是六位数的ID,有问题找策划
            var id = (this.creatureSpawnConf.attrID * 1000) + this.creatureSpawnConf.level;
            var creatureAttrTypeConfig = CreatureAttrTypeConfig.GetConfig(id);
            //最大生命 攻击力 物理防御 魔法防御 暴击值 韧性值 速度 这几个是乘法
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE, this.GetValue(this.creatureConf.life, creatureAttrTypeConfig.life));
            this.basicattr.OriHp = this.creatureConf.life;
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_DAMAGE, this.GetValue(this.creatureConf.damage, creatureAttrTypeConfig.damage));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_PHYSICAL_DEFENCE, this.GetValue(this.creatureConf.physical_defence, creatureAttrTypeConfig.physical_defence));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SPELL_DEFENCE, this.GetValue(this.creatureConf.spell_defence, creatureAttrTypeConfig.spell_defence));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_AMOUNT, this.GetValue(this.creatureConf.crit_amount, creatureAttrTypeConfig.crit_amount));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_AMOUNT, this.GetValue(this.creatureConf.toughness_amout, creatureAttrTypeConfig.toughness_amout));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED, this.GetValue(this.creatureConf.shot_speed, creatureAttrTypeConfig.shot_speed));
            //下面的值是加法
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_CHANCE, this.creatureConf.crit_chance + creatureAttrTypeConfig.crit_chance);
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_CHANCE, this.creatureConf.toughness_chance + creatureAttrTypeConfig.toughness_chance);
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_DAMAGE, this.creatureConf.crit_damage + creatureAttrTypeConfig.crit_damage);
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT, this.creatureConf.crit_reduced_amount + creatureAttrTypeConfig.crit_reduced_amount);
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT, this.creatureConf.treatment_effect + creatureAttrTypeConfig.treatment_effect);
        }
        else {
            var creatureAttrForceConf = CreatureAttrForceConfig.GetConfig(this.creatureSpawnConf.attrID);
            if (creatureAttrForceConf != null) {
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE, creatureAttrForceConf.life);
                this.basicattr.OriHp = creatureAttrForceConf.life;
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_DAMAGE, creatureAttrForceConf.damage);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_PHYSICAL_DEFENCE, creatureAttrForceConf.physical_defence);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SPELL_DEFENCE, creatureAttrForceConf.spell_defence);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_AMOUNT, creatureAttrForceConf.crit_amount);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_AMOUNT, creatureAttrForceConf.toughness_amout);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED, creatureAttrForceConf.shot_speed);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_CHANCE, creatureAttrForceConf.crit_chance);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_CHANCE, creatureAttrForceConf.toughness_chance);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_DAMAGE, creatureAttrForceConf.crit_damage);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT, creatureAttrForceConf.crit_reduced_amount);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT, creatureAttrForceConf.treatment_effect);
            }
        }
        /*
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE,this.creatureConf.life);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_DAMAGE,this.creatureConf.damage);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_PHYSICAL_DEFENCE,this.creatureConf.physical_defence);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SPELL_DEFENCE,this.creatureConf.spell_defence);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_AMOUNT,this.creatureConf.crit_amount);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_AMOUNT,this.creatureConf.toughness_amout);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED,this.creatureConf.shot_speed);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_CHANCE,this.creatureConf.crit_chance);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_CHANCE,this.creatureConf.toughness_chance);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_DAMAGE,this.creatureConf.crit_damage);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT,this.creatureConf.crit_reduced_amount);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT,this.creatureConf.treatment_effect);
        */
    };
    /**
     * 封装一层是因为这个乘法结果如果是0,哪需要给一个默认值,默认值是1,有变化找策划
     *  basicValue CreatureTempletConfig表里面的值  changeValue CreatureSpawnConfig表里面的比例值
     */
    GameObject.prototype.GetValue = function (basicValue, changeValue) {
        var result = 0;
        result = Math.floor(basicValue * changeValue); //取整方式为下取整,策划说的
        if (result == 0)
            result = 1;
        return result;
    };
    GameObject.prototype.Death = function () {
        var avatarCom = this.getComponent(ComponentType.Dragon);
        if (avatarCom && this.gameView) {
            var index = this.gameView.getChildIndex(avatarCom.Body);
            if (index != -1) {
                this.gameView.removeChildAt(index);
            }
        }
        this.RemoveAllEventListener();
        var componentNames = Object.keys(this._components);
        while (componentNames.length) {
            var componentName = componentNames[0];
            this.removeComponent(componentName);
            componentNames = Object.keys(this._components);
        }
        this.mClientBit.SetBitSet(ClientBits.CLIENT_BIT_DEAD, true);
        this.gameView = null;
        this.battleObj = null;
        this.basicattr = null;
    };
    GameObject.prototype.addComponent = function (componentName) {
        if (this._components[componentName]) {
            return null;
        }
        var component = ObjectPool.pop(componentName);
        component.type = componentName;
        component.entity = this;
        component.start();
        ComponentSystem.addComponent(component);
        this._components[componentName] = component;
        return component;
    };
    GameObject.prototype.removeComponent = function (componentName) {
        var component = this._components[componentName];
        if (!component) {
            return;
        }
        ComponentSystem.removeComponent(component);
        component.stop();
        ObjectPool.push(component);
        this._components[componentName] = null;
        delete this._components[componentName];
    };
    GameObject.prototype.getComponent = function (componentName) {
        var hasComponent = this._components[componentName];
        return hasComponent;
    };
    GameObject.prototype.setInCamera = function (value) {
        this._inCamera = value;
    };
    GameObject.prototype.getInCamera = function () {
        return this._inCamera;
    };
    Object.defineProperty(GameObject.prototype, "RealTimeProperties", {
        /**实时属性 */
        get: function () {
            var result = [];
            var ownerBuffArray = this.getComponent(ComponentType.Buff).BuffArray;
            var buffeffattrpercentage = []; //BuffEffect修改属性 - 百分比修改
            var buffeffattrValue = []; //BuffEffect修改属性 - 固定值修改
            var buffeffattrvalueandper = []; //BuffEffect修改属性 - 索引属性修改
            for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
                buffeffattrpercentage[i] = 0;
            }
            for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
                buffeffattrValue[i] = 0;
            }
            for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
                buffeffattrvalueandper[i] = 0;
            }
            for (var i = 0; i < ownerBuffArray.length; i++) {
                for (var j = 0; j < ownerBuffArray[i].BuffEffectArray.length; j++) {
                    if (ownerBuffArray[i].BuffEffectArray[j].Type == BuffEffecttype.BuffEffecttype_ChangeAttr) {
                        for (var k = 0; k < EStatistic.STATISTIC_MAX; k++) {
                            if (ownerBuffArray[i].BuffEffectArray[j].Config.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_TheSpec) {
                                buffeffattrValue[k] += ownerBuffArray[i].BuffEffectArray[j].BuffStatistics[k];
                            }
                            else if (ownerBuffArray[i].BuffEffectArray[j].Config.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_Percentage) {
                                buffeffattrpercentage[k] += (ownerBuffArray[i].BuffEffectArray[j].BuffStatistics[k]);
                            }
                            else if (ownerBuffArray[i].BuffEffectArray[j].Config.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_Percentage) {
                                buffeffattrvalueandper[k] += ownerBuffArray[i].BuffEffectArray[j].BuffStatistics[k];
                            }
                        }
                    }
                }
            }
            for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
                if (buffeffattrpercentage[i] == 0) {
                    result[i] = this.basicattr.GetCurrentValue(i) * 1;
                }
                else {
                    result[i] = this.basicattr.GetCurrentValue(i) * (buffeffattrpercentage[i] + 1);
                }
            }
            for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
                result[i] += buffeffattrValue[i];
            }
            for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
                result[i] += buffeffattrvalueandper[i];
            }
            for (var i = 0; i < EStatistic.STATISTIC_MAX; i++) {
                var conf = AttributeFormatConfig.GetConfig(i);
                if (result[i] < 0) {
                    if (conf.canBeNegative == 0) {
                        result[i] = 0;
                    }
                }
            }
            return result;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GameObject.prototype, "Alive", {
        get: function () {
            return !this.mClientBit.GetBitset(ClientBits.CLIENT_BIT_DEAD);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GameObject.prototype, "IsDead", {
        get: function () {
            return this.mClientBit.GetBitset(ClientBits.CLIENT_BIT_DEAD);
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GameObject.prototype, "ClientBit", {
        get: function () {
            return this.mClientBit;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(GameObject.prototype, "CreatureConf", {
        get: function () {
            return this.creatureConf;
        },
        enumerable: true,
        configurable: true
    });
    GameObject.prototype.AddClientBitState = function (bit) {
        if (!this.TestClientBitState(bit)) {
            this.mClientBit.SetBitSet(bit, true);
            this.OnClientBitsetChanged(bit);
        }
    };
    GameObject.prototype.DelClientBitState = function (bit) {
        if (this.TestClientBitState(bit)) {
            this.mClientBit.SetBitSet(bit, false);
            this.OnClientBitsetChanged(bit);
        }
    };
    GameObject.prototype.TestClientBitState = function (bit) {
        return this.mClientBit.GetBitset(bit);
    };
    GameObject.prototype.OnClientBitsetChanged = function (bit) {
    };
    return GameObject;
}());
__reflect(GameObject.prototype, "GameObject");
//# sourceMappingURL=GameObject.js.map