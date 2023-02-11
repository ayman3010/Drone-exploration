import { Component, ElementRef, OnInit, ViewChild } from '@angular/core';
import { CommunicationService } from 'src/app/services/communication.service';
import { DataService } from 'src/app/services/data.service';
import { DashboardComponent } from '../dashboard/dashboard.component';

enum DroneMode{
  Physical = 0,
  Simulation
};

@Component({
  selector: 'app-database-page',
  templateUrl: './database-page.component.html',
  styleUrls: ['./database-page.component.scss']
})
export class DatabasePageComponent implements OnInit{

  @ViewChild('mapDisplay', { read: ElementRef })
  mapDisplay: ElementRef<HTMLCanvasElement> = {} as ElementRef;

  constructor(private communicationService: CommunicationService, private dataService: DataService) {}

  missionData= [
    {
      number_of_drones: 1,
      date: "2022/09/24",
      time: "10:25",
      flight_time: 10,
      flight_type: "flight",
      flight_distance: 25.6
    },
  ];

  ngOnInit() {
    this.communicationService.emit("get-flight-db")
    this.communicationService.listen('flight_db').subscribe((flights) => {
      // let dataString = JSON.stringify(flights);
      // console.log("_______________________")
      // const map = Object.entries(JSON.parse(JSON.stringify(flights)));
      const map = JSON.parse(JSON.parse(JSON.stringify(flights)));
      // console.log(map);
      // let information = JSON.parse(dataString);
      this.missionData = map;
    })

    this.communicationService.emit('get-map-db')
    this.communicationService.listen('map_db').subscribe((map) => {
      console.log(map);
      const mapData = JSON.parse(JSON.parse(JSON.stringify(map)))
      console.log(mapData)
    })

    // this.dataService.drawMap(this.mapDisplay, []);
  }

  
  missionMode(mode: string): string {
    switch(mode) {
      case "flight": return "Drone Physique";
      break;
      case "simulation": return "Simulation";
      break;
      default: return "Undefined";
    }
  }

}
