enum HurtType{
	Hurt,//伤害
	Gain,//增益
	Max
}

class ActionManager extends BaseClass {
	private currentObj:MilitaryOfficerObject=null;//当前行动对象
	private currentSkill:Skill=null;	//当前技能
	private currentTarget:MilitaryOfficerObject=null;//当前目标

	private actioning:boolean=false;//行动中
	private waitAuto:boolean=false;//等待操作

	private currentEnd:Function;//当前行动结束回调

	private currentBuffCom:BuffComponent;//当前buff组件
	private currentKillCom:SkillComponent;//当前技能组件

	private currentCamp:Camp;//当前阵营
	private	currentotherSide:MilitaryOfficerObject[];//当前对方列表
	private currentSelfSide:MilitaryOfficerObject[];//己方列表

	private currentInjuredList:MilitaryOfficerObject[];//受伤列表

	private timeHandler:TimerHandler;//时间
	private timer:number;//剩余时间

	public constructor() {
		super();
	}

	/**
	 * 开启行动
	 */
	public StartAction( obj:MilitaryOfficerObject,actionEnd?:Function):void
	{	
		this.actioning=true;
		this.timer=10;
		this.ResetAction();
		this.currentEnd=actionEnd;
		this.currentObj=obj;
		this.currentCamp=obj.camp;

		this.currentBuffCom =<BuffComponent>this.currentObj.getComponent(ComponentType.Buff);
		this.currentKillCom =<SkillComponent>this.currentObj.getComponent(ComponentType.Skill);
		
        this.SetSideList();

		this.SelectedEffectShow(this.currentObj,true);
		if(!App.FightManager.IsAutomatic)
		this.timeHandler=App.TimerManager.doTimer(1000, this.timer, ()=>this.OnTimeUpdate(), this,0,()=>this.OnTimeFinity(),this);//一秒一次

		this.DiversionAction();
	}	

	public SetSideList(){
	   if(this.currentCamp==Camp.Friendly)
		{
			this.currentotherSide=App.FightManager.EnemyPlayers;
			this.currentSelfSide=App.FightManager.OwnerPlayers;
		}else{
			this.currentotherSide=App.FightManager.OwnerPlayers;
			this.currentSelfSide=App.FightManager.EnemyPlayers;
		}
	}

	/**
	 * 选中
	 */
	public  SelectedEffectShow(target:MilitaryOfficerObject,self:boolean){
		
		let avatarCom:DragonComponent=<DragonComponent>target.getComponent(ComponentType.Dragon);
		if(avatarCom)
		selectCharacter.onSelectImg(avatarCom .Body,target.camp);

		if(self){
			this.currentSelfSide.forEach(element => {
			if(element.uid!=target.uid){
				let enemyCom:DragonComponent=<DragonComponent>element.getComponent(ComponentType.Dragon);
				selectCharacter.unSelectImg(enemyCom.Body);
			}
		});
		}else{
			this.currentotherSide.forEach(element => {
			if(element.uid!=target.uid){
				let enemyCom:DragonComponent=<DragonComponent>element.getComponent(ComponentType.Dragon);
				selectCharacter.unSelectImg(enemyCom.Body);
			}
		});
		}
	}

	/**
	 * 分类执行
	 */
	public DiversionAction(){
 		if(!this.currentBuffCom .IsDizziness())
		{
		if(this.currentObj.camp==Camp.Friendly)
			 this.FriendlyAction();
			else
			 this.HostilityAction();
		}else
		{
			 this.currentEnd();//如果眩晕直接结束行为
		}
	}

	/**
	 * 计时器更新
	 */
	public OnTimeUpdate()
	{
		this.timer--;
		if(this.timer<=2&&!App.FightManager.IsAutomatic){
			App.EventMgrHelper.PushEvent(EventDef.UpdateTimer,this.timer);
		}
	}

	/**
	 * 计时结束
	 */
	public OnTimeFinity(){
	 if(this.timer<=0){
		if(this.timeHandler)
		App.TimerManager.remove(this.timeHandler.id,this);
		App.FightManager.IsAutomatic = true;
		 }
	}

	/**
	 * 友好
	 */
	public FriendlyAction():void
	{
		let skillCom:SkillComponent=<SkillComponent> this.currentObj.getComponent(ComponentType.Skill);
		let skills:Skill[]=skillCom.GetAvailableSkill();
		App.EventMgrHelper.PushEventEx(EventDef.OpenSkill,this.currentObj,skills,0,0,"","");

		if(!App.FightManager.IsAutomatic)
		{
		this.waitAuto=true;

		}else
		{
		this.AutoAction();
		}
	}

	/**
	 * 敌人的话直接执行ai
	 */
	public HostilityAction():void
	{
		App.EventMgrHelper.PushEventEx(EventDef.OpenSkill,this.currentObj,null,0,0,"","");
		this.AutoAction();
    }
 
	/**
	 * 自动执行
	 */
	public AutoAction()
	{
	this.currentSkill= this.currentKillCom. GetAvailable();	//获取主动技能
	
	this.currentTarget = this.GetTarget();
//	console.log("AutoAction:"+this.currentTarget.basicattr.Name);
	this.UseSkillAction();
	}

	/**
	 * 执行战斗
	 */
	public UseSkillAction(){
        this.actioning=false;
		this.waitAuto=false;
		if(this.currentTarget!=null){
			this.SelectedEffectShow(this.currentTarget,false);
		if(this.currentSkill!=null){

		this.currentKillCom.SetTarget(this.currentTarget);

	 	this.currentKillCom.UseSkill(this.currentSkill.SkillId,this.currentTarget,function()  {

		this.SkillCallback(this.currentTarget);

		}.bind(this));

		}else{//没有找到技能
		}
		}else{
			//没有找到目标
		}
	}

	/**
	 * 玩家缩放高亮
	 */
	public PlayerScale(obj:MilitaryOfficerObject,enlarge:boolean,callback:Function){

		if(obj){
			let multiple:number=obj.oriScale*1.2;

			if(enlarge){
		this.playerMaskViableTrue(obj.uid);
		this.playerObjExpression(obj, [1, 1], [obj.oriScale, multiple], [0,30], [0, 200], 200, function(){
			if(callback)
				callback(); 
		}.bind(this));

		}else{
			this.playerObjExpression(obj, [1, 1], [obj.oriScale, obj.oriScale], [30, 0], [0, 200], 200, function(){
			if(callback)
				callback();
		}.bind(this));
		}
		}else{
			if(callback)		
				callback();
		}	
	}

	/**
	 * 技能释放完毕回调
	 */
	public SkillCallback(target:MilitaryOfficerObject):void{
		//console.log("SkillCallback");
		this.ActionFinity();
	}

	/**
	 * 选择目标
	 */
	public GetTarget():MilitaryOfficerObject
	{
		 this.SetSideList();
		//顺序  血量百分比少的， 血量数值少的， 按站位 1 2 3
		//console.log(this.currentotherSide.length);
		if(this.currentotherSide.length>0){
		return  this.Sortpercentage()[0];
		}
		return null;
	}

	/**
	 * 行动结束
	 */
	public ActionFinity()
	{
	if(this.timeHandler)
	App.TimerManager.remove(this.timeHandler.id,this);
	this .currentEnd();
	}
	
	/**
	 * 重置行动
	 */
	public ResetAction()
	{
		this.currentObj=null;
		this.currentSkill=null;
		this.currentTarget=null;
	}

	/**
	 * 按百分比排序
	 */
	public Sortpercentage():MilitaryOfficerObject[]{
		
		let tempObjs:MilitaryOfficerObject[]=this.currentotherSide;
		tempObjs.sort(function(a,b){
			if((a.basicattr.OriHp/ a.basicattr.MaxHP) <(a.basicattr.OriHp/ a.basicattr.MaxHP))
                return 1;
            else
                return -1;
        });

		let sameObjs:MilitaryOfficerObject[];
		let comObj :MilitaryOfficerObject =tempObjs[0];
		tempObjs.forEach(element => {
			if((comObj.basicattr.OriHp/comObj.basicattr.MaxHP)==(element.basicattr.OriHp/element.basicattr.MaxHP)){
				sameObjs.push(element);
			}
		});

		if(sameObjs!=null&& sameObjs.length>1){
			return  this.SortHPValue(sameObjs);
		}else{
			return tempObjs;
		}
	}

	/**
	 * 按血量排序
	 */
	public SortHPValue(objlist:MilitaryOfficerObject[]):MilitaryOfficerObject[]{
		
		objlist.sort(function(a,b){
			if(a.basicattr.OriHp <a.basicattr.OriHp)
                return 1;
            else
                return -1;
        });

		let sameObjs:MilitaryOfficerObject[];
		let comObj :MilitaryOfficerObject =objlist[0];
		objlist.forEach(element => {
			if(comObj.basicattr.OriHp==element.basicattr.OriHp){
				sameObjs.push(element);
			}
		});

		if(sameObjs!=null&& sameObjs.length>1){
			return  this.SortPoint(sameObjs);
		}else{
			return objlist;
		}
	}

	/**
	 * 按站位从上往下排序
	 */
	public SortPoint(objlist:MilitaryOfficerObject[]):MilitaryOfficerObject[]{
		objlist.sort(function(a,b){
			if(a.posInfo.LineNum <a.posInfo.LineNum)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        });
		return objlist;
	}

    public get WaitAuto(){return this.waitAuto;}
	public set CurrentObj(value:MilitaryOfficerObject){this.currentObj=value;}

	/**
	 * 设置目标
	 */
	public set CurrentTarget(value:MilitaryOfficerObject){
		if(this.actioning&& value.camp!=this.currentCamp ){
		this.currentTarget=value;

		this.SelectedEffectShow(this.currentTarget,false);

		if(this.currentSkill!=null){
			this.UseSkillAction();
		}else{


		}

		}else{

		}
	}

	/**
	 * 设置技能
	 */
	public set CurrentSkill(value:Skill){
		if(this.actioning){
			this.currentSkill=value;

		if(this.currentTarget!=null){
	 		this.UseSkillAction();
		}else{
			this.currentTarget = this.GetTarget();
			this.UseSkillAction();
		}
		}
	}

	/**
	 * 初始化受伤列表
	 */
	public InitInjuredList(){
		this.currentInjuredList=[];
	}

	/**
	 * 添加受伤
	 */
	public AddInjureList(obj:MilitaryOfficerObject){
		for(let i = 0; i <  this.currentInjuredList.length; i++){
			if(this.currentInjuredList[i].uid==obj.uid){
				return ;
			}
		}
		if(obj){
			let buffCom:BuffComponent=<BuffComponent>obj.getComponent(ComponentType.Buff);	
			if(!buffCom.CheckIsHaveSameIDBuff(parseInt( ClientConstConfig.GetConfig(5).value))){
 				this.currentInjuredList.push(obj);
			}
		}
	}

	/**
	 * 受伤立绘
	 */
	public PlayInjure(callback:Function){
		if(App.FightManager.IsBackstage){
			if(callback)
			callback();
			return;
		}
		
		if(this.currentInjuredList.length<=0){
			if(callback)
			callback();
		}else{
			let currentObj=this.currentInjuredList[0];
			let index:number =this.currentInjuredList.indexOf(currentObj);
			if(index!=-1){
				this.currentInjuredList.splice(index,1);
			}
			if(currentObj){
		
			App.EventMgrHelper.PushEventEx(EventDef.SetBackMainBtnVis,false,null,0,0,"","");

			App.EventMgrHelper.PushEventEx(EventDef.HPPICTURE_C2C,function(){

			let  buffCom=<BuffComponent>currentObj.getComponent(ComponentType.Buff);
			if(buffCom){
			App.EventMgrHelper.PushEventEx(EventDef.SetBackMainBtnVis,true,null,0,0,"","");
		  	buffCom.AddBuff(parseInt( ClientConstConfig.GetConfig(5).value),currentObj.uid);
			this.PlayInjure(callback);
			}else{
				if(callback)
					callback(); 
			}
			}.bind(this),null,0,0,"","");

			}else{
				if(callback)
				callback();
			}
		}
	}

	/**
	 * 开启半透明遮罩
	*/
	public playerMaskViableTrue(objUID:string):void
	{
		App.EventMgrHelper.PushEvent(EventDef.FightMaskViableTrue,0,0,objUID);
	}

	/**
	 * 关闭半透明遮罩
	*/
	public playerMaskViableFalse(objUID:string):void
	{
			App.EventMgrHelper.PushEvent(EventDef.FightMaskViableFalse,0,0,objUID);
	}


	/**
	 * 角色透明度，放缩和滤镜
	 * 
     * alpha[]初始透明度, 变化透明度
     * scale[]初始缩放比例, 变化缩放比例
     * filter[]初始滤镜值, 滤镜变化值
     * time[]等待时长，变化时长
     * functionTime回掉函数等待时长
     * callBack回掉函数
    */
	public playerObjExpression(obj:MilitaryOfficerObject, alpha:number[], scale:number[],  filter:number[], time:number[], functionTime:number = 0, callBack?:Function):void
    {
        if(obj != null)
        {
            var compon:Component = obj.getComponent(ComponentType.Dragon);
            if(compon != null)
            {
                if(compon instanceof DragonComponent)
                {
                    if((compon as DragonComponent).Body != null) 
                    {
                        var body = (compon as DragonComponent).Body;
					
                        this.playerBodyExpression(body, alpha, scale, filter, time,functionTime, callBack);
                    }
                }
            }
        }
    }

    /**
     * alpha[]初始透明度, 变化透明度
     * scale[]初始缩放比例, 变化缩放比例
     * filter[]初始滤镜值, 滤镜变化值
     * time[]等待时长，变化时长
     * functionTime回掉函数等待时长
     * callBack回掉函数
    */
    private playerBodyExpression(target:any, alpha:number[], scale:number[], filter:number[], time:number[], functionTime:number = 0, callBack?:Function):void 
    {
        if(target == null || alpha.length < 2 || scale.length < 2 || time.length < 2 || filter.length < 2)
        {
            return;
        }

        target.alpha = alpha[0];
        target.scaleX = scale[0];
        target.scaleY = scale[0];
        egret.Tween.get(target)
        .wait(time[0])
        .call(() => 
        {
			this.setObjFilters(target, filter[0], filter[1]);
            egret.Tween.get(target)
            .to({alpha: alpha[1], scaleX: scale[1], scaleY:scale[1]}, time[1])
            .wait(functionTime)
            .call(() => 
            {
                if (callBack != null) 
				{
					callBack();
				}
            });
        });
    }

    /**
     * 设置高亮滤镜
    */
    private setObjFilters(target:any, oTime:number, tTime:number):void
    {
        if(target == null || oTime < 0 || tTime < 0)
        {
            return;
        }

        var intervalID = setInterval( function onTick()
        {
            if(oTime < tTime)
            {
                oTime++;
            }
            else if(oTime > tTime)
            {
                oTime--
            }

            var colorMatrix = 
            [
                1,0,0,0,oTime,
                0,1,0,0,oTime,
                0,0,1,0,oTime,
                0,0,0,1,0
            ];
            target.filters = [new egret.ColorMatrixFilter(colorMatrix)];

            if(oTime == tTime)
            {
                clearInterval(intervalID);
            }
        }.bind(this), 1);
    }


	/**
	 * 受伤表现
	*/
	public playerObjHurtExpression(obj:MilitaryOfficerObject, color:string, chaTime:number, showTime, functionTime:number = 0, callBack?:Function):void
	{
		if(obj != null)
		{
			var compon:Component = obj.getComponent(ComponentType.Avatar);
			if(compon != null)
			{
				if(compon instanceof DragonComponent)
				{
					if((compon as DragonComponent).Body != null)
					{
						var body = (compon as DragonComponent).Body;
						this.playerBodyHurtExpression(body, color, chaTime, showTime, functionTime, callBack);
					}
				}
			}
		}
	}

	/**
	 * body受伤表现
	*/
	private playerBodyHurtExpression(target:any, color:string, chaTime:number, showTime, funcTime:number = 0, callBack?:Function):void 
    {
        if(target == null || color == null || color == "" || chaTime <= 0)
        {
            return;
        }

		let array = this.getRgbByColor(color);
		if(array.length = 3)
		{
			this.setObjHurtFilters(target, array[0], array[1], array[2], chaTime, true);
			egret.Tween.get(target)
			.wait(chaTime + showTime)
			.call(() => 
			{
				this.setObjHurtFilters(target, array[0], array[1], array[2], chaTime, false);
				egret.Tween.get(target)
				.wait(chaTime + funcTime)
				.call(() => 
				{
					if (callBack != null) 
					{
						callBack();
					}
				});
			});
		}
    }

	public getRgbByColor(color:string):Array<number>
	{
		let array = new Array<number>();
		let num = Number(color);
		let b = num % 256;
		let g = (num / 256) % 256;
		let r = (num / 256 / 256) % 256;
		array.push(r);
		array.push(g);
		array.push(b);
		return array;
	}

	/**
     * 设置受伤滤镜
    */
    private setObjHurtFilters(target:any, rTime:number, gTime:number, bTime:number, ctime:number, increase:boolean = false):void
    {
        if(target == null || rTime < 0 || gTime < 0 || bTime < 0 || ctime <= 0)
        {
            return;
        }

		let or = 0;
		let ocr = rTime/ctime;

		let og = 0;
		let ocg = gTime/ctime;
		
		let ob = 0;
		let ocb = bTime/ctime;

		if(increase)
		{
			var intervalID = setInterval( function onTick(){
				ctime--; 
				or+=ocr; 
				og+=ocg; 
				ob+=ocb;

				var colorMatrix = [
					1,0,0,0,or,
					0,1,0,0,og,
					0,0,1,0,ob,
					0,0,0,1,0
				];

				target.filters = [new egret.ColorMatrixFilter(colorMatrix)];
				if(ctime <= 0) { clearInterval(intervalID); }
			}.bind(this), 1);
		}
		else
		{
			var intervalID = setInterval( function onTick(){
				ctime--; 
				rTime-=ocr; 
				gTime-=ocg; 
				bTime-=ocb;

				var colorMatrix = [
					1,0,0,0,rTime,
					0,1,0,0,gTime,
					0,0,1,0,bTime,
					0,0,0,1,0
				];

				target.filters = [new egret.ColorMatrixFilter(colorMatrix)];
				if(ctime <= 0) { clearInterval(intervalID); }
			}.bind(this), 1);
		}
    }
}	
