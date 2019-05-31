enum TriggerType {
    Trigger_No,//不触发
    Trigger_Plot,//剧情
    Trigger_Fighting,//战斗
}

/**
 * 指引管理
*/
class GuideManager extends BaseManager {
    public isGuide: string = "newPlayerGuide00";//指引

    public constructor() {
        super();
        this.isSaveKeyData(this.isGuide, "true");
    }

	/**
	 * 初始key值
	*/
    private isSaveKeyData(str: string, key: string): void {
        if (egret.localStorage.getItem(str) == null) {
            egret.localStorage.setItem(str, key);
        }
    }

    public setIsGuide(bool: boolean): boolean {
        return egret.localStorage.setItem(this.isGuide, bool.toString());
    }

    public get getIsGuide() {
        return egret.localStorage.getItem(this.isGuide) == "true";
    }

    /**
     * 剧情指引
    */
    public guidePlotById(strId: number) {
        let config = GuideConfig.GetConfig(strId);
        if (config != null && config.triggerType == TriggerType.Trigger_Plot) {
            App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, config.para2, function () {
                App.ViewManager.close(ViewConst.Dialog);
            }.bind(this), 0, 0, "", "");
            // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, config.para2, function () {
            //     App.ViewManager.close(ViewConst.Dialog);
            // });
        }
    }
}


/**
 * 指引锁屏
*/
class GuideMask extends BaseEuiView {
    private image_mask: eui.Image;
    private dianji_effect: eui.Group;
    private movieClip: egret.MovieClip;
    private btn: any = null;
    public item: any = null;

    public constructor(child: any, callBack: Function, str?: string, isBtn: boolean = true, adjustX: number = 0, adjustY: number = 0) {
        super(null, null);
        this.skinName = "resource/skins/New_player_guide.exml";

        if (isBtn) {
            this.initChildBtn(child, str);
        }
        else {
            this.item = child;
            this.addChild(this.item);
        }

        this.initChildMc(adjustX, adjustY);
        this.addBtnEventListener(callBack);
    }

    private initChildBtn(btn: any, str?: string) {
        let newBtn = new eui.Button();
        newBtn.skinName = btn.skinName;
        newBtn.width = btn.width;
        newBtn.height = btn.height;
        newBtn.x = btn.localToGlobal().x;
        newBtn.y = btn.localToGlobal().y;
        newBtn.label = str;
        this.btn = newBtn;
        this.addChild(this.btn);
    }

    private initChildMc(adjustX: number, adjustY: number) {
        var data = RES.getRes("ui_effect_json");
        var txtr = RES.getRes("ui_effect_png");
        var mcFactory: egret.MovieClipDataFactory = new egret.MovieClipDataFactory(data, txtr);
        this.movieClip = new egret.MovieClip(mcFactory.generateMovieClipData("ui_effect"));
        this.movieClip.x = this.btn == null ? this.item.x : (this.btn.x < 0 ? 0 : this.btn.x);
        this.movieClip.x += adjustX;
        this.movieClip.y = this.btn == null ? this.item.y : this.btn.y;
        this.movieClip.y += adjustY;
        this.movieClip.gotoAndPlay("dianji_2", -1);
        this.addChild(this.movieClip);
    }

    private addBtnEventListener(callBack: Function) {
        if (this.btn != null) {
            this.btn.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
                if (callBack != null) {
                    callBack();
                }
                this.hide();
            }, this);
        }
        else {
            this.item.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
                if (callBack != null) {
                    callBack();
                }
                this.hide();
            }, this);
        }
    }

    private hide() {
        if (this.btn != null) {
            this.removeChild(this.btn);
        }

        if (this.item != null) {
            this.removeChild(this.item);
        }

        this.removeChild(this.movieClip);
        this.removeFromParent();
    }
}