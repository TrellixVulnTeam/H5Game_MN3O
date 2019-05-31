
enum EStatistic{
        /**活力 */	
        STATISTIC_VITALITY          = 0,	//活力
        /**智力 */
        STATISTIC_INTELLECT         = 1,	//智力
        /**力量 */
        STATISTIC_STRENGTH          = 2,	//力量
        /**敏捷 */	
        STATISTIC_AGILITY           = 3,	//敏捷
        /**一级属性占位4 */
        STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER4    = 4,    //一级属性占位4
        /**一级属性占位5 */
        STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER5    = 5,    //一级属性占位5
        /**一级属性占位6 */
        STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER6    = 6,    //一级属性占位6
        /**一级属性占位7 */
        STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER7    = 7,    //一级属性占位7
        /**一级属性占位8 */
        STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER8    = 8,    //一级属性占位8
        /**一级属性占位9 */
        STATISTIC_FIRSTLEVEL_ATTRIBUTES_PLACEHOLDER9    = 9,    //一级属性占位9
        /**生命值 */
        STATISTIC_LIFE              = 10,	//生命值
        /**预留魔法值 */
        STATISTIC_MANA,	                    //预留魔法值
        /**攻击力 */
        STATISTIC_DAMAGE            = 11,	//攻击力
        /**物理防御 */	
        STATISTIC_PHYSICAL_DEFENCE  = 12,	//物理防御
        /**魔法防御 */	
        STATISTIC_SPELL_DEFENCE     = 13,	//魔法防御
        /**伤害减免 */
        STATISTIC_DAMAGE_REDUCTION  = 14,   //伤害减免
        /**伤害加深 */
        STATISTIC_DEEPER_DAMAGE     = 15,   //伤害加深
        /**伤害公式预留6 */
        STATISTIC_DAMAGE_FORMULA_6  = 16,   //伤害公式预留6
        /**伤害公式预留7 */
        STATISTIC_DAMAGE_FORMULA_7  = 17,   //伤害公式预留7
        /**伤害公式预留8 */
        STATISTIC_DAMAGE_FORMULA_8  = 18,   //伤害公式预留8
        /**伤害公式预留9 */
        STATISTIC_DAMAGE_FORMULA_9  = 19,   //伤害公式预留9
        /**出手速度 */
        STATISTIC_SHOT_SPEED        = 20,   //出手速度
        /**暴击值 */
        STATISTIC_CRIT_AMOUNT       = 21,	//暴击值
        /**韧性值 */
		STATISTIC_TOUGHNESS_AMOUNT  = 22,	//韧性值
        /**暴击率 */
        STATISTIC_CRIT_CHANCE       = 23,	//暴击率
        /**韧性率 */
		STATISTIC_TOUGHNESS_CHANCE  = 24,   //韧性率
        /**暴击伤害 */
        STATISTIC_CRIT_DAMAGE       = 25,		    //暴击伤害
        /**暴击伤害减免 */
        STATISTIC_CRIT_REDUCED_AMOUNT   = 26,	    //暴击伤害减免
        /**治疗效果 */
        STATISTIC_TREATMENT_EFFECT  = 27,           //治疗效果
        /**连携技概率 */
        STATISTIC_LINKING_SKILLS_PROBABILITY = 28,  //连携技概率
        /**破甲临界血量比例 */
        SUNDER_CRITICAL_BLOOD_PROPORTION= 29,    //破甲临界血量比例  
        /**战斗公式预留30 */
        STATISTIC_FIGHT_FORMULA_30  = 30,    //战斗公式预留30
        /**战斗公式预留31 */
        STATISTIC_FIGHT_FORMULA_31  = 31,    //战斗公式预留31
        /**战斗公式预留32 */
        STATISTIC_FIGHT_FORMULA_32  = 32,    //战斗公式预留32
        /**战斗公式预留33 */
        STATISTIC_FIGHT_FORMULA_33  = 33,    //战斗公式预留33
        /**战斗公式预留34 */
        STATISTIC_FIGHT_FORMULA_34  = 34,    //战斗公式预留34
        /**战斗公式预留35 */
        STATISTIC_FIGHT_FORMULA_35  = 35,    //战斗公式预留35
        /**战斗公式预留36 */
        STATISTIC_FIGHT_FORMULA_36  = 36,    //战斗公式预留36
        /**战斗公式预留37 */
        STATISTIC_FIGHT_FORMULA_37  = 37,    //战斗公式预留37
        /**战斗公式预留38 */
        STATISTIC_FIGHT_FORMULA_38  = 38,    //战斗公式预留38
        /**战斗公式预留39 */
        STATISTIC_FIGHT_FORMULA_39  = 39,    //战斗公式预留39
        STATISTIC_MAX
}

class CreatureStatistics{
    
    public readonly CONVERT_SILVER_NUMBER:number = 100000; //银币转换
    public readonly MONEY_UNIT_NUMBER:number = 10000;    //货币单位数量
    public readonly MONEY_INFO_ID:number = 2314;         //万
    public readonly MAX_PLAYER_LEVEL:number = 99;        //人物最大等级
    public readonly CONVERT_EXP_NUMBER:number = 100000;  //转换经验值
    public readonly EXP_UNIT_NUMBER:number = 10000;

    protected mIsAutoFighting:boolean = false;		     //是否为自动战斗

    private mCurrentStaticValues:number[]=[<number> EStatistic.STATISTIC_MAX];
    private mStandardCriProb:number = 0.2;  //标准暴击率
    private mStandardCriMul:number = 2;     //标准暴击倍数
    private mLevel:number=0;              //当前等级
    private mGoldNum:number=0;            //金币数量
    private mDiamondNum:number=0;         //钻石数量
    private mPhysicalStrength:number=0;   //体力数量

    private name:string="";
    private titile:string;

    public constructor(){
        for(var i=0 ; i< <number>EStatistic.STATISTIC_MAX; i++)
        {
            this.SetCurrentValue(i,0);
        }
        this.mStandardCriProb=parseFloat( ClientConstConfig.GetConfig(1).value);
        this.mStandardCriMul=parseFloat(ClientConstConfig.GetConfig(2).value);
    }

    public get Name(){
        return this.name;
    }
    public set Name(value:string){
        this.name =value;
    }

    public get Title(){
        return this.titile;
    }
    public set Title(value:string){
        this.titile =value;
    }

    /**是否自动战斗 */
    public get IsAutoFighting():boolean{
        return this.mIsAutoFighting;
    }
    public set IsAutoFighting(value:boolean){
        this.mIsAutoFighting = value;
    }
    /**标准暴击率 */
    public get StandardCriProb():number{
        return this.mStandardCriProb;
    }
    /**标准暴击倍数 */
    public get StandardCriMul():number{
        return this.mStandardCriMul;
    }

    /**检测最终暴击率合法性 */
    public CheckUltimatelyCriProbIsLegal(value:number):boolean
    {
        if(value<=0.05){
            value=0.05;
        }

         if(value>=0.6){
            value=0.6;
         }
         
        if (App.RandomUtils.limitInteger(0, 100) <= value*100) {
            return true;
        }
        return false;
    }
    /**检测最终暴击系数合法性 */
    public CheckUltimatelyCriMulIsLegal(value:number):boolean{
        if(1.1 <= value && value >=5)
        {
            return true;
        }
        else{
            return false;
        }
    }

    public SetCurrentValue(index:EStatistic,value:number);
    public SetCurrentValue(index:number,value:number);
    public SetCurrentValue(index,value){
        if(typeof index == "number")
        {
            this.mCurrentStaticValues[index]=value;
        }
        else{
            this.mCurrentStaticValues[<number>index]=value;
        }
    }
    
    public GetCurrentValue(index:EStatistic):number;
    public GetCurrentValue(index:number):number;
    public GetCurrentValue(index){
        if(typeof index == "number")
        {
           return this.mCurrentStaticValues[index];
        }
        else{
           return this.mCurrentStaticValues[<number>index];
        }
    }


    public get OriHP():number
    {
        return this.GetCurrentValue(EStatistic.STATISTIC_VITALITY); 
    }

    public set OriHp(value){
        this.SetCurrentValue(EStatistic.STATISTIC_VITALITY,value);
    }
		
    public get HP():number
    {
       return Math.ceil( this.OriHP );
    }
    
    public get MaxHP():number
    {
        if(this.OriMaxHP < 1)
        {
            return 1;
        }else{
            return Math.ceil( this.OriMaxHP );
        }
    }

    public get OriMaxHP():number
    {
        return Math.max( this.mCurrentStaticValues[<number>EStatistic.STATISTIC_VITALITY], 1 );
    }

    public get OriMaxMP():number
    {
        return Math.max( this.mCurrentStaticValues[<number>EStatistic.STATISTIC_INTELLECT], 1 );
    }
    
    public get MaxMP():number
    {
        return Math.ceil( this.OriMaxMP );
    }

    public get OriMP()
    { 
        return this.GetCurrentValue(EStatistic.STATISTIC_INTELLECT);
    }
    public set OriMP(value:number){
        this.SetCurrentValue(EStatistic.STATISTIC_INTELLECT,value);
    }
    
    public get MP()
    {
        return Math.ceil( this.OriMP );
    }

    /**等级 */
    public get Level(){
        return this.mLevel;
    }
    public set Level(value:number){
        this.mLevel =value;
    }
    
    /**金币数量 */
    public get GoldNum():number{
        return this.mGoldNum;
    }
    public set GoldNum(value:number){
        this.mGoldNum=value;
    }

    /**钻石数量 */
    public get DiamondNum():number{
        return this.mDiamondNum;
    }
    public set DiamondNum(value:number){
        this.mDiamondNum =value;
    }

    /**体力 */
    public get PhysicalStrength(){
        return this.mPhysicalStrength;
    }
    public set PhysicalStrength(value:number){
        this.mPhysicalStrength=value;
    }
}