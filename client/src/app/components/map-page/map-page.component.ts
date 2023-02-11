import { AfterViewInit, Component, ElementRef, OnInit, ViewChild } from '@angular/core';
import { Camera } from 'src/app/classes/camera';
import { Drone, DroneStatus } from 'src/app/classes/drone';
import { DataService } from 'src/app/services/data.service';

@Component({
  selector: 'app-map-page',
  templateUrl: './map-page.component.html',
  styleUrls: ['./map-page.component.scss']
})
export class MapPageComponent implements OnInit, AfterViewInit {

  @ViewChild('mapDisplay') 
  mapDisplay: ElementRef<HTMLCanvasElement> = {} as ElementRef;
  
  cameras = [new Camera(undefined, undefined)];
  selectedCam: any;

  constructor (private dataService: DataService) {  
  }

  ngOnInit(): void {
    this.setup(this.dataService.getCameras());
    this.selectedCam = this.cameras[0];
  }

  ngAfterViewInit() {
    this.dataService.drawMap(this.mapDisplay, this.cameras[0].drones, this.cameras[0].obstacles);
  }
  
  setup(cameras: Camera[]) {
    this.cameras.pop();
    for (let camera of cameras) {
      this.cameras.push(camera);
    }
  }

  selectCamera(index: number): void { 
    this.selectedCam = this.cameras[index];
    this.dataService.drawMap(this.mapDisplay, this.cameras[index].drones, this.cameras[0].obstacles);
  }

}
