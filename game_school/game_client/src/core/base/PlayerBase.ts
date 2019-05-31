/** 
 * 玩家基础信息  zsy
 */
class PlayerBase extends BaseClass{
	public constructor() {
		super();
		this.ownGirl=[];
		this.ownGirlId=[];
		this.ownGirlUid=[];

		this.ownHero=[];
		this.ownHeroId=[];
		this.ownHeroUid=[];
	}

	//基础信息*********************************************************************************************/
	
	/**玩家名称 */
	protected name:string;
	/**玩家等级 */
	protected level:number;
	/**玩家总战斗力 */
	protected fightingPower:number;
	/**玩家头像名称 */
	protected headIcon:string;
	
	/**玩家激活的girl*/
	protected ownGirl:GirlInfo[];
	protected ownGirlId:number[];
	protected ownGirlUid:string[];

	/**玩家拥有英雄 */
	protected ownHero:HeroData[];
	protected ownHeroId:number[];
	protected ownHeroUid:string[];

	
	
	/*********************************************************************************************/
	public SetBasicInfo(name:string,ownHero:number[],level:number,fightPower:number){
		this.name=name;
		this.ownHeroId=ownHero;
		this.level=level;
		this.fightingPower=fightPower;
	}

	/**新加girl  并返回*/
	public   GetGirl(id:string):GirlInfo;
	public   GetGirl(id:number):GirlInfo;
	public   GetGirl(id):GirlInfo{
		if(typeof id =="number"){
			let tempConfig:GirlConfig=	GirlConfig.GetConfig(id);
			if(tempConfig){
					let index=this.ownGirlId.indexOf(id);
					if(index!=-1){
					return this.ownGirl[index];
			}else{
			let info:GirlInfo=	new GirlInfo(id,this);
			if(info){
			this.ownGirlId.push(id);
			this.ownGirl.push(info);
			this.ownGirlUid.push(info.UId);
			return info;
			}else{
			return null;
			}
			}
			}	
		}

		if(typeof id =="string"){
			let index=this.ownGirlUid.indexOf(id);
			if(index!=-1){
				return this.ownGirl[index];
			}else{
				return null;
			}
		}
	}

	/**新加hero  并返回*/
	public   GetHero(id:string):HeroData;
	public   GetHero(id:number):HeroData;
	public   GetHero(id):HeroData{
		if(typeof id =="number"){
			let index=this.ownHeroId.indexOf(id);
		if(index!=-1){
			return this.ownHero[index];
		}else{
			let info:HeroData=	new HeroData(id);
			if(info){
			this.ownHeroId.push(id);
			this.ownHero.push(info);
			this.ownHeroUid.push(info.UId);
			return info;
			}else{
			return null;
			}
		}
		}

		if(typeof id =="string"){
			let index=this.ownHeroUid.indexOf(id);
			if(index!=-1){
				return this.ownHero[index];
			}else{
				return null;
			}
		}
	}


	public get Name():string{return this.name;};
	public set Name(value:string){this.name=value;}
	public get Level():number{return this.level;}
	public set Level(value :number){this.level=value;}
	public get FightingPower():number{return this.fightingPower;}
	public set FightingPower(value:number){this.fightingPower=value;}
	public get HeadIcon():string{return this.headIcon;}
	public set HeadIcon(value:string){this.headIcon=value;}

	public get OwnHero():HeroData[]{return this.ownHero;}
	public get OwnHeroID():number[]{return this.ownHeroId;}
	public get OwnHeroUid():string[]{return this.ownHeroUid;}	

	public get OwnGirl():GirlInfo[]{return this.ownGirl;}
	public get OwnGirlId():number[]{return this.ownGirlId;}
	public get OwnGirlUid():string[]{return this.ownGirlUid;}


	/**根据友好度获取拥有的girl*/
	public GetFriendlySortList():GirlInfo[]{
    this.ownGirl.sort((a,b)=>this.AddressListSort(a,b));
	this.ownGirlId.splice(0,this.ownGirlId.length);
	this.ownGirlUid.splice(0,this.ownGirlUid.length);
	this.ownGirl.forEach(element=>{
	this.ownGirlId.push(element.GirlId);
	this.ownGirlUid.push(element.UId);
	});
    return this.ownGirl;
    }
	
    public AddressListSort(a:GirlInfo,b:GirlInfo):number{
		if(b.FriendlyNum==a.FriendlyNum){
		 	return 	b.GirlId-a.GirlId;
		}
        return b.FriendlyNum-a.FriendlyNum;
    }








}