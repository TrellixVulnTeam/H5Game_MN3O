var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * zsy
 */
var BattleInfoConst = (function () {
    function BattleInfoConst() {
    }
    BattleInfoConst.Admission_MAX = 12; //最多入场12人
    BattleInfoConst.Side_MAX = 6; //一个阵营6人
    return BattleInfoConst;
}());
__reflect(BattleInfoConst.prototype, "BattleInfoConst");
//# sourceMappingURL=BattleInfoConst.js.map