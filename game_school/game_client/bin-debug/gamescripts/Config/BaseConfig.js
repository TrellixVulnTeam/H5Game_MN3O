var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var BaseConfig = (function () {
    function BaseConfig() {
    }
    BaseConfig.GetAsset = function (name) {
        return null;
    };
    BaseConfig.isUseLocalTable = true;
    BaseConfig.bytespath = "resource/resource_json/config_json/bytes/";
    return BaseConfig;
}());
__reflect(BaseConfig.prototype, "BaseConfig");
//# sourceMappingURL=BaseConfig.js.map