/**
 */
class MainUIModel extends BaseModel {

    /**
     * 构造函数
     * @param $controller 所属模块
     */
    public constructor($controller: BaseController) {
        super($controller);
    }




    /**
    * 根据ID获得 ChapterConfig表数据 章节表
    * @param $ID 表ID
    */
    public GetFaceConfigByID(ID: number): FaceConfig {
        var array: Array<FaceConfig> = FaceConfig.array;
        for (var i = 0; i < array.length; i++) {
            if (ID == array[i].id) {
                return array[i];
            }
        }
        return null;
    }

}
