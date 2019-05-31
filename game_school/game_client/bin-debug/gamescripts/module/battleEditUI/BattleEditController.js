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
 * 战斗编辑控制
 */
var BattleEditController = (function (_super) {
    __extends(BattleEditController, _super);
    function BattleEditController() {
        var _this = _super.call(this) || this;
        //View战斗编辑
        _this.editView = new BattleEditMainView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.BattleEdit, _this.editView);
        //布阵
        _this.arrayView = new BattleArrayEditView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.BattleArray, _this.arrayView);
        //Model
        _this.editModel = new BattleEditModel(_this);
        _this.setModel(_this.editModel);
        //注册模块消息
        _this.RegisterEvent(EventDef.UpdateArrayList);
        _this.RegisterEvent(EventDef.ChangeTeam);
        _this.RegisterEvent(EventDef.ShowHeroList);
        _this.RegisterEvent(EventDef.AddHero);
        _this.RegisterEvent(EventDef.SetAddState);
        _this.RegisterEvent(EventDef.CheckCollision);
        _this.RegisterEvent(EventDef.InitArray);
        _this.RegisterEvent(EventDef.StartFightByArray);
        return _this;
    }
    BattleEditController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        switch (ev) {
            case EventDef.UpdateArrayList:
                this.UpdateArrayList();
                break;
            case EventDef.ChangeTeam:
                this.ChangeTeam(le.IntParam0);
                break;
            case EventDef.ShowHeroList:
                this.ShowHeroList(le.IntParam0);
                break;
            case EventDef.AddHero:
                this.AddHero(le.IntParam0);
                break;
            case EventDef.SetAddState:
                this.SetAddBtnState(le.Object0);
                break;
            case EventDef.CheckCollision:
                this.CheckCollisionImage(le.Object0, le.Object1);
                break;
            case EventDef.InitArray:
                this.InitArray(le.Object0, le.IntParam0);
                break;
            case EventDef.StartFightByArray:
                this.StartFightByArray(le.IntParam0);
                break;
        }
    };
    /**更新列表 */
    BattleEditController.prototype.UpdateArrayList = function () {
        this.editView.UpdateUI(this.editModel.GetAllHero());
    };
    /**更改队伍 */
    BattleEditController.prototype.ChangeTeam = function (index) {
        this.arrayView.ChangeTeam(this.editModel.GetTeamByIndex(index));
    };
    /**显示列表 */
    BattleEditController.prototype.ShowHeroList = function (index) {
        this.editModel.currentIndex = index;
        App.ViewManager.open(ViewConst.BattleEdit);
    };
    /**添加英雄到队伍 */
    BattleEditController.prototype.AddHero = function (id) {
        if (this.editModel.AddToCurrentArray(id))
            this.arrayView.ChangeTeam(this.editModel.GetTeamByIndex(this.editModel.currentTeam));
    };
    /**设置所有添加按钮状态 */
    BattleEditController.prototype.SetAddBtnState = function (state) {
        this.arrayView.SetAddBtnVisible(state);
    };
    /**检测人物是否与站位碰撞 */
    BattleEditController.prototype.CheckCollisionImage = function (demObj, disObj) {
        var tempDis = this.arrayView.HitCheckAllPoint(disObj);
        if (tempDis != null && this.editModel.ExchangePoint(demObj.indexPos, tempDis.indexPos)) {
            this.arrayView.ChangeTeam(this.editModel.GetTeamByIndex(this.editModel.currentTeam));
        }
        else {
            demObj.BackInPlace();
        }
    };
    /**检测人物是否与站位碰撞 */
    BattleEditController.prototype.CheckCollision = function (demObj, disObj) {
        var tempDis = this.arrayView.HitCheckAllPoint(disObj);
        if (tempDis != null && this.editModel.ExchangePoint(demObj.posInfo.Index, tempDis.indexPos)) {
            this.arrayView.ChangeTeam(this.editModel.GetTeamByIndex(this.editModel.currentTeam));
        }
        else {
            demObj.BackInPlace();
        }
    };
    /**初始化站位信息 */
    BattleEditController.prototype.InitArray = function (action, index) {
        this.editModel.InitArrayInfo(action, index);
    };
    /**开始战斗 */
    BattleEditController.prototype.StartFightByArray = function (mapId) {
        App.ViewManager.open(ViewConst.CCG_GameFight, mapId);
        App.EventMgrHelper.PushEventEx(EventDef.GameInit, this.editModel.GetTeamByIndex(this.editModel.currentTeam), null, mapId, 0, "", "");
    };
    return BattleEditController;
}(BaseController));
__reflect(BattleEditController.prototype, "BattleEditController");
//# sourceMappingURL=BattleEditController.js.map