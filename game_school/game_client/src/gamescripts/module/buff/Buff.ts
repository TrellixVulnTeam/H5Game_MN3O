/**Buff类型 */
enum BuffFriendlyType{
    /**良性效果 */
    BUFFTYPE_POSITIVE=0,
    /**负面效果 */
    BUFFTYPE_NEGATIVE=1,
    /**中立效果 */
    BUFFTYPE_NEUTRAL=2,
}

/**Buff共存逻辑类型 */
enum BuffOverlayProcessing
{
    /**冲抵 */
    BuffOverlayProcessing_Offset=1,
    /**免疫 */
    BuffOverlayProcessing_Immunity=2,
    /**共存 */
    BuffOverlayProcessing_coexist=3,
    /**叠加 */
    BuffOverlayProcessing_Overlay=4,

}

/**Buff驱散类型 */
enum BuffDisperseType{
    /**不可驱散 */
    BuffDisperseType_NotDis=0,
    /**可驱散 */
    BuffDisperseType_CanDis=1,
}

/**Buff控制类型 */
enum BuffControlType{
    /**眩晕 */
    BuffControlType_Dizziness=0x01,
    /**沉默 */
    BuffControlType_Silence=0x01,
}

/**
 * created by sjz on 2018-5-10.
 * Buff
 */
class Buff
{      
    private mBuffeffectArray:BuffEffect[];          //效果集合
    private mCasterId:string;                       //Buff施法者Id
    public get CasterId(): string {
        return this.mCasterId;
    }
    private mOwnerId:string;                        //Buff作用者Id
    public get OwnerId(): string {
        return this.mOwnerId;
    }
    private mConfig:BuffConfig;                     //Buff表
    private mCd:number;                             //CD
    private mFriendlyType:BuffFriendlyType;         //友好度类型
    private mDispleType:BuffDisperseType;           //被驱散性质类型
    private mControlType:BuffControlType;           //控制类型
    private mUid:number;                            //唯一ID
    private mLayers:number;                         //当前叠加层数
    private mMaxLayers:number;                      //最大叠加层数

    public constructor(uid:any,casterid:string,ownerid:string,buffconf:BuffConfig)
    {
        this.mUid=uid;
        this.mCasterId=casterid;
        this.mOwnerId=ownerid;
        this.mBuffeffectArray=new Array<BuffEffect>();
        this.mConfig=buffconf;
        this.mFriendlyType=buffconf.friendlyLevel;
        this.mDispleType =buffconf.dispelType;
        if(TestBits.TestBuffControlTypeBits(buffconf.controlBit,BuffControlType.BuffControlType_Dizziness)){
            this.mControlType= BuffControlType.BuffControlType_Dizziness;
        }
        else if(TestBits.TestBuffControlTypeBits(buffconf.controlBit,BuffControlType.BuffControlType_Silence)){
            this.mControlType= BuffControlType.BuffControlType_Silence;
        }

        this.mMaxLayers= this.mConfig.maxLayers;
        this.mLayers=this.mConfig.defaultLayers;
        this.mCd = this.mConfig.time;
    }

    public Destory(){
        this.DestoryBuffEffect();
    }
    public get UID(){
        return this.mUid;
    }

    public get BuffEffectArray(){
        return this.mBuffeffectArray;
    }

    public get Config(){
        return this.mConfig;
    }

    /**-1代表永久 */
    public get CD(){
        return this.mCd;
    }
    public set CD(value:number){
        this.mCd= value <=0?0:value;
    }

    /**友好度类型 */
    public get FriendlyType():BuffFriendlyType{
        return this.mFriendlyType;
    }
    /**控制类型 */
    public get ControlType():BuffControlType{
        return this.mControlType;
    }
    /**驱散性质 */
    public get DisperseType():BuffDisperseType{
        return this.mDispleType;
    }

    /**叠加层数 */
    public get Layers(){
        return this.mLayers;
    }

    /**增加叠加层数 */
    public AddLayers(value:number):void{
        let layers:number= value+this.mLayers;
        if(layers > this.mMaxLayers){
            layers= this.mMaxLayers;
        }
        this.mLayers = layers;
    }

    public Tigger(callback?:Function){
        this.AddBuffEffect();
    }

    private AddBuffEffect(callback?:Function){
        if(this.mConfig.effectID1 != -1){
            let buffEffect1:BuffEffect=new BuffEffect(this.mConfig.effectID1,this,App.FightManager.GetPlayerByUId(this.mOwnerId),App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect1);
        }
        if(this.mConfig.effectID2 !=-1){
            let buffEffect2:BuffEffect=new BuffEffect(this.mConfig.effectID2,this,App.FightManager.GetPlayerByUId(this.mOwnerId),App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect2);
        }
        if(this.mConfig.effectID3 !=-1){
            let buffEffect3:BuffEffect=new BuffEffect(this.mConfig.effectID3,this,App.FightManager.GetPlayerByUId(this.mOwnerId),App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect3);
        }
        if(this.mConfig.effectID4 !=-1){
            let buffEffect4:BuffEffect=new BuffEffect(this.mConfig.effectID4,this,App.FightManager.GetPlayerByUId(this.mOwnerId),App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect4);
        }
        if(this.mConfig.effectID5 !=-1){
            let buffEffect5:BuffEffect=new BuffEffect(this.mConfig.effectID5,this,App.FightManager.GetPlayerByUId(this.mOwnerId),App.FightManager.GetPlayerByUId(this.mCasterId));
            this.BuffEffectArray.push(buffEffect5);
        }
        if(this.mConfig.effect != null){
            //预留 客户端表现
            let entity :GameObject = App.FightManager.GetPlayerByUId(this.mOwnerId);
            if (entity) {
            let compont: BuffComponent = <BuffComponent>entity.getComponent(ComponentType.Buff);                      
                compont.PlayBuffEffect(this.mConfig.effect, this);   //播放特效            
            }
        }
    }

    /**
     * 移除当前buff所有表现
     */
    private DestoryBuffEffect(){
        for(let i=0; i< this.mBuffeffectArray.length;i++){
            this.mBuffeffectArray[i].Destory();
            delete this.mBuffeffectArray[i];
        }
        this.mBuffeffectArray.slice(0,this.mBuffeffectArray.length);
    }

    public Accounting(){
        for(let i =0; i< this.mBuffeffectArray.length; i++){
            this.mBuffeffectArray[i].Update();
        }
    }

}