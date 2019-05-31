var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var CCG_GameConst = (function () {
    function CCG_GameConst() {
    }
    CCG_GameConst.GameInit = 10000; //初始化战斗信息
    CCG_GameConst.GameResize = 10001; //游戏重置
    CCG_GameConst.GameStart = 10002; //战斗开始
    CCG_GameConst.UpdateRound = 10003; //更新回合数
    CCG_GameConst.InitUI = 10004; //初始化ui
    CCG_GameConst.UpdateTimer = 10005; //更新时间
    CCG_GameConst.UpdateHpBar = 10006; //更新血条
    CCG_GameConst.OpenSkill = 10007; //打开技能
    CCG_GameConst.SwitchingFight = 10008; //切换战斗方式
    CCG_GameConst.FightAni = 10009; //战斗动画
    CCG_GameConst.FightConvert = 10010; //转换下场战斗
    CCG_GameConst.FightMaskViableTrue = 10011; //战斗表现
    CCG_GameConst.FightMaskViableFalse = 10012; //战斗表现
    CCG_GameConst.SetBackMainBtnVis = 10013; //返回主页按钮显隐
    return CCG_GameConst;
}());
__reflect(CCG_GameConst.prototype, "CCG_GameConst");
//# sourceMappingURL=CCG_GameConst.js.map