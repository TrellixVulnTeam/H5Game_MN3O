var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var game;
(function (game) {
    var ClientSCLoginGateHandler = (function () {
        function ClientSCLoginGateHandler() {
        }
        ClientSCLoginGateHandler.HandleMsg = function (msg) {
            Log.trace("msgtest:" + msg.result);
        };
        return ClientSCLoginGateHandler;
    }());
    game.ClientSCLoginGateHandler = ClientSCLoginGateHandler;
    __reflect(ClientSCLoginGateHandler.prototype, "game.ClientSCLoginGateHandler");
})(game || (game = {}));
//# sourceMappingURL=SCLoginGateHandler.js.map