
/**
 * created by sjz on 2018-5-31
 * 龙骨对象基类
 */
class DragonObjectBase extends egret.DisplayObjectContainer{

    private originX:number = 0;
    private originY:number = 0;
    private originZ:number = 0;
    private trueY:number = 0;

    public armature:DragonBonesArmatureContainer;

    private res_ske_json:string;
    private armatureName:string;
    private dragonBonesName:string;
    private playSpeed:number;
    private skeletonData:any;
    private texturePng:any;
    private textureData:any;
    private actionArray:string[];
    private oriAction:string;


    public constructor() {
        super();
    }

    public init(res_ske_json:string,armatureName:string,actionName?:string[],oriAction?:string,playSpeed:number=1):void{

        App.TimerManager.doFrame(1, 0, this.onFrame, this);
        if(!this.armature){
                   this.armature = new DragonBonesArmatureContainer();
                   this.addChild(this.armature);
        }

        this.armature.init();
        
        this.res_ske_json=res_ske_json + "_ske_json";
        this.armatureName=armatureName;
        this.actionArray=actionName;
        this.dragonBonesName=res_ske_json;
        this.playSpeed = playSpeed;
        this.oriAction=oriAction;
        RES.getResAsync(this.res_ske_json,this.LoadObjSkeJsonSuccess,this);
    }


    private LoadObjSkeJsonSuccess(data:any,key:string){
        this.skeletonData=data;
        RES.getResAsync(data.name+ "_tex_json",this.LoadObjTexJsonSuccess,this);
    }
    
    private LoadObjTexJsonSuccess(data:any,key:string){
        this.textureData=data;
        RES.getResAsync(data.name+ "_tex_png",this.LoadObjTexPngSuccess,this);
    }

    private LoadObjTexPngSuccess(data:any,key:string){
        this.texturePng=data;
        App.DragonBonesFactory.initArmatureFile(this.skeletonData, this.texturePng, this.textureData)
        this.createArmature(this.armatureName,this.actionArray,this.dragonBonesName,this.playSpeed);
        if(!this.oriAction||this.oriAction==""||this.oriAction==undefined)
        this.armature.play(this.actionArray[0],0);
        else
        this.armature.play(this.oriAction,0);
    }

    /**
     * 创建一个动画
     * @param armatureName 骨架数据名称
     * @param dragonBonesName - DragonBonesData 实例的缓存名称。 （如果未设置，将检索所有的 DragonBonesData 实例，当多个 DragonBonesData 实例中包含同名的骨架数据时，可能无法准确的创建出特定的骨架）
     *  
     */
    public createArmature(armatureName:string,actionName:string[],dragonBonesName?:string,playSpeed:number=1):void{
        this.armature.register(App.DragonBonesFactory.makeArmature(armatureName,dragonBonesName, playSpeed), actionName);
    }

    public destory():void{
        this.armature.stop();
        this.armature.destroy();
        App.TimerManager.remove(this.onFrame, this);
        App.DisplayUtils.removeFromParent(this);
        ObjectPool.push(this);
    }

    private onFrame(time:number):void{
        this.update(time);
        this.setPos();
    }

    public setPos():void{
        if(this.$getX() != this.originX){
            this.$setX(this.originX);
        }

        if(this.$getY() != this.trueY){
            this.$setY(this.trueY);
        }
    }

    public update(time:number):void{

    }

    //预留
    public registerArmature(actionName:string):void{
    }

    public set x(value:number) {
        this.originX = value;
    }

    public set y(value:number) {
        this.originY = value;
        this.trueY = this.originY + this.originZ;
    }

    public set z(value:number) {
        this.originZ = value;
        this.trueY = this.originY + this.originZ;
    }

    public get x():number {
        return this.originX;
    }

    public get y():number {
        return this.originY;
    }

    public get z():number {
        return this.originZ;
    }
}