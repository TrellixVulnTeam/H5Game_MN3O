/**
 * 
 */
class MainUIView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    private curConfig: FaceConfig = null;

    public get Model(): MainUIModel {
        return App.ControllerManager.getControllerModel(ControllerConst.MainUI) as MainUIModel;
    }

    private image_face: eui.Image;
    public Dragon: eui.Group;

    private btn_message: eui.Button;
    private btn_story: eui.Button;
    private btn_setup: eui.Button;
    private btn_player: eui.Button;
    private btn_active: eui.Button;

    private btn_challenge: eui.Button;
    private btn_mail: eui.Button;
    private btn_huodong: eui.Button;


    private btn_shop: eui.Button; //现在用来测试spine动画 
    /**
	 * 临时指引标记
	*/
    private isFirstGuide = false;
    private isSecondGuide = false;
    private isThirdGuide = false;

    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.MainUI);

        this.isFirstGuide = App.GuideManager.getIsGuide;
        this.isSecondGuide = App.GuideManager.getIsGuide;
        this.isThirdGuide = App.GuideManager.getIsGuide;

        this.onMainUI();

        if (this.curConfig == null)
            this.curConfig = this.Model.GetFaceConfigByID(11);

        this.btn_player.icon = this.curConfig.player_icon;
        this.image_face.x = this.curConfig.face_location[0];
        this.image_face.y = this.curConfig.face_location[1];
        this.image_face.width = this.curConfig.face_size[0];
        this.image_face.height = this.curConfig.face_size[1];

        //this.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onMainUI, this);
        this.btn_player.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onPlayer, this);

        // TODO 临时处理一下,强制关闭一下登录页面
        if (App.ViewManager.isShow(ViewConst.Login)) {
            App.ViewManager.close(ViewConst.Login);
        }
        if (App.ViewManager.isShow(ViewConst.CreatureRoleUI)) {
            App.ViewManager.close(ViewConst.CreatureRoleUI);
        }
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
        App.SoundManager.playBg("A1_mp3");

        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide();//剧情
        }
        else if (this.isFirstGuide == false && this.isSecondGuide) {
            this.isSecondGuide = false;
            this.addSecondGuide();//指引
        }
        else if (this.isFirstGuide == false && this.isSecondGuide == false && this.isThirdGuide) {
            this.isThirdGuide = false;
            this.addThirdGuide();//指引
        }
    }

    /**
     * 临时指引1（播放剧情后，进入固定战斗场景）
    */
    public addFirstGuide() {
        //临时播剧情
        App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 103, function () {
            App.ViewManager.close(ViewConst.Dialog);
            App.SceneManager.runScene(SceneConsts.CCG_FIGHT, 1001);
        }.bind(this), 0, 0, "", "");

        // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 103, function () {
        //     App.ViewManager.close(ViewConst.Dialog);
        //     App.SceneManager.runScene(SceneConsts.CCG_FIGHT, 1001);
        // }.bind(this));
    }

    /**
     * 临时指引2（打开 活动界面 签到页签）
    */
    public addSecondGuide() {
        this.validateNow();
        let mask = new GuideMask(this.btn_active, () => {
            App.ViewManager.open(ViewConst.ActivityRewardUI);
        }, "", true, -(this.btn_active.width / 3), -(this.btn_active.height / 3));
        this.addChild(mask);
    }

    /**
     * 临时指引3（打开 关卡界面）
    */
    public addThirdGuide() {
        this.validateNow();
        let mask = new GuideMask(this.btn_story, () => {
            App.ViewManager.open(ViewConst.Chapter);
        });
        this.addChild(mask);
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);
        App.SoundManager.stopBg();
    }

    private onPlayer(): void {
        var index = this.getRandonNum(0, this.curConfig.face_icon.length - 1);
        this.image_face.source = this.curConfig.face_icon[index];
    }

    private getRandonNum(min: number, max: number): number {
        return Math.floor(Math.random() * (max - min + 1) + min);
    }

    private onMainUI(): void {

        /// 故事逻辑
        this.btn_story.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            this.onClose();
            if (!App.FightManager.IsFightFinish) {
                let model: ChapterModel = App.ControllerManager.getControllerModel(ControllerConst.Chapter) as ChapterModel;
                if (model.isFirstOpenChapter)
                    App.ViewManager.open(ViewConst.ChapterChoose);
                else
                    App.ViewManager.open(ViewConst.Chapter);
            } else {
                App.ViewManager.open(ViewConst.CCG_GameFight);
                if (App.FightManager.WaitSettlement) {
                    App.FightManager.FightClearing();
                }
            }

        }, this);

        /// 活动逻辑
        this.btn_active.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            App.ViewManager.open(ViewConst.ActivityRewardUI);
        }, this);

        /// 设置界面
        this.btn_setup.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            App.ViewManager.open(ViewConst.SettingUI);
        }, this);

        //通信
        this.btn_message.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            App.ViewManager.open(ViewConst.WechatUI);
        }, this);

        /// 挑战逻辑
        this.btn_challenge.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            App.ViewManager.close(ViewConst.MainUI);
            App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 1, function () {
                App.ViewManager.close(ViewConst.Dialog);
                App.ViewManager.open(ViewConst.MainUI);
            }.bind(this), 0, 0, "", "");
            // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 1, () => {
            //     App.ViewManager.close(ViewConst.Dialog);
            //     App.ViewManager.open(ViewConst.MainUI);
            // });
        }, this);

        this.btn_huodong.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            App.ViewManager.open(ViewConst.MainActivity);
        }, this);

        this.btn_mail.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            App.ViewManager.open(ViewConst.MailMain);
        }, this);


        /// 商城逻辑
        this.btn_shop.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            // this.onClose();
            // App.ViewManager.open(ViewConst.TestSpine);
        }, this);

        /*
        /// 背包逻辑
        this.btn_bag.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            //this.dispatchEventWith(GameEvents.EVT_RETURN);          
            Log.trace("打开背包");
        }, this);

        /// 返回逻辑
        this.btn_mail.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            console.log("打开邮件");
        }, this);

        /// 好友逻辑
        this.btn_friend.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            console.log("打开好友");
            //App.ViewManager.open(ViewConst.Friend);
        }, this);

        /// 家园逻辑
        this.btn_home.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            console.log("家园好友");
        }, this);

       
       */

    }


    /**骨骼角色拥有的动作列表**/
    private actionArray;
    private mDrag: DragonObjectTest;
    /**创建骨骼模型**/
    private createMotorcycleExp(): void {
        this.actionArray = ["stand", "standby"]
        let dbName: string = "相川小春_部活_制服";

        this.mDrag = ObjectPool.pop("DragonObjectTest");
        this.mDrag.init( dbName, "buhuo_zhifu", this.actionArray);
        this.mDrag.armature.x = 250;
        this.mDrag.armature.y = 1250;
        this.mDrag.armature.touchEnabled = true;
        this.mDrag.armature.$addListener(egret.TouchEvent.TOUCH_BEGIN, this.ArmatureClick, this);
        this.Dragon.addChild(this.mDrag);
    }

    public ArmatureClick(): void {
        let act = App.RandomUtils.randomArray(this.actionArray);
        this.mDrag.armature.play(act, 0);
    }
}