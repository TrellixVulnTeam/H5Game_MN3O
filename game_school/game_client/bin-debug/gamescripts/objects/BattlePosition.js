var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * 站位
 */
var Arrange;
(function (Arrange) {
    Arrange[Arrange["FRONTROW"] = 0] = "FRONTROW";
    Arrange[Arrange["BACKROW"] = 1] = "BACKROW"; //后排
})(Arrange || (Arrange = {}));
var BattlePosition = (function () {
    function BattlePosition() {
        this.posOffset = 300; //上场位置和站位偏移
        this.turnOffset = 500; //站位和跳转位置偏移
        this.pos = new egret.Point();
        this.prepPos = new egret.Point();
        this.turningPos = new egret.Point();
    }
    BattlePosition.prototype.InitDisPos = function (index, point) {
        this.pos = point;
        this.index = index;
        this.selfArrAnger = 0; //站位（前排后排）
        this.lineNum = 0; //行号
    };
    /**
     * 初始化
     */
    BattlePosition.prototype.InitPos = function (index, point) {
        this.index = index + 1;
        //不能直接将point赋值，赋值的是内存地址
        this.pos.x = point.x;
        this.pos.y = point.y;
        this.prepPos.x = point.x;
        this.prepPos.y = point.y;
        this.turningPos.x = point.x;
        this.turningPos.y = point.y;
        if (this.index > 0 && this.index <= BattleInfoConst.Admission_MAX) {
            if (this.index < 7) {
                this.beLongCamp = Camp.Friendly;
                if ((this.index / 3) > 1) {
                    this.selfArrAnger = Arrange.BACKROW;
                }
                else {
                    this.selfArrAnger = Arrange.FRONTROW;
                }
                this.prepPos.x -= this.posOffset;
                this.turningPos.x += this.turnOffset;
            }
            else {
                this.beLongCamp = Camp.Hostility;
                if (((this.index - 6) / 3) > 1) {
                    this.selfArrAnger = Arrange.BACKROW;
                }
                else {
                    this.selfArrAnger = Arrange.FRONTROW;
                }
                this.prepPos.x += this.posOffset;
                this.turningPos.x += 0;
            }
            if (this.index % 3 == 0)
                this.lineNum = 3;
            else
                this.lineNum = this.index % 3;
        }
    };
    Object.defineProperty(BattlePosition.prototype, "Index", {
        get: function () { return this.index; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BattlePosition.prototype, "SelfArrAnger", {
        get: function () { return this.selfArrAnger; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BattlePosition.prototype, "LineNum", {
        get: function () { return this.lineNum; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BattlePosition.prototype, "BeLongCamp", {
        get: function () { return this.beLongCamp; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BattlePosition.prototype, "Pos", {
        get: function () { return this.pos; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BattlePosition.prototype, "X", {
        get: function () { return this.pos.x; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BattlePosition.prototype, "Y", {
        get: function () { return this.pos.y; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BattlePosition.prototype, "PrepPos", {
        get: function () { return this.prepPos; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(BattlePosition.prototype, "TurningPos", {
        get: function () { return this.turningPos; },
        enumerable: true,
        configurable: true
    });
    return BattlePosition;
}());
__reflect(BattlePosition.prototype, "BattlePosition");
//# sourceMappingURL=BattlePosition.js.map