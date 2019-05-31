 enum BelongArray{
	Array1,//组1
	Array2,//组2
	Array3,//组2
	Unassigned,//未分配
}

/**
 * 战斗编辑Model
 */
class BattleEditModel extends BaseModel{

	private battleArray1:HeroInfo[];
	private battleArray2:HeroInfo[];
	private battleArray3:HeroInfo[];
	private allBattleArray:any[]; 
	private allHero:HeroInfo[];
	public currentTeam:BelongArray=BelongArray.Array1;//当前队伍
	public currentIndex:number=1;//当前选择位置

	public constructor($controller: BaseController) {
		super($controller);

		let objs:number[]=[
			200110,
			200410,
			200610,
			200710,
			200910,
		    201010,
			201610,
			202010,
			202110,
			210410,
		];
		App.PlayerManager.SetBasicInfo("",objs,0,0);
		this.battleArray1=[];
		this.battleArray2=[];
		this.battleArray3=[];
		this.allBattleArray=[this.battleArray1,this.battleArray2,this.battleArray3];
		

		this.AddToArray(1,this.currentTeam,0);
		this.AddToArray(2,this.currentTeam,200110);
	}
	
	/**
	 * 添加到当前选择组
	 */
	public AddToCurrentArray(id:number):boolean{
	return 	this.AddToArray(this.currentIndex,this.currentTeam,id);
	}

	/**初始化站位信息 */
	public InitArrayInfo(action:boolean,index:number){

		let info :HeroInfo=new HeroInfo(index,0,false);
		info.action=action;
		this.battleArray2.push(info);
		this.battleArray3.push(info);
		for(let i=0;i<this.battleArray1.length;i++){
			if(this.battleArray1[i].index==index){
				return;
			}
		}
		this.battleArray1.push(info);
	}

	/**
	 * 添加到指定组
	 */
	public AddToArray(index:number,belong:BelongArray, id:number):boolean{
		if(!this.CheckIsExistHero(belong,id)){
		for(let i=0;i<this.allBattleArray[belong].length;i++){
			if(this.allBattleArray[belong][i].index==index){//当前位置有英雄
					if(this.allBattleArray[belong][i].id!=id){
						let info :HeroInfo=new HeroInfo(index,id,true);
						info.action=true;
						this.allBattleArray[belong][i]=info;
						return true;
					}else{
						return false;
					}
			}
		}
		let info :HeroInfo=new HeroInfo(index,id,true);
		info.action=true;
		this.allBattleArray[belong].push(info);
		return true;
		}else{
			return false;
		}
	}

	/**
	 * 交换位置 
	 */
	public ExchangePoint(index1:number,index2:number):boolean{
		if(index1!=index2){
		let tempArray:HeroInfo[]=	this.GetTeamByIndex(this.currentTeam);
		let info1:HeroInfo=this.GetInfoByIndex(tempArray, index1);
		let info2:HeroInfo=this.GetInfoByIndex(tempArray, index2);
		if(info1&&info2&&info2.action){
		let tempIndex=info1.index;
		info1.index=info2.index;
		info2.index=tempIndex;
		return true;
		}else{
		return false;
		}
		}else{
		return false;
		}
	}

	/**
	 * 根据下表获取信息
	 */
	public GetInfoByIndex(infos:HeroInfo[], index:number):HeroInfo{
		for(let i=0;i<infos.length;i++){
			if(infos[i].index==index){
				return infos[i];
			}
		}
		return null;
	}

	/**
	 * 判断当前组是否有当前英雄
	 */
	public CheckIsExistHero(belong:BelongArray,id:number):boolean{
		for(let i=0;i<this.allBattleArray[belong].length;i++){
			if(this.allBattleArray[belong][i].id==id){
				return true;
			}
		}
		return false;
	}

	/**
	 * 检测是否已经上阵
	 */
	public CheckInArray(id:number):boolean{
		for(let i=0;i<this.allBattleArray.length;i++){
			for(let j=0;j<this.allBattleArray[i].length;j++){
				if(id==this.allBattleArray[i][j].id){
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * 获取所有英雄
	 */
	public GetAllHero():HeroInfo[]{
	this.allHero=[];//每次重新获取
	App.PlayerManager.OwnHeroID.forEach(element => {
		let info=new HeroInfo(0,element,this.CheckInArray(element));
		this.allHero.push(info);
		});
		return this.allHero;
	}

	/**
	 * 获取某队信息
	 */
	public GetTeamByIndex(index:number):HeroInfo[]{
		this.currentTeam=index;
		if(index<this.allBattleArray.length)
		return this.allBattleArray[index];
	}


	
}

 /** 英雄信息*/
 class HeroInfo{
	 
	 public index:number;//位置
	 public id:number;//id
	 public belong:boolean;//所属分组
	 public action:boolean;//是否激活

	 public constructor(index:number,id:number,belong:boolean){
		 this.index=index;
		 this.id=id;
		 this.belong=belong;
	 }


 }