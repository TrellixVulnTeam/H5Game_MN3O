/**
 * @author sjz
 * @time 2018-8-13 19:10
 */
class EventMgrHelper extends BaseClass {
    public constructor() {
        super();
        App.TimerManager.doFrame(1, 0, this.update, this);
        this.mListEvent = this.paramArray[this.mParamIndex]
    }
    private mDicHandler: Dictionary<EventDef, Array<EventHandler>> = new Dictionary<EventDef, Array<EventHandler>>(true);

    private mListEvent: Array<LogicEvent> = null;
    private paramArray: Array<LogicEvent>[] = [new Array<LogicEvent>(), new Array<LogicEvent>()];
    private mParamIndex: number = 0;
    public RegisterEventHandler(ed: EventDef, handler: EventHandler): void {
        let lh: Array<EventHandler>;
        if (this.mDicHandler.TryGetValue(ed) != null) {
            lh = this.mDicHandler.TryGetValue(ed);
            lh.push(handler);
        }
        else {
            lh = new Array<EventHandler>();
            lh.push(handler);
            this.mDicHandler.Add(ed, lh);
        }
    }

    public UnRegisterEventHandler(ed: EventDef, handler: EventHandler): void {
        let lh: Array<EventHandler>;
        if (this.mDicHandler.TryGetValue(ed) != null) {
            lh = this.mDicHandler.TryGetValue(ed);
            for (let i = 0; i < lh.length; ++i) {
                if (lh[i] == handler) {
                    lh.splice(i, 1)
                    return;
                }
            }
        }
    }

    public PushEvent(ed: EventDef, intdata0: number = -1, intdata1: number = -1, strData0: string = "", strData1: string = "", checkSameEvent: boolean = false): void {
        if (checkSameEvent) {
            if (this.ExistEvent(ed)) {
                return;
            }
        }
        let le: LogicEvent = this.CreateLogicEvent();
        le.Event = ed;
        le.IntParam0 = intdata0;
        le.IntParam1 = intdata1;
        le.StrParam0 = strData0;
        le.StrParam1 = strData1;

        this.Push(le);

    }

    public PushEventEx(ed: EventDef, object0: any, object1: any, data0: number, data1: number, strData0: string, strData1: string,object2: any=null, checkSameEvent: boolean = false): void {
        if (checkSameEvent) {
            if (this.ExistEvent(ed)) {
                return;
            }
        }
        let le: LogicEvent = this.CreateLogicEvent();
        le.Event = ed;
        le.Object0 = object0;
        le.Object1 = object1;
        le.IntParam0 = data0;
        le.IntParam1 = data1;
        le.StrParam0 = strData0;
        le.StrParam1 = strData1;
        le.Object2=object2;
        this.Push(le);
    }

    private Push(le: LogicEvent): void {
        this.mListEvent.push(le);

        if (this.mListEvent.length > 50) {
            let i: number = 0;
            ++i;
        }
    }

    private CreateLogicEvent(): LogicEvent {
        return LogicEvent.CreateEvent();
    }

    private ExistEvent(le: EventDef): boolean {
        for (let i = 0; i < this.mListEvent.length; ++i) {
            if (this.mListEvent[i].Event == le) {
                return true;
            }
        }
        return false;
    }

    private update(advancetime: number): void {
        if (this.mListEvent != null && this.mListEvent.length == 0) {
            return;
        }

        let oldEvent: Array<LogicEvent> = this.mListEvent;

        this.mParamIndex = (this.mParamIndex + 1) % 2;

        this.mListEvent = this.paramArray[this.mParamIndex];

        for (let i = 0; i < oldEvent.length; ++i) {
            let le: LogicEvent = oldEvent[i];

            let lh: Array<EventHandler>;
            if (this.mDicHandler.TryGetValue(le.Event) == null) {
                continue;
            }
            lh = this.mDicHandler.TryGetValue(le.Event);
            for (let j = 0; j < lh.length; ++j) {
                try {
                    lh[j].HandleEvent(le.Event, le);
                }
                catch (Error) {
                    Log.Error(Error);
                }
            }

            if (!le.Locked) {
                LogicEvent.DestroyEvent(le);
            }

        }

        oldEvent = [];
    }
}