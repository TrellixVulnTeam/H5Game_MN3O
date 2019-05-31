
/**
 * 技能效果结算
 * @type 掩码
 */
enum MagicEffectClearingBits
{
    /**结算伤害 */
    Bits_SettlementDamage=0x01,
    /**结算治疗 */
    Bits_ClearingTreatment=0x02
}

/**
 * 技能效果驱散方式
 * @type 掩码
 */
enum MagicEffectDisperseCcontent
{
    /**驱散正面 */
    Disperse_TheFront=0x01,
    /**驱散负面 */
    Disperse_Negative=0x02,
    /**驱散中立 */
    Disperse_Neutral=0x03
}

/**结算类型 */
enum ClearingType{
    /**物理 */
    ClearingType_Physical=1,
    /**魔法 */
    ClearingType_Magic=2,
}

class SkillEffect
{
    private mSkillEffectid:number;
    private mConfig:MagicEffectConfig;
    private mTargetObj:MilitaryOfficerObject;
    private mOwnerObj:MilitaryOfficerObject;
    private targetS:MilitaryOfficerObject[]=[];
    private endCount:number=0;
    private mHurtPercentageModifiers:LevelModifiers = new LevelModifiers();	        //技能伤害百分比 - 等级修正
    private mHurtValueModifiers:LevelModifiers = new LevelModifiers();	            //技能伤害固定值 - 等级修正
    private mTreatmentPercentageModifiers:LevelModifiers = new LevelModifiers();    //技能治疗百分比 - 等级修正
    private mTreatmentValueModifiers:LevelModifiers = new LevelModifiers();         //技能治疗固定值 - 等级修正
    public constructor(id:number,target:MilitaryOfficerObject,owner:MilitaryOfficerObject){
        this.mSkillEffectid=id;
        this.mConfig = MagicEffectConfig.GetConfig(this.mSkillEffectid);
        this.mTargetObj = target;
        this.mOwnerObj = owner;
        this.mHurtPercentageModifiers.Load(this.mConfig.hurtPercentageMods);
        this.mHurtValueModifiers.Load(this.mConfig.hurtValueMods);
        this.mTreatmentPercentageModifiers.Load(this.mConfig.curePercentageMods);
        this.mTreatmentValueModifiers.Load(this.mConfig.cureValueMods);
    }

    /**
     * 技能效果结算
     * 顺序（驱散->加Buff->伤害/治疗）
     */
    public Accounting(bufflayers?:number,callback?:Function):void{
        this.targetS =this.GetmTargetObject(this.mTargetObj,this.mOwnerObj);
        this.endCount=0;

        if( this.targetS){
        for(let i=0; i<  this.targetS.length; i++){
            this.Disperse( this.targetS[i],this.mOwnerObj,function(){
                this.AddBuff( this.targetS[i],this.mOwnerObj,function(){
                    if(TestBits.TestMagicEffectBits(this.mConfig.effectBits,MagicEffectClearingBits.Bits_SettlementDamage))
                    {
                            this.Damage( this.targetS[i],this.mOwnerObj,0,callback);
                    }
                    else if(TestBits.TestMagicEffectBits(this.mConfig.effectBits,MagicEffectClearingBits.Bits_ClearingTreatment))
                    {
                            this.Treatment( this.targetS[i],this.mOwnerObj,0,callback);
                    }else{

                      this.endCount++;
                      if(this.endCount==this.targetS.length){
                      if(callback){
                           callback();
                      }   
                     }

                    }
                }.bind(this));
            }.bind(this));
        }
        }else{
              if(callback)
                 callback();
        }
    }

    /**驱散 */
    private Disperse(target:MilitaryOfficerObject,owner:MilitaryOfficerObject,callback?:Function):void{
        let buffCom:BuffComponent =<BuffComponent>target.getComponent(ComponentType.Buff);

        if(buffCom)
        {
            if(TestBits.TestDisperseCcontent(this.mConfig.dispelBit,MagicEffectDisperseCcontent.Disperse_TheFront))
            {
                buffCom.DisperseBuff(BuffFriendlyType.BUFFTYPE_POSITIVE,callback);
            }
            else if(TestBits.TestDisperseCcontent(this.mConfig.dispelBit,MagicEffectDisperseCcontent.Disperse_Neutral))
            {
                buffCom.DisperseBuff(BuffFriendlyType.BUFFTYPE_NEUTRAL,callback);
            }
            else if(TestBits.TestDisperseCcontent(this.mConfig.dispelBit,MagicEffectDisperseCcontent.Disperse_Negative))
            {
                buffCom.DisperseBuff(BuffFriendlyType.BUFFTYPE_NEGATIVE,callback);
            }
            else
            {
                if(callback)
                {
                    callback();              
                }
            }
        }
    }

    /**
     * 添加Buff
     * @param target 目标
     * @param owner 施法者
     */
    private AddBuff(target:MilitaryOfficerObject,owner:MilitaryOfficerObject,callback?:Function):void{
        if(!target){
            if(callback)
            callback();
            return;
        }

        for (let i = 0; i < this.mConfig.effect.length; i++) {
                   App.TimerManager.doTimer(this.mConfig.effectDelay[i], 1,
                        function () {
                             let effectCompont: AvatarEffectComponent = <AvatarEffectComponent>target.getComponent(ComponentType.AvatarEffect);   
                             if(effectCompont)                        
                                effectCompont.PlayEffect(this.mConfig.effect[i], this.mConfig.effectPosType[i], AvatarEffectType.Skill);
                        }.bind(this),
                        this, 0, null, this);
        }
        
        let buffCom:BuffComponent =<BuffComponent>target.getComponent(ComponentType.Buff);

        if(buffCom)
        {
            let isnothitbuff:boolean=true;
            if(this.mConfig.hitBuff1>0)
            {
                if(this.mConfig.hitBuffChance1 * 100 >= App.RandomUtils.limitInteger(0,100))
                {
                    buffCom.AddBuff(this.mConfig.hitBuff1,owner.uid,callback);
                    isnothitbuff=false;
                }
            }

            if(this.mConfig.hitBuff2>0)
            {
                if(this.mConfig.hitBuffChance2 * 100 >= App.RandomUtils.limitInteger(0,100))
                {
                    buffCom.AddBuff(this.mConfig.hitBuff2,owner.uid,callback);
                    isnothitbuff=false;
                }
            }

            if(this.mConfig.hitBuff3>0)
            {
                if(this.mConfig.hitBuffChance3 * 100 >= App.RandomUtils.limitInteger(0,100))
                {
                    buffCom.AddBuff(this.mConfig.hitBuff3,owner.uid,callback);
                    isnothitbuff=false;
                }
            }
              
        }
          if(callback){
             callback();
         }
    }
    
    /**
     * 伤害结算
     */
    private Damage(target:MilitaryOfficerObject,owner:MilitaryOfficerObject,bufflayers:number=0,callback:Function):void{
        if(target.Alive){
                 let isCRI:boolean=false;    //是否暴击
        let ownerStatistics:number[] = owner.RealTimeProperties;
        let targetStatistics:number[] =target.RealTimeProperties;
        //暴击率
        let CritRate:number = (ownerStatistics[<number>EStatistic.STATISTIC_CRIT_AMOUNT] + 100) / (ownerStatistics[<number>EStatistic.STATISTIC_CRIT_AMOUNT] + targetStatistics[<number>EStatistic.STATISTIC_TOUGHNESS_AMOUNT] + 2000) * 2 * owner.basicattr.StandardCriProb + ownerStatistics[<number>EStatistic.STATISTIC_CRIT_CHANCE] - targetStatistics[<number>EStatistic.STATISTIC_TOUGHNESS_CHANCE];
        //暴击系数
        let CritCoefficient:number=0;

        if(owner.basicattr.CheckUltimatelyCriProbIsLegal(CritRate))
        {
            CritCoefficient =  (ownerStatistics[<number>EStatistic.STATISTIC_CRIT_AMOUNT] + 1000) / (ownerStatistics[<number>EStatistic.STATISTIC_CRIT_AMOUNT] + 
            targetStatistics[<number>EStatistic.STATISTIC_TOUGHNESS_AMOUNT] + 2000) * 2 * (owner.basicattr.StandardCriMul - 1) + 1 + 
            ownerStatistics[<number>EStatistic.STATISTIC_CRIT_DAMAGE] - targetStatistics[<number>EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT];

            if(CritCoefficient<1.1)
            {
                CritCoefficient=1.1;
            }
            else if(CritCoefficient >5)
            {
                CritCoefficient=5;
            }
            isCRI=true;
        }
        else
        {
            CritCoefficient = 1;
        }

         //基础伤害
         let Basedamage = (ownerStatistics[<number>EStatistic.STATISTIC_DAMAGE]*//人物攻击
         ownerStatistics[<number>EStatistic.STATISTIC_DAMAGE] /  
         (ownerStatistics[<number>EStatistic.STATISTIC_DAMAGE] + 
         (<ClearingType>this.mConfig.additionalHurtType==ClearingType.ClearingType_Physical? //是否物理伤害
         targetStatistics[<number>EStatistic.STATISTIC_PHYSICAL_DEFENCE]*2://守方物理防御
         targetStatistics[<number>EStatistic.STATISTIC_SPELL_DEFENCE]*2))* //守方魔法防御
         (bufflayers?//buff层数
         this.HurtPercentageModifiers.Calc(owner.basicattr.Level,this.mConfig.hurtPercentage)*bufflayers/100://技能伤害百分比
         this.HurtPercentageModifiers.Calc(owner.basicattr.Level,this.mConfig.hurtPercentage)/100)+ 
         this.mHurtValueModifiers.Calc(owner.basicattr.Level,this.mConfig.hurtValue)) *//技能伤害固定值
         CritCoefficient;//暴击系数
    
        //计算最终伤害值
        //目标受击表现，状态结算 
        this.ActionClearing(target,owner,Basedamage,HurtType.Hurt,isCRI,callback);
        }else{
            this.endCount++;
            if(this.endCount==this.targetS.length){
                 if(callback){
                     callback();
             }   }
        }
       
    }

    /**
     * 治疗结算
     */
    private Treatment(target:MilitaryOfficerObject,owner:MilitaryOfficerObject,bufflayers:number=0,callback:Function):void{
        if(target.Alive){
         let ownerStatistics:number[] = owner.RealTimeProperties;
        let TreatmentEff:number = target.basicattr.GetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT);    //治疗效果

        let BasicTreatment = (ownerStatistics[<number>EStatistic.STATISTIC_DAMAGE] *(( bufflayers?this.mTreatmentPercentageModifiers.Calc(owner.basicattr.Level,
        this.mConfig.curePercentage) * bufflayers : this.mTreatmentPercentageModifiers.Calc(owner.basicattr.Level,this.mConfig.curePercentage))/100) * 
        0.5 + this.mTreatmentValueModifiers.Calc(owner.basicattr.Level,this.mConfig.cureValue)) * (1 + TreatmentEff);

        //加血
       this.ActionClearing(target,owner,BasicTreatment,HurtType.Gain,false,callback);   
        }else{
            this.endCount++;
            if(this.endCount==this.targetS.length){
                 if(callback){
                     callback();
                          }   }
        }
      
    }

    	/*
	 *回合结算
	 */
	public ActionClearing(target:MilitaryOfficerObject,owner:MilitaryOfficerObject,bloodLoss:number,type:HurtType,crit?:boolean,callback?:Function){
		if(target){
		let head:HeadComponent=	<HeadComponent> target.getComponent(ComponentType.Head);
		let beforeBlood:number= target.basicattr.GetCurrentValue(EStatistic.STATISTIC_LIFE);

		let currentBlood:number=0;
		let total:number;

		if(type==HurtType.Gain){
  		 currentBlood = beforeBlood+bloodLoss;
		 total=App.FightManager.GetCampTotalBlood(target.camp,bloodLoss);
		}else{
	     currentBlood = (beforeBlood-bloodLoss)<=0?0:(beforeBlood-bloodLoss);
 		 let realBlood:number=(beforeBlood-bloodLoss)<=0?beforeBlood:bloodLoss;
 		 total=App.FightManager.GetCampTotalBlood(target.camp,-realBlood);
         let proportion:number=  target.basicattr.GetCurrentValue(EStatistic.SUNDER_CRITICAL_BLOOD_PROPORTION);  
         proportion=proportion+owner.CreatureConf.break_strength-target.CreatureConf.break_resistance;

         if(currentBlood>0&& currentBlood<(target.basicattr.OriHP*proportion)){//受伤
                App.ActionManager.AddInjureList(target);
            }
	    }

		target.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE,currentBlood);

        App.TimerManager.doTimer(this.MConfig.delay,1,function(){   
            	App.FightManager.showHpChange(target,bloodLoss,type,crit);//跳血

                 head.changehpslider(currentBlood);//血条

                 App.EventMgrHelper.PushEvent(EventDef.UpdateHpBar,target.camp,total);

                if(currentBlood<=0)
                App.FightManager.removeplayer(target,false);//先从列表删掉，不销毁

                if(type==HurtType.Hurt){
                      let compont: DragonComponent = <DragonComponent>target.getComponent(ComponentType.Dragon);
                      let action:string="";
                    	if(currentBlood<=0){
                            compont.PlayAct(ActionStr.Die,1,function(){
                              
                                
                                target.Death();
                                this.endCount++;

                          if(this.endCount==this.targetS.length){
                              if(callback){
                                 callback();
                             }  
                         } 
                            }.bind(this));//播放死亡动画，销毁
	                	}else{

                        var endCallBack: Function = function () {
                            
                                 this.endCount++;

                          if(this.endCount==this.targetS.length){
                              if(callback){
                                 callback();
                              }  
                             } 
                          }.bind(this);

                            App.ActionManager.playerObjHurtExpression(target,this.mConfig.effect_colour,this.mConfig.effect_colour_time1,this.mConfig.effect_colour_time2);
                            compont.PlayAct(ActionStr.Hit1,1,endCallBack);
                            
                        }
                        
                }else{
                    this.endCount++;
                    if(this.endCount==this.targetS.length){
                    if(callback){
                     callback();
                    }   
                    }
                }
         }.bind(this),this );
		
		}
	}

    

    public get ID(){
        return this.mSkillEffectid;
    }

    private GetmTargetObject(mTargetObj:MilitaryOfficerObject,owner:MilitaryOfficerObject):MilitaryOfficerObject[]{
        let targetArray:MilitaryOfficerObject[] = [];
        if(this.mConfig.objectType==1)  //选择当前所选目标
        {
            targetArray.push(mTargetObj);
        }
        else if(this.mConfig.objectType==2) //所选目标及其后排
        {
            targetArray.push(mTargetObj);
            for(let i=0; i< App.FightManager.AllPlayers.length;i++)
            {
                if(App.FightManager.AllPlayers[i].camp == mTargetObj.camp)
                {
                    if(App.FightManager.AllPlayers[i].colnum == (mTargetObj.colnum+1) && App.FightManager.AllPlayers[i].rownum == mTargetObj.rownum)
                    {
                        targetArray.push(App.FightManager.AllPlayers[i]);
                        break;
                    }
                }
            }
        }
        else if(this.mConfig.objectType==3) //所选目标后排
        {
            for(let i=0; i< App.FightManager.AllPlayers.length;i++)
            {
                if(App.FightManager.AllPlayers[i].camp == mTargetObj.camp)
                {
                    if(App.FightManager.AllPlayers[i].colnum == (mTargetObj.colnum+1) && App.FightManager.AllPlayers[i].rownum == mTargetObj.rownum)
                    {
                        targetArray.push(App.FightManager.AllPlayers[i]);
                        break;
                    }
                }
            }
        }
        else if(this.mConfig.objectType==4) //选择敌方目标
        {
            let enemy:MilitaryOfficerObject[] = [];
            for(let i=0; i< App.FightManager.AllPlayers.length;i++)
            {
                if(App.FightManager.AllPlayers[i].camp != owner.camp && App.FightManager.AllPlayers[i]!= owner)
                {
                    enemy.push(App.FightManager.AllPlayers[i]);
                }
            }

            if(this.mConfig.objectType2==1) //随机X体
            {
                targetArray = App.RandomUtils.randomArrayInterval(enemy,this.mConfig.objectNum);
            }
            else if(this.mConfig.objectType2==2)    //后排随机X体
            {
                let backPlayers:MilitaryOfficerObject[] = [];
                for(let i=0;i<enemy.length;i++){
                    if(enemy[i].colnum== 1)
                    {
                        backPlayers.push(enemy[i]);
                    }
                }
                if(backPlayers.length == 0){    //后排死光，将前排视为后排
                    for(let i=0;i<enemy.length;i++){
                        if(enemy[i].colnum== 0)
                        {
                            backPlayers.push(enemy[i]);
                        }
                    }
                }
                targetArray = App.RandomUtils.randomArrayInterval(backPlayers,this.mConfig.objectNum);
                backPlayers=null;
            }
            else if(this.mConfig.objectType2==3)    //前排随机X体
            {
                let frontPlayers:MilitaryOfficerObject[] = [];
                for(let i=0;i<enemy.length;i++){
                    if(enemy[i].colnum==0)
                    {
                        frontPlayers.push(enemy[i]);
                    }
                }
                if(frontPlayers.length == 0){   //前排死光，将后排视为前排
                    for(let i=0;i<enemy.length;i++){
                        if(enemy[i].colnum== 1)
                        {
                            frontPlayers.push(enemy[i]);
                        }
                    }
                }
                targetArray = App.RandomUtils.randomArrayInterval(frontPlayers,this.mConfig.objectNum);
                frontPlayers=null;
            }
            else if(this.mConfig.objectType2==4)    //生命比例最少的单位
            {
                enemy.sort(function(a,b){
                    if((a.basicattr.HP/a.basicattr.MaxHP)<(b.basicattr.HP/b.basicattr.MaxHP))
                    {
                        return 1;
                    }else{
                        return -1;
                    }
                })
                targetArray.push(enemy[0]);
            }
            enemy=null;
        }
        else if(this.mConfig.objectType==5) //选择己方目标
        {
            let owners:MilitaryOfficerObject[] = [];
            for(let i=0; i< App.FightManager.AllPlayers.length;i++)
            {
                if(App.FightManager.AllPlayers[i].camp == owner.camp )//&& App.FightManager.AllPlayers[i]!= owner)
                {
                    owners.push(App.FightManager.AllPlayers[i]);
                }
            }
            if(this.mConfig.objectType2==1) //随机X体
            {
                targetArray = App.RandomUtils.randomArrayInterval(owners,this.mConfig.objectNum);
            }
            else if(this.mConfig.objectType2==2)    //后排随机X体
            {
                let backPlayers:MilitaryOfficerObject[] = [];
                for(let i=0;i<owners.length;i++){
                    if(owners[i].colnum== 1)
                    {
                        backPlayers.push(owners[i]);
                    }
                }
                 if(backPlayers.length == 0){    //后排死光，将前排视为后排
                    for(let i=0;i<owners.length;i++){
                        if(owners[i].colnum== 0)
                        {
                            backPlayers.push(owners[i]);
                        }
                    }
                }
                targetArray = App.RandomUtils.randomArrayInterval(backPlayers,this.mConfig.objectNum);
                backPlayers=null;
            }
            else if(this.mConfig.objectType2==3)    //前排随机X体
            {
                let frontPlayers:MilitaryOfficerObject[] = [];
                for(let i=0;i<owners.length;i++){
                    if(owners[i].colnum==0)
                    {
                        frontPlayers.push(owners[i]);
                    }
                }
                if(frontPlayers.length == 0){   //前排死光，将后排视为前排
                    for(let i=0;i<owners.length;i++){
                        if(owners[i].colnum== 1)
                        {
                            frontPlayers.push(owners[i]);
                        }
                    }
                }
                targetArray = App.RandomUtils.randomArrayInterval(frontPlayers,this.mConfig.objectNum);
                frontPlayers=null;
            }
            else if(this.mConfig.objectType2==4)    //生命比例最少的单位
            {
                owners.sort(function(a,b){
                    if((a.basicattr.HP/a.basicattr.MaxHP)<(b.basicattr.HP/b.basicattr.MaxHP))
                    {
                        return 1;
                    }else{
                        return -1;
                    }
                })
                targetArray.push(owners[0]);
            }
            owners=null;
        }
        else if(this.mConfig.objectType==6) //选择自己
        {
            targetArray.push(owner);
        }
        return targetArray;
    }

    /**技能伤害百分比 - 等级修正 */
    public get HurtPercentageModifiers(){
        return this.mHurtPercentageModifiers;
    }
    /**技能伤害固定值 - 等级修正 */
    public get HurtValueModifiers(){
        return this.mHurtValueModifiers;
    }
    /**技能治疗百分比 - 等级修正 */
    public get TreatmentPercentageModifiers(){
        return this.mTreatmentPercentageModifiers;
    }
    /**技能治疗固定值 - 等级修正 */
    public get TreatmentValueModifiers(){
        return this.mTreatmentValueModifiers;
    }
    /**计算表格 */
    public get MConfig(){
        return this.mConfig;
    }

}