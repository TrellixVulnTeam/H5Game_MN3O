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
 * created by sjz on 2018-5-10.
 * 战斗场景
 */
var CCG_GameFightScene = (function (_super) {
    __extends(CCG_GameFightScene, _super);
    function CCG_GameFightScene() {
        var _this = _super.call(this) || this;
        _this.mapId = 0;
        return _this;
    }
    CCG_GameFightScene.prototype.InitScene = function () {
        _super.prototype.InitScene.call(this);
    };
    CCG_GameFightScene.prototype.onEnter = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.onEnter.call(this);
        //参数
        this.mapId = param[0];
        //开启ComponentSystem
        ComponentSystem.start();
        //添加该Scene使用的Layer
        this.addLayerAt(LayerManager.Game_Main, 0);
        this.addLayer(LayerManager.UI_Main);
        this.addLayer(LayerManager.UI_Popup);
        this.addLayer(LayerManager.UI_Message);
        this.addLayer(LayerManager.UI_Tips);
        App.ViewManager.open(ViewConst.Loading);
        var groupName = "battle_preload_main";
        var subGroups = ["preload_effect", "battle_preload_objects"];
        App.ResourceUtils.loadGroups(groupName, subGroups, this.onResourceLoadComplete, this.onResourceLoadProgress, this);
    };
    /**
    * 资源组加载完成
    */
    CCG_GameFightScene.prototype.onResourceLoadComplete = function () {
        App.ViewManager.close(ViewConst.Loading);
        if (!App.FightManager.IsFightFinish) {
            //运行CCG战斗
            App.EventMgrHelper.PushEvent(EventDef.StartFightByArray, this.mapId);
        }
    };
    /**
    * 资源组加载进度
    */
    CCG_GameFightScene.prototype.onResourceLoadProgress = function (itemsLoaded, itemsTotal) {
        App.EventMgrHelper.PushEvent(EventDef.LoadingRes_progress, itemsLoaded, itemsTotal);
    };
    /**
     * 退出Scene调用
     */
    CCG_GameFightScene.prototype.onExit = function () {
        _super.prototype.onExit.call(this);
        //关闭ComponentSystem
        ComponentSystem.stop();
    };
    return CCG_GameFightScene;
}(BaseScene));
__reflect(CCG_GameFightScene.prototype, "CCG_GameFightScene");
//# sourceMappingURL=CCG_GameFightScene.js.map