/**
 */
class SimpleLoading extends BaseClass 
{
    private dobj:egret.DisplayObjectContainer = null;
    private label:egret.TextField;
    private img:egret.Bitmap;
    private probg:egret.Bitmap;
    private proimg:egret.Bitmap;
    private isShow:boolean = false;
    private totalNum;

    constructor() {
        super();
        this.init();
    }

    private init():void {
        this.totalNum = ConfFact.ConfigCount();
        this.dobj = new egret.DisplayObjectContainer();

        RES.getResByUrl("resource/assets/bg/loading1.png", function(texture:egret.Texture):void{
            this.img = new egret.Bitmap();
            this.img.texture = texture;
            this.dobj.addChild(this.img);

            RES.getResByUrl("resource/assets/bg/loading2.png", function(texture:egret.Texture):void{
                this.probg = new egret.Bitmap();
                this.probg.texture = texture;
                this.probg.x = (App.StageUtils.getWidth() - this.probg.width) / 2;
                this.probg.y = App.StageUtils.getHeight() / 2;
                this.dobj.addChild(this.probg);

                RES.getResByUrl("resource/assets/bg/loading3.png", function(texture:egret.Texture):void{
                    this.proimg = new egret.Bitmap();
                    this.proimg.texture = texture;
                    this.proimg.x = (App.StageUtils.getWidth() - this.proimg.width) / 2;
                    this.proimg.y = App.StageUtils.getHeight() / 2;
                    this.dobj.addChild(this.proimg);

                    this.label = new egret.TextField();
                    this.label.size = 30;
                    this.label.textColor = 0xcc7c76;
                    this.dobj.addChild( this.label );

                }, this, RES.ResourceItem.TYPE_IMAGE);

            }, this, RES.ResourceItem.TYPE_IMAGE);

        }, this, RES.ResourceItem.TYPE_IMAGE);
    }

    public showLoading():void {
        this.isShow = true;
        App.StageUtils.getStage().addChild(this.dobj);
    }

    public hideLoading():void {
        if (this.dobj && this.dobj.parent) {
            App.StageUtils.getStage().removeChild(this.dobj);
        }
        this.isShow = false;
    }

    public enterFrame() {
        if(this.isShow && this.label != null && this.proimg != null)
        {
            this.label.text = "config loading " + ConfFact.GetLoadedConfigName().length + " / " + this.totalNum;
            this.label.x = (App.StageUtils.getWidth() - this.label.width) / 2;
            this.label.y = App.StageUtils.getHeight() / 2 - this.proimg.height * 2;
            this.proimg.scrollRect = new egret.Rectangle(0, 0, this.proimg.width * (21 / this.totalNum), this.proimg.height);
        }
    }

    public initFinish(callback:Function):void{
        var intervalID = setInterval( function onTick(){
            if(this.label != null && this.proimg != null)
            {
               callback();
               clearInterval(intervalID);
            }
        }.bind(this), 1);
    }
}
