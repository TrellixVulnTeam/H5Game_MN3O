class DialogAvatarEffectComponent {
    public dealTime: number;
    public dealInterval: number;
    public isRuning: boolean;
    public type: string;
    public group: eui.Group;

    //要播放的特效
    private mcEffectList: Array<DialogEffectComponent> = []; //这里的特效是NEW出来的
    private mcEffectEvent: { [key: string]: Array<Function>; } = {};

    public constructor(group: eui.Group) {
        this.group = group;
        this.start();
    }

    public start(): void {
        this.dealTime = 0;
        this.dealInterval = 0;
        this.isRuning = true;
    }

    public stop(): void {
        this.dealTime = null;
        this.dealInterval = null;
        this.isRuning = false;
        this.type = null;
        this.group = null;

        for (let i = 0; i < this.mcEffectList.length; i++) {
            this.mcEffectList[i].stop();
        }
    }

    public update(advancedTime: number): void {

        for (let i = 0; i < this.mcEffectList.length; i++) {
            this.mcEffectList[i].update(advancedTime);
        }
    }

    /**
    * 播放特效
    * @param id 特效的ID
    * @param effectPosType 特效的位置类型
    * @param effectType 特效类型
    */
    public PlayEffect(id: number, point: egret.Point, effectPosType: number = 0, callback?: Function) {
        let effectConf: EffectConfig = EffectConfig.GetConfig(id);
        if (effectConf == null)
            return;
        this.AddEffect(id, point, effectPosType, callback);
    }

    //添加一个特效
    private AddEffect(id: number, point: egret.Point, effectPosType: number, callback?: Function): void {
        if (this.mcEffectEvent[id]) {
            this.mcEffectEvent[id].push(callback);
        } else {
            let callList: Array<Function> = [];
            callList.push(callback);
            this.mcEffectEvent[id] = callList;
        }
        let effect: DialogEffectComponent = new DialogEffectComponent(id, this.group, this);
        this.mcEffectList.push(effect);
        effect.MovieClip.x = point.x;
        effect.MovieClip.y = point.y;
        effect.PlayEffect(id, effectPosType);
    }

    //移除一个特效
    public RemoveEffect(id: number): void {
        let index = -1;
        for (let i = 0; i < this.mcEffectList.length; i++) {
            if (id == this.mcEffectList[i].EffectID) {
                index = i;
                this.mcEffectList[i].stopMc();
            }
        }

        for (let key in this.mcEffectEvent) {
            if (key == id.toString()) {
                for (let index = 0; index < this.mcEffectEvent[key].length; index++) {
                    if (this.mcEffectEvent[key][index] != null) {
                        this.mcEffectEvent[key][index]();
                        this.mcEffectEvent[key].splice(index, 1);
                    }
                }
            }
        }

        if (index >= 0)
            this.mcEffectList.splice(index, 1);
    }

    public RemoveAllEffect() {
        let array: Array<number> = [];
        for (let i = 0; i < this.mcEffectList.length; i++) {
            let oldeff = this.mcEffectList[i];
            array.push(oldeff.EffectID);
        }
        for (let i = 0; i < array.length; i++) {
            this.RemoveEffect(array[i]);
        }
    }

}

class DialogEffectMovieClip extends MovieClipComponentBase {
    public constructor() {
        super()
    }
    private mEffectID: number;
    public mHand: DialogAvatarEffectComponent;

    public Init(gameResGroupName: string, mcpath: string, mcname: string, entity) {
        super.Init(gameResGroupName, mcpath, mcname, entity);
    }

    public SetEffectID(ID: number, mHand: DialogAvatarEffectComponent) {
        this.mEffectID = ID;
        this.mHand = mHand;
    }

    public start() {
        super.start();
    }

    public stop() {
        super.stop();
    }

    public update(advancetime: number) {
        super.update(advancetime);
        if (this.MovieClip)
            this.MovieClip.runAction(advancetime);
    }

    public complateAction(): void {
        super.complateAction();
        let playNum = this.MovieClip.GetPlayNum(); //获取播放次数,非循环的播放完毕会自毁
        if (playNum != 0) {
            this.mHand.RemoveEffect(this.mEffectID);
        }
    }
}