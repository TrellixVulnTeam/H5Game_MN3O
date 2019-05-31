/**
 * 
 */
class TestSpineController extends BaseController {  
    //本模块的所有UI
    private testSpineView: TestSpineView;

    public constructor() {
        super();
    
        //初始化UI
        this.testSpineView = new TestSpineView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.TestSpine, this.testSpineView); 
    }
}