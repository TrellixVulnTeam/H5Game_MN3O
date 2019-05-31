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
 * 布阵界面
 */
var BattleArrayEditView = (function (_super) {
    __extends(BattleArrayEditView, _super);
    function BattleArrayEditView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        /**
         * 临时指引标记
        */
        _this.isFirstGuide = false;
        _this.isSecondGuide = false;
        _this.isThirdGuide = false;
        _this.isFourthGuide = false;
        return _this;
    }
    BattleArrayEditView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.BattleArray);
        this.isFirstGuide = App.GuideManager.getIsGuide;
        this.isSecondGuide = App.GuideManager.getIsGuide;
        this.isThirdGuide = App.GuideManager.getIsGuide;
        this.isFourthGuide = App.GuideManager.getIsGuide;
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.open(ViewConst.Chapter);
            App.ViewManager.close(ViewConst.BattleArray);
        }, this);
        this.CreateItem();
        this.playermove.touchEnabled = false;
        var radioGroup = new eui.RadioButtonGroup();
        radioGroup.addEventListener(eui.UIEvent.CHANGE, this.radioChangeHandler, this);
        this.btn_team1.value = BelongArray.Array1;
        this.btn_team2.value = BelongArray.Array2;
        this.btn_team3.value = BelongArray.Array3;
        this.btn_team1.group = radioGroup;
        this.btn_team2.group = radioGroup;
        this.btn_team3.group = radioGroup;
        this.btn_team1.selected = true;
        this.btn_teamchoose.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            App.ViewManager.close(ViewConst.BattleArray);
            App.ViewManager.open(ViewConst.Chapter);
        }, this);
        App.EventMgrHelper.PushEvent(EventDef.ChangeTeam, BelongArray.Array1);
    };
    /**选项卡监听 */
    BattleArrayEditView.prototype.radioChangeHandler = function (evt) {
        var radioGroup = evt.target;
        App.EventMgrHelper.PushEvent(EventDef.ChangeTeam, radioGroup.selectedValue);
    };
    /**
     * 切换队伍
     */
    BattleArrayEditView.prototype.ChangeTeam = function (teamInfo) {
        for (var i = 0; i < this.listGroup.numElements; i++) {
            var tempItem = this.listGroup.getChildAt(i);
            if (tempItem) {
                if (tempItem.indexPos <= parseInt(PublicConstConfig.GetConfig(1).value)) {
                    var tempInfo = this.GetInfoByIndex(tempItem.indexPos, teamInfo);
                    if (tempInfo && tempInfo.id != 0) {
                        tempItem.UpdateInfo(tempInfo);
                    }
                    else {
                        tempItem.SetNoIncrease();
                    }
                }
                else {
                    tempItem.SetAction(false);
                }
            }
        }
        if (this.isFirstGuide == false && this.isSecondGuide == false && this.isThirdGuide) {
            this.isThirdGuide = false;
            this.addThirdGuide();
        }
    };
    /**
     * 根据位置获取信息
     */
    BattleArrayEditView.prototype.GetInfoByIndex = function (index, infos) {
        for (var i = 0; i < infos.length; i++) {
            if (infos[i].index == index) {
                return infos[i];
            }
        }
        return null;
    };
    /**
     * 获取指定下标item
     */
    BattleArrayEditView.prototype.GetItemByIndex = function (index) {
        for (var i = 0; i < this.listGroup.numElements; i++) {
            var tempItem = this.listGroup.getChildAt(i);
            if (tempItem.indexPos == index) {
                return tempItem;
            }
        }
        return null;
    };
    BattleArrayEditView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    BattleArrayEditView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        //开启ComponentSystem
        ComponentSystem.start();
        if (this.isFirstGuide) {
            this.isFirstGuide = false;
            this.addFirstGuide();
        }
    };
    /**
     * 临时指引1（第一次进入布阵界面, 点击阵型1按钮）
    */
    BattleArrayEditView.prototype.addFirstGuide = function () {
        var _this = this;
        this.validateNow();
        var mask = new GuideMask(this.btn_team1, function () {
            App.EventMgrHelper.PushEvent(EventDef.ChangeTeam, BelongArray.Array1);
            if (_this.isFirstGuide == false && _this.isSecondGuide) {
                _this.addSecondGuide();
            }
        });
        this.addChild(mask);
    };
    /**
     * 临时指引2（点击阵型1按钮后，点击阵型上的第二个位置）
    */
    BattleArrayEditView.prototype.addSecondGuide = function () {
        var _this = this;
        var item = this.listGroup.getChildAt(0);
        if (item != null) {
            this.validateNow();
            var mask = new GuideMask(item.image_plus, function () {
                _this.isSecondGuide = false;
                App.EventMgrHelper.PushEvent(EventDef.ShowHeroList, item.indexPos);
            });
            this.addChild(mask);
        }
    };
    /**
     * 临时指引3（第二次进入布阵界面，点击退出按钮）
    */
    BattleArrayEditView.prototype.addThirdGuide = function () {
        var _this = this;
        this.validateNow();
        var mask = new GuideMask(this.btn_back, function () {
            _this.onClose();
            _this.addFourthGuide();
        }, "", true, 0, -(this.btn_back.height / 2));
        this.addChild(mask);
    };
    /**
     * 临时指引4（点击退出按钮后，播放剧情，播放剧情后打开主界面）
    */
    BattleArrayEditView.prototype.addFourthGuide = function () {
        //临时播剧情
        App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 105, function () {
            App.ViewManager.close(ViewConst.Dialog);
            App.ViewManager.open(ViewConst.MainUI);
        }.bind(this), 0, 0, "", "");
        // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 105, function () {
        // 	App.ViewManager.close(ViewConst.Dialog);
        // 	App.ViewManager.open(ViewConst.MainUI);
        // });
    };
    /**
     * 生成item
     */
    BattleArrayEditView.prototype.CreateItem = function () {
        if (this.listGroup.numElements == 6)
            return;
        for (var i = 0; i < 6; i++) {
            var item = new HeroArrayItem(i, this.playermove, this.width / 3);
            this.listGroup.addChild(item);
            if (item.indexPos <= parseInt(PublicConstConfig.GetConfig(1).value)) {
                App.EventMgrHelper.PushEventEx(EventDef.InitArray, true, null, item.indexPos, 0, "", "");
                item.SetNoIncrease();
            }
            else {
                App.EventMgrHelper.PushEventEx(EventDef.InitArray, false, null, item.indexPos, 0, "", "");
                item.SetAction(false);
            }
        }
    };
    /**设置所有添加按钮状态 */
    BattleArrayEditView.prototype.SetAddBtnVisible = function (visible) {
        for (var i = 0; i < this.listGroup.numElements; i++) {
            var item = this.listGroup.getChildAt(i);
            if (item && item.action) {
                item.SetAddState(visible);
            }
        }
    };
    /**检测所有站位 */
    BattleArrayEditView.prototype.HitCheckAllPoint = function (target) {
        for (var i = 0; i < this.listGroup.numElements; i++) {
            var item = this.listGroup.getChildAt(i);
            var tempDis = this.hitTestP(target, item);
            if (tempDis != null) {
                return tempDis;
            }
        }
        return null;
    };
    /**碰撞检测 */
    BattleArrayEditView.prototype.hitTestP = function (obj1, obj2) {
        var rect1 = obj1.getBounds(); //获取显示对象的测量边界
        var tempItem = obj2;
        var rect2 = tempItem.Base_back.getBounds();
        4;
        var point1 = this.listGroup.localToGlobal(obj1.x + 400, obj1.y + 200);
        var point2 = this.listGroup.localToGlobal(tempItem.x, tempItem.y);
        rect1.x = point1.x;
        rect1.y = point1.y;
        rect2.x = point2.x;
        rect2.y = point2.y;
        if (rect1.intersects(rect2)) {
            return obj2;
        }
        else {
            return null;
        }
    };
    return BattleArrayEditView;
}(BaseEuiView));
__reflect(BattleArrayEditView.prototype, "BattleArrayEditView");
/**
 * 英雄item
 */
var HeroArrayItem = (function (_super) {
    __extends(HeroArrayItem, _super);
    function HeroArrayItem(index, rootView, width) {
        var _this = _super.call(this) || this;
        _this.isMove = false;
        _this.oriPoint = new egret.Point(); //玩家原始位置
        _this.skinName = App.ViewManager.getSkin(ViewConst.ArrayItem);
        _this.oriPoint.x = _this.player_image.x;
        _this.oriPoint.y = _this.player_image.y;
        _this.width = width;
        _this.player_image.width = width;
        _this.rootView = rootView;
        _this.rootgroup.touchEnabled = false;
        _this.group_player.touchEnabled = false;
        _this.base_back.touchEnabled = false;
        _this.point_back.touchEnabled = false;
        //this.ConvertIndex(index)
        _this.indexPos = index + 1;
        var backImgName = _this.base_back.source.toString();
        var pndIndex = backImgName.indexOf("_png");
        backImgName = backImgName.substring(0, pndIndex - 1) + _this.indexPos + "_png";
        _this.base_back.source = backImgName;
        _this.label_position.text = _this.indexPos.toString();
        _this.btn_add.removeEventListener(egret.TouchEvent.TOUCH_TAP, _this.OnClickAddBtn, _this);
        _this.btn_add.addEventListener(egret.TouchEvent.TOUCH_TAP, _this.OnClickAddBtn, _this);
        _this.player_image.removeEventListener(egret.TouchEvent.TOUCH_TAP, _this.OnClickAddBtn, _this);
        _this.player_image.addEventListener(egret.TouchEvent.TOUCH_TAP, _this.OnClickAddBtn, _this);
        _this.player_image.removeEventListener(egret.TouchEvent.TOUCH_BEGIN, _this.StartMove, _this);
        _this.player_image.addEventListener(egret.TouchEvent.TOUCH_BEGIN, _this.StartMove, _this);
        _this.player_image.removeEventListener(egret.TouchEvent.TOUCH_END, _this.StopMove, _this);
        _this.player_image.addEventListener(egret.TouchEvent.TOUCH_END, _this.StopMove, _this);
        _this.player_image.removeEventListener(egret.TouchEvent.TOUCH_RELEASE_OUTSIDE, _this.StopMove, _this);
        _this.player_image.addEventListener(egret.TouchEvent.TOUCH_RELEASE_OUTSIDE, _this.StopMove, _this);
        return _this;
    }
    HeroArrayItem.prototype.StartMove = function (e) {
        var pos = this.player_image.localToGlobal(this.player_image.x, this.player_image.y); //转成世界坐标
        this.rootView.addChild(this.player_image);
        //this.rootgroup.removeChild(this.player_image);
        var localPos = this.player_image.globalToLocal(pos.x, pos.y); //世界坐标转本地坐标
        this.player_image.x = localPos.x;
        this.player_image.y = localPos.y;
        this.offsetX = e.stageX - this.player_image.x;
        this.offsetY = e.stageY - this.player_image.y;
        this.player_image.addEventListener(egret.TouchEvent.TOUCH_MOVE, this.OnMove, this);
    };
    HeroArrayItem.prototype.StopMove = function (e) {
        App.EventMgrHelper.PushEventEx(EventDef.CheckCollision, this, this.player_image, 0, 0, "", "");
        this.rootgroup.addChild(this.player_image);
        this.BackInPlace();
        this.player_image.removeEventListener(egret.TouchEvent.TOUCH_MOVE, this.OnMove, this);
    };
    HeroArrayItem.prototype.OnMove = function (e) {
        if (!this.isMove)
            this.isMove = true;
        this.player_image.x = e.stageX - this.offsetX;
        this.player_image.y = e.stageY - this.offsetY;
    };
    //返回
    HeroArrayItem.prototype.BackInPlace = function () {
        this.player_image.x = this.oriPoint.x;
        this.player_image.y = this.oriPoint.y;
    };
    /**
     * 设置出站
     */
    HeroArrayItem.prototype.UpdateInfo = function (info) {
        //this.group_player.visible=true;
        this.image_plus.visible = false;
        this.player_image.visible = true;
        this.SetAction(true);
        if (this.id != info.id) {
            this.id = info.id;
            // this.posInfo=new BattlePosition();
            // let Pos:egret.Point=new egret.Point(0,this.group_player.y*0.5);
            // this.posInfo.InitDisPos(this.indexPos,Pos);
            // if(this.currentObj){
            // 	this.currentObj.Death();
            // 	ObjectPool.push(this.currentObj);
            // 	this.currentObj=null;
            // }
            // this.currentObj = ObjectPool.pop("DemonstrationObject");
            // this.currentObj.init(info.id,this.posInfo,Camp.Friendly,this.group_player,this.rootView);
            var modelConfig = ModelConfig.GetConfig(CreatureTempletConfig.GetConfig(info.id).model);
            if (modelConfig) {
                this.player_image.source = modelConfig.animation;
                this.player_image.x = this.oriPoint.x;
                this.player_image.y = this.oriPoint.y;
            }
        }
    };
    /**
     * 设置未出战
     */
    HeroArrayItem.prototype.SetNoIncrease = function () {
        this.SetAction(true);
        this.group_player.visible = false;
        this.image_plus.visible = true;
        this.player_image.visible = false;
        this.id = 0;
    };
    /**
     * 设置按钮状态
     */
    HeroArrayItem.prototype.SetAddState = function (state) {
        if (this.btn_add && this.btn_add.visible != state) {
            this.btn_add.touchEnabled = state;
            this.btn_add.visible = state;
        }
    };
    /**
     * 添加按钮点击事件
     */
    HeroArrayItem.prototype.OnClickAddBtn = function () {
        if (!this.isMove) {
            App.EventMgrHelper.PushEvent(EventDef.ShowHeroList, this.indexPos);
        }
        else {
            this.isMove = false;
        }
    };
    /**
     * 是否激活
     */
    HeroArrayItem.prototype.SetAction = function (action, level) {
        if (level === void 0) { level = 0; }
        if (action) {
            this.label_lock.visible = false;
            this.image_lock.visible = false;
            this.btn_add.visible = true;
        }
        else {
            this.image_lock.visible = false;
            this.group_player.visible = false;
            this.label_lock.visible = false;
            this.image_plus.visible = false;
            this.btn_add.visible = false;
            this.player_image.visible = false;
        }
    };
    /**
     * 转换为与战斗位置相同的下标
     */
    HeroArrayItem.prototype.ConvertIndex = function (index) {
        switch (index) {
            case 0:
                this.indexPos = 4;
                break;
            case 1:
                this.indexPos = 1;
                break;
            case 2:
                this.indexPos = 5;
                break;
            case 3:
                this.indexPos = 2;
                break;
            case 4:
                this.indexPos = 6;
                break;
            case 5:
                this.indexPos = 3;
                break;
        }
    };
    Object.defineProperty(HeroArrayItem.prototype, "Base_back", {
        get: function () { return this.base_back; },
        enumerable: true,
        configurable: true
    });
    return HeroArrayItem;
}(eui.Component));
__reflect(HeroArrayItem.prototype, "HeroArrayItem");
//# sourceMappingURL=BattleArrayEditView.js.map