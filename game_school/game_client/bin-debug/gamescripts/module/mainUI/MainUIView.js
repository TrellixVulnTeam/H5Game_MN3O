var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var __extends = this && this.__extends || function __extends(t, e) { 
 function r() { 
 this.constructor = t;
}
for (var i in e) e.hasOwnProperty(i) && (t[i] = e[i]);
r.prototype = e.prototype, t.prototype = new r();
};
/**
 *
 */
var MainUIView = (function (_super) {
    __extends(MainUIView, _super);
    function MainUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.curConfig = null;
        /**
         * 临时指引标记
        */
        _this.isFirstGuide = false;
        _this.isSecondGuide = false;
        _this.isThirdGuide = false;
        return _this;
    }
    Object.defineProperty(MainUIView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.MainUI);
        },
        enumerable: true,
        configurable: true
    });
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    MainUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
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
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    MainUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    MainUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        App.SoundManager.playBg("A1_mp3");
        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide(); //剧情
        }
        else if (this.isFirstGuide == false && this.isSecondGuide) {
            this.isSecondGuide = false;
            this.addSecondGuide(); //指引
        }
        else if (this.isFirstGuide == false && this.isSecondGuide == false && this.isThirdGuide) {
            this.isThirdGuide = false;
            this.addThirdGuide(); //指引
        }
    };
    /**
     * 临时指引1（播放剧情后，进入固定战斗场景）
    */
    MainUIView.prototype.addFirstGuide = function () {
        //临时播剧情
        App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 103, function () {
            App.ViewManager.close(ViewConst.Dialog);
            App.SceneManager.runScene(SceneConsts.CCG_FIGHT, 1001);
        }.bind(this), 0, 0, "", "");
        // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 103, function () {
        //     App.ViewManager.close(ViewConst.Dialog);
        //     App.SceneManager.runScene(SceneConsts.CCG_FIGHT, 1001);
        // }.bind(this));
    };
    /**
     * 临时指引2（打开 活动界面 签到页签）
    */
    MainUIView.prototype.addSecondGuide = function () {
        this.validateNow();
        var mask = new GuideMask(this.btn_active, function () {
            App.ViewManager.open(ViewConst.ActivityRewardUI);
        }, "", true, -(this.btn_active.width / 3), -(this.btn_active.height / 3));
        this.addChild(mask);
    };
    /**
     * 临时指引3（打开 关卡界面）
    */
    MainUIView.prototype.addThirdGuide = function () {
        this.validateNow();
        var mask = new GuideMask(this.btn_story, function () {
            App.ViewManager.open(ViewConst.Chapter);
        });
        this.addChild(mask);
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    MainUIView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
        App.SoundManager.stopBg();
    };
    MainUIView.prototype.onPlayer = function () {
        var index = this.getRandonNum(0, this.curConfig.face_icon.length - 1);
        this.image_face.source = this.curConfig.face_icon[index];
    };
    MainUIView.prototype.getRandonNum = function (min, max) {
        return Math.floor(Math.random() * (max - min + 1) + min);
    };
    MainUIView.prototype.onMainUI = function () {
        var _this = this;
        /// 故事逻辑
        this.btn_story.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.onClose();
            if (!App.FightManager.IsFightFinish) {
                var model = App.ControllerManager.getControllerModel(ControllerConst.Chapter);
                if (model.isFirstOpenChapter)
                    App.ViewManager.open(ViewConst.ChapterChoose);
                else
                    App.ViewManager.open(ViewConst.Chapter);
            }
            else {
                App.ViewManager.open(ViewConst.CCG_GameFight);
                if (App.FightManager.WaitSettlement) {
                    App.FightManager.FightClearing();
                }
            }
        }, this);
        /// 活动逻辑
        this.btn_active.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.open(ViewConst.ActivityRewardUI);
        }, this);
        /// 设置界面
        this.btn_setup.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.open(ViewConst.SettingUI);
        }, this);
        //通信
        this.btn_message.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.open(ViewConst.WechatUI);
        }, this);
        /// 挑战逻辑
        this.btn_challenge.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.close(ViewConst.MainUI);
            App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 1, function () {
                App.ViewManager.close(ViewConst.Dialog);
                App.ViewManager.open(ViewConst.MainUI);
            }.bind(_this), 0, 0, "", "");
            // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 1, () => {
            //     App.ViewManager.close(ViewConst.Dialog);
            //     App.ViewManager.open(ViewConst.MainUI);
            // });
        }, this);
        this.btn_huodong.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.open(ViewConst.MainActivity);
        }, this);
        this.btn_mail.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.open(ViewConst.MailMain);
        }, this);
        /// 商城逻辑
        this.btn_shop.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
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
    };
    /**创建骨骼模型**/
    MainUIView.prototype.createMotorcycleExp = function () {
        this.actionArray = ["stand", "standby"];
        var dbName = "相川小春_部活_制服";
        this.mDrag = ObjectPool.pop("DragonObjectTest");
        this.mDrag.init(dbName, "buhuo_zhifu", this.actionArray);
        this.mDrag.armature.x = 250;
        this.mDrag.armature.y = 1250;
        this.mDrag.armature.touchEnabled = true;
        this.mDrag.armature.$addListener(egret.TouchEvent.TOUCH_BEGIN, this.ArmatureClick, this);
        this.Dragon.addChild(this.mDrag);
    };
    MainUIView.prototype.ArmatureClick = function () {
        var act = App.RandomUtils.randomArray(this.actionArray);
        this.mDrag.armature.play(act, 0);
    };
    return MainUIView;
}(BaseEuiView));
__reflect(MainUIView.prototype, "MainUIView");
//# sourceMappingURL=MainUIView.js.map