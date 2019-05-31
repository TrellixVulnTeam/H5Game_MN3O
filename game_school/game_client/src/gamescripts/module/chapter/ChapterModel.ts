/**
 */
class ChapterModel extends BaseModel {
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    public constructor($controller: BaseController) {
        super($controller);
    }

    //是否第一次打开章节
    public isFirstOpenChapter :boolean = true;

    //当先选择的章节信息
    public curSelectChapter: number = 1;

    //当前的战斗关卡
    public curCheckPoint: number = 1;

    //关卡的最大进度
    public maxCheckPoint: number;

    //章节的最大进度
    public maxChapter: number = 1;

    public checkPointDataArray: Array<checkPointData> = [];

    //设置数据
    public setCheckPointData(): void {

    }


    /**
    * 根据ID获得 ChapterConfig表数据 章节表
    * @param $ID 表ID
    */
    public GetChapterConfigByID(ID: number): ChapterConfig {
        var array: Array<ChapterConfig> = ChapterConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (ID == array[i].id) {
                return array[i];
            }
        }
        return null;
    }


    /**
    * 根据章节ID获得 CheckPointConfig 关卡表
    * @param $ID 章节ID
    */
    public GetCheckPointConfigListByChapterID(chapterID: number): Array<CheckPointConfig> {
        var array: Array<CheckPointConfig> = CheckPointConfig.array;
        var resultArray: Array<CheckPointConfig> = [];
        for (var i = 0; i < array.length; i++) {
            if (chapterID == array[i].chapter) {
                resultArray.push(array[i]);
            }
        }
        return resultArray;
    }

    /**
    * 根据ID获得 CheckPointConfig 关卡表
    * @param $ID 表ID
    */
    public GetCheckPointConfigByID(ID: number): CheckPointConfig {
        var array: Array<CheckPointConfig> = CheckPointConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (ID == array[i].id) {
                return array[i];
            }
        }
        return null;
    }

}

class checkPointData {
    public constructor() {
    }
    public checkPointID: number;
    public isOpen: boolean = false;
}
