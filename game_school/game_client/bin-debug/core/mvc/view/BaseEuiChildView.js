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
 * ViewChild基类
 */
var BaseEuiChildView = (function (_super) {
    __extends(BaseEuiChildView, _super);
    /**
     * 构造函数
     * @param $controller 所属模块
     * @param $parent 父级
     */
    function BaseEuiChildView($controller, $parent, key) {
        var _this = _super.call(this, $controller, $parent) || this;
        _this._controller = $controller;
        _this._myParent = $parent;
        _this._key = key;
        _this._isInit = false;
        _this._isPreload = false;
        _this.percentHeight = 100;
        _this.percentWidth = 100;
        return _this;
    }
    Object.defineProperty(BaseEuiChildView.prototype, "myParent", {
        /**
         * 获取我的父级
         * @returns {egret.DisplayObjectContainer}
         */
        get: function () {
            return this._myParent;
        },
        enumerable: true,
        configurable: true
    });
    /**
     * 设置初始加载资源
     * @param resources
     */
    BaseEuiChildView.prototype.setResources = function (resources) {
        this._resources = resources;
    };
    /**
     * Child EUI View key
    */
    BaseEuiChildView.prototype.register = function (key) {
        this._key = key;
    };
    /**
     * 是否已经初始化
     * @returns {boolean}
     */
    BaseEuiChildView.prototype.isInit = function () {
        return this._isInit;
    };
    /**
     * 触发本模块消息
     * @param key 唯一标识
     * @param param 参数
     *
     */
    BaseEuiChildView.prototype.applyFunc = function (key) {
        var param = [];
        for (var _i = 1; _i < arguments.length; _i++) {
            param[_i - 1] = arguments[_i];
        }
        return this._controller.applyFunc.apply(this._controller, arguments);
    };
    /**
     * 触发其他模块消息
     * @param controllerKey 模块标识
     * @param key 唯一标识
     * @param param 所需参数
     *
     */
    BaseEuiChildView.prototype.applyControllerFunc = function (controllerKey, key) {
        var param = [];
        for (var _i = 2; _i < arguments.length; _i++) {
            param[_i - 2] = arguments[_i];
        }
        return this._controller.applyControllerFunc.apply(this._controller, arguments);
    };
    /**
     * 面板是否显示
     * @return
     *
     */
    BaseEuiChildView.prototype.isShow = function () {
        return this.stage != null && this.visible;
    };
    /**
     * 添加到父级
     */
    BaseEuiChildView.prototype.addToParent = function () {
        this._myParent.addChild(this);
    };
    /**
     * 从父级移除
     */
    BaseEuiChildView.prototype.removeFromParent = function () {
        App.DisplayUtils.removeFromParent(this);
    };
    /**
     *对面板进行显示初始化，用于子类继承
     *
     */
    BaseEuiChildView.prototype.initUI = function () {
        this._isInit = true;
    };
    /**
     *对面板数据的初始化，用于子类继承
     *
     */
    BaseEuiChildView.prototype.initData = function () {
    };
    /**
     * 销毁
     */
    BaseEuiChildView.prototype.destroy = function () {
        this._controller = null;
        this._myParent = null;
        this._resources = null;
        this._isPreload = false;
    };
    /**
     * 面板开启执行函数，用于子类继承
     * @param param 参数
     */
    BaseEuiChildView.prototype.open = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
    };
    /**
     * 面板关闭执行函数，用于子类继承
     * @param param 参数
     */
    BaseEuiChildView.prototype.close = function () {
        var param = [];
        for (var _i = 0; _i < arguments.length; _i++) {
            param[_i] = arguments[_i];
        }
    };
    /**
     * 关闭自身面板
     */
    BaseEuiChildView.prototype.onClose = function () {
        App.ViewManager.close(this._key);
    };
    /**
     * 是否已经预加载资源
     * @returns {boolean}
     */
    BaseEuiChildView.prototype.isPreload = function () {
        return this._isPreload;
    };
    /**
     * 是否已经预加载资源
     *  @param value
     */
    BaseEuiChildView.prototype.preloadTrue = function (value) {
        this._isPreload = value;
    };
    /**
     /**
     * 加载面板所需资源
     */
    BaseEuiChildView.prototype.loadResource = function (loadComplete, initComplete) {
        if (initComplete === void 0) { initComplete = null; }
        if (this._resources && this._resources.length > 0) {
            App.ResourceUtils.loadResource(this._resources, [], loadComplete, null, this);
            // this.once(eui.UIEvent.CREATION_COMPLETE, initComplete, this);
        }
        else {
            loadComplete();
            if (initComplete != null) {
                initComplete();
            }
        }
    };
    /**
     * 设置是否隐藏
     * @param value
     */
    BaseEuiChildView.prototype.setVisible = function (value) {
        this.visible = value;
    };
    /**
    * 释放资源
    */
    BaseEuiChildView.prototype.freeResources = function () {
        for (var index = 0; index < this._resources.length; index++) {
            RES.destroyRes(this._resources[index]);
        }
        this._isPreload = false;
    };
    /**
     * 打开子页签
     */
    BaseEuiChildView.prototype.onChildGroupShow = function () {
    };
    /**
    * 关闭子页签
    */
    BaseEuiChildView.prototype.onChildGroupHide = function () {
    };
    return BaseEuiChildView;
}(BaseEuiView));
__reflect(BaseEuiChildView.prototype, "BaseEuiChildView");
//# sourceMappingURL=BaseEuiChildView.js.map