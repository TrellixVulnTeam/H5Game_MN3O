/**
 * @author sjz
 * @time 2018-8-13 19:10
 */
class LogicEvent {
    public constructor() {
    }

    NUMBER_MIN_STR: string = "MIN";
    NUMBER_MAX_STR: string = "MAX";
    NUMBER_DEFAULT_STR: string = "DEFAULT";
    private mEvent: EventDef = EventDef.NONE;
    private mIntParam0: number = -1;
    private mIntParam1: number = -1;
    private mStrParam0: string = "";
    private mStrParam1: string = "";
    private mObject0: any;
    private mObject1: any;
    private mObject2: any;
    private mLocked: boolean = false;
    private mDicParam0: Dictionary<string, number> = new Dictionary<string, number>(true);

    private static msEventPool: MemoryPool<LogicEvent> = new MemoryPool<LogicEvent>(50);


    private Reset(): void {
        this.mEvent = EventDef.NONE;
        this.mIntParam0 = -1;
        this.mIntParam1 = -1;
        this.mStrParam0 = "";
        this.mStrParam1 = "";
        this.mObject0 = null;
        this.mObject1 = null;
        this.mDicParam0.Clear();
    }

    public static CreateEvent(): LogicEvent {
        let le: LogicEvent = this.msEventPool.Alloc();
        if (le != null) {
            return le;
        }

        return new LogicEvent();
    }

    public static DestroyEvent(le: LogicEvent): void {
        le.Reset();
        this.msEventPool.Free(le);
    }

    public get Event() {
        return this.mEvent;
    }
    public set Event(value) {
        this.mEvent = value;
    }

    public get Locked() {
        return this.mLocked;
    }
    public set Locked(value) {
        this.mLocked = value;
    }

    public get IntParam0() {
        return this.mIntParam0;
    }
    public set IntParam0(value) {
        this.mIntParam0 = value;
    }

    public get IntParam1() {
        return this.mIntParam1;
    }
    public set IntParam1(value) {
        this.mIntParam1 = value;
    }

    public get StrParam0() {
        return this.mStrParam0;
    }
    public set StrParam0(value) {
        this.mStrParam0 = value;
    }

    public get StrParam1() {
        return this.mStrParam1;
    }
    public set StrParam1(value) {
        this.mStrParam1 = value;
    }

    public get Object0() {
        return this.mObject0;
    }
    public set Object0(value) {
        this.mObject0 = value;
    }


    public get Object1() {
        return this.mObject1;
    }
    public set Object1(value) {
        this.mObject1 = value;
    }

    public get Object2() {
        return this.mObject2;
    }
    public set Object2(value) {
        this.mObject2 = value;
    }

    public get DicParam0() {
        return this.mDicParam0;
    }
    public set DicParam0(value) {
        this.mDicParam0 = value;
    }
}