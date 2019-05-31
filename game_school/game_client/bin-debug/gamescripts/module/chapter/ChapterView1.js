/**
/**
 * 这是个单纯的备份
 */
// class ChapterView1 extends BaseEuiView {
//     public constructor($controller: BaseController, $parent: eui.Group) {
//         super($controller, $parent);
//     }
//     public get Model(): ChapterModel {
//         return App.ControllerManager.getControllerModel(ControllerConst.Chapter) as ChapterModel;
//     }
//     private lastUIName: string;
//     //整个UI的面板Group
//     public chapterItemGroup: eui.Group;
//     private chapterItemArray: Array<ChapterItem> = [];
//     //章节标题
//     private label_chaptername: eui.Label;
//     //章节背景图
//     private image_background: eui.Image;
//     //返回
//     private btn_back: eui.Button;
//     //选择章节
//     private btn_arrow: eui.Button;
//     //队伍编辑
//     private btn_team: eui.Button;
//     /**
//      *对面板进行显示初始化，用于子类继承
//      *
//      */
//     public initUI(): void {
//         super.initUI();
//         this.skinName = App.ViewManager.getSkin(ViewConst.Chapter);//"resource/skins/Chapter.exml";
//         this.btn_back.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
//             this.onClose();
//             App.ViewManager.close(ViewConst.ChapterMseeag);
//             App.ViewManager.close(ViewConst.ChapterChoose);
//             App.ViewManager.open(ViewConst.MainUI);
//         }, this);
//         this.btn_arrow.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onArrow, this);
//         this.btn_team.addEventListener(egret.TouchEvent.TOUCH_TAP, () => {
//             App.ViewManager.close(ViewConst.Chapter);
//             App.ViewManager.close(ViewConst.ChapterMseeag);
//             App.ViewManager.close(ViewConst.ChapterChoose);
//             App.ViewManager.open(ViewConst.Loading);
//             var groupName: string = "battle_preload_main";
//             var subGroups: Array<string> = ["preload_effect", "battle_preload_objects"];
//             App.ResourceUtils.loadGroups(groupName, subGroups, this.onResourceLoadComplete, this.onResourceLoadProgress, this);
//         }, this);
//     }
//     /**
//     * 资源组加载完成
//     */
//     private onResourceLoadComplete(): void {
//         App.ViewManager.close(ViewConst.Loading);
//         App.ViewManager.open(ViewConst.BattleArray);
//     }
//     /**
//     * 资源组加载进度
//     */
//     private onResourceLoadProgress(itemsLoaded: number, itemsTotal: number): void {
//         App.ControllerManager.applyFunc(ControllerConst.Loading, LoadingConst.SetProgress, itemsLoaded, itemsTotal);
//     }
//     /**
//     *对面板数据的初始化，用于子类继承
//     *
//     */
//     public initData(): void {
//         super.initData();
//     }
//     /**
//      * 面板开启执行函数，用于子类继承
//      * @param param 参数
//      */
//     public open(...param: any[]): void {
//         super.open(param);
//         this.updataUI();
//     }
//     /**
//      * 面板关闭执行函数，用于子类继承
//      * @param param 参数
//      */
//     public close(...param: any[]): void {
//         super.close(param);
//         App.SoundManager.stopBg();
//     }
//     //选择关卡页面
//     private onArrow(): void {
//         // 如果已经打开了,就不在重复打开了,或者出战UI是否已经打开了
//         if (App.ViewManager.isShow(ViewConst.ChapterMseeag)
//             || App.ViewManager.isShow(ViewConst.ChapterChoose)) {
//             return;
//         }
//         App.ViewManager.open(ViewConst.ChapterChoose);
//     }
//     //刷新页面UI
//     public updataUI(): void {
//         var array: Array<CheckPointConfig> = this.Model.GetCheckPointConfigListByChapterID(this.Model.curSelectChapter);
//         this.createOrUpdateItem(array);
//         for (var i: number = 0; i < this.chapterItemArray.length; i++) {
//             this.chapterItemArray[i].setVisible(false);
//         }
//         for (var i: number = 0; i < array.length; i++) {
//             this.chapterItemArray[i].setData(array[i]);
//             this.chapterItemArray[i].setVisible(true);
//         }
//         var con: ChapterConfig = this.Model.GetChapterConfigByID(this.Model.curSelectChapter);
//         this.label_chaptername.text = con.chapter_num + " " + con.chapter_name;
//         this.image_background.source = con.chapter_bg;
//         App.SoundManager.playBg(con.chapter_music);
//     }
//     public createOrUpdateItem(listCount: Array<CheckPointConfig>): void {
//         //创建UI chapterItem
//         for (var i: number = this.chapterItemArray.length; i < listCount.length; i++) {
//             var chapterItem: ChapterItem = new ChapterItem();
//             chapterItem.init(this);
//             this.chapterItemGroup.addChild(chapterItem);
//             this.chapterItemArray.push(chapterItem);
//         }
//     }
//     public selectChapterPoint(chapterPontID: number): void {
//         this.applyFunc(ChapterConst.SELECTCHECKPOINTEREVENT_C2C, chapterPontID);
//     }
// }
// class ChapterItem extends eui.Component {
//     constructor() {
//         super();
//         this.skinName = "resource/skins/ChapterItem.exml";
//     }
//     private mHandView: ChapterView;
//     private mCon: CheckPointConfig;
//     private btn_chapter: eui.Button;
//     private image_bg: eui.Image;
//     private label_name: eui.Label;
//     private image_star1: eui.Image;
//     private image_star2: eui.Image;
//     private image_star3: eui.Image;
//     private image_lock: eui.Image;
//     private image_battle: eui.Image;
//     public setVisible(v: boolean): void {
//         this.visible = v;
//     }
//     //刷新数据
//     public init(view: ChapterView): void {
//         if (view == null)
//             return;
//         this.mHandView = view;
//         this.btn_chapter.addEventListener(egret.TouchEvent.TOUCH_TAP, this.onClick, this);
//     }
//     //设置数据
//     public setData(data: CheckPointConfig): void {
//         if (data == null)
//             return;
//         this.mCon = data;
//         this.setPos(data.coordinate[0], data.coordinate[1]);
//         this.label_name.text = data.checkpoint_name;
//         this.image_star1.visible = false;
//         this.image_star2.visible = false;
//         this.image_star3.visible = false;
//         //this.image_lock.visible = true;
//         // if (data.id <= this.mHandView.Model.maxCheckPoint) {
//         //     this.image_lock.visible = false;
//         // }
//         let list = this.mHandView.Model.checkPointDataArray;
//         for (var i = 0; i < list.length; i++) {
//             if (data.id == list[i].checkPointID) {
//                 this.image_lock.visible = !list[i].isOpen;
//             }
//         }
//         this.image_bg.source = data.battle_bg;
//         this.image_battle.visible = false;
//         if (App.FightManager.CheckPointID) {
//             //当前战斗的是不是这一课
//             if (data.id == App.FightManager.CheckPointID) {
//                 this.image_battle.visible = App.FightManager.IsFightFinish;
//             }
//         }
//     }
//     //设置位置
//     public setPos(posX: number, posY: number): void {
//         this.x = posX;
//         this.y = posY;
//         //等比的修改方案
//         // let w = this.mHandView.width;
//         // let h = this.mHandView.height;
//         // this.x = posX * w / 750;
//         // this.y = posY * h / 1334;
//     }
//     private onClick(): void {
//         if (this.image_lock.visible)
//             return;
//         if (App.ViewManager.isShow(ViewConst.ChapterMseeag)
//             || App.ViewManager.isShow(ViewConst.ChapterChoose)) {
//             return;
//         }
//         this.mHandView.selectChapterPoint(this.mCon.id);
//     }
// } 
//# sourceMappingURL=ChapterView1.js.map