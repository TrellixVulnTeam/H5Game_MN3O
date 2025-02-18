/**
 * Created by sjz on 2018-5-9.
 */
class Component {
    public dealTime: number;
    public dealInterval: number;

    public entity: GameObject;
    public isRuning: boolean;
    public type: string;

    public constructor() {
    }

    public start(): void {
        this.dealTime = 0;
        this.dealInterval = 0;
        this.isRuning = true;
    }

    public stop(): void {
        this.dealTime = null;
        this.dealInterval = null;

        this.entity = null;
        this.isRuning = false;
        this.type = null;
    }

    public update(advancedTime: number): void {

    }
}