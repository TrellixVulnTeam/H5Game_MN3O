/**
 * 视频播放UI,视图层
 * @constructor {sjz}
 * @data {2018-6-27}
 */
class VideoPlayUIView extends BaseEuiView {
    public btn_play:eui.Button;
    public PlayGroup:eui.Group;

    private mIsEnteredUIScene:boolean = false;//首次进入UIScene显示登陆界面

    public constructor(controller:BaseController, parent:eui.Group) {
        super(controller, parent);
    }

    public open(...param:any[]){
        super.open(param);
    }

    public close(...param:any[]){
        super.close(param);
    }

    public initUI(){
        super.initUI();
        this.skinName =App.ViewManager.getSkin(ViewConst.VideoPlayUI);
        this.btn_play.addEventListener(egret.TouchEvent.TOUCH_TAP,this.PlayVideo,this);
    }
    public PlayVideo(){
        this.PlayGroup.visible=false;
        App.VideoUtils.PlayVideo("video_default.png","start.mp4",function(){
            if(this.mIsEnteredUIScene == false)
            {
                this.mIsEnteredUIScene = true;
                App.ViewManager.close(ViewConst.VideoPlayUI);
                App.ViewManager.open(ViewConst.Login);
            }
        }.bind(this));
    }
}