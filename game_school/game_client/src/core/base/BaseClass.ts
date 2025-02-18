/**
 * 
 * 基类
 */
class BaseClass {
    public constructor() {

    }

    /**
     * 获取一个单例
     * @returns {any}
     */
    public static getInstance(...args:any[]):any {
        var Class:any = this;
        if (!Class._instance) {
            var argsLen:number = args.length;
            Class._instance = new Class(...args);
        }
        return Class._instance;
    }
}