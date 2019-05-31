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
/**
 * Created by sjz on 2018-5-10.
 */
var Game_FightController = (function (_super) {
    __extends(Game_FightController, _super);
    function Game_FightController() {
        var _this = _super.call(this) || this;
        //View初始化
        _this.gameView = new CCG_FightGameView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.CCG_GameFight, _this.gameView);
        //Model初始化
        _this.gameModel = new CCG_GameModel(_this);
        _this.setModel(_this.gameModel);
        _this.RegisterEvent(EventDef.GameInit);
        _this.RegisterEvent(EventDef.GameResize);
        _this.RegisterEvent(EventDef.GameStart);
        _this.RegisterEvent(EventDef.UpdateRound);
        _this.RegisterEvent(EventDef.InitUI);
        _this.RegisterEvent(EventDef.UpdateTimer);
        _this.RegisterEvent(EventDef.UpdateHpBar);
        _this.RegisterEvent(EventDef.OpenSkill);
        _this.RegisterEvent(EventDef.SwitchingFight);
        _this.RegisterEvent(EventDef.FightAni);
        _this.RegisterEvent(EventDef.FightConvert);
        _this.RegisterEvent(EventDef.FightMaskViableTrue);
        _this.RegisterEvent(EventDef.FightMaskViableFalse);
        _this.RegisterEvent(EventDef.SetBackMainBtnVis);
        return _this;
    }
    Game_FightController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        switch (ev) {
            case EventDef.GameInit:
                this.gameInit(le.IntParam0, le.Object0);
                break;
            case EventDef.GameResize:
                this.gameResize();
                break;
            case EventDef.GameStart:
                this.gameStart();
                break;
            case EventDef.UpdateRound:
                this.UpdateRound(le.IntParam0);
                break;
            case EventDef.InitUI:
                this.InitGameUI(le.Object0);
                break;
            case EventDef.UpdateTimer:
                this.UpdateTimer(le.IntParam0);
                break;
            case EventDef.UpdateHpBar:
                this.UpdateHpBar(le.IntParam0, le.IntParam1);
                break;
            case EventDef.OpenSkill:
                this.UpdateSkill(le.Object0, le.Object1);
                break;
            case EventDef.SwitchingFight:
                this.SwitchingFightStyle(le.Object0);
                break;
            case EventDef.FightAni:
                this.PlayFightAni(le.Object0);
                break;
            case EventDef.FightConvert:
                this.FightConvert(le.Object0);
                break;
            case EventDef.FightMaskViableTrue:
                this.FightMaskViableTrue(le.StrParam0);
                break;
            case EventDef.FightMaskViableFalse:
                this.FightMaskViableFalse(le.StrParam0);
                break;
            case EventDef.SetBackMainBtnVis:
                this.SetBackMainBtnVis(le.Object0);
                break;
        }
    };
    /**
     * 战斗表现
     */
    Game_FightController.prototype.FightMaskViableTrue = function (objUID) {
        this.gameView.setObjMaskViewIndex(objUID, true);
    };
    /**
     * 战斗表现
     */
    Game_FightController.prototype.FightMaskViableFalse = function (objUID) {
        this.gameView.setObjMaskViewIndex(objUID, false);
    };
    /**
     * 战斗转换
     */
    Game_FightController.prototype.FightConvert = function (callback) {
        this.gameView.FightConvert(callback);
    };
    /**
     * 播放战斗动画
     */
    Game_FightController.prototype.PlayFightAni = function (callback) {
        this.gameView.PlayFightAni(callback);
    };
    /**
     * 战斗数据
     */
    Game_FightController.prototype.gameInit = function (mapId, arrayInfos) {
        this.gameModel.InitGameData(mapId, arrayInfos);
        this.gameStart();
    };
    /**
     * 显隐返回主界面按钮
     */
    Game_FightController.prototype.SetBackMainBtnVis = function (vis) {
        if (this.gameModel.mapId != 1001) {
            this.gameView.SetBackMainBtnVis(vis);
        }
    };
    /**
     * 战斗开始
     */
    Game_FightController.prototype.gameStart = function () {
        if (this.gameModel.mapId == 1001) {
            this.gameView.SetBackMainBtnVis(false);
        }
        else {
            this.gameView.SetBackMainBtnVis(true);
        }
        App.FightManager.InitData(this.gameModel.mapId, this.gameModel.onwerplayerData, this.gameModel.enemyplayerData, this.gameView); //初始化战斗人员数据
    };
    /**
     * 更新回合数
     */
    Game_FightController.prototype.UpdateRound = function (roundCount) {
        this.gameView.UpdateRound(roundCount);
    };
    /**
     * 更新时间
     */
    Game_FightController.prototype.UpdateTimer = function (timer) {
        this.gameView.UpdateTimer(timer);
    };
    /**
     * 初始化ui
     */
    Game_FightController.prototype.InitGameUI = function (fightInfo) {
        this.gameView.InitGameUI(fightInfo);
    };
    /**
     * 更新血条
     */
    Game_FightController.prototype.UpdateHpBar = function (camp, value) {
        this.gameView.UpdateHpBar(camp, value);
    };
    /**
     * 更新技能
     */
    Game_FightController.prototype.UpdateSkill = function (own, skills) {
        this.gameView.OpenSkillGroup(own, skills);
    };
    /**
     * 切换战斗
     */
    Game_FightController.prototype.SwitchingFightStyle = function (auto) {
        this.gameView.SwitchingFightStyle(auto);
    };
    Game_FightController.prototype.gameResize = function () {
        //this.gameView.resize();
    };
    return Game_FightController;
}(BaseController));
__reflect(Game_FightController.prototype, "Game_FightController");
//# sourceMappingURL=Game_FightController.js.map