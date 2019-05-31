var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var BattleEditConst = (function () {
    function BattleEditConst() {
    }
    BattleEditConst.UpdateArrayList = 10000; //更新英雄列表
    BattleEditConst.ChangeTeam = 10001; //切换队伍
    BattleEditConst.ShowHeroList = 10002; //显示英雄列表
    BattleEditConst.AddHero = 10003; //添加英雄
    BattleEditConst.SetAddState = 10004; //设置添加按钮
    BattleEditConst.CheckCollision = 10005; //检测碰撞
    BattleEditConst.InitArray = 10006; //初始化队伍信息
    BattleEditConst.StartFightByArray = 10007; //从编队开启战斗
    return BattleEditConst;
}());
__reflect(BattleEditConst.prototype, "BattleEditConst");
//# sourceMappingURL=BattleEditConst.js.map