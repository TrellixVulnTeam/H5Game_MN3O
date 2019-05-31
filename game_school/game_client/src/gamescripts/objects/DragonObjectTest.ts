
class DragonObjectTest extends DragonObjectBase{
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