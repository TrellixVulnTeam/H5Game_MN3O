/**
 */
class DialogModel extends BaseModel {
    public constructor($controller: BaseController) {
        super($controller);
    }

    /// <summary>
    /// 当前需要播放的对话组ID
    /// </summary>
    public curPlotGroupID: number;

    /// <summary>
    /// 对话结束回调函数
    /// </summary>
    public GoOutCallBack?: Function;

    /// <summary>
    /// 当前对话数据
    /// </summary>
    public curDialogConf: DialogConfig;

    /**
    * 根据ID获得 ChapterConfig表数据 章节表
    * @param $ID 表ID
    */
    public GetDialogConfigByID(ID: number): DialogConfig {
        var array: Array<DialogConfig> = DialogConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (ID == array[i].dialogID) {
                return array[i];
            }
        }
        return null;
    }

    public GetDialogGroupDataByDialogGroupID(plotGroupID: number): PlotGroupConfig {
        var array: Array<PlotGroupConfig> = PlotGroupConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (plotGroupID == array[i].plotGroupID) {
                return array[i];
            }
        }
        return null;
    }

    public GetDialogOptionConfigByOptionID(optionID: number): DialogOptionConfig {
        var array: Array<DialogOptionConfig> = DialogOptionConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (optionID == array[i].optionID) {
                return array[i];
            }
        }
        return null;
    }

    //遍历 BlackScreenConfig 表
    public GetBlackScreenConfigArray(startID: number): Array<BlackScreenConfig> {
        let array: Array<BlackScreenConfig> = [];
        let nextID: number = startID;
        while (nextID != -1) {
            let con = BlackScreenConfig.GetConfig(nextID);
            nextID = con.nextId;
            array.push(con);
        }
        return array;
    }
}
