class AvatarEffectComponent extends Component {

    //要播放的特效
    private mcEffectList: Array<EffectComponent> = []; //这里的特效是NEW出来的
    private mcEffectEvent: { [key: string]: Array<Function>; } = {};

    public constructor() {
        super();
    }

    public start(): void {
        super.start();
    }

    public stop(): void {
        super.stop();
        for (let i = 0; i < this.mcEffectList.length; i++) {
          this. RemoveEffect(this.mcEffectList[i].EffectID);
           // this.mcEffectList[i].stopMc();
        }
    }

    public update(advancedTime: number): void {
        super.update(advancedTime);
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
    public PlayEffect(id: number, effectPosType: number, effectType: AvatarEffectType, callback?: Function) {
        let effectConf: EffectConfig = EffectConfig.GetConfig(id);
        if (effectConf == null)
            return;
       this.AddEffect(id, effectPosType, effectType, callback);
    }

    //添加一个特效
    private AddEffect(id: number, effectPosType: number, effectType: AvatarEffectType, callback?: Function): void {
        if (this.mcEffectEvent[id]) {
            this.mcEffectEvent[id].push(callback);
        } else {
            let callList: Array<Function> = [];
            callList.push(callback);
            this.mcEffectEvent[id] = callList;
        }
        let effect: EffectComponent = new EffectComponent(id, this.entity, effectType, this);
        this.mcEffectList.push(effect);
       // console.log("AddEffect::"+"  "+id+"  :"+this.entity.basicattr.Name +"  :"+this.entity.uid);              
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

}

class EffectMovieClip extends MovieClipComponentBase {
    public constructor() {
        super()
    }
    private mEffectID: number;
    private avatarEffectComponent: AvatarEffectComponent;
    public Init(gameResGroupName: string, mcpath: string, mcname: string, entity,scale:number=1) {
        super.Init(gameResGroupName, mcpath, mcname, entity,scale);
    }

    public SetEffectID(ID: number, avatarEffectComponent: AvatarEffectComponent) {
        this.mEffectID = ID;
        this.avatarEffectComponent = avatarEffectComponent;
    }

    public start(_body: egret.DisplayObjectContainer) {
        super.start(_body);
    }

    public stop() {
        super.stop(false); //这里涉及到移除body,特效的body,就是人,所以这里不能移除这个body,这个false,绝对不能删
    }

    public update(advancetime: number) {
        super.update(advancetime);
       
        if (this.MovieClip){
            this.MovieClip.runAction(advancetime);
        }
            
    }

    public complateAction(): void {
        super.complateAction();
        let playNum = this.MovieClip.GetPlayNum(); //获取播放次数,非循环的播放完毕会自毁
        if (playNum != 0) {
           // console.log("complateAction::"+"    name:"+this.Entity.basicattr.Name+"    uid:"+this.Entity.uid+"   id"+this.mEffectID);
            this.avatarEffectComponent.RemoveEffect(this.mEffectID);
        }
    }
}