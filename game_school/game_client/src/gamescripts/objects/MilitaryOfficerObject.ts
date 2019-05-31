
/** 
 * Player
 * created by sjz on 2018-5-9. 
 */
class MilitaryOfficerObject extends GameObject
{
    public constructor()
    {
        super();
    }
    
    public init(id:number,posinfo:BattlePosition, camp:Camp, gameView:egret.DisplayObjectContainer,data?:any):void
    {
        super.init(id,posinfo, camp, gameView,data);
       // this.addComponent(ComponentType.Avatar);
        this.addComponent(ComponentType.Dragon);//骨骼组件必须放在最前
        this.addComponent(ComponentType.AvatarEffect);
        this.addComponent(ComponentType.Head);
        this.addComponent(ComponentType.Move);
        this.addComponent(ComponentType.Skill);
        this.addComponent(ComponentType.Buff);
   
        this.ClientBit.SetBitSet(<number>ClientBits.CLIENT_BIT_DEAD,false);

        this.RegisEventListener(egret.TouchEvent.TOUCH_TAP,()=>{
              App.ActionManager.CurrentTarget = this;
        });
    }
    
    public Death():void
    {
        super.Death();
        this.ClientBit.SetBitSet(<number>ClientBits.CLIENT_BIT_DEAD,true);
        this.DelClientBitState(ClientBits.CLIENT_BIT_SKILL_ACTIVATE);
    }

    /**
     * 掉血
     * @param 伤害值（掉血值）
     * @param 是否暴击
     * @param 回调函数
     */
    public DamageSettlemen(hurt:number,isCri:boolean,callback?:Function):void{
        if(callback)
        {
            callback();
        }
    }




}