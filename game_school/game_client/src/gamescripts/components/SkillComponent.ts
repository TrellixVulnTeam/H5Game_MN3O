/**
 * 技能管理
 */
class SkillComponent extends Component {
    private target: MilitaryOfficerObject;
    private SkillAyyary: Array<Skill> = new Array<Skill>();
    private mCurTimer: TimerHandler;
    private abilityConf: CreatureAbilityConfig;//能力表

    public constructor() {
        super();
    }

    public start(): void {
        super.start();
        this.InitData();
    }

    public stop(): void {
        super.stop();
        for (let skill in this.SkillAyyary) {
            ObjectPool.push(skill);
        }
        this.SkillAyyary = [];
    }

    public update(advancedTime: number): void {
        super.update(advancedTime);
    }

    public InitData(): void {
        this.abilityConf = CreatureAbilityConfig.GetConfig(this.entity.CreatureConf.ability);

        if (this.abilityConf&&this.abilityConf.magic1 != 0 ) {
            let skill1: Skill = ObjectPool.pop("Skill", this.abilityConf.magic1, this.entity as MilitaryOfficerObject);
            this.SkillAyyary.push(skill1);
        }

        if (this.abilityConf&&this.abilityConf.magic2 != 0) {
            let skill2: Skill = ObjectPool.pop("Skill", this.abilityConf.magic2, this.entity as MilitaryOfficerObject);
            this.SkillAyyary.push(skill2);
        }

        if (this.abilityConf&&this.abilityConf.magic3 != 0) {
            let skill3: Skill = ObjectPool.pop("Skill", this.abilityConf.magic3, this.entity as MilitaryOfficerObject);
            this.SkillAyyary.push(skill3);
        }

        if (this.abilityConf&&this.abilityConf.magic4 != 0 ) {
            let skill4: Skill = ObjectPool.pop("Skill", this.abilityConf.magic4, this.entity as MilitaryOfficerObject);
            this.SkillAyyary.push(skill4);
        }

    }

    /**
     * 使用技能
     * @param skill 技能
     * @param target 目标
     */
    public UseSkill(skill: Skill, targertObj?: MilitaryOfficerObject, callback?: Function);

    /**
     * 使用技能
     * @param id 技能id
     * @param target 目标
     */
    public UseSkill(id: number, targertObj?: MilitaryOfficerObject, callback?: Function, previousCallback?: Function);
    public UseSkill(value, targertObj?, callback?,previousCallback?) {
      
        if (typeof value == "number") {
            let skill: Skill = this.GetSkill(value);
            if (skill) {
                if (!skill.InCD) {
                    if (skill.MagicConfig) {
                        if (App.TimerManager.TimeScale == 1)//单倍加速
                        {
                            this.PlayerScaleAndDrawing(skill,skill.MagicConfig.ID,targertObj,callback,previousCallback);
                        }
                        else {
                            if (targertObj) {
                                this.IsNeedMove(skill, targertObj, callback);
                            }
                            else {
                                this.IsNeedMove(skill, targertObj, callback);
                            }
                        }
                    }
                }
            }
        }
        else {
            if (value) {
                if (!value.InCD) {
                    if (value.MagicConfig) {
                        if (App.TimerManager.TimeScale == 1)//单倍加速
                        {
                           
                          this.PlayerScaleAndDrawing(value,value.MagicConfig.ID,targertObj,callback,previousCallback);
                        }
                        else {
                            if (targertObj) {
                                this.IsNeedMove(value, targertObj, callback);
                            }
                            else {
                                this.IsNeedMove(value, targertObj, callback);
                            }
                        }
                    }
                }
            }   
        }
    }

    /**
     * 播放放大高亮及立绘
     */
    private PlayerScaleAndDrawing(skill:Skill,id:number, targertObj?: MilitaryOfficerObject,callback?: Function, previousCallback?: Function){

        if(skill.MagicConfig.ifEnlarge){//是否放大
    
            App.ActionManager.PlayerScale(this.entity as MilitaryOfficerObject,true,function(){

                 if (skill.MagicConfig.ifAnimation)//是否需要播放立绘
                    {
                        this.PlayThreeDimensionalDrawing(skill.MagicConfig.ID, function(){
                            
                                     if(previousCallback)
                                        previousCallback();//连携技播放完立绘再让上一个玩家回去

                                    App.ActionManager. playerMaskViableFalse(this.entity.uid);     
                                    this.IsNeedMove(skill, targertObj, 
                                    function(){
                                           App.ActionManager.PlayerScale(this.entity,false,callback)
                                    }.bind(this));
                                }.bind(this)
                                    );
                    }  else{
                          App.ActionManager. playerMaskViableFalse(this.entity.uid);
                         if (targertObj) {
                                      this.IsNeedMove(skill, targertObj, 
                                    function(){
                                           App.ActionManager.PlayerScale(this.entity,false,callback)
                                    }.bind(this));
                                }
                                else {
                                     this.IsNeedMove(skill, targertObj, 
                                    function(){
                                           App.ActionManager.PlayerScale(this.entity,false,callback)
                                    }.bind(this));
                                }
                    }       

            }.bind(this));

        }else{
             if (skill.MagicConfig.ifAnimation)//是否需要播放立绘
                    {
                        this.PlayThreeDimensionalDrawing(skill.MagicConfig.ID, function(){
                                     if(previousCallback)
                                            previousCallback();//连携技播放完立绘再让上一个玩家回去

                                    this.IsNeedMove(skill, targertObj, callback);}.bind(this)
                                    );
                    }  else{
                         if (targertObj) {
                                    this.IsNeedMove(skill, targertObj, callback);
                                }
                                else {
                                    this.IsNeedMove(skill, targertObj, callback);
                                }
                    }       
        }
    }


                                                                 
    /**
     * 使用技能播放立绘
     * callback 回调函数
     */
    private PlayThreeDimensionalDrawing(id:number, callback: Function): void {

        if( !App.FightManager.IsBackstage){
             App.EventMgrHelper.PushEventEx(EventDef.SetBackMainBtnVis,false,null,0,0,"","");
             let effectCompont: AvatarEffectComponent = <AvatarEffectComponent>this.entity.getComponent(ComponentType.AvatarEffect);
             effectCompont.PlayEffect(1000010, 5, AvatarEffectType.Buff,function(){

               App.EventMgrHelper.PushEventEx(EventDef.SKILLPICTURE_C2C,function(){
               App.EventMgrHelper.PushEventEx(EventDef.SetBackMainBtnVis,true,null,0,0,"","");

            let effectCompont: AvatarEffectComponent = <AvatarEffectComponent>this.entity.getComponent(ComponentType.AvatarEffect);
             effectCompont.PlayEffect(1000020, 5, AvatarEffectType.Buff,function(){
                 if(callback)
                    callback();

             }.bind(this));
             }.bind(this),null,id,0,"","");   
             }.bind(this));
        }else{
            if(callback)
                callback();
        }
    }

    /**
     * 是否需要移动 
     * @param skill
     * @param isNeedMove 是否需要移动
     * @param target 目标
     * @param callback 回调函数
     */
    private IsNeedMove(skill: Skill, target?: MilitaryOfficerObject, callback?: Function) {
        if (skill.MagicConfig.rolePosType == 1) {
            let moveCom: MoveComponent = <MoveComponent>this.entity.getComponent(ComponentType.Move);

            //坐标      
            let point: egret.Point = new egret.Point();
            if(target.dir==Dir.Left){
            point.x = target.position.x + skill.MagicConfig.rolePosition[0];
            point.y = target.position.y + skill.MagicConfig.rolePosition[1];
            }else{
            point.x = target.position.x - skill.MagicConfig.rolePosition[0];
            point.y = target.position.y - skill.MagicConfig.rolePosition[1];
            }
           
            //let point: egret.Point = new egret.Point(target.position.x + skill.MagicConfig.rolePosition[0], target.position.y + skill.MagicConfig.rolePosition[1]);
            moveCom.DoMove(point, function () {
                if (target) {
                    this.DoSKill(skill, target, callback);
                }
                else {
                    this.DoSKill(skill, this.GetTarget(), callback);
                }
            }.bind(this));
        }
        else {
            if (target) {
                this.DoSKill(skill, target, callback);
            }
            else {
                this.DoSKill(skill, this.GetTarget(), callback);
            }
        }
    }

    /**
     * 执行技能
     * @param skill 
     * @param target 目标
     * @param isNeedReturnPos 技能执行完毕是否需要返回原位置
     * @param callback 回调函数
     */
    private DoSKill(skill: Skill, target: MilitaryOfficerObject, callback?: Function): void {
         
        if (skill) {
            this.entity.AddClientBitState(ClientBits.CLIENT_BIT_CASTING);        
            skill.Tigger(target, function () {
                if (skill.SkillType == SkillType.ActiveSkills) {
                    if (skill.MagicConfig.ifCombo&&target.Alive) {
                       
                           this.TriggerConnectionTechnology(target,callback,function(callback?:Function){
                                this.SkillEnd(skill,callback,this.entity);
                                }.bind(this));
                    }
                    else {
                        this.SkillEnd(skill, callback);
                    }
                }else if (skill.SkillType == SkillType.LinkingSkill) {
                    callback();
                }
                else {
                    this.SkillEnd(skill, callback);
                }
            }.bind(this));
        }
    }

    /**
     * 触发连携技
     */
    public TriggerConnectionTechnology(target: MilitaryOfficerObject, callback?: Function,skillCallback?:Function) {
        let linkObjs: MilitaryOfficerObject[] = App.FightManager.CanUseLinkingSkillPlayer(this.entity as MilitaryOfficerObject);
        if(linkObjs.length<1){
            skillCallback(callback);
        }else{
         this.UserConnectionTechnology(linkObjs,target,callback,skillCallback);
        }
    }

    /**
     * 递归执行连携技
     */
    public UserConnectionTechnology(linkObjs: MilitaryOfficerObject[],target: MilitaryOfficerObject, callback?: Function ,skillCallback?: Function){
    
        if (linkObjs.length > 0&&target&&App.FightManager.IsExistInAllObj(target)) {
                let currentObj=linkObjs[0];
                let skillCom: SkillComponent = <SkillComponent>currentObj.getComponent(ComponentType.Skill);
                if (skillCom) {
                    let skill=skillCom.GetSkill(SkillType.LinkingSkill);
                    skillCom.UseSkill(skill, target, () => {
                        let index: number = linkObjs.indexOf(currentObj);
                        if (index != -1) {
                            linkObjs.splice(index, 1);
                            if(linkObjs.length==0){
                                this.SkillEnd(skill,null,currentObj);
                            }
                           this.UserConnectionTechnology(linkObjs,target,callback,()=>this.SkillEnd(skill,null,currentObj) );
                        }
                    },skillCallback);
                }
        }
        else {
            
            if (callback) {
                callback();
            }
        }
    }

    public GetTarget(): MilitaryOfficerObject {
        return this.target;
    }

    public SetTarget(object: MilitaryOfficerObject) {
        this.target = object;
    }

    public GetSkill(skillType: SkillType);
    public GetSkill(id: number);
    public GetSkill(val) {
        if (typeof val == "number"&&val>SkillType.MAX) {
            for (let i = 0; i < this.SkillAyyary.length; i++) {
                if (this.SkillAyyary[i].SkillId == val) {
                    return this.SkillAyyary[i];
                }
            }
        }
        else {
            for (let i = 0; i < this.SkillAyyary.length; i++) {
                if (this.SkillAyyary[i].SkillType == val) {
                    return this.SkillAyyary[i];
                }
            }
        }
    }


    public SkillEnd(skill: Skill, callback?: Function,obj?:GameObject) {
  
        if(obj==null){
            if(callback)
                callback();
                return ;
        }
         let currentEntity;
        if(obj!=null){
             currentEntity=obj;
        }else{
             currentEntity=this.entity;
        }
        
        if (skill.MagicConfig.rolePosType == 1) {
            let moveCom: MoveComponent = <MoveComponent>currentEntity.getComponent(ComponentType.Move);

            let point: egret.Point = currentEntity.StartPosition;
            moveCom.DoMove(point, function () {
                 (<DragonComponent>currentEntity.getComponent(ComponentType.Dragon)).PlayAct(ActionStr.Stand);
                if (callback) {
                    callback();
                }
            }.bind(this), 249);
        }
        else {
              (<DragonComponent>currentEntity.getComponent(ComponentType.Dragon)).PlayAct(ActionStr.Stand); 
               
            if (callback) {
                callback();
            }
        }
        currentEntity.DelClientBitState(ClientBits.CLIENT_BIT_CASTING);
    }

    /**
     * 更新技能状态
     */
    public UpdateSkillState(): void {
        //CD 
        this.SkillAyyary.forEach(function (data: Skill) {
            data.CD = (data.CD - 1);
        });
    }


    /**
      * 获得被动技能
      */
    public GetPassiveSkill(): Skill {
        for (let element of this.SkillAyyary) {
            if (element.MagicConfig.type == SkillType.PassiveSkill) {
                return element;
            }
        }
        return null;
    }

    /**
     * 获取可用主动技能
     */
    public GetAvailable(): Skill {
        let tempArr: Array<Skill> = this.SkillAyyary;
    
        //按主动技能优先级排序
        tempArr.sort(function (a, b) {
            if (a.MagicConfig.autoSkillPriority < b.MagicConfig.autoSkillPriority) {
                return 1;
            }
            else {
                return -1;
            }
        });

        for (let element of tempArr) {
            if (element.MagicConfig.type == SkillType.ActiveSkills) {
                if (element.CD == 0) {
 
                    return element;
                }
            }
        }
        return null;
    }

    /**
     * 获取所有主动技能
     */
    public GetAvailableSkill(): Skill[] {
        let avaSkill: Skill[] = [];
        this.SkillAyyary.forEach(element => {
            if (element.SkillType == SkillType.ActiveSkills)
                avaSkill.push(element);
        });
        return avaSkill;
    }
}