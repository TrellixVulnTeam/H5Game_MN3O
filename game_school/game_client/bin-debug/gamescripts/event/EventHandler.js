var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * @author sjz
 * @time 2018-8-13 5:21
 * @description 事件管理器
 */
var EventHandler = (function () {
    function EventHandler() {
        this.mhandler = null;
    }
    EventHandler.prototype.RegisterEvent = function (ev) {
        App.EventMgrHelper.RegisterEventHandler(ev, this);
    };
    EventHandler.prototype.UnRegisterEvent = function (ev) {
        App.EventMgrHelper.UnRegisterEventHandler(ev, this);
    };
    EventHandler.prototype.HandleEvent = function (ev, le) {
        if (this.mhandler != null) {
            this.mhandler(ev, le);
        }
    };
    Object.defineProperty(EventHandler.prototype, "Handler", {
        set: function (value) {
            this.mhandler = value;
        },
        enumerable: true,
        configurable: true
    });
    return EventHandler;
}());
__reflect(EventHandler.prototype, "EventHandler");
//# sourceMappingURL=EventHandler.js.map