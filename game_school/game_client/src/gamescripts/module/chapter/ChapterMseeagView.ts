/**
 * 战斗确认界面
 */
class ChapterMseeagView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    get Model(): ChapterModel {
        return App.ControllerManager.getControllerModel(ControllerConst.Chapter) as ChapterModel;
    }

    //关闭
    private btn_close: eui.Button;

    //出站
    private btn_battle: eui.Button;

    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        
        this.skinName = App.ViewManager.getSkin(ViewConst.ChapterMseeag);

        this.btn_close.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            TweenManager.scaleTween(this, this, 0, 249, () => {
                this.onClose();
            });

        }, this);

        this.btn_battle.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            App.SceneManager.runScene(SceneConsts.CCG_FIGHT, this.Model.curCheckPoint);
            this.onClose();
        }, this);
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

        TweenManager.scaleTween(this, this, 1, 249, () => {
        });
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);
    }



}

