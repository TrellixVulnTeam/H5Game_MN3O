
/* 这个类,由BuffComponent管理*/
class AvatarBuffComponent {
    private mMovieClip: AvatarBuffMovieClip;
    private mcParent: egret.DisplayObjectContainer;
    private mbuffEffectName: string;
    private entity: GameObject;
    private totalPlayNum: number = 0;

    public constructor(entity: GameObject) {
        this.entity = entity;
        this.start();
    }

    public start(): void {
        this.mMovieClip = ObjectPool.pop("AvatarBuffMovieClip", GameResGroupName.BuffeffGroup, this.entity.buffeffpath, this.entity.buffName, this.entity);
        this.mMovieClip.Init(GameResGroupName.BuffeffGroup, this.entity.buffeffpath, this.entity.buffName, this.entity);
        this.mMovieClip.start();

        var avatarComponent: DragonComponent = <DragonComponent>this.entity.getComponent(ComponentType.Dragon);
        this.mcParent = avatarComponent.Body;
    }

    public stop(): void {
        
        this.mMovieClip.stop();
        ObjectPool.push(this.mMovieClip);
        this.mMovieClip = null;
        this.mcParent = null;
    }

    public update(advancedTime: number): void {
        if (this.mMovieClip.MovieClip.parent) {
            this.mMovieClip.update(advancedTime);
        }
    }

    public PlayBuffEffect(name: string, buff: Buff, totalPlayNum: number = 0) {
        this.mbuffEffectName = name;
        this.totalPlayNum = totalPlayNum;
        //this.setPos(buff);
        this.startMc();
    }


    private setPos(buff: Buff): void {
        let point: egret.Point = new egret.Point();
        //point.x += buff.MagicConfig.effectPosition[0];
        //point.y += buff.MagicConfig.effectPosition[1];
        this.mMovieClip.MovieClip.x = point.x;
        this.mMovieClip.MovieClip.y = point.y;
    }

    private startMc(): void {

        this.mMovieClip.MovieClip.gotoAction(this.mbuffEffectName, this.entity.dir, true, this.totalPlayNum);
        if (this.entity.dir == Dir.Top
            || this.entity.dir == Dir.TopLeft
            || this.entity.dir == Dir.TopRight) {
            this.mcParent.addChildAt(this.mMovieClip.MovieClip, 0);
        } else {
            this.mcParent.addChild(this.mMovieClip.MovieClip);
        }
    }

    public stopMc(): void {
        App.DisplayUtils.removeFromParent(this.mMovieClip.MovieClip);
        this.mMovieClip.MovieClip.x = 0;
        this.mMovieClip.MovieClip.y = 0;
    }

    private complateAction(): void {
        //this.stopMc();
    }

    public get CurMovieClipData() {
        return this.mMovieClip;
    }

    public get BuffEffectName() {
        return this.mbuffEffectName;
    }
}
