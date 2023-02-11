import { setTestabilityGetter } from "@angular/core";

export class Drone {
    id: number = -1;
    x: number = 0;
    y: number = 0;
    orientation: number = 0;
    status: number = DroneStatus.Waiting;
    batteryLevel: number = 0;
    peerToPeer: boolean = false;
    simulationId?: string;

    public constructor(
        id: number,
        x: number,
        y: number,
        orientation: number,
        status: number,
        batteryLevel: number,
        peerToPeer: boolean) {
            this.id = id;
            this.x = x;
            this.y = y;
            this.orientation = orientation;
            if (status <= 4 && status >= 0) this.status = status;
            if (batteryLevel<=100 && batteryLevel >= 0) this.batteryLevel = batteryLevel;
            this.peerToPeer = peerToPeer;
        }

    setX(x: number) {
        this.x = x;
    }

    setY(y: number) {
        this.y = y;
    }

    setStatus(status: string) {
        switch(status) {
            case 'Waiting': this.status = DroneStatus.Waiting;
            break;
            case 'Takeoff': this.status = DroneStatus.TakeOff;
            break;
            case 'Exploring': this.status = DroneStatus.OnMission;
            break;
            case 'Landing': this.status = DroneStatus.Landing;
            break;
            case 'Returning': this.status = DroneStatus.BackToBase;
            break;
            case 'Crashed': this.status = DroneStatus.Crashed;
            break;
            default: this.status = DroneStatus.Waiting;
          }
    }

    setOrientation(rad: number) {
        this.orientation = rad;
    }

    setBatteryLevel(level:number) {
        this.batteryLevel = level;
    }

    setSimulationId(id: string) {
        this.simulationId = id;
    }
}

export enum DroneStatus {
    Waiting = 0,
    TakeOff,
    OnMission,
    Landing,
    BackToBase,
    Crashed,
};