/**
 * 战斗结算
 */
class BattleResultView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    private btn_ok: eui.Button;

    /**
	 * 临时指引标记（战斗结算界面）
	*/
    private isFirstGuide = false;


    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();

        this.skinName = App.ViewManager.getSkin(ViewConst.BattleResult);

        this.isFirstGuide = App.GuideManager.getIsGuide;
        this.btn_ok.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            if (this.isFirstGuide) {
                this.addFirstGuide();//退出界面播放剧情
            }
            else {
                App.SceneManager.runScene(SceneConsts.UI);
                App.ViewManager.open(ViewConst.MainUI);
                this.onClose();
            }
        }, this);
    }

    /**
     * 临时指引1（退出结算界面）
    */
    public addFirstGuide() {
        this.isFirstGuide = false;
        App.SceneManager.runScene(SceneConsts.UI);
        this.onClose();

        //临时播剧情
        App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 104, function () {
            App.ViewManager.close(ViewConst.Dialog);
            App.ViewManager.open(ViewConst.ChapterChoose);//打开章节界面
        }.bind(this), 0, 0, "", "");
        // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 104, function () {
        //     App.ViewManager.close(ViewConst.Dialog);
        //     App.ViewManager.open(ViewConst.ChapterChoose);//打开章节界面
        // });
    }

    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    public initData(): void {
        super.initData();
    }

    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    public open(...param: any[]): void {
        super.open(param);
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);
    }

}