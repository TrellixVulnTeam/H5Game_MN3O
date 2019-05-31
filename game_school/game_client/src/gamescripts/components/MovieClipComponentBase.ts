
class MovieClipComponentBase {
    private body: egret.DisplayObjectContainer;
    private mc: MovieClip;
    private mMovieClipEvent: { [key: string]: { [key: string]: Array<Function>; }; } = {};
    private mEventListenerList: { [key: string]: Function; } = {};
    private gameResGroupName: string;
    private mcPath: string;
    private mcName: string;
    private mEntity: MilitaryOfficerObject;
    private isRuning: boolean = false;
    private mcData:any;
    private scaleOffset:number;

    public constructor() {

    }

    public Init(gameResGroupName: string, mcpath: string, mcname: string, entity: MilitaryOfficerObject,scale:number=1) {
        this.gameResGroupName = gameResGroupName;
        this.mcPath = mcpath;
        this.mcName = mcname;
        this.mEntity = entity;
        this.scaleOffset=scale;
    }


    public get MovieClip() {
        return this.mc;
    }
    public get Body() {
        return this.body;
    }
    public get Entity() {
        return this.mEntity;
    }
    
    public RemoveChild(){
        if(this.mEntity)
        this.mEntity.gameView.removeChild(this.body);
    }

    public start(_body: egret.DisplayObjectContainer = null) {
        this.isRuning = true;
        this.mc =ObjectPool.pop("MovieClip"); 
        //this.mc.setDefault("avatarDefault_png");
        this.mc.setComplateAction(this.complateAction, this);

        if (_body == null) {
            this.body = ObjectPool.pop("egret.DisplayObjectContainer");
            this.body.$touchEnabled = true;
            this.body.addChild(this.mc);
        }
        else {
            this.body = _body;
        }

        this.body.scaleX=this.scaleOffset;
        this.body.scaleY=this.scaleOffset;

        if (this.mEntity != null) {
            this.mEntity.gameView.addChild(this.body);
        }

        if(this.mcName.search("_avatar")!=-1){
            RES.getResAsync(this.mcName + "_json",this.MCJsonLoadSuccess,this);
        }
        else
        {
            let res = RES.getRes(this.mcName + "_json");
            if (res == null) {
                GameRes.loadRes(this.gameResGroupName, this.mcPath, this.mcName, this.OnLoadComplateBySync, this);
            }
            else {
                this.OnLoadComplateBySync();
            }
        }
    }
    private MCJsonLoadSuccess(data:any,key:string){
        this.mcData=data;
        RES.getResAsync(this.mcName + "_png",this.OnLoadComplateByAsync,this);
    }

    /**
     * 修改父组件，切换层级
     */
    public ChangeParent(view: egret.DisplayObjectContainer) {
        view.addChild(this.body);
    }

    public update(advancedTime: number) {

    }

    //默认是否移除body,默认会移除
    public stop(isRemoveBody: boolean = true) {
        this.isRuning = false;
        this.mcPath = null;
        this.mcName = null;
        this.mEntity = null;
       // ObjectPool.push(this.mc);
       if(this.mc){
        this.mc.destroy();
        this.mc = null;
       }
        
        if (isRemoveBody) {
            App.DisplayUtils.removeFromParent(this.body);
            ObjectPool.push(this.body);
            this.body.removeChildren();
            this.body = null;
        }
    }

    /**
     * 资源加载完毕了
     * @param _json与_png 对应resource_objects&resource_effect等文件内的后缀
     */
    private OnLoadComplateByAsync(data:any,key:string): void {
        if (!this.isRuning) {
            return;
        }
        var texture = data;
        var mcFactory: egret.MovieClipDataFactory = new egret.MovieClipDataFactory(this.mcData, texture);
        this.mc.setMcData(mcFactory.generateMovieClipData(this.mcName), this.mcName);
        this.mc.addEventListener("MovieClipEnd", this.MovieClipEnd, this);
    }
    private OnLoadComplateBySync(): void {
        if (!this.isRuning) {
            return;
        }
        var avatarResName: string = this.mcName;
        var data = RES.getRes(avatarResName + "_json");
        var texture = RES.getRes(avatarResName + "_png");
        var mcFactory: egret.MovieClipDataFactory = new egret.MovieClipDataFactory(data, texture);
        this.mc.setMcData(mcFactory.generateMovieClipData(avatarResName), avatarResName);
        this.mc.addEventListener("MovieClipEnd", this.MovieClipEnd, this);
    }

    public complateAction(): void {
    }

    private MovieClipEnd(event: egret.Event) {
        if (this.mEntity != null) {
            for (let eventType in this.mMovieClipEvent) {
                if (eventType == event.type) {
                    for (let key in this.mMovieClipEvent[eventType]) {
                        if (key + "_" + this.mc.getDir(this.mEntity.dir)[0] == event.data ) {
                           let funs:Array<Function>= this.mMovieClipEvent[eventType][key];
                           if(funs){
                            for (let index = 0; index <funs.length; index++) {
                               // console.log("MovieClipEnd"+this.mEntity.basicattr.Name+"     "+event.data);
                                this.mMovieClipEvent[eventType][key][index]();
                              }
                           }
                        }
                    }
                }
            }
        }
    }

    public AddMovieClipEvent(event: string, key: string, callback: Function) {
        if (this.mMovieClipEvent[event]) {
            if (this.mMovieClipEvent[event][key]) {
                this.mMovieClipEvent[event][key].push(callback);
            } else {
                let dic: { [key: string]: Array<Function>; } = {};
                let callList: Array<Function> = [];
                callList.push(callback);
                dic[key] = callList;
                this.mMovieClipEvent[event] = dic;
                dic = {};
                callList = [];
            }
        }
        else {
            let dic: { [key: string]: Array<Function>; } = {};
            let callList: Array<Function> = [];
            callList.push(callback);
            dic[key] = callList;
            this.mMovieClipEvent[event] = dic;
            dic = {};
            callList = [];
        }
    }

    public RemoveMovieClipEvent(event?: string, key?: string, callback?: Function) {
        if (this.mMovieClipEvent[event]) {
            if (this.mMovieClipEvent[event][key]) {
                var index = this.mMovieClipEvent[event][key].indexOf(callback);
                if (index > -1) {
                    this.mMovieClipEvent[event][key].splice(index, 1);
                }
            }
        }
    }

    /**注册事件监听 */
    public RegisEventListener(eventType: string, event: Function) {
        if (this.mEventListenerList[eventType]) {
            this.RemoveEventListener(eventType, event);
        }
        this.body.addEventListener(eventType, event, this);
        this.mEventListenerList[eventType] = event;
    }


    /**注销事件监听 */
    public RemoveEventListener(eventType: string, event?: Function) {
        if (event) {
            this.body.removeEventListener(eventType, event, this);
            this.mEventListenerList[eventType] = null;
        } else {
            if (this.mEventListenerList[eventType]) {
                this.body.removeEventListener(eventType, this.mEventListenerList[eventType], this);
                this.mEventListenerList[eventType] = null;
            }
        }

    }

    /**注册所有事件 */
    public RemoveAllEventListener() {
        for (let key in this.mEventListenerList) {
            if (key != null && this.mEventListenerList[key] != null) {
                this.RemoveEventListener(key, this.mEventListenerList[key]);
            }
        }
        this.mEventListenerList = {};
     }
}