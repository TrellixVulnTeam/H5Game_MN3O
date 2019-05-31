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
var PictureType;
(function (PictureType) {
    PictureType[PictureType["injured"] = 1] = "injured";
    PictureType[PictureType["skill"] = 2] = "skill";
})(PictureType || (PictureType = {}));
/**
 * 战斗立绘
 */
var BattlePictureView = (function (_super) {
    __extends(BattlePictureView, _super);
    function BattlePictureView($controller, $parent) {
        return _super.call(this, $controller, $parent) || this;
    }
    /* 技能立绘组件结束 */
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    BattlePictureView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.BattlePicture);
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    BattlePictureView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    BattlePictureView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.HPGroup.visible = false;
        this.SkillGroup.visible = false;
        //this.playPicturnAnimation(220010, null);//测试
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    BattlePictureView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    /**
     * 播放立绘
    */
    BattlePictureView.prototype.playPicturnAnimation = function (id, callBack) {
        var config = DrawAnimationConfig.GetConfig(id);
        if (config == null) {
            return;
        }
        var drawConfig = DrawConfig.GetConfig(config.drawID);
        if (drawConfig == null) {
            return;
        }
        if (config.type == PictureType.injured) {
            this.PlayHPPicture(id, callBack);
        }
        else if (config.type == PictureType.skill) {
            this.PlaySkillPicture(id, callBack);
        }
    };
    //破甲立绘//
    BattlePictureView.prototype.PlayHPPicture = function (id, callBack) {
        var _this = this;
        this.HPGroup.visible = true;
        var config = DrawAnimationConfig.GetConfig(id);
        var drawConfig = DrawConfig.GetConfig(config.drawID);
        //和谐//
        var isCN = App.GlobalData.GamePlatform == "CN" ? true : false;
        if (isCN) {
            this.image_player_blood.source = drawConfig.draw2;
        }
        else {
            this.image_player_blood.source = drawConfig.draw;
        }
        //是否换表情//
        if (config.face != 0) {
            if (drawConfig.face.length > config.face) {
                this.image_face0.visible = true;
                this.image_face0.source = drawConfig.face[config.face];
                if (drawConfig.facePosition.length >= 2) {
                    this.image_face0.x = drawConfig.facePosition[0];
                    this.image_face0.y = drawConfig.facePosition[1];
                }
            }
            else {
                this.image_face0.visible = false;
            }
        }
        else {
            this.image_face0.visible = false;
        }
        //动画//
        this.pojia.play(0);
        //音效//
        App.SoundManager.playDelyInsetEffect(config.sound, config.soundDelay);
        //回调//
        egret.Tween.get(this.SkillGroup, {})
            .wait(config.liveTime)
            .call(function () {
            _this.pojia.stop();
            _this.onClose();
            if (callBack != null) {
                callBack();
            }
        });
    };
    //技能立绘//
    BattlePictureView.prototype.PlaySkillPicture = function (id, callBack) {
        var _this = this;
        this.SkillGroup.visible = true;
        var config = DrawAnimationConfig.GetConfig(id);
        var drawConfig = DrawConfig.GetConfig(config.drawID);
        //和谐//
        var isCN = App.GlobalData.GamePlatform == "CN" ? true : false;
        if (isCN) {
            this.image_player.source = drawConfig.draw2;
        }
        else {
            this.image_player.source = drawConfig.draw;
        }
        //是否换表情//
        if (config.face != 0) {
            if (drawConfig.face.length > config.face) {
                this.image_face.visible = true;
                this.image_face.source = drawConfig.face[config.face];
                if (drawConfig.facePosition.length >= 2) {
                    this.image_face.x = drawConfig.facePosition[0];
                    this.image_face.y = drawConfig.facePosition[1];
                }
            }
            else {
                this.image_face.visible = false;
            }
        }
        else {
            this.image_face.visible = false;
        }
        //技能//
        this.image_skill.source = config.extraResource1;
        //动画//
        this.star.play(0);
        //音效//
        App.SoundManager.playDelyInsetEffect(config.sound, config.soundDelay);
        //回调//
        egret.Tween.get(this.SkillGroup, {})
            .wait(config.liveTime)
            .call(function () {
            _this.star.stop();
            _this.onClose();
            if (callBack != null) {
                callBack();
            }
        });
    };
    return BattlePictureView;
}(BaseEuiView));
__reflect(BattlePictureView.prototype, "BattlePictureView");
//# sourceMappingURL=BattlePictureView.js.map