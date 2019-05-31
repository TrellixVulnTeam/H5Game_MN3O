var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var game;
(function (game) {
    var MsgHelper = (function () {
        function MsgHelper() {
            this.opcode = -1;
        }
        MsgHelper.prototype.Send = function (buf) {
            var msg = {};
            msg.key = this.opcode;
            msg.body = buf;
            App.Socket.send(msg);
        };
        return MsgHelper;
    }());
    game.MsgHelper = MsgHelper;
    __reflect(MsgHelper.prototype, "game.MsgHelper");
})(game || (game = {}));
//# sourceMappingURL=MsgHelper.js.map