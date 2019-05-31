/**
 * 
 */
class ChapterController extends BaseController {
    //本模块的数据存储
    private chapterModel: ChapterModel;
    //本模块的所有UI
    private chapterView: ChapterView;
    private chapterChooseView: ChapterChooseView;
    private chapterMseeagView: ChapterMseeagView;

    //本模块的Proxy
    private chapterProxy: ChapterProxy;

    public constructor() {
        super();

        this.RegisterEvent(EventDef.SelectChapter);
        this.RegisterEvent(EventDef.SelectCheckPoint);
        this.RegisterEvent(EventDef.NextCheckPoint);

        //初始化Model
        this.chapterModel = new ChapterModel(this);

        //初始化UI
        this.chapterView = new ChapterView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.Chapter, this.chapterView);

        this.chapterChooseView = new ChapterChooseView(this, LayerManager.UI_Popup)
        App.ViewManager.register(ViewConst.ChapterChoose, this.chapterChooseView);

        this.chapterMseeagView = new ChapterMseeagView(this, LayerManager.UI_Popup)
        App.ViewManager.register(ViewConst.ChapterMseeag, this.chapterMseeagView);

        //初始化Proxy
        this.chapterProxy = new ChapterProxy(this);

        //注册模块间、模块内部事件监听
        // this.registerFunc(ChapterConst.SELECTCHAPTEREVENT_C2C, this.onSelectChapter, this);
        // this.registerFunc(ChapterConst.SELECTCHECKPOINTEREVENT_C2C, this.onSelectCheckPoint, this);

        // this.registerFunc(ChapterConst.NextCheckPoint_C2C, this.onNextCheckPoint, this);

        //初始化数据 这是个包含本地临时存储的方法
        this.setCheckPointData();
    }

    public HandleEvent(ev: EventDef, le: LogicEvent): void {
        super.HandleEvent(ev, le);
        if (EventDef.SelectChapter == ev) {
            this.onSelectChapter(le.IntParam0);
        }
        else if (EventDef.SelectCheckPoint == ev) {
            this.onSelectCheckPoint(le.IntParam0);
        }
        else if (EventDef.NextCheckPoint == ev) {
            this.onNextCheckPoint(le.IntParam0);
        }
    }

    //选择章节事件
    private onSelectChapter(chapterId: number): void {
        this.chapterModel.curSelectChapter = chapterId;
        if (!App.ViewManager.isShow(ViewConst.Chapter))
            App.ViewManager.open(ViewConst.Chapter);
        this.chapterView.updataUI();
    }


    //选择出击小关卡事件
    private onSelectCheckPoint(checkPointId: number): void {
        this.chapterModel.curCheckPoint = checkPointId;
        let con = this.chapterModel.GetCheckPointConfigByID(checkPointId);
        switch (con.checkpoint_type) {
            case 1:
                App.SceneManager.runScene(SceneConsts.CCG_FIGHT, checkPointId);
                App.ViewManager.close(ViewConst.Chapter);
                //App.ViewManager.open(ViewConst.ChapterMseeag);
                break;
            case 2: //纯剧情关卡 目前的简单逻辑
                App.EventMgrHelper.PushEventEx(EventDef.PlayPlotGroup, con.plot, function () {
                    App.ViewManager.close(ViewConst.Dialog);
                    App.EventMgrHelper.PushEvent(EventDef.NextCheckPoint, checkPointId);
                    //App.ControllerManager.applyFunc(ControllerConst.Chapter, ChapterConst.NextCheckPoint_C2C, le.IntParam0);
                }.bind(this), 0, 0, "", "");
                break;
        }
    }

    private setCheckPointData() {
        let isFirst: boolean = false; //用来检测第一关是不是打开
        var array: Array<CheckPointConfig> = CheckPointConfig.array;
        let tempData: CheckPointConfig = null;
        let tempValue: number = 1; //用来临时记录最大章节数
        //处理关卡信息
        for (var i = 0; i < array.length; i++) {
            if (array[i].chapter == 0)
                continue;
            if (array[i].chapter == 1 && tempData == null)
                tempData = array[i];
            let data = new checkPointData();
            data.checkPointID = array[i].id;
            this.chapterModel.checkPointDataArray.push(data);

            let value: string = egret.localStorage.getItem(array[i].id.toString());
            let isOpen: boolean = value == "1" ? true : false;  //1 代表已经过关了
            data.isOpen = isOpen;

            if (isOpen) {
                isFirst = true;
                this.chapterModel.maxCheckPoint = array[i].id;
                tempValue = array[i].chapter;
            }
        }

        //处理最大章节数
        this.chapterModel.maxChapter = tempValue;

        if (!isFirst) //如果第一次没有打开第一关,默认打开一下第一关
        {
            this.chapterModel.maxCheckPoint = tempData.id;
            this.chapterModel.maxChapter = 1;
            this.chapterModel.checkPointDataArray[0].isOpen = true;
            egret.localStorage.setItem(tempData.id.toString(), "1"); //保存一下 
        }
    }


    private onNextCheckPoint(curID: number): void {
        let curCon: CheckPointConfig = this.chapterModel.GetCheckPointConfigByID(curID);
        let chapterID: number = curCon.chapter;
        if (chapterID != 0) {
            let curChapterCon = this.chapterModel.GetChapterConfigByID(chapterID);

            let nextID: number = -1;
            let index: number;
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
                let nextChapterID = chapterID + 1;
                let nextChapterCon = this.chapterModel.GetChapterConfigByID(nextChapterID);
                if (nextChapterCon != null) {
                    nextID = nextChapterCon.chapter_id[0];
                }
            }


            let tempValue: number = 1; //用来临时记录最大章节数
            if (nextID != -1) {
                let key: string = nextID.toString();
                let value: string = "1";
                egret.localStorage.setItem(key, value);
                this.chapterModel.maxCheckPoint = nextID;

                let list = this.chapterModel.checkPointDataArray;
                for (var i = 0; i < list.length; i++) {
                    if (nextID == list[i].checkPointID) {
                        list[i].isOpen = true;
                    }
                    if (list[i].isOpen) {
                        //处理最大章节数
                        let tempCon = CheckPointConfig.GetConfig(list[i].checkPointID)
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
    }
}