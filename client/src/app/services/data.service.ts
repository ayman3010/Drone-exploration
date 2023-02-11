import { ElementRef, Injectable } from '@angular/core';
import { Camera } from '../classes/camera';
import { Drone, DroneStatus } from '../classes/drone';
import { Obstacle } from '../classes/obstacle';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  private drones: Drone[] = [
    new Drone(1, -1.5, -2, -140, DroneStatus.Waiting, 80, false),
    new Drone(2, 0.6, 1.8, 0, DroneStatus.OnMission, 40, false),
  ];

  private obstacles: Obstacle[] = [
    new Obstacle(1, 2.0, 2.0),
    new Obstacle(2, 1.5, 1.5)
  ];

  private cameras: Camera[] = this.loadCameras(this.drones);

  context: CanvasRenderingContext2D | null = null;
  
  constructor() { }

  update(data: number[][]) {
    let droneIndex = 0;
    for(let i = 0; i< data.length; i++) {
      let realdata = data[i][0] as unknown as number[]
      this.drones[droneIndex].setX(realdata[1]/100);
      this.drones[droneIndex].setY(realdata[2]/100);
      this.drones[droneIndex].setOrientation(realdata[3]/100);
      droneIndex++;
    }
  }
  // data [[id, sta, x, y, z, distFront, distBack, distLeft, distRight, battery]
  updateSimulatorData(map: Map<string, unknown>) {
    let droneIndex = 0;
    for (let value of map.values()) {
      let objValue = value as any[]; 
      this.drones[droneIndex].setX(objValue[2]);
      this.drones[droneIndex].setY(objValue[3]);
      this.drones[droneIndex].setStatus(objValue[1]);
      this.drones[droneIndex].setBatteryLevel(objValue[9] * 100);
      this.drones[droneIndex].setSimulationId(objValue[0]);
      droneIndex++;
    }
  }

  updatePhysiqueData(packet: any) {
    console.log(packet)
    this.drones[packet.idx-1].setX(packet.pos_x / 10);
    this.drones[packet.idx-1].setY(packet.pos_y / 10);
    this.drones[packet.idx-1].setBatteryLevel(packet.battery_level);
    if (packet.crashed == 1)
        this.drones[packet.idx-1].setStatus('Crashed');
  }

  updateFromMap(value:any, key:any, map:any) {
    console.log(`m[${key}] = ${value}`);
  }

  loadCameras(drones: Drone[]): Camera[] {
    let cameras: Camera[] = [];
    for (let drone of drones) {
      cameras.push(new Camera(drone, this.obstacles, undefined));
    }
    return cameras.concat([new Camera(undefined, undefined, cameras)]);
  }

  getCameras() {
    return this.cameras.slice();
  }

  getDrones() {
    return this.drones.slice();
  }

  exportCanvasContext(context: CanvasRenderingContext2D) {
    this.context = context
    return this.context;
  }

  addObstacles(idx: number, coords: number[]) {
    this.obstacles.push(new Obstacle(idx, coords[0], coords[1]));
    this.cameras.forEach((camera:Camera) => {
      if (camera.drones[0].id = idx)
        camera.obstacles = this.obstacles.filter((obstacle: Obstacle) => { return obstacle.id == idx;})
    })
  }

  addObstaclesHelper(packet: any) {
    let index = packet.idx;
    let obstacles = packet.obstacles;
    obstacles.forEach((obstacle: number[]) => {
      this.addObstacles(index, obstacle);
    });
  }

  drawMap(mapDisplay: ElementRef, drones: Drone[], obstacles?: Obstacle[]) {
    let context: CanvasRenderingContext2D = mapDisplay.nativeElement.getContext('2d')!;
    let rec = mapDisplay.nativeElement.getBoundingClientRect();

    mapDisplay.nativeElement.width = rec.width * devicePixelRatio;
    mapDisplay.nativeElement.height = rec.height * devicePixelRatio;
    context.scale(devicePixelRatio, devicePixelRatio);

    mapDisplay.nativeElement.style.width = rec.width + "px";
    mapDisplay.nativeElement.style.height = rec.height + "px";
    
    this.exportCanvasContext(context);
    this.drawAxis(context, rec);
    this.drawDrones(context, rec, drones);
    
    if(obstacles)
    {
      console.log("Condition Obstacle: ", obstacles)
      this.drawObstacles(context, rec, obstacles);
    }
  }

  drawObstacles(context: CanvasRenderingContext2D, rec:any, obstacles: Obstacle[]) {
    for (let obstacle of obstacles){
      let pixelX = ((obstacle.x + 2.5) / 5 * rec.width);
      let pixelY = ((obstacle.y + 2.5) / 5 * rec.height);
      context.fillStyle = 'black';
      context.fillRect(pixelX, pixelY, 5, 5);
    }
  }

  drawDrones(context: CanvasRenderingContext2D, rec:any,  drones: Drone[]) {
    if (!drones) return;
    for (let drone of drones) {
      let pixelX = ((drone.x + 2.5) / 5 * rec.width);
      let pixelY = ((drone.y + 2.5) / 5 * rec.height);
      this.drawDrone(context, pixelX, pixelY, drone.orientation, 1);
    }
  }

  drawDrone(context: CanvasRenderingContext2D,x: number, y: number, orientation: number, scale: number) { 
    let size = 12 * scale;
    context.translate(-size/2, -size/2)
    context.fillStyle = 'black';
    context.fillRect(x, y, size, size);
    this.drawCircle(context, x       , y       , 3 * scale);
    this.drawCircle(context, x       , y + size, 3 * scale);
    this.drawCircle(context, x + size, y       , 3 * scale);
    this.drawCircle(context, x + size, y + size, 3 * scale);
  }

  drawCircle(context: CanvasRenderingContext2D, x: number, y: number, radius:number) {
    context.beginPath();
    context.arc(x, y, radius, 0, 2 * Math.PI, false);
    context.fillStyle = 'white';
    context.fill();
    context.lineWidth = 1;
    context.strokeStyle = '#00000';
    context.stroke();
  }

  drawDroneVision(context: CanvasRenderingContext2D, x: number, y: number, droneSize: number, radius:number) {
    context.beginPath();
    context.lineTo(x + droneSize / 2, y + droneSize / 2);
    context.arc(x + droneSize / 2, y + droneSize / 2, radius, - Math.PI / 6, Math.PI / 6, false);
    context.lineTo(x + droneSize / 2, y + droneSize / 2);
    context.fillStyle = 'rgba(0, 255, 0, 0.3)';
    context.fill();
    context.strokeStyle = 'green';
    context.stroke();

    context.beginPath();
    context.arc(x + droneSize / 2, y + droneSize / 2, radius, 0, 2 * Math.PI, false);
    context.lineWidth = 0;
    context.fillStyle = 'rgba(0, 255, 0, 0.3)';
    context.fill();
  }

  drawAxis(context: CanvasRenderingContext2D, rec: any) {
    let xAxis = [-2, -1, 0, 1, 2];
    let yAxis = [-2, -1, 0, 1, 2];
    for( let x = 0; x< xAxis.length; x++) {
      context.strokeStyle = 'rgba(0, 0, 0, 0.3)';
      if (xAxis[x] === 0 && yAxis[x] === 0) {
        context.strokeStyle = 'rgba(0, 0, 0, 1)';
      }
      context.beginPath();
      context.moveTo((xAxis[x] + 2.5) /5 * rec.width, 0         );
      context.lineTo((xAxis[x] + 2.5) /5 * rec.width, rec.height);
      context.stroke();

      context.beginPath();
      context.moveTo(0        , (yAxis[x] + 2.5) /5 * rec.height);
      context.lineTo(rec.width, (yAxis[x] + 2.5) /5 * rec.height);
      context.stroke();
    }
  }
}
