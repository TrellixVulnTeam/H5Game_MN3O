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
var GrilDetailedInfoUiView = (function (_super) {
    __extends(GrilDetailedInfoUiView, _super);
    function GrilDetailedInfoUiView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.disExtent = 150; //
        _this.currentIndex = 0;
        return _this;
    }
    GrilDetailedInfoUiView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.GrilInfo);
        this.oriImageX = this.imagelist_group.x;
        this.enlarge_group.visible = false;
        this.imagelist_group.visible = false;
        // for(let i=0;i<this.imagelist_group.numElements;i++){
        // 	this.imagelist_group.getChildAt(i).width=this.height;
        // 	this.imagelist_group.getChildAt(i).height=this.width;
        // }
        this.btn_chatback.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.EventMgrHelper.PushEvent(EventDef.CloseGirlInfoView);
        }, this);
        this.btn_ok.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickEnterBtnEventHandler, this);
        this.btn_huanyuan.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickReductionBtnEventHandler, this);
        this.btn_xiugai.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickChangeBtnEventHandler, this);
        this.btn_chat.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickChatBtnEventHandler, this);
        this.btn_history.addEventListener(egret.TouchEvent.TOUCH_TAP, this.OnClickhistoryBtnEventHandler, this);
        this.change_inputtext.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            this.change_inputtext.text = "";
        }.bind(this), this);
        this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_TAP, this.ZoomoutImage, this);
        this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_BEGIN, this.StartMove, this);
        this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_END, this.StopMove, this);
        this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_RELEASE_OUTSIDE, this.StopMove, this);
    };
    GrilDetailedInfoUiView.prototype.StartMove = function (e) {
        this.offsetX = e.stageX;
        this.imagelist_group.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.OnMove, this);
    };
    GrilDetailedInfoUiView.prototype.StopMove = function (e) {
        var _this = this;
        var tempDis = e.stageX - this.offsetX;
        var absDis = (tempDis > 0) ? tempDis : -tempDis;
        if (absDis > this.disExtent) {
            if (tempDis > 0) {
                var imagename_1 = this.GetBeforeImage();
                if (imagename_1 != "") {
                    egret.Tween.get(this.imagelist_group, { loop: false, onChangeObj: this })
                        .to({ x: 0 }, 300)
                        .call(function () {
                        _this.enlarge_Image.source = imagename_1;
                        _this.UpdateImage();
                        _this.imagelist_group.x = _this.oriImageX;
                    });
                }
            }
            else {
                var imagename_2 = this.GetNextImage();
                if (imagename_2 != "") {
                    egret.Tween.get(this.imagelist_group, { loop: false, onChangeObj: this })
                        .to({ x: -(this.middle_image.height * 2) }, 300)
                        .call(function () {
                        _this.enlarge_Image.source = imagename_2;
                        _this.UpdateImage();
                        _this.imagelist_group.x = _this.oriImageX;
                    });
                }
            }
        }
        else {
            this.imagelist_group.x = this.oriImageX;
        }
    };
    GrilDetailedInfoUiView.prototype.OnMove = function (e) {
        if (!this.isMove)
            this.isMove = true;
        var tempOffset = e.stageX - this.offsetX;
        if (tempOffset > 0) {
            if (this.currentIndex > 0) {
                this.imagelist_group.x = this.oriImageX + tempOffset;
            }
        }
        else {
            if (this.currentIndex < this.images.length - 1) {
                this.imagelist_group.x = this.oriImageX + tempOffset;
            }
        }
    };
    GrilDetailedInfoUiView.prototype.GetNextImage = function () {
        if (this.currentIndex < (this.images.length - 1)) {
            this.currentIndex++;
            return this.images[this.currentIndex];
        }
        return "";
    };
    GrilDetailedInfoUiView.prototype.GetBeforeImage = function () {
        if (this.currentIndex > 0) {
            this.currentIndex--;
            return this.images[this.currentIndex];
        }
        return "";
    };
    /**
     * 缩小图片
     */
    GrilDetailedInfoUiView.prototype.ZoomoutImage = function () {
        if (!this.isMove) {
            this.imagelist_group.visible = false;
            this.enlarge_Image.visible = true;
            this.back.play(0);
            App.TimerManager.doTimer(250, 1, function () {
                this.enlarge_group.visible = false;
            }.bind(this), this);
        }
        else {
            this.isMove = false;
        }
    };
    /**
     * 放大
     */
    GrilDetailedInfoUiView.prototype.EnlargeImage = function (imagename) {
        this.isMove = false;
        if (imagename != "") {
            var index = this.images.indexOf(imagename);
            if (index == -1) {
                return;
            }
            this.currentIndex = index;
            this.enlarge_Image.source = imagename;
            this.enlarge_group.visible = true;
            this.xuanzhuan.play(0);
            App.TimerManager.doTimer(250, 1, function () {
                this.UpdateImage();
                this.enlarge_Image.visible = false;
                this.imagelist_group.visible = true;
                this.imagelist_group.height = this.height;
                this.imagelist_group.width = this.width * 3;
            }.bind(this), this);
        }
    };
    GrilDetailedInfoUiView.prototype.UpdateImage = function () {
        this.middle_image.source = this.images[this.currentIndex];
        if (this.currentIndex > 0)
            this.left_image.source = this.images[this.currentIndex - 1];
        if (this.currentIndex < this.images.length - 1)
            this.right_image.source = this.images[this.currentIndex + 1];
    };
    /**
     *  聊天记录
     */
    GrilDetailedInfoUiView.prototype.OnClickhistoryBtnEventHandler = function () {
        App.EventMgrHelper.PushEvent(EventDef.OpenHistoryView, this.currentGirl.GirlId);
    };
    /**
     * 前往聊天
     */
    GrilDetailedInfoUiView.prototype.OnClickChatBtnEventHandler = function () {
        App.EventMgrHelper.PushEvent(EventDef.OpendialogView, this.currentGirl.GirlId, WechatUIType.Wechat_record);
    };
    /**
     * 改名确认
     */
    GrilDetailedInfoUiView.prototype.OnClickEnterBtnEventHandler = function () {
        if (this.change_inputtext) {
            var text = this.change_inputtext.text;
            var tips = StrConfig.GetConfig(11033).str;
            if (text.length > 0 && text != tips) {
                this.change_name.visible = false;
                this.label_name.visible = true;
                this.label_name.text = text;
                this.currentGirl.GirlName = text;
            }
            else {
                this.change_inputtext.text = tips;
            }
        }
    };
    /**
     * 名称还原
     */
    GrilDetailedInfoUiView.prototype.OnClickReductionBtnEventHandler = function () {
        this.label_name.visible = true;
        this.label_name.text = this.currentGirl.Config.name;
        this.currentGirl.GirlName = this.currentGirl.Config.name;
    };
    /**
     * 名称修改
     */
    GrilDetailedInfoUiView.prototype.OnClickChangeBtnEventHandler = function () {
        if (!this.change_name.visible) {
            this.change_name.visible = true;
            this.change_inputtext.text = "";
            this.label_name.visible = false;
        }
        else {
            this.change_name.visible = false;
            this.label_name.visible = true;
        }
    };
    /**
     * 初始化
     */
    GrilDetailedInfoUiView.prototype.InitViewInfo = function (gridId) {
        var _this = this;
        if (gridId) {
            this.change_name.visible = false;
            this.currentGirl = App.PlayerManager.GetGirl(gridId);
            this.image_player.source = this.currentGirl.Config.icon;
            this.label_name.text = this.currentGirl.GirlName;
            this.label_blood_type.text = this.currentGirl.Config.bloodType;
            this.label_star.text = this.currentGirl.Config.constellation;
            var upperLimit = parseInt(PublicConstConfig.GetConfig(5).value);
            this.label_rank.text = this.currentGirl.FriendlyNum.toString();
            this.progre.value = (this.currentGirl.FriendlyNum / upperLimit) * 100;
            this.images = [];
            for (var i = 0; i < App.WechatManager.AlreadyAnnIds.length; i++) {
                var config = WechatConfig.GetConfig(App.WechatManager.AlreadyAnnIds[i]);
                if (config) {
                    if (config.personID == this.currentGirl.GirlId) {
                        this.images.push(config.pic);
                    }
                }
            }
            var num = this.scr_playertalk.numElements;
            for (var j = 0; j < num; j++) {
                var item = void 0;
                if (j < this.images.length) {
                    item = this.scr_playertalk.getChildAt(j);
                    item.visible = true;
                    item.UpdateItem(this.images[j], function (imageName) { return _this.EnlargeImage(imageName); });
                }
                else {
                    item = this.scr_playertalk.getChildAt(this.scr_playertalk.numElements - 1);
                    item.visible = false;
                    ObjectPool.push(item);
                    this.scr_playertalk.removeChild(item);
                }
            }
            var index = this.scr_playertalk.numElements;
            for (var y = index; y < this.images.length; y++) {
                var item = ObjectPool.pop("FriendcircleImageItem");
                item.UpdateItem(this.images[y], function (imageName) { return _this.EnlargeImage(imageName); });
                item.visible = true;
                this.scr_playertalk.addChild(item);
            }
        }
    };
    return GrilDetailedInfoUiView;
}(BaseEuiView));
__reflect(GrilDetailedInfoUiView.prototype, "GrilDetailedInfoUiView");
/**朋友圈图片 */
var FriendcircleImageItem = (function (_super) {
    __extends(FriendcircleImageItem, _super);
    function FriendcircleImageItem() {
        var _this = _super.call(this) || this;
        _this.imageName = "";
        _this.skinName = "resource/skins/Friendcircle_Image.exml";
        _this.root_btn.addEventListener(egret.TouchEvent.TOUCH_TAP, _this.rootBtnClick, _this);
        return _this;
    }
    FriendcircleImageItem.prototype.rootBtnClick = function () {
        this.OnClickRootBtnEvent(this.imageName);
    };
    FriendcircleImageItem.prototype.UpdateItem = function (imageName, itemClickCallback) {
        this.imageName = imageName;
        this.back_Image.source = this.imageName;
        this.OnClickRootBtnEvent = itemClickCallback;
    };
    return FriendcircleImageItem;
}(eui.Component));
__reflect(FriendcircleImageItem.prototype, "FriendcircleImageItem");
//# sourceMappingURL=GrilDetailedInfoUiView.js.map