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
var ConfigEvent = (function (_super) {
    __extends(ConfigEvent, _super);
    function ConfigEvent(type, bubbles, cancelable, data) {
        if (bubbles === void 0) { bubbles = false; }
        if (cancelable === void 0) { cancelable = false; }
        return _super.call(this, type, bubbles, cancelable, data) || this;
    }
    ConfigEvent.ResLoaded = "ResLoaded";
    return ConfigEvent;
}(egret.Event));
__reflect(ConfigEvent.prototype, "ConfigEvent");
var AppointConfigEvent = (function (_super) {
    __extends(AppointConfigEvent, _super);
    function AppointConfigEvent() {
        return _super.call(this) || this;
    }
    return AppointConfigEvent;
}(egret.EventDispatcher));
__reflect(AppointConfigEvent.prototype, "AppointConfigEvent");
//# sourceMappingURL=ConfigEvent.js.map