/**
 * 龙骨组件
 */
class DragonComponent extends Component {
    
     private mDragon:DragonCombatantObject;//龙骨对象
     private playNum:number;//动画循环次数
     private body:egret.DisplayObjectContainer;//身体
     private positive:boolean;//朝向是否正面
     private currentAction:string;//当前动作

     private actionArray:string[]=[
        "attack",
        "chant",
        "dead",
        "hit01",
        "hit02",
        "hit03",
        "hit04",
        "idle",
        "run",
        "skill",
        "win"
    ];

    public constructor() {
        super();
    
    }
 
    public start(): void {
        super.start();
        if(!this.body){
             this.body=  new egret.DisplayObjectContainer();// ObjectPool.pop("egret.DisplayObjectContainer");
        }
        this.body.x=0;
        this.body.y=0;
        this.body.removeChildren();
        this.entity.gameView.addChild(this.body);
       
        if(!this.mDragon){
             this.mDragon = new DragonCombatantObject();// ObjectPool.pop("DragonCombatantObject");
        }
        this.mDragon.x=0;
        this.mDragon.y=0
        this.body.addChild(this.mDragon);
      
        this.mDragon.init(this.entity.avatarName, "armatureName", this.actionArray,ActionStr.Stand);
        this.mDragon.armature.touchEnabled = true;
        //this.mDragon.armature.$addListener(egret.TouchEvent.TOUCH_BEGIN, this.TurnDragon, this);
        this.body.scaleX=this.entity.oriScale;
        this.body.scaleY=this.entity.oriScale;
        this.TurnDragon(this.entity.camp==Camp.Friendly);
    }

    public TurnDragon(positive:boolean=undefined){
        if(positive==undefined){
            if(this.positive){
               this.mDragon.armature.skewY=180;
            }else{
                this.mDragon.armature.skewY=0;
            }
             this.positive=!positive;
             return;
        }
        if(positive)
         this.mDragon.armature.skewY=0;
         else
         this.mDragon.armature.skewY=180;
         this.positive=positive;
    }

    public ArmatureClick(){

    }
    
    public stop(): void {
        super.stop();
        this.mDragon.destory();
        App.DisplayUtils.removeFromParent(this.body);
        ObjectPool.push(this.body);
        App.DisplayUtils.removeFromParent(this.mDragon);
        ObjectPool.push(this.mDragon);
    }

    public update(advancedTime: number): void {
        super.update(advancedTime);
        this.setPos();
    }

    public PlayAct(act: string,playNum:number=1, callback?: Function) {

        if(!act||act=="")
        {
            if(callback){
                callback();
            }
             return ;
        }

        if(act==ActionStr.Stand||act==ActionStr.Move){
                this.playNum=0;
        }else{
            this.playNum=playNum;
        }

        this.mDragon.armature.play(act,this.playNum);
        this.currentAction=act;

        if(act!=ActionStr.Stand){
             let endCallback:Function=function(){

            if(this.playNum!=0&&this.currentAction!=ActionStr.Die){
                this.mDragon.armature.play(ActionStr.Stand,0);
                this.currentAction=ActionStr.Stand;
            }

         this.mDragon.armature.removeCompleteCallFunc(endCallback,act);

          if(callback){
                callback();
          }

        }.bind(this);

        this.mDragon.armature.addCompleteCallFunc(endCallback,act);
        }
       
    }
    
    public setPos(): void {
       
        if (this.Body.x != this.entity.position.x) {
                this.Body.x = this.entity.position.x;
            }
            if (this.Body.y != this.entity.position.y) {
                this.Body.y = this.entity.position.y;
            }
    }

    public get Body():egret.DisplayObjectContainer{return this.body;}
    public get MDragon():DragonCombatantObject{return this.mDragon;};
}