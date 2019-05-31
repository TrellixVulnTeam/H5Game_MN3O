/**
 * 演示
 */
class DemonstrationObject extends GameObject {
    
    private draggedObject:egret.DisplayObjectContainer;
    private offsetX:number;
    private offsetY:number;
    private rootCom:egret.DisplayObjectContainer;//根组件
    private originalpoint:egret.Point=new egret.Point;//原位
    private avatarCom:DragonComponent;//骨骼

	  public constructor()
    {
        super();
    }
    
    public init(id:number,posinfo:BattlePosition, camp:Camp, gameView:egret.DisplayObjectContainer,rootView:egret.DisplayObjectContainer, data?:any):void
    {
        super.init(id,posinfo, camp, gameView,data);
		this.avatarCom= this.addComponent(ComponentType.Avatar) as DragonComponent;

        this.rootCom=rootView;
    
        this.RegisEventListener(egret.TouchEvent.TOUCH_BEGIN,function(e:egret.TouchEvent){
            this.StartMove(e)
        }.bind(this) );

	    this.RegisEventListener(egret.TouchEvent.TOUCH_END, function(e:egret.TouchEvent){
            this.StopMove(e)
        }.bind(this) );

        this.RegisEventListener(egret.TouchEvent.TOUCH_RELEASE_OUTSIDE,function(e:egret.TouchEvent){
           this.StopMove(e);
        }.bind(this));
    }
    
    public StartMove(e:egret.TouchEvent){
      
        this.draggedObject=e.currentTarget;
        this.originalpoint.x=this.position.x;
        this.originalpoint.y=this.position.y;
        
        let pos:egret.Point = this.draggedObject.localToGlobal(this.draggedObject.x,this.draggedObject.y);//转成世界坐标
        this.ChangeParent(this.rootCom);//转到移动层
    
        this.position=this.draggedObject.globalToLocal(pos.x,pos.y);//世界坐标转本地坐标
 
        this.offsetX = e.stageX - this.position.x;
        this.offsetY = e.stageY - this.position.y;        
        
        App.EventMgrHelper.PushEventEx(EventDef.SetAddState,false,null,0,0,"","");
        this.RegisEventListener(egret.TouchEvent.TOUCH_MOVE, function(e:egret.TouchEvent){
            this.OnMove(e);
        }.bind(this) );  
    }

     public StopMove(e:egret.TouchEvent){
         if( this.draggedObject){
         
         let pos:egret.Point = this.draggedObject.localToGlobal(this.draggedObject.x,this.draggedObject.y);
         
         this.ChangeParent(this.gameView);

         this.position=this.draggedObject.globalToLocal(pos.x,pos.y);
         
         App.EventMgrHelper.PushEventEx(EventDef.CheckCollision,this,this.draggedObject,0,0,"","");

         App.EventMgrHelper.PushEventEx(EventDef.SetAddState,true,null,0,0,"","");

        this.draggedObject=null;
         }
              
         this.RemoveEventListener(egret.TouchEvent.TOUCH_MOVE);
     }

    public OnMove(e:egret.TouchEvent){
          if( this.draggedObject){
                this.position.x = e.stageX - this.offsetX;
                this.position.y = e.stageY - this.offsetY;
                if(this.avatarCom)
                this.avatarCom.setPos();
          }
    }

    public BackInPlace(){
        this.position.x=this.posInfo.Pos.x;
        this.position.y=this.posInfo.Pos.y;
    }
   
   

}