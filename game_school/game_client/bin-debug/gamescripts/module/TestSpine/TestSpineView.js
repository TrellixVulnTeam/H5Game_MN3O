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
var TestSpineView = (function (_super) {
    __extends(TestSpineView, _super);
    function TestSpineView($controller, $parent) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this.btnArray = [];
        /**骨骼角色拥有的动作列表**/
        _this.actionArray = ["attack", "dead", "hit01", "hit02", "hit03", "hit04", "idle", "run", "skill", "win"];
        _this.mDragSkeletonNames = [];
        return _this;
    }
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    TestSpineView.prototype.initUI = function () {
        var _this = this;
        _super.prototype.initUI.call(this);
        this.skinName = "resource/skins/text.exml";
        this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, function () {
            _this.onClose();
            App.ViewManager.open(ViewConst.MainUI);
        }, this);
        //遍历找到所有单选按钮
        for (var i = 0; i < this.group_btn.$children.length; i++) {
            var btn = this.group_btn.getChildAt(i);
            btn.label = this.actionArray[i];
            //btn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onBtnClick, this)
            this.btnArray.push(btn);
        }
        this.updataBtn();
        this.createMotorcycleExp();
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    TestSpineView.prototype.initData = function () {
        _super.prototype.initData.call(this);
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    TestSpineView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.open.call(this, param);
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    TestSpineView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
        _super.prototype.close.call(this, param);
    };
    /**创建骨骼模型**/
    TestSpineView.prototype.createMotorcycleExp = function () {
        var arr = ["role002"];
        for (var i = 0, len = arr.length; i < len; i++) {
            var dbName = arr[i];
            var str = dbName + "_ske_json";
            var skeletonData = RES.getRes(str);
            console.log(str);
            if (skeletonData == null)
                continue;
            for (var j = 0; j < skeletonData.armature.length; j++) {
                this.mDragSkeletonNames.push(skeletonData.armature[0].name);
            }
            var texturePng = RES.getRes(dbName + "_tex_png");
            var textureData = RES.getRes(dbName + "_tex_json");
            App.DragonBonesFactory.initArmatureFile(skeletonData, texturePng, textureData);
        }
        this.mDrag = ObjectPool.pop("DragonObjectTest");
        this.mDrag.init("buhuo_zhifu", "", this.actionArray);
        this.mDrag.armature.x = 250;
        this.mDrag.armature.y = 1250;
        this.mDrag.armature.touchEnabled = true;
        //this.mDrag.armature.$addListener(egret.TouchEvent.TOUCH_BEGIN, this.ArmatureClick, this);
        this.mDrag.armature.scaleX = 2;
        this.mDrag.armature.scaleY = 2;
        this.mDrag.createArmature(this.mDragSkeletonNames[0], this.actionArray);
        this.mDrag.armature.play(this.actionArray[0], 0);
        this.addChild(this.mDrag);
    };
    TestSpineView.prototype.ArmatureClick = function () {
        this.mDrag.armature.clear();
        var name = App.RandomUtils.randomArray(this.mDragSkeletonNames);
        var act = App.RandomUtils.randomArray(this.actionArray);
        this.mDrag.createArmature(name, this.actionArray);
        this.mDrag.armature.play(act, 0);
    };
    TestSpineView.prototype.onBtnClick = function (str) {
        this.mDrag.armature.play(str, 0);
    };
    TestSpineView.prototype.updataBtn = function () {
        for (var i = 0; i < this.btnArray.length; i++) {
            var btn = new TestBtnItem();
            btn.init(this.btnArray[i], this);
        }
    };
    return TestSpineView;
}(BaseEuiView));
__reflect(TestSpineView.prototype, "TestSpineView");
var TestBtnItem = (function () {
    function TestBtnItem() {
    }
    TestBtnItem.prototype.init = function (btn, view) {
        if (btn == null || view == null) {
            return;
        }
        this.btn = btn;
        this.mHandView = view;
        this.con = btn.label;
        this.btn.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
    };
    TestBtnItem.prototype.onClick = function () {
        this.mHandView.onBtnClick(this.con);
    };
    return TestBtnItem;
}());
__reflect(TestBtnItem.prototype, "TestBtnItem");
//# sourceMappingURL=TestSpineView.js.map