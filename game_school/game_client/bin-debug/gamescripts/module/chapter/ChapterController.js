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
var ChapterController = (function (_super) {
    __extends(ChapterController, _super);
    function ChapterController() {
        var _this = _super.call(this) || this;
        _this.RegisterEvent(EventDef.SelectChapter);
        _this.RegisterEvent(EventDef.SelectCheckPoint);
        _this.RegisterEvent(EventDef.NextCheckPoint);
        //初始化Model
        _this.chapterModel = new ChapterModel(_this);
        //初始化UI
        _this.chapterView = new ChapterView(_this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Chapter, _this.chapterView);
        _this.chapterChooseView = new ChapterChooseView(_this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.ChapterChoose, _this.chapterChooseView);
        _this.chapterMseeagView = new ChapterMseeagView(_this, LayerManager.UI_Popup);
        App.ViewManager.register(ViewConst.ChapterMseeag, _this.chapterMseeagView);
        //初始化Proxy
        _this.chapterProxy = new ChapterProxy(_this);
        //注册模块间、模块内部事件监听
        // this.registerFunc(ChapterConst.SELECTCHAPTEREVENT_C2C, this.onSelectChapter, this);
        // this.registerFunc(ChapterConst.SELECTCHECKPOINTEREVENT_C2C, this.onSelectCheckPoint, this);
        // this.registerFunc(ChapterConst.NextCheckPoint_C2C, this.onNextCheckPoint, this);
        //初始化数据 这是个包含本地临时存储的方法
        _this.setCheckPointData();
        return _this;
    }
    ChapterController.prototype.HandleEvent = function (ev, le) {
        _super.prototype.HandleEvent.call(this, ev, le);
        if (EventDef.SelectChapter == ev) {
            this.onSelectChapter(le.IntParam0);
        }
        else if (EventDef.SelectCheckPoint == ev) {
            this.onSelectCheckPoint(le.IntParam0);
        }
        else if (EventDef.NextCheckPoint == ev) {
            this.onNextCheckPoint(le.IntParam0);
        }
    };
    //选择章节事件
    ChapterController.prototype.onSelectChapter = function (chapterId) {
        this.chapterModel.curSelectChapter = chapterId;
        if (!App.ViewManager.isShow(ViewConst.Chapter))
            App.ViewManager.open(ViewConst.Chapter);
        this.chapterView.updataUI();
    };
    //选择出击小关卡事件
    ChapterController.prototype.onSelectCheckPoint = function (checkPointId) {
        this.chapterModel.curCheckPoint = checkPointId;
        var con = this.chapterModel.GetCheckPointConfigByID(checkPointId);
        switch (con.checkpoint_type) {
            case 1:
                App.SceneManager.runScene(SceneConsts.CCG_FIGHT, checkPointId);
                App.ViewManager.close(ViewConst.Chapter);
                //App.ViewManager.open(ViewConst.ChapterMseeag);
                break;
            case 2://纯剧情关卡 目前的简单逻辑
                App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, con.plot, function () {
                    App.ViewManager.close(ViewConst.Dialog);
                    App.EventMgrHelper.PushEvent(EventDef.NextCheckPoint, checkPointId);
                    //App.ControllerManager.applyFunc(ControllerConst.Chapter, ChapterConst.NextCheckPoint_C2C, le.IntParam0);
                }.bind(this), 0, 0, "", "");
                break;
        }
    };
    ChapterController.prototype.setCheckPointData = function () {
        var isFirst = false; //用来检测第一关是不是打开
        var array = CheckPointConfig.array;
        var tempData = null;
        var tempValue = 1; //用来临时记录最大章节数
        //处理关卡信息
        for (var i = 0; i < array.length; i++) {
            if (array[i].chapter == 0)
                continue;
            if (array[i].chapter == 1 && tempData == null)
                tempData = array[i];
            var data = new checkPointData();
            data.checkPointID = array[i].id;
            this.chapterModel.checkPointDataArray.push(data);
            var value = egret.localStorage.getItem(array[i].id.toString());
            var isOpen = value == "1" ? true : false; //1 代表已经过关了
            data.isOpen = isOpen;
            if (isOpen) {
                isFirst = true;
                this.chapterModel.maxCheckPoint = array[i].id;
                tempValue = array[i].chapter;
            }
        }
        //处理最大章节数
        this.chapterModel.maxChapter = tempValue;
        if (!isFirst) {
            this.chapterModel.maxCheckPoint = tempData.id;
            this.chapterModel.maxChapter = 1;
            this.chapterModel.checkPointDataArray[0].isOpen = true;
            egret.localStorage.setItem(tempData.id.toString(), "1"); //保存一下 
        }
    };
    ChapterController.prototype.onNextCheckPoint = function (curID) {
        var curCon = this.chapterModel.GetCheckPointConfigByID(curID);
        var chapterID = curCon.chapter;
        if (chapterID != 0) {
            var curChapterCon = this.chapterModel.GetChapterConfigByID(chapterID);
            var nextID = -1;
            var index = void 0;
            for (var i = 0; i < curChapterCon.chapter_id.length; i++) {
                if (curChapterCon.chapter_id[i] == curID) {
                    index = i;
                    break;
                }
            }
            if (index + 1 < curChapterCon.chapter_id.length) {
                nextID = curChapterCon.chapter_id[index + 1];
            }
            else {
                var nextChapterID = chapterID + 1;
                var nextChapterCon = this.chapterModel.GetChapterConfigByID(nextChapterID);
                if (nextChapterCon != null) {
                    nextID = nextChapterCon.chapter_id[0];
                }
            }
            var tempValue = 1; //用来临时记录最大章节数
            if (nextID != -1) {
                var key = nextID.toString();
                var value = "1";
                egret.localStorage.setItem(key, value);
                this.chapterModel.maxCheckPoint = nextID;
                var list = this.chapterModel.checkPointDataArray;
                for (var i = 0; i < list.length; i++) {
                    if (nextID == list[i].checkPointID) {
                        list[i].isOpen = true;
                    }
                    if (list[i].isOpen) {
                        //处理最大章节数
                        var tempCon = CheckPointConfig.GetConfig(list[i].checkPointID);
                        tempValue = tempCon.chapter;
                    }
                }
            }
            //处理最大章节数
            this.chapterModel.maxChapter = tempValue;
            if (App.ViewManager.isShow(ViewConst.Chapter)) {
                this.chapterView.updataUI();
            }
            if (App.ViewManager.isShow(ViewConst.ChapterChoose)) {
                this.chapterChooseView.updataUI();
            }
        }
    };
    return ChapterController;
}(BaseController));
__reflect(ChapterController.prototype, "ChapterController");
//# sourceMappingURL=ChapterController.js.map