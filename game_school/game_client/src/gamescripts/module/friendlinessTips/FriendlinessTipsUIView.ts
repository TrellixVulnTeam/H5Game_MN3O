/**
 * 友好度提示界面
*/
class FriendlinessTipsUIView extends BaseEuiView 
{
    private fly:egret.tween.TweenGroup;
    private label_content:eui.Label;
    private content:string;

    public constructor($controller: BaseController, $parent: eui.Group) 
    {
        super($controller, $parent);

        this.addEventListener(eui.UIEvent.COMPLETE, ()=>{
            this.uiCompHandler($controller);
        }, this);
    }

    private uiCompHandler($controller: BaseController):void
    {
        this.fly.addEventListener(egret.Event.LEAVE_STAGE, this.onClose, this);
    }
    
    public initUI():void
    {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.FriendlinessTipsUI);
    }

    public initData():void
    {
        super.initData();
    }

    public open(...param: any[]): void {
        super.open(param);

        this.label_content.text = this.content;
        this.fly.play(0);
        var time = 125;//动画播放时间//
        var intervalID = setInterval( function onTick(){
            time--;
            if(time < 0)
            {
                this.onClose();
                clearInterval(intervalID);
            }
        }.bind(this), 10);
    }

    public setContent(content:string):void
    {
        this.content = content;
    }
}