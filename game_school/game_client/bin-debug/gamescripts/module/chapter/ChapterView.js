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
 * 这是个备份文件
 */
var ChapterView = (function (_super) {
    __extends(ChapterView, _super);
    function ChapterView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.radioBtnArray = [];
        /**
         * 临时指引标记
        */
        _this.isFirstGuide = false;
        _this.isSecondGuide = false;
        _this.isThirdGuide = false;
        _this.isFourthGuide = false;
        _this.isFifthGuide = false;
        return _this;
    }
    Object.defineProperty(ChapterView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.Chapter);
        },
        enumerable: true,
        configurable: true
    });
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    ChapterView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.Chapter); //"resource/skins/Chapter.exml";
        this.isFirstGuide = App.GuideManager.getIsGuide;
        this.isSecondGuide = App.GuideManager.getIsGuide;
        this.isThirdGuide = App.GuideManager.getIsGuide;
        this.isFourthGuide = App.GuideManager.getIsGuide;
        this.isFifthGuide = App.GuideManager.getIsGuide;
        //遍历找到所有单选按钮
        for (var i = 0; i < this.Group_Radio.$children.length; i++) {
            var btn = this.Group_Radio.getChildAt(i);
            btn.groupName = "selectChapterPoint";
            btn.group.addEventListener(eui.UIEvent.CHANGE, this.radioChangeHandler, this);
            this.radioBtnArray.push(btn);
        }
        this.btn_battle.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBattle, this);
        //下面是基本数据处理
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.onClose();
            //App.ViewManager.close(ViewConst.ChapterMseeag);
            App.ViewManager.close(ViewConst.ChapterChoose);
            App.ViewManager.open(ViewConst.MainUI);
        }, this);
        this.btn_arrow.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onArrow, this);
        this.btn_team.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.onFormationTeam();
        }, this);
        //--------------清楚数据
        this.btn_clear.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            //egret.localStorage.clear();
            for (var i = 0; i < _this.Model.checkPointDataArray.length; i++) {
                var id = _this.Model.checkPointDataArray[i].checkPointID;
                egret.localStorage.removeItem(id.toString());
            }
        }, this);
        //------------------------------
    };
    /**
     * 编队
    */
    ChapterView.prototype.onFormationTeam = function () {
        this.onClose();
        //App.ViewManager.close(ViewConst.ChapterMseeag);
        App.ViewManager.close(ViewConst.ChapterChoose);
        App.ViewManager.open(ViewConst.BattleArray);
        // App.ViewManager.open(ViewConst.Loading);
        // var groupName: string = "battle_preload_main";
        // var subGroups: Array<string> = ["preload_effect", "battle_preload_objects"];
        // App.ResourceUtils.loadGroups(groupName, subGroups, this.onResourceLoadComplete, this.onResourceLoadProgress, this);
    };
    /**
    * 资源组加载完成
    */
    ChapterView.prototype.onResourceLoadComplete = function () {
        App.ViewManager.close(ViewConst.Loading);
        App.ViewManager.open(ViewConst.BattleArray);
    };
    /**
    * 资源组加载进度
    */
    ChapterView.prototype.onResourceLoadProgress = function (itemsLoaded, itemsTotal) {
        App.EventMgrHelper.PushEvent(EventDef.LoadingRes_progress, itemsLoaded, itemsTotal);
    };
    /**
    *对面板数据的初始化，用于子类继承
    *
    */
    ChapterView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    ChapterView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.updataUI();
        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide(); //指引
        }
        else if (this.isFirstGuide == false && this.isSecondGuide) {
            this.isSecondGuide = false;
            this.addSecondGuide(); //指引
        }
    };
    /**
     * 临时指引1（第一次进入关卡界面，点击编队按钮，进入编队界面）
    */
    ChapterView.prototype.addFirstGuide = function () {
        var _this = this;
        this.validateNow();
        var mask = new GuideMask(this.btn_team, function () {
            _this.onFormationTeam();
        });
        this.addChild(mask);
    };
    /**
     * 临时指引2（第二次进入关卡界面，点击关卡1）
    */
    ChapterView.prototype.addSecondGuide = function () {
        var _this = this;
        var btn = this.Group_Radio.getChildAt(0);
        if (btn != null) {
            this.validateNow();
            var mask = new GuideMask(btn, function () {
                if (_this.isFirstGuide == false && _this.isSecondGuide == false && _this.isThirdGuide) {
                    _this.isThirdGuide = false;
                    _this.addThirdGuide(); //指引
                }
            }, btn.label, true, (-btn.width / 4), (-btn.height / 4));
            this.addChild(mask);
        }
    };
    /**
     * 临时指引3 (点击关卡1后，点击调查按钮)
    */
    ChapterView.prototype.addThirdGuide = function () {
        var _this = this;
        this.validateNow();
        var mask = new GuideMask(this.btn_battle, function () {
            _this.onBattle();
        }, "", true, (this.btn_battle.width / 6), (-this.btn_battle.height / 2));
        this.addChild(mask);
    };
    /**
    * 临时指引4（第三次打开关卡界面，点击关卡2）
   */
    ChapterView.prototype.addFourthGuide = function () {
        var _this = this;
        var btn = this.Group_Radio.getChildAt(1);
        if (btn != null) {
            this.validateNow();
            var mask = new GuideMask(btn, function () {
                if (_this.isFirstGuide == false && _this.isSecondGuide == false && _this.isThirdGuide == false && _this.isFourthGuide == false && _this.isFifthGuide) {
                    _this.isFifthGuide = false;
                    _this.radioBtnArray[1].selected = true;
                    _this.updataData(_this.radioBtnArray[1].value);
                    _this.addFifthGuide(); //指引
                }
            }, btn.label, true, (-btn.width / 4), (-btn.height / 4));
            this.addChild(mask);
        }
    };
    /**
     * 临时指引5 (点击关卡2后，点击调查按钮)
    */
    ChapterView.prototype.addFifthGuide = function () {
        var _this = this;
        this.validateNow();
        var mask = new GuideMask(this.btn_battle, function () {
            App.GuideManager.setIsGuide(false);
            _this.onBattle();
        }, "", true, (this.btn_battle.width / 6), (-this.btn_battle.height / 2));
        this.addChild(mask);
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    ChapterView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
        App.SoundManager.stopBg();
    };
    //选择关卡页面
    ChapterView.prototype.onArrow = function () {
        // 如果已经打开了,就不在重复打开了,或者出战UI是否已经打开了
        if (App.ViewManager.isShow(ViewConst.ChapterChoose))
            return;
        App.ViewManager.open(ViewConst.ChapterChoose);
    };
    //刷新页面UI
    ChapterView.prototype.updataUI = function () {
        var array = this.Model.GetCheckPointConfigListByChapterID(this.Model.curSelectChapter);
        for (var i = 0; i < this.radioBtnArray.length; i++) {
            this.radioBtnArray[i].visible = false;
            this.radioBtnArray[i].enabled = false;
            this.radioBtnArray[i].selected = false;
        }
        //设置一下默认的选项,这个只有显示效果
        this.radioBtnArray[0].selected = true;
        //按钮上刷新数据
        for (var i = 0; i < array.length; i++) {
            if (i < this.radioBtnArray.length) {
                this.setRadioBtnData(array[i], this.radioBtnArray[i]);
            }
        }
        //默认ID根据第一个选择按钮上绑定的数据ID为准
        this.updataData(this.radioBtnArray[0].value);
        //刷新章节数据
        var con = this.Model.GetChapterConfigByID(this.Model.curSelectChapter);
        this.label_chaptername.text = con.chapter_num + " " + con.chapter_name;
        this.image_background.source = con.chapter_bg;
        App.SoundManager.playBg(con.chapter_music);
        if (this.isFirstGuide == false && this.isSecondGuide == false && this.isThirdGuide == false && this.isFourthGuide) {
            this.isFourthGuide = false;
            this.addFourthGuide(); //指引
        }
    };
    ChapterView.prototype.setRadioBtnData = function (data, btn) {
        if (data == null)
            return;
        btn.value = data;
        btn.label = data.checkpoint_name;
        btn.visible = true;
        var list = this.Model.checkPointDataArray;
        for (var i = 0; i < list.length; i++) {
            if (data.id == list[i].checkPointID) {
                btn.enabled = list[i].isOpen;
                btn.visible = list[i].isOpen;
            }
        }
        // this.image_battle.visible = false;
        // if (App.FightManager.CheckPointID) {
        //     //当前战斗的是不是这一课
        //     if (data.id == App.FightManager.CheckPointID) {
        //         this.image_battle.visible = App.FightManager.IsFightFinish;
        //     }
        // }
    };
    //刷新页面详细数据
    ChapterView.prototype.updataData = function (data) {
        this.curSelectCheckPointID = data.id;
        this.checkBattleIsEnabled();
    };
    //判断出击按钮是够可以点击
    ChapterView.prototype.checkBattleIsEnabled = function () {
        var list = this.Model.checkPointDataArray;
        for (var i = 0; i < list.length; i++) {
            if (this.curSelectCheckPointID == list[i].checkPointID) {
                this.btn_battle.enabled = list[i].isOpen;
            }
        }
    };
    ChapterView.prototype.onBattle = function () {
        App.EventMgrHelper.PushEvent(EventDef.SelectCheckPoint, this.curSelectCheckPointID);
        //this.applyFunc(ChapterConst.SELECTCHECKPOINTEREVENT_C2C, this.curSelectCheckPointID);
    };
    //关卡事件
    // public selectChapterPoint(chapterPontID: number): void {
    //     this.applyFunc(ChapterConst.SELECTCHECKPOINTEREVENT_C2C, chapterPontID);
    // }
    //选择关卡产生的事件
    ChapterView.prototype.radioChangeHandler = function (evt) {
        var data = evt.target.selection.value;
        this.updataData(data);
    };
    return ChapterView;
}(BaseEuiView));
__reflect(ChapterView.prototype, "ChapterView");
//# sourceMappingURL=ChapterView.js.map