/**
 * 适配FIXED_WIDTH、FIXED_HEIGHT、NO_BORDER、SHOW_ALL四种缩放模式
 * 暂未考虑、屏幕旋转以及单页面多Webplay实例的情形
 */
class WebView extends egret.DisplayObjectContainer {

    private tempStage: egret.Stage;
    private _x:number=0;
    private _y:number=0;
    private _width:number=0;
    private _height:number=0;
    private _src:string="";

    private _scaleMode:string=egret.MainContext.instance.stage.scaleMode;
    private _stageW:number;
    private _stageH:number;
    private _windowW:number;
    private _windowH:number;
    private _displayH:number;
    private _displayW:number;
    private _designH:number;
    private _designW:number;
    private _canvas:any;

    private _iframeWrapper:HTMLDivElement=null;
    private _iframe:HTMLIFrameElement=null;
    public get iframe(): HTMLIFrameElement {
        return this._iframe;
    }

    /**
     * @param src
     */
    public constructor(src:string){
        super();
        
        let stageDelegateDom:HTMLElement=document.getElementById("StageDelegateDiv"),playerContainer:HTMLElement=stageDelegateDom.parentElement;
        let iframeWrapperDom=document.getElementById("iframe-wrapper");
        if(!iframeWrapperDom){
            iframeWrapperDom=document.createElement("div");
            iframeWrapperDom.style.display="none";
            iframeWrapperDom.attributes['style'].value+=' position:absolute;-webkit-overflow-scrolling: touch;overflow-y: scroll=no;';//解决iframe在ios下的显示问题//scroll;
            iframeWrapperDom.id="iframe-wrapper";
            stageDelegateDom.appendChild(iframeWrapperDom);
        }
        this._iframeWrapper=<HTMLDivElement>iframeWrapperDom;
        this._iframeWrapper.style.display="none";
        this._iframeWrapper.style.opacity="0";
        this._iframeWrapper.style.margin="0 px";
        this._iframeWrapper.style.width="100%";
        this._iframeWrapper.style.height="100%";


        let iframe = document.createElement("iframe"),t=new Date().getTime();
        iframe.src=src;
        iframe.id="webview-iframe-"+t;
        iframe.name="webview-iframe-"+t;
        iframe.style.position="absolute";
        iframe.style.top="0";
        iframe.style.left="0";
        iframe.style.opacity="0";
        iframe.style.display='none';
        iframe.style.width='100%';
        iframe.style.height='100%';
        iframe.frameBorder='0';
        iframe.border="0";
        this._iframeWrapper.appendChild(iframe);

        this._iframe=<HTMLIFrameElement>document.getElementById("webview-iframe-"+t);
        let self=this;
        this._iframe.onload=function(){
            self._iframeWrapper.style.opacity="1";
            self._iframe.style.opacity="1";
        }

        this._stageW=egret.MainContext.instance.stage.stageWidth;
        this._stageH=egret.MainContext.instance.stage.stageHeight;
        this._windowW=window.innerWidth;
        this._windowH=window.innerHeight;
        this._designH=parseInt(playerContainer.attributes['data-content-height'].value);
        this._designW=parseInt(playerContainer.attributes['data-content-width'].value);

        let stageSize = egret.sys.screenAdapter.calculateStageSize(egret.MainContext.instance.stage.scaleMode, this._windowW, this._windowH, this._designW, this._designH);
        this._displayH=stageSize.displayHeight;
        this._displayW=stageSize.displayWidth;

        
        App.StageUtils.getStage().addEventListener(egret.Event.RESIZE, this.onResize, this);
        Log.trace("windowW:"+this._windowW);
        Log.trace("stageW:"+this._stageW);
        Log.trace("disPlayW:"+this._displayW);
        Log.trace("windowH:"+this._windowH);
        Log.trace("stageH:"+this._stageH);
        Log.trace("displayH:"+this._displayH);

        for(let i=0; i<document.all.length;i++){
            if(document.all[i].nodeName=="CANVAS"){
                this._canvas = document.all[i];
            }
        }
    }

    public show():void {
        this._iframe.style.display='block';
        this._iframeWrapper.style.display='block';
    }

    public destroy():void {
        this.removeEventListener(egret.Event.RESIZE,this.onResize,this);
        if(this._iframe){
            this._iframeWrapper.style.display="none";
            this._iframeWrapper.removeChild(this._iframe);
        }
        if(document.getElementById("StageDelegateDiv") && this._iframeWrapper)
        {
            document.getElementById("StageDelegateDiv").removeChild(this._iframeWrapper);
        }
    }

    public get width():number {
        return this._width;
    }

    public set width(value:number) {
        this._width = value;
        if(App.DeviceUtils.IsMobile)
        {
            this._iframe.width=this._canvas.width;
            this._iframe.attributes["style"].value = this._canvas.style;
        }
        else
        {
            if(this._scaleMode==egret.StageScaleMode.FIXED_WIDTH || this._scaleMode==egret.StageScaleMode.FIXED_HEIGHT ){
                this._iframe.width=this._width/this._stageW*this._windowW+"px";
                this._iframeWrapper.style.width=this._width/this._stageW*this._windowW+"px";
            }
            if(this._scaleMode==egret.StageScaleMode.SHOW_ALL || this._scaleMode==egret.StageScaleMode.NO_BORDER ) {
                if(this._windowW==this._displayW){
                    this._iframe.style.width = this._width / this._stageW * this._windowW + "px";
                    this._iframeWrapper.style.width = this._width / this._stageW * this._windowW + "px";
                }else{
                    this._iframe.style.width = this._width / this._stageW * this._displayW + "px";
                    this._iframeWrapper.style.width = this._width / this._stageW * this._displayW + "px";
                }
            }
        }
    }

    public set height(value:number) {
        this._height = value;
        if(App.DeviceUtils.IsMobile){
            this._iframe.height=this._canvas.height;
            this._iframe.attributes["style"].value = this._canvas.style;
        }
        else
        {
            if(this._scaleMode==egret.StageScaleMode.FIXED_WIDTH || this._scaleMode==egret.StageScaleMode.FIXED_HEIGHT ) {
                this._iframe.height=this._height/this._height*this._windowH+"px";
                this._iframeWrapper.style.height=this._height/this._stageH*this._windowH+"px";
            }
            if(this._scaleMode==egret.StageScaleMode.SHOW_ALL || this._scaleMode==egret.StageScaleMode.NO_BORDER ) {
                if(this._windowH==this._displayH){
                    this._iframe.style.height = this._height / this._stageH * this._windowH + "px";
                    this._iframeWrapper.style.height = this._height / this._stageH * this._windowH + "px";
                }else{
                    this._iframe.style.height = this._height / this._stageH * this._displayH + "px";
                    this._iframeWrapper.style.height = this._height / this._stageH * this._displayH + "px";
                }
            }
        }
    }

    public set x(value:number) {
        this._x = value;
        if(this._scaleMode==egret.StageScaleMode.FIXED_WIDTH   || this._scaleMode==egret.StageScaleMode.FIXED_HEIGHT) {
            this._iframeWrapper.style.left = this._x / this._stageW * this._windowW + "px";
        }
        if(this._scaleMode==egret.StageScaleMode.SHOW_ALL || this._scaleMode==egret.StageScaleMode.NO_BORDER ) {
            if(this._windowW==this._displayW){
                this._iframeWrapper.style.left = this._x / this._stageW * this._windowW + "px";
            }else{
                this._iframeWrapper.style.left = this._x / this._stageW * this._displayW + "px";
            }
        }
    }

    public set y(value:number) {
        this._y = value;
        if(this._scaleMode==egret.StageScaleMode.FIXED_WIDTH  || this._scaleMode==egret.StageScaleMode.FIXED_HEIGHT ) {
            this._iframeWrapper.style.top = this._y / this._stageH * this._windowH + "px";
        }
        if(this._scaleMode==egret.StageScaleMode.SHOW_ALL || this._scaleMode==egret.StageScaleMode.NO_BORDER){
            if(this._windowH==this._displayH){
                this._iframeWrapper.style.top = this._y / this._stageH * this._windowH + "px";
            }else{
                this._iframeWrapper.style.top =this._y / this._stageH * this._displayH + "px";
            }
        }
    }

    public get x():number {
        return this._x;
    }

    public get y():number {
        return this._y;
    }

    public get src():string {
        return this._src;
    }

    public set src(value:string) {
        this._src = value;
    }

    private onResize(): void {
        let stageDelegateDom:HTMLElement=document.getElementById("StageDelegateDiv"),playerContainer:HTMLElement=stageDelegateDom.parentElement;
        this._stageW=egret.MainContext.instance.stage.stageWidth;
        this._stageH=egret.MainContext.instance.stage.stageHeight;
        this._windowW=window.innerWidth;
        this._windowH=window.innerHeight;
        this._designH=parseInt(playerContainer.attributes['data-content-height'].value);
        this._designW=parseInt(playerContainer.attributes['data-content-width'].value);

        let stageSize = egret.sys.screenAdapter.calculateStageSize(egret.MainContext.instance.stage.scaleMode, this._windowW, this._windowH, this._designW, this._designH);
        this._displayH=stageSize.displayHeight;
        this._displayW=stageSize.displayWidth;

        this.width=750;
        this.height=1334;
    }
}