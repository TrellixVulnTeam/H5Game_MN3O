var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var game;
(function (game) {
    var ClientSCCharacterDeleteHandler = (function () {
        function ClientSCCharacterDeleteHandler() {
        }
        ClientSCCharacterDeleteHandler.HandleMsg = function (msg) {
        };
        return ClientSCCharacterDeleteHandler;
    }());
    game.ClientSCCharacterDeleteHandler = ClientSCCharacterDeleteHandler;
    __reflect(ClientSCCharacterDeleteHandler.prototype, "game.ClientSCCharacterDeleteHandler");
})(game || (game = {}));
//# sourceMappingURL=SCCharacterDeleteHandler.js.map