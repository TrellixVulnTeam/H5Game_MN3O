/**
 * Created by egret on 15-1-7.
 */
class LoadingView extends BaseEuiView{

    private pro : eui.ProgressBar;
    public txtMsg:eui.Label;
    
    public constructor($controller:BaseController, $parent:eui.Group) {
        super($controller, $parent);
    }

    public initUI(): void {
        super.initUI();
        this.skinName = "resource/skins/LoadingUISkin.exml";//登陆界面Config数据还没加载不使用App.ViewManager.getSkin
    }

    public setProgress(current:number, total:number):void {
        this.txtMsg.text = "资源加载中..." + ((current/total)*100).toFixed() + "%" ;
        this.pro.value = current / total * 100;
    }

    public configLoadingProgress(current:number, total:number):void {
        this.txtMsg.text = "configloading " + ((current/total)*100).toFixed() + "%" ;
        this.pro.value = current / total * 100;
    }
}