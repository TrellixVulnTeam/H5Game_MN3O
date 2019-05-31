var __reflect = (this && this.__reflect) || function (p, c, t) {
    p.__class__ = c, t ? t.push(c) : t = [c], p.__types__ = p.__types__ ? t.concat(p.__types__) : t;
};
var GameResGroupName = (function () {
    function GameResGroupName() {
    }
    GameResGroupName.AvatarGroup = "avatarGroup_";
    GameResGroupName.SkilleffGroup = "skilleffGroup_";
    GameResGroupName.BuffeffGroup = "buffeffGroup_";
    return GameResGroupName;
}());
__reflect(GameResGroupName.prototype, "GameResGroupName");
/**
* Created by sjz on 2018-5-10.
*/
var GameRes = (function () {
    function GameRes() {
    }
    GameRes.clearAvatar = function (avatarResName) {
        var groupName = "avatarGroup_" + avatarResName;
        if (this.LoadingResList[groupName]) {
            this.LoadingResList[groupName] = null;
            delete this.LoadingResList[groupName];
        }
        if (this.ComplateResList[groupName]) {
            this.ComplateResList[groupName] = null;
            delete this.ComplateResList[groupName];
        }
        RES.destroyRes(groupName);
    };
    GameRes.loadAvatar = function (avatarResPath, avatarResName, onLoadComplate, onLoadComplateTarget) {
        var groupName = "avatarGroup_" + avatarResName;
        if (this.ComplateResList[groupName]) {
            onLoadComplate.call(onLoadComplateTarget);
        }
        else if (this.LoadingResList[groupName]) {
            this.LoadingResList[groupName].push([onLoadComplate, onLoadComplateTarget]);
        }
        else {
            this.LoadingResList[groupName] = [];
            this.LoadingResList[groupName].push([onLoadComplate, onLoadComplateTarget]);
            var avatarResKeys = [];
            [
                {
                    name: avatarResName + ".json",
                    type: "json"
                },
                {
                    name: avatarResName + ".png",
                    type: "image"
                }
            ].forEach(function (res) {
                var resKey = "avatar_" + res.name;
                avatarResKeys.push(resKey);
                App.ResourceUtils.createResource(resKey, res.type, avatarResPath + res.name);
            });
            App.ResourceUtils.createGroup(groupName, avatarResKeys);
            App.ResourceUtils.loadGroup(groupName, this.onLoadGroupComplate, this.onLoadGroupProgress, this);
        }
    };
    GameRes.loadSkillEffect = function (skillEffResPath, skillEffResName, onLoadComplate, onLoadComplateTarget) {
        var groupName = "skilleffGroup_" + skillEffResName;
        if (this.ComplateResList[groupName]) {
            onLoadComplate.call(onLoadComplateTarget);
        }
        else if (this.LoadingResList[groupName]) {
            this.LoadingResList[groupName].push([onLoadComplate, onLoadComplateTarget]);
        }
        else {
            this.LoadingResList[groupName] = [];
            this.LoadingResList[groupName].push([onLoadComplate, onLoadComplateTarget]);
            var avatarResKeys = [];
            [
                {
                    name: skillEffResName + ".json",
                    type: "json"
                },
                {
                    name: skillEffResName + ".png",
                    type: "image"
                }
            ].forEach(function (res) {
                var resKey = "avatar_" + res.name;
                avatarResKeys.push(resKey);
                App.ResourceUtils.createResource(resKey, res.type, skillEffResPath + res.name);
            });
            App.ResourceUtils.createGroup(groupName, avatarResKeys);
            App.ResourceUtils.loadGroup(groupName, this.onLoadGroupComplate, this.onLoadGroupProgress, this);
        }
    };
    GameRes.loadBuffEffect = function (buffEffResPath, buffEffResName, onLoadComplate, onLoadComplateTarget) {
        var groupName = "buffeffGroup_" + buffEffResName;
        if (this.ComplateResList[groupName]) {
            onLoadComplate.call(onLoadComplateTarget);
        }
        else if (this.LoadingResList[groupName]) {
            this.LoadingResList[groupName].push([onLoadComplate, onLoadComplateTarget]);
        }
        else {
            this.LoadingResList[groupName] = [];
            this.LoadingResList[groupName].push([onLoadComplate, onLoadComplateTarget]);
            var avatarResKeys = [];
            [
                {
                    name: buffEffResName + ".json",
                    type: "json"
                },
                {
                    name: buffEffResName + ".png",
                    type: "image"
                }
            ].forEach(function (res) {
                var resKey = "avatar_" + res.name;
                avatarResKeys.push(resKey);
                App.ResourceUtils.createResource(resKey, res.type, buffEffResPath + res.name);
            });
            App.ResourceUtils.createGroup(groupName, avatarResKeys);
            App.ResourceUtils.loadGroup(groupName, this.onLoadGroupComplate, this.onLoadGroupProgress, this);
        }
    };
    /**
     * 加载资源
     * @param {string} gameResGroupName 使用GameResGroupName里面的静态资源
     * @param {string} resPath
     * @param {string} resName
     */
    GameRes.loadRes = function (gameResGroupName, resPath, resName, onLoadComplate, onLoadComplateTarget) {
        var groupName = gameResGroupName + resName;
        if (this.ComplateResList[groupName]) {
            onLoadComplate.call(onLoadComplateTarget);
        }
        else if (this.LoadingResList[groupName]) {
            this.LoadingResList[groupName].push([onLoadComplate, onLoadComplateTarget]);
        }
        else {
            this.LoadingResList[groupName] = [];
            this.LoadingResList[groupName].push([onLoadComplate, onLoadComplateTarget]);
            var avatarResKeys = [];
            [
                {
                    name: resName + ".json",
                    type: "json"
                },
                {
                    name: resName + ".png",
                    type: "image"
                }
            ].forEach(function (res) {
                var resKey = "avatar_" + res.name;
                avatarResKeys.push(resKey);
                App.ResourceUtils.createResource(resKey, res.type, resPath + res.name);
            });
            App.ResourceUtils.createGroup(groupName, avatarResKeys);
            App.ResourceUtils.loadGroup(groupName, this.onLoadGroupComplate, this.onLoadGroupProgress, this);
        }
    };
    GameRes.onLoadGroupComplate = function (groupName) {
        var callBacks = this.LoadingResList[groupName];
        callBacks.forEach(function (arr) {
            arr[0].call(arr[1]);
        });
        this.LoadingResList[groupName] = null;
        delete this.LoadingResList[groupName];
        this.ComplateResList[groupName] = 1;
    };
    GameRes.onLoadGroupProgress = function (groupName) {
    };
    GameRes.ComplateResList = {};
    GameRes.LoadingResList = {};
    return GameRes;
}());
__reflect(GameRes.prototype, "GameRes");
//# sourceMappingURL=GameRes.js.map