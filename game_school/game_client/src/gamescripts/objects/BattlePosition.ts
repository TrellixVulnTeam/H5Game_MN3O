 /**
  * 站位
  */
enum Arrange{
FRONTROW,//前排
BACKROW//后排
}

class BattlePosition {
	private index:number;//位置
	private selfArrAnger:Arrange;//站位（前排后排）
	private lineNum:number;//行号
	private beLongCamp:Camp;//所属阵营
	private pos:egret.Point//站位坐标
	private x:number;//x
	private y:number;//y
	private prepPos:egret.Point;//战斗开始前位置，生成时赋值，由此跑到战斗位置
	private posOffset:number=300;//上场位置和站位偏移
	private turnOffset:number=500;//站位和跳转位置偏移
	private turningPos:egret.Point;//战斗结束往前跑的位置

	public constructor() {
		this.pos=new egret.Point();
		this.prepPos=new egret.Point();
		this.turningPos=new egret.Point();
		
	}

	public InitDisPos(index:number,point:egret.Point){
		this.pos=point;
		this.index=index;
		this.selfArrAnger=0;//站位（前排后排）
		this.lineNum=0;//行号
	}

	/**
	 * 初始化
	 */
	public InitPos(index:number,point:egret.Point){
	
		this. index=index+1;
		//不能直接将point赋值，赋值的是内存地址
		this. pos.x=point.x;
		this. pos.y=point.y;

		this. prepPos.x=point.x;
		this. prepPos.y=point.y;

		this. turningPos.x=point.x;
		this. turningPos.y=point.y;

		if(this.index>0&&this.index<=BattleInfoConst.Admission_MAX){
			if(this.index<7){
				this.beLongCamp=Camp.Friendly;
				if((this.index/3)>1){
					this.selfArrAnger=Arrange.BACKROW;
				}else{
					this.selfArrAnger=Arrange.FRONTROW;
				}
				this.prepPos.x-=this.posOffset;
				this. turningPos.x+=this.turnOffset;
			}else{
				this.beLongCamp=Camp.Hostility;
				if(((this.index-6)/3)>1){
					this.selfArrAnger=Arrange.BACKROW;
				}else{
					this.selfArrAnger=Arrange.FRONTROW;
				}
				this.prepPos.x+=this.posOffset;
				this. turningPos.x+=0;
			}
			if(this.index%3==0)this.lineNum=3;
			else
			this.lineNum=this.index%3;
		}
	}




	public get Index():number{return this.index; }
	public get SelfArrAnger():Arrange{return this.selfArrAnger}
	public get LineNum():number{return this.lineNum;}
	public get BeLongCamp():Camp{return this.beLongCamp;}
	public get Pos():egret.Point{return this.pos;}
	public get X():number{return this.pos.x;}
	public get Y():number{return this.pos.y;}
	public get PrepPos():egret.Point{return this.prepPos;}
	public get TurningPos():egret.Point{return this.turningPos;}

}