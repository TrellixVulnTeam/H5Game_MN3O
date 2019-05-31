var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 *
 */
var BattleConst = (function () {
    function BattleConst() {
    }
    //战斗放大招的立绘
    BattleConst.SKILLPICTURE_C2C = 20001;
    //战斗残血出现的破损立绘
    BattleConst.HPPICTURE_C2C = 20002;
    return BattleConst;
}());
__reflect(BattleConst.prototype, "BattleConst");
//# sourceMappingURL=BattleConst.js.map