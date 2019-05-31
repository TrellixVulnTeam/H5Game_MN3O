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
var game;
(function (game) {
    var CSLoginEndedHelper = (function (_super) {
        __extends(CSLoginEndedHelper, _super);
        function CSLoginEndedHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSLoginEnded();
            _this.opcode = MsgDef.msgid_CSLoginEnded;
            return _this;
        }
        CSLoginEndedHelper.prototype.Send = function () {
            var buf = GeneralMes.CSLoginEnded.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSLoginEndedHelper;
    }(game.MsgHelper));
    game.CSLoginEndedHelper = CSLoginEndedHelper;
    __reflect(CSLoginEndedHelper.prototype, "game.CSLoginEndedHelper");
    var CSKickDroppedHumanHelper = (function (_super) {
        __extends(CSKickDroppedHumanHelper, _super);
        function CSKickDroppedHumanHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSKickDroppedHuman();
            _this.opcode = MsgDef.msgid_CSKickDroppedHuman;
            return _this;
        }
        CSKickDroppedHumanHelper.prototype.Send = function () {
            var buf = GeneralMes.CSKickDroppedHuman.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSKickDroppedHumanHelper;
    }(game.MsgHelper));
    game.CSKickDroppedHumanHelper = CSKickDroppedHumanHelper;
    __reflect(CSKickDroppedHumanHelper.prototype, "game.CSKickDroppedHumanHelper");
    var CSCharacterEnterWorldHelper = (function (_super) {
        __extends(CSCharacterEnterWorldHelper, _super);
        function CSCharacterEnterWorldHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSCharacterEnterWorld();
            _this.opcode = MsgDef.msgid_CSCharacterEnterWorld;
            return _this;
        }
        CSCharacterEnterWorldHelper.prototype.Send = function () {
            var buf = GeneralMes.CSCharacterEnterWorld.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSCharacterEnterWorldHelper;
    }(game.MsgHelper));
    game.CSCharacterEnterWorldHelper = CSCharacterEnterWorldHelper;
    __reflect(CSCharacterEnterWorldHelper.prototype, "game.CSCharacterEnterWorldHelper");
    var CSCharacterLoginHelper = (function (_super) {
        __extends(CSCharacterLoginHelper, _super);
        function CSCharacterLoginHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSCharacterLogin();
            _this.opcode = MsgDef.msgid_CSCharacterLogin;
            return _this;
        }
        CSCharacterLoginHelper.prototype.Send = function () {
            var buf = GeneralMes.CSCharacterLogin.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSCharacterLoginHelper;
    }(game.MsgHelper));
    game.CSCharacterLoginHelper = CSCharacterLoginHelper;
    __reflect(CSCharacterLoginHelper.prototype, "game.CSCharacterLoginHelper");
    var CSCharacterDeleteHelper = (function (_super) {
        __extends(CSCharacterDeleteHelper, _super);
        function CSCharacterDeleteHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSCharacterDelete();
            _this.opcode = MsgDef.msgid_CSCharacterDelete;
            return _this;
        }
        CSCharacterDeleteHelper.prototype.Send = function () {
            var buf = GeneralMes.CSCharacterDelete.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSCharacterDeleteHelper;
    }(game.MsgHelper));
    game.CSCharacterDeleteHelper = CSCharacterDeleteHelper;
    __reflect(CSCharacterDeleteHelper.prototype, "game.CSCharacterDeleteHelper");
    var CSCharacterCreateHelper = (function (_super) {
        __extends(CSCharacterCreateHelper, _super);
        function CSCharacterCreateHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSCharacterCreate();
            _this.opcode = MsgDef.msgid_CSCharacterCreate;
            return _this;
        }
        CSCharacterCreateHelper.prototype.Send = function () {
            var buf = GeneralMes.CSCharacterCreate.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSCharacterCreateHelper;
    }(game.MsgHelper));
    game.CSCharacterCreateHelper = CSCharacterCreateHelper;
    __reflect(CSCharacterCreateHelper.prototype, "game.CSCharacterCreateHelper");
    var CSCharacterRevertHelper = (function (_super) {
        __extends(CSCharacterRevertHelper, _super);
        function CSCharacterRevertHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSCharacterRevert();
            _this.opcode = MsgDef.msgid_CSCharacterRevert;
            return _this;
        }
        CSCharacterRevertHelper.prototype.Send = function () {
            var buf = GeneralMes.CSCharacterRevert.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSCharacterRevertHelper;
    }(game.MsgHelper));
    game.CSCharacterRevertHelper = CSCharacterRevertHelper;
    __reflect(CSCharacterRevertHelper.prototype, "game.CSCharacterRevertHelper");
    var CSLoginGateHelper = (function (_super) {
        __extends(CSLoginGateHelper, _super);
        function CSLoginGateHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSLoginGate();
            _this.opcode = MsgDef.msgid_CSLoginGate;
            return _this;
        }
        CSLoginGateHelper.prototype.Send = function () {
            var buf = GeneralMes.CSLoginGate.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSLoginGateHelper;
    }(game.MsgHelper));
    game.CSLoginGateHelper = CSLoginGateHelper;
    __reflect(CSLoginGateHelper.prototype, "game.CSLoginGateHelper");
    var CSLoginBeganHelper = (function (_super) {
        __extends(CSLoginBeganHelper, _super);
        function CSLoginBeganHelper() {
            var _this = _super.call(this) || this;
            _this.msg = new GeneralMes.CSLoginBegan();
            _this.opcode = MsgDef.msgid_CSLoginBegan;
            return _this;
        }
        CSLoginBeganHelper.prototype.Send = function () {
            var buf = GeneralMes.CSLoginBegan.encode(this.msg).finish();
            _super.prototype.Send.call(this, buf);
        };
        return CSLoginBeganHelper;
    }(game.MsgHelper));
    game.CSLoginBeganHelper = CSLoginBeganHelper;
    __reflect(CSLoginBeganHelper.prototype, "game.CSLoginBeganHelper");
})(game || (game = {}));
//# sourceMappingURL=MsgCommonHelper.js.map