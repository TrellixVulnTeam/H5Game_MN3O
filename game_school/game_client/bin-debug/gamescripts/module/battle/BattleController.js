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
 *
 */
var BattleController = (function (_super) {
    __extends(BattleController, _super);
    function BattleController() {
        var _this = _super.call(this) || this;
        //初始化Proxy
        _this.battleProxy = new BattleProxy(_this);
        //初始化Model
        _this.battleModel = new BattleModel(_this);
        _this.setModel(_this.battleModel);
        //初始化战斗主界面
        _this.battleMainView = new BattleMainView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.BattleMain, _this.battleMainView);
        //初始化战斗结算
        _this.battleView = new BattleResultView(_this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.BattleResult, _this.battleView);
        //初始化战斗立绘
        _this.battlePictureView = new BattlePictureView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.BattlePicture, _this.battlePictureView);
        _this.RegisterEvent(EventDef.SKILLPICTURE_C2C);
        _this.RegisterEvent(EventDef.HPPICTURE_C2C);
        return _this;
    }
    BattleController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        switch (ev) {
            case EventDef.SKILLPICTURE_C2C:
                this.onSkillPictre(le.IntParam0, le.Object0);
                break;
            case EventDef.HPPICTURE_C2C:
                this.onHPPictre(le.IntParam0, le.Object0);
                break;
        }
    };
    BattleController.prototype.onSkillPictre = function (id, callBack) {
        if (id < 0)
            return;
        var mconfig = MagicConfig.GetConfig(id);
        if (mconfig != null) {
            App.ViewManager.open(ViewConst.BattlePicture);
            this.battlePictureView.playPicturnAnimation(mconfig.animationDraw, callBack);
        }
    };
    BattleController.prototype.onHPPictre = function (uid, callBack) {
        if (uid < 0) {
            if (callBack)
                callBack();
            return;
        }
        var cconfig = CreatureTempletConfig.GetConfig(uid);
        if (cconfig != null) {
            App.ViewManager.open(ViewConst.BattlePicture);
            this.battlePictureView.playPicturnAnimation(cconfig.hurtDraw, callBack);
        }
        else {
            if (callBack)
                callBack();
        }
    };
    return BattleController;
}(BaseController));
__reflect(BattleController.prototype, "BattleController");
//# sourceMappingURL=BattleController.js.map