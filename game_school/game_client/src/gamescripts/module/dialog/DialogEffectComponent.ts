

class DialogEffectComponent {
    private mMovieClip: DialogEffectMovieClip;
    private mcParent: egret.DisplayObjectContainer;
    private mEffectID: number;
    private mEffectName: string;
    private group: eui.Group;
    private totalPlayNum: number = 1;
    private effConfig: EffectConfig;
    public mHand: DialogAvatarEffectComponent;

    public constructor(id: number, group: eui.Group, hand: DialogAvatarEffectComponent) {
        this.group = group;
        this.mEffectID = id;
        this.mHand = hand;
        this.effConfig = EffectConfig.GetConfig(id);
        this.start();
    }

    public start(): void {
        this.mMovieClip = ObjectPool.pop("DialogEffectMovieClip");
        this.mMovieClip.Init(GameResGroupName.BuffeffGroup, GameobjConst.Buffeffpath, this.effConfig.resourcesGroup, null);
        this.mMovieClip.start();
        this.mcParent = this.group;
    }

    public stop(): void {
        if (this.mMovieClip) {
            this.mMovieClip.stop();
            ObjectPool.push(this.mMovieClip);
            this.mMovieClip = null;
            this.mcParent = null;
        }

    }

    public update(advancedTime: number): void {
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
        this.mMovieClip.SetEffectID(id, this.mHand);
        let effectConf: EffectConfig = EffectConfig.GetConfig(id);
        if (effectConf == null)
            return;
        this.mEffectName = effectConf.effectResources;
        this.totalPlayNum = effectConf.repeat;
        this.setPos(effectPosType, new egret.Point(effectConf.position[0], effectConf.position[1]));
        this.startMc();
    }

    private setPos(effctPosType: number, posPoint: egret.Point): void {
        // var point: egret.Point = new egret.Point(); //最后取值的世界舞台坐标
        // let temp = this.mcParent.globalToLocal(point.x, point.y);
        // //加上偏移量     
        // temp.x += posPoint.x;
        // temp.y += posPoint.y;
        this.mMovieClip.MovieClip.x += posPoint.x;
        this.mMovieClip.MovieClip.y += posPoint.y;
    }

    private startMc(): void {
        if (this.mEffectName) {
            // let skillComponent = <SkillComponent>this.entity.getComponent(ComponentType.Skill);
            // let target = skillComponent.GetTarget();
            // let dir = this.entity.dir;
            // if (!this.isCamp(this.entity, target)) {
            //     if (this.entity.dir == Dir.Left) {
            //         dir = Dir.Right;
            //     } else {
            //         dir = Dir.Left;
            //     }
            // }          
            this.mMovieClip.MovieClip.gotoAction(this.mEffectName, Dir.Left, true, this.totalPlayNum);
            this.mcParent.addChild(this.mMovieClip.MovieClip);
            // if (this.entity.dir == Dir.Top
            //     || this.entity.dir == Dir.TopLeft
            //     || this.entity.dir == Dir.TopRight) {
            //     this.mcParent.addChildAt(this.mMovieClip.MovieClip, 0);
            // } else {          
            // }
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

    public get MovieClip() {
        return this.mMovieClip.MovieClip;
    }
}
