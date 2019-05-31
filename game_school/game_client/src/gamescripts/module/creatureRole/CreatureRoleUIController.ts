/**
 * 
 */
class CreatureRoleUIController extends BaseController
{
    private creatureRoleUIModel:CreatureRoleUIModel;
    private creatureRoleUIProxy:CreatureRoleUIProxy;
    private creatureRole:CreatureRoleUIView;

    public constructor(){
        super();

        this.creatureRoleUIModel = new CreatureRoleUIModel(this);
        this.creatureRoleUIProxy = new CreatureRoleUIProxy(this);

        this.creatureRole = new CreatureRoleUIView(this, LayerManager.UI_Main);
        App.ViewManager.register(ViewConst.CreatureRoleUI, this.creatureRole);
    }
}