var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var game;
(function (game) {
    var MsgHandlerFact = (function () {
        function MsgHandlerFact() {
        }
        MsgHandlerFact.Build = function () {
            App.MessageCenter.addListener(MsgDef.msgid_SCCharacterRevert.toString(), game.SCCharacterRevertHandler.HandleMsg, this);
            App.MessageCenter.addListener(MsgDef.msgid_SCDroppedHumanHint.toString(), game.SCDroppedHumanHintHandler.HandleMsg, this);
            App.MessageCenter.addListener(MsgDef.msgid_SCCharacterDelete.toString(), game.SCCharacterDeleteHandler.HandleMsg, this);
            App.MessageCenter.addListener(MsgDef.msgid_SCCharacterCreate.toString(), game.SCCharacterCreateHandler.HandleMsg, this);
            App.MessageCenter.addListener(MsgDef.msgid_SCCharacterLogin.toString(), game.SCCharacterLoginHandler.HandleMsg, this);
            App.MessageCenter.addListener(MsgDef.msgid_SCLoginGate.toString(), game.SCLoginGateHandler.HandleMsg, this);
        };
        return MsgHandlerFact;
    }());
    game.MsgHandlerFact = MsgHandlerFact;
    __reflect(MsgHandlerFact.prototype, "game.MsgHandlerFact");
})(game || (game = {}));
//# sourceMappingURL=MsgHandlerFact.js.map