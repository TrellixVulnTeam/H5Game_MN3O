var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var MovieClipComponentBase = (function () {
    function MovieClipComponentBase() {
        this.mMovieClipEvent = {};
        this.mEventListenerList = {};
        this.isRuning = false;
    }
    MovieClipComponentBase.prototype.Init = function (gameResGroupName, mcpath, mcname, entity, scale) {
        if (scale === void 0) { scale = 1; }
        this.gameResGroupName = gameResGroupName;
        this.mcPath = mcpath;
        this.mcName = mcname;
        this.mEntity = entity;
        this.scaleOffset = scale;
    };
    Object.defineProperty(MovieClipComponentBase.prototype, "MovieClip", {
        get: function () {
            return this.mc;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(MovieClipComponentBase.prototype, "Body", {
        get: function () {
            return this.body;
        },
        enumerable: true,
        configurable: true
    });
    Object.defineProperty(MovieClipComponentBase.prototype, "Entity", {
        get: function () {
            return this.mEntity;
        },
        enumerable: true,
        configurable: true
    });
    MovieClipComponentBase.prototype.RemoveChild = function () {
        if (this.mEntity)
            this.mEntity.gameView.removeChild(this.body);
    };
    MovieClipComponentBase.prototype.start = function (_body) {
        if (_body === void 0) { _body = null; }
        this.isRuning = true;
        this.mc = ObjectPool.pop("MovieClip");
        //this.mc.setDefault("avatarDefault_png");
        this.mc.setComplateAction(this.complateAction, this);
        if (_body == null) {
            this.body = ObjectPool.pop("egret.DisplayObjectContainer");
            this.body.$touchEnabled = true;
            this.body.addChild(this.mc);
        }
        else {
            this.body = _body;
        }
        this.body.scaleX = this.scaleOffset;
        this.body.scaleY = this.scaleOffset;
        if (this.mEntity != null) {
            this.mEntity.gameView.addChild(this.body);
        }
        if (this.mcName.search("_avatar") != -1) {
            RES.getResAsync(this.mcName + "_json", this.MCJsonLoadSuccess, this);
        }
        else {
            var res = RES.getRes(this.mcName + "_json");
            if (res == null) {
                GameRes.loadRes(this.gameResGroupName, this.mcPath, this.mcName, this.OnLoadComplateBySync, this);
            }
            else {
                this.OnLoadComplateBySync();
            }
        }
    };
    MovieClipComponentBase.prototype.MCJsonLoadSuccess = function (data, key) {
        this.mcData = data;
        RES.getResAsync(this.mcName + "_png", this.OnLoadComplateByAsync, this);
    };
    /**
     * 修改父组件，切换层级
     */
    MovieClipComponentBase.prototype.ChangeParent = function (view) {
        view.addChild(this.body);
    };
    MovieClipComponentBase.prototype.update = function (advancedTime) {
    };
    //默认是否移除body,默认会移除
    MovieClipComponentBase.prototype.stop = function (isRemoveBody) {
        if (isRemoveBody === void 0) { isRemoveBody = true; }
        this.isRuning = false;
        this.mcPath = null;
        this.mcName = null;
        this.mEntity = null;
        // ObjectPool.push(this.mc);
        if (this.mc) {
            this.mc.destroy();
            this.mc = null;
        }
        if (isRemoveBody) {
            App.DisplayUtils.removeFromParent(this.body);
            ObjectPool.push(this.body);
            this.body.removeChildren();
            this.body = null;
        }
    };
    /**
     * 资源加载完毕了
     * @param _json与_png 对应resource_objects&resource_effect等文件内的后缀
     */
    MovieClipComponentBase.prototype.OnLoadComplateByAsync = function (data, key) {
        if (!this.isRuning) {
            return;
        }
        var texture = data;
        var mcFactory = new egret.MovieClipDataFactory(this.mcData, texture);
        this.mc.setMcData(mcFactory.generateMovieClipData(this.mcName), this.mcName);
        this.mc.addEventListener("MovieClipEnd", this.MovieClipEnd, this);
    };
    MovieClipComponentBase.prototype.OnLoadComplateBySync = function () {
        if (!this.isRuning) {
            return;
        }
        var avatarResName = this.mcName;
        var data = RES.getRes(avatarResName + "_json");
        var texture = RES.getRes(avatarResName + "_png");
        var mcFactory = new egret.MovieClipDataFactory(data, texture);
        this.mc.setMcData(mcFactory.generateMovieClipData(avatarResName), avatarResName);
        this.mc.addEventListener("MovieClipEnd", this.MovieClipEnd, this);
    };
    MovieClipComponentBase.prototype.complateAction = function () {
    };
    MovieClipComponentBase.prototype.MovieClipEnd = function (event) {
        if (this.mEntity != null) {
            for (var eventType in this.mMovieClipEvent) {
                if (eventType == event.type) {
                    for (var key in this.mMovieClipEvent[eventType]) {
                        if (key + "_" + this.mc.getDir(this.mEntity.dir)[0] == event.data) {
                            var funs = this.mMovieClipEvent[eventType][key];
                            if (funs) {
                                for (var index = 0; index < funs.length; index++) {
                                    // console.log("MovieClipEnd"+this.mEntity.basicattr.Name+"     "+event.data);
                                    this.mMovieClipEvent[eventType][key][index]();
                                }
                            }
                        }
                    }
                }
            }
        }
    };
    MovieClipComponentBase.prototype.AddMovieClipEvent = function (event, key, callback) {
        if (this.mMovieClipEvent[event]) {
            if (this.mMovieClipEvent[event][key]) {
                this.mMovieClipEvent[event][key].push(callback);
            }
            else {
                var dic = {};
                var callList = [];
                callList.push(callback);
                dic[key] = callList;
                this.mMovieClipEvent[event] = dic;
                dic = {};
                callList = [];
            }
        }
        else {
            var dic = {};
            var callList = [];
            callList.push(callback);
            dic[key] = callList;
            this.mMovieClipEvent[event] = dic;
            dic = {};
            callList = [];
        }
    };
    MovieClipComponentBase.prototype.RemoveMovieClipEvent = function (event, key, callback) {
        if (this.mMovieClipEvent[event]) {
            if (this.mMovieClipEvent[event][key]) {
                var index = this.mMovieClipEvent[event][key].indexOf(callback);
                if (index > -1) {
                    this.mMovieClipEvent[event][key].splice(index, 1);
                }
            }
        }
    };
    /**注册事件监听 */
    MovieClipComponentBase.prototype.RegisEventListener = function (eventType, event) {
        if (this.mEventListenerList[eventType]) {
            this.RemoveEventListener(eventType, event);
        }
        this.body.addEventListener(eventType, event, this);
        this.mEventListenerList[eventType] = event;
    };
    /**注销事件监听 */
    MovieClipComponentBase.prototype.RemoveEventListener = function (eventType, event) {
        if (event) {
            this.body.removeEventListener(eventType, event, this);
            this.mEventListenerList[eventType] = null;
        }
        else {
            if (this.mEventListenerList[eventType]) {
                this.body.removeEventListener(eventType, this.mEventListenerList[eventType], this);
                this.mEventListenerList[eventType] = null;
            }
        }
    };
    /**注册所有事件 */
    MovieClipComponentBase.prototype.RemoveAllEventListener = function () {
        for (var key in this.mEventListenerList) {
            if (key != null && this.mEventListenerList[key] != null) {
                this.RemoveEventListener(key, this.mEventListenerList[key]);
            }
        }
        this.mEventListenerList = {};
    };
    return MovieClipComponentBase;
}());
__reflect(MovieClipComponentBase.prototype, "MovieClipComponentBase");
//# sourceMappingURL=MovieClipComponentBase.js.map