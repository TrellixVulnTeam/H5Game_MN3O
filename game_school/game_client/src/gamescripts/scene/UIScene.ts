/**
 * UI场景层
 */
class UIScene extends BaseScene{

    private mIsEnteredUIScene:boolean = false;//首次进入UIScene显示登陆界面
    /**
     * 构造函数
     */
    public constructor(){
        super();
    }

     public InitScene():void{
        super.InitScene();
         App.ResourceUtils.pilfererLoadGroup(App.PreLoad_GroupName, App.GetLoadResourceGroup(App.LoadReourcesSetp),this.OnLoadSuccess,null,this);
    }
    
    public OnLoadSuccess(){
        App.EnterNextLoad();
        App.ResourceUtils.pilfererLoadGroup(App.PreLoad_GroupName, App.GetLoadResourceGroup(App.LoadReourcesSetp));
    }

    /**
     * 进入Scene调用
     */
    public onEnter():void{
        super.onEnter();

        //添加该Scene使用的层级
        this.addLayer(LayerManager.UI_Main);
        this.addLayer(LayerManager.UI_Popup);
        this.addLayer(LayerManager.UI_Message);
        this.addLayer(LayerManager.UI_Tips);

        //添加一个纯色背景
        // var rect: eui.Rect = new eui.Rect();
        // rect.fillColor = 0x78b93f;
        // rect.percentHeight = 100;
        // rect.percentWidth = 100;
        // LayerManager.UI_Main.addChild(rect);

        //是否第一次进游戏,暂用本地持久化数据，等待以后有服务器接入，以服务器返回结果来判断
        // if(window.localStorage)
        // {
        //     let localStorage =window.localStorage; 
        //     if(!localStorage.getItem("IsFirstEnter")){
        //         localStorage.setItem("IsFirstEnter","false");
        //         App.VideoUtils.PlayVideo("video_default.png","start.mp4");
        //         if(this.mIsEnteredUIScene == false)
        //         {
        //             this.mIsEnteredUIScene = true;
        //             App.ViewManager.open(ViewConst.Login);
        //         }
        //         // if(App.DeviceUtils.IsPC){
        //         // }
        //         // else if(App.DeviceUtils.IsMobile){
        //         //     App.VideoUtils.PlayVideo("video_default.png","start.mp4");
        //         //     App.ViewManager.open(ViewConst.VideoPlayUI);
        //         //     App.ViewManager.open(ViewConst.Login);
        //         // }
        //     }
        //     else
        //     {
        //         if(this.mIsEnteredUIScene == false)
        //         {
        //             this.mIsEnteredUIScene = true;
        //             App.ViewManager.open(ViewConst.Login);
        //         }
        //     }
        // }
        if(this.mIsEnteredUIScene == false)
        {
            this.mIsEnteredUIScene = true;
            App.ViewManager.open(ViewConst.Login);
        }
    }

    /**
     * 退出Scene调用
     */
    public onExit():void{
        super.onExit();
    }
}
