enum AvatarEffectType {
    Skill = 0,
    Buff = 1,
}

/* 这个类,AvatarEffectComponent*/
class EffectComponent {
    private avatarEffectComponent: AvatarEffectComponent;
    private mMovieClip: EffectMovieClip;
    private mcParent: egret.DisplayObjectContainer; //实际上是人的容器,最后特效层级操作这个
    private avatarMC: DragonCombatantObject;  //人的mc
    private mEffectID: number;
    private mEffectName: string;
    private entity: GameObject;
    private totalPlayNum: number = 1;
    private effConfig: EffectConfig;

    private effectType: AvatarEffectType = AvatarEffectType.Skill;

    public constructor(id: number, entity: GameObject, effectType: AvatarEffectType, avatarEffectComponent: AvatarEffectComponent) {
        this.avatarEffectComponent = avatarEffectComponent;
        this.entity = entity;
        this.effectType = effectType;
        this.mEffectID = id;
        this.effConfig = EffectConfig.GetConfig(id);
        this.start();
    }

    public start(): void {
        if (this.effectType == AvatarEffectType.Skill) {
            this.mMovieClip = new EffectMovieClip();//ObjectPool.pop("EffectMovieClip", GameResGroupName.SkilleffGroup, this.entity.skilleffpath, this.effConfig.resourcesGroup, this.entity);
            this.mMovieClip.Init(GameResGroupName.SkilleffGroup, this.entity.skilleffpath, this.effConfig.resourcesGroup, this.entity,this.entity.oriScale);
        }
        else if (this.effectType == AvatarEffectType.Buff) {
            this.mMovieClip =new EffectMovieClip();// ObjectPool.pop("EffectMovieClip", GameResGroupName.BuffeffGroup, this.entity.buffeffpath, this.effConfig.resourcesGroup, this.entity);
            this.mMovieClip.Init(GameResGroupName.BuffeffGroup, this.entity.buffeffpath, this.effConfig.resourcesGroup, this.entity,this.entity.oriScale);
        }

        var avatarComponent: DragonComponent = <DragonComponent>this.entity.getComponent(ComponentType.Dragon);
        this.mcParent = avatarComponent.Body;
        this.avatarMC = avatarComponent.MDragon;

        this.mMovieClip.start(this.mcParent);

        if (this.effConfig.layer == 1)  //在模型上面
        {
            this.mcParent.addChild(this.mMovieClip.MovieClip);
        }
        else if (this.effConfig.layer == 2)  //在模型下面
        {
            let index = this.mcParent.getChildIndex(this.avatarMC);     
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
    }

    public stop(): void {
        if (this.mMovieClip) {
            this.mMovieClip.stop();
            ObjectPool.push(this.mMovieClip);
            this.mcParent = null;
        }
    }

    public update(advancedTime: number) : void {
        if (this.mMovieClip) {
            this.mMovieClip.update(advancedTime);
        }
    }

    /**
    * 播放特效
    * @param id 特效的ID
    * @param effectPosType 特效的位置类型
    */
    public PlayEffect(id: number, effectPosType: number) {

        this.mEffectID = id;
        this.mMovieClip.SetEffectID(id, this.avatarEffectComponent);
        let effectConf: EffectConfig = EffectConfig.GetConfig(id);
        if (effectConf == null) return;
        this.mEffectName = effectConf.effectResources;
        this.totalPlayNum = effectConf.repeat;
        this.mMovieClip.MovieClip.scaleX = effectConf.scale;
        this.mMovieClip.MovieClip.scaleY = effectConf.scale;
 
        this.setPos(effectPosType, new egret.Point(effectConf.position[0], effectConf.position[1]));
        this.startMc();
    }

    private setPos(effctPosType: number, posPoint: egret.Point): void {
        this.mMovieClip.MovieClip.x = 0;
        this.mMovieClip.MovieClip.y = 0;

        //特效位置确认方式
        //0.默认和1一样,按照目标为原点
        //1.以目标为原点
        //2.敌方前排中间原点
        //3.己方前排中间原点
        //4.屏幕中央 
        //5.自身 
        var point: egret.Point = new egret.Point(); //最后取值的世界舞台坐标
        switch (effctPosType) {
            case 0:
            case 1:
                let skillComponent = <SkillComponent>this.entity.getComponent(ComponentType.Skill);
                let target = skillComponent.GetTarget();
                if (target) {
                    let targetPoint = new egret.Point(target.position.x, target.position.y); //取的是目标的当前坐标
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
                var FightGameView = App.ViewManager.getView(ViewConst.CCG_GameFight) as CCG_FightGameView
                point.x = FightGameView.width / 2;
                point.y = FightGameView.height / 2;
                break;
            case 5:  //就是自身
                point = this.entity.position;
                break;
        }

        let temp = this.mcParent.globalToLocal(point.x, point.y);

        //加上偏移量     
        if (this.entity.camp == Camp.Friendly)
            temp.x += posPoint.x;
        else if (this.entity.camp == Camp.Hostility) //位于敌方阵容,x方向坐标要反转,有问题找策划,策划要求的
            temp.x += -posPoint.x;
              temp.y += posPoint.y;

        this.mMovieClip.MovieClip.x = temp.x;
        this.mMovieClip.MovieClip.y = temp.y;
    }

    //判断自己和技能目标是不是都属于一个阵营
    private isCamp(entity: GameObject, skillTarget: GameObject): boolean {
        if (entity == null || skillTarget == null)
            return false;
        if (entity.camp == skillTarget.camp)
            return true;
        else
            return false;
    }

    private startMc(): void {
        if (this.mEffectName) {
            let skillComponent = <SkillComponent>this.entity.getComponent(ComponentType.Skill);
            let target = skillComponent.GetTarget();
            let dir = this.entity.dir;
            if (!this.isCamp(this.entity, target)) {
                if (this.entity.dir == Dir.Left) {
                    dir = Dir.Right;
                } else {
                    dir = Dir.Left;
                }
            }
            this.mMovieClip.MovieClip.gotoAction(this.mEffectName, dir, true, this.totalPlayNum,this.EffectID);
        }
    }

    public stopMc(): void {
        if (this.mMovieClip)
            App.DisplayUtils.removeFromParent(this.mMovieClip.MovieClip);
        this.stop();
    }

    public get CurMovieClipData() {
        return this.mMovieClip;
    }

    public get EffectName() {
        return this.mEffectName;
    }

    public get EffectID() {
        return this.mEffectID;
    }
}
