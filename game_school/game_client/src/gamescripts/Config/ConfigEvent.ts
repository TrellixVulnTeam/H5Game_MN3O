class ConfigEvent extends egret.Event       
{
    public static ResLoaded:string = "ResLoaded";

    public constructor(type:string, bubbles:boolean = false, cancelable:boolean = false, data?: any)    
    {             
        super(type, bubbles, cancelable, data);
    }
}

class AppointConfigEvent extends egret.EventDispatcher
{
    public constructor()
    {
        super();
    }
}