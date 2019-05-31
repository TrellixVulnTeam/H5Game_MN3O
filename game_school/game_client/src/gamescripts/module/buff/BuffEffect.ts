/**
 * 效果类型
 */
enum BuffEffecttype{
    /**
     * 属性修改
     */
    BuffEffecttype_ChangeAttr=1,
    /**
     * 持续伤害
     */
    BuffEffecttype_Dot=2,
    /**
     * 持续治疗
     */
    BuffEffecttype_AC=3,
}

/**
 * Buff属性修改方式
 */
enum BuffEffectChangeAttrType{
    /**
     * 定值
     */
    BuffEffectChangeAttrType_TheSpec=0,
    /**
     * 百分比
     */
    BuffEffectChangeAttrType_Percentage=1,
    /**
     * 定值加索引属性
     */
    BuffEffectChangeAttrType_TheSpecAndPercentage=2,
}
/**
 * created by sjz on 2018-5-11.
 * @class BuffEffect
 */
class BuffEffect
{
    private mId:number;
    private mConfig:BuffEffectConfig;
    private mEntity:MilitaryOfficerObject;  //自己
    private mCaster:MilitaryOfficerObject;  //施法者，即Buff添加者
    private mBuffStatistics:number[]=[];
    private mAdditionAuraEffect:AdditionAuraEffect;
    private mSkillMaicEffect:SkillEffect;   //结算效果Id
    private mType:BuffEffecttype;
    private mChangeAttrType:BuffEffectChangeAttrType;
    private mParent:Buff;

   public constructor(id:number,parent:Buff,entity:MilitaryOfficerObject,caster:MilitaryOfficerObject){

       for(var i=0 ; i< <number>EStatistic.STATISTIC_MAX; i++)
        {
            this.mBuffStatistics[i] = 0;
        }
        this.mId =id;
        this.mEntity = entity;
        this.mCaster = caster;
        this.mParent = parent;
        this.mConfig = BuffEffectConfig.GetConfig(id);
        this.mAdditionAuraEffect=new AdditionAuraEffect(id);
        this.mType = <BuffEffecttype>this.mConfig.type;
        this.Tigger();

   }

   public get Type(){
       return this.mType;
   }

   public get BuffStatistics(){
       return this.mBuffStatistics;
   }

   public get Config(){
       return this.mConfig;
   }

   /**
    * 更新Buff效果
    * 只更新buff效果附带的技能结算效果，属性修改的只在初次修改，之后不再修改
    */
   public Update(){
       if(this.mSkillMaicEffect != null){
           this.mSkillMaicEffect.Accounting();
       }
   }

    /**
     * 效果移除逻辑
     */
    public Destory(){
        this.mId=0;
        this.mConfig=null;
        this.mEntity=null;
        this.mBuffStatistics=null;
        this.mSkillMaicEffect=null;
        this.mAdditionAuraEffect=null;
    }

    /**
     * 效果触发
     */
    public Tigger(){
        if(!this.mEntity) return; 
        if(<BuffEffecttype>this.mConfig.type == BuffEffecttype.BuffEffecttype_ChangeAttr){
            let changenum:number= Number(this.mAdditionAuraEffect.GetField(this.mEntity.basicattr.Level,"para4"));
            if(<BuffEffectChangeAttrType>this.mConfig.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_TheSpec) //定值
            {
                this.mBuffStatistics[this.mConfig.para1] = changenum;
            }
            else if(<BuffEffectChangeAttrType>this.mConfig.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_Percentage)   //百分比
            {
                changenum = changenum / 100;
                this.mBuffStatistics[this.mConfig.para1] = changenum;
            }
            else if(<BuffEffectChangeAttrType>this.mConfig.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_Percentage)   //定值+索引属性
            {
                let indexproperty:number = this.mCaster.basicattr.GetCurrentValue(this.mConfig.para3) * this.mConfig.para5;         //索引者为施法者，即Buff添加者
                changenum = changenum + this.mEntity.basicattr.GetCurrentValue(this.mConfig.para1) + indexproperty;
                this.mBuffStatistics[this.mConfig.para1] = changenum;
                indexproperty=null;
            }
        }
        else if(<BuffEffecttype>this.mConfig.type == BuffEffecttype.BuffEffecttype_Dot){
            this.mSkillMaicEffect = new SkillEffect(this.mConfig.para1,this.mEntity,this.mCaster);
            this.mSkillMaicEffect.Accounting(this.mParent.Layers);
        }
        else if(<BuffEffecttype>this.mConfig.type == BuffEffecttype.BuffEffecttype_AC){
            this.mSkillMaicEffect = new SkillEffect(this.mConfig.para1,this.mEntity,this.mCaster);
            this.mSkillMaicEffect.Accounting(this.mParent.Layers);
        }
    }

}