/**技能类型 */
enum SkillType {
    /**主动技能 */
    ActiveSkills = 1,
    /**被动技能 */
    PassiveSkill = 2,
    /**连携技 */
    LinkingSkill = 3,
    /**触发技 */
    TriggerSkill = 4,

    MAX = 5
}
class Skill {
    private skillId: number;
    private skillType: SkillType;
    private skillCd: number;

    private isCanuse: boolean = false;
    private isFinished: boolean = false;

    private magicConfig: MagicConfig;
    private entity: MilitaryOfficerObject;

    private actionEnd:boolean=false;//动作都执行完毕
    private effectCount:number=0;//特效执行完毕计数

    public constructor(skillid: number, owner: MilitaryOfficerObject) {
        this.skillId = skillid;
        this.magicConfig = MagicConfig.GetConfig(this.skillId);
        this.skillType = this.magicConfig.type;
        this.entity = owner;
        this.OnFightInitCD();
    }

    /**战斗开始所有技能初始化CD */
    public OnFightInitCD(): void {
        this.CD = this.magicConfig.cdInit;
    }

    /**技能触发 */
    public Tigger(target: MilitaryOfficerObject, callback?: Function): void {
     //   console.log("Tigger......................................................................................................"+this.entity.basicattr.Name);
        if (this.entity) {
            this.actionEnd=false;
 
            let compont: DragonComponent = <DragonComponent>this.entity.getComponent(ComponentType.Dragon);

            var endCallBack: Function = function () {
              
                    this.SkillClearingRecursive(callback);
                 // console.log("SkillClearingRecursive");
                  
            }.bind(this);

            if (compont && SkillType.PassiveSkill != <SkillType>this.magicConfig.type) {

                compont.PlayAct(this.magicConfig.active,1,endCallBack);   //播放技能动作

                  //播放特效,现在特效是个数组 释放者特效
                for (let i = 0; i < this.magicConfig.effect.length; i++) {
                    App.TimerManager.doTimer(this.magicConfig.effectDelay[i], 1,
                        function () {
                            let effectCompont: AvatarEffectComponent = <AvatarEffectComponent>this.entity.getComponent(ComponentType.AvatarEffect);
                            if(effectCompont){
                                
                                  effectCompont.PlayEffect(this.magicConfig.effect[i], this.magicConfig.effctPosType[i], AvatarEffectType.Skill);
                            }
                          
                        }.bind(this),
                        this, 0, null, this);
                };

                if(!App.FightManager.IsBackstage){
                        for (let i = 0; i < this.magicConfig.sound.length; i++) {
                        App.TimerManager.doTimer(this.magicConfig.soundDelay[i], 1,
                        function () {
                            App.SoundManager.playEffect(this.magicConfig.sound[i]);   //播放音效
                        }.bind(this),
                        this, 0, null, this);
                       }
                }
                App.ActionManager.InitInjuredList();

                /**目标特效，并结算 */
                 let effectIds:number[]= [];
                  this.magicConfig.effectID.forEach(element => {
                     effectIds.push(element);
                 });

                 this.SkillClearing(effectIds,target,callback); 
            }else{
                    /**目标特效，并结算 */ 
                 let effectIds:number[]= [];
                 this.magicConfig.effectID.forEach(element => {
                     effectIds.push(element);
                 });
                 this.SkillClearing(effectIds,target,callback); 
            }
        }   
    }

    /**技能效果结算 */
    public SkillClearing(effectID:number[],target:MilitaryOfficerObject,callback:Function){
                      
                     if(effectID.length>0){
                         let currentId=effectID[0];
                         let magicEff: SkillEffect = new SkillEffect(currentId, target, this.entity);   
                         let index :number =effectID.indexOf(currentId);
                         if(index!=-1){
                             effectID.splice(index,1);
                         }
                         magicEff.Accounting(0,()=>this.SkillClearing(effectID,target,callback));
                     }else{
                         if(callback)
                             this.SkillClearingRecursive(callback);
                     }   
    }

    /**技能效果结算和技能动作需要 */
    public SkillClearingRecursive(callback:Function){
       // console.log("SkillClearingRecursive    "+this.actionEnd+"    "+this.SkillId);
        if(this.actionEnd)  {
          // console.log("actionEnd");
             this.actionEnd=false;
             this.effectCount=0;
             this.CD = this.magicConfig.cd;
     App.ActionManager.PlayInjure(function(){
        // console.log("PlayInjure");
        if(callback){
               callback();
         }
         }.bind(this));
        }else{
            // console.log("this.actionEnd=true;");
            this.actionEnd=true;
        }
    }

    get SkillId() {
        return this.skillId;
    }

    get SkillType() {
        return this.skillType;
    }

    get MagicConfig() {
        return this.magicConfig;
    }

    get CD() { return this.skillCd; }
    set CD(val: number) {
        this.skillCd = val <= 0 ? 0 : val;
    }

    get IsCanUse() {
        return this.isCanuse;
    }

    set IsCanUse(val: boolean) {
        this.isCanuse = val;
    }

    get InCD(): boolean {
        if (this.CD > 0) {
            return true;
        }
        return false;
    }



}