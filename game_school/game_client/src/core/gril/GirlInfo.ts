/**
 * girl基础信息  拥有的聊天信息，朋友圈信息等
 */
class GirlInfo {
	private girlId:number=0;//表格id
	private uid:string="";//唯一id
	private config:GirlConfig;//表格
	private friendlyNum:number=0;//友好度
	private headIcon:string="";//头像图片
	private girlName:string="";//名称
	private player:PlayerBase;//归属

	public constructor(id:number,player:PlayerBase) {
		this.girlId=id;
		this.uid=App.MathUtils.uuid(10,16);
		this.config=GirlConfig.GetConfig(id);
		this.headIcon=this.config.icon;
		this.girlName=this.config.name;
		this.player=player;
	}

	public get GirlId():number{return this.girlId;}
	public get Config():GirlConfig{return this.config;}
	public get UId():string{return this.uid;}
	public get FriendlyNum():number{return this.friendlyNum;}
	
	public get HeadIcon():string{return this.headIcon;}
	public set HeadIcon(value:string){this.headIcon=value;}
	public get GirlName():string{return this.girlName;}
	public set GirlName(value:string){this.girlName=value;}

	public  SetFriendlyNum(value:number){
		 this.friendlyNum+=value;
	}


}

 
