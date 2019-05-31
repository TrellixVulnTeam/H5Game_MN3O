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
 * 对话界面
 */
var DialogueCommentUIView = (function (_super) {
    __extends(DialogueCommentUIView, _super);
    function DialogueCommentUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.toggleArr = []; //选项卡
        _this.isOpenPlayer = true; //是否展开
        _this.isPlayerTalk = false; //是否到玩家发言
        _this.upPull = false; //上拉
        _this.dounPull = false; //下拉
        _this.laseIndex = 0;
        _this.openType = WechatUIType.Wechat_chat;
        return _this;
    }
    /**
     * 打开与某角色的对话
    */
    DialogueCommentUIView.prototype.OpenByOwner = function (ownId) {
        this.ReSetUI();
        this.currentInfoList = App.WechatManager.GetChatListByownId(ownId);
        var info;
        if (this.currentInfoList.IsExistNoTrigger()) {
            info = this.currentInfoList.GetCurrentChat();
        }
        else {
            info = this.currentInfoList.GetLastChatByStatu();
        }
        if (info) {
            this.currentInfo = info;
            if (info.mChatConfig.type == WeChatGroupType.Flock) {
                var config = ChatGroupNumConfig.GetConfig(info.mChatConfig.belong);
                this.talk_name.text = config.name;
            }
            else {
                var config = GirlConfig.GetConfig(info.mChatConfig.belong);
                this.talk_name.text = config.name;
            }
            this.CreateTalk(info.mChatConfig.startChatID, info, false);
        }
        else {
            //未发现聊天信息
        }
    };
    /**
     * 打开某条对话
     */
    DialogueCommentUIView.prototype.OpenByChatID = function (ownId, chatId) {
        this.ReSetUI();
        var info = App.WechatManager.GetChatById(ownId, chatId);
        if (info)
            this.CreateTalk(info.mChatConfig.startChatID, info, false);
    };
    DialogueCommentUIView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.Dialogue);
        this.tab_height = this.tab_backImage.height;
        this.oriHeight = this.Group_player.y; //默认选项卡的ui是展开的，记录下位置
        this.scr_talk.viewport = this.scr_playertalk;
        this.btn_open.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OpenBtnClickEvent, this);
        this.btn_sent.addEventListener(egret.TouchEvent.TOUCH_TAP, this.SendBtnClickEvent, this);
        this.radioGroup = new eui.RadioButtonGroup();
        this.radioGroup.addEventListener(eui.UIEvent.CHANGE, this.radioChangeHandler, this);
        this.btn_chatback.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.EventMgrHelper.PushEvent(EventDef.BackDialogListView, _this.openType);
        }, this);
        this.scr_talk.addEventListener(eui.UIEvent.CHANGE, this.MoveHandler, this);
        this.scr_talk.addEventListener(eui.UIEvent.CHANGE_END, this.MoveEndHandler, this);
    };
    /**
     * 拖动滚动条
     */
    DialogueCommentUIView.prototype.MoveHandler = function () {
        //上拉
        if (this.scr_talk.viewport.scrollV > (this.scr_talk.viewport.contentHeight - this.scr_talk.viewport.height) + 100) {
            this.upPull = true;
        }
        //下拉
        if (this.scr_talk.viewport.scrollV < -100) {
            this.dounPull = true;
        }
    };
    /**
     * 拖动结束
     */
    DialogueCommentUIView.prototype.MoveEndHandler = function () {
        if (this.upPull && this.currentInfo.CurrentStatus == WeChatGroupStatus.Triggered) {
            this.upPull = false;
            var info = this.currentInfoList.GetNextChat();
            if (info) {
                this.currentInfo = info;
                this.CreateTalk(info.mChatConfig.startChatID, info, false);
            }
        }
        if (this.dounPull && this.currentInfo.CurrentStatus == WeChatGroupStatus.Triggered) {
            this.dounPull = false;
            var info = this.currentInfoList.GetLastChat();
            if (info) {
                this.currentInfo = info;
                this.laseIndex = 0;
                this.CreateLastTalk(info.mChatConfig.startChatID, info, false);
            }
        }
    };
    /**
     * 生成上一个
     */
    DialogueCommentUIView.prototype.CreateLastTalk = function (id, info, isDelay) {
        if (id != -1) {
            var config = ChatConfig.GetConfig(id);
            if (config) {
                if (info.CurrentStatus == WeChatGroupStatus.ActivationNotTrigger) {
                }
                else {
                    if (config.type == DialogType.Player) {
                        var item = ObjectPool.pop("DialogueItemView");
                        var optionConfig = ChatOptionConfig.GetConfig(config.optionID);
                        item.CreatePlayDialog(optionConfig, info, info.mSelectMap[optionConfig.optionID]);
                        this.scr_playertalk.addChildAt(item, this.laseIndex);
                        this.laseIndex++;
                        item.visible = true;
                        info.lastchatId = config.chatId;
                        var id_1;
                        if (info.mSelectMap[optionConfig.optionID] == 1) {
                            id_1 = optionConfig.nextChat1;
                            info.LastSentence = optionConfig.optionContent1;
                        }
                        if (info.mSelectMap[optionConfig.optionID] == 2) {
                            id_1 = optionConfig.nextChat2;
                            info.LastSentence = optionConfig.optionContent2;
                        }
                        if (info.mSelectMap[optionConfig.optionID] == 3) {
                            id_1 = optionConfig.nextChat3;
                            info.LastSentence = optionConfig.optionContent3;
                        }
                        if (info.mSelectMap[optionConfig.optionID] == 4) {
                            id_1 = optionConfig.nextChat4;
                            info.LastSentence = optionConfig.optionContent4;
                        }
                        this.CreateLastTalk(id_1, info, false);
                    }
                    else {
                        var item = ObjectPool.pop("DialogueItemView");
                        item.UpdateInfo(config, info);
                        info.lastchatId = config.chatId;
                        info.LastSentence = config.content;
                        item.visible = true;
                        if (this.isOpenPlayer) {
                            this.scr_playertalk.removeChild(this.tab_filling);
                            this.tab_filling.visible = false;
                        }
                        this.scr_playertalk.addChildAt(item, this.laseIndex);
                        this.laseIndex++;
                        if (this.isOpenPlayer) {
                            this.scr_playertalk.addChild(this.tab_filling);
                            this.tab_filling.visible = true;
                        }
                        item.SetChatText();
                        if (config.nextId != 0)
                            this.CreateLastTalk(config.nextId, info, isDelay);
                    }
                }
            }
            else {
                console.log("dont find ChatConfig!");
            }
        }
        else {
            //聊天结束
            info.CurrentStatus = WeChatGroupStatus.Triggered;
            this.btn_sent.visible = false;
            var dividingLine = new eui.Image();
            dividingLine.source = "image_wuchatline_png";
            dividingLine.width = this.width * 0.6;
            dividingLine.explicitWidth = 100;
            this.laseIndex++;
            this.scr_playertalk.addChildAt(dividingLine, this.laseIndex);
        }
    };
    /**
     * 输入框点击
     */
    DialogueCommentUIView.prototype.OpenBtnClickEvent = function () {
        if (this.isPlayerTalk) {
            this.PlayerGroupOperating(!this.isOpenPlayer);
        }
    };
    /**
     * 发送按钮
     */
    DialogueCommentUIView.prototype.SendBtnClickEvent = function () {
        if (this.isPlayerTalk) {
            this.isPlayerTalk = false;
            var item = ObjectPool.pop("DialogueItemView");
            var config = ChatOptionConfig.GetConfig(this.currentOptionId);
            item.CreatePlayDialog(config, this.currentInfo, this.currentSelectIndex);
            this.currentInfo.mSelectMap[this.currentOptionId] = this.currentSelectIndex;
            this.scr_playertalk.addChild(item);
            item.visible = true;
            var id = void 0;
            if (this.currentSelectIndex == 1) {
                id = config.nextChat1;
                this.currentInfo.LastSentence = config.optionContent1;
            }
            if (this.currentSelectIndex == 2) {
                id = config.nextChat2;
                this.currentInfo.LastSentence = config.optionContent2;
            }
            if (this.currentSelectIndex == 3) {
                id = config.nextChat3;
                this.currentInfo.LastSentence = config.optionContent3;
            }
            if (this.currentSelectIndex == 4) {
                id = config.nextChat4;
                this.currentInfo.LastSentence = config.optionContent4;
            }
            this.SetScrend();
            this.currentInfo.AddToPast(this.currentChatId);
            this.CreateTalk(id, this.currentInfo, true);
            this.PlayerGroupOperating(false);
            this.btn_sent.visible = false;
            this.label_choose.visible = false;
            if (this.toggle1)
                this.toggle1.selected = false;
            if (this.toggle2)
                this.toggle2.selected = false;
            if (this.toggle3)
                this.toggle3.selected = false;
            if (this.toggle4)
                this.toggle4.selected = false;
        }
    };
    /**
     * 重置ui
     */
    DialogueCommentUIView.prototype.ReSetUI = function () {
        var _this = this;
        this.isPlayerTalk = false;
        this.btn_sent.visible = false;
        this.Group_player.y = this.oriHeight + this.tab_height;
        this.isOpenPlayer = false;
        this.label_choose.visible = false;
        var childs = [];
        for (var i = 0; i < this.scr_playertalk.numElements; i++) {
            var child = this.scr_playertalk.getChildAt(i);
            if (child) {
                ObjectPool.push(child);
                childs.push(child);
            }
        }
        childs.forEach(function (element) {
            _this.scr_playertalk.removeChild(element);
        });
        App.TimerManager.removeAll(this);
        this.scr_talk.validateNow();
        this.scr_talk.viewport.scrollV = 0;
    };
    /**
     * 打开或关闭选项卡
     */
    DialogueCommentUIView.prototype.PlayerGroupOperating = function (open, timer) {
        if (timer === void 0) { timer = 100; }
        if (open == this.isOpenPlayer) {
            return;
        }
        else {
            this.isOpenPlayer = open;
            var targetY = void 0;
            var scrollY_1;
            if (open) {
                targetY = this.oriHeight;
                this.scr_playertalk.addChild(this.tab_filling);
                this.tab_filling.visible = true;
            }
            else {
                targetY = this.oriHeight + this.tab_height;
                this.scr_playertalk.removeChild(this.tab_filling);
                this.tab_filling.visible = false;
            }
            egret.Tween.get(this.Group_player, { loop: false, onChangeObj: this })
                .to({ y: targetY }, timer);
            this.SetScrend();
        }
    };
    /**
     * 生成聊天
     */
    DialogueCommentUIView.prototype.CreateTalk = function (id, info, isDelay) {
        if (!this.isShow())
            return;
        if (id != -1) {
            var config = ChatConfig.GetConfig(id);
            if (config) {
                if (info.CurrentStatus == WeChatGroupStatus.ActivationNotTrigger && !info.FindPastChat(id)) {
                    if (config.type == DialogType.Player) {
                        //未触发己方发言
                        if (config.optionID != 0) {
                            this.currentOptionId = config.optionID;
                            this.currentChatId = id;
                            this.CreateTabItem(config.optionID);
                            this.isPlayerTalk = true;
                            this.PlayerGroupOperating(true);
                            this.SetScrend();
                        }
                        else {
                            console.log("ChatConfig optionID null!");
                        }
                    }
                    else {
                        //未触发对方发言
                        if (isDelay) {
                            this.DelayAction(config, info, true);
                        }
                        else {
                            this.DirectAction(config, info, true);
                        }
                    }
                }
                else {
                    if (config.type == DialogType.Player) {
                        var item = ObjectPool.pop("DialogueItemView");
                        var optionConfig = ChatOptionConfig.GetConfig(config.optionID);
                        item.CreatePlayDialog(optionConfig, info, info.mSelectMap[optionConfig.optionID]);
                        this.scr_playertalk.addChild(item);
                        item.visible = true;
                        info.lastchatId = config.chatId;
                        var id_2;
                        if (info.mSelectMap[optionConfig.optionID] == 1) {
                            id_2 = optionConfig.nextChat1;
                            info.LastSentence = optionConfig.optionContent1;
                        }
                        if (info.mSelectMap[optionConfig.optionID] == 2) {
                            id_2 = optionConfig.nextChat2;
                            info.LastSentence = optionConfig.optionContent2;
                        }
                        if (info.mSelectMap[optionConfig.optionID] == 3) {
                            id_2 = optionConfig.nextChat3;
                            info.LastSentence = optionConfig.optionContent3;
                        }
                        if (info.mSelectMap[optionConfig.optionID] == 4) {
                            id_2 = optionConfig.nextChat4;
                            info.LastSentence = optionConfig.optionContent4;
                        }
                        info.AddToPast(config.chatId);
                        this.SetScrend();
                        this.CreateTalk(id_2, info, false);
                    }
                    else {
                        this.DirectAction(config, info, false);
                    }
                }
            }
            else {
                console.log("dont find ChatConfig!");
            }
        }
        else {
            //聊天结束
            info.CurrentStatus = WeChatGroupStatus.Triggered;
            this.btn_sent.visible = false;
            var dividingLine = new eui.Image();
            dividingLine.source = "image_wuchatline_png";
            dividingLine.width = this.width * 0.6;
            dividingLine.explicitWidth = 100;
            this.scr_playertalk.addChild(dividingLine);
        }
    };
    /**
     * 直接执行
     */
    DialogueCommentUIView.prototype.DirectAction = function (config, info, isDelay) {
        var item = ObjectPool.pop("DialogueItemView");
        item.UpdateInfo(config, info);
        info.lastchatId = config.chatId;
        info.AddToPast(config.chatId);
        info.LastSentence = config.content;
        item.visible = true;
        if (this.isOpenPlayer) {
            this.scr_playertalk.removeChild(this.tab_filling);
            this.tab_filling.visible = false;
        }
        this.scr_playertalk.addChild(item);
        if (this.isOpenPlayer) {
            this.scr_playertalk.addChild(this.tab_filling);
            this.tab_filling.visible = true;
        }
        item.SetChatText();
        this.SetScrend();
        if (config.nextId != 0)
            this.CreateTalk(config.nextId, info, isDelay);
    };
    /**
     * 延时
     */
    DialogueCommentUIView.prototype.DelayAction = function (config, info, isDelay) {
        App.TimerManager.doTimer(500, 1, function () {
            var item = ObjectPool.pop("DialogueItemView");
            item.UpdateInfo(config, info);
            item.visible = true;
            var delay = parseFloat(ClientConstConfig.GetConfig(6).value) * 1000;
            var multiple = ((item.mconfig.content.length / 10) - 1) * (parseFloat(ClientConstConfig.GetConfig(7).value)) * 1000;
            delay += multiple;
            var count = delay / 500;
            if (this.isOpenPlayer) {
                this.scr_playertalk.removeChild(this.tab_filling);
                this.tab_filling.visible = false;
            }
            this.scr_playertalk.addChild(item);
            if (this.isOpenPlayer) {
                this.scr_playertalk.addChild(this.tab_filling);
                this.tab_filling.visible = true;
            }
            this.SetScrend();
            App.TimerManager.doTimer(delay / count, count, function () {
                item.SetWaitInput();
            }.bind(this), this, 0, function () {
                item.SetChatText();
                this.SetScrend();
                info.AddToPast(config.chatId);
                info.LastSentence = config.content;
                this.CreateTalk(config.nextId, info, isDelay);
            }.bind(this), this);
        }.bind(this), this);
    };
    /**
     * 滚动条置底
     */
    DialogueCommentUIView.prototype.SetScrend = function () {
        this.scr_talk.validateNow();
        if (this.scr_talk.viewport.contentHeight > this.scr_talk.viewport.height)
            this.scr_talk.viewport.scrollV = this.scr_talk.viewport.contentHeight - this.scr_talk.viewport.height;
    };
    /**
     * 生成选项卡
     */
    DialogueCommentUIView.prototype.CreateTabItem = function (option) {
        var optionConfig = ChatOptionConfig.GetConfig(option);
        if (optionConfig) {
            if (optionConfig.optionContent1) {
                if (!this.toggle1) {
                    this.toggle1 = new eui.RadioButton();
                    this.toggle1.skinName = "resource/eui_skins/DialogViewRadioButtonSkin.exml";
                }
                this.toggle1.visible = true;
                var str = optionConfig.optionContent1;
                if (str.length > 18) {
                    str = str.substring(0, 18) + "...";
                }
                this.toggle1.label = str;
                this.toggle1.value = 1;
                this.toggle1.group = this.radioGroup;
                this.tab_group.addChild(this.toggle1);
            }
            else {
                if (this.toggle1) {
                    var index = this.tab_group.getChildIndex(this.toggle1);
                    if (index != -1)
                        this.tab_group.removeChildAt(index);
                }
            }
            if (optionConfig.optionContent2) {
                if (!this.toggle2) {
                    this.toggle2 = new eui.RadioButton();
                    this.toggle2.skinName = "resource/eui_skins/DialogViewRadioButtonSkin.exml";
                }
                var str = optionConfig.optionContent2;
                if (str.length > 18) {
                    str = str.substring(0, 18) + "...";
                }
                this.toggle2.label = str;
                this.toggle2.value = 2;
                this.toggle2.group = this.radioGroup;
                this.tab_group.addChild(this.toggle2);
            }
            else {
                if (this.toggle2) {
                    var index = this.tab_group.getChildIndex(this.toggle2);
                    if (index != -1)
                        this.tab_group.removeChildAt(index);
                }
            }
            if (optionConfig.optionContent3) {
                if (!this.toggle3) {
                    this.toggle3 = new eui.RadioButton();
                    this.toggle3.skinName = "resource/eui_skins/DialogViewRadioButtonSkin.exml";
                }
                var str = optionConfig.optionContent3;
                if (str.length > 18) {
                    str = str.substring(0, 18) + "...";
                }
                this.toggle3.label = str;
                this.toggle3.value = 3;
                this.toggle3.group = this.radioGroup;
                this.tab_group.addChild(this.toggle3);
            }
            else {
                if (this.toggle3) {
                    var index = this.tab_group.getChildIndex(this.toggle3);
                    if (index != -1)
                        this.tab_group.removeChildAt(index);
                }
            }
            if (optionConfig.optionContent4) {
                if (!this.toggle4) {
                    this.toggle4 = new eui.RadioButton();
                    this.toggle4.skinName = "resource/eui_skins/DialogViewRadioButtonSkin.exml";
                }
                var str = optionConfig.optionContent4;
                if (str.length > 18) {
                    str = str.substring(0, 18) + "...";
                }
                this.toggle4.label = str;
                this.toggle4.value = 4;
                this.toggle4.group = this.radioGroup;
                this.tab_group.addChild(this.toggle4);
            }
            else {
                if (this.toggle4) {
                    var index = this.tab_group.getChildIndex(this.toggle4);
                    if (index != -1)
                        this.tab_group.removeChildAt(index);
                }
            }
        }
        else {
            console.log("dont find ChatOptionConfig || toggle1 null");
        }
    };
    /**
     * 选项切换
     */
    DialogueCommentUIView.prototype.radioChangeHandler = function (evt) {
        var btnGroup = evt.target;
        this.btn_sent.visible = true;
        this.label_choose.visible = true;
        this.currentSelectIndex = btnGroup.selectedValue;
        var text = btnGroup.selection.label;
        if (text.length > 10) {
            text = text.substr(0, 9) + "...";
        }
        this.label_choose.text = text;
    };
    return DialogueCommentUIView;
}(BaseEuiView));
__reflect(DialogueCommentUIView.prototype, "DialogueCommentUIView");
/**
 * 玩家或ai发言
 */
var DialogType;
(function (DialogType) {
    DialogType[DialogType["Player"] = 0] = "Player";
    DialogType[DialogType["Ai"] = 1] = "Ai";
})(DialogType || (DialogType = {}));
/**
 * 对话条
 */
var DialogueItemView = (function (_super) {
    __extends(DialogueItemView, _super);
    function DialogueItemView() {
        var _this = _super.call(this) || this;
        _this.pointList = ".";
        _this.count = 0;
        _this.audioNames = ["image_voice1_png", "image_voice2_png", "image_voice3_png"];
        _this.imageIndex = 0;
        _this.isPlay = false; //
        _this.skinName = "resource/skins/Wechat_talk_dialogue_item.exml";
        _this.root_oriHeight = _this.root_Group.height;
        _this.left_audio_play.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            var _this = this;
            if (!this.isPlay) {
                App.SoundManager.stopChat();
                App.SoundManager.playChat(this.mconfig.voice, function (sound) { return _this.UpdateAudioBtn(sound); }, function () { return _this.StopSound(); });
                this.SetImageAuto();
            }
            else {
                if (this.currentSound) {
                    this.StopSound();
                }
            }
        }.bind(_this), _this);
        return _this;
    }
    /**
     * 播放或暂停
     */
    DialogueItemView.prototype.UpdateAudioBtn = function (sound) {
        if (sound) {
            this.currentSound = sound;
            this.isPlay = true;
            var lasting = sound.length;
            App.TimerManager.doTimer(lasting * 1000, 1, function () {
                App.SoundManager.stopChat();
            }.bind(this), this);
            App.TimerManager.doTimer(500, 0, function () {
                this.SetImageAuto();
            }.bind(this), this);
        }
    };
    /**
     * 设置图片
     */
    DialogueItemView.prototype.SetImageAuto = function () {
        this.left_audioImage.source = this.audioNames[this.imageIndex];
        this.imageIndex++;
        this.imageIndex = this.imageIndex % 3;
    };
    /**
     * 停止播放
     */
    DialogueItemView.prototype.StopSound = function () {
        this.isPlay = false;
        this.left_audioImage.source = this.audioNames[2];
        App.TimerManager.removeAll(this);
    };
    /**
     *  更新非玩家
     */
    DialogueItemView.prototype.UpdateInfo = function (config, info) {
        this.mconfig = config;
        this.left_group.visible = true;
        this.right_group.visible = false;
        this.left_audio_play.visible = false;
        this.left_label.visible = true;
        this.left_talkdi.visible = true;
        this.left_talkdi1.visible = true;
        this.left_audioImage.visible = false;
        if (this.mconfig.chatType == WeChatGroupType.Flock) {
            this.left_name.text = this.mconfig.name;
            this.left_name.visible = true;
        }
        else {
            this.left_name.visible = false;
        }
        this.height = this.root_oriHeight;
        this.left_playericon.source = config.head;
        this.SetWaitInput();
        this.UpdateScale();
    };
    /**
     * 设置等待输入
     */
    DialogueItemView.prototype.SetWaitInput = function () {
        this.count++;
        this.count = this.count % 3;
        var pointStr = "";
        for (var i = 0; i <= this.count; i++) {
            pointStr += this.pointList;
        }
        this.left_label.text = StrConfig.GetConfig(1007).str + pointStr;
    };
    /**
     * 设置ai聊天内容
     */
    DialogueItemView.prototype.SetChatText = function () {
        if (this.mconfig.npcDialogType == 1) {
            this.left_label.visible = true;
            this.left_talkdi.visible = true;
            this.left_talkdi1.visible = true;
            this.left_audio_play.visible = false;
            this.left_label.text = this.mconfig.content;
            this.UpdateScale();
        }
        else if (this.mconfig.npcDialogType == 2) {
            this.left_label.visible = false;
            this.left_talkdi.visible = false;
            this.left_talkdi1.visible = false;
            this.left_audio_play.visible = true;
            this.left_audioImage.visible = true;
            this.left_audioImage.source = this.audioNames[2];
        }
    };
    /**
     * 更新组件大小
     */
    DialogueItemView.prototype.UpdateScale = function () {
        if (this.left_label.width > this.left_dialoggroup.width) {
            this.left_label.width = this.left_dialoggroup.width;
        }
        if (this.left_label.height > this.root_Group.height - 60) {
            this.height = this.left_label.height + 80;
        }
        this.left_talkdi.height = this.left_label.height + 20;
        this.left_talkdi.width = this.left_label.width + 40;
    };
    /**
     * 生成玩家聊天
     */
    DialogueItemView.prototype.CreatePlayDialog = function (config, info, selectId) {
        if (selectId === void 0) { selectId = 0; }
        this.left_group.visible = false;
        this.right_group.visible = true;
        this.right_playericon.source = "boy_icon_png"; //玩家头像暂时写死
        this.height = this.root_oriHeight;
        this.right_audio_play.visible = false;
        if (selectId == 0) {
        }
        else {
            var text = void 0;
            if (selectId == 1) {
                text = config.optionContent1;
            }
            if (selectId == 2) {
                text = config.optionContent2;
            }
            if (selectId == 3) {
                text = config.optionContent3;
            }
            if (selectId == 4) {
                text = config.optionContent4;
            }
            this.right_label.text = text;
            if (this.right_label.width > this.right_dialoggroup.width) {
                this.right_label.width = this.right_dialoggroup.width;
            }
            if (this.right_label.height > this.root_Group.height - 60) {
                this.height = this.right_label.height + 80;
            }
            this.right_talkdi.height = this.right_label.height + 20;
            this.right_talkdi.width = this.right_label.width + 20;
        }
    };
    return DialogueItemView;
}(eui.Component));
__reflect(DialogueItemView.prototype, "DialogueItemView");
//# sourceMappingURL=DialogueCommentUIView.js.map