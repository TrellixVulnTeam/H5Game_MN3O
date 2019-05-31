var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var __extends = this && this.__extends || function __extends(t, e) { 
 function r() { 
 this.constructor = t;
}
for (var i in e) e.hasOwnProperty(i) && (t[i] = e[i]);
r.prototype = e.prototype, t.prototype = new r();
};
/**
 * strConfig管理
*/
var StrConfigManager = (function (_super) {
    __extends(StrConfigManager, _super);
    function StrConfigManager() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    /**
     * get str
    */
    StrConfigManager.getStrById = function (strId) {
        var config = StrConfig.GetConfig(strId);
        if (config != null) {
            return config.str;
        }
        else {
            return "";
        }
    };
    /**
     * get Format str
    */
    StrConfigManager.GetStringFormatById = function (strId, replaceStr) {
        var str = "";
        var config = StrConfig.GetConfig(strId);
        if (config != null) {
            str = config.str;
            for (var index = 0; index < replaceStr.length; index++) {
                str = this.replaceString(str, replaceStr[index]);
            }
        }
        return str;
    };
    /**
     * 设置带颜色的str
    */
    StrConfigManager.SetLabelColorTextById = function (label, strId) {
        var config = StrConfig.GetConfig(strId);
        if (config != null) {
            this.SetLabelColorTextByStr(label, config.str);
        }
    };
    /**
     * 设置带颜色的str
    */
    StrConfigManager.SetLabelColorTextByStr = function (label, str) {
        if (label != null) {
            var resultStr = str;
            var resultColor = 0;
            var flagBegin = str.indexOf("[", 0);
            var flagEnd = str.indexOf("]", flagBegin + 1);
            if (flagBegin != -1 && flagBegin < flagEnd) {
                var str1 = str.substring(flagBegin, flagEnd + 1);
                var str2 = str.substring(flagBegin + 1, flagEnd);
                resultStr = str.replace(str1, "");
                resultColor = Number(str2);
            }
            label.text = resultStr;
            label.textColor = resultColor;
        }
    };
    /**
     * 设置Format str
    */
    StrConfigManager.SetLabelFormatById = function (label, strId, replaceStr) {
        var config = StrConfig.GetConfig(strId);
        if (label != null && config != null) {
            var str = config.str;
            for (var index = 0; index < replaceStr.length; index++) {
                str = this.replaceString(str, replaceStr[index]);
            }
            label.text = str;
        }
    };
    StrConfigManager.replaceString = function (str, reStr) {
        return str.replace("{}", reStr);
    };
    return StrConfigManager;
}(BaseManager));
__reflect(StrConfigManager.prototype, "StrConfigManager");
//# sourceMappingURL=StrConfigManager.js.map