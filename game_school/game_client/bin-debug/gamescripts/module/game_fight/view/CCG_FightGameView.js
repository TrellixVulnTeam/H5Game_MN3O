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
 * created by sjz on 2018-5-19.
 * 战斗视图层
 */
var CCG_FightGameView = (function (_super) {
    __extends(CCG_FightGameView, _super);
    function CCG_FightGameView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.skillArr = []; //技能item列表
        /**
         * 更新时间
         */
        _this.timeStr = ["image_time1_png", "image_time2_png", "image_time3_png"];
        return _this;
    }
    Object.defineProperty(CCG_FightGameView.prototype, "Model", {
        get: function () {
            return App.ControllerManager.getControllerModel(ControllerConst.CCG_GameFight);
        },
        enumerable: true,
        configurable: true
    });
    CCG_FightGameView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = "resource/skins/MainBattle.exml"; // App.ViewManager.getSkin(ViewConst.BattleMain);
        this.background = new CCG_SceneBackGround();
        this.addChild(this.background);
        this.image_mask.visible = false;
        this.gameObjcetLayer = new egret.DisplayObjectContainer();
        this.gameObjcetLayer.name = "GameObjectLayer";
        this.pointList.addChild(this.gameObjcetLayer);
        this.gameEffectLayer = new egret.DisplayObjectContainer;
        this.gameEffectLayer.name = "GameEffectLayer";
        this.addChild(this.gameEffectLayer);
        this.GetBattleMainPoint();
        this.btn_auto.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.SwitchingFightStyle(true);
        }, this);
        this.btn_manual.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.SwitchingFightStyle(false);
        }, this);
        this.btn_backmain.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.open(ViewConst.MainUI);
            App.FightManager.IsBackstage = true;
        }, this);
        this.btn_manual.visible = false;
        this.image_time.visible = false;
        this.image_black.visible = false;
        this.battle_time.visible = false;
        this.time_Pos = new egret.Point(this.image_time.localToGlobal().x, this.image_time.localToGlobal().y);
        this.playerBlood = new MainBlood(this.pro_player, this.label_numplayer);
        this.enemyBlood = new MainBlood(this.pro_enemy, this.label_numenemy);
    };
    CCG_FightGameView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    CCG_FightGameView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        App.FightManager.IsBackstage = false;
    };
    CCG_FightGameView.prototype.SetBackMainBtnVis = function (isVis) {
        this.btn_backmain.visible = isVis;
    };
    /**
     * 进入下场战斗时跳转背景
     */
    CCG_FightGameView.prototype.FightConvert = function (callback) {
        var _this = this;
        this.image_black.visible = true;
        this.image_black.alpha = 0;
        //  this.setChildIndex(this.image_black, this.getChildIndex(this.getGameObjcetLayer())+1);
        egret.Tween.get(this.image_black, { loop: false, onChangeObj: this })
            .to({ alpha: 1 }, 500)
            .wait(500)
            .call(function () {
            egret.Tween.get(_this.image_black, { loop: false, onChangeObj: _this })
                .to({ alpha: 0 }, 500)
                .call(function () {
                _this.image_black.visible = false;
                callback();
            });
        });
    };
    /**
     * 播放战斗开始动画
     */
    CCG_FightGameView.prototype.PlayFightAni = function (callback) {
        if (!this.fights) {
            this.fights = new FightStartView();
            this.addChild(this.fights);
        }
        this.fights.visible = true;
        this.fights.AniPlay(callback);
    };
    /**
     * 回合提示
     */
    CCG_FightGameView.prototype.RoundPrompt = function (round) {
        var _this = this;
        if (round / 10 >= 1) {
            var bit = void 0;
            if (this.rount_group.getElementAt(1)) {
                bit = this.rount_group.getElementAt(1);
            }
            else {
                bit = new eui.BitmapLabel();
                bit.width = this.font_battle_time.width;
                bit.height = this.font_battle_time.height;
                bit.font = this.font_battle_time.font;
                bit.visible = true;
                this.rount_group.addChild(bit);
            }
            bit.text = (round % 10).toString();
            this.font_battle_time.text = parseInt((round / 10).toString()).toString();
        }
        else {
            if (this.rount_group.getElementAt(1))
                this.rount_group.removeChildAt(1);
            this.font_battle_time.text = round.toString();
        }
        this.battle_time.x = -this.battle_time.width;
        this.battle_time.visible = true;
        egret.Tween.get(this.battle_time, { loop: false, onChangeObj: this })
            .to({ x: 0 }, 500)
            .wait(500)
            .call(function () {
            egret.Tween.get(_this.battle_time, { loop: false, onChangeObj: _this })
                .to({ x: _this.battle_time.width }, 500)
                .call(function () {
                _this.battle_time.visible = false;
            });
        });
    };
    /*
    *临时方法，从战斗页面获取站位
    */
    CCG_FightGameView.prototype.GetBattleMainPoint = function () {
        if (!App.FightManager.IsFightFinish) {
            for (var i = 0; i < this.pointList.numChildren; i++) {
                var childPoint = this.pointList.getElementAt(i);
                var po = childPoint.localToGlobal(childPoint.x, childPoint.y);
                App.FightManager.AddPoint(po);
            }
        }
    };
    /**
     * 切换战斗方式
     */
    CCG_FightGameView.prototype.SwitchingFightStyle = function (auto) {
        this.btn_auto.visible = !auto;
        this.btn_manual.visible = auto;
    };
    /**
     * 初始化
     */
    CCG_FightGameView.prototype.InitGameUI = function (fightInfo) {
        this.UpdateRound(0);
        this.label_name_player.text = fightInfo[0].name;
        this.label_name_enemy.text = fightInfo[1].name;
        this.playerBlood.maximum = fightInfo[0].blood;
        this.playerBlood.minimum = 0;
        this.playerBlood.setValue(fightInfo[0].blood);
        this.enemyBlood.maximum = fightInfo[1].blood;
        this.enemyBlood.minimum = 0;
        this.enemyBlood.setValue(fightInfo[1].blood);
        if (this.skillArr.length == 0) {
            var item = new SkillItem();
            var item1 = new SkillItem();
            this.skillArr.push(item);
            this.skillArr.push(item1);
            this.skill_list.addChild(item);
            this.skill_list.addChild(item1);
        }
        this.skillGroup.visible = false;
        this.backImage.source = fightInfo[0].backImage;
    };
    /**
     * 更新回合数
     */
    CCG_FightGameView.prototype.UpdateRound = function (roundCount) {
        if (roundCount != null) {
            this.label_round.text = roundCount.toString();
        }
        else {
            this.label_round.text = "0";
        }
        //if(roundCount>0)
        // this. RoundPrompt(roundCount);
    };
    CCG_FightGameView.prototype.UpdateTimer = function (timer) {
        var _this = this;
        this.image_time.visible = true;
        this.image_time.scaleY = 0;
        this.image_time.scaleX = 0;
        this.image_time.source = this.timeStr[timer];
        egret.Tween.get(this.image_time, {
            loop: false,
            onChangeObj: this
        })
            .to({ scaleY: 1, scaleX: 1, x: this.image_time.x - this.image_time.width / 4, y: this.image_time.y - this.image_time.height / 4 }, 500)
            .call(function () {
            if (timer == 0) {
                egret.Tween.get(_this.image_time)
                    .to({ scaleX: 0, scaleY: 0, x: _this.btn_auto.localToGlobal().x, y: _this.btn_auto.localToGlobal().y }, 500)
                    .call(function () {
                    _this.image_time.x = _this.time_Pos.x;
                    _this.image_time.y = _this.time_Pos.y;
                    _this.SwitchingFightStyle(true);
                });
            }
            else {
                egret.Tween.get(_this.image_time)
                    .to({ scaleX: 0, scaleY: 0, x: _this.image_time.x + _this.image_time.width / 4, y: _this.image_time.y + _this.image_time.height / 4 }, 500);
            }
        });
    };
    /**
     * 更新血条
     */
    CCG_FightGameView.prototype.UpdateHpBar = function (camp, value) {
        if (camp == Camp.Friendly) {
            this.playerBlood.setValue(value);
        }
        else {
            this.enemyBlood.setValue(value);
        }
    };
    /**
     * 打开技能框
     */
    CCG_FightGameView.prototype.OpenSkillGroup = function (own, skills) {
        if (own.camp == Camp.Friendly && skills != null) {
            this.skillGroup.visible = true;
            for (var i = 0; i < this.skillArr.length; i++) {
                this.skillArr[i].visible = true;
                this.skillArr[i].ResetSkillItem(skills[i]);
            }
        }
        else {
            for (var i = 0; i < this.skillArr.length; i++) {
                this.skillArr[i].visible = false;
            }
        }
        this.players_kill.source = own.CreatureConf.icon;
        this.label_name_skill.text = own.basicattr.Name;
    };
    CCG_FightGameView.prototype.initBackground = function (mapId, view) {
        this.background.init(mapId, view);
    };
    CCG_FightGameView.prototype.getGameObjcetLayer = function () {
        return this.gameObjcetLayer;
    };
    CCG_FightGameView.prototype.getGameEffectLayer = function () {
        return this.gameEffectLayer;
    };
    CCG_FightGameView.prototype.getBackground = function () {
        return this.background;
    };
    CCG_FightGameView.prototype.setObjMaskViewViable = function (bool) {
        this.image_mask.visible = bool;
    };
    /**
     * 设置遮盖
     */
    CCG_FightGameView.prototype.setObjMaskViewIndex = function (objUID, mask) {
        if (this.image_mask == null || objUID == null) {
            return;
        }
        this.setObjMaskViewViable(mask);
        var maskDepth = this.gameObjcetLayer.getChildIndex(this.image_mask);
        if (maskDepth == -1) {
            this.gameObjcetLayer.addChild(this.image_mask);
        }
        maskDepth = this.gameObjcetLayer.numChildren;
        this.gameObjcetLayer.setChildIndex(this.image_mask, maskDepth);
        var currentObj = App.FightManager.GetPlayerByUId(objUID);
        if (!currentObj)
            return;
        var avatar = currentObj.getComponent(ComponentType.Dragon);
        if (!avatar)
            return;
        if (mask) {
            this.gameObjcetLayer.setChildIndex(avatar.Body, maskDepth + 1);
        }
        else {
            this.gameObjcetLayer.setChildIndex(avatar.Body, maskDepth - 1);
        }
    };
    return CCG_FightGameView;
}(BaseEuiView));
__reflect(CCG_FightGameView.prototype, "CCG_FightGameView");
/**
 * 战斗开始界面
 */
var FightStartView = (function (_super) {
    __extends(FightStartView, _super);
    function FightStartView() {
        var _this = _super.call(this, null, null) || this;
        _this.skinName = "resource/skins/Battle_star.exml";
        _this.star1.addEventListener("complete", _this.onTweenGroupComplete, _this);
        _this.star1.addEventListener("itemComplete", _this.onTweenItemComplete, _this);
        return _this;
    }
    /**
     * 动画播放
     */
    FightStartView.prototype.AniPlay = function (callback) {
        this.star1.play(0);
        if (callback)
            this.playEndFun = callback;
        else
            this.playEndFun = null;
    };
    /**
     * 动画组播放完成
     */
    FightStartView.prototype.onTweenGroupComplete = function () {
        this.visible = false;
        if (this.playEndFun)
            this.playEndFun();
    };
    /**
     * 动画组中的一项播放完成
     */
    FightStartView.prototype.onTweenItemComplete = function (event) {
        var item = event.data;
    };
    return FightStartView;
}(BaseEuiView));
__reflect(FightStartView.prototype, "FightStartView");
/**
 * 技能图标
 */
var SkillItem = (function (_super) {
    __extends(SkillItem, _super);
    function SkillItem() {
        var _this = _super.call(this) || this;
        _this.skinName = "resource/skins/Item_skill.exml";
        _this.touchEnabled = true;
        _this.addEventListener(egret.TouchEvent.TOUCH_TAP, _this.OnClickSKill, _this);
        return _this;
    }
    /**
     * 选择技能
     */
    SkillItem.prototype.OnClickSKill = function () {
        if (this.currentSkill.CD == 0 && !App.FightManager.IsAutomatic) {
            App.ActionManager.CurrentSkill = this.currentSkill;
        }
        else {
        }
    };
    /**
     * 重置技能
     */
    SkillItem.prototype.ResetSkillItem = function (skill) {
        if (skill) {
            this.currentSkill = skill;
            this.label_cd.text = skill.CD.toString();
            this.image_skill.source = skill.MagicConfig.Icon;
            this.image_cd.visible = skill.CD == 0 ? false : true;
            this.label_cd.visible = skill.CD == 0 ? false : true;
        }
    };
    return SkillItem;
}(eui.Component));
__reflect(SkillItem.prototype, "SkillItem");
/* 血条 */
var MainBlood = (function (_super) {
    __extends(MainBlood, _super);
    function MainBlood(mthumb, labelDisplay) {
        var _this = _super.call(this) || this;
        _this.mthumb = mthumb;
        _this.labelDisplay = labelDisplay;
        _this.oriWidth = _this.mthumb.width;
        return _this;
    }
    MainBlood.prototype.setLabel = function (str) {
        this.labelDisplay.text = str;
    };
    MainBlood.prototype.setValue = function (num) {
        if (num <= 0) {
            num = 0;
        }
        if (num >= this.maximum) {
            this.maximum = num;
        }
        var max = Math.round(this.maximum).toString();
        var current = Math.round(num).toString();
        this.setLabel(current + "/" + max);
        this.pendingValue = num;
        this.mthumb.width = this.oriWidth * (num / this.maximum);
    };
    return MainBlood;
}(eui.HSlider));
__reflect(MainBlood.prototype, "MainBlood");
//# sourceMappingURL=CCG_FightGameView.js.map