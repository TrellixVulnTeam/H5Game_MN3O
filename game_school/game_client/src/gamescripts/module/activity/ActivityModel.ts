/**
 */
class ActivityModel extends BaseModel {
    /**
     * 构造函数
     * @param $controller 所属模块
     */
    public constructor($controller: BaseController) {
        super($controller);
    }

    public activityConArray: Array<ActivityClientConfig> = [];

    public initActivityArray(): void {
        function _sort(a: ActivityClientConfig, b: ActivityClientConfig) {
            return a.sort - b.sort;
        }
        let array: Array<ActivityClientConfig> = ActivityClientConfig.array;
        this.activityConArray = array.splice(0);  //数组的深拷贝
        this.activityConArray.sort(_sort);
    }
}
