/**
 * 视频播放UI,控制层
 * @constructor {sjz}
 * @data {2018-6-27}
 */
class VideoPlayUIController extends BaseController {
    private videoview:VideoPlayUIView;

    public constructor() {
        super();

        this.videoview = new VideoPlayUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.VideoPlayUI, this.videoview);
    }
}