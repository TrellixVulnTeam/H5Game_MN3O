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
var RoleType;
(function (RoleType) {
    RoleType[RoleType["Role_A"] = 0] = "Role_A";
    RoleType[RoleType["Role_B"] = 1] = "Role_B";
})(RoleType || (RoleType = {}));
/**
 * 创建角色
 */
var CreatureRoleUIView = (function (_super) {
    __extends(CreatureRoleUIView, _super);
    function CreatureRoleUIView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.btnGroup = new eui.RadioButtonGroup(); //role type 按钮组//
        _this.symbolStrs = [" ", "@"];
        _this.isFirstGuide = false;
        _this.addEventListener(eui.UIEvent.COMPLETE, _this.uiCompHandler, _this);
        return _this;
    }
    CreatureRoleUIView.prototype.initUI = function () {
        _super.prototype.initUI.call(this);
        this.skinName = App.ViewManager.getSkin(ViewConst.CreatureRoleUI);
        this.isFirstGuide = App.GuideManager.getIsGuide;
    };
    CreatureRoleUIView.prototype.uiCompHandler = function () {
        this.onSetBtnGroup();
        this.create_btn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onCreatureRole, this);
        this.btn_suiji.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onRandomRoleName, this);
        this.role_name.text = StrConfigManager.getStrById(1003);
        this.role_name.addEventListener(egret.TouchEvent.FOCUS_IN, this.onSetRolename, this);
        this.role_name.addEventListener(egret.TouchEvent.FOCUS_OUT, this.offSetRolename, this);
        this.role_name.addEventListener(egret.TouchEvent.CHANGE, this.onChangeRolename, this);
    };
    /**
     * 创建角色
    */
    CreatureRoleUIView.prototype.onCreatureRole = function () {
        if (this.role_name.text == "") {
            App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, StrConfigManager.getStrById(1006));
        }
        else {
            if (this.isFirstGuide) {
                this.addFirstGuide(); //剧情
            }
            else {
                App.ViewManager.open(ViewConst.MainUI);
            }
        }
    };
    /**
     * 临时指引1（选择学渣或学霸 播放相应的剧情 然后打开主界面）
    */
    CreatureRoleUIView.prototype.addFirstGuide = function () {
        if (this.curRoleType == RoleType.Role_A) {
            App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 101, function () {
                App.ViewManager.close(ViewConst.Dialog);
                App.ViewManager.open(ViewConst.MainUI);
            }.bind(this), 0, 0, "", "");
            // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 101, function () {
            //     App.ViewManager.close(ViewConst.Dialog);
            //     App.ViewManager.open(ViewConst.MainUI);
            // });
        }
        else {
            App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, 102, function () {
                App.ViewManager.close(ViewConst.Dialog);
                App.ViewManager.open(ViewConst.MainUI);
            }.bind(this), 0, 0, "", "");
            // App.ControllerManager.applyFunc(ControllerConst.Dialog, DialogConst.PLAYPLOTGROUP_C2C, 102, function () {
            //     App.ViewManager.close(ViewConst.Dialog);
            //     App.ViewManager.open(ViewConst.MainUI);
            // });
        }
    };
    /**
     * 随机名字
    */
    CreatureRoleUIView.prototype.onRandomRoleName = function () {
        this.role_name.text = RandomNameManager.getRoleName();
    };
    CreatureRoleUIView.prototype.onSetRolename = function () {
        this.role_name.text = "";
    };
    CreatureRoleUIView.prototype.offSetRolename = function () {
        if (this.role_name.text == "") {
            this.role_name.text = StrConfigManager.getStrById(1003);
        }
    };
    CreatureRoleUIView.prototype.onChangeRolename = function (ev) {
        if (this.iSRegularName(ev.target.text)) {
            this.role_name.text = ev.target.text;
        }
        else {
            this.role_name.text = StrConfigManager.getStrById(1003);
        }
    };
    CreatureRoleUIView.prototype.iSRegularName = function (name) {
        var flag = true;
        for (var index = 0; index < FilterNameConfig.array.length; index++) {
            var str = "/*" + FilterNameConfig.array[index].str + "/*";
            var pattern = new RegExp(str);
            if (pattern.exec(name)) {
                flag = false;
                App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, StrConfigManager.getStrById(1005));
                break;
            }
        }
        for (var index = 0; index < this.symbolStrs.length; index++) {
            var str = "/*" + this.symbolStrs[index] + "/*";
            var pattern = new RegExp(str);
            if (pattern.exec(name)) {
                flag = false;
                App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, "不合理字符");
                break;
            }
        }
        if (flag && name.length > RandomNameManager.MAX_Length) {
            flag = false;
            App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, StrConfigManager.getStrById(1004));
        }
        return flag;
    };
    CreatureRoleUIView.prototype.onSetBtnGroup = function () {
        this.btnGroup.addEventListener(eui.UIEvent.CHANGE, this.selectRoleTypeHandler, this);
        this.btn_A.value = RoleType.Role_A;
        this.btn_B.value = RoleType.Role_B;
        this.btn_A.group = this.btnGroup;
        this.btn_B.group = this.btnGroup;
    };
    CreatureRoleUIView.prototype.selectRoleTypeHandler = function (evt) {
        this.btnGroup = evt.target;
        this.selectedRoleType(this.btnGroup.selectedValue);
    };
    CreatureRoleUIView.prototype.selectedRoleType = function (type) {
        this.curRoleType = type;
        if (this.curRoleType == RoleType.Role_B) {
            this.group_a.visible = true;
            this.group_b.visible = false;
        }
        else {
            this.group_a.visible = false;
            this.group_b.visible = true;
        }
    };
    CreatureRoleUIView.prototype.initData = function () {
        _super.prototype.initData.call(this);
        var data = RES.getRes("ui_load_effect1_json");
        var txtr = RES.getRes("ui_load_effect1_png");
        var mcFactory = new egret.MovieClipDataFactory(data, txtr);
        var mc_water = new egret.MovieClip(mcFactory.generateMovieClipData("ui_load_effect1"));
        mc_water.gotoAndPlay("water_2", -1);
        this.group_water.addChild(mc_water);
        var mc_x = new egret.MovieClip(mcFactory.generateMovieClipData("ui_load_effect1"));
        mc_x.gotoAndPlay("xiong_2", -1);
        this.group_xiong.addChild(mc_x);
        data = RES.getRes("ui_load_effect2_json");
        txtr = RES.getRes("ui_load_effect2_png");
        mcFactory = new egret.MovieClipDataFactory(data, txtr);
        var mc_piao = new egret.MovieClip(mcFactory.generateMovieClipData("ui_load_effect2"));
        mc_piao.gotoAndPlay("piao_2", -1);
        this.group_piao.addChild(mc_piao);
    };
    CreatureRoleUIView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
        this.star.play(0);
        this.selectDefaultRole();
    };
    /**
     * 默认选择
    */
    CreatureRoleUIView.prototype.selectDefaultRole = function () {
        this.btn_A.selected = true;
        this.selectedRoleType(RoleType.Role_A);
    };
    return CreatureRoleUIView;
}(BaseEuiView));
__reflect(CreatureRoleUIView.prototype, "CreatureRoleUIView");
//# sourceMappingURL=CreatureRoleUIView.js.map