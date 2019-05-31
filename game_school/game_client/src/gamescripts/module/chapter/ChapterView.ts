/**
 * 这是个备份文件
 */
class ChapterView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);    
    }

    public get Model(): ChapterModel {
        return App.ControllerManager.getControllerModel(ControllerConst.Chapter) as ChapterModel;
    }

    private Group_Radio: eui.Group;
    private radioBtnArray: Array<eui.RadioButton> = [];

    private curSelectCheckPointID: number;
    //战斗按钮,默认禁用状态
    private btn_battle: eui.Button;

    //章节标题
    private label_chaptername: eui.Label;
    //章节背景图
    private image_background: eui.Image;
    //返回
    private btn_back: eui.Button;
    //选择章节
    private btn_arrow: eui.Button;
    //队伍编辑
    private btn_team: eui.Button;


    private btn_clear: eui.Button;
    /**
	 * 临时指引标记
	*/
    private isFirstGuide = false;
    private isSecondGuide = false;
    private isThirdGuide = false;
    private isFourthGuide = false;
    private isFifthGuide = false;


    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.Chapter);//"resource/skins/Chapter.exml";

        this.isFirstGuide = App.GuideManager.getIsGuide;
        this.isSecondGuide = App.GuideManager.getIsGuide;
        this.isThirdGuide = App.GuideManager.getIsGuide;
        this.isFourthGuide = App.GuideManager.getIsGuide;
        this.isFifthGuide = App.GuideManager.getIsGuide;

        //遍历找到所有单选按钮
        for (var i: number = 0; i < this.Group_Radio.$children.length; i++) {
            let btn: eui.RadioButton = this.Group_Radio.getChildAt(i) as eui.RadioButton;
            btn.groupName = "selectChapterPoint";
            btn.group.addEventListener(eui.UIEvent.CHANGE, this.radioChangeHandler, this)
            this.radioBtnArray.push(btn);
        }

        this.btn_battle.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBattle, this);
        //下面是基本数据处理
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            this.onClose();
            //App.ViewManager.close(ViewConst.ChapterMseeag);
            App.ViewManager.close(ViewConst.ChapterChoose);

            App.ViewManager.open(ViewConst.MainUI);
        }, this);

        this.btn_arrow.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onArrow, this);

        this.btn_team.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            this.onFormationTeam();
        }, this);


        //--------------清楚数据
        this.btn_clear.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
            //egret.localStorage.clear();
            for (var i = 0; i < this.Model.checkPointDataArray.length; i++) {
                let id = this.Model.checkPointDataArray[i].checkPointID;
                egret.localStorage.removeItem(id.toString());
            }

        }, this);
        //------------------------------
    }

    /**
     * 编队
    */
    private onFormationTeam() {
        this.onClose();
        //App.ViewManager.close(ViewConst.ChapterMseeag);
        App.ViewManager.close(ViewConst.ChapterChoose);

        App.ViewManager.open(ViewConst.BattleArray);

        // App.ViewManager.open(ViewConst.Loading);
        // var groupName: string = "battle_preload_main";
        // var subGroups: Array<string> = ["preload_effect", "battle_preload_objects"];
        // App.ResourceUtils.loadGroups(groupName, subGroups, this.onResourceLoadComplete, this.onResourceLoadProgress, this);
    }

    /**
    * 资源组加载完成
    */
    private onResourceLoadComplete(): void {
        App.ViewManager.close(ViewConst.Loading);
        App.ViewManager.open(ViewConst.BattleArray);
    }

    /**
    * 资源组加载进度
    */
    private onResourceLoadProgress(itemsLoaded: number, itemsTotal: number): void 
    {
        App.EventMgrHelper.PushEvent(EventDef.LoadingRes_progress, itemsLoaded, itemsTotal);
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
        this.updataUI();

        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide();//指引
        }
        else if (this.isFirstGuide == false && this.isSecondGuide) {
            this.isSecondGuide = false;
            this.addSecondGuide();//指引
        }
    }

    /**
     * 临时指引1（第一次进入关卡界面，点击编队按钮，进入编队界面）
    */
    public addFirstGuide() {
        this.validateNow();
        let mask = new GuideMask(this.btn_team, () => {
            this.onFormationTeam();
        });
        this.addChild(mask);
    }

    /**
     * 临时指引2（第二次进入关卡界面，点击关卡1）
    */
    public addSecondGuide() {
        let btn = this.Group_Radio.getChildAt(0) as eui.RadioButton;
        if (btn != null) {
            this.validateNow();
            let mask = new GuideMask(btn, () => {
                if (this.isFirstGuide == false && this.isSecondGuide == false && this.isThirdGuide) {
                    this.isThirdGuide = false;
                    this.addThirdGuide();//指引
                }
            }, btn.label, true, (-btn.width / 4), (-btn.height / 4));
            this.addChild(mask);
        }
    }

    /**
     * 临时指引3 (点击关卡1后，点击调查按钮)
    */
    public addThirdGuide() {
        this.validateNow();
        let mask = new GuideMask(this.btn_battle, () => {
            this.onBattle();
        }, "", true, (this.btn_battle.width / 6), (-this.btn_battle.height / 2));
        this.addChild(mask);
    }

    /**
    * 临时指引4（第三次打开关卡界面，点击关卡2）
   */
    public addFourthGuide() {
        let btn = this.Group_Radio.getChildAt(1) as eui.RadioButton;
        if (btn != null) {
            this.validateNow();
            let mask = new GuideMask(btn, () => {
                if (this.isFirstGuide == false && this.isSecondGuide == false && this.isThirdGuide == false && this.isFourthGuide == false && this.isFifthGuide) {
                    this.isFifthGuide = false;
                    this.radioBtnArray[1].selected = true;
                    this.updataData(this.radioBtnArray[1].value);
                    this.addFifthGuide();//指引
                }
            }, btn.label, true, (-btn.width / 4), (-btn.height / 4));
            this.addChild(mask);
        }
    }

    /**
     * 临时指引5 (点击关卡2后，点击调查按钮)
    */
    public addFifthGuide() {
        this.validateNow();
        let mask = new GuideMask(this.btn_battle, () => {
            App.GuideManager.setIsGuide(false);
            this.onBattle();
        }, "", true, (this.btn_battle.width / 6), (-this.btn_battle.height / 2));
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

    //选择关卡页面
    private onArrow(): void {
        // 如果已经打开了,就不在重复打开了,或者出战UI是否已经打开了
        if (App.ViewManager.isShow(ViewConst.ChapterChoose))
            return;
        App.ViewManager.open(ViewConst.ChapterChoose);
    }


    //刷新页面UI
    public updataUI(): void {
        var array: Array<CheckPointConfig> = this.Model.GetCheckPointConfigListByChapterID(this.Model.curSelectChapter);

        for (let i: number = 0; i < this.radioBtnArray.length; i++) {
            this.radioBtnArray[i].visible = false;
            this.radioBtnArray[i].enabled = false;
            this.radioBtnArray[i].selected = false;
        }
        //设置一下默认的选项,这个只有显示效果
        this.radioBtnArray[0].selected = true;

        //按钮上刷新数据
        for (let i: number = 0; i < array.length; i++) {
            if (i < this.radioBtnArray.length) {
                this.setRadioBtnData(array[i], this.radioBtnArray[i]);
            }
        }

        //默认ID根据第一个选择按钮上绑定的数据ID为准
        this.updataData(this.radioBtnArray[0].value);

        //刷新章节数据
        var con: ChapterConfig = this.Model.GetChapterConfigByID(this.Model.curSelectChapter);
        this.label_chaptername.text = con.chapter_num + " " + con.chapter_name;
        this.image_background.source = con.chapter_bg;

        App.SoundManager.playBg(con.chapter_music);

        if (this.isFirstGuide == false && this.isSecondGuide == false && this.isThirdGuide == false && this.isFourthGuide) {
            this.isFourthGuide = false;
            this.addFourthGuide();//指引
        }
    }

    private setRadioBtnData(data: CheckPointConfig, btn: eui.RadioButton): void {
        if (data == null)
            return;
        btn.value = data;
        btn.label = data.checkpoint_name;
        btn.visible = true;

        let list = this.Model.checkPointDataArray;
        for (let i = 0; i < list.length; i++) {
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
    }

    //刷新页面详细数据
    public updataData(data: CheckPointConfig) {
        this.curSelectCheckPointID = data.id;
        this.checkBattleIsEnabled();
    }

    //判断出击按钮是够可以点击
    private checkBattleIsEnabled() {
        let list = this.Model.checkPointDataArray;
        for (let i = 0; i < list.length; i++) {
            if (this.curSelectCheckPointID == list[i].checkPointID) {
                this.btn_battle.enabled = list[i].isOpen;
            }
        }
    }

    public onBattle(): void {
        App.EventMgrHelper.PushEvent(EventDef.SelectCheckPoint, this.curSelectCheckPointID);
        //this.applyFunc(ChapterConst.SELECTCHECKPOINTEREVENT_C2C, this.curSelectCheckPointID);
    }

    //关卡事件
    // public selectChapterPoint(chapterPontID: number): void {
    //     this.applyFunc(ChapterConst.SELECTCHECKPOINTEREVENT_C2C, chapterPontID);
    // }

    //选择关卡产生的事件
    private radioChangeHandler(evt: eui.UIEvent): void {
        let data: CheckPointConfig = evt.target.selection.value as CheckPointConfig;
        this.updataData(data);
    }

}



