
/**
 * created by sjz on 2018-5-10.
 * 战斗场景
 */
class CCG_GameFightScene extends BaseScene
{
    private mapId:number=0;
    public constructor(){
        super();
    }

    public InitScene():void{
        super.InitScene();
    }
    
    public onEnter(...param:any[]):void{
        super.onEnter();


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
        var groupName: string = "battle_preload_main";
        var subGroups: Array<string> = ["preload_effect","battle_preload_objects"];
        App.ResourceUtils.loadGroups(groupName, subGroups, this.onResourceLoadComplete, this.onResourceLoadProgress, this);
    }


     /**
     * 资源组加载完成
     */
    private onResourceLoadComplete(): void {
        
        App.ViewManager.close(ViewConst.Loading);
        if(!App.FightManager.IsFightFinish){
        //运行CCG战斗
        App.EventMgrHelper.PushEvent(EventDef.StartFightByArray,this.mapId);
        }
 
    }

     /**
     * 资源组加载进度
     */
    private onResourceLoadProgress(itemsLoaded: number, itemsTotal: number): void 
    {
        App.EventMgrHelper.PushEvent(EventDef.LoadingRes_progress, itemsLoaded, itemsTotal);
    }

    /**
     * 退出Scene调用
     */
    public onExit():void{
        super.onExit();

        //关闭ComponentSystem
        ComponentSystem.stop();
    }
}