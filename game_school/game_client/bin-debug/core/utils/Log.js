var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**Log工具，用于正式版本统一控制Log输出 */
var Log = (function () {
    function Log() {
    }
    /**
     * Debug_Log
     * @param messsage 内容
     * @constructor
     */
    Log.trace = function () {
        var optionalParams = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            optionalParams[_i] = arguments[_i];
        }
        if (App.DebugUtils.isDebug) {
            optionalParams[0] = "[DebugLog]" + optionalParams[0];
            console.log.apply(console, optionalParams);
        }
    };
    /**
    * Waring_Log
    * @param messsage 内容
    * @constructor
    */
    Log.Waring = function () {
        var optionalParams = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            optionalParams[_i] = arguments[_i];
        }
        if (App.DebugUtils.isDebug) {
            optionalParams[0] = "[WaringLog]" + optionalParams[0];
            console.warn.apply(console, optionalParams);
        }
    };
    /**
    * Error_Log
    * @param messsage 内容
    * @constructor
    */
    Log.Error = function () {
        var optionalParams = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            optionalParams[_i] = arguments[_i];
        }
        if (App.DebugUtils.isDebug) {
            optionalParams[0] = "[ErrorLog]" + optionalParams[0];
            console.warn.apply(console, optionalParams);
        }
    };
    return Log;
}());
__reflect(Log.prototype, "Log");
//# sourceMappingURL=Log.js.map