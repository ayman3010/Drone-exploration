import { AfterViewInit, Component, ElementRef, OnInit, ViewChild } from '@angular/core';
import { Camera } from 'src/app/classes/camera';
import { Drone, DroneStatus } from 'src/app/classes/drone';
import { AreaSelectorService } from 'src/app/services/area-selector.service';
import { CommunicationService } from 'src/app/services/communication.service';
import { DataService } from 'src/app/services/data.service';
@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss']
})


export class DashboardComponent implements OnInit, AfterViewInit {
  
  @ViewChild('mapDisplay', { read: ElementRef })
  mapDisplay: ElementRef<HTMLCanvasElement> = {} as ElementRef;
  
  dronesData:Drone[] = [new Drone(1, 80, DroneStatus.Waiting, 0.0, 0.0, 0, false)];
  cameras = [new Camera(undefined, undefined)];
  logMsgs =['Système: Application Started...']
  selectedDrone = this.dronesData[0];
  selectedCamera = this.cameras[0];
  isSimulation: boolean = false;
  isFlying:boolean = (this.selectedDrone.status == DroneStatus.TakeOff || 
                      this.selectedDrone.status == DroneStatus.OnMission ||
                      this.selectedDrone.status == DroneStatus.Landing);
  startX:number = 0;
  startY:number = 0;
  width: number = 0;
  height: number = 0;
  isSelecting:boolean = false;
  isDrawn: boolean = false;
  zoneSelect: any = {x: 0, y: 0, width: 610, height: 610};

  constructor(private dataService: DataService, private communicationService: CommunicationService, private selector: AreaSelectorService) {

  }
 
  ngOnInit() {
    this.setup(this.dataService.getDrones(), this.dataService.getCameras());
    this.selectedCamera = this.cameras[0];
    this.selectedDrone = this.dronesData[0];
    // Simulation Listening
    this.communicationService.listen('simulation_update_drones').subscribe((data) => {
      console.log('ehatattat')
      let dataString = JSON.stringify(data);
      const map = new Map(Object.entries(JSON.parse(dataString)));
      this.dataService.updateSimulatorData(map);
      this.dataService.drawMap(this.mapDisplay, [this.selectedCamera.drones[0]], this.selectedCamera.obstacles);
      this.logMsgs.push(`Systeme: Drones Data Map Received From Simulator!`);
      this.printLogFromMap(map);
    })
    this.communicationService.listen('simulation_command_log').subscribe((msg) => {
      this.logMsgs.push(`Drone ${this.selectedDrone.id}: ${msg}`);
    })
    this.communicationService.listen('new_obstacle_simulation').subscribe((msg) => {
      let msgString = JSON.stringify(msg)
      let obstacle = JSON.parse(msgString);
      this.dataService.addObstaclesHelper(obstacle);
    })
    this.communicationService.listen('send_logs').subscribe((msg) => {
      let logString = JSON.stringify(msg);
      let packet_parsed = JSON.parse(logString);
      console.log(`LEFT: ${packet_parsed.obs_left}, RIGHT: ${packet_parsed.obs_right}`);
      let msgPushed = `Packet[id: ${packet_parsed.idx}, x: ${packet_parsed.pos_x},y: ${packet_parsed.pos_y},right: ${packet_parsed.obs_right},left: ${packet_parsed.obs_left},front: ${packet_parsed.obs_front},back: ${packet_parsed.obs_back}, battery level: ${packet_parsed.battery_level}]`;
      this.logMsgs.push(msgPushed)
      this.dataService.updatePhysiqueData(packet_parsed);
      this.dataService.drawMap(this.mapDisplay, [this.selectedCamera.drones[0]], this.selectedCamera.obstacles);
      // this.communicationService.emit('get_logs');
    })
    this.communicationService.listen('new_obstacle').subscribe((obstacle) => {
      this.dataService.addObstaclesHelper(obstacle);
    })

    this.communicationService.listen('command_ack').subscribe((message) => {
      console.log(message);
    })

    this.communicationService.listen('new_obstacle_simulation').subscribe((msg) => {
      let msgString = JSON.stringify(msg)
      let obstacle = JSON.parse(msgString);
      this.dataService.addObstaclesHelper(obstacle);
    })
  }

  ngAfterViewInit() {
    this.dataService.drawMap(this.mapDisplay, [this.selectedCamera.drones[0]], this.selectedCamera.obstacles);
    
    this.selector.context = this.dataService.context;
  }

  sendZoneSelection() {
    let x = (document.querySelector('input[id=x]') as HTMLInputElement).value;
    let y = (document.querySelector('input[id=y]') as HTMLInputElement).value;
    let width = (document.querySelector('input[id=width]') as HTMLInputElement).value;
    let height = (document.querySelector('input[id=height]') as HTMLInputElement).value;

    if ( Math.abs(Number(x)) > 2.5)
      window.alert("Enter Valid X");
    if ( Math.abs(Number(y)) > 2.5)
      window.alert("Enter Valid Y");
    if ( Number(width) < 0)
      window.alert("Enter Valid Width");
    if ( Number(height) < 0)
      window.alert("Enter Valid Height");
    this.zoneSelect = {x: x, y: y, width: width, height: height};
    let zone_string = `${this.zoneSelect.x} ${this.zoneSelect.y} ${this.zoneSelect.width} ${this.zoneSelect.height}`;
    console.log(this.zoneSelect);
    this.communicationService.emit('select_zone_client', zone_string)
  }

  setup(dronesData: Drone[], cameras: Camera[]) {
    this.dronesData.pop();
    for (let drone of dronesData) {
      this.dronesData.push(drone);
    }
    this.cameras.pop();
    for (let camera of cameras) {
      this.cameras.push(camera);
    }
    this.cameras.pop();
  }

// data [[id, sta, x, y, z, distRight, distFront, distLeft, distBack, battery]
  printLogFromMap(map: Map<any, any>) {
    let cfIndex = 0;
    for ( let value of map.values()) {
      this.logMsgs.push(`Drone ${cfIndex+1}: status: ${value[1]}, x: ${value[2]}, y: ${value[3]}, battery-level: ${value[9]}, obstacle-right: ${value[5]}, obstacle-front: ${value[6]}, obstacle-left: ${value[7]}, obstacle-back: ${value[8]}`);
      cfIndex++;
    }

  }

  //Style Methods
  batteryStyle(batteryLevel: number): string {
    if      (batteryLevel >= 50) return "";
    else if (batteryLevel >= 30) return "battery-medium";
    else if (batteryLevel >= 0)  return "battery-low";
    else return "";
  }

  droneStatus(statusValue: number): string {
    switch(statusValue) {
      case DroneStatus.Waiting: return "En attente";
      break;
      case DroneStatus.TakeOff: return "Décollage";
      break;
      case DroneStatus.OnMission: return "En mission";
      break;
      case DroneStatus.Landing: return "Atterrissage";
      break;
      case DroneStatus.BackToBase: return "Retour à la base";
      break;
      case DroneStatus.Crashed: return "Écrasé";
      break;
      default: return "En Attente";
    }
  }


  //Buttons Methods
  identify(): void {
    try {
      if (this.isSimulation)
        this.communicationService.emit('identify', this.selectedDrone.simulationId, this.isSimulation);
      else 
        this.communicationService.emit('identify', this.selectedDrone.id, this.isSimulation);

      this.logMsgs.push(`Drone ${this.selectedDrone.id} : Identification Request Sent To Server!`);
    } catch (HttpErrorResponse) {
      this.logMsgs.push('Systeme: (Identification) Connection to server failed!')
    }
  }

  start(): void {
    let droneIndex = this.dronesData.indexOf(this.selectedDrone);
    this.dronesData[droneIndex].status = DroneStatus.OnMission;
    console.log("Status: ", this.selectedDrone.status, this.isFlying);
    try {
      if (this.isSimulation)
        this.communicationService.emit('launch_mission', this.selectedDrone.simulationId, this.isSimulation);
      else {
        this.communicationService.emit('launch_mission', this.selectedDrone.id, this.isSimulation);
      }
    } catch (HttpErrorResponse) {
      this.logMsgs.push('Systeme: (Start Mission) Connection to server failed!')
    }  
  }

  finish(): void {
    let droneIndex = this.dronesData.indexOf(this.selectedDrone);
    this.dronesData[droneIndex].status = DroneStatus.Landing;
    //Log Message
    try {
      if (this.isSimulation) {
        this.communicationService.emit('end_mission', this.selectedDrone.simulationId, this.isSimulation);
      } else {
        this.communicationService.emit('end_mission', this.selectedDrone.id, this.isSimulation);
      }
    } catch (HttpErrorResponse) {
      this.logMsgs.push('Systeme: (End Mission) Connection to server failed!');
    }
    this.logMsgs.push(`Drone ${this.selectedDrone.id} : Mission Finished!`);
  }

  peerToPeer(): void {
    this.logMsgs.push(`Drone ${this.selectedDrone.id} : PeerToPeer Stat Changed!`);
  }

  backToBase(): void {
    let droneIndex = this.dronesData.indexOf(this.selectedDrone);
    this.dronesData[droneIndex].status = DroneStatus.BackToBase;
    if (this.isSimulation) {
      this.communicationService.emit('return_to_base_client', this.selectedDrone.simulationId, this.isSimulation);
    } else {
      this.communicationService.emit('return_to_base_client', this.selectedDrone.id, this.isSimulation);

    }
    // Log Message
    this.logMsgs.push(`Drone ${this.selectedDrone.id} : Coming back to base!`);
  }
  startRequest() {
    setInterval(() => {this.logRequest();}, 1000);
  }

  logRequest() {
    // if(!this.communicationService) return;
    this.communicationService.logRequest(this.selectedDrone.id).subscribe((msg) => {
      let logString = JSON.stringify(msg);
      let packet_parsed = JSON.parse(logString);
      console.log(`LEFT: ${packet_parsed.obs_left}, RIGHT: ${packet_parsed.obs_right}`);
      let msgPushed = `Packet[id: ${packet_parsed.idx}, x: ${packet_parsed.pos_x},y: ${packet_parsed.pos_y},right: ${packet_parsed.obs_right},left: ${packet_parsed.obs_left},front: ${packet_parsed.obs_front},back: ${packet_parsed.obs_back}, battery level: ${packet_parsed.battery_level}]`;
      this.logMsgs.push(msgPushed);
      this.dataService.updatePhysiqueData(packet_parsed);
      this.dataService.drawMap(this.mapDisplay, [this.selectedCamera.drones[0]], this.selectedCamera.obstacles);
    });
  }

  connectDrones(): void {
    // To be Implemented
    this.logMsgs.push(`System: Drone Connect Request Sent!`);
  }

  simulate() {
    this.isSimulation = !this.isSimulation;
  }

  //Select Option Change Methods
  onCameraChange(newCamera: any) {
    this.dataService.drawMap(this.mapDisplay, [newCamera.drones[0]]);
  }

  onDroneChange(newDrone: any) {
    this.selectedDrone = newDrone;
  }


  //Download Log Methods
  download(): void {
    this.writeContent(this.logMsgs, 'mission-log'+'.txt', 'text/plain');
  }

  writeContent(content:any, fileName:string, contentType:string): void {
    let a = document.createElement('a');
    let file = new Blob([content], {type: contentType});
    a.href = URL.createObjectURL(file);
    a.download = fileName;
    a.click();
  }

}
