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
 * 朋友圈界面
*/
var FriendMomentUIView = (function (_super) {
    __extends(FriendMomentUIView, _super);
    function FriendMomentUIView($controller, $parent, key) {
        var _this = _super.call(this, $controller, $parent, key) || this;
        _this.py_gro_gap = 0;
        _this.py_gro_array = new Array();
        _this.py_gro_data = new Array(); //朋友圈的临时数据
        _this.gro_pyq = $parent;
        _this.onInitUI();
        return _this;
    }
    FriendMomentUIView.prototype.onInitUI = function () {
        this.py_btn_back = this.gro_pyq.getChildByName("py_btn_back");
        this.py_btn_announce = this.gro_pyq.getChildByName("py_btn_announce");
        this.py_gro_total = this.gro_pyq.getChildByName("py_scr").getChildByName("py_gro_total");
        this.py_gro_gap = this.py_gro_total.layout.gap;
        this.py_btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClose, this);
        this.py_btn_announce.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onAnnounceInfo, this);
    };
    FriendMomentUIView.prototype.onChildGroupShow = function () {
        _super.prototype.onChildGroupShow.call(this);
        if (FriendMomentUIView.isFirstOpen == 1) {
            for (var index = 0; index < WechatConfig.array.length; index++) {
                var config = WechatConfig.array[index];
                if (config != null && config.personID != 0) {
                    this.py_gro_data.push(config.id);
                    App.WechatManager.addAlreadyAnnId(config.id); //添加临时数据
                }
            }
        }
        this.onSetFriendMessageUIInfo();
    };
    FriendMomentUIView.prototype.onChildGroupHide = function () {
        FriendMomentUIView.isFirstOpen++;
    };
    /**
     * 朋友圈动态
    */
    FriendMomentUIView.prototype.onSetFriendMessageUIInfo = function (ctid) {
        for (var index = 0; index < this.py_gro_data.length; index++) {
            var config = WechatConfig.GetConfig(this.py_gro_data[index]);
            if (config != null) {
                if (!this.isArrayContain(config.id)) {
                    var tempgroup = new FCFriendGroup(config.id);
                    tempgroup.initItemGropuHeight(this.py_gro_gap);
                    tempgroup.creatureCondition(config, ctid); //朋友圈动态//
                    if (ctid == null) {
                        tempgroup.creatureOtherMessage(config); //朋友圈伙伴留言//
                    }
                    else {
                        tempgroup.creatureOtherMessage(config, true); //玩家动态,伙伴留言//
                    }
                    tempgroup.cretureAddLine(this.py_gro_gap); //朋友圈分割线//
                    this.py_gro_array.push(tempgroup);
                    this.py_gro_total.addChild(tempgroup.getItemGroup);
                }
                else if (FriendMomentUIView.isFirstOpen >= 2) {
                    var temp = this.getArrayInfoItem(this.py_gro_data[index]);
                    if (temp != null) {
                        temp.updateCondition();
                        temp.updateMessReply();
                        temp.updateMessComm();
                    }
                }
            }
        }
    };
    /**
     * 发布动态
    */
    FriendMomentUIView.prototype.onAnnounceInfo = function () {
        var config = WechatConfig.GetConfig(1);
        App.EventMgrHelper.PushEvent(EventDef.announceInfo, config.id);
    };
    /**
     * 发布朋友圈
    */
    FriendMomentUIView.prototype.onUpdateAnnounceInfo = function (cfid, ctid) {
        this.py_gro_data.push(cfid);
        this.onSetFriendMessageUIInfo(ctid);
    };
    /**
     * 玩家添加留言
    */
    FriendMomentUIView.prototype.onUpdateCommentInfo = function (cfid, ctid) {
        var temp = this.getArrayInfoItem(cfid);
        if (temp != null) {
            temp.cretureAddMessage(cfid, ctid);
        }
    };
    /**
     * 是否已经显示动态
    */
    FriendMomentUIView.prototype.isArrayContain = function (id) {
        var flag = false;
        for (var index = 0; index < this.py_gro_array.length; index++) {
            if (this.py_gro_array[index].getItemId == id) {
                flag = true;
                break;
            }
        }
        return flag;
    };
    /**
     * 获取动态
    */
    FriendMomentUIView.prototype.getArrayInfoItem = function (id) {
        var infoItem;
        for (var index = 0; index < this.py_gro_array.length; index++) {
            if (this.py_gro_array[index].getItemId == id) {
                infoItem = this.py_gro_array[index];
                break;
            }
        }
        return infoItem;
    };
    FriendMomentUIView.isFirstOpen = 1;
    return FriendMomentUIView;
}(BaseEuiChildView));
__reflect(FriendMomentUIView.prototype, "FriendMomentUIView");
/**
 * 朋友圈朋友消息group
*/
var FCFriendGroup = (function (_super) {
    __extends(FCFriendGroup, _super);
    function FCFriendGroup(cid) {
        var _this = _super.call(this, null, null) || this;
        _this.group_id = 0;
        _this.group_id = cid;
        _this.skinName = "resource/skins/item_vertical_group.exml";
        return _this;
    }
    Object.defineProperty(FCFriendGroup.prototype, "getItemGroup", {
        get: function () {
            return this.py_item_group;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FCFriendGroup.prototype, "getItemId", {
        get: function () {
            return this.group_id;
        },
        enumerable: true,
        configurable: true
    });
    FCFriendGroup.prototype.initItemGropuHeight = function (gap) {
        this.py_item_group.height = gap;
    };
    /**
     * 添加动态
    */
    FCFriendGroup.prototype.creatureCondition = function (config, ctid) {
        this.scrann = new FCFriendAnnounce(config.id);
        if (config.personID == 0) {
            this.scrann.setConditionInfo(ctid); //玩家的动态//
        }
        else {
            this.scrann.setConditionInfo(config.contentId[0]); //伙伴的动态//
        }
        this.py_item_group.height += this.scrann.groupHeight;
        this.py_item_group.addChild(this.scrann.getGroup);
    };
    /**
     * 刷新动态
    */
    FCFriendGroup.prototype.updateCondition = function () {
        this.py_item_group.height -= this.scrann.groupHeight;
        this.scrann.updateConditionInfo();
        this.py_item_group.height += this.scrann.groupHeight;
    };
    /**
     * 添加伙伴留言
     * isSelf是否是自己的动态
    */
    FCFriendGroup.prototype.creatureOtherMessage = function (config, isSelf) {
        if (isSelf === void 0) { isSelf = false; }
        this.scremss = new FCFriendMessage(config.id);
        this.scremss.setOtherMessaged(config, isSelf);
        this.py_item_group.height += this.scremss.groupHeight;
        this.py_item_group.addChild(this.scremss.groallMessage);
    };
    /**
     * 玩家添加留言
    */
    FCFriendGroup.prototype.cretureAddMessage = function (cfid, ctid) {
        this.py_item_group.height -= this.scremss.groupHeight;
        this.scremss.setSelfComment(cfid, ctid);
        this.py_item_group.height += this.scremss.groupHeight;
    };
    /**
     * 刷新留言
    */
    FCFriendGroup.prototype.updateMessComm = function () {
        this.py_item_group.height -= this.scremss.groupHeight;
        this.scremss.updateMessComm();
        this.py_item_group.height += this.scremss.groupHeight;
    };
    /**
     * 刷新留言回复
    */
    FCFriendGroup.prototype.updateMessReply = function () {
        this.py_item_group.height -= this.scremss.groupHeight;
        this.scremss.updateReply();
        this.py_item_group.height += this.scremss.groupHeight;
    };
    /**
     * 添加分割线
    */
    FCFriendGroup.prototype.cretureAddLine = function (gap) {
        this.myLine = new eui.Image();
        this.myLine.source = "image_wuchatline1_png";
        this.myLine.width = this.py_item_group.width;
        this.py_item_group.height += this.myLine.height;
        this.py_item_group.addChild(this.myLine);
        this.py_item_group.height += gap;
    };
    Object.defineProperty(FCFriendGroup.prototype, "preLineIndex", {
        /**
         * 分割线之前的位置
        */
        get: function () {
            return this.py_item_group.getChildIndex(this.myLine) - 1;
        },
        enumerable: true,
        configurable: true
    });
    return FCFriendGroup;
}(BaseEuiView));
__reflect(FCFriendGroup.prototype, "FCFriendGroup");
/**
 * 朋友圈朋友动态
*/
var FCFriendAnnounce = (function (_super) {
    __extends(FCFriendAnnounce, _super);
    function FCFriendAnnounce(id) {
        var _this = _super.call(this, null, null) || this;
        _this.gro_con_gap = 0;
        _this.isSelfReply = false;
        _this.infoId = 0;
        _this.infoId = id;
        _this.skinName = "resource/skins/Wechat_item.exml";
        _this.btn_message.addEventListener(egret.TouchEvent.TOUCH_TAP, _this.onClickMessage, _this);
        _this.gro_con_gap = _this.gro_content.layout.gap;
        return _this;
    }
    Object.defineProperty(FCFriendAnnounce.prototype, "getGroup", {
        get: function () {
            return this.player;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FCFriendAnnounce.prototype, "groupHeight", {
        get: function () {
            return this.player.height;
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 动态消息
    */
    FCFriendAnnounce.prototype.setConditionInfo = function (ctid) {
        if (ctid === void 0) { ctid = 0; }
        var config = WechatConfig.GetConfig(this.infoId);
        var cConfig = WechatContentConfig.GetConfig(ctid);
        var girl;
        if (config.personID != 0) {
            girl = App.PlayerManager.GetGirl(config.personID);
        }
        if (cConfig == null) {
            return;
        }
        this.head.source = config.head;
        if ((config.personID == 0 || this.isSelfReply) && this.gro_content.getChildIndex(this.btn_message) != -1) {
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.btn_message.height;
            this.gro_content.removeChild(this.btn_message);
        }
        if (cConfig.content != "") {
            if (config.personID == 0) {
                this.myname.text = App.PlayerManager.Name;
            }
            else {
                if (girl)
                    this.myname.text = girl.GirlName;
            }
            this.des.text = cConfig.content;
        }
        else {
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.myname.height;
            this.gro_content.removeChild(this.myname);
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.des.height;
            this.gro_content.removeChild(this.des);
        }
        if (config.pic != "") {
            this.pic.source = config.pic;
        }
        else {
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.pic.height;
            this.gro_content.removeChild(this.pic);
        }
        this.player.height = this.gro_content.height;
    };
    /**
     * 刷新动态
    */
    FCFriendAnnounce.prototype.updateConditionInfo = function () {
        var config = WechatConfig.GetConfig(this.infoId);
        if (config.personID != 0) {
            var girl = App.PlayerManager.GetGirl(config.personID);
            if (girl)
                this.myname.text = girl.GirlName;
        }
        else {
            this.myname.text = App.PlayerManager.Name;
        }
        if ((config.personID == 0 || this.isSelfReply) && this.gro_content.getChildIndex(this.btn_message) != -1) {
            this.gro_content.height -= this.gro_con_gap;
            this.gro_content.height -= this.btn_message.height;
            this.gro_content.removeChild(this.btn_message);
            this.player.height = this.gro_content.height;
        }
    };
    /**
     * 点击留言
    */
    FCFriendAnnounce.prototype.onClickMessage = function () {
        this.isSelfReply = true;
        this.btn_message.enabled = false;
        var config = WechatConfig.GetConfig(this.infoId);
        App.EventMgrHelper.PushEvent(EventDef.commentInfo, config.id);
    };
    return FCFriendAnnounce;
}(BaseEuiView));
__reflect(FCFriendAnnounce.prototype, "FCFriendAnnounce");
/**
 * 朋友圈留言
*/
var FCFriendMessage = (function (_super) {
    __extends(FCFriendMessage, _super);
    function FCFriendMessage(id) {
        var _this = _super.call(this, null, null) || this;
        _this.gro_gap = 0;
        _this.gro_height = 0;
        _this.gro_textY = 0;
        _this.infoId = 0;
        _this.replyStrName = new Array();
        _this.isFirstSelfReply = true;
        _this.isFirstOtherComment = true;
        _this.isFirstOtherReply = true;
        _this.infoId = id;
        _this.skinName = "resource/skins/Wechat_talk_item.exml";
        _this.gro_gap = _this.gro_mess.layout.gap;
        return _this;
    }
    Object.defineProperty(FCFriendMessage.prototype, "groallMessage", {
        get: function () {
            return this.gro_all;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(FCFriendMessage.prototype, "groupHeight", {
        get: function () {
            return this.gro_all.height;
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 玩家添加留言
    */
    FCFriendMessage.prototype.setSelfComment = function (cfid, ctid) {
        var cConfig = WechatContentConfig.GetConfig(ctid);
        if (cConfig != null) {
            this.creatrueTextField(new LeaveMessage(leaveType.leave, cConfig.content, 0));
            if (cConfig.replyContent != "" && this.isFirstSelfReply) {
                this.isFirstSelfReply = false;
                var config = WechatConfig.GetConfig(cfid);
                this.replyStrName.push(new LeaveMessage(leaveType.reply, cConfig.replyContent, config.personID, 0));
            }
        }
        this.gro_all.height = this.gro_height;
        this.gro_mess.height = this.gro_height;
        this.imagebg.height = this.gro_height;
    };
    /**
     * 伙伴留言
     * isSelf是否是自己的动态
    */
    FCFriendMessage.prototype.setOtherMessaged = function (config, isSelf) {
        if (isSelf === void 0) { isSelf = false; }
        this.gro_height = this.gro_gap;
        for (var index = 0; index < config.otherReply.length; index++) {
            var cConfig = WechatContentConfig.GetConfig(config.otherReply[index]);
            if (cConfig != null) {
                if (isSelf && this.isFirstOtherComment) {
                    this.replyStrName.push(new LeaveMessage(leaveType.leave, cConfig.content, cConfig.type));
                }
                else {
                    this.creatrueTextField(new LeaveMessage(leaveType.leave, cConfig.content, cConfig.type));
                }
                if (cConfig.replyContent != "" && this.isFirstOtherReply) {
                    this.isFirstOtherReply = false;
                    this.replyStrName.push(new LeaveMessage(leaveType.reply, cConfig.replyContent, config.personID, cConfig.type));
                }
            }
        }
        if (isSelf && this.isFirstOtherComment) {
            this.gro_all.height = this.gro_height;
            this.gro_mess.height = this.gro_height;
            this.imagebg.height = this.gro_height;
            this.imagebg.visible = false;
        }
        else {
            this.gro_all.height = this.gro_height;
            this.gro_mess.height = this.gro_height;
            this.imagebg.height = this.gro_height;
            this.imagebg.visible = true;
        }
        this.isFirstOtherComment = false;
    };
    /**
     * 刷新留言
    */
    FCFriendMessage.prototype.updateMessComm = function () {
        if (this.replyStrName.length > 0) {
            for (var index = 0; index < this.replyStrName.length; index++) {
                if (this.replyStrName[index].CurrentType == leaveType.leave)
                    this.creatrueTextField(this.replyStrName[index]);
            }
            this.gro_all.height = this.gro_height;
            this.gro_mess.height = this.gro_height;
            this.imagebg.height = this.gro_height;
            this.imagebg.visible = true;
        }
    };
    /**
     * 刷新回复
    */
    FCFriendMessage.prototype.updateReply = function () {
        if (this.replyStrName.length > 0) {
            for (var index = 0; index < this.replyStrName.length; index++) {
                if (this.replyStrName[index].CurrentType == leaveType.reply)
                    this.creatrueTextField(this.replyStrName[index]);
            }
            this.gro_all.height = this.gro_height;
            this.gro_mess.height = this.gro_height;
            this.imagebg.height = this.gro_height;
            this.imagebg.visible = true;
        }
    };
    /**
     * 添加消息
    */
    FCFriendMessage.prototype.creatrueTextField = function (msg) {
        for (var i = 0; i < this.gro_mess.numElements; i++) {
            var temptext = this.gro_mess.getChildAt(i);
            if (temptext.Data == msg.UID) {
                temptext.textFlow = [
                    { text: msg.GetName(), style: { "textColor": 0x000000, "fontFamily": "Microsoft YaHei", "size": 30 } },
                    { text: msg.Content, style: { "textColor": 0xffffff, "fontFamily": "Microsoft YaHei", "size": 30 } }
                ];
                return;
            }
        }
        var myText = new InfoTExtField();
        myText.Data = msg.UID;
        myText.width = this.gro_mess.width;
        myText.textFlow = [
            { text: msg.GetName(), style: { "textColor": 0x000000, "fontFamily": "Microsoft YaHei", "size": 30 } },
            { text: msg.Content, style: { "textColor": 0xffffff, "fontFamily": "Microsoft YaHei", "size": 30 } }
        ];
        myText.y = this.gro_textY;
        this.gro_textY += myText.height + this.gro_gap;
        this.gro_height += myText.height + this.gro_gap;
        this.gro_mess.addChild(myText);
    };
    return FCFriendMessage;
}(BaseEuiView));
__reflect(FCFriendMessage.prototype, "FCFriendMessage");
var InfoTExtField = (function (_super) {
    __extends(InfoTExtField, _super);
    function InfoTExtField() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    Object.defineProperty(InfoTExtField.prototype, "Data", {
        get: function () { return this.data; },
        set: function (value) { this.data = value; },
        enumerable: true,
        configurable: true
    });
    return InfoTExtField;
}(egret.TextField));
__reflect(InfoTExtField.prototype, "InfoTExtField");
var leaveType;
(function (leaveType) {
    /**留言*/
    leaveType[leaveType["leave"] = 0] = "leave";
    /**回复*/
    leaveType[leaveType["reply"] = 1] = "reply";
})(leaveType || (leaveType = {}));
var LeaveMessage = (function () {
    function LeaveMessage(type, content, leftID, rightID) {
        if (leftID === void 0) { leftID = 0; }
        if (rightID === void 0) { rightID = 0; }
        this.currentType = type;
        this.content = content;
        this.leftID = leftID;
        this.rightID = rightID;
        this.uid = App.MathUtils.uuid(8, 10);
    }
    Object.defineProperty(LeaveMessage.prototype, "Content", {
        get: function () { return this.content; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LeaveMessage.prototype, "CurrentType", {
        get: function () { return this.currentType; },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(LeaveMessage.prototype, "UID", {
        get: function () { return this.uid; },
        enumerable: true,
        configurable: true
    });
    LeaveMessage.prototype.GetName = function () {
        var leftName;
        var rightName;
        var retName;
        if (this.leftID == 0) {
            leftName = App.PlayerManager.Name;
        }
        else {
            leftName = App.PlayerManager.GetGirl(this.leftID).GirlName;
        }
        if (this.currentType == leaveType.leave) {
            retName = leftName + ": ";
        }
        else if (this.currentType == leaveType.reply) {
            if (this.rightID == 0) {
                rightName = App.PlayerManager.Name;
            }
            else {
                rightName = App.PlayerManager.GetGirl(this.rightID).GirlName;
            }
            retName = leftName + "回复" + rightName + "：";
        }
        return retName;
    };
    return LeaveMessage;
}());
__reflect(LeaveMessage.prototype, "LeaveMessage");
//# sourceMappingURL=FriendMomentUIView.js.map