enum BuffTimeType {
    BuffTimeType_Begin = 1,
    BuffTimeType_End = 2,
}

class BuffComponent extends Component {
    private avatarEffectComponent: AvatarEffectComponent;
    private avatarComponent: DragonComponent;
    private headComponent: HeadComponent;
    private mBuffArray: Array<Buff>;

    private mcParent: egret.DisplayObjectContainer;

    public constructor() {
        super();
    }

    public start(): void {
        super.start();
        this.mBuffArray = new Array<Buff>();
        this.avatarEffectComponent = <AvatarEffectComponent>this.entity.getComponent(ComponentType.AvatarEffect);
        this.headComponent = <HeadComponent>this.entity.getComponent(ComponentType.Head);
        this.headComponent.createhpslider(this.entity.camp);
        var avatarComponent: DragonComponent = <DragonComponent>this.entity.getComponent(ComponentType.Dragon);
        this.mcParent = avatarComponent.Body;    
    }
    
    public stop(): void {
        super.stop();
    }

    public update(advancetime: number): void {
        super.update(advancetime);
    }

    /**添加Buff
     * @param id BuffID
     * @param casterObj 作俑者
     */
    public AddBuff(id: number, casterObjId: string, callback?: Function): void {

        let buffConf: BuffConfig = BuffConfig.GetConfig(id);

        if (this.CheckIsHaveSameIDBuff(id))  //检测同ID
        {
            this.BuffDealWithSameId(buffConf, casterObjId);
        }
        else if (this.CheckIsHaveSameGroupBuff(buffConf.group))   //检测同Group
        {
            this.BuffDealWithSameGroup(buffConf, casterObjId);
        }
        else {
            this.AddNewBuff(buffConf, casterObjId);
        }

        if (callback) {
            callback();
        }
    }

    /**
     * 驱散Buff
     */
    public DisperseBuff(type: BuffFriendlyType, callback?: Function): void {
        let num: number = this.mBuffArray.length;
        for (let i = 0; i < num; i++) {
            if (this.mBuffArray[i].FriendlyType == type && this.mBuffArray[i].DisperseType == <number>BuffDisperseType.BuffDisperseType_CanDis) {
                this.RemoveBuff(this.mBuffArray[i]);
                num = null
                this.DisperseBuff(type, callback);
                return;
            }
        }
        if (callback) {
            callback();
        }
     }

    /**检测是否存在相同ID的buff */
    public CheckIsHaveSameIDBuff(id: number): boolean {
        for (let i = 0; i < this.mBuffArray.length; i++) {
            if (this.mBuffArray[i].Config.ID == id) {
                return true;
            }
        }
        return false;
    }

    /**检测是否存在相同Group的buff */
    public CheckIsHaveSameGroupBuff(group: number): boolean {
        for (let i = 0; i < this.mBuffArray.length; i++) {
            if (this.mBuffArray[i].Config.group == group) {
                return true;
            }
        }
        return false;
    }

    /**
     * Buff相同ID共存逻辑处理
     */
    private BuffDealWithSameId(buffConf: BuffConfig, casterObjId: string) {
        if (buffConf.liveStyle == <number>BuffOverlayProcessing.BuffOverlayProcessing_Offset) {
            this.mBuffArray.forEach(function (data) {
                if (data.Config.ID == buffConf.ID) {
                    this.RemoveBuff(data);
                }
            }.bind(this));

            this.AddNewBuff(buffConf, casterObjId);
        }
        else if (buffConf.liveStyle == <number>BuffOverlayProcessing.BuffOverlayProcessing_coexist) {
            this.AddNewBuff(buffConf, casterObjId);
        }
        else if (buffConf.liveStyle == <number>BuffOverlayProcessing.BuffOverlayProcessing_Overlay) {
            this.mBuffArray.forEach(function (data) {
                if (data.Config.ID == buffConf.ID) {
                    data.CD = buffConf.time;
                    data.AddLayers(1);
                }
            }.bind(this));
        }
        else if (buffConf.liveStyle == <number>BuffOverlayProcessing.BuffOverlayProcessing_Immunity) {

        }
    }

    /**
     * Buff相同Group共存逻辑处理
     */
    private BuffDealWithSameGroup(buffConf: BuffConfig, casterObjId: string) {
        let buffGroup: BuffGroupConfig = BuffGroupConfig.GetConfig(buffConf.group);
        if (buffGroup.oper == <number>BuffOverlayProcessing.BuffOverlayProcessing_Offset) {
            this.mBuffArray.forEach(function (data) {
                if (data.Config.group == buffConf.group) {
                    this.RemoveBuff(data);
                }
            }.bind(this));

            this.AddNewBuff(buffConf, casterObjId);
        }
        else if (buffGroup.oper == <number>BuffOverlayProcessing.BuffOverlayProcessing_coexist) {
            this.AddNewBuff(buffConf, casterObjId);
        }
        else if (buffConf.liveStyle == <number>BuffOverlayProcessing.BuffOverlayProcessing_Overlay) {
            this.mBuffArray.forEach(function (data) {
                if (data.Config.ID == buffConf.ID) {
                    data.CD = buffConf.time;
                    data.AddLayers(1);
                }
            }.bind(this));
        }
        else if (buffGroup.oper == <number>BuffOverlayProcessing.BuffOverlayProcessing_Immunity) {

        }
    }

    private AddNewBuff(buffConf: BuffConfig, casterObjId: string) {
        let buff: Buff = new Buff(App.MathUtils.uuid(8, 10), casterObjId, this.entity.uid, buffConf);
        buff.Tigger();
        this.mBuffArray.push(buff);
        this.headComponent.addBuffItem(buff.Config.Icon, buff.Config.ID);
        //测试用代码
        //this.AddBuffEffect(buff.Config.ClientEffect, buff);
    }


    /**移除Buff */
    public RemoveBuff(value: Buff) {
        let index: number = this.mBuffArray.indexOf(value);
        if (index != -1) {
            delete this.mBuffArray[index];
            this.mBuffArray.splice(index, 1);
        }
        this.headComponent.removeBuffItem(value.Config.ID);
        this.RemoveBuffEffect(value.Config.effect);
        value.Destory();
        value = null;
    }

    /**播放Buff效果
    * @param id 
    * @param buff
    */
    public PlayBuffEffect(id: number, buff: Buff) {
        this.avatarEffectComponent.PlayEffect(id, buff.Config.effectPosType, AvatarEffectType.Buff);
    }

    public RemoveBuffEffect(id: number): void {
        this.avatarEffectComponent.RemoveEffect(id);
    }

    public UpdateBuffState(type: BuffTimeType = BuffTimeType.BuffTimeType_Begin, objectId: string = "") {
        this.mBuffArray.sort(function (a, b) {
            if (b.Config.settlePriority > a.Config.settlePriority) {
                return 1;
            } else {
                return -1;
            }
        });

        this.UpdateBuffDeath(type, objectId);
        this.UpdateBuffAccount(type, objectId);
        this.UpdateBuffCD(type, objectId);
    }

    /**施法者死亡的 */
    public UpdateBuffDeath(type: BuffTimeType, objectId: string){
         
        for (let i = 0; i < this.mBuffArray.length; i++) {
            let tempObj:MilitaryOfficerObject= App.FightManager.GetPlayerByUId(this.mBuffArray[i].CasterId);
             if(!tempObj){
                 if (this.mBuffArray[i].Config.settleType == 3 && type == BuffTimeType.BuffTimeType_Begin) { //施法者行动开始时
                     if (this.mBuffArray[i].OwnerId == objectId) {
                          this.mBuffArray[i].Accounting();

                            this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                        }
                     }
                 }else if (this.mBuffArray[i].Config.settleType == 4 && type == BuffTimeType.BuffTimeType_End) {//施法者行动结束时
                    if (this.mBuffArray[i].OwnerId == objectId) {
                              this.mBuffArray[i].Accounting();

                            this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                        }
                     }
                 }
            }
        }
    }

    /** 更新Buff结算*/
    public UpdateBuffAccount(type: BuffTimeType, objectId: string) {
        let num: number = this.mBuffArray.length;
        
        for (let i = 0; i < num; i++) {
            if (this.mBuffArray[i].Config.settleType == 1 && type == BuffTimeType.BuffTimeType_Begin) { //拥有者行动开始时
                if (this.mBuffArray[i].OwnerId == objectId) {
                    this.mBuffArray[i].Accounting();
                }
            }
            else if (this.mBuffArray[i].Config.settleType == 2 && type == BuffTimeType.BuffTimeType_End) {//拥有者行动结束时
                if (this.mBuffArray[i].OwnerId == objectId) {
                    this.mBuffArray[i].Accounting();
                }
            }
            else if (this.mBuffArray[i].Config.settleType == 3 && type == BuffTimeType.BuffTimeType_Begin) {//施法者行动开始时
                if (this.mBuffArray[i].CasterId == objectId) {
                    this.mBuffArray[i].Accounting();
                }
            }
            else if (this.mBuffArray[i].Config.settleType == 4 && type == BuffTimeType.BuffTimeType_End) {//施法者行动结束时
                if (this.mBuffArray[i].CasterId == objectId) {
                    this.mBuffArray[i].Accounting();
                }
            }

        }
        num = 0;
    }

    /**更新BuffCD */
    public UpdateBuffCD(type: BuffTimeType, objectId: string) {

        let num: number = this.mBuffArray.length;
        for (let i = 0; i < num; i++) {
            if (this.mBuffArray[i].CD != -1) {
                if (this.mBuffArray[i].Config.timeType == 1 && type == BuffTimeType.BuffTimeType_Begin) { //拥有者行动开始时
                    if (this.mBuffArray[i].OwnerId == objectId) {
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                            this.UpdateBuffCD(type, objectId);
                            num = null;
                            return;
                        }
                    }
                }
                else if (this.mBuffArray[i].Config.timeType == 2 && type == BuffTimeType.BuffTimeType_End) {//拥有者行动结束时
                    if (this.mBuffArray[i].OwnerId == objectId) {
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                            this.UpdateBuffCD(type, objectId);
                            num = null;
                            return;
                        }
                    }
                }
                else if (this.mBuffArray[i].Config.timeType == 3 && type == BuffTimeType.BuffTimeType_Begin) {//施法者行动开始时
                    if (this.mBuffArray[i].CasterId == objectId) {
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                            this.UpdateBuffCD(type, objectId);
                            num = null;
                            return;
                        }
                    }
                }
                else if (this.mBuffArray[i].Config.timeType == 4 && type == BuffTimeType.BuffTimeType_End) {//施法者行动结束时
                    if (this.mBuffArray[i].CasterId == objectId) {
                        this.mBuffArray[i].CD -= 1;
                        if (this.mBuffArray[i].CD == 0) {
                            this.RemoveBuff(this.mBuffArray[i]);
                            this.UpdateBuffCD(type, objectId);
                            num = null;
                            return;
                        }
                    }
                }
            }
        }
    }

    /**
     * 身上是否有眩晕buff
     */
    public IsDizziness(): boolean {
        for (let buf of this.BuffArray) {
            if (buf.ControlType == BuffControlType.BuffControlType_Dizziness) {
                return true;
            }
        }
        return false;
    }

    /**
     * 身上是否沉默buf
     */
    public IsSilence(): boolean {
        for (let buf of this.BuffArray) {
            if (buf.ControlType == BuffControlType.BuffControlType_Silence) {
                return true;
            }
        }
        return false;
    }

    public get BuffArray(): Buff[] {
        return this.mBuffArray;
    }
}

class AvatarBuffMovieClip extends MovieClipComponentBase {
    public constructor() {
        super()
    }

    public Init(gameResGroupName: string, mcpath: string, mcname: string, entity) {
        super.Init(gameResGroupName, mcpath, mcname, entity);
    }

    public start() {
        super.start();
    }

    public stop() {
        super.stop();
    }

    public update(advancetime: number) {
        super.update(advancetime);
        this.MovieClip.runAction(advancetime);
    }

    public complateAction(): void {
        super.complateAction();
    }
}