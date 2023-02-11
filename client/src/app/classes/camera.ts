import { Drone, DroneStatus } from "./drone";
import { Obstacle } from "./obstacle";

export class Camera {
    drones: Drone[] = [new Drone(0, 350, 350, 0, DroneStatus.OnMission, 0, false)];
    obstacles: Obstacle[] = [];
    subCameras?:Camera[];
    name:string = 'Globale';

    constructor(drone?: Drone, obstacles?: Obstacle[], subCameras?: Camera[]) {
        if (drone) {
            this.drones[0] = drone;
            this.name = drone.id.toString();
        }

        if (obstacles) {
            this.obstacles = obstacles.filter((obstacle: Obstacle) => { return obstacle.id == drone?.id;});
        }

        if (subCameras) {
            this.drones.pop();
            this.drones.pop();
            for (let camera of subCameras) {
                this.drones = this.drones.concat(camera.drones);
            }
        }
    }
}