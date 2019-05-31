var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var game;
(function (game) {
    var ClientSCDroppedHumanHintHandler = (function () {
        function ClientSCDroppedHumanHintHandler() {
        }
        ClientSCDroppedHumanHintHandler.HandleMsg = function (msg) {
        };
        return ClientSCDroppedHumanHintHandler;
    }());
    game.ClientSCDroppedHumanHintHandler = ClientSCDroppedHumanHintHandler;
    __reflect(ClientSCDroppedHumanHintHandler.prototype, "game.ClientSCDroppedHumanHintHandler");
})(game || (game = {}));
//# sourceMappingURL=SCDroppedHumanHintHandler.js.map