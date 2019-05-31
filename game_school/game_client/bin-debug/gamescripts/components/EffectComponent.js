var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var AvatarEffectType;
(function (AvatarEffectType) {
    AvatarEffectType[AvatarEffectType["Skill"] = 0] = "Skill";
    AvatarEffectType[AvatarEffectType["Buff"] = 1] = "Buff";
})(AvatarEffectType || (AvatarEffectType = {}));
/* 这个类,AvatarEffectComponent*/
var EffectComponent = (function () {
    function EffectComponent(id, entity, effectType, avatarEffectComponent) {
        this.totalPlayNum = 1;
        this.effectType = AvatarEffectType.Skill;
        this.avatarEffectComponent = avatarEffectComponent;
        this.entity = entity;
        this.effectType = effectType;
        this.mEffectID = id;
        this.effConfig = EffectConfig.GetConfig(id);
        this.start();
    }
    EffectComponent.prototype.start = function () {
        if (this.effectType == AvatarEffectType.Skill) {
            this.mMovieClip = new EffectMovieClip(); //ObjectPool.pop("EffectMovieClip", GameResGroupName.SkilleffGroup, this.entity.skilleffpath, this.effConfig.resourcesGroup, this.entity);
            this.mMovieClip.Init(GameResGroupName.SkilleffGroup, this.entity.skilleffpath, this.effConfig.resourcesGroup, this.entity, this.entity.oriScale);
        }
        else if (this.effectType == AvatarEffectType.Buff) {
            this.mMovieClip = new EffectMovieClip(); // ObjectPool.pop("EffectMovieClip", GameResGroupName.BuffeffGroup, this.entity.buffeffpath, this.effConfig.resourcesGroup, this.entity);
            this.mMovieClip.Init(GameResGroupName.BuffeffGroup, this.entity.buffeffpath, this.effConfig.resourcesGroup, this.entity, this.entity.oriScale);
        }
        var avatarComponent = this.entity.getComponent(ComponentType.Dragon);
        this.mcParent = avatarComponent.Body;
        this.avatarMC = avatarComponent.MDragon;
        this.mMovieClip.start(this.mcParent);
        if (this.effConfig.layer == 1) {
            this.mcParent.addChild(this.mMovieClip.MovieClip);
        }
        else if (this.effConfig.layer == 2) {
            var index = this.mcParent.getChildIndex(this.avatarMC);
            if (index > 0)
                this.mcParent.addChildAt(this.mMovieClip.MovieClip, index - 1);
            else
                this.mcParent.addChildAt(this.mMovieClip.MovieClip, 0);
        }
        // if (this.entity.dir == Dir.Top
        //     || this.entity.dir == Dir.TopLeft
        //     || this.entity.dir == Dir.TopRight) {
        //     this.mcParent.addChildAt(this.mMovieClip.MovieClip, 0);
        // } else {
        //     this.mcParent.addChild(this.mMovieClip.MovieClip);
        // }
    };
    EffectComponent.prototype.stop = function () {
        if (this.mMovieClip) {
            this.mMovieClip.stop();
            ObjectPool.push(this.mMovieClip);
            this.mcParent = null;
        }
    };
    EffectComponent.prototype.update = function (advancedTime) {
        if (this.mMovieClip) {
            this.mMovieClip.update(advancedTime);
        }
    };
    /**
    * 播放特效
    * @param id 特效的ID
    * @param effectPosType 特效的位置类型
    */
    EffectComponent.prototype.PlayEffect = function (id, effectPosType) {
        this.mEffectID = id;
        this.mMovieClip.SetEffectID(id, this.avatarEffectComponent);
        var effectConf = EffectConfig.GetConfig(id);
        if (effectConf == null)
            return;
        this.mEffectName = effectConf.effectResources;
        this.totalPlayNum = effectConf.repeat;
        this.mMovieClip.MovieClip.scaleX = effectConf.scale;
        this.mMovieClip.MovieClip.scaleY = effectConf.scale;
        this.setPos(effectPosType, new egret.Point(effectConf.position[0], effectConf.position[1]));
        this.startMc();
    };
    EffectComponent.prototype.setPos = function (effctPosType, posPoint) {
        this.mMovieClip.MovieClip.x = 0;
        this.mMovieClip.MovieClip.y = 0;
        //特效位置确认方式
        //0.默认和1一样,按照目标为原点
        //1.以目标为原点
        //2.敌方前排中间原点
        //3.己方前排中间原点
        //4.屏幕中央 
        //5.自身 
        var point = new egret.Point(); //最后取值的世界舞台坐标
        switch (effctPosType) {
            case 0:
            case 1:
                var skillComponent = this.entity.getComponent(ComponentType.Skill);
                var target = skillComponent.GetTarget();
                if (target) {
                    var targetPoint = new egret.Point(target.position.x, target.position.y); //取的是目标的当前坐标
                    point = targetPoint;
                }
                break;
            case 2:
                if (this.entity.camp == Camp.Friendly) {
                    point = App.FightManager.GetBattlePoints(7);
                }
                else if (this.entity.camp == Camp.Hostility) {
                    point = App.FightManager.GetBattlePoints(1);
                }
                break;
            case 3:
                if (this.entity.camp == Camp.Friendly) {
                    point = App.FightManager.GetBattlePoints(1);
                }
                else if (this.entity.camp == Camp.Hostility) {
                    point = App.FightManager.GetBattlePoints(7);
                }
                break;
            case 4:
                var FightGameView = App.ViewManager.getView(ViewConst.CCG_GameFight);
                point.x = FightGameView.width / 2;
                point.y = FightGameView.height / 2;
                break;
            case 5://就是自身
                point = this.entity.position;
                break;
        }
        var temp = this.mcParent.globalToLocal(point.x, point.y);
        //加上偏移量     
        if (this.entity.camp == Camp.Friendly)
            temp.x += posPoint.x;
        else if (this.entity.camp == Camp.Hostility)
            temp.x += -posPoint.x;
        temp.y += posPoint.y;
        this.mMovieClip.MovieClip.x = temp.x;
        this.mMovieClip.MovieClip.y = temp.y;
    };
    //判断自己和技能目标是不是都属于一个阵营
    EffectComponent.prototype.isCamp = function (entity, skillTarget) {
        if (entity == null || skillTarget == null)
            return false;
        if (entity.camp == skillTarget.camp)
            return true;
        else
            return false;
    };
    EffectComponent.prototype.startMc = function () {
        if (this.mEffectName) {
            var skillComponent = this.entity.getComponent(ComponentType.Skill);
            var target = skillComponent.GetTarget();
            var dir = this.entity.dir;
            if (!this.isCamp(this.entity, target)) {
                if (this.entity.dir == Dir.Left) {
                    dir = Dir.Right;
                }
                else {
                    dir = Dir.Left;
                }
            }
            this.mMovieClip.MovieClip.gotoAction(this.mEffectName, dir, true, this.totalPlayNum, this.EffectID);
        }
    };
    EffectComponent.prototype.stopMc = function () {
        if (this.mMovieClip)
            App.DisplayUtils.removeFromParent(this.mMovieClip.MovieClip);
        this.stop();
    };
    Object.defineProperty(EffectComponent.prototype, "CurMovieClipData", {
        get: function () {
            return this.mMovieClip;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(EffectComponent.prototype, "EffectName", {
        get: function () {
            return this.mEffectName;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(EffectComponent.prototype, "EffectID", {
        get: function () {
            return this.mEffectID;
        },
        enumerable: true,
        configurable: true
    });
    return EffectComponent;
}());
__reflect(EffectComponent.prototype, "EffectComponent");
//# sourceMappingURL=EffectComponent.js.map