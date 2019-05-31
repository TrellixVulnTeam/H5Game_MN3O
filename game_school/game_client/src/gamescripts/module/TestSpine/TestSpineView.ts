/**
 * 
 */
class TestSpineView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    private group_btn: eui.Group;
    private btnArray: Array<eui.Button> = [];

    private btn_back: eui.Button;

    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = "resource/skins/text.exml";
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP,
            () => {
                this.onClose();
                App.ViewManager.open(ViewConst.MainUI);
            }
            , this);

        //遍历找到所有单选按钮
        for (var i: number = 0; i < this.group_btn.$children.length; i++) {
            let btn: eui.Button = this.group_btn.getChildAt(i) as eui.Button;
            btn.label = this.actionArray[i];
            //btn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnClick, this)
            this.btnArray.push(btn);
        }

        this.updataBtn();
        this.createMotorcycleExp();
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

    /**骨骼角色拥有的动作列表**/
    private actionArray = ["attack", "dead", "hit01", "hit02", "hit03", "hit04", "idle", "run", "skill", "win"];
    private mDrag: DragonObjectTest;
    private mDragSkeletonNames: Array<string> = [];
    /**创建骨骼模型**/
    private createMotorcycleExp(): void {
        let arr: Array<string> = ["role002"];
        for (var i: number = 0, len: number = arr.length; i < len; i++) {
            let dbName: string = arr[i];
            let str = dbName + "_ske_json";
            let skeletonData: any = RES.getRes(str);
            console.log(str);
            if (skeletonData == null)
                continue;

            for (let j = 0; j < skeletonData.armature.length; j++) {
                this.mDragSkeletonNames.push(skeletonData.armature[0].name);
            }
            let texturePng: egret.Texture = RES.getRes(dbName + "_tex_png");
            let textureData: any = RES.getRes(dbName + "_tex_json");
            App.DragonBonesFactory.initArmatureFile(skeletonData, texturePng, textureData);
        }
        this.mDrag = ObjectPool.pop("DragonObjectTest");
        this.mDrag.init( "buhuo_zhifu", "",this.actionArray);
        this.mDrag.armature.x = 250;
        this.mDrag.armature.y = 1250;
        this.mDrag.armature.touchEnabled = true;
        //this.mDrag.armature.$addListener(egret.TouchEvent.TOUCH_BEGIN, this.ArmatureClick, this);

        this.mDrag.armature.scaleX = 2;
        this.mDrag.armature.scaleY = 2;

        this.mDrag.createArmature(this.mDragSkeletonNames[0], this.actionArray);

        this.mDrag.armature.play(this.actionArray[0], 0);
        this.addChild(this.mDrag);
    }

    public ArmatureClick(): void {
        this.mDrag.armature.clear();
        let name = App.RandomUtils.randomArray(this.mDragSkeletonNames);
        let act = App.RandomUtils.randomArray(this.actionArray);
        this.mDrag.createArmature(name, this.actionArray);
        this.mDrag.armature.play(act, 0);
    }


    public onBtnClick(str: string): void {
        this.mDrag.armature.play(str, 0);
    }

    private updataBtn() {
        for (var i: number = 0; i < this.btnArray.length; i++) {
            let btn = new TestBtnItem();
            btn.init(this.btnArray[i], this);
        }
    }

}

class TestBtnItem {

    public constructor() {
    }

    private btn: eui.Button;
    private mHandView: TestSpineView;
    //传进来的表数据
    private con: string;

    public init(btn: eui.Button, view: TestSpineView): void {
        if (btn == null || view == null) {
            return;
        }
        this.btn = btn;
        this.mHandView = view;
        this.con = btn.label;
        this.btn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    }

    private onClick(): void {
        this.mHandView.onBtnClick(this.con);
    }
}

