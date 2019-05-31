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
 * UI场景层
 */
var UIScene = (function (_super) {
    __extends(UIScene, _super);
    /**
     * 构造函数
     */
    function UIScene() {
        var _this = _super.call(this) || this;
        _this.mIsEnteredUIScene = false; //首次进入UIScene显示登陆界面
        return _this;
    }
    UIScene.prototype.InitScene = function () {
        _super.prototype.InitScene.call(this);
        App.ResourceUtils.pilfererLoadGroup(App.PreLoad_GroupName, App.GetLoadResourceGroup(App.LoadReourcesSetp), this.OnLoadSuccess, null, this);
    };
    UIScene.prototype.OnLoadSuccess = function () {
        App.EnterNextLoad();
        App.ResourceUtils.pilfererLoadGroup(App.PreLoad_GroupName, App.GetLoadResourceGroup(App.LoadReourcesSetp));
    };
    /**
     * 进入Scene调用
     */
    UIScene.prototype.onEnter = function () {
        _super.prototype.onEnter.call(this);
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
        if (this.mIsEnteredUIScene == false) {
            this.mIsEnteredUIScene = true;
            App.ViewManager.open(ViewConst.Login);
        }
    };
    /**
     * 退出Scene调用
     */
    UIScene.prototype.onExit = function () {
        _super.prototype.onExit.call(this);
    };
    return UIScene;
}(BaseScene));
__reflect(UIScene.prototype, "UIScene");
//# sourceMappingURL=UIScene.js.map