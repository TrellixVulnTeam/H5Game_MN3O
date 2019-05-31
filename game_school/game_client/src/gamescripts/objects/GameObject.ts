/**
 * 阵营
 */
enum Camp{
    /**友好 */
    Friendly=0,
    /**中立 */
    Neutral=1,
    /**敌对 */
    Hostility=2,
}

enum ClientBits{
    CLIENT_BIT_DEAD=0,          //死亡
    CLIENT_BIT_MOVING,          //移动
    CLIENT_BIT_CASTING,         //僵直
    CLIENT_BIT_SKILL_ACTIVATE,  //技能激活
    CLIENT_BIT_CANNOT_MOVE,     //不可移动
    CLIENT_BIT_SLIENT,          //沉默
    CLIENT_BIT_TALKING,         //对话
    CLIENT_BIT_COMBAT,          //战斗中
    CLIENT_BIT_PLOT_CANNOTMOVE, //剧情，不可移动
}


/**
 * created by sjz 2018-5-9.
 * 模型基类
 */
class GameObject
{
    /**组件*/
    private _components:any;
    /**唯一ID*/
    public uid:string;
    /**modelId */
    public modelId:number;
    /**世界坐标 */
    public position:egret.Point=new egret.Point();
    /** 初始化世界坐标 用于移动之后走回来 这个坐标初始化之后就不在改变 初始化请用下面的 initPosition*/
    private startPosition: egret.Point = new egret.Point();
    /**行 */
    public rownum:number;
    /**列 0->前排 1->后排 */
    public colnum:number;
    /**技能表现文件名称 */
    public skillName:string;
    /**技能表现文件路径，json文件 */
    public skilleffpath:string;

    /**BUFF表现文件名称 */
    public buffName:string;
    /**BUFF表现文件路径，json文件 */
    public buffeffpath:string;

    /**动作表现文件名称*/
    public avatarName:string;  
    /**动作表现文件路径，json文件 */
    public avatarPath:string;
    /**朝向（分为8个方向，目前只用到了左右） */
    public dir:Dir;
    /**动作名称（需要提前加载动作资源，即: mcPath+mcName） */
    public action:string;
    /**基本属性数据 */
    public basicattr: CreatureStatistics;
    /**阵营 */
    public camp:Camp;
    /**战斗视图层 */
    public gameView:egret.DisplayObjectContainer;
    /**原始模型缩放 */
    public oriScale:number;

    public battleObj: GameObject;
    /**站位管理*/
    public  posInfo:BattlePosition;
   
    private mClientBit:MyBitset = new MyBitset(32); 
    /**角色模板表, 所有怪物数据初始化,都要强制走这个表*/
    private creatureSpawnConf:CreatureSpawnConfig;
    /**角色表*/
    private creatureConf:CreatureTempletConfig;
    /**模型表 */
    private modelConf:ModelConfig;
    /**是否在摄像机统照范围内，留于以后好扩展 */
    private _inCamera: boolean;
     /**龙骨*/
    public mDragon:DragonObjectBase;
    
   
    public get StartPosition():egret.Point
    {
        return this.startPosition;
    }

    public constructor()
    {
        this._components={};
       
    }

    public init(id:number,posinfo:BattlePosition, camp:Camp, gameView:egret.DisplayObjectContainer,data?:any):void
    {  
        
        this.uid=App.MathUtils.uuid(10,16);
        this.basicattr=new CreatureStatistics();

        /*
          CreatureSpawnConfig表通过这个ID来获取,CreatureTempletConfig 表要用CreatureSpawnConfig 里面的templet字段来获取
          CreatureTempletConfig 表里的数据现在已经是属于一种模板数据了,实际的最终数据,要通过CreatureSpawnConfig表来计算一次
          实际的数据处理,在下面初始化数据的时候真正处理,需要依赖的两张表是  CreatureAttrForceConfig(强制数据表) 和 CreatureAttrTypeConfig
        */
        
        if(camp==Camp.Friendly)
        {
             this.modelId=id;
           this.creatureConf=CreatureTempletConfig.GetConfig(id);
        }
        else if(camp==Camp.Hostility) //敌人强制走下面的初始化数据
        {
            this.creatureSpawnConf= CreatureSpawnConfig.GetConfig(id); 
            this.modelId=this.creatureSpawnConf.templet;
            this.creatureConf=CreatureTempletConfig.GetConfig(this.creatureSpawnConf.templet);
        }     

        this.modelConf=ModelConfig.GetConfig(this.creatureConf.model);

        this.avatarPath = GameobjConst.McPath;
        this.avatarName=this.modelConf.filename;
       
        
        this.oriScale=this.modelConf.size;
        
        this.skilleffpath = GameobjConst.SkillEffectFilePath;
        this.skillName=GameobjConst.SkillName;

        this.buffeffpath = GameobjConst.Buffeffpath;
        this.buffName=GameobjConst.BuffName;

        this.gameView = gameView;
        this.action = Action.Stand;
        
        this.camp=camp;

        if(camp==Camp.Friendly)
            this.dir =  Dir.Left;
        else
            this.dir =  Dir.Right;

        this.posInfo=posinfo;
        
        this.initPosition();

        if(camp==Camp.Friendly)
        {
            //目前data是己方数据的增幅比例
            this.InitOwnBasicattr(<number>data);     //己方的数据独立处理
        }
        else if(camp==Camp.Hostility) //敌人强制走下面的初始化数据
        {
            this.InitEnemyBasicattr();
        }        
    }

    /**事件监听 */
    public RegisEventListener(eventType:string,event:Function){
        let avater:AvatarComponent=  <AvatarComponent>this.getComponent(ComponentType.Avatar);
     if(avater){
          avater.AvatarMovieClip.RegisEventListener(eventType,event);
       }
    } 

    /**删除事件监听 */
    public RemoveEventListener(eventType:string,event?:Function){
        let avater:AvatarComponent=  <AvatarComponent>this.getComponent(ComponentType.Avatar);
     if(avater){
          avater.AvatarMovieClip.RemoveEventListener(eventType,event);
       }
    } 

    /**修改父物体 */
    public ChangeParent(view:egret.DisplayObjectContainer){
        let avater:AvatarComponent=  <AvatarComponent>this.getComponent(ComponentType.Avatar);
     if(avater){
          avater.AvatarMovieClip.ChangeParent(view);
       }
    } 

    /**删除所有事件监听 */
    public RemoveAllEventListener(){
       let avater:AvatarComponent=  <AvatarComponent>this.getComponent(ComponentType.Avatar);
     if(avater){
          avater.AvatarMovieClip.RemoveAllEventListener();
       }
    }


    public initPosition():void
    {
        this.position.x = this.posInfo. Pos.x;
        this.position.y = this.posInfo. Pos.y;
        
        this.startPosition.x = this.posInfo.Pos.x;
        this.startPosition.y = this.posInfo.Pos.y;
        this.colnum = this.posInfo.SelfArrAnger;
        this.rownum = this.posInfo.LineNum;

    }

    public InitOwnBasicattr(awardAttr : number = 1)
    {
        this.basicattr.Name=this.creatureConf.name;
        this.basicattr. Title="[111]";
        //有六个属性可能有加成,其中,速度不享受加成,目前是这样的  
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE,this.GetValue(this.creatureConf.life,awardAttr));
        this.basicattr.OriHp=this.creatureConf.life;
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_DAMAGE,this.GetValue(this.creatureConf.damage,awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_PHYSICAL_DEFENCE,this.GetValue(this.creatureConf.physical_defence,awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SPELL_DEFENCE,this.GetValue(this.creatureConf.spell_defence,awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_AMOUNT,this.GetValue(this.creatureConf.crit_amount,awardAttr));
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_AMOUNT,this.GetValue(this.creatureConf.toughness_amout,awardAttr));    

        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED,this.creatureConf.shot_speed);

        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_CHANCE,this.creatureConf.crit_chance);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_CHANCE,this.creatureConf.toughness_chance);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_DAMAGE,this.creatureConf.crit_damage);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT,this.creatureConf.crit_reduced_amount);
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT,this.creatureConf.treatment_effect);   
        this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LINKING_SKILLS_PROBABILITY,this.creatureConf.linking_skills_probability);  
    
    }


     public InitEnemyBasicattr()
     {
        this.basicattr.Name=this.creatureConf.name;
        this.basicattr. Title="[111]";
        /* 
        attrMethod =1 使用CreatureAttrTypeConfig表
        attrMethod =/ CreatureAttrForceConfig(强制数据表)
        */
        if(this.creatureSpawnConf.attrMethod == 1)
        {  
            // CreatureAttrTypeConfig 表ID = attrID*1000 * level ,最后结果是六位数的ID,有问题找策划
            let id :number  =  (this.creatureSpawnConf.attrID * 1000) + this.creatureSpawnConf.level;    
            let creatureAttrTypeConfig : CreatureAttrTypeConfig = CreatureAttrTypeConfig.GetConfig(id);
            //最大生命 攻击力 物理防御 魔法防御 暴击值 韧性值 速度 这几个是乘法
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE,  this.GetValue(this.creatureConf.life,creatureAttrTypeConfig.life));
            this.basicattr.OriHp=this.creatureConf.life;
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_DAMAGE,this.GetValue(this.creatureConf.damage,creatureAttrTypeConfig.damage));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_PHYSICAL_DEFENCE,this.GetValue(this.creatureConf.physical_defence,creatureAttrTypeConfig.physical_defence));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SPELL_DEFENCE,this.GetValue(this.creatureConf.spell_defence,creatureAttrTypeConfig.spell_defence));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_AMOUNT,this.GetValue(this.creatureConf.crit_amount,creatureAttrTypeConfig.crit_amount));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_AMOUNT,this.GetValue(this.creatureConf.toughness_amout,creatureAttrTypeConfig.toughness_amout));
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED,this.GetValue(this.creatureConf.shot_speed,creatureAttrTypeConfig.shot_speed));

            //下面的值是加法
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_CHANCE,this.creatureConf.crit_chance + creatureAttrTypeConfig.crit_chance);
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_CHANCE,this.creatureConf.toughness_chance + creatureAttrTypeConfig.toughness_chance);
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_DAMAGE,this.creatureConf.crit_damage + creatureAttrTypeConfig.crit_damage);
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT,this.creatureConf.crit_reduced_amount + creatureAttrTypeConfig.crit_reduced_amount);
            this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT,this.creatureConf.treatment_effect + creatureAttrTypeConfig.treatment_effect);  
        }
        else
        {   //使用的是强制数据
            let creatureAttrForceConf : CreatureAttrForceConfig = CreatureAttrForceConfig.GetConfig(this.creatureSpawnConf.attrID);
            if(creatureAttrForceConf != null)
            {   
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE,creatureAttrForceConf.life);
                this.basicattr.OriHp=creatureAttrForceConf.life;
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_DAMAGE,creatureAttrForceConf.damage);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_PHYSICAL_DEFENCE,creatureAttrForceConf.physical_defence);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SPELL_DEFENCE,creatureAttrForceConf.spell_defence);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_AMOUNT,creatureAttrForceConf.crit_amount);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_AMOUNT,creatureAttrForceConf.toughness_amout);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED,creatureAttrForceConf.shot_speed);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_CHANCE,creatureAttrForceConf.crit_chance);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_CHANCE,creatureAttrForceConf.toughness_chance);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_DAMAGE,creatureAttrForceConf.crit_damage);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT,creatureAttrForceConf.crit_reduced_amount);
                this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT,creatureAttrForceConf.treatment_effect);  
            }
        }
     /*
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_LIFE,this.creatureConf.life);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_DAMAGE,this.creatureConf.damage);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_PHYSICAL_DEFENCE,this.creatureConf.physical_defence);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SPELL_DEFENCE,this.creatureConf.spell_defence);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_AMOUNT,this.creatureConf.crit_amount);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_AMOUNT,this.creatureConf.toughness_amout);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_SHOT_SPEED,this.creatureConf.shot_speed);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_CHANCE,this.creatureConf.crit_chance);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TOUGHNESS_CHANCE,this.creatureConf.toughness_chance);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_DAMAGE,this.creatureConf.crit_damage);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_CRIT_REDUCED_AMOUNT,this.creatureConf.crit_reduced_amount);
     this.basicattr.SetCurrentValue(EStatistic.STATISTIC_TREATMENT_EFFECT,this.creatureConf.treatment_effect);  
     */
    }
    
    /**
     * 封装一层是因为这个乘法结果如果是0,哪需要给一个默认值,默认值是1,有变化找策划
     *  basicValue CreatureTempletConfig表里面的值  changeValue CreatureSpawnConfig表里面的比例值
     */
    private GetValue(basicValue : number ,changeValue : number) : number 
    {
        let result :number = 0;
        result = Math.floor(basicValue*changeValue);  //取整方式为下取整,策划说的
        if(result == 0)
            result = 1;
        return result;    
    }

    public Death():void
    {
       let avatarCom:DragonComponent= this.getComponent(ComponentType.Dragon)as DragonComponent;
       if(avatarCom&&this.gameView){
          let index= this.gameView.getChildIndex(avatarCom.Body);
          if(index!=-1){
                this.gameView.removeChildAt(index);
          }
       }

        this.RemoveAllEventListener();
        let componentNames: string[] = Object.keys(this._components);
        while (componentNames.length) {
            let componentName: string = componentNames[0];
            this.removeComponent(componentName); 
            componentNames = Object.keys(this._components);
        }
        
        this.mClientBit.SetBitSet(<number>ClientBits.CLIENT_BIT_DEAD,true);
        this.gameView = null;
        this.battleObj = null;
        this.basicattr = null;
    }
    
    public addComponent(componentName: string): Component {
        if (this._components[componentName]) {
            return null;
        }

        let component: Component = ObjectPool.pop(componentName);
        component.type = componentName;
        component.entity = this;
        component.start();

        ComponentSystem.addComponent(component);

        this._components[componentName] = component;
        return component;
    }

    public removeComponent(componentName: string): void {
        let component: Component = this._components[componentName];
        if (!component) {
            return;
        }
       
        ComponentSystem.removeComponent(component);
 		component.stop();     
        ObjectPool.push(component);
        this._components[componentName] = null;
        delete this._components[componentName];
    }

    public getComponent(componentName: string): Component {
        let hasComponent: Component = this._components[componentName];
        return hasComponent;
    }


    public setInCamera(value: boolean) {
        this._inCamera = value;
    }

    public getInCamera(): boolean {
        return this._inCamera;
    }

    /**实时属性 */
    public get RealTimeProperties():number[]{
        let result:number[]=[];
        
        let ownerBuffArray:Buff[] = (<BuffComponent>this.getComponent(ComponentType.Buff)).BuffArray;
        let buffeffattrpercentage:number[] = [];    //BuffEffect修改属性 - 百分比修改
        let buffeffattrValue:number[] = [];         //BuffEffect修改属性 - 固定值修改
        let buffeffattrvalueandper:number[] = [];   //BuffEffect修改属性 - 索引属性修改

        for(let i=0; i< <number>EStatistic.STATISTIC_MAX; i++){
            buffeffattrpercentage[i]=0;
        }
        for(let i=0; i< <number>EStatistic.STATISTIC_MAX; i++){
            buffeffattrValue[i]=0;
        }
        for(let i=0; i< <number>EStatistic.STATISTIC_MAX; i++){
            buffeffattrvalueandper[i]=0;
        }

        for(let i=0;  i<ownerBuffArray.length; i++){
            for(let j=0; j< ownerBuffArray[i].BuffEffectArray.length; j++){
                 if(ownerBuffArray[i].BuffEffectArray[j].Type == BuffEffecttype.BuffEffecttype_ChangeAttr)
                 {
                    for(let k=0; k< <number>EStatistic.STATISTIC_MAX; k++){
                        if(<BuffEffectChangeAttrType>ownerBuffArray[i].BuffEffectArray[j].Config.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_TheSpec) //定值
                        {
                            buffeffattrValue[k] += ownerBuffArray[i].BuffEffectArray[j].BuffStatistics[k];
                        }
                        else if(<BuffEffectChangeAttrType>ownerBuffArray[i].BuffEffectArray[j].Config.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_Percentage)   //百分比
                        {
                            buffeffattrpercentage[k] += (ownerBuffArray[i].BuffEffectArray[j].BuffStatistics[k]);
                        }
                        else if(<BuffEffectChangeAttrType>ownerBuffArray[i].BuffEffectArray[j].Config.para2 == BuffEffectChangeAttrType.BuffEffectChangeAttrType_Percentage)   //定值+索引属性
                        {
                            buffeffattrvalueandper[k] += ownerBuffArray[i].BuffEffectArray[j].BuffStatistics[k];
                        }
                    }
                }
            }
        }

        for(let i=0; i< <number>EStatistic.STATISTIC_MAX; i++){
            if(buffeffattrpercentage[i]==0)
            {
                result[i] = this.basicattr.GetCurrentValue(i) * 1;
            }
            else
            {
                result[i] = this.basicattr.GetCurrentValue(i) * (buffeffattrpercentage[i]+1);
            }
        }

        for(let i=0; i< <number>EStatistic.STATISTIC_MAX; i++){
            result[i] += buffeffattrValue[i];
        }

        for(let i=0; i< <number>EStatistic.STATISTIC_MAX; i++){
            result[i] += buffeffattrvalueandper[i];
        }
        for(let i=0; i< <number>EStatistic.STATISTIC_MAX; i++){
            let conf:AttributeFormatConfig = AttributeFormatConfig.GetConfig(i);
            if(result[i]<0){
                if(conf.canBeNegative==0){
                    result[i]=0;
                }
            }
        }
        return result;
    }

    public get Alive():boolean
    {
        return !this.mClientBit.GetBitset(<number>ClientBits.CLIENT_BIT_DEAD);
    }

    public get IsDead():boolean
    {
        return this.mClientBit.GetBitset(<number>ClientBits.CLIENT_BIT_DEAD);
    }
    
    public get ClientBit(){
        return this.mClientBit;
    }

    public get CreatureConf():CreatureTempletConfig{
         return this.creatureConf;
    }

    public AddClientBitState(bit:ClientBits):void
    {
        if ( !this.TestClientBitState (bit))
        {
            this.mClientBit.SetBitSet(<number>bit,true);
            this.OnClientBitsetChanged ( bit );
        }
    }
    public  DelClientBitState(bit:ClientBits):void
    {
        if ( this.TestClientBitState(bit))
        {
            this.mClientBit.SetBitSet(<number>bit,false);
            this.OnClientBitsetChanged (bit);
        }
    }
		
    public TestClientBitState(bit:ClientBits):boolean
    {
        return this.mClientBit.GetBitset(<number>bit);
    }

    public  OnClientBitsetChanged (bit:ClientBits):void
    {

    }
}