/**
 * 登陆界面
 */
class LoginView extends BaseEuiView 
{
    private loginbtn: eui.Button;
    private username: eui.EditableText;
    private password: eui.EditableText;

    private Group_Dragon: eui.Group;
    private actionArray:string[];
    private mDrag: DragonObjectTest;

    private play = false;
    private taiyang:egret.tween.TweenGroup;
    

    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
        this.addEventListener(eui.UIEvent.COMPLETE, this.uiCompHandler, this)
    }

    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.Login);
        this.createPlayerArmature();
    }

    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    public initData(): void {
        super.initData();        
        App.KeyboardUtils.addKeyDown(this.onKeyDown, this);
    }

    private onKeyDown(keyCode:number):void {
        switch (keyCode) {
            case Keyboard.SPACE:
                App.GuideManager.setIsGuide(true);
                break;
            case Keyboard.A:
                App.GuideManager.setIsGuide(false);
                break;
            default :
                break;
        }
    }

    private uiCompHandler(): void {
        this.username.addEventListener(egret.TouchEvent.CHANGE, this.onChangeUsername, this);
        this.username.addEventListener(egret.TouchEvent.FOCUS_IN, this.onSetUsername, this);
        this.username.addEventListener(egret.TouchEvent.FOCUS_OUT, this.offSetUsername, this);

        this.password.addEventListener(egret.TouchEvent.CHANGE, this.onChangePassword, this);
        this.password.addEventListener(egret.TouchEvent.FOCUS_IN, this.onSetPassword, this);
        this.password.addEventListener(egret.TouchEvent.FOCUS_OUT, this.offSetPassword, this);

        this.loginbtn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onLogin, this);
    }

    private onSetUsername(): void {
        this.username.text = "";
    }

    private offSetUsername(): void {
        if (this.username.text == "") {
            this.username.text = "用户名";
        }
    }

    private onChangeUsername(ev: egret.Event): void {
        this.username.text = ev.target.text;
    }

    private onSetPassword(): void {
        this.password.text = "";
    }

    private offSetPassword(): void {
        if (this.password.text == "") {
            this.password.displayAsPassword = false;
            this.password.text = "密码";
        }
    }

    private onChangePassword(ev: egret.Event): void {
        this.password.displayAsPassword = true;
        this.password.text = ev.target.text;
    }

    /**
     * 请求登陆处理
     * @param userName
     * @param pwd
     */
    private onLogin(): void {
        var userName: string = this.username.text;
        var pwd: string = this.password.text;

        if (userName == null || userName.length == 0) {
            return;
        }
        if (pwd == null || pwd.length == 0) {
            return;
        }

        this.onClose();
        App.ViewManager.open(ViewConst.CreatureRoleUI);
        //this.applyFunc(LoginConst.LOGIN_C2S, userName, pwd);
    }

    /**
     * 登陆成功处理
     */
    public loginSuccess(): void {
        //TODO 登陆成功处理
        this.onClose();
        App.ViewManager.open(ViewConst.CreatureRoleUI);
    }

    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    public open(...param: any[]): void {
        super.open(param);

        this.taiyang.play(0);
        var time = 200;//动画播放时间//
        var intervalID = setInterval( function onTick(){
            time--;
            if(time < 0)
            {
                time = 200;
                this.taiyang.play(0);
            }

            if(this.play)
            {
                clearInterval(intervalID);
            }
        }.bind(this), 10);
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);
        this.play = true;
    }

    /**
     * 人物
     */
    private createPlayerArmature(): void 
    {
        this.actionArray = ["stand", "standby"];
        let dbName: string = "相川小春_部活_制服";

        this.mDrag = ObjectPool.pop("DragonObjectTest");
        this.mDrag.init( dbName, "buhuo_zhifu", this.actionArray);

        this.mDrag.armature.x = (this.Group_Dragon.width + 100) / 2;
        this.mDrag.armature.y = this.Group_Dragon.height;
        this.mDrag.armature.touchEnabled = true;
        this.mDrag.armature.$addListener(egret.TouchEvent.TOUCH_BEGIN, this.changeArmature, this);
        this.Group_Dragon.scaleX = 1.28;
        this.Group_Dragon.scaleY = 1.28;
        this.Group_Dragon.addChild(this.mDrag);
    }

    /**
     * 点击动作
     */
    private changeArmature(): void 
    {
        let act = App.RandomUtils.randomArray(this.actionArray);
        this.mDrag.armature.play(act, 0);
    }
}