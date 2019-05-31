/**
 * 
 */
class HintView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    public get Model(): HintModel {
        return App.ControllerManager.getControllerModel(ControllerConst.Dialog) as HintModel;
    }


    private label_tishi: eui.Label;
    private label_str: eui.Label;
    private btn_ensure: eui.Button;
    private btn_cancel: eui.Button;

    private ensureClick: Function = null;
    private cancelClick: Function = null;

    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.Hint);
        this.btn_ensure.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnEnsure, this);
        this.btn_cancel.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnCancel, this);
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


    public setData(tishi: string, text: string, ensureClick?: Function, cancelClick?: Function): void {
        this.label_tishi.text = tishi;
        this.label_str.text = text;
        // this.btn_ensure.label = ensureLabel;
        // this.btn_cancel.label = cancelLabel;
        this.ensureClick = ensureClick;
        this.cancelClick = cancelClick;
    }

    private onBtnEnsure(): void {
        this.onClose();
        if (this.ensureClick != null)
            this.ensureClick();
    }

    private onBtnCancel(): void {
        if (this.cancelClick != null)
            this.cancelClick();
        else {
            this.onClose();
        }
    }
}

