
/**
 * @author sjz 
 * @time 2018-8-13 19:09
 */
class MemoryPool<T>{
    
    /**
     * @description 切勿单独操作此数组，如需增删请引用封装的函数
     * @description 此数组在此用作模拟队列来处理数据，遵循先进先出，所以请勿单独操作此数组
     */
    private mobjs:Array<T> = new Array<T>();
    public get Count() 
    {  
        return this.mobjs.length; 
    }
    private mMaxSize:number = 10;
    public constructor(maxSize:number=10){

    }

    public Alloc():T
    {
        let t:T = null;
        if ( this.mobjs.length > 0 )
        {
            t = this.mobjs.shift();
        }
        return t;
    }
    
    public Free(  t:T ):void
    {
        if ( this.mobjs.length < this.mMaxSize )
        {
            this.mobjs.push(t);
        }
    }
    public Dispose():void
    {
        this.mobjs.slice(0,this.mobjs.length);
    }

}