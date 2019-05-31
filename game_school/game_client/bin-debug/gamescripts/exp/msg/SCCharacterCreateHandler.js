var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var game;
(function (game) {
    var ClientSCCharacterCreateHandler = (function () {
        function ClientSCCharacterCreateHandler() {
        }
        ClientSCCharacterCreateHandler.HandleMsg = function (msg) {
        };
        return ClientSCCharacterCreateHandler;
    }());
    game.ClientSCCharacterCreateHandler = ClientSCCharacterCreateHandler;
    __reflect(ClientSCCharacterCreateHandler.prototype, "game.ClientSCCharacterCreateHandler");
})(game || (game = {}));
//# sourceMappingURL=SCCharacterCreateHandler.js.map