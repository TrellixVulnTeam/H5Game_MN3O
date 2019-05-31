
/**
 * 游戏主入口
 */
class GameMain
{
    public constructor() {
        App.ResourceUtils.loadGroups(App.PreLoad_GroupName, App.GetLoadResourceGroup(App.LoadReourcesSetp), this.onResourceLoadComplete, this.onResourceLoadProgress, this);
    }

    /**
     * 资源组加载完成
     */
    private onResourceLoadComplete(): void {
        App.ControllerManager.RegisterAllController();
       
        App.PlayerManager.Name="傻甜甜";

        App.Init();
        //音乐音效处理
        App.SoundManager.setBgOn(true);
        App.SoundManager.setEffectOn(true);
        //进入ui场景
        App.SceneManager.runScene(SceneConsts.UI);
        App.EnterNextLoad();
        
    }

    /**
     * 资源组加载进度
     */
    private onResourceLoadProgress(itemsLoaded: number, itemsTotal: number): void 
    {
         App.EventMgrHelper.PushEvent(EventDef.LoadingRes_progress, itemsLoaded, itemsTotal);
    }
}