enum RoleType {
    Role_A,//学渣
    Role_B,//学霸
}

/**
 * 创建角色
 */
class CreatureRoleUIView extends BaseEuiView {
    private group_a: eui.Group;
    private group_water: eui.Group;
    private group_xiong: eui.Group;

    private group_b: eui.Group;
    private group_piao: eui.Group;


    private role_name: eui.EditableText;
    private btn_suiji: eui.Button;
    private create_btn: eui.Button;

    private btn_A: eui.RadioButton;
    private btn_B: eui.RadioButton;
    private btnGroup: eui.RadioButtonGroup = new eui.RadioButtonGroup();//role type 按钮组//
    private star: egret.tween.TweenGroup;

    private symbolStrs: string[] = [" ", "@"];

    private curRoleType: RoleType;

    private isFirstGuide = false;

    public constructor($controller: BaseController, $parent: eui.Group) {
        super($controller, $parent);
        this.addEventListener(eui.UIEvent.COMPLETE, this.uiCompHandler, this)
    }

    public initUI(): void {
        super.initUI();

        this.skinName = App.ViewManager.getSkin(ViewConst.CreatureRoleUI);

        this.isFirstGuide = App.GuideManager.getIsGuide;
    }

    private uiCompHandler(): void {
        this.onSetBtnGroup();
        this.create_btn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onCreatureRole, this);
        this.btn_suiji.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onRandomRoleName, this);

        this.role_name.text = StrConfigManager.getStrById(1003);
        this.role_name.addEventListener(egret.TouchEvent.FOCUS_IN, this.onSetRolename, this);
        this.role_name.addEventListener(egret.TouchEvent.FOCUS_OUT, this.offSetRolename, this);
        this.role_name.addEventListener(egret.TouchEvent.CHANGE, this.onChangeRolename, this);
    }

    /**
     * 创建角色
    */
    private onCreatureRole(): void {
        if (/*this.role_name.text == StrConfigManager.getStrById(1003) ||*/ this.role_name.text == "") 
        {
             App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, StrConfigManager.getStrById(1006));
        }
        else 
        {
            if (this.isFirstGuide) 
            {
                this.addFirstGuide();//剧情
            }
            else 
            {
                App.ViewManager.open(ViewConst.MainUI);
            }
        }
    }

    /**
     * 临时指引1（选择学渣或学霸 播放相应的剧情 然后打开主界面）
    */
    public addFirstGuide() {
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
    }

    /**
     * 随机名字
    */
    private onRandomRoleName(): void {
        this.role_name.text = RandomNameManager.getRoleName();
    }

    private onSetRolename(): void {
        this.role_name.text = "";
    }

    private offSetRolename(): void {
        if (this.role_name.text == "") {
            this.role_name.text = StrConfigManager.getStrById(1003);
        }
    }

    private onChangeRolename(ev: egret.Event): void {
        if (this.iSRegularName(ev.target.text)) {
            this.role_name.text = ev.target.text;
        }
        else {
            this.role_name.text = StrConfigManager.getStrById(1003);
        }
    }

    private iSRegularName(name: string): boolean {
        let flag = true;
        for (let index = 0; index < FilterNameConfig.array.length; index++) {
            let str = "/*" + FilterNameConfig.array[index].str + "/*";
            let pattern = new RegExp(str);
            if (pattern.exec(name)) {
                flag = false;
                App.EventMgrHelper.PushEvent(EventDef.Setdrift_world, -1, -1, StrConfigManager.getStrById(1005));
                break;
            }
        }

        for (let index = 0; index < this.symbolStrs.length; index++) {
            let str = "/*" + this.symbolStrs[index] + "/*";
            let pattern = new RegExp(str);
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
    }

    private onSetBtnGroup(): void {
        this.btnGroup.addEventListener(eui.UIEvent.CHANGE, this.selectRoleTypeHandler, this);
        this.btn_A.value = RoleType.Role_A;
        this.btn_B.value = RoleType.Role_B;

        this.btn_A.group = this.btnGroup;
        this.btn_B.group = this.btnGroup;
    }

    private selectRoleTypeHandler(evt: eui.UIEvent): void {
        this.btnGroup = evt.target;
        this.selectedRoleType(this.btnGroup.selectedValue);
    }

    private selectedRoleType(type: RoleType): void {
        this.curRoleType = type;
        if (this.curRoleType == RoleType.Role_B) {
            this.group_a.visible = true;
            this.group_b.visible = false;
        }
        else {
            this.group_a.visible = false;
            this.group_b.visible = true;
        }
    }

    public initData(): void {
        super.initData();

        var data = RES.getRes("ui_load_effect1_json");
        var txtr = RES.getRes("ui_load_effect1_png");
        var mcFactory: egret.MovieClipDataFactory = new egret.MovieClipDataFactory(data, txtr);
        let mc_water = new egret.MovieClip(mcFactory.generateMovieClipData("ui_load_effect1"));
        mc_water.gotoAndPlay("water_2", -1);
        this.group_water.addChild(mc_water);

        let mc_x = new egret.MovieClip(mcFactory.generateMovieClipData("ui_load_effect1"));
        mc_x.gotoAndPlay("xiong_2", -1);
        this.group_xiong.addChild(mc_x);

        data = RES.getRes("ui_load_effect2_json");
        txtr = RES.getRes("ui_load_effect2_png");
        mcFactory = new egret.MovieClipDataFactory(data, txtr);
        let mc_piao = new egret.MovieClip(mcFactory.generateMovieClipData("ui_load_effect2"));
        mc_piao.gotoAndPlay("piao_2", -1);
        this.group_piao.addChild(mc_piao);
    }

    public open(...param: any[]): void {
        super.open(param);
        this.star.play(0);
        this.selectDefaultRole();
    }

    /**
     * 默认选择
    */
    private selectDefaultRole(): void {
        this.btn_A.selected = true;
        this.selectedRoleType(RoleType.Role_A);
    }
}