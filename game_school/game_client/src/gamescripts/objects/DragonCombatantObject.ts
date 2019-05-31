
class ActionStr {  
    public static Die: string = "dead";
    public static Move: string = "run";
    public static Stand: string = "idle";
    public static Hit1: string = "hit01";
    public static Hit2: string = "hit02";
    public static Hit3: string = "hit03";
    public static Hit4: string = "hit04";
    public static Win:  string = "win";
    public static Attack : string="attack";
    public static Chant : string="chant";
    public static Skill : string="skill";
}

class DragonCombatantObject extends DragonObjectBase {
	 public constructor(){
        super();
    }


	public init(res_ske_json:string,armatureName:string,actionName:string[],oriAction?:string,playSpeed:number=1):void {
        super.init(res_ske_json,armatureName,actionName,oriAction,playSpeed);

    }

    public destory(){
        super.destory();
    }

    public update(timer:number){
        super.update(timer);
    }

}