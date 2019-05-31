
class GameResGroupName {
    public static AvatarGroup: string = "avatarGroup_";
    public static SkilleffGroup: string = "skilleffGroup_";
    public static BuffeffGroup: string = "buffeffGroup_";
}


/**
* Created by sjz on 2018-5-10.
*/
class GameRes {
    private static ComplateResList: any = {};
    private static LoadingResList: any = {};

    public static clearAvatar(avatarResName: string): void {
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
    }

    public static loadAvatar(avatarResPath: string, avatarResName: string, onLoadComplate: Function, onLoadComplateTarget: any): void {
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

            var avatarResKeys: string[] = [];
            [
                {
                    name: avatarResName + ".json",
                    type: "json"
                },
                {
                    name: avatarResName + ".png",
                    type: "image"
                }
            ].forEach(function (res: any) {
                var resKey: string = "avatar_" + res.name;
                avatarResKeys.push(resKey);
                App.ResourceUtils.createResource(resKey, res.type, avatarResPath + res.name);
            });

            App.ResourceUtils.createGroup(groupName, avatarResKeys);
            App.ResourceUtils.loadGroup(groupName, this.onLoadGroupComplate, this.onLoadGroupProgress, this);
        }
    }

    public static loadSkillEffect(skillEffResPath: string, skillEffResName: string, onLoadComplate: Function, onLoadComplateTarget: any): void {
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

            var avatarResKeys: string[] = [];
            [
                {
                    name: skillEffResName + ".json",
                    type: "json"
                },
                {
                    name: skillEffResName + ".png",
                    type: "image"
                }
            ].forEach(function (res: any) {
                var resKey: string = "avatar_" + res.name;
                avatarResKeys.push(resKey);
                App.ResourceUtils.createResource(resKey, res.type, skillEffResPath + res.name);
            });

            App.ResourceUtils.createGroup(groupName, avatarResKeys);
            App.ResourceUtils.loadGroup(groupName, this.onLoadGroupComplate, this.onLoadGroupProgress, this);
        }
    }

    public static loadBuffEffect(buffEffResPath: string, buffEffResName: string, onLoadComplate: Function, onLoadComplateTarget: any): void {
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

            var avatarResKeys: string[] = [];
            [
                {
                    name: buffEffResName + ".json",
                    type: "json"
                },
                {
                    name: buffEffResName + ".png",
                    type: "image"
                }
            ].forEach(function (res: any) {
                var resKey: string = "avatar_" + res.name;
                avatarResKeys.push(resKey);
                App.ResourceUtils.createResource(resKey, res.type, buffEffResPath + res.name);
            });

            App.ResourceUtils.createGroup(groupName, avatarResKeys);
            App.ResourceUtils.loadGroup(groupName, this.onLoadGroupComplate, this.onLoadGroupProgress, this);
        }
    }

    /**
     * 加载资源
     * @param {string} gameResGroupName 使用GameResGroupName里面的静态资源
     * @param {string} resPath
     * @param {string} resName
     */
    public static loadRes(gameResGroupName: string, resPath: string, resName: string, onLoadComplate: Function, onLoadComplateTarget: any): void {
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

            var avatarResKeys: string[] = [];
            [
                {
                    name: resName + ".json",
                    type: "json"
                },
                {
                    name: resName + ".png",
                    type: "image"
                }
            ].forEach(function (res: any) {
                var resKey: string = "avatar_" + res.name;
                avatarResKeys.push(resKey);
                App.ResourceUtils.createResource(resKey, res.type, resPath + res.name);
            });

            App.ResourceUtils.createGroup(groupName, avatarResKeys);
            App.ResourceUtils.loadGroup(groupName, this.onLoadGroupComplate, this.onLoadGroupProgress, this);
        }
    }

    private static onLoadGroupComplate(groupName: string): void {
        var callBacks = this.LoadingResList[groupName];
        callBacks.forEach(function (arr) {
            arr[0].call(arr[1]);
        })

        this.LoadingResList[groupName] = null;
        delete this.LoadingResList[groupName];

        this.ComplateResList[groupName] = 1;
    }

    private static onLoadGroupProgress(groupName: string): void {

    }
}