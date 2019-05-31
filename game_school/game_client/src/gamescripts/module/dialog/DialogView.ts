/**
 * 
 */
class DialogView extends BaseEuiView {
    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
    }

    public get Model(): DialogModel {
        return App.ControllerManager.getControllerModel(ControllerConst.Dialog) as DialogModel;
    }

    private effect: DialogAvatarEffectComponent = null;

    private soundChannel: egret.SoundChannel = null; //音效音轨
    private voiceChannel: egret.SoundChannel = null; //人物语音音轨

    private isDoText: boolean = false;
    private nextOptionDialogID = -1; //需要跳过的下一个带选项的对话ID
    //是否打开自动了
    private isAuto: boolean = false;
    //打开自动之后循环索引
    private timerID: number = 100001;

    //---------人物对话组件------------
    private Group_Dia_left: eui.Group;  //总的人物对话组件

    private Group_left: eui.Group;
    private Group_center: eui.Group;
    private Group_right: eui.Group;

    private player: eui.Group;
    private image_player: eui.Image;
    private image_face: eui.Image;
    private Group_face: eui.Group;  //用来放系列帧的父物体

    private Group_dialogue: eui.Group;//整个文本框的组
    private group_imagenext: eui.Group; //image_next的组
    private image_next: eui.Image;
    private dia_name: eui.Label;
    private label_dia: eui.Label;
    private btn_skip: eui.Button;
    public btn_auto: eui.Button;
    private image_background: eui.Image;
    public btn_next: eui.Button;

    //场景特效用的背景图
    private Group_bg: eui.Group;
    private image_v: eui.Image;
    private image_h: eui.Image;
    private sceneEffectIndex: number = 0; //当前在执行的场景效果索引,场景效果是个数组
    private sceneEffectCallback?: Function; //当前所有场景效果都走完要执行的回调函数
    //----------------------------------------

    //------黑屏文本组件----------------------
    private Group_black: eui.Group;  //总的黑屏对话组件
    private image_black: eui.Image;
    private Group_label: eui.Group;
    private btn_go: eui.Button;
    private labelItemArray: Array<eui.Label> = [];

    private isTween: boolean = false;
    private labelTweenIndex: number = 0;
    //---------------------------------------

    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    public initUI(): void {
        super.initUI();
        this.skinName = App.ViewManager.getSkin(ViewConst.Dialog);
        this.btn_next.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnNtxt, this);
        this.btn_auto.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnAuto, this);
        this.btn_skip.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnSkip, this);

        this.btn_go.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnGo, this);
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
        this.effect = new DialogAvatarEffectComponent(this.Group_face);
        App.TimerManager.doFrame(1, 0, this.update, this);
    }

    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    public close(...param: any[]): void {
        super.close(param);
        App.TimerManager.remove(this.update, this);
    }

    /**
    * 用来执行帧动画的心跳,注意在close里停止这个函数
    */
    public update(advancedTime: number): void {
        if (this.effect != null)
            this.effect.update(advancedTime);
    }

    //当前页面关闭事件
    public _closeCick(): void {
        if (this.soundChannel != null)
            this.soundChannel.stop();
        if (this.voiceChannel != null)
            this.voiceChannel.stop();

        this.effect.RemoveAllEffect();
        this.effect = null;

        this.closeAuto();
        this.clickTweenOne();
        this.Group_black.visible = false;
        this.Group_Dia_left.visible = true;
        this.isDoText = false;
        this.isTween = false;
        this.nextOptionDialogID = -1;
        this.Group_bg.visible = false;

        //TODO 处理对话结束之后的逻辑
        this.endTrigger();

        if (this.Model.GoOutCallBack)
            this.Model.GoOutCallBack();
    }

    private endTrigger(): void {
        let con = this.Model.GetDialogGroupDataByDialogGroupID(this.Model.curPlotGroupID);
        switch (con.triggerType) {
            case 0:
                return;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }
    }

    public start(): boolean {
        let dialogGroupData = this.Model.GetDialogGroupDataByDialogGroupID(this.Model.curPlotGroupID);
        if (dialogGroupData == null) {
            console.log("原因：对话组ID不存在，数据：DialogGroupID='" + this.Model.curPlotGroupID + "'！");
            return false;
        }
        this.Model.curDialogConf = this.Model.GetDialogConfigByID(dialogGroupData.startDialogID);

        egret.Tween.get(this.image_next, { loop: true })
            .to({ y: 10 }, 1000)
            .to({ y: 23 }, 1000);
        this.group_imagenext.visible = false;

        this.startDialog();
        return true;
    }

    /// <summary>
    /// 开始对话回路
    /// </summary>
    private startDialog(): void {
        if (this.Model.curDialogConf.sound != "" && this.Model.curDialogConf.soundDelay >= 0) {
            if (this.soundChannel != null)
                this.soundChannel.stop();
            App.TimerManager.doTimer(this.Model.curDialogConf.soundDelay, 1,
                function () {
                    this.soundChannel = App.SoundManager.playEffect(this.Model.curDialogConf.sound);   //播放音效
                }.bind(this),
                this);
        }
        //设置基础背景
        if (this.Model.curDialogConf.background != "") {
            this.image_background.source = this.Model.curDialogConf.background;
        }

        let music: string = this.Model.curDialogConf.music;
        if (music != "" && music != "stop") {
            App.SoundManager.playBg(music);   //播放背景音乐
        }
        else if (this.Model.curDialogConf.music == "stop") {
            App.SoundManager.stopBg();
        }

        let type = this.Model.curDialogConf.dialogType;
        switch (type) {
            case DIALOG_TYPE.Text:
                this.playTextDialog(false);
                break;
            case DIALOG_TYPE.TextWithOption:
                this.playTextDialog(true);
                break;
            case DIALOG_TYPE.CGImage:
                //_PlayCGAtlas();
                break;
            case DIALOG_TYPE.BlackLabel:
                this.playBalckLabel(this.Model.curDialogConf.optionID);
                break;
        }
    }
    //------------------场景特效处理----------------------------------
    //ID 会是一个有序数组,执行完一个效果,就继续执行下一个效果
    private sceneEffect(id: number[]): void {
        //this.sceneEffectIndex = 0; 在执行这个递归之前,要在外部先确保一下索引是0,总回调是一个全局函数
        this.btn_next.visible = false;
        if (id == null) {
            if (this.sceneEffectCallback != null) {
                this.sceneEffectCallback();
            }
            return;
        }
        let con = SceneEffectConfig.GetConfig(id[this.sceneEffectIndex]);
        if (con == null) {
            if (this.sceneEffectCallback != null) {
                this.sceneEffectCallback();
            }
            return;
        }
        this.startSceneEffect(con, function () {
            this.sceneEffectIndex++;
            if (this.sceneEffectIndex < id.length) {
                this.sceneEffect(id);
            }
            else {
                if (this.sceneEffectCallback != null) {
                    this.sceneEffectCallback();
                }
            }
        }.bind(this));
    }

    //这个回调是下一个场景效果的执行回调
    private startSceneEffect(con: SceneEffectConfig, callback?: Function) {
        // 1 屏幕抖动     次数     方向(1纵向,2横向,3混合方向) 抖动的大小 是否隐藏文本框(0隐藏,1不隐藏) 抖动回调执行时机(0是抖完出字,1是边抖边出字)
        // 2 npc淡入淡出  0淡出1淡入 时间 是否隐藏文本框(0隐藏,1不隐藏)
        // 3 切换场景 方向 上下左右
        switch (con.type) {
            case 1: //抖屏
                let isVisible: boolean = con.para4 == 1 ? true : false;
                this.Group_dialogue.visible = isVisible;
                if (con.para5 == 0) { //抖完开始出字
                    App.ShockUtils.shockFree(this, con.para1, con.para2, con.para3, callback);
                }
                else if (con.para5 == 1) { //边抖边出字
                    App.ShockUtils.shockFree(this, con.para1, con.para2, con.para3);
                    if (callback != null)
                        callback();
                }
                return;
            case 2: //处理NPC淡入淡出
                this.setNPCDoAlpha(con.para1, con.para2, con.para3, callback);
                return;
            case 3:  //切换场景
                this.setGroupBG(con.para1, con.para2, callback);
                return;
        }
        if (callback != null)
            callback();
    }

    //设置NPC立绘形象的淡入淡出
    private setNPCDoAlpha(value: number, time: number, isDialoVisible: number, callback?: Function) {
        // 0淡出效果基本只在退场效果出, 1 基本只在进场效果
        //先处理对话框是否是否显示
        let isVisible: boolean = isDialoVisible == 1 ? true : false;
        this.Group_dialogue.visible = isVisible;

        if (value == 1) //进场的时候,要先处理一下立绘
        {

        }

        TweenManager.doAlpha(this.player, value, time, callback);
    }

    private setGroupBG(dir: number, time: number, callback?: Function) {
        this.Group_bg.visible = true;

        //1 上 2 下 3 左 4 右
        switch (dir) {
            case 1:
                this.image_h.visible = true;
                this.image_v.visible = false;
                this.image_h.scaleY = -1;
                this.image_h.y = 0;
                egret.Tween.get(this.image_h)
                    .to({ y: 1334 }, time)//设置500毫秒内 scaleY 属性变为 0     
                    .call(function () {
                        if (callback) {
                            callback()
                        }
                    });
                return;
            case 2:
                this.image_h.visible = true;
                this.image_v.visible = false;
                this.image_h.scaleY = 1;
                this.image_h.y = 1344;
                egret.Tween.get(this.image_h)
                    .to({ y: 0 }, time)//设置500毫秒内 scaleY 属性变为 0     
                    .call(function () {
                        if (callback) {
                            callback()
                        }
                    });
                return;
            case 3:
                this.image_h.visible = false;
                this.image_v.visible = true;
                this.image_v.scaleX = 1;
                this.image_v.x = -750;
                egret.Tween.get(this.image_v)
                    .to({ x: 0 }, time)//设置500毫秒内 scaleY 属性变为 0     
                    .call(function () {
                        if (callback) {
                            callback()
                        }
                    });
                return;
            case 4:
                this.image_h.visible = false;
                this.image_v.visible = true;
                this.image_v.scaleX = -1;
                this.image_v.x = 1550;
                egret.Tween.get(this.image_v)
                    .to({ x: 750 }, time)//设置500毫秒内 scaleY 属性变为 0     
                    .call(function () {
                        if (callback) {
                            callback()
                        }
                    });
                return;
        }
    }
    //------------------------------------------------------------------

    /// <summary>
    /// 播放文字对话
    /// </summary
    private playTextDialog(option: boolean): void {
        this.Group_bg.visible = false;
        this.Group_dialogue.visible = true;
        this.Group_Dia_left.visible = true;
        this.Group_black.visible = false;

        this.btn_next.visible = true;

        let con = this.Model.curDialogConf;
        this.label_dia.text = "";
        //显示说话人  npcID 0代表玩家自己 -1代表旁白
        if (con.npcID == 0)//0 代表玩家自己 
        {
            this.dia_name.text = "测试玩家"; //TODO 回头找角色名字读取一哈
        }
        else // 
        {
            this.dia_name.text = con.npcName;
        }

        //半身像
        if (con.npcID == -1 || con.npcID == 0) //旁白和玩家自己不需要显示立绘
        {
            this.image_player.visible = false;
        }
        else //正常显示人物立绘
        {
            this.image_player.visible = true;
            this.image_player.alpha = 1;
            this.image_player.source = this.getPlayerImg(con.npcID);
        }

        //处理表情
        if (con.npcID == -1 || con.npcID == 0 || (con.faceIndex - 1) == -1) //旁白和玩家自己不需要表情 ,表情默认-1是没有的,不过表里填的是0,所以-1操作
        {
            this.image_face.visible = false;
        }
        else //正常显示
        {
            this.setFace(con.npcID, con.faceIndex);
        }

        //控制人物左右  1左,2 中间 3 右边 
        if (con.pos == 1) {
            this.player.x = this.Group_left.x;
            this.player.y = this.Group_left.y;
        }
        else if (con.pos == 2) {
            this.player.x = this.Group_center.x;
            this.player.y = this.Group_center.y;
        }
        else if (con.pos == 3) {
            this.player.x = this.Group_right.x;
            this.player.y = this.Group_right.y;
        }

        this.sceneEffectIndex = 0;
        this.sceneEffectCallback = null;
        this.sceneEffectCallback = //闭包封装了一个全局函数
            function () {
                this.Group_dialogue.visible = true;
                this.btn_next.visible = true;
                //播放人物语音
                if (this.voiceChannel != null)
                    this.voiceChannel.stop();

                if (con.voice != "") {
                    this.voiceChannel = App.SoundManager.playEffect(con.voice);
                }

                //对话内容处理
                if (con.content == "") {
                    this.label_dia.visible = false;
                }
                else {
                    //继续的图标 开始对话的时候先关掉
                    //this.image_next.visible = false;
                    this.group_imagenext.visible = false;

                    this.label_dia.visible = true;
                    //this.label_dia.text = "";

                    if (!option) // 没有对话 
                    {
                        this.isDoText = true;
                        TweenManager.doText(this.label_dia, con.content, 50,
                            () => {
                                this.group_imagenext.visible = true;
                                this.isDoText = false;
                                //console.log("文本显示结束");
                            });
                    }
                    else {
                        this.label_dia.text = con.content;
                    }
                }
            }.bind(this);
        //执行开场效果
        this.sceneEffect(this.Model.curDialogConf.startSceneEffect);

        //基准点
        let point: egret.Point = this.getPoint(con.npcID, con.faceSymbolPos);
        this.effect.RemoveAllEffect();
        let effectCon = EffectConfig.GetConfig(con.faceSymbol);
        //处理帧特效
        if (effectCon != null) {
            this.effect.PlayEffect(con.faceSymbol, point);
        }

        if (option)
            this.playDialogOption();
    }

    private playDialogOption(): void {
        this.btn_next.visible = false;  //暂时关闭这个按钮
        App.ViewManager.open(ViewConst.DialogOption);
    }

    //根据NPCID,获得人物在DrawConfig表里面的立绘形象
    private getPlayerImg(npcID: number): string {
        let str = "";
        let con: DrawConfig = DrawConfig.GetConfig(npcID);
        if (con == null) {
            return str;
        }

        let isCN: boolean = App.GlobalData.GamePlatform == "CN" ? true : false;
        if (isCN) {
            str = con.draw2;
        }
        else {
            str = con.draw;
        }
        return str;
    }

    private setFace(npcID: number, faceIndex: number): void {
        //表情索引需要-1
        let index = faceIndex - 1;

        let con: DrawConfig = DrawConfig.GetConfig(npcID);
        if (con == null) {
            return;
        }
        this.image_face.visible = true;
        this.image_face.source = con.face[index];

        this.image_face.x = con.facePosition[0];
        this.image_face.y = con.facePosition[1];
    }

    private getPoint(npcID: number, index: number): egret.Point {
        //表情索引需要-1
        let point: egret.Point = new egret.Point();
        let con: DrawConfig = DrawConfig.GetConfig(npcID);
        if (con == null) {
            return point;
        }

        switch (index) {
            case 1:
                point.x = con.emotionPosition1[0];
                point.y = con.emotionPosition1[1];
                break;
            case 2:
                point.x = con.emotionPosition2[0];
                point.y = con.emotionPosition2[1];
                break;
            case 3:
                point.x = con.emotionPosition3[0];
                point.y = con.emotionPosition3[1];
                break;
            default:
                return point;
        }
        return point;
    }

    public SetNextDialog(nextDialogID: number, isSceneEffect: boolean = true): void {
        //先执行下退场效果
        this.sceneEffectIndex = 0;
        this.sceneEffectCallback = null;
        this.sceneEffectCallback =
            function () {
                let nextDialogData = this.Model.GetDialogConfigByID(nextDialogID);
                if (nextDialogData == null) {
                    console.log("原因：对话ID不存在，数据：NextDialogID = '" + nextDialogID + "'！");
                    return;
                }
                this.Model.curDialogConf = nextDialogData;
                this.startDialog();
            }.bind(this);

        if (isSceneEffect)
            this.sceneEffect(this.Model.curDialogConf.endSceneEffect);
        else
            this.sceneEffectCallback();
    }
    /// <summary>
    /// 玩家点击
    /// </summary>
    private onBtnNtxt(): void {
        this.closeAuto();
        if (this.isDoText) //如果正常进行doText操作 
        {
            this.ClickOne();
        }
        else //没有doText操作,进行正常的下一条文本 
        {
            this.ClickTwo();
        }
    }

    /// <summary>
    /// 玩家第一次点击 直接完成所有文本
    /// </summary>
    private ClickOne(): void {
        TweenManager.closeDoText();
        this.label_dia.text = this.Model.curDialogConf.content;
        this.group_imagenext.visible = true;
        this.isDoText = false;
    }

    /// <summary>
    /// 玩家第二次点击
    /// </summary>
    private ClickTwo(): void {
        if (this.isDoText) //如果现在有doText进行中,就不执行下一步
            return;
        TweenManager.closeDoText();
        let con = this.Model.curDialogConf;
        if (con.nextDialogID == -1) {
            this._closeCick();
        }
        else {
            this.SetNextDialog(con.nextDialogID);
        }
    }

    private onBtnAuto(): void {
        if (!this.isAuto)
            this.openAuto();
        else
            this.closeAuto();
    }

    private openAuto(): void {
        this.isAuto = true;
        App.TimerManager.doTimer(1000, 0, this.startAuto, this, this.timerID);
        this.btn_next.visible = false;  //暂时关闭这个按钮       
    }

    private startAuto() {
        if (this.isDoText) //如果正常进行doText操作 
            return;
        let type = this.Model.curDialogConf.dialogType;
        if (type == 2) //自动到有选项的时候,就停止自动 
        {
            this.closeAuto();
            return;
        }
        this.ClickTwo();
    }

    private closeAuto(): void {
        App.TimerManager.remove(this.timerID, this);

        this.isAuto = false;
        this.btn_next.visible = true;
    }

    //玩家点跳过按钮 
    private onBtnSkip(): void {
        this.GetNextOptionDialogID(this.Model.curDialogConf);
        if (this.nextOptionDialogID != -1) {
            App.EventMgrHelper.PushEventEx(EventDef.DialogSkip,
                function () {
                    this.SetNextDialog(this.nextOptionDialogID, false);
                }.bind(this),
                null, 0, 0, "提示", "确定要跳过本次剧情吗?");
        }
        else {
            App.EventMgrHelper.PushEventEx(EventDef.DialogSkip,
                function () {
                    this._closeCick();
                }.bind(this),
                null, 0, 0, "提示", "确定要跳过本次剧情吗?");
        }
    }

    //获得下一个对话选项的ID
    private GetNextOptionDialogID(dialogConf: DialogConfig): void {
        if (dialogConf.dialogType == DIALOG_TYPE.TextWithOption) //有选项的对话       
        {
            this.nextOptionDialogID = dialogConf.dialogID;
            return;
        }
        else if (dialogConf.nextDialogID == -1) {
            this.nextOptionDialogID = -1;
            return;  //对话结束了
        }

        let nextDialogData = this.Model.GetDialogConfigByID(dialogConf.nextDialogID);
        if (nextDialogData != null)
            this.GetNextOptionDialogID(nextDialogData);
        else {
            this.nextOptionDialogID = -1;
            return;
        }
    }

    //--------------黑屏文本逻辑
    private playBalckLabel(startID: number): void {
        this.Group_black.visible = true;
        this.Group_Dia_left.visible = false;

        var array: Array<BlackScreenConfig> = this.Model.GetBlackScreenConfigArray(startID);
        this.createOrUpdateItem(array);

        for (var i: number = 0; i < this.labelItemArray.length; i++) {
            this.labelItemArray[i].visible = false;
        }

        //判断数据奇偶
        let IsOdd = (array.length % 2 == 1) ? true : false;
        let centerNum = Math.ceil(array.length / 2);  //上取整得到中间数
        let height = this.labelItemArray[0].size * 2;
        for (var i: number = 1; i < array.length + 1; i++) {
            //this.labelItemArray[i].visible = true;
            let index = i - 1;
            this.labelItemArray[index].text = array[index].content;
            this.labelItemArray[index].x = -10;
            if (!IsOdd) {
                if (i <= centerNum)
                    this.labelItemArray[index].y = (centerNum - i) * -(height);
                else
                    this.labelItemArray[index].y = (i - centerNum) * height;
            }
            else {
                if (i < centerNum)
                    this.labelItemArray[index].y = (centerNum - i) * -(height);
                else if (i > centerNum)
                    this.labelItemArray[index].y = (i - centerNum) * height;
                else
                    this.labelItemArray[index].y = 0;
            }
        }

        this.isTween = true;
        this.labelTweenIndex = 0;
        this.labelDoAlpha(this.labelItemArray[0], 2000, array.length);
    }

    private createOrUpdateItem(listCount: Array<BlackScreenConfig>): void {
        //创建UI chapterItem
        for (var i: number = this.labelItemArray.length; i < listCount.length; i++) {
            var labelItem: eui.Label = new eui.Label();
            labelItem.fontFamily = "Microsoft YaHei";
            labelItem.textAlign = egret.HorizontalAlign.CENTER; //设置文本的对齐方式
            labelItem.verticalAlign = egret.VerticalAlign.MIDDLE;
            labelItem.textColor = 0xffffff;
            labelItem.size = 50;
            labelItem.width = this.width;
            labelItem.height = this.height;
            this.Group_label.addChild(labelItem);
            this.labelItemArray.push(labelItem);
        }
    }

    private labelDoAlpha(label: eui.Label, time: number, maxNum: number) {
        label.visible = true;
        label.alpha = 0;
        //创建 Tween 对象

        TweenManager.doAlpha(label, 1, time,
            function () {
                this.labelTweenIndex++;
                if (this.labelTweenIndex < maxNum) {
                    this.labelDoAlpha(this.labelItemArray[this.labelTweenIndex], time, maxNum);
                }
                else {
                    this.isTween = false;
                }
            }.bind(this))
        return;
    }


    private onBtnGo(): void {
        if (this.isTween)
            this.clickTweenOne();
        else
            this.clickTweenTwo();
    }

    /// <summary>
    /// 玩家第一次点击 直接完成所有文本
    /// </summary>
    private clickTweenOne(): void {
        for (var i: number = 0; i < this.labelItemArray.length; i++) {
            egret.Tween.removeTweens(this.labelItemArray[i]);
            this.labelItemArray[i].alpha = 1;
            this.labelItemArray[i].visible = true;
        }
        this.isTween = false;
    }

    /// <summary>
    /// 玩家第二次点击
    /// </summary>
    private clickTweenTwo(): void {
        if (this.isTween) //如果现在有doText进行中,就不执行下一步
            return;
        let con = this.Model.curDialogConf;
        if (con.nextDialogID == -1) {
            this._closeCick();
        }
        else {
            this.SetNextDialog(con.nextDialogID);
        }
    }

    //----------------------------------------
}

/// <summary>
/// 对话类型
/// </summary>
enum DIALOG_TYPE {
    //纯文本
    Text = 1,
    //文本带选项
    TextWithOption = 2,
    //CG图
    CGImage = 3,
    //黑屏出文本
    BlackLabel = 4,
}

