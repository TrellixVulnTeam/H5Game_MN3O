var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
/**
 * 游戏主入口
 */
var GameMain = (function () {
    function GameMain() {
        App.ResourceUtils.loadGroups(App.PreLoad_GroupName, App.GetLoadResourceGroup(App.LoadReourcesSetp), this.onResourceLoadComplete, this.onResourceLoadProgress, this);
    }
    /**
     * 资源组加载完成
     */
    GameMain.prototype.onResourceLoadComplete = function () {
        App.ControllerManager.RegisterAllController();
        App.PlayerManager.Name = "傻甜甜";
        App.Init();
        //音乐音效处理
        App.SoundManager.setBgOn(true);
        App.SoundManager.setEffectOn(true);
        //进入ui场景
        App.SceneManager.runScene(SceneConsts.UI);
        App.EnterNextLoad();
    };
    /**
     * 资源组加载进度
     */
    GameMain.prototype.onResourceLoadProgress = function (itemsLoaded, itemsTotal) {
        App.EventMgrHelper.PushEvent(EventDef.LoadingRes_progress, itemsLoaded, itemsTotal);
    };
    return GameMain;
}());
__reflect(GameMain.prototype, "GameMain");
//# sourceMappingURL=GameMain.js.map