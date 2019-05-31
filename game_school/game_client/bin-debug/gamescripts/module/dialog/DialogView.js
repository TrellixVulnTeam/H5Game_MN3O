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
var DialogView = (function (_super) {
    __extends(DialogView, _super);
    function DialogView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.effect = null;
        _this.soundChannel = null; //音效音轨
        _this.voiceChannel = null; //人物语音音轨
        _this.isDoText = false;
        _this.nextOptionDialogID = -1; //需要跳过的下一个带选项的对话ID
        //是否打开自动了
        _this.isAuto = false;
        //打开自动之后循环索引
        _this.timerID = 100001;
        _this.sceneEffectIndex = 0; //当前在执行的场景效果索引,场景效果是个数组
        _this.labelItemArray = [];
        _this.isTween = false;
        _this.labelTweenIndex = 0;
        return _this;
    }
    Object.defineProperty(DialogView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.Dialog);
        },
        enumerable: true,
        configurable: true
    });
    //---------------------------------------
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    DialogView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.Dialog);
        this.btn_next.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnNtxt, this);
        this.btn_auto.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnAuto, this);
        this.btn_skip.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnSkip, this);
        this.btn_go.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnGo, this);
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    DialogView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    DialogView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.effect = new DialogAvatarEffectComponent(this.Group_face);
        App.TimerManager.doFrame(1, 0, this.update, this);
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    DialogView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
        App.TimerManager.remove(this.update, this);
    };
    /**
    * 用来执行帧动画的心跳,注意在close里停止这个函数
    */
    DialogView.prototype.update = function (advancedTime) {
        if (this.effect != null)
            this.effect.update(advancedTime);
    };
    //当前页面关闭事件
    DialogView.prototype._closeCick = function () {
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
    };
    DialogView.prototype.endTrigger = function () {
        var con = this.Model.GetDialogGroupDataByDialogGroupID(this.Model.curPlotGroupID);
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
    };
    DialogView.prototype.start = function () {
        var dialogGroupData = this.Model.GetDialogGroupDataByDialogGroupID(this.Model.curPlotGroupID);
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
    };
    /// <summary>
    /// 开始对话回路
    /// </summary>
    DialogView.prototype.startDialog = function () {
        if (this.Model.curDialogConf.sound != "" && this.Model.curDialogConf.soundDelay >= 0) {
            if (this.soundChannel != null)
                this.soundChannel.stop();
            App.TimerManager.doTimer(this.Model.curDialogConf.soundDelay, 1, function () {
                this.soundChannel = App.SoundManager.playEffect(this.Model.curDialogConf.sound); //播放音效
            }.bind(this), this);
        }
        //设置基础背景
        if (this.Model.curDialogConf.background != "") {
            this.image_background.source = this.Model.curDialogConf.background;
        }
        var music = this.Model.curDialogConf.music;
        if (music != "" && music != "stop") {
            App.SoundManager.playBg(music); //播放背景音乐
        }
        else if (this.Model.curDialogConf.music == "stop") {
            App.SoundManager.stopBg();
        }
        var type = this.Model.curDialogConf.dialogType;
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
    };
    //------------------场景特效处理----------------------------------
    //ID 会是一个有序数组,执行完一个效果,就继续执行下一个效果
    DialogView.prototype.sceneEffect = function (id) {
        //this.sceneEffectIndex = 0; 在执行这个递归之前,要在外部先确保一下索引是0,总回调是一个全局函数
        this.btn_next.visible = false;
        if (id == null) {
            if (this.sceneEffectCallback != null) {
                this.sceneEffectCallback();
            }
            return;
        }
        var con = SceneEffectConfig.GetConfig(id[this.sceneEffectIndex]);
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
    };
    //这个回调是下一个场景效果的执行回调
    DialogView.prototype.startSceneEffect = function (con, callback) {
        // 1 屏幕抖动     次数     方向(1纵向,2横向,3混合方向) 抖动的大小 是否隐藏文本框(0隐藏,1不隐藏) 抖动回调执行时机(0是抖完出字,1是边抖边出字)
        // 2 npc淡入淡出  0淡出1淡入 时间 是否隐藏文本框(0隐藏,1不隐藏)
        // 3 切换场景 方向 上下左右
        switch (con.type) {
            case 1://抖屏
                var isVisible = con.para4 == 1 ? true : false;
                this.Group_dialogue.visible = isVisible;
                if (con.para5 == 0) {
                    App.ShockUtils.shockFree(this, con.para1, con.para2, con.para3, callback);
                }
                else if (con.para5 == 1) {
                    App.ShockUtils.shockFree(this, con.para1, con.para2, con.para3);
                    if (callback != null)
                        callback();
                }
                return;
            case 2://处理NPC淡入淡出
                this.setNPCDoAlpha(con.para1, con.para2, con.para3, callback);
                return;
            case 3://切换场景
                this.setGroupBG(con.para1, con.para2, callback);
                return;
        }
        if (callback != null)
            callback();
    };
    //设置NPC立绘形象的淡入淡出
    DialogView.prototype.setNPCDoAlpha = function (value, time, isDialoVisible, callback) {
        // 0淡出效果基本只在退场效果出, 1 基本只在进场效果
        //先处理对话框是否是否显示
        var isVisible = isDialoVisible == 1 ? true : false;
        this.Group_dialogue.visible = isVisible;
        if (value == 1) {
        }
        TweenManager.doAlpha(this.player, value, time, callback);
    };
    DialogView.prototype.setGroupBG = function (dir, time, callback) {
        this.Group_bg.visible = true;
        //1 上 2 下 3 左 4 右
        switch (dir) {
            case 1:
                this.image_h.visible = true;
                this.image_v.visible = false;
                this.image_h.scaleY = -1;
                this.image_h.y = 0;
                egret.Tween.get(this.image_h)
                    .to({ y: 1334 }, time) //设置500毫秒内 scaleY 属性变为 0     
                    .call(function () {
                    if (callback) {
                        callback();
                    }
                });
                return;
            case 2:
                this.image_h.visible = true;
                this.image_v.visible = false;
                this.image_h.scaleY = 1;
                this.image_h.y = 1344;
                egret.Tween.get(this.image_h)
                    .to({ y: 0 }, time) //设置500毫秒内 scaleY 属性变为 0     
                    .call(function () {
                    if (callback) {
                        callback();
                    }
                });
                return;
            case 3:
                this.image_h.visible = false;
                this.image_v.visible = true;
                this.image_v.scaleX = 1;
                this.image_v.x = -750;
                egret.Tween.get(this.image_v)
                    .to({ x: 0 }, time) //设置500毫秒内 scaleY 属性变为 0     
                    .call(function () {
                    if (callback) {
                        callback();
                    }
                });
                return;
            case 4:
                this.image_h.visible = false;
                this.image_v.visible = true;
                this.image_v.scaleX = -1;
                this.image_v.x = 1550;
                egret.Tween.get(this.image_v)
                    .to({ x: 750 }, time) //设置500毫秒内 scaleY 属性变为 0     
                    .call(function () {
                    if (callback) {
                        callback();
                    }
                });
                return;
        }
    };
    //------------------------------------------------------------------
    /// <summary>
    /// 播放文字对话
    /// </summary
    DialogView.prototype.playTextDialog = function (option) {
        this.Group_bg.visible = false;
        this.Group_dialogue.visible = true;
        this.Group_Dia_left.visible = true;
        this.Group_black.visible = false;
        this.btn_next.visible = true;
        var con = this.Model.curDialogConf;
        this.label_dia.text = "";
        //显示说话人  npcID 0代表玩家自己 -1代表旁白
        if (con.npcID == 0) {
            this.dia_name.text = "测试玩家"; //TODO 回头找角色名字读取一哈
        }
        else {
            this.dia_name.text = con.npcName;
        }
        //半身像
        if (con.npcID == -1 || con.npcID == 0) {
            this.image_player.visible = false;
        }
        else {
            this.image_player.visible = true;
            this.image_player.alpha = 1;
            this.image_player.source = this.getPlayerImg(con.npcID);
        }
        //处理表情
        if (con.npcID == -1 || con.npcID == 0 || (con.faceIndex - 1) == -1) {
            this.image_face.visible = false;
        }
        else {
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
        this.sceneEffectCallback =
            function () {
                var _this = this;
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
                    if (!option) {
                        this.isDoText = true;
                        TweenManager.doText(this.label_dia, con.content, 50, function () {
                            _this.group_imagenext.visible = true;
                            _this.isDoText = false;
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
        var point = this.getPoint(con.npcID, con.faceSymbolPos);
        this.effect.RemoveAllEffect();
        var effectCon = EffectConfig.GetConfig(con.faceSymbol);
        //处理帧特效
        if (effectCon != null) {
            this.effect.PlayEffect(con.faceSymbol, point);
        }
        if (option)
            this.playDialogOption();
    };
    DialogView.prototype.playDialogOption = function () {
        this.btn_next.visible = false; //暂时关闭这个按钮
        App.ViewManager.open(ViewConst.DialogOption);
    };
    //根据NPCID,获得人物在DrawConfig表里面的立绘形象
    DialogView.prototype.getPlayerImg = function (npcID) {
        var str = "";
        var con = DrawConfig.GetConfig(npcID);
        if (con == null) {
            return str;
        }
        var isCN = App.GlobalData.GamePlatform == "CN" ? true : false;
        if (isCN) {
            str = con.draw2;
        }
        else {
            str = con.draw;
        }
        return str;
    };
    DialogView.prototype.setFace = function (npcID, faceIndex) {
        //表情索引需要-1
        var index = faceIndex - 1;
        var con = DrawConfig.GetConfig(npcID);
        if (con == null) {
            return;
        }
        this.image_face.visible = true;
        this.image_face.source = con.face[index];
        this.image_face.x = con.facePosition[0];
        this.image_face.y = con.facePosition[1];
    };
    DialogView.prototype.getPoint = function (npcID, index) {
        //表情索引需要-1
        var point = new egret.Point();
        var con = DrawConfig.GetConfig(npcID);
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
    };
    DialogView.prototype.SetNextDialog = function (nextDialogID, isSceneEffect) {
        if (isSceneEffect === void 0) { isSceneEffect = true; }
        //先执行下退场效果
        this.sceneEffectIndex = 0;
        this.sceneEffectCallback = null;
        this.sceneEffectCallback =
            function () {
                var nextDialogData = this.Model.GetDialogConfigByID(nextDialogID);
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
    };
    /// <summary>
    /// 玩家点击
    /// </summary>
    DialogView.prototype.onBtnNtxt = function () {
        this.closeAuto();
        if (this.isDoText) {
            this.ClickOne();
        }
        else {
            this.ClickTwo();
        }
    };
    /// <summary>
    /// 玩家第一次点击 直接完成所有文本
    /// </summary>
    DialogView.prototype.ClickOne = function () {
        TweenManager.closeDoText();
        this.label_dia.text = this.Model.curDialogConf.content;
        this.group_imagenext.visible = true;
        this.isDoText = false;
    };
    /// <summary>
    /// 玩家第二次点击
    /// </summary>
    DialogView.prototype.ClickTwo = function () {
        if (this.isDoText)
            return;
        TweenManager.closeDoText();
        var con = this.Model.curDialogConf;
        if (con.nextDialogID == -1) {
            this._closeCick();
        }
        else {
            this.SetNextDialog(con.nextDialogID);
        }
    };
    DialogView.prototype.onBtnAuto = function () {
        if (!this.isAuto)
            this.openAuto();
        else
            this.closeAuto();
    };
    DialogView.prototype.openAuto = function () {
        this.isAuto = true;
        App.TimerManager.doTimer(1000, 0, this.startAuto, this, this.timerID);
        this.btn_next.visible = false; //暂时关闭这个按钮       
    };
    DialogView.prototype.startAuto = function () {
        if (this.isDoText)
            return;
        var type = this.Model.curDialogConf.dialogType;
        if (type == 2) {
            this.closeAuto();
            return;
        }
        this.ClickTwo();
    };
    DialogView.prototype.closeAuto = function () {
        App.TimerManager.remove(this.timerID, this);
        this.isAuto = false;
        this.btn_next.visible = true;
    };
    //玩家点跳过按钮 
    DialogView.prototype.onBtnSkip = function () {
        this.GetNextOptionDialogID(this.Model.curDialogConf);
        if (this.nextOptionDialogID != -1) {
            App.EventMgrHelper.PushEventEx(EventDef.DialogSkip, function () {
                this.SetNextDialog(this.nextOptionDialogID, false);
            }.bind(this), null, 0, 0, "提示", "确定要跳过本次剧情吗?");
        }
        else {
            App.EventMgrHelper.PushEventEx(EventDef.DialogSkip, function () {
                this._closeCick();
            }.bind(this), null, 0, 0, "提示", "确定要跳过本次剧情吗?");
        }
    };
    //获得下一个对话选项的ID
    DialogView.prototype.GetNextOptionDialogID = function (dialogConf) {
        if (dialogConf.dialogType == DIALOG_TYPE.TextWithOption) {
            this.nextOptionDialogID = dialogConf.dialogID;
            return;
        }
        else if (dialogConf.nextDialogID == -1) {
            this.nextOptionDialogID = -1;
            return; //对话结束了
        }
        var nextDialogData = this.Model.GetDialogConfigByID(dialogConf.nextDialogID);
        if (nextDialogData != null)
            this.GetNextOptionDialogID(nextDialogData);
        else {
            this.nextOptionDialogID = -1;
            return;
        }
    };
    //--------------黑屏文本逻辑
    DialogView.prototype.playBalckLabel = function (startID) {
        this.Group_black.visible = true;
        this.Group_Dia_left.visible = false;
        var array = this.Model.GetBlackScreenConfigArray(startID);
        this.createOrUpdateItem(array);
        for (var i = 0; i < this.labelItemArray.length; i++) {
            this.labelItemArray[i].visible = false;
        }
        //判断数据奇偶
        var IsOdd = (array.length % 2 == 1) ? true : false;
        var centerNum = Math.ceil(array.length / 2); //上取整得到中间数
        var height = this.labelItemArray[0].size * 2;
        for (var i = 1; i < array.length + 1; i++) {
            //this.labelItemArray[i].visible = true;
            var index = i - 1;
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
    };
    DialogView.prototype.createOrUpdateItem = function (listCount) {
        //创建UI chapterItem
        for (var i = this.labelItemArray.length; i < listCount.length; i++) {
            var labelItem = new eui.Label();
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
    };
    DialogView.prototype.labelDoAlpha = function (label, time, maxNum) {
        label.visible = true;
        label.alpha = 0;
        //创建 Tween 对象
        TweenManager.doAlpha(label, 1, time, function () {
            this.labelTweenIndex++;
            if (this.labelTweenIndex < maxNum) {
                this.labelDoAlpha(this.labelItemArray[this.labelTweenIndex], time, maxNum);
            }
            else {
                this.isTween = false;
            }
        }.bind(this));
        return;
    };
    DialogView.prototype.onBtnGo = function () {
        if (this.isTween)
            this.clickTweenOne();
        else
            this.clickTweenTwo();
    };
    /// <summary>
    /// 玩家第一次点击 直接完成所有文本
    /// </summary>
    DialogView.prototype.clickTweenOne = function () {
        for (var i = 0; i < this.labelItemArray.length; i++) {
            egret.Tween.removeTweens(this.labelItemArray[i]);
            this.labelItemArray[i].alpha = 1;
            this.labelItemArray[i].visible = true;
        }
        this.isTween = false;
    };
    /// <summary>
    /// 玩家第二次点击
    /// </summary>
    DialogView.prototype.clickTweenTwo = function () {
        if (this.isTween)
            return;
        var con = this.Model.curDialogConf;
        if (con.nextDialogID == -1) {
            this._closeCick();
        }
        else {
            this.SetNextDialog(con.nextDialogID);
        }
    };
    return DialogView;
}(BaseEuiView));
__reflect(DialogView.prototype, "DialogView");
/// <summary>
/// 对话类型
/// </summary>
var DIALOG_TYPE;
(function (DIALOG_TYPE) {
    //纯文本
    DIALOG_TYPE[DIALOG_TYPE["Text"] = 1] = "Text";
    //文本带选项
    DIALOG_TYPE[DIALOG_TYPE["TextWithOption"] = 2] = "TextWithOption";
    //CG图
    DIALOG_TYPE[DIALOG_TYPE["CGImage"] = 3] = "CGImage";
    //黑屏出文本
    DIALOG_TYPE[DIALOG_TYPE["BlackLabel"] = 4] = "BlackLabel";
})(DIALOG_TYPE || (DIALOG_TYPE = {}));
//# sourceMappingURL=DialogView.js.map