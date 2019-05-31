var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var game;
(function (game) {
    var ClientSCCharacterRevertHandler = (function () {
        function ClientSCCharacterRevertHandler() {
        }
        ClientSCCharacterRevertHandler.HandleMsg = function (msg) {
        };
        return ClientSCCharacterRevertHandler;
    }());
    game.ClientSCCharacterRevertHandler = ClientSCCharacterRevertHandler;
    __reflect(ClientSCCharacterRevertHandler.prototype, "game.ClientSCCharacterRevertHandler");
})(game || (game = {}));
//# sourceMappingURL=SCCharacterRevertHandler.js.map