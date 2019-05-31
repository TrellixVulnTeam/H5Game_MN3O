var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var game;
(function (game) {
    var SCCharacterRevertHandler = (function () {
        function SCCharacterRevertHandler() {
        }
        SCCharacterRevertHandler.HandleMsg = function (_msg) {
            var msg = _msg;
            game.ClientSCCharacterRevertHandler.HandleMsg(msg);
        };
        return SCCharacterRevertHandler;
    }());
    game.SCCharacterRevertHandler = SCCharacterRevertHandler;
    __reflect(SCCharacterRevertHandler.prototype, "game.SCCharacterRevertHandler");
    var SCDroppedHumanHintHandler = (function () {
        function SCDroppedHumanHintHandler() {
        }
        SCDroppedHumanHintHandler.HandleMsg = function (_msg) {
            var msg = _msg;
            game.ClientSCDroppedHumanHintHandler.HandleMsg(msg);
        };
        return SCDroppedHumanHintHandler;
    }());
    game.SCDroppedHumanHintHandler = SCDroppedHumanHintHandler;
    __reflect(SCDroppedHumanHintHandler.prototype, "game.SCDroppedHumanHintHandler");
    var SCCharacterDeleteHandler = (function () {
        function SCCharacterDeleteHandler() {
        }
        SCCharacterDeleteHandler.HandleMsg = function (_msg) {
            var msg = _msg;
            game.ClientSCCharacterDeleteHandler.HandleMsg(msg);
        };
        return SCCharacterDeleteHandler;
    }());
    game.SCCharacterDeleteHandler = SCCharacterDeleteHandler;
    __reflect(SCCharacterDeleteHandler.prototype, "game.SCCharacterDeleteHandler");
    var SCCharacterCreateHandler = (function () {
        function SCCharacterCreateHandler() {
        }
        SCCharacterCreateHandler.HandleMsg = function (_msg) {
            var msg = _msg;
            game.ClientSCCharacterCreateHandler.HandleMsg(msg);
        };
        return SCCharacterCreateHandler;
    }());
    game.SCCharacterCreateHandler = SCCharacterCreateHandler;
    __reflect(SCCharacterCreateHandler.prototype, "game.SCCharacterCreateHandler");
    var SCCharacterLoginHandler = (function () {
        function SCCharacterLoginHandler() {
        }
        SCCharacterLoginHandler.HandleMsg = function (_msg) {
            var msg = _msg;
            game.ClientSCCharacterLoginHandler.HandleMsg(msg);
        };
        return SCCharacterLoginHandler;
    }());
    game.SCCharacterLoginHandler = SCCharacterLoginHandler;
    __reflect(SCCharacterLoginHandler.prototype, "game.SCCharacterLoginHandler");
    var SCLoginGateHandler = (function () {
        function SCLoginGateHandler() {
        }
        SCLoginGateHandler.HandleMsg = function (_msg) {
            var msg = _msg;
            game.ClientSCLoginGateHandler.HandleMsg(msg);
        };
        return SCLoginGateHandler;
    }());
    game.SCLoginGateHandler = SCLoginGateHandler;
    __reflect(SCLoginGateHandler.prototype, "game.SCLoginGateHandler");
})(game || (game = {}));
//# sourceMappingURL=MsgCommonHandler.js.map