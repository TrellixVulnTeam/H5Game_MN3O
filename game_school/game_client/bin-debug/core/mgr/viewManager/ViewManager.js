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
var ViewManager = (function (_super) {
    __extends(ViewManager, _super);
    /**
     * 构造函数
     */
    function ViewManager() {
        var _this = _super.call(this) || this;
        _this._views = {};
        _this._opens = [];
        _this._needPreload = [];
        _this._enterFBClose = [];
        _this._freeResClose = [];
        _this._changeSceneClose = [];
        return _this;
    }
    /**
     * 清空处理
     */
    ViewManager.prototype.clear = function () {
        this.closeAll();
        this._views = {};
    };
    /**
     * 面板注册
     * @param key 面板唯一标识
     * @param view 面板
     */
    ViewManager.prototype.register = function (key, view) {
        if (view == null) {
            return;
        }
        if (this._views[key]) {
            return;
        }
        view.register(key);
        this._views[key] = view;
        this.inintViewParent(view);
        //this.initNeedPreloadUI(key);
        this.initFreeResCloseUI(key);
        this.initEnterFBCloseUI(key);
        this.initChangeSceneCloseUI(key);
    };
    /**
     * 面板解除注册
     * @param key
     */
    ViewManager.prototype.unregister = function (key) {
        if (!this._views[key]) {
            return;
        }
        this._views[key] = null;
        delete this._views[key];
    };
    /**
     * 销毁一个面板
     * @param key 唯一标识
     * @param newView 新面板
     */
    ViewManager.prototype.destroy = function (key, newView) {
        if (newView === void 0) { newView = null; }
        var oldView = this.getView(key);
        if (oldView) {
            this.unregister(key);
            oldView.destroy();
            oldView = null;
        }
        this.register(key, newView);
    };
    /**
     * 开启面板
     * @param key 面板唯一标识
     * @param param 参数
     *
     */
    ViewManager.prototype.open = function (key) {
        var param = [];
        for (var _i = 1; _i < arguments.length; _i++) {
            param[_i - 1] = arguments[_i];
        }
        var view = this.getView(key);
        if (view == null) {
            Log.Error("UI_" + key + "不存在");
            return;
        }
        if (view.isShow()) {
            view.open.apply(view, param);
            return view;
        }
        if (view.isInit()) {
            view.addToParent();
            view.open.apply(view, param);
        }
        else if (key == ViewConst.Loading) {
            if (view.isPreload()) {
                this.setViewOpen(view, param);
            }
            else {
                this.setViewLoading(view, ["ui_loading"], param);
            }
        }
        else {
            var config = GuiConfig.GetConfig(key);
            if (config == null) {
                Log.Error("GuiConfig " + key + " error");
                return;
            }
            else if (config.ReadyToLoad == false || view.isPreload()) {
                this.setViewOpen(view, param);
            }
            else if (config.readyLoadGroup == null) {
                Log.Error("GuiConfig " + key + "'s readyLoadGroup is null");
                return;
            }
            else if (config.readyLoadGroup.length <= 0) {
                Log.Error("ui " + key + "'s readyLoadGroup is empty");
                return;
            }
            else {
                this.setViewLoading(view, config.readyLoadGroup, param);
            }
        }
        this.openUIPlaySound(key);
        this._opens.push(key);
        this.setOpenDepth();
        return view;
    };
    ViewManager.prototype.setViewOpen = function (view) {
        var param = [];
        for (var _i = 1; _i < arguments.length; _i++) {
            param[_i - 1] = arguments[_i];
        }
        view.initUI();
        view.initData();
        view.addToParent();
        view.open.apply(view, param);
        view.setVisible(true);
    };
    ViewManager.prototype.setViewLoading = function (view, resources) {
        var param = [];
        for (var _i = 2; _i < arguments.length; _i++) {
            param[_i - 2] = arguments[_i];
        }
        view.setResources(resources);
        App.EasyLoading.showLoading();
        view.loadResource(function () {
            view.preloadTrue(true);
            this.setViewOpen(view, param);
            App.EasyLoading.hideLoading();
        }.bind(this), null);
    };
    /**
     * 初始化view父级
    */
    ViewManager.prototype.inintViewParent = function (view) {
        if (this._viewParent == null) {
            if (view instanceof BaseEuiView) {
                this._viewParent = view.myParent;
            }
        }
    };
    /**
     * 设置正在打开界面的深度
    */
    ViewManager.prototype.setOpenDepth = function () {
        if (this._viewParent == null) {
            return;
        }
        if (this._opens.length <= 1) {
            return;
        }
        var config = null;
        var configNext = null;
        var view1 = null;
        var view2 = null;
        for (var index = 0; index < this._opens.length; index++) {
            for (var indexNext = index + 1; indexNext < this._opens.length; indexNext++) {
                config = GuiConfig.GetConfig(this._opens[index]);
                configNext = GuiConfig.GetConfig(this._opens[indexNext]);
                if (config != null && configNext != null) {
                    if (config.PosZ > configNext.PosZ) {
                        view1 = this.getView(this._opens[index]);
                        view2 = this.getView(this._opens[indexNext]);
                        if (view1 != null && view2 != null) {
                            var depth1 = this._viewParent.getChildIndex(view1);
                            var depth2 = this._viewParent.getChildIndex(view2);
                            if (depth1 != -1 && depth2 != -1 && depth1 < depth2) {
                                this._viewParent.swapChildren(view1, view2);
                            }
                        }
                    }
                }
            }
        }
    };
    /**
     * 置顶界面（界面在打开中才可以置顶）
    */
    ViewManager.prototype.topView = function (key) {
        var view = this.getView(key);
        if (view == null) {
            Log.Error("UI_" + key + "不存在");
            return;
        }
        if (!view.isShow()) {
            Log.Error("请先打开" + "UI_" + key);
            return;
        }
        var bool = view instanceof BaseEuiView;
        if (bool) {
            var maxDepth = this._viewParent.numChildren;
            this._viewParent.setChildIndex(view, maxDepth);
        }
        else {
            Log.Error("view type error");
        }
    };
    /**
     * 关闭面板
     * @param key 面板唯一标识
     * @param param 参数
     *
     */
    ViewManager.prototype.close = function (key) {
        var param = [];
        for (var _i = 1; _i < arguments.length; _i++) {
            param[_i - 1] = arguments[_i];
        }
        if (!this.isShow(key)) {
            return;
        }
        var view = this.getView(key);
        if (view == null) {
            return;
        }
        var viewIndex = this._opens.indexOf(key);
        if (key >= 0) {
            this._opens.splice(viewIndex, 1);
        }
        if (this.isFreeResCloseUI(key)) {
            view.freeResources();
        }
        this.closeUIPlaySound(key);
        view.removeFromParent();
        view.close.apply(view, param);
    };
    /**
     * 关闭面板
     * @param view
     * @param param
     */
    ViewManager.prototype.closeView = function (view) {
        var param = [];
        for (var _i = 1; _i < arguments.length; _i++) {
            param[_i - 1] = arguments[_i];
        }
        var keys = Object.keys(this._views);
        for (var i = 0, len = keys.length; i < len; i++) {
            var key = parseInt(keys[i]);
            if (this._views[key] == view) {
                this.close(key, param);
                return;
            }
        }
    };
    /**
     * 根据唯一标识获取一个UI对象
     * @param key
     * @returns {any}
     */
    ViewManager.prototype.getView = function (key) {
        return this._views[key];
    };
    /**
     * 关闭所有开启中的UI
     */
    ViewManager.prototype.closeAll = function () {
        while (this._opens.length) {
            this.close(this._opens[0]);
        }
    };
    /**
     * 当前ui打开数量
     * @returns {number}
     */
    ViewManager.prototype.currOpenNum = function () {
        return this._opens.length;
    };
    /**
     * 检测一个UI是否开启中
     * @param key
     * @returns {boolean}
     */
    ViewManager.prototype.isShow = function (key) {
        return this._opens.indexOf(key) != -1;
    };
    /**
     * 获取皮肤（界面在initUI方法里设置皮肤）
     */
    ViewManager.prototype.getSkin = function (skinId) {
        var config = GuiConfig.GetConfig(skinId);
        if (config != null) {
            return "resource/skins/" + config.ResName;
        }
        else {
            console.log("GuiConfig" + skinId + "error");
            return;
        }
    };
    /**
     * 角色死亡关闭界面
    */
    ViewManager.prototype.heroDeathCloseUI = function () {
        var config = null;
        var closeUI = new Array();
        for (var index = 0; index < this._opens.length; index++) {
            config = GuiConfig.GetConfig(this._opens[index]);
            if (config != null && config.EscClose) {
                closeUI.push(this._opens[index]);
            }
        }
        for (var index = 0; index < closeUI.length; index++) {
            this.close(closeUI[index]);
        }
    };
    /**
     * 关闭互斥界面
    */
    ViewManager.prototype.closeExclusionUI = function (key) {
        var config = GuiConfig.GetConfig(key);
        if (config == null) {
            return;
        }
        for (var index = 0; index < config.exclusion.length; index++) {
            this.close(config.exclusion[index]);
        }
    };
    /**
     * 初始化切换场景关闭界面数据
    */
    ViewManager.prototype.initChangeSceneCloseUI = function (key) {
        var config = GuiConfig.GetConfig(key);
        if (config != null && config.switchSceneIsClose) {
            this._changeSceneClose.push(key);
        }
    };
    /**
     * 切换场景需要关闭的界面
    */
    ViewManager.prototype.closeChangeSceneUI = function () {
        if (this._changeSceneClose == null) {
            return;
        }
        for (var index = 0; index < this._changeSceneClose.length; index++) {
            this.close(this._changeSceneClose[index]);
        }
    };
    /**
     * 初始化进入副本需要关闭的界面数据
    */
    ViewManager.prototype.initEnterFBCloseUI = function (key) {
        var config = GuiConfig.GetConfig(key);
        if (config != null && config.dungeonHide) {
            this._enterFBClose.push(key);
        }
    };
    /**
     * 进入副本需要关闭的界面
    */
    ViewManager.prototype.closeEnterFBUI = function () {
        if (this._enterFBClose == null) {
            return;
        }
        for (var index = 0; index < this._enterFBClose.length; index++) {
            this.close(this._enterFBClose[index]);
        }
    };
    /**
     * 初始化关闭时需要释放资源的界面数据
    */
    ViewManager.prototype.initFreeResCloseUI = function (key) {
        var config = GuiConfig.GetConfig(key);
        if (config != null && config.needFreeRes) {
            this._freeResClose.push(key);
        }
    };
    /**
     * 关闭界面时释放资源
    */
    ViewManager.prototype.isFreeResCloseUI = function (key) {
        if (this._freeResClose == null) {
            return false;
        }
        for (var index = 0; index < this._freeResClose.length; index++) {
            if (this._freeResClose[index] == key) {
                return true;
            }
        }
        return false;
    };
    /**
     * 需要预加载的界面数据
    */
    ViewManager.prototype.initNeedPreloadUI = function (key) {
        var config = GuiConfig.GetConfig(key);
        if (config != null && config.ReadyToLoad) {
            this._needPreload.push(key);
        }
    };
    /**
     * 加载登陆预加载
    */
    ViewManager.prototype.onLoadingPreloadUI = function (callback) {
        var view = this.getView(ViewConst.Loading);
        if (view == null) {
            Log.Error("加载界面不存在");
            return;
        }
        else {
            view.setResources(["ui_loading"]);
            App.EasyLoading.showLoading();
            view.loadResource(function () {
                view.setVisible(false);
                view.preloadTrue(true);
                App.EasyLoading.hideLoading();
                if (callback != null) {
                    callback();
                }
            }.bind(this), function () {
                view.setVisible(false);
            }.bind(this));
        }
    };
    /**
     * 加载需要预加载的界面(GuiConfig ReadyToLoad == true 需要预加载)
    */
    ViewManager.prototype.onLoadNeedPreloadUI = function () {
        if (this._needPreload == null) {
            return;
        }
        for (var index = 0; index < this._needPreload.length; index++) {
            var config = GuiConfig.GetConfig(this._needPreload[index]);
            if (config == null) {
                Log.Error("GuiConfig " + this._needPreload[index] + " error");
                continue;
            }
            else if (config.readyLoadGroup == null) {
                Log.Error("GuiConfig " + this._needPreload[index] + "'s readyLoadGroup is null");
                return;
            }
            else if (config.readyLoadGroup.length <= 0) {
                Log.Error("ui " + this._needPreload[index] + "'s readyLoadGroup is empty");
                return;
            }
            var view = this.getView(this._needPreload[index]);
            if (view == null) {
                Log.Error("UI_" + this._needPreload[index] + "不存在");
                continue;
            }
            else if (view.isShow()) {
                Log.Error("UI_" + this._needPreload[index] + "在显示中");
                continue;
            }
            else if (view.isInit()) {
                Log.Error("UI_" + this._needPreload[index] + "is already init");
                continue;
            }
            else if (view.isPreload()) {
                Log.Error("UI_" + this._needPreload[index] + "is already preload");
                continue;
            }
            else {
                view.setResources(config.readyLoadGroup);
                view.loadResource(function () {
                    view.setVisible(false);
                    view.preloadTrue(true);
                }.bind(this), function () {
                    view.setVisible(false);
                }.bind(this));
            }
        }
    };
    /**
     * 打开界面时播放音乐
    */
    ViewManager.prototype.openUIPlaySound = function (key) {
        var config = GuiConfig.GetConfig(key);
        if (config != null && config.AudioOfOpen != "") {
            App.SoundManager.playEffect(config.AudioOfOpen);
        }
    };
    /**
     * 关闭界面时播放音乐
    */
    ViewManager.prototype.closeUIPlaySound = function (key) {
        var config = GuiConfig.GetConfig(key);
        if (config != null && config.AudioOfClose != "") {
            App.SoundManager.playEffect(config.AudioOfClose);
        }
    };
    return ViewManager;
}(BaseClass));
__reflect(ViewManager.prototype, "ViewManager");
//# sourceMappingURL=ViewManager.js.map