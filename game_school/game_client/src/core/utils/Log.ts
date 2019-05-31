
/**Log工具，用于正式版本统一控制Log输出 */
class Log {
    /**
     * Debug_Log
     * @param messsage 内容
     * @constructor
     */
    public static trace(...optionalParams:any[]):void {
        if (App.DebugUtils.isDebug) {
            optionalParams[0] = "[DebugLog]" + optionalParams[0];
            console.log.apply(console, optionalParams);
        }
    }

     /**
     * Waring_Log
     * @param messsage 内容
     * @constructor
     */
    public static Waring(...optionalParams:any[]):void{
        if (App.DebugUtils.isDebug) {
            optionalParams[0] = "[WaringLog]" + optionalParams[0];
            console.warn.apply(console, optionalParams);
        }
    }

     /**
     * Error_Log
     * @param messsage 内容
     * @constructor
     */
    public static Error(...optionalParams:any[]):void{
        if (App.DebugUtils.isDebug) {
            optionalParams[0] = "[ErrorLog]" + optionalParams[0];
            console.warn.apply(console, optionalParams);
        }

    }


}